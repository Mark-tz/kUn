#include "Factory.h"
#include <TaskMediator.h>

#include <misc_types.h>
#include <WorldModel.h>
#include "CommandFactory.h"
#include "GDebugEngine.h"

/************************************************************************/
/*								concrete skill							*/
/************************************************************************/
//1.atom skills(TODO)
#include "GotoPosition.h"
#include "GotoPositionNew.h"
#include "GoImmortalRush.h"
#include "SmartGotoPosition.h"

//2.basic skills(TODO)
#include "StopRobot.h"
#include "Speed.h"
#include "OpenSpeed.h"
#include "InterceptBallV3.h"
#include "CrazyPush.h"
#include "GoAndTurnKickV3.h"
#include "ChaseKickV2.h"
#include "ZChaseKick.h"
#include "TouchKick.h"
#include "PenaltyDefV2.h"
#include "PenaltyDef2017V2.h"
#include "AdvanceBallV1.h"
#include "AdvanceBallV2.h"
#include "StaticGetBallNew.h"
#include "GetBallV4.h"
#include "SlowGetBall.h"
#include "Marking.h"
#include "ZMarking.h"
#include "ZBlocking.h"
#include "GetBallV3.h"
#include "ReceivePass.h"
#include "PenaltyKick2017V1.h"
#include "PenaltyKick2017V2.h"
#include "GoAvoidShootLine.h"
#include "DribbleTurn.h"
#include "MarkingTouch.h"
#include "MarkingFront.h"
#include "DribbleTurnKick.h"
#include "InterceptBallV7.h"
#include "InterceptTouch.h"
#include "OpenSpeedCircle.h"
#include "ZGoalie.h"
#include "ZPass.h"
#include "ZCirclePass.h"
#include "zmessi.h"
#include "HoldBall.h"
#include "GoAndTurnKickV4.h"
#include "CmuTurnKickV1.h"
#include "ZPassV2.h"

/************************************************************************/
/*                      TaskFactoryV2									*/
/* 请注意:																*/
/* 上层（CStatedScriptPlay) 通过调用 CBasicPlay 中的 setTask() 设定任务	*/
/* 并将每个策略执行小车对应的任务存放在 TaskMediator 里面				*/
/* 执行（ActionModule）通过任务的 execute() 接口生成任务小车对应的指令	*/
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// an template used as a task pool for storing tasks for executing player
template < class CTaskType >
CPlayerTask* CTaskFactoryV2::MakeTask(const TaskT& task )
{
	static CTaskType taskPool[Param::Field::MAX_PLAYER + 1];
	taskPool[task.executor].reset(task);
	return &taskPool[task.executor];
}

//////////////////////////////////////////////////////////////////////////
// current now debugged skill for game
CPlayerTask* CTaskFactoryV2::GotoPosition(const TaskT& task) {
	return MakeTask< CGotoPositionV2 >(task);
}

CPlayerTask* CTaskFactoryV2::GotoPositionNew(const TaskT& task) {
    return MakeTask< CGotoPositionNew >(task);
}

CPlayerTask* CTaskFactoryV2::SmartGotoPosition(const TaskT& task) {
    return MakeTask< CSmartGotoPositionV2 >(task);
}

CPlayerTask* CTaskFactoryV2::GoImmortalRush(const TaskT& task) {
    return MakeTask< CGoImmortalRush >(task);
}

CPlayerTask* CTaskFactoryV2::GoAvoidShootLine(const TaskT& task){
	return MakeTask< CGoAvoidShootLine>(task);
}

CPlayerTask* CTaskFactoryV2::StopRobot(const TaskT& task) {
	return MakeTask< CStopRobotV2 >(task);
}

CPlayerTask	* CTaskFactoryV2::Speed(const TaskT& task) {
	return MakeTask< CSpeed >(task);
}

CPlayerTask	* CTaskFactoryV2::OpenSpeed(const TaskT& task) {
	return MakeTask< COpenSpeed >(task);
}

CPlayerTask * CTaskFactoryV2::OpenSpeedCircle(const TaskT &task) {
    return MakeTask< COpenSpeedCircle >(task);
}

CPlayerTask* CTaskFactoryV2::StaticGetBallNew(const TaskT& task) {
	return MakeTask< CStaticGetBallNew >(task);
}

CPlayerTask* CTaskFactoryV2::NoneTrajGetBall(const TaskT& task) {
    return MakeTask< CGetBallV3 >(task);
}

CPlayerTask* CTaskFactoryV2::GetBallV4(const TaskT& task) {
	return MakeTask< CGetBallV4 >(task);
}

CPlayerTask* CTaskFactoryV2::ZGoalie(const TaskT& task) {
    return MakeTask< CZGoalie >(task);
}

CPlayerTask* CTaskFactoryV2::ChaseKickV1(const TaskT& task) {
    return MakeTask< CZChaseKick >(task);
}

CPlayerTask* CTaskFactoryV2::ChaseKickV2(const TaskT& task){
	return MakeTask< CChaseKickV2>(task);
}

CPlayerTask* CTaskFactoryV2::ZChaseKick(const TaskT& task){
    return MakeTask< CZChaseKick>(task);
}

CPlayerTask* CTaskFactoryV2::TouchKick(const TaskT& task) {
	return MakeTask< CTouchKick >(task);
}

CPlayerTask* CTaskFactoryV2::InterceptBallV3(const TaskT& task) {
	return MakeTask< CInterceptBallV3>(task);
}

CPlayerTask* CTaskFactoryV2::MarkingTouch(const TaskT& task) {
	return MakeTask< CMarkingTouch >(task);
}

CPlayerTask* CTaskFactoryV2::MarkingFront(const TaskT& task) {
	return MakeTask< CMarkingFront >(task);
}

CPlayerTask* CTaskFactoryV2::CarzyPush(const TaskT& task){
	return MakeTask<CCrazyPush>(task);
}

CPlayerTask* CTaskFactoryV2::PenaltyDefV2(const TaskT& task) {
	return MakeTask< CPenaltyDefV2 >(task);
}

CPlayerTask* CTaskFactoryV2::PenaltyDef2017V2(const TaskT& task) {
	return MakeTask< CPenaltyDef2017V2 >(task);
}

CPlayerTask* CTaskFactoryV2::AdvanceBallV1(const TaskT& task) {
	return MakeTask< CAdvanceBallV1 >(task);
}

CPlayerTask* CTaskFactoryV2::AdvanceBallV2(const TaskT& task) {
	return MakeTask< CAdvanceBallV2 >(task);
}

CPlayerTask* CTaskFactoryV2::GoAndTurnKickV3(const TaskT& task) {
	return MakeTask< CGoAndTurnKickV3 >(task);
}

CPlayerTask* CTaskFactoryV2::SlowGetBall(const TaskT& task) {
	return MakeTask< CSlowGetBall >(task);
}

CPlayerTask* CTaskFactoryV2::Marking(const TaskT& task) {
	return MakeTask< CMarking >(task);
}

CPlayerTask* CTaskFactoryV2::ZMarking(const TaskT& task) {
	return MakeTask< CZMarking >(task);
}


CPlayerTask* CTaskFactoryV2::ZBlocking(const TaskT& task) {
    return MakeTask< CZBlocking >(task);
}

CPlayerTask* CTaskFactoryV2::ReceivePass(const TaskT& task) {
	return MakeTask< CReceivePass >(task);
}

CPlayerTask* CTaskFactoryV2::InterceptBallV7(const TaskT& task)
{
	return MakeTask< CInterceptBallV7 >(task);
}

CPlayerTask* CTaskFactoryV2::PenaltyKick2017V1(const TaskT& task) {
	return MakeTask<CPenaltyKick2017V1>(task);
}

CPlayerTask* CTaskFactoryV2::PenaltyKick2017V2(const TaskT& task) {
	return MakeTask<CPenaltyKick2017V2>(task);
}

CPlayerTask* CTaskFactoryV2::DribbleTurn(const TaskT& task){
	return MakeTask<CDribbleTurn>(task);
}

CPlayerTask* CTaskFactoryV2::ZPass(const TaskT& task){
    return MakeTask<CZPass>(task);
}

CPlayerTask* CTaskFactoryV2::Messi(const TaskT& task){
    return MakeTask<CZMessi>(task);
}

CPlayerTask* CTaskFactoryV2::ZCirclePass(const TaskT& task){
    return MakeTask<CZCirclePass>(task);
}

CPlayerTask* CTaskFactoryV2::DribbleTurnKick(const TaskT& task){
	return MakeTask<CDribbleTurnKick>(task);
}

CPlayerTask* CTaskFactoryV2::InterceptTouch(const TaskT& task) {
	return MakeTask<CInterceptTouch>(task);
}

CPlayerTask* CTaskFactoryV2::HoldBall(const TaskT &task){
    return MakeTask<CHoldBall>(task);
}

CPlayerTask* CTaskFactoryV2::GoAndTurnKickV4(const TaskT &task){
    return MakeTask<CGoAndTurnKickV4>(task);
}

CPlayerTask* CTaskFactoryV2::CmuTurnKickV1(const TaskT &task){
    return MakeTask<CCmuTurnKickV1>(task);
}

CPlayerTask* CTaskFactoryV2::ZPassV2(const TaskT &task){
    return MakeTask<CZPassV2>(task);
}

//////////////////////////////////////////////////////////////////////////
// define the namespace used to provide interface for task calling
namespace PlayerRole {
	CPlayerTask* makeItStop(const int num, const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->StopRobot(playerTask);
	}
	CPlayerTask* makeItGoto(const int num, const CGeoPoint& target, const double dir, const int flags, const int sender)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.pos = target;
        playerTask.player.vel = CVector(0.0,0.0);
		playerTask.player.rotvel = 0;
		playerTask.player.angle = dir;
		playerTask.player.flag = flags;
		playerTask.ball.Sender = sender;
		return TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
	}
	CPlayerTask* makeItGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotvel, const int flags, const int sender)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.pos = target;
		playerTask.player.angle = dir;
		playerTask.player.vel = vel;
		playerTask.player.rotvel = rotvel;
		playerTask.player.flag = flags;
		playerTask.ball.Sender = sender;
		return TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
	}

    CPlayerTask* makeItGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotVel, const double& maxAcc, const double& maxRotAcc, const double& maxSpeed, const double& maxRotSpeed, const int flags, const int sender) {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.angle = dir;
        playerTask.player.vel = vel;
        playerTask.player.rotvel = rotVel;
        playerTask.player.max_acceleration = maxAcc;
        playerTask.player.max_rot_acceleration = maxRotAcc;
        playerTask.player.max_speed = maxSpeed;
        playerTask.player.max_rot_speed = maxRotSpeed;
        playerTask.player.flag = flags;
        playerTask.ball.Sender = sender;
        return TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
    }


	CPlayerTask* makeItSimpleGoto(const int num, const CGeoPoint& target, const double dir, const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.pos = target;
		playerTask.player.vel = CVector(0.0,0.0);
		playerTask.player.rotvel = 0;
		playerTask.player.angle = dir;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->GotoPosition(playerTask);
	}


	CPlayerTask* makeItSimpleGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotvel, const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.pos = target;
		playerTask.player.angle = dir;
		playerTask.player.vel = vel;
		playerTask.player.rotvel = rotvel;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->GotoPosition(playerTask);
	}

    CPlayerTask* makeItSimpleGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotVel, const double& maxAcc, const double& maxRotAcc, const double& maxSpeed, const double& maxRotSpeed, const int flags) {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.angle = dir;
        playerTask.player.vel = vel;
        playerTask.player.rotvel = rotVel;
        playerTask.player.max_acceleration = maxAcc;
        playerTask.player.max_rot_acceleration = maxRotAcc;
        playerTask.player.max_speed = maxSpeed;
        playerTask.player.max_rot_speed = maxRotSpeed;
        playerTask.player.flag = flags;
        return TaskFactoryV2::Instance()->GotoPosition(playerTask);
    }

    CPlayerTask* makeItSmartGoto(const int num, const CGeoPoint& target, const double dir, const int flags)
    {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.vel = CVector(0.0,0.0);
        playerTask.player.rotvel = 0;
        playerTask.player.angle = dir;
        playerTask.player.flag = flags;
        return TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
    }

    CPlayerTask* makeItSmartGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotvel, const int flags)
    {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.angle = dir;
        playerTask.player.vel = vel;
        playerTask.player.rotvel = rotvel;
        playerTask.player.flag = flags;
        return TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
    }

    CPlayerTask* makeItSmartGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotVel, const double& maxAcc, const double& maxRotAcc, const double& maxSpeed, const double& maxRotSpeed, const int flags) {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.angle = dir;
        playerTask.player.vel = vel;
        playerTask.player.rotvel = rotVel;
        playerTask.player.max_acceleration = maxAcc;
        playerTask.player.max_rot_acceleration = maxRotAcc;
        playerTask.player.max_speed = maxSpeed;
        playerTask.player.max_rot_speed = maxRotSpeed;
        playerTask.player.flag = flags;
        return TaskFactoryV2::Instance()->SmartGotoPosition(playerTask);
    }


	CPlayerTask* makeItCrazyPush(const int num, double faceDir)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = faceDir;
		return TaskFactoryV2::Instance()->CarzyPush(playerTask);
	}
	CPlayerTask* makeItRun(const int num, const double speedX, const double speedY, const double rotSpeed, int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.speed_x = speedX;
		playerTask.player.speed_y = speedY;
		playerTask.player.rotate_speed = rotSpeed;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->Speed(playerTask);
	}
    CPlayerTask* makeItOpenRun(const int num, const double speedX, const double speedY, const double rotSpeed, int flags)
    {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.speed_x = speedX;
        playerTask.player.speed_y = speedY;
        playerTask.player.rotate_speed = rotSpeed;
        playerTask.player.flag = flags;
        return TaskFactoryV2::Instance()->OpenSpeed(playerTask);
    }

	CPlayerTask* makeItStaticGetBallNew(const int num, const double dir, CVector finalVel, int flags, double StopDist, CTRL_METHOD mode)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = dir;
		playerTask.player.vel = finalVel;
		playerTask.player.flag = flags;
		playerTask.player.rotvel = StopDist;
		playerTask.player.specified_ctrl_method = mode;
		return TaskFactoryV2::Instance()->StaticGetBallNew(playerTask);
	}

	CPlayerTask* makeItNoneTrajGetBall(const int num,const double dir,CVector finalVel,int flags,double StopDist,CTRL_METHOD mode)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = dir;
		playerTask.player.vel = finalVel;
		playerTask.player.flag = flags;
		playerTask.player.rotvel = StopDist;
		playerTask.player.specified_ctrl_method = mode;
		return TaskFactoryV2::Instance()->NoneTrajGetBall(playerTask);
	}

	CPlayerTask* makeItChaseKickV1(const int num, double faceDir, int flags,bool isChip)
	//重载 add by gty 17-3-26
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = faceDir;
		playerTask.player.flag = flags;
		playerTask.player.ischipkick = isChip;
		return TaskFactoryV2::Instance()->ChaseKickV1(playerTask);
	}
	CPlayerTask* makeItChaseKickV1(const int num,double faceDir,int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = faceDir;
		playerTask.player.flag = flags;
        return TaskFactoryV2::Instance()->ZChaseKick(playerTask);
	}

	CPlayerTask* makeItChaseKickV2(const int num,double faceDir,int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = faceDir;
		//playerTask.player.ischipkick = isChip;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->ChaseKickV2(playerTask);
	}

    CPlayerTask* makeItZChaseKick(const int num,double faceDir,int flags)
    {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.angle = faceDir;
        //playerTask.player.ischipkick = isChip;
        playerTask.player.flag = flags;
        return TaskFactoryV2::Instance()->ZChaseKick(playerTask);
    }

	CPlayerTask* makeItTouchKick(const int num,double kickDir, bool isPass, int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = kickDir;
		playerTask.player.ispass = isPass;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->TouchKick(playerTask);
	}

	CPlayerTask* makeItInterKickV3(const int num, const double dir, const int flags,const bool kickway)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = dir;
		playerTask.player.flag = flags;
		playerTask.player.ischipkick = kickway;

		//		playerTask.player.pos = target;
		return TaskFactoryV2::Instance()->InterceptBallV3(playerTask);
	}


	CPlayerTask* makeItMarkingTouch(const int num,const double kickDir,const CGeoPoint leftUpPos,const CGeoPoint rightDownPos,const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = kickDir;
		playerTask.player.flag = flags;
		playerTask.ball.pos=leftUpPos;
		playerTask.player.pos=rightDownPos;
		return TaskFactoryV2::Instance()->MarkingTouch(playerTask);
	}

	CPlayerTask* makeItMarkingFront(const int num,const int markNum,const double kickDir,const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.ball.Sender=markNum;
		playerTask.player.angle = kickDir;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->MarkingFront(playerTask);
	}

	CPlayerTask* makeItAdvanceBallV1(const int num,const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->AdvanceBallV1(playerTask);
	}
	CPlayerTask* makeItAdvanceBallV2(const int num, const int flags, const int tendemNum)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flags;
		playerTask.ball.receiver = tendemNum;
		return TaskFactoryV2::Instance()->AdvanceBallV2(playerTask);
	}

    CPlayerTask* makeItGetBallV4(const int num, const int flag, const CGeoPoint& pos, const CGeoPoint& waitPos, const int power)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flag;
        //playerTask.player.angle = targetdir;
		playerTask.player.pos = pos;
		playerTask.player.kickpower = waitPos.x();
		playerTask.player.chipkickpower = waitPos.y();
        playerTask.player.rotdir =power;
		return TaskFactoryV2::Instance()->GetBallV4(playerTask);
	}

    CPlayerTask* makeItZGoalie(const int runner,const CGeoPoint& pos,const int power,const int flag){
        static TaskT playerTask;
        playerTask.executor = runner;
        playerTask.player.flag = flag;
        playerTask.player.pos = pos;
        playerTask.player.kickpower = power;
        return TaskFactoryV2::Instance()->ZGoalie(playerTask);
    }

	CPlayerTask* makeItGoAndTurnKickV3(const int num ,const double targetdir,int circleNum,const double fixAngle,const double maxAcc,const int radius,const int numPerCir,const double gotoPre,const double gotoDist,const double adjustPre,const double kickprecision,const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = targetdir;
		playerTask.player.flag = flags;
		playerTask.ball.angle = circleNum;
		playerTask.player.kickprecision = kickprecision;
		playerTask.player.rotate_speed = fixAngle;
		playerTask.player.max_acceleration = maxAcc;
		playerTask.player.rotvel = radius;
		playerTask.player.chipkickpower = numPerCir;
		playerTask.player.kickpower = gotoPre;
		playerTask.player.max_deceleration = gotoDist;
		playerTask.player.speed_x = adjustPre;
		return TaskFactoryV2::Instance()->GoAndTurnKickV3(playerTask);
	}

	CPlayerTask* makeItSlowGetBall(const int num, const double dir, const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = dir;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->SlowGetBall(playerTask);
	}
	CPlayerTask* makeItMarkEnemy(const int num,const int priority,const bool front, const int flags,const CGeoPoint pos,const double dir)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.ball.Sender = priority;
		playerTask.ball.front = front;
		playerTask.player.flag = flags;
		playerTask.player.pos = pos;
		playerTask.player.angle = dir;
		return TaskFactoryV2::Instance()->Marking(playerTask);
	}
	CPlayerTask* makeItZMarkEnemy(const int num, const int priority, const bool front, const int flags, const CGeoPoint pos, const double dir)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.ball.Sender = priority;
		playerTask.ball.front = front;
		playerTask.player.flag = flags;
		playerTask.player.pos = pos;
		playerTask.player.angle = dir;
		return TaskFactoryV2::Instance()->ZMarking(playerTask);
	}

    CPlayerTask* makeItAMarkEnemy(const int num, const int enemyNum, const CGeoPoint pos)
    {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.ball.Sender = enemyNum;
        playerTask.player.pos = pos;
        return TaskFactoryV2::Instance()->ZBlocking(playerTask);
    }

	CPlayerTask* makeItReceivePass(const int num, const double dir, const int flags)
	{
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = dir;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->ReceivePass(playerTask);
	}

	CPlayerTask* makeItPenaltyGoalieV2(const int num, const int flags) {
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->PenaltyDefV2(playerTask);
	}

	CPlayerTask* makeItPenaltyGoalie2017V2(const int num, const int flags) {
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flags;
		return TaskFactoryV2::Instance()->PenaltyDef2017V2(playerTask);
	}


	CPlayerTask* makeItPenaltyKick2017V1(const int num, const int flag /* = 0 */) {
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flag;
		return TaskFactoryV2::Instance()->PenaltyKick2017V1(playerTask);
	}

	CPlayerTask* makeItPenaltyKick2017V2(const int num, const int flag /* = 0 */) {
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.flag = flag;
		return TaskFactoryV2::Instance()->PenaltyKick2017V2(playerTask);
	}

	CPlayerTask* makeItDribbleTurn(const int num, const double finalDir, const double pre) {
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.angle = finalDir;
		playerTask.player.speed_x = pre;
		return TaskFactoryV2::Instance()->DribbleTurn(playerTask);
	}

    CPlayerTask* makeItZPass(const int num,const CGeoPoint& target, const double power, const int flag) {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.kickpower = power;
        if(flag == 1)//kick.lua中flat为1， chip为2
            playerTask.player.ischipkick = false;
        else if(flag == 2)
            playerTask.player.ischipkick = true;
        return TaskFactoryV2::Instance()->ZPass(playerTask);
    }

    CPlayerTask* makeItMessi(const int num,const CGeoPoint& target,const double power){
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.kickpower = power;
        return TaskFactoryV2::Instance()->Messi(playerTask);
    }

    CPlayerTask* makeItZCirclePass(const int num, CGeoPoint target, const double power, const int flag) {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.kickpower = power;
        if(flag == 1)//kick.lua中flat为1， chip为2
            playerTask.player.ischipkick = false;
        else if(flag == 2)
            playerTask.player.ischipkick = true;
        return TaskFactoryV2::Instance()->ZCirclePass(playerTask);
    }

	CPlayerTask* makeItDribbleTurnKick(const int num, const double finalDir, const double turnRotVel,const double kickPower) {
		static TaskT playerTask;
		playerTask.executor = num;
        playerTask.player.angle = finalDir;
        playerTask.player.rotvel=turnRotVel;
		playerTask.player.kickpower=kickPower;
		return TaskFactoryV2::Instance()->DribbleTurnKick(playerTask);
	}


    CPlayerTask* makeItInterceptTouch(const int num, const CGeoPoint& waitPos, const double touchDir, const double power, const double buffer, const bool useChip,const bool testMode, const CGeoPoint target) {
		static TaskT playerTask;
		playerTask.executor = num;
		playerTask.player.pos = waitPos;
		playerTask.player.angle = touchDir;
		playerTask.player.kickpower = power;
		playerTask.player.chipkickpower = buffer;  // 截球时后退的距离
		playerTask.player.ischipkick = useChip;
		playerTask.ball.front = testMode; // testMode use for testing compensation. !!!!!!!!!!
        playerTask.player.speed_x = target.x();
        playerTask.player.speed_y = target.y();
		return TaskFactoryV2::Instance()->InterceptTouch(playerTask);
	}

    CPlayerTask* makeItOpenSpeedCircle(const int num, const double dist2Center,
                                       const int rotateMethod,
                                       const double finalAngle,
                                       const int needDribble,
                                       const double dirDiff,
                                       const int openspeedversion) {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.speed_x = dist2Center;
        playerTask.player.rotdir = rotateMethod;
        playerTask.player.angle = finalAngle;
        playerTask.player.speed_y = dirDiff;
        playerTask.player.needdribble = needDribble;
        playerTask.player.flag = openspeedversion;
        return TaskFactoryV2::Instance()->OpenSpeedCircle(playerTask);
    }

    CPlayerTask* makeItHoldBall(const int num, const CGeoPoint& target){
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        return TaskFactoryV2::Instance()->HoldBall(playerTask);
    }

    CPlayerTask* makeItGoAndTurnKickV4(const int num, const CGeoPoint& pos,
                                       const int flag, const double power,
                                       const double angle){
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = pos;
        playerTask.player.flag = flag;
        playerTask.player.kickpower = power;
        playerTask.player.angle = angle;
        return TaskFactoryV2::Instance()->GoAndTurnKickV4(playerTask);
    }
    CPlayerTask* makeItCmuTurnKickV1(const int num, const CGeoPoint& pos,
                                     const int flag, const double power,
                                     const double dir){
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = pos;
        playerTask.player.flag = flag;
        playerTask.player.kickpower = power;
        playerTask.player.angle = dir;
        return TaskFactoryV2::Instance()->CmuTurnKickV1(playerTask);
    }

    CPlayerTask* makeItZPassV2(const int num,const CGeoPoint& target,
                               const CGeoPoint& waitpos, const double power,
                               const double dir, const int flag) {
        static TaskT playerTask;
        playerTask.executor = num;
        playerTask.player.pos = target;
        playerTask.player.speed_x = waitpos.x();
        playerTask.player.speed_y = waitpos.y();
        playerTask.player.kickpower = power;
        playerTask.player.angle = dir;
        playerTask.player.flag = flag;
        return TaskFactoryV2::Instance()->ZPassV2(playerTask);
    }
}
