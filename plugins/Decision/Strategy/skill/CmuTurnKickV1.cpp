#include "CmuTurnKickV1.h"
#include "skill/Factory.h"
#include <CMmotion.h>
#include <iostream>
#include "KickStatus.h"
#include "DribbleStatus.h"
#include <RobotSensor.h>
#include "SkillUtils.h"
#include "TaskMediator.h"
#include "Compensate.h"

namespace {
enum{
    GOINTERPOS = 1,
    WAITBALL = 2,
    KICK = 3,
    TURN = 4,
    GETBALL = 5
};
    const bool verbose = false;
    int turnway = 2;
    const double newVehicleBuffer = 0.6;
    const double StopDist = 1;
    const double directGetBallDist = 35;
    const double directGetBallDirLimit = Param::Math::PI / 4;
    const double SHOOT_ACCURATE  = 3;   // degree
    const double TURN_COMPENSATE = 0;   // radius
    const double TURN_RADIUS     = 30;  // radius
    const double TURN_MODE_THRESHOLD = 20;  // threshold for turn mode
    const int    maxFrared = 5;
    const double buffer = 2;
    const double kAngleBias = 15;
}
CCmuTurnKickV1::CCmuTurnKickV1()
{
}

CCmuTurnKickV1::~CCmuTurnKickV1()
{
}

void CCmuTurnKickV1::plan(const CVisionModule * pVision)
{

    const int robotNum = task().executor;
    const CGeoPoint target = task().player.pos;
    const int flag = task().player.flag;//是否射门
    const double kickpower = task().player.kickpower;//射门力度
    const double angle = task().player.angle;

    needkick = flag & PlayerStatus::KICK;//是否需要射出球
    chip = flag & PlayerStatus::CHIP;//是否挑射

    const MobileVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);

    TaskT chase_kick_task(task());
    //double ballArriveTime = 0;
    CGeoLine ballLine(ball.RawPos(), ball.Vel().dir());//球线
    CGeoPoint testPoint(ball.RawPos().x(), ball.RawPos().y());
    CGeoPoint ballLineProjection = ballLine.projection(me.RawPos());
    CVector me2Ball = ball.RawPos() - me.RawPos();
    CVector ball2Me = me.RawPos() - ball.RawPos();
    CVector ball2Projection = ballLineProjection - ball.RawPos();
    CVector projection2Me = me.RawPos() - ballLineProjection;
    CVector me2target = target - me.Pos();

    double meArriveTime = 9999;
//    bool isSensored = RobotSensor::Instance()->IsInfoValid(robotNum) &&
//            RobotSensor::Instance()->IsInfraredOn(robotNum);	//是否有检测到红外

//    cout << "[CmuTurnKickV1.cpp] id: " << robotNum << endl;
//    cout << "[CmuTurnKickV1.cpp] " << robotNum << " isSensored:" << isSensored
//         << ", IsInfraredOn " << RobotSensor::Instance()->IsInfraredOn(robotNum + 1 ) << endl;

    double final_angle = angle;
    if ( angle >= 999 ){
        //不射门的情况下角度，但是没有算射门角
        if (!Utils::InTheirPenaltyArea(target, 0)){
            final_angle = Compensate::Instance()->getKickDir(robotNum,target);
            chase_kick_task.player.angle = final_angle;
        }
        else {
            if (needkick){
                KickDirection::Instance()->
                        GenerateShootDir(robotNum, me.Pos());
                final_angle = KickDirection::Instance()->getRealKickDir();
                chase_kick_task.player.angle = final_angle;
            }
            else
                chase_kick_task.player.angle = me2Ball.dir();//只截球，不射
        }
    }
    //距车40cm，发送吸球指令
    if (me2Ball.mod()<60) {//球在车前方
        DribbleStatus::Instance()->setDribbleCommand(robotNum, 3);
    }

//    cout << "[CmuTurnKickV1.cpp] " << isSensored << endl;
    //红外触发 且方向正确，则直接射门
    if (needkick  && me2Ball.mod() < Param::Vehicle::V2::PLAYER_SIZE + buffer){
//        GDebugEngine::Instance()->gui_debug_msg( me.Pos() + Utils::Polar2Vector(10, Param::Math::PI / 4),
//                                                 std::to_string(abs(final_angle - me.Dir()) / Param::Math::PI * 180).c_str() );
//        std::cout << "[CmuTurnKickV1.cpp] " << abs(final_angle - me.Dir()) / Param::Math::PI * 180 << std::endl;
        if ( fabs(Utils::Normalize(final_angle - me.Dir()) ) <
             SHOOT_ACCURATE * Param::Math::PI / 180 ) {
            _new_status = KICK;
        }
        else {
            _new_status = TURN;
//            GDebugEngine::Instance()->gui_debug_line( me.Pos(),
//                                                      me.Pos() + Utils::Polar2Vector(1000, me.Dir()) );
            DribbleStatus::Instance()->setDribbleCommand(robotNum, 0);
        }
    }
    else if (abs(ball.Vel().mod()) < 40){
        _new_status = GETBALL;
    }
    else if (me.RawPos().dist(ballLineProjection) < 15 && me2Ball.mod()<60 &&
             fabs(Utils::Normalize(ball2Projection.dir() - ball.Vel().dir()))
             <0.1){
        _new_status = WAITBALL;
    }
    else {
        _new_status = GOINTERPOS;
    }
//    GDebugEngine::Instance()->gui_debug_line( me.Pos(),
//                                              me.Pos() + Utils::Polar2Vector(100, me.Dir()),
//                                              COLOR_RED);
//    GDebugEngine::Instance()->gui_debug_line( me.Pos(),
//                                              me.Pos() + Utils::Polar2Vector(100, final_angle),
//                                              COLOR_GREEN);
//    GDebugEngine::Instance()->gui_debug_msg( me.Pos() + Utils::Polar2Vector(10, Param::Math::PI / 4),
//                                             std::to_string(_new_status).c_str());
//    _new_status = TURN;
    switch (_new_status) {
        case KICK:{
        if (verbose)
            cout << "My Angle:" << abs(me.Dir() - final_angle) << endl;
        if (chip) KickStatus::Instance()->setChipKick(robotNum, kickpower);
        else KickStatus::Instance()->setKick(robotNum, kickpower);
        break;
        }
        case WAITBALL:{
        if (fabs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) >
                Param::Math::PI / 3 * 2)//夹角小于60度直接去截球线
            chase_kick_task.player.pos = ballLineProjection;
        else
            chase_kick_task.player.pos = ballLineProjection +
                    ball.Vel() * 2.5;//往前补偿
        chase_kick_task.player.angle = me2Ball.dir();//车朝球
        if (Utils::InTheirPenaltyArea(chase_kick_task.player.pos,0))
            chase_kick_task.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
        setSubTask(PlayerRole::makeItGoto(robotNum,
                                          chase_kick_task.player.pos,
                                          chase_kick_task.player.angle));
        if (verbose) cout << "touch ball" << endl;
        break;
        }
        case GOINTERPOS:{
        ZSkillUtils::instance()->predictedInterTime(pVision, robotNum,
                                                    testPoint, meArriveTime,
                                                    0.2);//0.2秒反应时间
        CVector ball2me = ball.RawPos() - me.Pos();
        chase_kick_task.player.angle = ball2me.dir();//面向球截球

        //追在球屁股后面，且可能撞上球
        if (fabs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) <
                Param::Math::PI / 2 && me2Ball.mod() <= 40)
            chase_kick_task.player.pos = testPoint +
                    (projection2Me / projection2Me.mod() * 40);//跑到球的侧面
        else
            chase_kick_task.player.pos = testPoint;
        if (Utils::InTheirPenaltyArea(chase_kick_task.player.pos,0))
            chase_kick_task.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
        setSubTask(PlayerRole::makeItGoto(robotNum,
                                          chase_kick_task.player.pos,
                                          chase_kick_task.player.angle));
        if (verbose) cout << "normal" << endl;
        break;
        }
        case TURN:{
        if ( fabs(Utils::Normalize(final_angle - me.Dir())) / Param::Math::PI * 180 >
             TURN_MODE_THRESHOLD ){
            if ( Utils::Normalize( final_angle - me.Dir() ) > 0 ){
                turnway = 2;
                final_angle = final_angle + TURN_COMPENSATE;
            }
            else {
                turnway = 1;
                final_angle = final_angle - TURN_COMPENSATE;
            }
            setSubTask(PlayerRole::makeItOpenSpeedCircle(robotNum, TURN_RADIUS,
                                                         turnway, final_angle,
                                                         1,
                                                         kAngleBias / 180 * Param::Math::PI, 2));
        }
        else {
            setSubTask(PlayerRole::makeItGoAndTurnKickV4(robotNum,
                                                         Utils::MakeOutOfTheirPenaltyArea(target,0),
                                                         flag,
                                                         kickpower,
                                                         angle));
        }
        break;
        }
        case GETBALL:{
        bool canGetBall = false;
        bool needAvoidBall;
        const double me2BallDirDiff =
                Utils::Normalize(me2Ball.dir() - me2target.dir());
        //是否在直接冲上去拿球距离之内
        bool isInDirectGetBallCircle =
                me.Pos().dist(ball.RawPos()) < directGetBallDist;
        bool isGetBallDirReached =
                fabs(me2BallDirDiff) < directGetBallDirLimit;
        //重要布尔量:是否能直接上前拿球
        canGetBall = isInDirectGetBallCircle && isGetBallDirReached;

        if (!canGetBall && me2Ball.mod() < 30) needAvoidBall = true;
        else needAvoidBall = false;
        static int staticDir;
        staticDir = getStaticDir(pVision, staticDir);

        if (needAvoidBall) {
            if (fabs(me2BallDirDiff) > Param::Math::PI / 3) {
                double avoidDir =
                        Utils::Normalize(ball2Me.dir() +
                                         staticDir * Param::Math::PI / 4);
                chase_kick_task.player.pos =
                        ball.Pos() + Utils::Polar2Vector(30, avoidDir);
            }
            else {
                double directDist =
                        Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER +
                        newVehicleBuffer + Param::Field::BALL_SIZE +
                        StopDist - 2.5;
                chase_kick_task.player.pos =
                        ball.Pos() +
                        Utils::Polar2Vector(directDist,
                                            Utils::Normalize(final_angle -
                                                         Param::Math::PI));
                if (fabs(me2BallDirDiff) < 0.2)
                    chase_kick_task.player.pos =
                         ball.Pos() +
                         Utils::Polar2Vector(directDist,
                            Utils::Normalize(final_angle -
                                             Param::Math::PI));
            }
        }
        else {
            if (fabs(me2BallDirDiff) > Param::Math::PI / 2) {
                double gotoDir =
                        Utils::Normalize(me2target.dir() +
                                         staticDir * Param::Math::PI*3/5);
                chase_kick_task.player.pos =
                        ball.Pos() + Utils::Polar2Vector(40, gotoDir);
            }
            else {
                double directDist =
                        Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER - 2.5;
                chase_kick_task.player.pos = ball.Pos() +
                        Utils::Polar2Vector(directDist,
                                        Utils::Normalize(me2target.dir() -
                                                         Param::Math::PI));
            }
            if (verbose) cout << "GETBALL" << endl;
        }
        chase_kick_task.player.angle = me2Ball.dir();
        if (Utils::InTheirPenaltyArea(chase_kick_task.player.pos,0))
            chase_kick_task.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
        setSubTask(PlayerRole::makeItGoto(robotNum,
                                          chase_kick_task.player.pos,
                                          chase_kick_task.player.angle));
        break;
    }
    }
    CStatedTask::plan(pVision);
    return;
}


CPlayerCommand* CCmuTurnKickV1::execute(const CVisionModule* pVision)
{
    if (subTask()) {
        return subTask()->execute(pVision);
    }
    return nullptr;
}

int CCmuTurnKickV1::getStaticDir(const CVisionModule * pVision, int staticDir)
{
    const MobileVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const CGeoPoint target = task().player.pos;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CVector me2Target = target - me.Pos();
    double ball2MeDir = (me.Pos() - ball.Pos()).dir();
    double finalDir = me2Target.dir();
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
