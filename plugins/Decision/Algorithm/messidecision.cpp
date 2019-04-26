#include "messidecision.h"
#include "receivePos.h"
#include "SkillUtils.h"
#include <QDebug>
#include "GDebugEngine.h"
#include "BallStatus.h"
#include "RobotSensor.h"
#include "parammanager.h"
#include "param.h"
#include "ShootRangeList.h"
#include "runpos.h"
#include <QRandomGenerator>
#include <iostream>
#include "WorldModel.h"

#ifdef USE_CUDA_MODULE
#include "CUDAModule/CUDAModule.h"
#endif

namespace {
bool TEST_PASS;
//生成跑位点的随机性
const double runPosEpsilon = 0.2;
//判断进攻车数量的参数
enum Field {
    FrontField = 1,
    MiddleField = 2,
    BackField = 3
};
const int front = 200; //判断前场的边界
const int back = -200; //判断后场的边界
const int buffer = 100;//缓冲区大小,避免在边界处变化太快

//更新接球点所需参数
const double recomputeDist1 = 50;
const double recomputeDist2 = 75;
int lastRecomputeCycle = 0;
const int recomputeInterval = 60;

const double powerBuffer = 1;
const CGeoPoint shootPos[3] = {CGeoPoint(200, 0), CGeoPoint(215, 70), CGeoPoint(215, -70)};
//避免射门后马上改变leader
const int minShootInterval = 50;
//射门时其他车的静态跑位点
const CGeoPoint STATIC_POS[2] = {CGeoPoint(Param::Field::PITCH_LENGTH / 4, Param::Field::PITCH_WIDTH / 4),
                                 CGeoPoint(Param::Field::PITCH_LENGTH / 4, -Param::Field::PITCH_WIDTH / 4)};
}

CMessiDecision::CMessiDecision()
    : _leader(1)
    , _receiver(2)
    , _leaderPassStateCount(0)
    , _leaderStealStateCount(0)
    , _cycle(0)
    , _lastChangeLeaderCycle(-999)
    , _lastUpdateRunPosCycle(-999)
    , _lastCanShootCycle(-999)
    , _lastAreaNum(-1)
    , _attackerAmount(1)
    , _passVel(0)
    , _messiRun(false)
    , _ourBall(false)
    , _theirBall(false)
    , _both(false)
    , _frared(false)
    , _isFlat(true)
    , _state("initState")
    , _laststate("initState")
    , _pVision(nullptr) {
    ZSS::ZParamManager::instance()->loadParam(TEST_PASS, "Test/NormalPlayPassTestPass", false);
}

void CMessiDecision::generateAttackDecision(const CVisionModule* pVision) {
    //更新图像信息
    _pVision = pVision;
    _cycle = pVision->Cycle();

    //判断是否需要reset
//    if(sth) reset();

    //Ball state
    judgeBallState();

    //判断进攻车数量
    judgeAttackerAmount();

//    //判断Leader的状态，给Leader的Skill使用
//    judgeLeaderState();

    //计算state
    judgeState(); //accroding to ball state

    //计算leader
    //此处应该有多种情况，①进攻时将receiver赋给Leader，②初始化leader，③状态改为Getball时如何确定Leader
    generateLeaderPos();
    confirmLeader();

    //计算Receiver跑位点
    if (needReceivePos()) {
        // just for test
//        RunPosModule::Instance()->generateRunPos(1);
//        updateRunPos();
        generateReceiverAndPos();
    }

    //计算其他进攻车的跑位点
    if (needRunPos()) {
        generateOtherRunPos();
    }

//    GDebugEngine::Instance()->gui_debug_x(RunPosModule::Instance()->runPos(0));
//    GDebugEngine::Instance()->gui_debug_x(RunPosModule::Instance()->runPos(1));
//    GDebugEngine::Instance()->gui_debug_x(RunPosModule::Instance()->runPos(2));
//    GDebugEngine::Instance()->gui_debug_x(RunPosModule::Instance()->runPos(3));

    //test部分
//    _state = "test";
//    _leader = 2;
//    _receiver = 3;

    //进攻车数量
//    _attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision, _leader); //可能要重写
    //判断是否需要getball
//    _state = "GetBall" + to_string(_attackerAmount);
//    GDebugEngine::Instance()->gui_debug_msg(_leaderPos, QString("LR").toLatin1(), COLOR_GREEN);
//    GDebugEngine::Instance()->gui_debug_msg(_receiverPos, QString("R").toLatin1(), COLOR_GREEN);
//    GDebugEngine::Instance()->gui_debug_msg(_otherPos[0], QString("1").toLatin1(), COLOR_GREEN);
//    GDebugEngine::Instance()->gui_debug_msg(_otherPos[1], QString("2").toLatin1(), COLOR_GREEN);
//    GDebugEngine::Instance()->gui_debug_msg(_otherPos[2], QString("3").toLatin1(), COLOR_GREEN);
//    GDebugEngine::Instance()->gui_debug_msg(_otherPos[3], QString("4").toLatin1(), COLOR_GREEN);
//    GDebugEngine::Instance()->gui_debug_msg(_receiverPos, QString("R").toLatin1(), COLOR_BLUE);
    GDebugEngine::Instance()->gui_debug_msg(_passPos, QString("PPPPPPP").toLatin1(), _isFlat ? COLOR_BLUE : COLOR_ORANGE);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, 40), QString("leader: %1  receiver: %2").arg(_leader).arg(_receiver).toLatin1(), COLOR_ORANGE);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, 60), QString("Kicked: %1").arg(BallStatus::Instance()->IsBallKickedOut(_leader + 1)).toLatin1(), COLOR_ORANGE);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, 80), QString("BallVel: %1 Vision Vel: %2").arg(_passVel).arg(pVision->Ball().Vel().mod()).toLatin1(), COLOR_ORANGE);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, 100), QString("recompute: %1").arg(lastRecomputeCycle).toLatin1(), COLOR_ORANGE);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, 120), QString("canshoot: %1").arg(canShoot()).toLatin1(), COLOR_ORANGE);
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, 140), _state.c_str(), COLOR_ORANGE);
    //只用于显示传球点是否合理
    // ZCUDAModule::instance()->calculateBestPass();
    //获得laststate方便计算点的判断
    _laststate = _state;
}

void CMessiDecision::judgeBallState() {
    string ballStatus = ZSkillUtils::instance()->getBallStatus();
    _frared = RobotSensor::Instance()->IsInfraredOn(_leader + 1);
//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(150, 300), QString("frared is %1").arg(_frared).toLatin1()); //wzdebug
    _ourBall = (ballStatus == "Our" || ballStatus == "OurHolding");
    _theirBall = (ballStatus == "Their" || ballStatus == "TheirHolding");
    _both = (ballStatus == "Both" || ballStatus == "BothHolding");//这里和pp不同
}

// 根据球的位置判断attacker amount
void CMessiDecision::judgeAttackerAmount() {
    static Field field = BackField;
    const MobileVisionT& ball = _pVision->Ball();
    // 判断球所在区域
    switch (field) {
    case FrontField:
        if(ball.X() < back)
            field = BackField;
        else if(ball.X() < front - buffer)
            field = MiddleField;
        break;
    case MiddleField:
        if(ball.X() > front)
            field = FrontField;
        else if(ball.X() < back)
            field = BackField;
        break;
    case BackField:
        if(ball.X() > front)
            field = FrontField;
        else if(ball.X() > back + buffer)
            field = MiddleField;
        break;
    }
    // 根据球所在区域判断进攻车数量
    switch (field) {
    case FrontField:
        _attackerAmount = _ourBall ? 3 : _both ? 2 : 2;
        break;
    case MiddleField:
        _attackerAmount = _ourBall ? 3 : _both ? 2 : 1;
        break;
    case BackField:
        _attackerAmount = _ourBall ? 3 : _both ? 1 : 1;
        break;
    }
//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(400, 0), QString("%1").arg(_attackerAmount).toLatin1(), COLOR_RED);
}

void CMessiDecision::judgeState() {
    static int count = 0;
    string temp = "GetBall";
    static string lastTemp = "GetBall";
    //所有状态机的判断
//    int bestInterPlayer = _leader + 1;
//    double bestInterTime = ZSkillUtils::instance()->getOurInterTime(bestInterPlayer);
//    for (int i=2; i <= Param::Field::MAX_PLAYER; i++) {
//        double interTime = ZSkillUtils::instance()->getOurInterTime(i);
//        if(interTime < bestInterTime){
//            bestInterPlayer = i;
//            bestInterTime = interTime;
//        }
//    }
//    if (bestInterTime > ZSkillUtils::instance()->getTheirBestInterTime() + 0.2){
//    if(_ourBall){
//        temp = "Pass";
//    } else {
//        temp = "GetBall";
//    }
    if(_state == "GetBall" && ZSkillUtils::instance()->getBallStatus() == "OurHolding") {
        temp = "Pass";
    } else if((_state == "Pass" && !_ourBall) || _state == "initState" ) {
        temp = "GetBall";
    } else {
        temp = _state;
    }
    //状态机持续时间大于5帧，跳转
    if (lastTemp != temp) {
        count = 0;
    } else {
        count++;
    }
    if (temp == "Pass" && count >= 20) {
        _state = "Pass";
    } else if (temp == "GetBall" && count >= 5) {
        _state = "GetBall";
    }
    lastTemp = temp;
//    _state = "Pass";
//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, -20), _state.c_str());
//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, -30), lastTemp.c_str());
}

void CMessiDecision::generateLeaderPos() {
    if(_state == "GetBall")
        _leaderPos = _pVision->Ball().Pos();
    else
        _leaderPos = _receiverPos;
}

void CMessiDecision::confirmLeader() {
    //选择最快拦截球的车作为leader,而不是单纯使用距离
    int bestInterPlayer = _leader + 1;
    double bestInterTime = ZSkillUtils::instance()->getOurInterTime(bestInterPlayer);
    if ((_state != _laststate || _state == "GetBall") && _cycle - _lastChangeLeaderCycle > 10) {
        //从2开始,不选择守门员
        for (int i = 2; i <= Param::Field::MAX_PLAYER; i++) {
            double interTime = ZSkillUtils::instance()->getOurInterTime(i);
            if(interTime < bestInterTime) {
                bestInterPlayer = i;
                bestInterTime = interTime;
            }
        }
        _leader = bestInterPlayer - 1;
        _lastChangeLeaderCycle = _cycle;
    } else if (BallStatus::Instance()->IsBallKickedOut(_leader + 1) && _cycle - _lastChangeLeaderCycle > 10 && _cycle - _lastCanShootCycle > minShootInterval) {
        changeLeaderToReceiver();
    }
#ifdef USE_CUDA_MODULE
    ZCUDAModule::instance()->setLeader(_leader);
#endif
}

void CMessiDecision::changeLeaderToReceiver() {
    _leader = _receiver;
    _lastChangeLeaderCycle = _cycle;
}

bool CMessiDecision::needReceivePos() {
    static int holdBallCnt = 0;
    holdBallCnt = ((_pVision->OurPlayer(_leader + 1).Pos() - _pVision->Ball().Pos()).mod() <= 15) ? holdBallCnt+1 : 0;

    //增加条件时写出调用哪个函数时使用，方便分辨条件之间的与或关系
    if (_laststate != _state) {//GetBall
        return true;
    } else if (_cycle == _lastChangeLeaderCycle) { //changeLeaderToReceiver
        return true;
    }
    // 当leader快拿到球的时候更新接球点,因为场上形势已经发生改变
    else if((_pVision->OurPlayer(_leader + 1).Pos() - _pVision->Ball().Pos()).mod() > recomputeDist1 && (_pVision->OurPlayer(_leader + 1).Pos() - _pVision->Ball().Pos()).mod() < recomputeDist2 && _cycle - lastRecomputeCycle > recomputeInterval) {
        lastRecomputeCycle = _cycle;
//        static int count = 0;
//        std::cout << "recomputing receive pos: " << count++ << std::endl;
        return true;
    }
    else if(holdBallCnt >= 180){
        lastRecomputeCycle = _cycle;
        holdBallCnt = 0;
        return true;
    }
    return false;
}

bool CMessiDecision::needRunPos() {
    bool needRunPos = false;
    //GetBall
    if (_laststate != _state) {
        needRunPos = true;
    }
    //changeLeaderToReceiver
    else if (_cycle == _lastChangeLeaderCycle) {
        needRunPos = true;
    }
    //每隔一段时间更新runPos
    else if (_cycle - _lastUpdateRunPosCycle > 50) {
        needRunPos = true;
    }
    //射门时不需要算
    if(canShoot())
        needRunPos = false;
    return needRunPos;
}

void CMessiDecision::generateReceiverAndPos() {
    //防止场上只有两辆车的时候把receiver赋给leader
//    if(_pVision->getValidNum() <= 2){
//        _receiver = 999;
//        return;
//    }
#ifdef USE_CUDA_MODULE

    ZCUDAModule::instance()->calculateBestPass(); //maybe wrong!!!!!!!!!!!!!!!!!!!!!!!!!!!

    _receiverPos = ZCUDAModule::instance()->getBestFlatPass();
//    if(ZSkillUtils::instance()->IsInField(_receiverPos)) {
    if(ZSkillUtils::instance()->IsInField(_receiverPos) && (getEnemyAmountInArea(_pVision->OurPlayer(_leader + 1).Pos(), 50) < getEnemyAmountInArea(_receiverPos, 50) || getEnemyAmountInArea(_pVision->OurPlayer(_leader + 1).Pos(), 50) == 0)) {
        _receiver = ZCUDAModule::instance()->getBestFlatPassNum() ? ZCUDAModule::instance()->getBestFlatPassNum() : _receiver;
//        _passVel = ZCUDAModule::instance()->getBestFlatPassVel() * powerBuffer;
//        std::cout << "_passVel is " << _passVel << std::endl;
        _isFlat = true;
//        std::cout << "generate" << _leader << _receiver << std::endl;
    } else {
        _receiverPos = ZCUDAModule::instance()->getBestChipPass();
        _receiver = ZCUDAModule::instance()->getBestChipPassNum() ? ZCUDAModule::instance()->getBestChipPassNum() : _receiver;
//        _passVel = ZCUDAModule::instance()->getBestChipPassVel() * powerBuffer;
//        std::cout << "_passVel is " << _passVel << std::endl;
        _isFlat = false;
    }
//    std::cout << "passVel: " << _passVel << std::endl;
//    std::cout << "receiver Num: " << _receiver << std::endl;
    //解决receiver在leader射门时到禁区接球的问题
    if (canShoot()) {
        _passPos = CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0);
        _isFlat = true;
        //receiver应该跑的点，避免挡住射门路线
//        CGeoPoint receiverPos = _pVision->OurPlayer(_receiver+1).Pos();
//        CVector goalToReceiver = receiverPos - CGeoPoint(Param::Field::PITCH_LENGTH/2, 0);
//        _receiverPos = CGeoPoint(Param::Field::PITCH_LENGTH/2, 0) + goalToReceiver/goalToReceiver.mod()*otherDistToGoal;
        _receiverPos = _pVision->OurPlayer(_leader + 1).Pos().y() < 0 ? STATIC_POS[0] : STATIC_POS[1];
        _lastCanShootCycle = _cycle;
//        qDebug() << "canShoot!!!";
    } else {
        _passPos = _receiverPos;
    }


#else
    ReceivePosModule::Instance()->generatePassPos(_pVision, _leader);
    _receiver = ReceivePosModule::Instance()->bestReceiver();
    _receiverPos = ReceivePosModule::Instance()->bestPassPoint();
    _isFlat = true;
    _passVel = 300;
#endif
}

void CMessiDecision::generateOtherRunPos() {
//    qDebug() << "generate run pos";
//    RunPosModule::Instance()->generateRunPos(_pVision, runPosEpsilon);
//    _otherPos[0] = RunPosModule::Instance()->runPos(0);
//    _otherPos[1] = RunPosModule::Instance()->runPos(1);
//    _otherPos[2] = RunPosModule::Instance()->runPos(2);
//    _otherPos[3] = RunPosModule::Instance()->runPos(3);
    //test
    _otherPos[0].setX(Param::Field::PITCH_LENGTH / 2 - _receiverPos.x());
    _otherPos[0].setY(-_receiverPos.y());
    _lastUpdateRunPosCycle = _cycle;
}

bool CMessiDecision::canShoot() {
    if (TEST_PASS) {
        return false;
    }
    const PlayerVisionT& me = _pVision->OurPlayer(_leader + 1);
    bool _canshoot = false;
    CShootRangeList shootRangeList(_pVision, _leader + 1, me.Pos());
    const CValueRangeList& shootRange = shootRangeList.getShootRange();
    if (shootRange.size() > 0) {
        auto bestRange = shootRange.getMaxRangeWidth();
        if (bestRange && bestRange->getWidth() > Param::Field::BALL_SIZE + 5) {	// 要求射门空档足够大
            _canshoot = true;
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, 130), QString("shootRange: %1").arg(bestRange->getWidth()).toLatin1(), COLOR_ORANGE);
        }
    }
    return _canshoot;
}

void CMessiDecision::reset() {
    //在特殊状态后需要重置角色和点
    _state = "GetBall";
    _laststate = "initState";
}

// 门将开大脚时的传球点
CGeoPoint CMessiDecision::goaliePassPos() {
    CGeoPoint leaderPos = _pVision->OurPlayer(_leader + 1).Pos();
//    CGeoPoint leaderPos(100,100);
    // leader在前场时传leader
    if(leaderPos.x() > 0)
        return leaderPos + CVector(50, 0);
    // 否则传到对方禁区前沿制造混乱
    else
        return CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0);
}

int CMessiDecision::getEnemyAmountInArea(CGeoPoint center, int radius) {
    int count = 0;
    for (int i = 1; i <= Param::Field::MAX_PLAYER_NUM; i++) {
        if (_pVision->TheirPlayer(i).Valid() && _pVision->TheirPlayer(i).Pos().dist2(center) <= radius) {
            count++;
        }
    }
    return count;
}
