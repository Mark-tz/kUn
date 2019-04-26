#include "HoldBall.h"
#include "VisionModule.h"
#include "DribbleStatus.h"
#include "SkillUtils.h"
#include "utils.h"
#include "TaskMediator.h"
#include "skill/Factory.h"
#include "RobotSensor.h"
#include "GDebugEngine.h"

namespace{
    const int verbose = false;
    const double MAX_PROTECT_DIR = 50.0;
    const int SAFETY_RADIUS = 100;
    enum{
        GETBALL = 1,
        HOLDBALL = 2,
    };
    int holdMode = GETBALL;
    int lastMode = GETBALL;
    int fraredOn;
    int fraredOff;
    int maxFrared = 100;
}

CHoldBall::CHoldBall()
{
    _lastCycle = 0;
    _directCommand = NULL;
}

void CHoldBall::plan(const CVisionModule* pVision)
{
    /***************************************************************/
    /* 第一步：视觉初步处理                                           */
    /**************************************************************/
    const MobileVisionT& ball = pVision->Ball();
    const CGeoPoint targetPoint = task().player.pos;//护球的点（圆心）
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const int oppoNum = BestPlayer::Instance()->getTheirBestPlayer();
    const PlayerVisionT& enemy = pVision->TheirPlayer(oppoNum);
    CVector enemy2me = me.Pos() - enemy.Pos();
    CVector me2enemy = enemy.Pos() - me.Pos();
    CVector me2ball = ball.Pos() - me.Pos();
    /***************************************************************/
    /* 第二步：判断方式                                              */
    /***************************************************************/
    // 判断是否正在拿球
    if(fraredOn == maxFrared)fraredOn = 0;
    bool frared = RobotSensor::Instance()->IsInfraredOn(robotNum);
    if(frared || me2ball.mod()<12){
        fraredOn = fraredOn >= maxFrared ? maxFrared : fraredOn + 1;
        fraredOff = 0;
    }
    else{
        fraredOn = 0;
        fraredOff = fraredOff >= maxFrared ? maxFrared: fraredOff + 1;
    }
    bool fraredGetBall = fraredOn > 20;
    if(fraredGetBall)
        holdMode = HOLDBALL;
    else
        holdMode = GETBALL;
    if((frared || me2ball.mod()<10.5) && lastMode==HOLDBALL)
        holdMode = HOLDBALL;
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,-200), std::to_string(holdMode).c_str(), COLOR_GREEN);
    if(pVision->Cycle() - _lastCycle > 6){
        //TODO
    }
    /***************************************************************/
    /* 第三部：决策执行                                               */
    /***************************************************************/
//    holdMode = HOLDBALL;
    if(holdMode == GETBALL){
        if(verbose) cout << "GETBALL!!!" << endl;
        CGeoPoint target;
        double dir;
        if(ball.Valid()) target = ball.Pos() + Utils::Polar2Vector(7, enemy.Dir());
        else target = enemy.Pos() + Utils::Polar2Vector(7, enemy.Dir());
        if(ball.Valid()) dir = me2ball.dir();
        else dir = me2enemy.dir();
        if(me2ball.mod() > 50 || ball.Vel().mod() > 50)
            setSubTask(PlayerRole::makeItGetBallV4(robotNum, PlayerStatus::DRIBBLE, target, CGeoPoint(999, 999), 0));
        else
            setSubTask(PlayerRole::makeItGoto(robotNum, target, dir));
    }
    if(holdMode == HOLDBALL){
        // 计算敌方最佳车到球的距离
        CGeoPoint enemyTarget = me.Pos() + Utils::Polar2Vector(2*Param::Vehicle::V2::PLAYER_SIZE, me.Dir());
        CVector target2me = me.Pos() - enemyTarget;
        CVector me2target = enemyTarget - me.Pos();
        CVector ball2me = me.Pos() - ball.Pos();
        CVector target2enemy = enemy.Pos() - enemyTarget;
        GDebugEngine::Instance()->gui_debug_x(enemyTarget);
        CVector enemy2Target = enemyTarget - enemy.Pos();
        double enemy2TargetDir = enemy2Target.dir();
        CGeoLine enemy2TargetLine(enemy.Pos(), enemy2TargetDir);
        CGeoPoint lineProjection = enemy2TargetLine.projection(me.Pos());
        CVector me2Line = me.Pos() - lineProjection;

        // 计算敌方最佳车到球的最短距离
        double enemy2TargetDis;
        // 计算直线距离
        double enemy2meDis = enemy2me.mod();
        if(enemy2meDis > 2*Param::Vehicle::V2::PLAYER_SIZE){
            double enemy2tanPointDis = sqrt(enemy2me.mod2() - pow(2*Param::Vehicle::V2::PLAYER_SIZE, 2));
            if(enemy2tanPointDis < enemy2Target.mod()){
                // 计算圆弧长度
                // 计算切点
                double enemy2meDir = enemy2me.dir();
                double angle = std::atan2(2*Param::Vehicle::V2::PLAYER_SIZE, enemy2tanPointDis);
                CGeoPoint tanPoint1 = enemy.Pos() + Utils::Polar2Vector(enemy2tanPointDis, enemy2meDir + angle);
                CGeoPoint tanPoint2 = enemy.Pos() + Utils::Polar2Vector(enemy2tanPointDis, enemy2meDir - angle);
                CVector me2tanPoint1 = tanPoint1 - me.Pos();
                CVector me2tanPoint2 = tanPoint2 - me.Pos();
                double theta1 = abs(me2tanPoint1.dir() - me.Dir()) < Param::Math::PI ? abs(me2tanPoint1.dir() - me.Dir()) : 2*Param::Math::PI - abs(me2tanPoint1.dir() - me.Dir());
                double theta2 = abs(me2tanPoint2.dir() - me.Dir()) < Param::Math::PI ? abs(me2tanPoint2.dir() - me.Dir()) : 2*Param::Math::PI - abs(me2tanPoint2.dir() - me.Dir());
                double arcDis = 2*Param::Vehicle::V2::PLAYER_SIZE*theta1 < 2*Param::Vehicle::V2::PLAYER_SIZE*theta2 ? 2*Param::Vehicle::V2::PLAYER_SIZE*theta1 : 2*Param::Vehicle::V2::PLAYER_SIZE*theta2;
                enemy2TargetDis = enemy2tanPointDis + arcDis;
//                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500,100), "1", COLOR_GREEN);
            }
            else{
                // 计算直线距离
//                GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(500,100), "2", COLOR_GREEN);
                enemy2TargetDis = enemy2Target.mod();
            }
        }
        else{
            CVector me2enemy = enemy.Pos() - me.Pos();
            CVector me2target = enemyTarget - me.Pos();
            double angle = abs(me2target.dir() - me2enemy.dir()) < Param::Math::PI ? abs(me2target.dir() - me2enemy.dir()) : 2*Param::Math::PI - abs(me2target.dir() - me2enemy.dir());
            enemy2TargetDis = angle * 2*Param::Vehicle::V2::PLAYER_SIZE;
        }
        // GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100,100), std::to_string(int(enemy2TargetDis)).c_str(), COLOR_GREEN);
        if(me2ball.mod() < 30){
        DribbleStatus::Instance()->setDribbleCommand(robotNum, 3);
        }

//        double rotVel = 0;
//        rotVel = abs(target2me.dir() - target2enemy.dir()) < Param::Math::PI ? abs(target2me.dir() - target2enemy.dir()) : 2*Param::Math::PI - abs(target2me.dir() - target2enemy.dir());
//        double diffAngle = me2enemy.dir() - me2target.dir() > 0 ? me2enemy.dir() - me2target.dir() : me2enemy.dir() - me2target.dir() + 2*Param::Math::PI;
//        if(diffAngle <= Param::Math::PI)rotVel *= -5;
//        else rotVel *= 5;
//        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,100), std::to_string(diffAngle).c_str(), COLOR_GREEN);

        // 计算多人包夹时的角度
        double finalAngle = 0;
        double coeff = 0;
        int enemyNum = pVision->getTheirValidNum();
        for(int i=1; i<=enemyNum; i++){
            const PlayerVisionT c_enemy = pVision->TheirPlayer(i);
            CVector c_enemy2me = me.Pos() - c_enemy.Pos();
            double targetAngle = c_enemy2me.dir() > 0 ? 2*Param::Math::PI - c_enemy2me.dir() : -1*c_enemy2me.dir();
            finalAngle += targetAngle/c_enemy2me.mod();
            coeff += 1/c_enemy2me.mod();
        }
        finalAngle /= coeff;
        // 计算最佳距离
        double anotherAngle = finalAngle < Param::Math::PI ? finalAngle+Param::Math::PI : finalAngle - Param::Math::PI;
        double diff1 = 0, diff2 = 0;
        for(int i=0; i<=enemyNum;i++){
            const PlayerVisionT c_enemy = pVision->TheirPlayer(i);
            CVector c_enemy2me = me.Pos() - c_enemy.Pos();
            double targetAngle = c_enemy2me.dir() > 0 ? 2*Param::Math::PI - c_enemy2me.dir() : -1*c_enemy2me.dir();
            double d_angle1 = abs(targetAngle-finalAngle) < Param::Math::PI ? abs(targetAngle-finalAngle) : 2*Param::Math::PI - abs(targetAngle-finalAngle);
            diff1 += d_angle1/c_enemy2me.mod();
            double d_angle2 = abs(targetAngle-anotherAngle) < Param::Math::PI ? abs(targetAngle-anotherAngle) : 2*Param::Math::PI - abs(targetAngle-anotherAngle);
            diff2 += d_angle2/c_enemy2me.mod();
        }
        if(diff1>diff2)finalAngle = anotherAngle;
        double c_angle = me2target.dir() > 0 ? 2*Param::Math::PI - me2target.dir() : -1*me2target.dir(); // current angle
        double diffAngle = c_angle - finalAngle > 0 ? c_angle - finalAngle : c_angle - finalAngle + 2*Param::Math::PI;
        double rotVel = diffAngle < Param::Math::PI ? diffAngle : 2*Param::Math::PI - diffAngle;
        if(diffAngle < Param::Math::PI)
            rotVel *= 3;
        else
            rotVel *= -3;
//        double targetAngle = enemy2me.dir() > 0 ? 2*Param::Math::PI - enemy2me.dir() : -1*enemy2me.dir();
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,100), std::to_string(finalAngle).c_str(), COLOR_GREEN);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(150,100), std::to_string(me.Dir()).c_str(), COLOR_GREEN);
        setSubTask(PlayerRole::makeItRun(robotNum, 0, 0, rotVel));
    }

    lastMode = holdMode;
    return CStatedTask::plan(pVision);
}

CPlayerCommand* CHoldBall::execute(const CVisionModule* pVision)
{
    if(subTask()){
        return subTask()->execute(pVision);
    }
    else
        return nullptr;
}
