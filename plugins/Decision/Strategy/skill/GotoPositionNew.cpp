#include "GotoPositionNew.h"
#include <utils.h>
#include "skill/Factory.h"
#include <CommandFactory.h>
#include <VisionModule.h>
#include <RobotCapability.h>
#include <sstream>
#include <TaskMediator.h>
#include <ControlModel.h>
#include <robot_power.h>
#include <DribbleStatus.h>
#include "PlayInterface.h"
#include <GDebugEngine.h>
#include "DynamicsSafetySearch.h"
#include "ObstacleNew.h"
#include "PathPlanner.h"
#include <fstream>
#include "parammanager.h"
#include "BezierCurve.h"
#include "BezierMotion.h"
#include <iostream>
/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace{
    /// debug switch
    bool DRAW_TARGET = false;
    bool DSS_AVOID = true;

    /// dealing with the shaking when approaching the target
    const double DIST_REACH_CRITICAL = 2;	// [unit : cm]
    const double SlowFactor = 0.5;
    const double FastFactor = 1.2;

    /// motion control parameters
    double MAX_TRANSLATION_SPEED = 400;		// [unit : cm/s]
    double MAX_TRANSLATION_ACC = 600;		// [unit : cm/s2]
    double MAX_ROTATION_SPEED = 5;			// [unit : rad/s]
    double MAX_ROTATION_ACC = 15;			// [unit : rad/s2]
    double TRANSLATION_ACC_LIMIT = 1000;
    double MAX_TRANSLATION_DEC = 650;

    /// for goalie
    double MAX_TRANSLATION_SPEED_GOALIE;
    double MAX_TRANSLATION_ACC_GOALIE;
    double MAX_TRANSLATION_DEC_GOALIE;

    /// for guards
    double MAX_TRANSLATION_SPEED_BACK;
    double MAX_TRANSLATION_ACC_BACK;
    double MAX_TRANSLATION_DEC_BACK;

    /// control method parameter
    int TASK_TARGET_COLOR = COLOR_CYAN;
    ofstream carVisionVel("D://zjunlict//JSH220//carVisionVel.txt");
    int SAO_ACTION;

    double Y_COMPENSATE_K;
    double Y_COMPENSATE_B;
    PlanType playType = RRT;

    //for bezier planner
    bool lastIsDirect[Param::Field::MAX_PLAYER + 1] { false };
    bool lastIsFailed[Param::Field::MAX_PLAYER + 1] { false };
    bool arrived[Param::Field::MAX_PLAYER + 1] { false };

    const int curvePointsNumber = 40;
    const double veryNearDistance = 60;
    const double nearDistance = 100;
    const double offLineDist = 25;
    const double radiusOfRobot = Param::Vehicle::V2::PLAYER_SIZE / 2;
    const double FRAME_PERIOD = 1.0 / Param::Vision::FRAME_RATE;
    const double ZERO_VEL = 10;
    vector<CGeoPoint> viaPoints[Param::Field::MAX_PLAYER + 1];
    vector<CGeoPoint> pathPoints[Param::Field::MAX_PLAYER + 1];
    vector<CGeoPoint> controlPoints[Param::Field::MAX_PLAYER + 1];
    stateNew nextStep[Param::Field::MAX_PLAYER + 1];
    BezierCurver curver[Param::Field::MAX_PLAYER + 1];
}
using namespace Param::Vehicle::V2;

CGotoPositionNew::CGotoPositionNew()
{

    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_SPEED,"CGotoPositionV2/MNormalSpeed",300);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_ACC,"CGotoPositionV2/MNormalAcc",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_DEC,"CGotoPositionV2/MNormalDec",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_SPEED_BACK,"CGotoPositionV2/MBackSpeed",300);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_ACC_BACK,"CGotoPositionV2/MBackAcc",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_DEC_BACK,"CGotoPositionV2/MBackDec",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_SPEED_GOALIE,"CGotoPositionV2/MGoalieSpeed",300);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_ACC_GOALIE,"CGotoPositionV2/MGoalieAcc",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_DEC_GOALIE,"CGotoPositionV2/MGoalieDec",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_ROTATION_SPEED,"CGotoPositionV2/RotationSpeed",15);
    ZSS::ZParamManager::instance()->loadParam(MAX_ROTATION_ACC,"CGotoPositionV2/RotationAcc",15);
    ZSS::ZParamManager::instance()->loadParam(DRAW_TARGET,"Debug/TargetPos",false);
    ZSS::ZParamManager::instance()->loadParam(DSS_AVOID,"CGotoPositionV2/DssAvoid",true);
    ZSS::ZParamManager::instance()->loadParam(TRANSLATION_ACC_LIMIT,"CGotoPositionV2/AccLimit",1400);
    ZSS::ZParamManager::instance()->loadParam(SAO_ACTION,"Alert/SaoAction",0);
    ZSS::ZParamManager::instance()->loadParam(Y_COMPENSATE_K,"CGotoPositionV2/YCompensateK",0.0035);
    ZSS::ZParamManager::instance()->loadParam(Y_COMPENSATE_B,"CGotoPositionV2/YCompensateB",-0.1042);
}

void CGotoPositionNew::toStream(std::ostream& os) const
{
    os << "Going to " << task().player.pos<<" angle:"<<task().player.angle;
}

void CGotoPositionNew::plan(const CVisionModule* pVision)
{
    return ;
}

CPlayerCommand* CGotoPositionNew::execute(const CVisionModule* pVision)
{

    const int vecNumber = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    static PlayerVisionT meLast = me;
    const double vecDir = me.Dir();
    CGeoPoint targetPos = task().player.pos;
    static CGeoPoint lastTargetPos[Param::Field::MAX_PLAYER + 1];
    const int goalieNum = PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie());
    const bool isGoalie = (vecNumber == goalieNum);
    const int playerFlag = task().player.flag;

    if (isnan(targetPos.x()) || isnan(targetPos.y())) {
        targetPos = me.Pos();
        cout << "Target Pos is NaN, vecNumber is : " << vecNumber << endl;
    }
    targetPos = Utils::MakeInField(targetPos, -Param::Vehicle::V2::PLAYER_SIZE);

    const double targetDir = task().player.angle;
    const CVector player2target = targetPos - me.Pos();
    const double dist = player2target.mod();
    const bool dribble = playerFlag & PlayerStatus::DRIBBLING;
    unsigned char dribblePower = 0;
    vector<CGeoPoint> initialControlPoints;

    CCommandFactory* pCmdFactory = CmdFactory::Instance();
    PlayerCapabilityT capability = setCapability(pVision);

    double buffer = 5;
    ObstaclesNew* obs = new ObstaclesNew(Param::Vehicle::V2::PLAYER_SIZE + buffer);
    obs->addObs(pVision, task());

    double arrivedDist = me.Vel().mod() * 0.1 + 1;
//    CVector realVel((me.RawPos().x() - meLast.RawPos().x()) * Param::Vision::FRAME_RATE, (me.RawPos().y() - meLast.RawPos().y()) * Param::Vision::FRAME_RATE);
    stateNew start(me.Pos(), vecDir, me.Vel(), me.RotVel());
    stateNew target(targetPos, targetDir, task().player.vel, task().player.rotvel);

    bool newTarget = false;
    bool needToPlan = false;
    bool isVeryNear = dist < veryNearDistance;
//    bool isNear = dist < nearDistance;

    if(!(target.pos.dist(lastTargetPos[vecNumber]) < 5)) {
        arrived[vecNumber] = false;
        newTarget = true;
        lastTargetPos[vecNumber] = target.pos;
    }
    if(dist < arrivedDist)
        arrived[vecNumber] = true;

    if(pathPoints[vecNumber].size() == 0
            || curver[vecNumber].isOffLine(me.Pos(), offLineDist)
            || lastIsFailed[vecNumber]
            )
        needToPlan = true;

    int numberOfPathPoints = pathPoints[vecNumber].size();
    int arrPoint = lastIsFailed[vecNumber] ? 1 : curver[vecNumber].getArrivedNumber();
    int PathNumberToCheck = lastIsFailed[vecNumber] ? 1 : 10;

    CGeoPoint segStartNew, segEndNew;
    double scale = 30.0;
    double uncertainDist = 2;

    for(int i = arrPoint + 1; i < min(arrPoint + PathNumberToCheck, numberOfPathPoints); i++) {
        int numberOfObs = obs->obs.size();
        for(int j = 0; j < numberOfObs; j++) {
            CGeoSegment seg(pathPoints[vecNumber][i - 1], pathPoints[vecNumber][i]);
            if(!obs->obs[j].check(seg, 0.0)) { //保证中远距离上可以往反方向拉；

                needToPlan = true;
                CVector obstacleVel = obs->obs[j].getVel();
                double obstacleSpeed = obstacleVel.mod();

                if(obstacleSpeed > ZERO_VEL) {
                    double obstacalMove = obstacleSpeed * FRAME_PERIOD * scale;
                    CVector step = Utils::Polar2Vector(obstacalMove, obs->obs[j].getVel().dir());
                    CVector myVelDirec = me.Vel() / me.Vel().mod();
                    CVector obsVelDirec = obstacleVel / obstacleVel.mod();
                    if(abs(myVelDirec * obsVelDirec) < 0.7) {
                        segStartNew = obs->obs[j].getStart() + step;
                        segEndNew = obs->obs[j].getEnd() + step;
                    }
                    obs->obs[j].setPos(segStartNew, segEndNew);
                    double obstacleLength = obstacalMove * uncertainDist;
                    obs->addLongCircle(segStartNew + (-obstacleVel / obstacleVel.mod() * obstacleLength / 2), segEndNew + (obstacleVel / obstacleVel.mod() * obstacleLength * 1000), CVector(0, 0), obs->obs[j].getRadius(), OBS_CAR_NEW);
                }
            }
        }
    }
    bool canDirect = obs->check(me.Pos(), targetPos);
    needToPlan = (needToPlan && (!isVeryNear || !canDirect)) || newTarget;
    if (canDirect && !lastIsDirect[vecNumber]/* && !isNear*/) { // the robot can directly head to the final pos
        needToPlan = true;
        lastIsDirect[vecNumber] = true;
        viaPoints[vecNumber].clear();
        viaPoints[vecNumber].push_back(me.Pos());
        viaPoints[vecNumber].push_back(targetPos.midPoint(me.Pos()));
        viaPoints[vecNumber].push_back(targetPos);
        initialControlPoints = viaPoints[vecNumber];
    }
    /**
    haven't plan yet || there are some obs between current pos and next pos || arrive at next pos
    */
    else if (needToPlan) {
        // if the robot can go to the next planned point then skip
        lastIsDirect[vecNumber] = false;
        CPathPlanner planner(pVision, task(), Param::Vehicle::V2::PLAYER_SIZE + buffer, playType);
        PathList middleList = planner.getPath();
        if (middleList.size() > 0) { // planning success
            viaPoints[vecNumber].clear();
            initialControlPoints.clear();
            CGeoPoint tmpPoint(me.Pos());
            viaPoints[vecNumber].push_back(tmpPoint);
            for (CGeoPoint p : middleList) {
                if (p == me.Pos() || p == targetPos) continue;
                viaPoints[vecNumber].push_back(p);
            }
            viaPoints[vecNumber].push_back(targetPos);
        }
        int numOfViaPoints = viaPoints[vecNumber].size();
        for(int i = 0; i < numOfViaPoints - 1; i++) {
            if(obs->check(targetPos, viaPoints[vecNumber][i])) {
                initialControlPoints.push_back(viaPoints[vecNumber][i]);
                break;
            }
            initialControlPoints.push_back(viaPoints[vecNumber][i]);
        }
        initialControlPoints.push_back(targetPos);
    }
//    cout << ::GetTickCount() - k << endl;

    bool PathIsValid = true;
    stateNew nextFrame;
    char TARGET[] = "TARGET";
    if(needToPlan) {
        curver[vecNumber].initControlList(start, target, capability.maxSpeed, initialControlPoints, curvePointsNumber, *obs, !arrived[vecNumber]);
        PathIsValid= curver[vecNumber].curveGreatPath();
        double timeNeeded;
        curver[vecNumber].calculateState(capability, timeNeeded, nextStep[vecNumber]);
        pathPoints[vecNumber] = curver[vecNumber].getPathList();
        controlPoints[vecNumber] = curver[vecNumber].getControlList();
    }
    if(isVeryNear && canDirect || arrived[vecNumber]) {
        GDebugEngine::Instance()->gui_debug_msg(start.pos, TARGET, COLOR_RED);
        nextStep[vecNumber] = target;
    }
    else if(me.Pos().dist(nextStep[vecNumber].pos) < arrivedDist){
        nextStep[vecNumber] = curver[vecNumber].getNextState();
    }

    double rawVelX = (me.RawPos().x() - meLast.RawPos().x()) * Param::Vision::FRAME_RATE;
    double rawVelY = (me.RawPos().y() - meLast.RawPos().y()) * Param::Vision::FRAME_RATE;
//    double rawVel = sqrt(rawVelX * rawVelX + rawVelY * rawVelY);
    carVisionVel << rawVelX << "   " << rawVelY << endl;
    meLast = me;

    char RRT[] = "RRT";
    char BEZIER[] = "BEZIER";

    double moveFactor = 1.0, rotateFactor = 1.0;

//    if(me.RawPos().dist(me.Pos()) > 15 && rawVel == 0)
//        PathIsValid = false;
    if(!PathIsValid /*|| isNear*/) {
        if(!lastIsFailed[vecNumber])
            pathPoints[vecNumber] = viaPoints[vecNumber];
        lastIsFailed[vecNumber] = true;
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, -50), RRT, COLOR_RED);
        PlayerPoseT startT, targetT, nextT;
        startT.SetDir(start.orient);
        startT.SetPos(start.pos);
        startT.SetRotVel(start.rotVel);
        startT.SetVel(start.vel);
        targetT.SetDir(target.orient);
        targetT.SetPos(viaPoints[vecNumber][1]);
        targetT.SetRotVel(0);
        targetT.SetVel(CVector(0.0, 0.0));
        goto_point_omni(startT, targetT, capability, moveFactor, rotateFactor, nextT, 0);
        nextFrame.orient = nextT.Dir();
        nextFrame.pos = nextT.Pos();
        nextFrame.rotVel = nextT.RotVel();
        nextFrame.vel = nextT.Vel();
        //绘制rrt生成路径点
        for (CGeoPoint point : viaPoints[vecNumber]) {
            GDebugEngine::Instance()->gui_debug_x(point, COLOR_RED);
        }
        for (size_t i = 0; i < viaPoints[vecNumber].size() - 1; i++) {
            GDebugEngine::Instance()->gui_debug_line(viaPoints[vecNumber][i], viaPoints[vecNumber][i + 1], COLOR_RED);
        }

    }
    else {
        lastIsFailed[vecNumber] = false;
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-50, -50), BEZIER, COLOR_RED);

        BezierMotion motionController;
        motionController.bezierGotoPoint(start, nextStep[vecNumber], capability, moveFactor, rotateFactor, nextFrame);

        //绘制轨迹
        numberOfPathPoints = pathPoints[vecNumber].size();
//        int pArrived = curver[vecNumber].getArrivedNumber();
//        for (int i = pArrived; i < numberOfPathPoints; i++) {
//            GDebugEngine::Instance()->gui_debug_x(pathPoints[vecNumber][i], COLOR_GREEN);
//        }

        for (size_t i = 0; i < numberOfPathPoints - 1; i++) {
            GDebugEngine::Instance()->gui_debug_line(pathPoints[vecNumber][i], pathPoints[vecNumber][i + 1], COLOR_GREEN);
        }
//        //绘制控制点
//        for (CGeoPoint point : controlPoints[vecNumber]) {
//            GDebugEngine::Instance()->gui_debug_x(point, COLOR_BLUE);
//        }
//        for (size_t i = 0; i < controlPoints[vecNumber].size() - 1; i++) {
//            GDebugEngine::Instance()->gui_debug_line(controlPoints[vecNumber][i], controlPoints[vecNumber][i + 1], COLOR_BLUE);
//        }
    }

    CVector globalVel = nextFrame.vel;
    double alpha = 1.0;
    if (dist <= DIST_REACH_CRITICAL) {
        alpha *= sqrt(dist / DIST_REACH_CRITICAL);
    }
    CVector localVel = (globalVel * alpha).rotate(-me.Dir());




//    GDebugEngine::Instance()->gui_debug_msg(start.pos, QString("local_vel.x = : %1").arg(localVel.x()).toLatin1(), COLOR_RED);
//    GDebugEngine::Instance()->gui_debug_msg(start.pos + CVector(0,20), QString("lastIsDirect =  : %1").arg(pArrived).toLatin1(), COLOR_RED);
//    GDebugEngine::Instance()->gui_debug_msg(start.pos + CVector(0,40), QString("nextStep.vel =  : %1").arg(nextStep.vel.mod()).toLatin1(), COLOR_RED);

    int numberOfObs = obs->obs.size();
    for(int i = 0; i < numberOfObs; i++) {
        GDebugEngine::Instance()->gui_debug_line(obs->obs[i].getStart(), obs->obs[i].getEnd(), COLOR_PURPLE);
    }

    delete obs;
    return pCmdFactory->newCommand(CPlayerSpeedV2(vecNumber, localVel.x(), localVel.y(), nextFrame.rotVel, dribblePower));
//    return pCmdFactory->newCommand(CPlayerSpeedV2(vecNumber, 0, 0, 0, dribblePower));
}

PlayerCapabilityT CGotoPositionNew::setCapability(const CVisionModule* pVision) {
    const int vecNumber = task().executor;
    const int playerFlag = task().player.flag;
    PlayerCapabilityT capability;

    // Traslation
    if (vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie())) {
        capability.maxSpeed = MAX_TRANSLATION_SPEED_GOALIE;
        capability.maxAccel = MAX_TRANSLATION_ACC_GOALIE;
        capability.maxDec = MAX_TRANSLATION_DEC_GOALIE;
    }
    else if (TaskMediator::Instance()->leftBack() != 0 && vecNumber == TaskMediator::Instance()->leftBack()
        || TaskMediator::Instance()->rightBack() != 0 && vecNumber == TaskMediator::Instance()->rightBack()
        || TaskMediator::Instance()->singleBack() != 0 && vecNumber == TaskMediator::Instance()->singleBack()
        || TaskMediator::Instance()->sideBack() != 0 && vecNumber == TaskMediator::Instance()->sideBack()) {
        capability.maxSpeed = MAX_TRANSLATION_SPEED_BACK;
        capability.maxAccel = MAX_TRANSLATION_ACC_BACK;
        capability.maxDec = MAX_TRANSLATION_DEC_BACK;
    }
    else {
        capability.maxSpeed = MAX_TRANSLATION_SPEED;
        capability.maxAccel = MAX_TRANSLATION_ACC;
        capability.maxDec = MAX_TRANSLATION_DEC;
    }
    // Rotation
    capability.maxAngularSpeed = MAX_ROTATION_SPEED;
    capability.maxAngularAccel = MAX_ROTATION_ACC;
    capability.maxAngularDec = MAX_ROTATION_ACC;

    if (playerFlag & PlayerStatus::SLOWLY) {
        capability.maxSpeed = 140;
        capability.maxAccel *= SlowFactor;
        capability.maxDec *= SlowFactor;
        capability.maxAngularSpeed *= SlowFactor;
        capability.maxAngularAccel *= SlowFactor;
        capability.maxAngularDec *= SlowFactor;
    }
    if (playerFlag & PlayerStatus::QUICKLY
        || vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie())) {
        capability.maxSpeed *= FastFactor;
        capability.maxAccel *= FastFactor;
        capability.maxDec *= FastFactor;
        capability.maxAngularSpeed *= FastFactor;
        capability.maxAngularAccel *= FastFactor;
        capability.maxAngularDec *= FastFactor;
    }

    if (playerFlag & PlayerStatus::QUICKLY
        || vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie())) {
    }

    if (task().player.max_acceleration > 1) {
        capability.maxAccel = task().player.max_acceleration > TRANSLATION_ACC_LIMIT ? TRANSLATION_ACC_LIMIT : task().player.max_acceleration;
        capability.maxDec = capability.maxAccel;
    }
    if (WorldModel::Instance()->CurrentRefereeMsg() == "GameStop") {
        const MobileVisionT ball = pVision->Ball();
        if (ball.Pos().x() < -240 && abs(ball.Pos().y()) > 150) {
            capability.maxSpeed = 100;
        }
        else {
            capability.maxSpeed = 150;
        }
    }
    return capability;
}

bool CGotoPositionNew::canGoto(const CVisionModule* pVision, const int player, const CGeoPoint& target)
{
    if( target.x() < -Param::Field::PITCH_LENGTH/2 || target.x() > Param::Field::PITCH_LENGTH/2 || target.y() < -Param::Field::PITCH_WIDTH / 2 || target.y() > Param::Field::PITCH_WIDTH / 2){
        return false;
    }
    bool _canGo = true;
    _canGo = Utils::canGo(pVision, player, target, 0, 0);
    if( _canGo ){
        _target = target;
        return true;
    }
    return false;
}
