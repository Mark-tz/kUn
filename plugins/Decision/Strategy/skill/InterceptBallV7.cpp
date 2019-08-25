#include "InterceptBallV7.h"
#include "skill/Factory.h"
#include <CMmotion.h>
#include <iostream>
#include "KickStatus.h"
#include "DribbleStatus.h"
#include <RobotSensor.h>
#include "SkillUtils.h"
#include "TaskMediator.h"

namespace {
	const double newVehicleBuffer = 0.6;
	const double StopDist = 1;
	const double directGetBallDist = 35;
	const double directGetBallDirLimit = Param::Math::PI / 4;
    const bool verbose = false;
}
CInterceptBallV7::CInterceptBallV7() :waitPoint(0, 0)
{
}

CInterceptBallV7::~CInterceptBallV7()
{
}

void CInterceptBallV7::plan(const CVisionModule * pVision)
{
	const MobileVisionT& ball = pVision->Ball();
	const int robotNum = task().executor;
	const double finalAngel = task().player.angle;//角度
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);
	const int ifshoot = task().player.flag;//是否射门
	double kickpower = task().player.kickpower;//射门力度
	const bool ifChip = task().player.ischipkick;//true 代表chip， flase代表flat

	CGeoLine ballLine(ball.RawPos(), ball.Vel().dir());//球线
	TaskT chase_kick_task(task());
	//double ballArriveTime = 0;
	double meArriveTime = 9999;
	CGeoPoint testPoint(ball.RawPos().x(), ball.RawPos().y());
	CVector me2Ball = ball.RawPos() - me.RawPos();
	CVector ball2Me = me.RawPos() - ball.RawPos();
	CGeoPoint ballLineProjection = ballLine.projection(me.RawPos());
	CVector ball2Projection = ballLineProjection - ball.RawPos();
	CVector projection2Me = me.RawPos() - ballLineProjection;
    double isSensored = RobotSensor::Instance()->IsInfraredOn(robotNum);	//是否有检测到红外

	//距车40cm，发送吸球指令
	if (me2Ball.mod()<60) {//球在车前方
		DribbleStatus::Instance()->setDribbleCommand(robotNum, 3);
	}
	//红外触发 且方向正确，则直接射门
    if (ifshoot == 1 && isSensored && abs(me.Dir() - finalAngel) < 10 * Param::Math::PI / 180) {
        if (verbose) cout << "My Angle:" << abs(me.Dir() - finalAngel) << endl;
		if (ifChip) KickStatus::Instance()->setChipKick(robotNum, kickpower);
		else KickStatus::Instance()->setKick(robotNum, kickpower);
	}

	//已经贴球，且朝向球，则踢球或改变踢球方向
	if (me2Ball.mod() < 16 && abs(Utils::Normalize(me.Dir() - me2Ball.dir())) < Param::Math::PI / 4) {
		/*
		if (ifshoot == 1 && abs(me.Dir() - finalAngel) < 7 * Param::Math::PI / 180) {
			if(ifChip) KickStatus::Instance()->setChipKick(robotNum, kickpower);
			else KickStatus::Instance()->setKick(robotNum, kickpower);
		}Utils::Polar2Vector(-40, Utils::Normalize(finalAngel))
		*/
		//如果车角度正确，低速往前冲
		if (ifshoot == 1 && abs(me.Dir() - finalAngel) < 3 * Param::Math::PI / 180) {
			chase_kick_task.player.pos = ball.RawPos() + Utils::Polar2Vector(-5, Utils::Normalize(finalAngel));
			//速度是否需要设置更低
			//setSubTask(TaskFactoryV2::Instance()->GotoPosition(chase_kick_task));
            setSubTask(PlayerRole::makeItGoto(robotNum, chase_kick_task.player.pos, chase_kick_task.player.angle));
            if (verbose) cout << "go to ball" << endl;
		}
		//如果车角度不对，需要转向
		else {
			int  CLOCKWISE = -1;	//-1 顺时针
			if (Utils::Normalize(me.Dir()) < Utils::Normalize(finalAngel) && Utils::Normalize(me.Dir()) + Param::Math::PI > Utils::Normalize(finalAngel))
				CLOCKWISE = 1;
			double newdir = me.Dir() + CLOCKWISE * Param::Math::PI / 18;//转10度
			chase_kick_task.player.pos = CGeoPoint(ball.RawPos().x() - me2Ball.mod()*std::cos(newdir), ball.RawPos().y() - me2Ball.mod()*std::sin(newdir));
			double omega;
			//与射出角度相差小于30度
			//if (abs(me.Dir() - finalAngel) < Param::Math::PI / 6 && me2Ball.mod() > 18) {
			if (abs(me.Dir() - finalAngel) < Param::Math::PI / 6) {//角度差比较小的时候减速
				omega = Param::Math::PI / 2;//降低角速度
                chase_kick_task.player.speed_x = 20;//推着球转
                if (verbose) cout << "slow turn" << endl;
			}
			else {
				omega = Param::Math::PI*1.5;//角度较大，加快转向
                chase_kick_task.player.speed_x = 30;
                if (verbose) cout << "fast turn" << endl;
			}
			chase_kick_task.player.speed_y = -CLOCKWISE*omega*me2Ball.mod();//车的y坐标
			chase_kick_task.player.rotate_speed = CLOCKWISE*omega;
			setSubTask(TaskFactoryV2::Instance()->OpenSpeed(chase_kick_task));
		}
	}
	//距离球较远，但球速较慢，近似静止
	else if (abs(ball.Vel().mod()) < 40) {
		bool canGetBall = false;
		bool needAvoidBall;
		const double me2BallDirDiff = Utils::Normalize(me2Ball.dir() - finalAngel);
		bool isInDirectGetBallCircle = me.Pos().dist(ball.RawPos()) < directGetBallDist;    //是否在直接冲上去拿球距离之内
		bool isGetBallDirReached = fabs(me2BallDirDiff) < directGetBallDirLimit;
		canGetBall = isInDirectGetBallCircle && isGetBallDirReached;     //重要布尔量:是否能直接上前拿球

		if (!canGetBall && me2Ball.mod() < 30) needAvoidBall = true;
		else needAvoidBall = false;
		//cout << "canGetBall?"<< canGetBall<<"\nneedAvoidBall?"<< needAvoidBall << endl;
		static int staticDir;
		staticDir = getStaticDir(pVision, staticDir);

		if (needAvoidBall) {
			if (fabs(me2BallDirDiff) > Param::Math::PI / 3) {
				double avoidDir = Utils::Normalize(ball2Me.dir() + staticDir * Param::Math::PI / 4);
				chase_kick_task.player.pos = ball.Pos() + Utils::Polar2Vector(30, avoidDir);
			}
			else {
				double directDist = Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer + Param::Field::BALL_SIZE + StopDist - 2.5;
				chase_kick_task.player.pos = ball.Pos() + Utils::Polar2Vector(directDist, Utils::Normalize(finalAngel - Param::Math::PI));
				if (fabs(me2BallDirDiff) < 0.2)
					chase_kick_task.player.pos = ball.Pos() + Utils::Polar2Vector(directDist, Utils::Normalize(finalAngel - Param::Math::PI));
			}
		}
		else {
			if (fabs(me2BallDirDiff) > Param::Math::PI / 2) {
				double gotoDir = Utils::Normalize(finalAngel + staticDir * Param::Math::PI * 3 / 5);
				chase_kick_task.player.pos = ball.Pos() + Utils::Polar2Vector(40, gotoDir);
				chase_kick_task.player.vel = Utils::Polar2Vector(100, (chase_kick_task.player.pos - me.Pos()).dir());
			}
			else {
				double directDist = Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + newVehicleBuffer + Param::Field::BALL_SIZE + StopDist - 2.5;
				chase_kick_task.player.pos = ball.Pos() + Utils::Polar2Vector(directDist, Utils::Normalize(finalAngel - Param::Math::PI));
			}
			//}
            //setSubTask(TaskFactoryV2::Instance()->GotoPosition(chase_kick_task));
            if (verbose) cout << "static get ball" << endl;
		}
		//setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(chase_kick_task));
		setSubTask(PlayerRole::makeItGoto(robotNum, chase_kick_task.player.pos, chase_kick_task.player.angle));
	}
	//车到球线很近，车离球不远，车在球前，则车到截球线上等着
	else if (me.RawPos().dist(ballLineProjection) < 15 && me2Ball.mod()<60 &&
		abs(Utils::Normalize(ball2Projection.dir() - ball.Vel().dir()))<0.1) {
		if (abs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) > Param::Math::PI / 3 * 2)//夹角小于60度直接去截球线
			chase_kick_task.player.pos = ballLineProjection;
		else
			chase_kick_task.player.pos = ballLineProjection + ball.Vel() * 2.5;//往前补偿
		chase_kick_task.player.angle = me2Ball.dir();//车朝球
		//setSubTask(TaskFactoryV2::Instance()->GotoPosition(chase_kick_task));
        setSubTask(PlayerRole::makeItGoto(robotNum, chase_kick_task.player.pos, chase_kick_task.player.angle));
        if (verbose) cout << "touch ball" << endl;
	}
	//普通情况，计算接球点
	else {
        ZSkillUtils::instance()->predictedInterTime(pVision, robotNum, testPoint, meArriveTime, 0.2);//0.2秒反应时间
		CVector testpoint2Ball = ball.RawPos() - testPoint;
		chase_kick_task.player.angle = testpoint2Ball.dir();//面向球截球

		if (abs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) < Param::Math::PI / 2 && me2Ball.mod() <= 40)//追在球屁股后面，且可能撞上球
			chase_kick_task.player.pos = testPoint + (projection2Me / projection2Me.mod() * 40);//跑到球的侧面
		else
			chase_kick_task.player.pos = testPoint;
        setSubTask(PlayerRole::makeItGoto(robotNum, chase_kick_task.player.pos, chase_kick_task.player.angle));
        if (verbose) cout << "normal" << endl;
	}
	CStatedTask::plan(pVision);
	return;
}


CPlayerCommand* CInterceptBallV7::execute(const CVisionModule* pVision)
{
	if (subTask()) {
		return subTask()->execute(pVision);
	}
	return NULL;
}

int CInterceptBallV7::getStaticDir(const CVisionModule * pVision, int staticDir)
{
	const MobileVisionT& ball = pVision->Ball();
	const int robotNum = task().executor;
	const PlayerVisionT& me = pVision->OurPlayer(robotNum);

	double ball2MeDir = (me.Pos() - ball.Pos()).dir();
	double finalDir = task().player.angle;
	double tmp2FinalDirDiff = Utils::Normalize(ball2MeDir - finalDir);

	if (!staticDir) staticDir = tmp2FinalDirDiff > 0 ? 1 : -1;
	else {
		if (staticDir == 1) {
			if (tmp2FinalDirDiff < -0.5) staticDir = -1;
		}
		else if (tmp2FinalDirDiff > 0.5) staticDir = 1;
	}

	return staticDir;
}
