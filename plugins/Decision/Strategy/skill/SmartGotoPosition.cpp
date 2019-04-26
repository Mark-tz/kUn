#include "SmartGotoPosition.h"
#include <PathPlanner.h>
#include "skill/Factory.h"
#include <utils.h>
#include <TaskMediator.h>
//#include <LeavePenaltyArea.h>
#include "PlayInterface.h"
#include <GDebugEngine.h>
#include <RobotCapability.h>
#include <CommandFactory.h>

#include <ControlModel.h>
#include <iostream>
#include "parammanager.h"
#include "CMmotion.h"

#include <iostream>

/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace{
	/// 调试开关
	bool VERBOSE_MODE = false;
	bool DRAW_TARGET = false;
    bool USE_DEBUG = false;

    const double SlowFactor = 0.5;
    const double FastFactor = 1.2;
    /// 底层运动控制参数 ： 默认增大平动的控制性能
    double MAX_TRANSLATION_SPEED = 400;		// [unit : cm/s]
    double MAX_TRANSLATION_ACC = 600;		// [unit : cm/s2]
    double MAX_ROTATION_SPEED = 5;			// [unit : rad/s]
    double MAX_ROTATION_ACC = 15;			// [unit : rad/s2]
    double TRANSLATION_ACC_LIMIT = 1000;
    double MAX_TRANSLATION_DEC = 650;

    /// 守门员专用
    double MAX_TRANSLATION_SPEED_GOALIE;
    double MAX_TRANSLATION_ACC_GOALIE;
    double MAX_TRANSLATION_DEC_GOALIE;

    /// 后卫专用
    double MAX_TRANSLATION_SPEED_BACK;
    double MAX_TRANSLATION_ACC_BACK;
    double MAX_TRANSLATION_DEC_BACK;

	/// 路径规划
	double NO_SMART_DIST = 5;
	double NO_SMART_DIST_IN_THEIR_DEFENCE_BOX = 5;
	double DO_NOT_AVOID_VEHICLE_EXTRA = Param::Field::MAX_PLAYER;
	double PATH_VALID_DIST = 2; // 小于此距离便认为路径点不可用
	int PATH_PLAN_TYPE = 0;  /* RRT = 0,GEO = 1,ASTAR = 2,STUPID = 3, BANGBANG = 4, PFAD = 5,DELAUNAY = 6,NEWGEO = 7,*/

	//int REPlanCount = 3;
	//int PATH_PLAN_CYCLE[Param::Field::MAX_PLAYER+1] = {-20,-20,-20,-20,-20,-20,-20};
	//CGeoPoint PATH_PLAN_RECORD_POINT[Param::Field::MAX_PLAYER+1] = {CGeoPoint(0,0),CGeoPoint(0,0),CGeoPoint(0,0),CGeoPoint(0,0),CGeoPoint(0,0),CGeoPoint(0,0),CGeoPoint(0,0)};

	/// 避碰规划
	bool DO_CHECK = false;		// 控制是否进行碰撞检测
	int TRAJECTORY_METHORD = 4;	// CMU_TRAJ = 1,ZERO_FINAL = 2,	ZERO_TRAP = 3,	NONE_TRAP = 4
	int MaxCheckSearchNum = 0;
	double CheckSearchStep = Param::Field::MAX_PLAYER_SIZE*1.5;
	int TRAP_COLLISION_BUFFER = 0;
	int TRAP_STEP = 6;
	double NeedCheckDist = 100;
	double MoveCritialSpeed = 50;
	double FuzzyStep = 2.5;
	double FuzzyBaseSpeed = 150;

	bool DRAW_TRAJ = false;		//Draw
	bool DRAW_PREDICT_POS = false;
	bool DRAW_TMP_ADDED = false;
    bool DRAW_OBSTACLES = false;

    /// related to rrt
    PathList middleList;
    CGeoPoint lastPoint[Param::Field::MAX_PLAYER + 1];
    CGeoPoint lastFinalPoint[Param::Field::MAX_PLAYER + 1];
    CGeoPoint veryStart[Param::Field::MAX_PLAYER + 1];
    bool isExecuting[Param::Field::MAX_PLAYER + 1];
    bool useImmortal[Param::Field::MAX_PLAYER + 1];
    const double Fake_PENALTY_AREA_R = 150; // added by ftq
    const double TEAMMATE_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 4.0f; // 2014/03/13 修改，为了减少stop的时候卡住的概率 yys
    const double OPP_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 5.5f;
    const double BALL_AVOID_DIST = Param::Field::BALL_SIZE + 5.0f;
    ofstream debug("C://Users//gayty//Desktop//Sydney//Sydney//debug.txt");
}
using namespace Param::Vehicle::V2;


/************************************************************************/
/*                       CSmartGotoPositionV2                           */
/************************************************************************/
/// 构造函数 ： 参数初始化
CSmartGotoPositionV2::CSmartGotoPositionV2()
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
    ZSS::ZParamManager::instance()->loadParam(NO_SMART_DIST,"CSmartGotoV2/NoSmartDist",5);
    ZSS::ZParamManager::instance()->loadParam(PATH_VALID_DIST,"CSmartGotoV2/PathValidDist",2);
    ZSS::ZParamManager::instance()->loadParam(DRAW_TARGET,"Debug/SmartTargetPos",true);
    ZSS::ZParamManager::instance()->loadParam(DRAW_OBSTACLES, "Debug/draw_Obs", false);
    ZSS::ZParamManager::instance()->loadParam(PATH_PLAN_TYPE,"CSmartGotoV2/PathPlanType",0);
    ZSS::ZParamManager::instance()->loadParam(DO_CHECK,"CSmartGotoV2/DoCheck",true);
    ZSS::ZParamManager::instance()->loadParam(TRAJECTORY_METHORD,"CGotoPositionV2/TrajectoryMethod",1);
}

/// 输出流 ： 调试显示
void CSmartGotoPositionV2::toStream(std::ostream& os) const
{
	os << "Smart going to " << task().player.pos;
}

/// 规划接口
void CSmartGotoPositionV2::plan(const CVisionModule* pVision)
{
    if ((lastFinalPoint[task().executor] - task().player.pos).mod() > 5) {
        lastPoint[task().executor] = task().player.pos; /// added by gjy 5.29
        lastFinalPoint[task().executor] = task().player.pos;
        veryStart[task().executor] = pVision->OurPlayer(task().executor).Pos();
        isExecuting[task().executor] = false;
    }
    /************************************************************************/
	/* 任务参数解析                                                         */
	/************************************************************************/
	playerFlag = task().player.flag;
	const bool rec = task().player.needdribble;
	const int vecNumber = task().executor;
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	const CGeoPoint& myPos = pVision->OurPlayer(vecNumber).Pos();
//	const CVector&myVel = pVision->OurPlayer(vecNumber).Vel();
    const bool isGoalie = vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie());

    const bool isBack = (vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->leftBack()))
                        || (vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->rightBack()));

    CGeoPoint finalTargetPos = task().player.pos;

    GDebugEngine::Instance()->gui_debug_x(finalTargetPos, COLOR_RED);

//    if (isExecuting[vecNumber] == false) {
//        if ((finalTargetPos - self.Pos()).mod() > 400) {
//            useImmortal[vecNumber] = true;
//        }
//        else {
//            useImmortal[vecNumber] = false;
//        }
//        isExecuting[vecNumber] = true;
//    }
    useImmortal[vecNumber] = (playerFlag & PlayerStatus::USE_IMMORTAL_RUSH) != 0;
//    if ((playerFlag & PlayerStatus::USE_IMMORTAL_RUSH) != 0) {
//        useImmortal[vecNumber] = true;
//    }

    _capability = setCapability(pVision);

	/************************************************************************/
	/* 任务参数解析                                                         */
	/************************************************************************/

	/// 路径规划
	//int buffer = Param::Field::BALL_SIZE;

    double buffer = 2.5;
    PlanType play_type = (PlanType)PATH_PLAN_TYPE;
    if (self.Vel().mod() < 200) {
        buffer = 2.5;
    }
    else if (self.Vel().mod() < 350) {
        buffer = 2.5 + (self.Vel().mod() - 200) / 50;
    }
    else {
        buffer = 5.5;
    }
    if (self.Vel().mod() < 150 && (self.Pos() - finalTargetPos).mod() < 100) {
        buffer /= 2;
    }
    if (isGoalie || isBack) {
        buffer = 0;
        play_type = RRT;
    }
    double avoidLength = Param::Vehicle::V2::PLAYER_SIZE + buffer;
    obstacles obs(avoidLength);
    updateObs(pVision, obs);

    //处理无效目标点:在禁区内、在车身内、在场地外
    finalTargetPos = Utils::MakeInField(finalTargetPos, avoidLength);
    int obsNum = obs.get_num();
    state goal;
    goal.pos = vector2f(finalTargetPos.x(), finalTargetPos.y());

    if(Utils::InOurPenaltyArea(finalTargetPos, avoidLength))
        finalTargetPos = Utils::MakeOutOfOurPenaltyArea(finalTargetPos, avoidLength);
    if(Utils::InTheirPenaltyArea(finalTargetPos, avoidLength))
        finalTargetPos = Utils::MakeOutOfTheirPenaltyArea(finalTargetPos, avoidLength);
    for(int i = 0; i < obsNum; i++) {
        if(obs.obs[i].type != OBS_RECTANGLE && !obs.obs[i].check(goal)) {
            if(obs.obs[i].type == OBS_CIRCLE) {
                finalTargetPos = Utils::MakeOutOfCircle(CGeoPoint(obs.obs[i].seg_start.x, obs.obs[i].seg_start.y), obs.obs[i].radius, myPos, finalTargetPos, avoidLength);
            }
            else {
                finalTargetPos = Utils::MakeOutOfLongCircle(CGeoPoint(obs.obs[i].seg_start.x, obs.obs[i].seg_start.y), CGeoPoint(obs.obs[i].seg_end.x, obs.obs[i].seg_end.y), obs.obs[i].radius, myPos, finalTargetPos, avoidLength);
            }
        }
    }


    GDebugEngine::Instance()->gui_debug_x(finalTargetPos, COLOR_YELLOW);

    CGeoPoint middlePoint =  myPos + (finalTargetPos - myPos) * 0.2; // 初始点
    /// modified the condition on which rrt would be executed 2018.5.29 gjy
    state start;
    start.pos = vector2f(self.Pos().x(), self.Pos().y());
    state middle;
    middle.pos = vector2f(lastPoint[vecNumber].x(), lastPoint[vecNumber].y());
    state final;
    final.pos = vector2f(finalTargetPos.x(), finalTargetPos.y());
    TaskT newTask(task());
    newTask.player.pos = finalTargetPos;

    obstacles immortalObs(Param::Vehicle::V2::PLAYER_SIZE + buffer * 3);
    updateObs(pVision, immortalObs);

    if (!immortalObs.check(start, middle)) {
        useImmortal[vecNumber] = false;
    }

    double arrivedDist = self.Vel().mod() * 0.1 + 5;
    if (obs.check(start, final)) { // the robot can directly head to the final pos
        middlePoint = finalTargetPos;
    }
    else if (obs.check(start, middle) && (lastPoint[vecNumber] - self.Pos()).mod() > arrivedDist) { // keep the pos last cycle

        middlePoint = lastPoint[vecNumber];
    }
    else { // replan the path

        CPathPlanner planner(pVision, newTask, avoidLength, play_type);
        middleList = planner.getPath();
        if (middleList.size() > 0) { // 规划成功
            CGeoPoint plannedPoint(*(planner.getPath().begin()));
//            if (plannedPoint.dist(myPos) >= (Param::Vehicle::V2::PLAYER_SIZE * 2 + 2) || plannedPoint.dist(finalTargetPos) <= Param::Vehicle::V2::PLAYER_SIZE * 0.5) {
                middlePoint = plannedPoint;
//            }
        }
    }

    if (rec) DribbleStatus::Instance()->setDribbleCommand(vecNumber,2);
    newTask.player.pos = middlePoint;
    lastPoint[vecNumber] = middlePoint;

    /// added goImmortalRush when the flag is triggered 2018.5.27 gjy
    if (useImmortal[vecNumber]) {
        if (!(middlePoint == finalTargetPos)) {
            newTask.player.angle = (self.Pos() - finalTargetPos).dir();
        }

        // plan the velocity of the middle pos
        CVector middleVel;
        if (middlePoint == task().player.pos) {
            middleVel = CVector(0, 0);
        }
        else {
            GDebugEngine::Instance()->gui_debug_x(veryStart[vecNumber], COLOR_PURPLE);
            CGeoLine start2FinalLine = CGeoLine(veryStart[vecNumber], lastFinalPoint[vecNumber]);
            CGeoPoint middleProj = start2FinalLine.projection(middlePoint);
            double velDir = (self.Pos() - middlePoint).dir();
            middleVel = Utils::Polar2Vector(getMiddleVel(pVision, middleProj), velDir);
        }
        newTask.player.vel = middleVel;

        if (!(middlePoint == finalTargetPos)) {
            CGeoPoint tmpPos = middlePoint + Utils::Polar2Vector(pow(middleVel.mod(), 2) / (2 * _capability.maxAccel), (middlePoint - self.Pos()).dir());
            middle.pos = vector2f(tmpPos.x(), tmpPos.y());
            if (obs.check(start, middle)) {
                double me2MiddleDist = (self.Pos() - middlePoint).mod();
                double avoidDist = pow(self.Vel().mod(), 2) / ((2 * _capability.maxAccel) * log(me2MiddleDist) / log(40));
                newTask.player.pos = /*newTask.player.pos*/ middlePoint + Utils::Polar2Vector(avoidDist, (self.Pos() - middlePoint).dir());
//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(300,280),QString("%1 %2").arg(pow(self.Vel().mod(), 2) / (2 * _capability.maxAccel)).arg(avoidDist).toLatin1());
//                lastPoint[vecNumber] = middlePoint;
                double velMod = 0; //middleVel.mod() / 10;
                double velDir = middleVel.dir();
                middleVel = Utils::Polar2Vector(velMod, velDir);
            }
        }
        if(USE_DEBUG) cout << "[SmartGotoPosition.cpp] GoImmortalRush" << endl;
        setSubTask(TaskFactoryV2::Instance()->GoImmortalRush(newTask));
    }
    else {
        if(USE_DEBUG) cout << "[SmartGotoPosition.cpp] GotoPosition" << endl;
        setSubTask(TaskFactoryV2::Instance()->GotoPosition(newTask));
    }

    _lastCycle = pVision->Cycle();
    CPlayerTask::plan(pVision);
	return ;
}

double CSmartGotoPositionV2::getMiddleVel(const CVisionModule *pVision, CGeoPoint middleProj) {
    int vecNum = task().executor;
    CGeoSegment start2FinalLine = CGeoSegment(veryStart[vecNum], lastFinalPoint[vecNum]);
    if (start2FinalLine.IsPointOnLineOnSegment(middleProj)) {
        double velMod;
        double middleDist = (middleProj - veryStart[vecNum]).mod();
        double finalDist = (lastFinalPoint[vecNum] - veryStart[vecNum]).mod();
        double triangleDist = pow(_capability.maxSpeed, 2) / _capability.maxAccel;
        if (finalDist < triangleDist) {
            double maxVel = sqrt(_capability.maxAccel * finalDist);
            triangleDist = pow(maxVel, 2) / _capability.maxAccel;
            velMod = middleDist < triangleDist / 2 ? sqrt(2 * _capability.maxAccel * middleDist) :
                                                     sqrt(2 * _capability.maxAccel * (finalDist - middleDist));
        }
        else {
            double flatDist = finalDist - triangleDist;
            velMod = middleDist < flatDist + triangleDist / 2 ?
                        _capability.maxSpeed : sqrt(2 * _capability.maxAccel * (triangleDist / 2));
        }
        return velMod * 0.3;
    }
    else {
        return 0;
    }
}

///// 轨迹碰撞检查
//void CSmartGotoPositionV2::doTrajCheck(const CVisionModule* pVision,int playerNum,const PlayerPoseT& middlePose,PlayerPoseT& nextStep)
//{
//	//player
//	const PlayerVisionT& player = pVision->OurPlayer(playerNum);
//
//	//motion-control
//	//1.param read
//	const CRobotCapability* robotCap = RobotCapFactory::Instance()->getRobotCap(pVision->Side(), playerNum);
//	double MaxSpeed = robotCap->maxSpeed(0);		//speed
//	if( playerFlag & PlayerStatus::SPECIFY_SPEED )			
//		MaxSpeed = task().player.max_speed;
//	double MaxAcceleration = robotCap->maxAcceleration(CVector(0,0),0);	//acceleration
//	if( playerFlag & PlayerStatus::SPECIFY_ACCELERATION )
//		MaxAcceleration = task().player.max_acceleration;
//	double MaxDeceleration = MaxAcceleration;				//deceleration
//	
//	double MaxAngularSpeed = robotCap->maxAngularSpeed();	//ang-speed
//	if( playerFlag & PlayerStatus::SPECIFY_ROTATE_SPEED )
//		MaxAngularSpeed = task().player.max_rotate_speed;
//	double MaxAngularAcceleration = robotCap->maxAngularAcceleration();	//ang-acceleration
//	if( playerFlag & PlayerStatus::SPECIFY_ROTATE_ACCELERATION )
//		MaxAngularAcceleration = task().player.max_rotate_acceleration;	//ang-acceleration
//	double MaxAngularDeceleration = MaxAngularAcceleration;
//	
//	if( playerFlag & PlayerStatus::SLOWLY )
//	{
//		MaxSpeed *= 0.6;
//	}
//	//std::cout<<MaxSpeed<<"\t"<<MaxAcceleration<<"\t"<<MaxDeceleration<<"\t"<<MaxAngularSpeed<<"\t"<<MaxAngularAcceleration<<"\t"<<MaxAngularDeceleration<<std::endl;
//
//	//2.generate
//	PlayerPoseT start;				//start
//	start.SetPos(player.Pos());
//	start.SetVel(player.Vel());
//	start.SetDir(player.Dir());
//	start.SetRotVel(player.RotVel());
//	PlayerPoseT final;				//final
//	final.SetPos(middlePose.Pos());
//	final.SetVel(middlePose.Vel());
//	final.SetDir(middlePose.Dir());
//	final.SetRotVel(0.0);
//	PlayerCapabilityT capability;	//capability
//	capability.maxSpeed = MaxSpeed;
//	capability.maxAccel = MaxAcceleration;
//	capability.maxDec = MaxDeceleration;
//	capability.maxAngularSpeed = MaxAngularSpeed;
//	capability.maxAngularAccel = MaxAngularAcceleration;
//	capability.maxAngularDec = MaxAngularDeceleration;
//
//	//根据 TRAJECTORY_METHORD 选择对应的控制算法
//	CControlModel control;
//	switch ( TRAJECTORY_METHORD )
//	{
//	case CMU_TRAJ:
//		control.makeCmTrajectory(start,final,capability);				//没有完整轨迹返回 TODO		这个还比较纠结，还没整明白
//		break;
//	case ZERO_FINAL:
//		control.makeZeroFinalVelocityPath(start, final, capability);	//没有完整轨迹返回 TODO		可以很方便通过改写返回
//		break;
//	case ZERO_TRAP:
//		control.makeTrapezoidalVelocityPath(start,final,capability);
//		break;
//	case NONE_TRAP:
//		control.makeNoneTrapezoidalVelocityPath(start, final, capability);
//		break;
//	default:
//		control.makeNoneTrapezoidalVelocityPath(start, final, capability);
//		break;
//	}  		
//	nextStep = control.getNextStep();
//
//	//do check : iterate
//	current_trajectory_safe = true;
//	collidePos = CGeoPoint(0.0,0.0);
//	collideVel = CVector(0,0);
//	collideRot = 0.0;
//	collideNum = 0;
//	vector< vector<double> > nonepathList = control.getFullPath();
//	int index = 0;
//	for( vector< vector<double> >::const_iterator iter = nonepathList.begin();
//			iter != nonepathList.end() && index < Param::Vision::FRAME_RATE ; iter++,index++)
//	{
//		CGeoPoint realPoint = CGeoPoint( (*iter)[1]+player.Pos().x(),(*iter)[2]+player.Pos().y());
//
//		if(DRAW_TRAJ)
//			GDebugEngine::Instance()->gui_debug_x(realPoint,COLOR_CYAN);
//
//		bool isCollide = false;
//		for(int i=1;i<=2*Param::Field::MAX_PLAYER;i++)
//		{
//			//not me
//			if( i == playerNum )
//				continue;
//
//			//... ... Higher Priority : not added yet
//			//... ...
//
//			bool isOnField = (i<=Param::Field::MAX_PLAYER)?pVision->OurPlayer(i).Valid():
//								pVision->TheirPlayer(i-Param::Field::MAX_PLAYER).Valid();
//			//on field
//			if( !isOnField )
//				continue;
//
//			CGeoPoint currentPos = (i<=Param::Field::MAX_PLAYER)?pVision->OurPlayer(i).Pos():
//									pVision->TheirPlayer(i-Param::Field::MAX_PLAYER).Pos();
//			CVector currentVel = (i<=Param::Field::MAX_PLAYER)?pVision->OurPlayer(i).Vel():
//									pVision->TheirPlayer(i-Param::Field::MAX_PLAYER).Vel();
//
//			//in some distance
//			if( player.Pos().dist(currentPos) > NeedCheckDist )
//				continue;
//
//			//consider dynamic
//			if( index <= 1 )
//				currentPos = currentPos + currentVel*((index+1)*1.0/Param::Vision::FRAME_RATE);
//			else
//				currentPos = currentPos + currentVel*(1.0*((index-1)*TRAP_STEP+2)/Param::Vision::FRAME_RATE);
//
//			//fuzzy about speed
//			double SpeedBuffer = 0.0;
//			if( currentVel.mod2() > MoveCritialSpeed*MoveCritialSpeed )
//				SpeedBuffer = index * FuzzyStep * currentVel.mod() / FuzzyBaseSpeed;
//
//			double collideCheckBufferDist = Param::Vehicle::V2::PLAYER_SIZE*2 + TRAP_COLLISION_BUFFER + SpeedBuffer;
//
//			if( DRAW_PREDICT_POS)
//			{
//				if( i <= Param::Field::MAX_PLAYER )	//only ourside
//					GDebugEngine::Instance()->gui_debug_arc(currentPos,collideCheckBufferDist,0,360,COLOR_ORANGE);
//			}
//
//			if( realPoint.dist(currentPos) <= collideCheckBufferDist )
//			{
//				isCollide = true;
//				collidePos = realPoint;
//				collideVel = CVector((*iter)[4],(*iter)[5]);
//				collideRot = (*iter)[6];
//				collideNum = i;
//				break;							
//			}
//		}
//
//		if( isCollide )
//		{
//			current_trajectory_safe = false;
//			break;
//		}
//	}
//
//	return ;
//}

/// 生成避障跑位点
CGeoPoint CSmartGotoPositionV2::generateObstacleAvoidanceTmpPoint(const CVisionModule* pVision, int playerNum, const CGeoPoint& middlePoint)
{
	CGeoPoint collideVehiclePos = (collideNum <= Param::Field::MAX_PLAYER)?pVision->OurPlayer(collideNum).Pos():
									pVision->TheirPlayer(collideNum-Param::Field::MAX_PLAYER).Pos();
	CVector collideVehicleVel = (collideNum <= Param::Field::MAX_PLAYER)?pVision->OurPlayer(collideNum).Vel():
									pVision->TheirPlayer(collideNum-Param::Field::MAX_PLAYER).Vel();

	CGeoPoint selfPos = pVision->OurPlayer(playerNum).Pos();

	//若已经相撞
	if( selfPos.dist(collideVehiclePos) < 2*Param::Vehicle::V2::PLAYER_SIZE )
	{
		double avoid_dir = (selfPos - collideVehiclePos).dir();
		if( collideVehicleVel.mod() >= MoveCritialSpeed )
			return selfPos + Utils::Polar2Vector(100,Utils::Normalize(avoid_dir));
		else
			return generateObstacleAvoidanceStatic(pVision,playerNum,middlePoint);
	}
	else
	{
		if( collideVehicleVel.mod() >= MoveCritialSpeed )
			return generateObstacleAvoidanceDynamic(pVision,playerNum,middlePoint);
		else
			return generateObstacleAvoidanceStatic(pVision,playerNum,middlePoint);
	}	
}

/// 生成静态避障跑位点
CGeoPoint CSmartGotoPositionV2::generateObstacleAvoidanceStatic(const CVisionModule* pVision,int playerNum,const CGeoPoint& middlePoint)
{
	CGeoPoint collideVehiclePos = (collideNum <= Param::Field::MAX_PLAYER)?pVision->OurPlayer(collideNum).Pos():
									pVision->TheirPlayer(collideNum-Param::Field::MAX_PLAYER).Pos();
	CVector collideVehicleVel = (collideNum <= Param::Field::MAX_PLAYER)?pVision->OurPlayer(collideNum).Vel():
									pVision->TheirPlayer(collideNum-Param::Field::MAX_PLAYER).Vel();

	//设定偏移起始点以及偏移方向
	double offsideDir = 0.0;
	CGeoPoint tmpAddPoint = collidePos;

	CVector collidePos2collideVehiclePos = collidePos - collideVehiclePos;
	CGeoLine self2tmpPoint = CGeoLine(pVision->OurPlayer(playerNum).Pos(),middlePoint);
	CGeoPoint projPoint = self2tmpPoint.projection(collideVehiclePos);

	offsideDir = Utils::Normalize((projPoint-collideVehiclePos).dir());
	tmpAddPoint = tmpAddPoint + Utils::Polar2Vector(CheckSearchStep,offsideDir);

	return tmpAddPoint;
}

/// 生成动态避障跑位点
CGeoPoint CSmartGotoPositionV2::generateObstacleAvoidanceDynamic(const CVisionModule* pVision,int playerNum,const CGeoPoint& middlePoint)
{
	CGeoPoint collideVehiclePos = (collideNum <= Param::Field::MAX_PLAYER)?pVision->OurPlayer(collideNum).Pos():
									pVision->TheirPlayer(collideNum-Param::Field::MAX_PLAYER).Pos();
	CVector collideVehicleVel = (collideNum <= Param::Field::MAX_PLAYER)?pVision->OurPlayer(collideNum).Vel():
									pVision->TheirPlayer(collideNum-Param::Field::MAX_PLAYER).Vel();

	//设定偏移起始点以及偏移方向
	double offsideDir = 0.0;
	CGeoPoint tmpAddPoint = collidePos;

	CVector collidePos2collideVehiclePos = collidePos - collideVehiclePos;
	CGeoLine self2tmpPoint = CGeoLine(pVision->OurPlayer(playerNum).Pos(),middlePoint);
	CGeoPoint projPoint = self2tmpPoint.projection(collideVehiclePos);
	CGeoSegment collideVehicleSeg = CGeoSegment(collideVehiclePos,collideVehiclePos+Utils::Polar2Vector(1000,collideVehicleVel.dir()));

	CGeoPoint projectSelf = collideVehicleSeg.projection(pVision->OurPlayer(playerNum).Pos());
	bool NeedEmergencyStop = false;
	double dist = 0.0;
	if( collideVehicleSeg.IsPointOnLineOnSegment(projectSelf) )
	{
		dist = projectSelf.dist(pVision->OurPlayer(playerNum).Pos());
		if(  dist > Param::Vehicle::V2::PLAYER_SIZE*2 )
			NeedEmergencyStop = true;
	}

	CVector self2collodePos = collidePos - pVision->OurPlayer(playerNum).Pos();
	offsideDir = self2collodePos.dir();

	if( NeedEmergencyStop )	//急停
	{
		if( dist < 100 )
			tmpAddPoint = pVision->OurPlayer(playerNum).Pos() + Utils::Polar2Vector(0,offsideDir);
		else
			tmpAddPoint = pVision->OurPlayer(playerNum).Pos() + self2collodePos*0.5;

	}
	else
	{
		offsideDir = Utils::Normalize((projPoint-collideVehiclePos).dir());
		tmpAddPoint = collidePos + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_SIZE*2,offsideDir);
	}

	return tmpAddPoint;
}

PlayerCapabilityT CSmartGotoPositionV2::setCapability(const CVisionModule* pVision) {
    const int vecNumber = task().executor;
    const int playerFlag = task().player.flag;
    PlayerCapabilityT capability;
//    const CRobotCapability* robotCap = RobotCapFactory::Instance()->getRobotCap(pVision->Side(), vecNumber);

    // Traslation 确定平动运动参数
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
    // Rotation	  确定转动运动参数
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

    if (task().player.max_acceleration > 1) { // 2014-03-26 修改, 因为double数不能进行相等判断
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

void CSmartGotoPositionV2::updateObs(const CVisionModule *pVision, obstacles &obs) {
    int player = task().executor;
    int shootCar = task().ball.Sender;
    CGeoPoint target = task().player.pos;
    int flags = task().player.flag;

    vector2f playerPos(pVision->OurPlayer(player).X(), pVision->OurPlayer(player).Y());
    vector2f playerVel(pVision->OurPlayer(player).VelX(), pVision->OurPlayer(player).VelY());
    vector2f target_pos(target.x(), target.y());

    if (flags & PlayerStatus::FREE_KICK) {
           obs.add_rectangle(vector2f(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH/2 - OPP_AVOID_DIST * 3),
                             vector2f(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - OPP_AVOID_DIST * 3, Param::Field::PENALTY_AREA_WIDTH / 2 + OPP_AVOID_DIST * 3), 1, DRAW_OBSTACLES);
   }
   else {
       obs.add_rectangle(vector2f(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH/2),
                         vector2f(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2), 1, DRAW_OBSTACLES);
   }

    // 如果是躲避射门
    if (flags & PlayerStatus::AVOID_SHOOTLINE) {
        const PlayerVisionT& shooter = pVision->OurPlayer(shootCar);
        // 球门中心
        obs.add_long_circle(vector2f(shooter.Pos().x(), shooter.Pos().y()), vector2f(Param::Field::PITCH_LENGTH/2, 0.0f), vector2f(0.0f, 0.0f), 3.0f, 1, DRAW_OBSTACLES);
        // 球门左门柱
        obs.add_long_circle(vector2f(shooter.Pos().x(), shooter.Pos().y()), vector2f(Param::Field::PITCH_LENGTH/2, Param::Field::GOAL_WIDTH/2.0), vector2f(0.0f, 0.0f), 3.0f, 1, DRAW_OBSTACLES);
        // 球门右门柱
        obs.add_long_circle(vector2f(shooter.Pos().x(), shooter.Pos().y()), vector2f(Param::Field::PITCH_LENGTH/2, -Param::Field::GOAL_WIDTH/2.0), vector2f(0.0f, 0.0f), 3.0f, 1, DRAW_OBSTACLES);
    }

    // set up teammates as obstacles
    if (!(flags & PlayerStatus::NOT_AVOID_OUR_VEHICLE)) {
        for(int i = 1; i <= Param::Field::MAX_PLAYER; ++i) {
            const PlayerVisionT& teammate = pVision->OurPlayer(i);
            if((i != player) && teammate.Valid()) {
                if(i == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->rightBack()) || i == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->leftBack()))
                    obs.add_circle(vector2f(teammate.Pos().x(), teammate.Pos().y()), vector2f(teammate.Vel().x(), teammate.Vel().y()), Param::Vehicle::V2::PLAYER_SIZE, 1, DRAW_OBSTACLES);
                else
                    obs.add_circle(vector2f(teammate.Pos().x(), teammate.Pos().y()), vector2f(teammate.Vel().x(), teammate.Vel().y()), TEAMMATE_AVOID_DIST, 1, DRAW_OBSTACLES);
            }
        }
    }

    // set up opponents as obstacles
    if (!(flags & PlayerStatus::NOT_AVOID_THEIR_VEHICLE)) {
        for(int i=1; i<=Param::Field::MAX_PLAYER; ++i) {
            const PlayerVisionT& opp = pVision->TheirPlayer(i);
            if(opp.Valid()) {
                if( (false && (flags & PlayerStatus::IGNORE_PLAYER_CLOSE_TO_TARGET) && (target.dist(opp.Pos()) < Param::Field::MAX_PLAYER_SIZE / 2)) ) {
                    continue;
                }
                else {
                    obs.add_circle(vector2f(opp.Pos().x(), opp.Pos().y()), vector2f(opp.Vel().x(), opp.Vel().y()), OPP_AVOID_DIST, 1, DRAW_OBSTACLES);
                    //GDebugEngine::Instance()->gui_debug_arc(opp.Pos(), OPP_AVOID_DIST, 0, 360);
                }
            }
        }
    }

    // 禁区 和 门柱
    if((true || flags & PlayerStatus::DODGE_OUR_DEFENSE_BOX) && (player != PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie()))) {
        // 我方禁区
        obs.add_rectangle(vector2f(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH/2),
                          vector2f(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2), 1, DRAW_OBSTACLES);
    }

    // ball
    if(flags & PlayerStatus::DODGE_BALL) {
        const MobileVisionT& ball = pVision->Ball();
        obs.add_circle(vector2f(ball.Pos().x(), ball.Pos().y()), vector2f(ball.Vel().x(), ball.Vel().y()), BALL_AVOID_DIST, 1, DRAW_OBSTACLES);
    }

    if(flags & PlayerStatus::DODGE_REFEREE_AREA) {
        const MobileVisionT& ball = pVision->Ball();
        obs.add_circle(vector2f(ball.Pos().x(), ball.Pos().y()), vector2f(0.0f, 0.0f), 50.0f, 1, DRAW_OBSTACLES);
    }

    obs.set_mask(1);
}
