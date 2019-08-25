#include "ZPass.h"
#include "GDebugEngine.h"
#include <VisionModule.h>
#include "RobotSensor.h"
#include "skill/Factory.h"
#include "ControlModel.h"
#include <utils.h>
#include <DribbleStatus.h>
#include <ControlModel.h>
#include "GDebugEngine.h"
#include "TaskMediator.h"
#include "SkillUtils.h"

namespace {
const int verbose = false;
double MAX_DRIBBLE_DIST = 70; // dribbling ball cannot move more than 80 cm
double SHOOT_ACCURACY = 3 * Param::Math::PI / 180;
double MAX_ACC = 250;
double MAX_ROT_ACC = 10;
double MAX_ROT_SPEED = 10;
double MAX_TURN_DIR = 100 * Param::Math::PI / 180;
int MAX_BLOCK_CNT = 80;
enum {
    TURN = 1,
    SIDEMOVE = 2,
    DRIBBLE = 3,
};
int grabMode = DRIBBLE;
int last_mode = DRIBBLE;
int fraredOn;
int fraredOff;
CGeoPoint dribblePoint;
bool isDribble = false;
int maxFrared = 210;
bool isTurning[Param::Field::MAX_PLAYER + 1];
int blockCnt[Param::Field::MAX_PLAYER + 1] = {0};
bool shepi[Param::Field::MAX_PLAYER + 1];
int turnWay = 2;
int movingWay = 1;
bool returnPoint = false;
}

void CZPass::plan(const CVisionModule* pVision) {
    const MobileVisionT& ball = pVision->Ball();
    const CGeoPoint passTarget = task().player.pos;
    int vecNumber = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    oppNum = BestPlayer::Instance()->getTheirBestPlayer();
    const PlayerVisionT& enemy = pVision->TheirPlayer(oppNum);
    const double power = task().player.kickpower;
    const bool isChip = task().player.ischipkick;

    CVector me2Ball = ball.Pos() - me.Pos();
    CVector me2enemy = enemy.Pos() - me.Pos();
    CVector me2target = passTarget - me.Pos();
    bool canMoveOn = !(fabs(Utils::Normalize(me2target.dir() - me2enemy.dir())) < Param::Math::PI / 4 && me2enemy.mod() < 50); //���硅溅��﹀�ㄦ������
    double delta = fabs(Utils::Normalize(me2enemy.dir() - me.Dir()));
//    if(me2Ball.mod() < 100 && me.Vel().mod() < 150) getballTask.player.flag |= PlayerStatus::NOT_AVOID_THEIR_VEHICLE;
    //灏��ㄨ��稿��
    double finalDir;
    bool canShoot = true;
    if(Utils::InTheirPenaltyArea(passTarget, 0)) {
        KickDirection::Instance()->GenerateShootDir(vecNumber, me.Pos());
        finalDir = KickDirection::Instance()->getRealKickDir();//璁＄�灏��ㄨ�
        canShoot = KickDirection::Instance()->getKickValid();//�ゆ��藉�﹁涪��锛��宠矾绾挎��﹁瀹��ㄥ���
    } else { //涓�灏��ㄥ���存�ヤ���
        finalDir = me2target.dir();
        canShoot = true;
    }
//    cout <<"canShoot: "<<canShoot<< "  "<< 180*fabs(Utils::Normalize(me.Dir() - finalDir))/3.1415926<<endl;
    //�哥��杞���ゆ��
    if (pVision->Cycle() - _lastCycle > 6) {
        isTurning[vecNumber] = false;//杩�6甯ч��绠�
        movingWay = ball.RawPos().y() > 0 ? 1 : -1;
    }
    //sidemove�跺���ゆ��规��︿��存�¤溅
    if(!canMoveOn) blockCnt[oppNum]++;
    else blockCnt[oppNum] = 0;
    //��缁瀵规�规��MAX_BLOCK_CNT 甯у�����㈣蛋浣�
    if(blockCnt[oppNum] > MAX_BLOCK_CNT) {
        blockCnt[oppNum] = 0;//clear bit
        shepi[vecNumber] = ! shepi[vecNumber];
    }
    //30甯ц��ㄩ�㈠��灏卞��︿�涓�瑰����
    if (isTurning[vecNumber] == true) {
        if(! Utils::InTheirPenaltyArea(passTarget, 0)) {
            isTurning[vecNumber] = false;//涓�灏��ㄩ��绠�
        }
    }
    bool frared = RobotSensor::Instance()->IsInfraredOn(vecNumber);
    //甯︽��灏�缂�瀛����界��绾㈠�
    if (frared) {
        fraredOn = fraredOn >= maxFrared ? maxFrared : fraredOn + 1;
        fraredOff = 0;
        if(fraredOn > 5 && !isDribble) {
            dribblePoint = me.Pos(); // when dribble 5 frames, start to mark start point
            isDribble = true;   // not mark my point next time
        }
    } else {
        fraredOn = 0;
        fraredOff = fraredOff >= maxFrared ? maxFrared : fraredOff + 1;
        if(fraredOff > 10) {
            dribblePoint = me.Pos();//if lose ball  frames, dribblePoint become my position
            isDribble = false; //mark my point next time
        }
    }
//    cout << "frared:  "<<frared<<endl;
    TaskT grabTask(task());
    /*********************** judge mode ********************/
    if(fraredOn > 30) {
//        if(delta < MAX_TURN_DIR && me.Dir() < Param::Math::PI/2) grabMode = TURN;
        if(delta < MAX_TURN_DIR && fraredOn < 180) grabMode = TURN;
        else grabMode = SIDEMOVE;
    } else if(fraredOff > 5) {
        grabMode = DRIBBLE;
    }
    if(frared && last_mode == SIDEMOVE) grabMode = SIDEMOVE;
    last_mode = grabMode;
    /*********************** set subTask ********************/
    if(grabMode == TURN) {
        if (verbose) cout << "turn !!!" << endl;
        if(isTurning[vecNumber] == false) {
//            turnWay = Utils::Normalize(me2Ball.dir() - me2target.dir()) > 0 ? 4 : 2;//2锛�宸﹀��锛�4:�冲��
            turnWay = me2target.dir() > 0 ? 4 : 2;//2锛�宸﹀��锛�4:�冲��
            isTurning[vecNumber] = true;
        }
        setSubTask(PlayerRole::makeItOpenSpeedCircle(vecNumber, 5, turnWay, Param::Math::PI, 1, Param::Math::PI / 2));
    }
    if(grabMode == SIDEMOVE) {
        if (verbose) cout << "SIDEMOVE !!!" << endl;
        //if dribbleCnt bigger than MAX_DRIBBLE_CNT, then move back
        if(isDribble && (me.Pos() - dribblePoint).mod() > MAX_DRIBBLE_DIST) {
            //movingWay = - movingWay; // change moving way, but don't change dribblePoint
            returnPoint = true;
        } else returnPoint = false;
        grabTask.player.angle = finalDir;//me2target.dir(); turn to finalDir
        if(canMoveOn)
            grabTask.player.pos = me.Pos() + Utils::Polar2Vector(50, Utils::Normalize(me2target.dir() + movingWay * Param::Math::PI / 2));
        else
            grabTask.player.pos = enemy.Pos() + Utils::Polar2Vector(50, Utils::Normalize(me2target.dir() + movingWay * Param::Math::PI / 2));
        if(returnPoint) grabTask.player.pos = dribblePoint;
//        cout << "Dribble:  "<<(me.Pos() - dribblePoint).mod()<<endl;
        //        cout <<"movingWay: "<<movingWay<<"  canMoveOn: "<<canMoveOn<<endl;
        if(Utils::InTheirPenaltyArea(grabTask.player.pos, 9) || Utils::InTheirPenaltyArea(me.Pos(), 9)) {
//            grabTask.player.pos.setX(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - 15);
            grabTask.player.pos = Utils::MakeOutOfTheirPenaltyArea(grabTask.player.pos, 9);
        }
        if(Utils::OutOfField(me.Pos(), 30) && Utils::OutOfField(grabTask.player.pos,0))
            movingWay = - movingWay;
//        grabTask.player.flag = PlayerStatus::NOT_AVOID_THEIR_VEHICLE | PlayerStatus::DRIBBLING;
        grabTask.player.flag = PlayerStatus::DRIBBLING;
        grabTask.player.max_acceleration = MAX_ACC;
        grabTask.player.max_deceleration = MAX_ACC;
        grabTask.player.max_rot_acceleration = MAX_ROT_ACC;
        grabTask.player.max_rot_speed = MAX_ROT_SPEED;
        setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(grabTask));
    }
    if(grabMode == DRIBBLE) {
        if (verbose) cout << "DRIBBLE !!!" << endl;
        CGeoPoint target;
        double dir;
        if(ball.Valid()) target = ball.Pos() + Utils::Polar2Vector(7, enemy.Dir());
        else target = enemy.Pos() + Utils::Polar2Vector(7, enemy.Dir());
        if(ball.Valid()) dir = me2Ball.dir();
        else dir = me2enemy.dir();
        if(me2Ball.mod() > 50 || ball.Vel().mod() > 50)
            setSubTask(PlayerRole::makeItGetBallV4(vecNumber, PlayerStatus::DRIBBLE, target, CGeoPoint(999, 999), 0));
        else{
            if(Utils::OutOfField(target,Param::Vehicle::V2::PLAYER_SIZE+Param::Field::BALL_SIZE*2))
                target = Utils::MakeInField(target,Param::Vehicle::V2::PLAYER_SIZE+Param::Field::BALL_SIZE*2);
            setSubTask(PlayerRole::makeItGoto(vecNumber, target, dir, PlayerStatus::NOT_AVOID_THEIR_VEHICLE));
        }
    }
    /****************** other ***************/
    bool meInFrontOfBall = me2Ball.mod() < 30;//ball.Valid() ? (me2Ball.mod() < 20 && Utils::Normalize(me2BallDir - me.Dir()) < Param::Math::PI / 3) : RobotSensor::Instance()->IsInfraredOn(task().executor);
    if (meInFrontOfBall) {
        DribbleStatus::Instance()->setDribbleCommand(vecNumber, 3);
    }
    //��﹀���
    if (canShoot && fabs(Utils::Normalize(me.Dir() - finalDir)) < SHOOT_ACCURACY) {
        if(!isChip) KickStatus::Instance()->setKick(vecNumber, power);
        else KickStatus::Instance()->setChipKick(vecNumber, power);
    }
    _lastCycle = pVision->Cycle();
    return CStatedTask::plan(pVision);
}

CPlayerCommand* CZPass::execute(const CVisionModule* pVision) {
    if (subTask()) {
        return subTask()->execute(pVision);
    }
    return nullptr;
}
