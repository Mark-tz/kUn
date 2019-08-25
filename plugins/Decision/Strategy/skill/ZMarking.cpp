#include "ZMarking.h"
#include <skill/Factory.h>
#include "BestPlayer.h"
#include "VisionModule.h"
#include "utils.h"
#include "GDebugEngine.h"
#include "geometry.h"
#include "WorldModel.h"
#include "defence/DefenceInfo.h"
#include "MarkingPosV2.h"
#include "SkillUtils.h"
#include "TaskMediator.h"

namespace{
	static bool FRIENDLY_MODE = false;//友好盯人
	static bool NOT_VOILENCE = false;//不采取暴力模式,优先级高于FRIENDLY_MODE

	const bool VERBOSE_MODE = false;

	CGeoPoint ourGoalPoint;       //我方球门

	const double simpleGotoDirLimt = Param::Math::PI*150/180;
	const double enemyPredictTime = 3;											//敌人的位置预测
	const double simpleGotoStrictDirLimt = Param::Math::PI * 70/180;			//更加严厉的角度限制
	const double PATH_PLAN_CHANGE_DIST = 75;									//修改该值以获得更好的速度规划变动点!!!
	const double FRIENDLY_DIST_LIMIT = 10;										//友好模式 距离限制

	bool kickOffSide[Param::Field::MAX_PLAYER+1] = {0};

	const double kMarkingFrontMinDist = Param::Field::PITCH_WIDTH * 2 / 3;
	const CGeoPoint kOurGoal = CGeoPoint(-Param::Field::PITCH_LENGTH / 2, 0);
	const double kEnemyReceiverOffsetThresholdIn = 25;
	const double kEnemyRecieverOffsetThresholdOut = 40;

	const double MARKING_DIST_RATE = 0.8;
}
CZMarking::CZMarking(){
	ourGoalPoint = CGeoPoint(-Param::Field::PITCH_LENGTH/2,0);
	enemyNum = 1;
	_lastCycle = 0;

	// 判断是否绕前截球使用的变量
	needToUpdateTheirKicker = true;
	isMeCloserToBall = false;
	isTheirKickerPosSafe = false;
	isBallToEnemy = false;

	// 从xml中读取盯人模式 0是友好模式，1是普通模式，2是暴力模式
	int MARKING_MODE;
	ZSS::ZParamManager::instance()->loadParam(MARKING_MODE, "Defence/MARKING_MODE", 1);

	//NOT_VOILENCE = false:暴力模式
	//NOT_VOILENCE = true,FRIENDLY_MODE = false：普通模式	
	//NOT_VOILENCE = true,FRIENDLY_MODE = true：友好模式
	switch (MARKING_MODE) {
		case 0:  // 友好模式
			NOT_VOILENCE = true;
			FRIENDLY_MODE = true;
			break;
		case 1:  // 普通模式
			NOT_VOILENCE = true;
			FRIENDLY_MODE = false;
			break;
		case 2:  // 暴力模式
			NOT_VOILENCE = false;
			FRIENDLY_MODE = false;
			break;
	}
}

void CZMarking::plan(const CVisionModule* pVision){
	static bool is_first = true;
	//内部状态进行重置
	if ( pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1 )
		setState(BEGINNING);

	const MobileVisionT& ball = pVision->Ball();
	int vecNumber = task().executor;   //我方小车
	int enemyNum = task().ball.Sender;  //敌方
	bool front = task().ball.front;
	double markMethod = task().player.angle;
	CGeoPoint markPos;	

	if (is_first == true) is_first = false;

	CGeoPoint taskPos = task().player.pos;
    if (taskPos.dist(CGeoPoint(1000,1000)) < 10)
        markPos = MarkingPosV2::Instance()->getMarkingPosByNum(pVision,enemyNum);
	else markPos = task().player.pos;
	DefenceInfo::Instance()->setMarkList(pVision,vecNumber,enemyNum);

	const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
	const PlayerVisionT& enemy = pVision->TheirPlayer(enemyNum);
	CGeoPoint enemyPos = enemy.Pos();
	CGeoPoint mePos = me.Pos();	
	double me2ballDir = CVector(ball.Pos() - mePos).dir();
	double me2theirGoalDir = CVector(CGeoPoint(Param::Field::PITCH_LENGTH/2.0,0) - mePos).dir();
	TaskT MarkingTask(task());
	//避禁区
	MarkingTask.player.flag |= PlayerStatus::DODGE_OUR_DEFENSE_BOX;
	//定位球避开开球50cm区域
	const string refMsg = WorldModel::Instance()->CurrentRefereeMsg();
	if ("TheirIndirectKick" == refMsg || "TheirDirectKick" == refMsg || "TheirKickOff" == refMsg || "GameStop" == refMsg)
		MarkingTask.player.flag |= PlayerStatus::DODGE_REFEREE_AREA;

	//路径规划设置，采用CMU的轨迹规划
	if (me.Pos().dist(markPos) < PATH_PLAN_CHANGE_DIST){
		MarkingTask.player.is_specify_ctrl_method = true;
		MarkingTask.player.specified_ctrl_method = CMU_TRAJ;
	}

	//横向被甩开补充
	CVector opp2ourGoalVector = CVector(ourGoalPoint - enemyPos);
	CVector oppVel = enemy.Vel();
	double angle_oppVel_opp2Goal = fabs(Utils::Normalize(opp2ourGoalVector.dir() - oppVel.dir()));
	double sinPre = std::sin(angle_oppVel_opp2Goal);
	
	//避障设置
	CVector enemyPos2me = mePos - enemyPos;
	CVector enemyPos2ourGoal = ourGoalPoint - enemyPos;
	bool friendlyLimit = true;
	if (FRIENDLY_MODE && NOT_VOILENCE)
		friendlyLimit = fabs(Utils::Normalize(enemyPos2ourGoal.dir() - enemyPos2me.dir())) < simpleGotoStrictDirLimt;
	if (sinPre>0.8 && oppVel.mod() >40){
		GDebugEngine::Instance()->gui_debug_msg(markPos,"M",COLOR_ORANGE);
		double ratio = 0;
		double absvel = fabs(enemy.Vel().y());
		if (absvel >120) ratio = 1;
		else if (absvel >80 && absvel<=120) ratio = 0.025*absvel -2;
		else ratio = 0;
	
		double shiftDist = ratio*oppVel.y();
		if (shiftDist <-100) shiftDist = -100;
		if (shiftDist >100) shiftDist = 100;
		markPos = markPos + Utils::Polar2Vector(shiftDist,Param::Math::PI/2);
	}

	//对方朝着盯人车
	CGeoSegment enemySeg = CGeoSegment(enemyPos,enemyPos+Utils::Polar2Vector(500,enemy.Vel().dir()));
	CGeoPoint meProj = enemySeg.projection(mePos);
	if(enemy.Vel().mod()>80){
		if (enemySeg.IsPointOnLineOnSegment(meProj) && meProj.dist(mePos)<45 && mePos.dist(enemyPos)>60){
			markPos = mePos;
            GDebugEngine::Instance()->gui_debug_line(enemyPos,enemyPos+Utils::Polar2Vector(500,enemy.Vel().dir()),COLOR_WHITE);
		}
	}

	if (Utils::OutOfField(markPos,0))
		markPos = Utils::MakeInField(markPos,20);

	MarkingTask.player.pos = markPos;
	MarkingTask.player.angle = CVector(CGeoPoint(Param::Field::PITCH_LENGTH/2.0,0) - me.Pos()).dir();


	MarkingTask.player.is_specify_ctrl_method = true;
	MarkingTask.player.specified_ctrl_method = CMU_TRAJ;
	//当是角球区域，盯人车对着球
	if (("TheirIndirectKick" == refMsg || "TheirDirectKick" == refMsg || "GameStop" == refMsg) && pVision->Ball().X()<0 ) 
		MarkingTask.player.angle = me2ballDir;
	if (DefenceInfo::Instance()->getOppPlayerByNum(enemyNum)->isTheRole("RReceiver")){
		MarkingTask.player.is_specify_ctrl_method = true;
		MarkingTask.player.specified_ctrl_method = CMU_TRAJ;
		if (true == NameSpaceMarkingPosV2::DENY_LOG[enemyNum] && fabs(Utils::Normalize(me2ballDir - me2theirGoalDir)) < Param::Math::PI * 60 / 180){
			MarkingTask.player.angle = me2theirGoalDir;
			markMethod = me2theirGoalDir;
		}
	}
	bool checkKickOffArea = false;
	if ("TheirIndirectKick" == refMsg || "TheirDirectKick" == refMsg){
		if (pVision->Ball().Y() >0)
			kickOffSide[vecNumber] = false;
		else
			kickOffSide[vecNumber] = true;
	}
	if (kickOffSide[vecNumber] == false){
		CGeoPoint leftUp = CGeoPoint(Param::Field::PITCH_LENGTH/2,30+20);//？？？？？
		CGeoPoint rightDown = CGeoPoint(80,Param::Field::PITCH_WIDTH/2);
		if (DefenceInfo::Instance()->checkInRecArea(enemyNum,pVision,MarkField(leftUp,rightDown)))
			checkKickOffArea = true;
	}
	else if (kickOffSide[vecNumber] == true){
		CGeoPoint leftUp = CGeoPoint(Param::Field::PITCH_LENGTH/2,-Param::Field::PITCH_WIDTH/2);
		CGeoPoint rightDown = CGeoPoint(80,-30-20);
		if (DefenceInfo::Instance()->checkInRecArea(enemyNum,pVision,MarkField(leftUp,rightDown)))
			checkKickOffArea = true;
	}
	if (markMethod<100){
		MarkingTask.player.angle = markMethod;
	}
	int flag = task().player.flag;

	/****************************************************************************************/
	if (flag & PlayerStatus::TURN_AROUND_FRONT){
		// 正常比赛绕前
		MarkingTask.player.flag ^= PlayerStatus::TURN_AROUND_FRONT;
			//MarkingTask.player.flag |= PlayerStatus::NOT_AVOID_THEIR_VEHICLE;
		MarkingTask.player.angle = me2ballDir;
		MarkingTask.player.pos = enemyPos + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_SIZE * 2, me2ballDir);
		if ( "TheirKickOff" == refMsg && MarkingTask.player.pos.x() > -15)
            MarkingTask.player.pos.setX(-15);
		setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(MarkingTask));
	} 
	else if(front == true){
		if ( "TheirKickOff" == refMsg && MarkingTask.player.pos.x() > -15)
			MarkingTask.player.pos.setX(-15);
        DefenceInfo::Instance()->setMarkMode(vecNumber,enemyNum,true);
		setSubTask(PlayerRole::makeItMarkingFront(vecNumber,enemyNum,MarkingTask.player.angle,MarkingTask.player.flag));
	}
	else {
        //modify by Wang
        CGeoPoint interceptPoint = ZSkillUtils::instance()->predictedTheirInterPoint(enemyPos, ball.RawPos());
		//cout << "interceptPoint:" << interceptPoint.x()<<", "<< interceptPoint.y() << endl;
		double interDist = MARKING_DIST_RATE * (enemyPos - interceptPoint).mod();
		if (interDist < Param::Vehicle::V2::PLAYER_SIZE * 2)
			interDist = Param::Vehicle::V2::PLAYER_SIZE * 2 + 2;
		
		CVector point2goal = Utils::Polar2Vector(interDist, (CGeoPoint(-Param::Field::PITCH_LENGTH, 0)- interceptPoint).dir());
		MarkingTask.player.pos = interceptPoint + point2goal;
		MarkingTask.player.angle = me2ballDir;
		//防止车出场
		if (Utils::OutOfField(MarkingTask.player.pos, 18))
			MarkingTask.player.pos = Utils::MakeInField(MarkingTask.player.pos, 18);
		//防止车进入禁区
		if (Utils::InOurPenaltyArea(MarkingTask.player.pos, 18))
			MarkingTask.player.pos = Utils::MakeOutOfOurPenaltyArea(MarkingTask.player.pos, 18);
		//防止禁区前车挤车,绕前marking
		if ((MarkingTask.player.pos - enemyPos).mod() < 23)
			MarkingTask.player.pos = enemyPos + Utils::Polar2Vector(20, (ball.RawPos()- enemyPos).dir());
		if ("TheirKickOff" == refMsg && MarkingTask.player.pos.x() > -15)
				MarkingTask.player.pos.setX(-15);
		DefenceInfo::Instance()->setMarkMode(vecNumber,enemyNum,false);

        if(! enemy.Valid()){
            MarkingTask.player.pos = CGeoPoint(-150, 0);
            MarkingTask.player.angle = me2ballDir;
            MarkingTask.player.flag |= PlayerStatus::ALLOW_DSS;
        }
        else{
            GDebugEngine::Instance()->gui_debug_line(enemyPos,MarkingTask.player.pos,COLOR_WHITE);
        }
		setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(MarkingTask));
	}

    GDebugEngine::Instance()->gui_debug_msg(MarkingTask.player.pos,"M",COLOR_WHITE);
	_lastCycle = pVision->Cycle();
	CStatedTask::plan(pVision);
}


CPlayerCommand* CZMarking::execute(const CVisionModule* pVision){
	if( subTask() ) return subTask()->execute(pVision);
	return NULL;
}
