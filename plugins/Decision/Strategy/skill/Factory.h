#ifndef _TASK_FACTORY_V2_H_
#define _TASK_FACTORY_V2_H_

#include <singleton.h>
#include <misc_types.h>
#include "param.h"
/************************************************************************/
/*                         CTaskFactoryV2                               */
/************************************************************************/

class CPlayerTask;
class CTaskFactoryV2{
public:
	CPlayerTask* GotoPosition(const TaskT& task);
    CPlayerTask* GotoPositionNew(const TaskT& task);
    CPlayerTask* GoImmortalRush(const TaskT& task);
	CPlayerTask* SmartGotoPosition(const TaskT& task);
	CPlayerTask* GoAvoidShootLine(const TaskT& task);
    CPlayerTask* RotateToGetBall(const TaskT& task);// d
    CPlayerTask* InterceptBallV2(const TaskT& task);// d
    CPlayerTask* InterceptBallV3(const TaskT& task);// d
    CPlayerTask* InterceptBallV4(const TaskT& task);// d
    CPlayerTask* InterceptBallV5(const TaskT& task);// d
    CPlayerTask* InterceptBallV6(const TaskT& task);// d
    CPlayerTask* InterceptBallV7(const TaskT& task);// d
	CPlayerTask* StopRobot(const TaskT& task);
	CPlayerTask* Speed(const TaskT& task); // by zc
	CPlayerTask* OpenSpeed(const TaskT& task);
    CPlayerTask* OpenSpeedCircle(const TaskT& task);
	CPlayerTask* Marking(const TaskT& task);
	CPlayerTask* ZMarking(const TaskT& task);
    CPlayerTask* ZBlocking(const TaskT& task);
    CPlayerTask* NoneTrajGetBall(const TaskT& task);// d
    CPlayerTask* NoneTrajGetBallNew(const TaskT& task);// d
    CPlayerTask* ForceStartRush(const TaskT& task);	// d
    CPlayerTask* ChaseKickV1(const TaskT& task);// d
    CPlayerTask* ChaseKickV2(const TaskT& task);// d
    CPlayerTask* ZChaseKick(const TaskT& task);
    CPlayerTask* TouchKick(const TaskT& task);// d
	CPlayerTask* MarkingTouch(const TaskT& task);
	CPlayerTask* MarkingFront(const TaskT& task);
    CPlayerTask* GoAroundBall(const TaskT& task);// d
	CPlayerTask* PenaltyDefV1(const TaskT& task);
	CPlayerTask* PenaltyDefV2(const TaskT& task);
	CPlayerTask* PenaltyDef2017V1(const TaskT& task);
	CPlayerTask* PenaltyDef2017V2(const TaskT& task);
	
	CPlayerTask* AdvanceBallV1(const TaskT& task);
	CPlayerTask* AdvanceBallV2(const TaskT& task);
    CPlayerTask* Tandem(const TaskT& task);// d
	CPlayerTask* GoAndTurnKick(const TaskT& task);
	CPlayerTask* StaticGetBallNew(const TaskT& task);
	CPlayerTask* GetBallV4(const TaskT& task);
    CPlayerTask* ZGoalie(const TaskT& task);

	CPlayerTask* CircleAndPass(const TaskT& task);
    CPlayerTask* GoAndTurnKickV3(const TaskT& task);// d

    CPlayerTask* GoAndTurn(const TaskT& task);// d
	CPlayerTask* GoAroundRobot(const TaskT& task);
	CPlayerTask* SlowGetBall(const TaskT& task);

	CPlayerTask* timeDelayTest(const TaskT& task);
    CPlayerTask* TestCircleBall(const TaskT& task);// d
	CPlayerTask* CarzyPush(const  TaskT& task);

    CPlayerTask* ShootBall(const TaskT& task);// d
    CPlayerTask* ShootBallV2(const TaskT& task);// d
	CPlayerTask* PassBall(const TaskT& task);
	CPlayerTask* ReceivePass(const TaskT& task);
	CPlayerTask* PenaltyGoalie(const TaskT& task);

	CPlayerTask* PidToPosition(const TaskT& task);
	CPlayerTask* InterceptBall(const TaskT& task);

	CPlayerTask* WaitTouch(const TaskT& task);

	CPlayerTask* PenaltyKick2017V1(const TaskT& task);
	CPlayerTask* PenaltyKick2017V2(const TaskT& task);

    CPlayerTask* DribbleGrab(const TaskT& task);
    CPlayerTask* ZPass(const TaskT& task);
    CPlayerTask* Messi(const TaskT& task);
    CPlayerTask* ZCirclePass(const TaskT& task);
    CPlayerTask* DribbleTurn(const TaskT& task);
    CPlayerTask* PickBlock(const TaskT& task);
	CPlayerTask* DriftKick(const TaskT& task);
	CPlayerTask* DribbleTurnKick(const TaskT& task);
	CPlayerTask* ProtectTurn(const TaskT& task);
    CPlayerTask* InterceptTouch(const TaskT& task);
    CPlayerTask* HoldBall(const TaskT& task);
    CPlayerTask* GoAndTurnKickV4(const TaskT& task);
    CPlayerTask* CmuTurnKickV1(const TaskT &task);
protected:
	template < class CTaskType >
	CPlayerTask* MakeTask( const TaskT& task );
};
typedef NormalSingleton<CTaskFactoryV2> TaskFactoryV2;
/************************************************************************/
/*                 一些包裹(wrap)函数, 方便调用tasks                    */
/************************************************************************/

//! 调用skill的接口
namespace PlayerRole{
	extern CPlayerTask* makeItStop(const int num, const int flags = 0);
    extern CPlayerTask* makeItGoto(const int num, const CGeoPoint& target, const double dir, const int flags = 0, const int sender = 0);
    extern CPlayerTask* makeItGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotvel, const int flags = 0, const int sender = 0);
    extern CPlayerTask* makeItGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotVel, const double& maxAcc, const double& maxRotAcc, const double& maxSpeed = 0, const double& maxRotSpeed = 0, const int flags = 0, const int sender = 0);
    extern CPlayerTask* makeItSimpleGoto(const int num, const CGeoPoint& target, const double dir, const int flags = 0);
    extern CPlayerTask* makeItSimpleGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotvel, const int flags=0);
    extern CPlayerTask* makeItSimpleGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotVel, const double& maxAcc, const double& maxRotAcc, const double& maxSpeed = 0, const double& maxRotSpeed = 0, const int flags = 0);

    extern CPlayerTask* makeItSmartGoto(const int num, const CGeoPoint& target, const double dir, const int flags = 0);
    extern CPlayerTask* makeItSmartGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotvel, const int flags=0);
    extern CPlayerTask* makeItSmartGoto(const int num, const CGeoPoint& target, const double dir, const CVector& vel, const double rotVel, const double& maxAcc, const double& maxRotAcc, const double& maxSpeed = 0, const double& maxRotSpeed = 0, const int flags = 0);

    extern CPlayerTask* makeItInterKickV2(const int num, const double dir, const int flags, const bool isChip = false);
    extern CPlayerTask* makeItInterKickV3(const int num, const double dir, const int flags, const bool kickway = 0);
    extern CPlayerTask* makeItRun(const int num, const double speedX, const double speedY, const double rotSpeed, int flags = 0);
    extern CPlayerTask* makeItOpenRun(const int num, const double speedX, const double speedY, const double rotSpeed, int flags = 0);
    extern CPlayerTask* makeItCrazyPush(const int num, double faceDir);
    extern CPlayerTask* makeItNoneTrajGetBall(const int num,const double dir,CVector finalVel = CVector(0.0,0.0),int flags = 0,double StopDist = -2, CTRL_METHOD mode = CMU_TRAJ);
    extern CPlayerTask* makeItChaseKickV1(const int num, double faceDir, int flags = 0);
	extern CPlayerTask* makeItChaseKickV1(const int num, double faceDir, int flags,bool isChip);//重载 add by gty 17-3-26
    extern CPlayerTask* makeItChaseKickV2(const int num, double faceDir, int flags = 0);
    extern CPlayerTask* makeItZChaseKick(const int num, double faceDir, int flags = 0);
    extern CPlayerTask* makeItProtectBall(const int num,int flags=0);
    extern CPlayerTask* makeItTouchKick(const int num,double kickDir, bool isPass = false, int flags=0);
    extern CPlayerTask* makeItMarkingTouch(const int num,const double kickDir,const CGeoPoint leftUpPos,const CGeoPoint rightDownPos,const int flags);
    extern CPlayerTask* makeItMarkingFront(const int num,const int markNum,const double kickDir,const int flags);
    extern CPlayerTask* makeItAdvanceBallV1(const int num, const int flags = 0);
    extern CPlayerTask* makeItAdvanceBallV2(const int num, const int flags = 0,  const int tendemNum = 0);
    extern CPlayerTask* makeItStaticGetBallNew(const int num, const double dir, CVector finalVel, int flags, double StopDist, CTRL_METHOD mode);
    extern CPlayerTask* makeItGoAndTurnKickV3(const int num ,const double targetdir,int circleNum,const double fixAngle,const double maxAcc,const int radius,const int numPerCir,const double gotoPre,const double gotoDist,const double adjustPre,const double kickprecision = Param::Math::PI*5/180,const int flags = 0);
    extern CPlayerTask* makeItGetBallV4(const int num, const int flag, const CGeoPoint& pos, const CGeoPoint& waitPos, const int power);
    extern CPlayerTask* makeItZGoalie(const int num,const CGeoPoint& pos,const int power,const int flag = 0);
    extern CPlayerTask* makeItSlowGetBall(const int num, const double dir, const int flags = 0);
    extern CPlayerTask* makeItMarkEnemy(const int num,const int priority,const bool front = false,const int flags = 0,const CGeoPoint pos = CGeoPoint(1000,1000),const double dir=999);
	extern CPlayerTask* makeItZMarkEnemy(const int num, const int priority, const bool front, const int flags, const CGeoPoint pos, const double dir);
    extern CPlayerTask* makeItAMarkEnemy(const int num, const int enemyNum, const CGeoPoint pos);
    extern CPlayerTask* makeItReceivePass(const int num, const double dir, const int flags = 0);
    extern CPlayerTask* makeItPenaltyGoalieV2(const int num, const int flags = 0);
    extern CPlayerTask* makeItPenaltyGoalie2017V2(const int num, const int flags = 0);
    extern CPlayerTask* makeItPenaltyKick2017V1(const int num, const int flag = 0);
    extern CPlayerTask* makeItPenaltyKick2017V2(const int num, const int flag = 0);
    extern CPlayerTask* makeItZPass(const int num,const CGeoPoint& target, const double power, const int flag);
    extern CPlayerTask* makeItMessi(const int,const CGeoPoint& target,const double power = 100);
    extern CPlayerTask* makeItZCirclePass(const int num, CGeoPoint target, const double power, const int flag);
    extern CPlayerTask* makeItDribbleTurn(const int num, const double finalDir, const double pre = Param::Math::PI / 90);
    extern CPlayerTask* makeItDribbleTurnKick(const int num, const double finalDir, const double turnRotVel,const double kickPower);
    extern CPlayerTask* makeItInterceptTouch(const int num, const CGeoPoint& waitPos, const double touchDir, const double power, const double buffer, const bool useChip,const bool, const CGeoPoint target);
    extern CPlayerTask* makeItOpenSpeedCircle(const int num,
                                              const double dist2Center,
                                              const int rotateMethod,
                                              const double finalAngle,
                                              const int needDribble = 0,
                                              const double dirDiff = 0.0,
                                              const int openspeedversion = 1);
    extern CPlayerTask* makeItHoldBall(const int num, const CGeoPoint& target);
    extern CPlayerTask* makeItGoAndTurnKickV4(const int num,
                                              const CGeoPoint& pos,
                                              const int flag,
                                              const double power,
                                              const double dir);
    extern CPlayerTask* makeItCmuTurnKickV1(const int num,
                                            const CGeoPoint& pos,
                                            const int flag,
                                            const double power,
                                            const double dir);
}

#endif // _TASK_FACTORY_V2_H_
