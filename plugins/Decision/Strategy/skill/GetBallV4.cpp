#include "GetBallV4.h"
#include "GDebugEngine.h"
#include <VisionModule.h>
#include "skill/Factory.h"
#include <utils.h>
#include <DribbleStatus.h>
#include "BallSpeedModel.h"
#include <RobotSensor.h>
#include <KickStatus.h>
#include "KickDirection.h"
#include "PlayInterface.h"
#include "TaskMediator.h"
#include "CMmotion.h"
#include "SkillUtils.h"
#include "WaitKickPos.h"
#include "Compensate.h"

namespace {

double SHOOT_ACCURACY = 5 * Param::Math::PI / 180;
double SIMULATION_SHOOT_ACCURACY = 3 * Param::Math::PI / 180;
const double NORMAL_CHASE_DIR = 45.0;//根据球踢出后偏移的角度判断是否要chase
const double NORMAL_TOUCH_DIR = 110.0;//根据球踢出后偏移的角度判断是否要touch

const double newVehicleBuffer = 0.6;               // 小嘴巴机器人PLAYER_CENTER_TO_BALL_CENTER补偿
const double nearBallRadius = 20;                  // 小车半径+球半径+2~3视频误差裕度,判定是否需要AVOIDBALL的半径
const double ball2myheadLimit = 3.5;               // 小嘴巴车嘴长7cm，球半径2cm，想要稳定拿住球需要(7-2)/2=2.5cm 再加1.0的余值
const double directGetBallDist = 35;               // 直接冲上去拿球的距离
const double transverseBallSpeed = 20;             // 对拿球产生影响的最低横向球速 ori：30
const double directGetBallDirLimit = Param::Math::PI / 6;
const double getBallDist = 100;
const double touchDist = 100;					   //在touchDist内能截球则Touch
const double MIN_BALL_MOVING_VEL = 50;      // 球速小于这个值就算不在滚
bool needAvoidBall;
bool canGetBall;
bool canForwardShoot;
int fraredOn;
int fraredOff;
int FRICTION;

const int CHASEBALL = 0;
const int INTERBALL = 1;
const int STATICBALL = 2;
const int TOUCH = 3;
const int INTERTOUCH = 4;
const int RUSH = 5;

int MAX_CNT_FOR_TURN = 6;
double RESPONSE_TIME = 0.3;
int testMinFrame = 5;//最少帧数
const int maxFrared = 100;
int staticDir;
const double STICK_DIST = 50;
int stickTime = 0;

bool IF_DEBUG = false;
}

CGetBallV4::CGetBallV4() {
    ZSS::ZParamManager::instance()->loadParam(FRICTION, "AlertParam/Friction", 40);

    _lastCycle = 0;
    canForwardShoot = false;
    getBallMode = STATICBALL;
}

void CGetBallV4::plan(const CVisionModule* pVision) {
    if (pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1) {
        setState(BEGINNING);
        needAvoidBall = false;
        canGetBall = false;
    }

    /******************视觉初步处理****************************/
    const MobileVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const double StopDist = 0;//task().player.rotvel;
    //double isSensored = RobotSensor::Instance()->IsInfoValid(robotNum) && RobotSensor::Instance()->IsInfraredOn(robotNum);	//是否有检测到红外

    int power = task().player.rotdir;
    //const CGeoPoint myHead = me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER + newVehicleBuffer + StopDist, me.Dir());
    const CVector me2Ball = ball.RawPos() - me.Pos();
    const CVector ball2Me = me.Pos() - ball.RawPos();
    //const CVector head2Ball = ball.Pos() - myHead;
    CGeoLine ballLine(ball.RawPos(), ball.Vel().dir());
    ballLineProjection = ballLine.projection(me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER, me.Dir()));
    CVector me2line = me.Pos() - ballLineProjection;
    CVector ball2Projection = ballLineProjection - ball.RawPos();
    targetPoint = task().player.pos;//目标点
    waitPoint = CGeoPoint(task().player.kickpower, task().player.chipkickpower);//等待截球点

    /*****************拿球Task初始化***************/
    TaskT getballTask(task());
    //默认的射门角度，加了补偿和算射门角
    if (needkick) {
        KickDirection::Instance()->GenerateShootDir(robotNum, me.Pos());
        getballTask.player.angle = KickDirection::Instance()->getRealKickDir();
    } else getballTask.player.angle = me2Ball.dir(); //只截球，不射
    //不射门的情况下角度，但是没有算射门角
    if (!Utils::InTheirPenaltyArea(targetPoint, 0)) {
        getballTask.player.angle = Compensate::Instance()->getKickDir(robotNum, targetPoint);
    }

    double finalDir = getballTask.player.angle;
    const double me2BallDirDiff = Utils::Normalize(me2Ball.dir() - finalDir);

    const int flag = task().player.flag;
    needkick = flag & PlayerStatus::KICK;//是否需要射出球
    chip = flag & PlayerStatus::CHIP;//是否挑射
    needdribble = flag & PlayerStatus::DRIBBLE;
    safeMode = flag & PlayerStatus::SAFE;

    if (ZSkillUtils::instance()->IsInField(waitPoint)) {//若下发了wait的点，则尽量用touch
        isTouch = true;
    }

    // 球在车正前方对球预测时间的影响，考虑红外
    bool frared = RobotSensor::Instance()->IsInfraredOn(robotNum);
    //带有小缓存功能的红外
    if (frared) {
        fraredOn = fraredOn >= maxFrared ? maxFrared : fraredOn + 1;
        fraredOff = 0;
    } else {
        fraredOn = 0;
        fraredOff = fraredOff >= maxFrared ? maxFrared : fraredOff + 1;
    }

    bool ballStick = me2Ball.mod() < STICK_DIST;
    if (ballStick) stickTime = stickTime >= 9999 ? 9999 : stickTime + 1;
    else stickTime = 0;

    /********* 判断方式 **********/
    judgeMode(pVision);

    bool isInDirectGetBallCircle = me.Pos().dist(ball.RawPos()) < directGetBallDist && me.Pos().dist(ball.RawPos()) > Param::Vehicle::V2::PLAYER_SIZE + 5;    //是否在直接冲上去拿球距离之内
    bool isGetBallDirReached = fabs(me2BallDirDiff) < directGetBallDirLimit;
    canGetBall = isInDirectGetBallCircle && isGetBallDirReached;     //重要布尔量:是否能直接上前拿球
    bool fraredGetball = fraredOn > 5;

    if (!canGetBall && me2Ball.mod() < 25 && !fraredGetball) needAvoidBall = true;
    else needAvoidBall = false;
    staticDir = getStaticDir(pVision, staticDir);

    if(me2Ball.mod() < 100 && me.Vel().mod() < 150) getballTask.player.flag |= PlayerStatus::NOT_AVOID_THEIR_VEHICLE;

    /*****************决策执行********************/

    /*************** Touch **************/
    if (getBallMode == TOUCH) {
        CGeoLine ballVelLine(ball.RawPos(), ball.Vel().dir());//球线
        double perpendicularDir = Utils::Normalize(ball.Vel().dir() + Param::Math::PI / 2);//垂直球线的方向
        CGeoLine perpLineAcrossMyPos(waitPoint, perpendicularDir);//过截球点的垂线
        CGeoPoint projectionPos = CGeoLineLineIntersection(ballVelLine, perpLineAcrossMyPos).IntersectPoint();//垂线与球线的交点
        //CVector ball2waitpoint = waitPoint - ball.RawPos();
        double ballDist = (ball.RawPos() - projectionPos).mod();
        bool isBallMovingToWaitPoint = ball.Vel().mod() > MIN_BALL_MOVING_VEL;//球是否在动
        bool canInterceptBall = false;
        //在touch半径内，且离场地边界9cm内，且球向waitpoint移动
        if (ZSkillUtils::instance()->IsInFieldV2(projectionPos, 9) && projectionPos.dist(waitPoint) < touchDist && isBallMovingToWaitPoint) {
            double meArriveTime = predictedTime(me, projectionPos);
            if((me.Pos() - projectionPos).mod() < 5) meArriveTime = 0;
            double ballArriveTime = 0;
            if (ball.Vel().mod2() / (2 * FRICTION) > ballDist) {//球能到
                ballArriveTime = (ball.Vel().mod() - sqrt(ball.Vel().mod2() - 2 * FRICTION * ballDist)) / FRICTION;
                if (meArriveTime < ballArriveTime) canInterceptBall = true;
            }
        }
        if (canInterceptBall) {
            if(IF_DEBUG) cout << "touch !!!" << endl;
            getballTask.player.pos = ballLineProjection + Utils::Polar2Vector(-Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER, getballTask.player.angle);
            if (Utils::InTheirPenaltyArea(getballTask.player.pos,0))
                getballTask.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
            setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle, getballTask.player.flag));
        } else {
            isTouch = false;
            judgeMode(pVision);//随你咋办
        }
    }

    /***************** rush *****************/
    if(getBallMode == RUSH) {
        if(IF_DEBUG) cout << "rush !!!" << endl;
        getballTask.player.pos = interPoint;// + Utils::Polar2Vector(-Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER, getballTask.player.angle);
        setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle, getballTask.player.flag));
    }

    /***************** inter touch *****************/
    if(getBallMode == INTERTOUCH) {
        if(IF_DEBUG) cout << "inter touch !!!" << endl;
        CVector projection2Me = me.Pos() - ballLineProjection;
//        finalDir = getballTask.player.angle;//判断射门
        getballTask.player.pos = interPoint + Utils::Polar2Vector(-Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER, getballTask.player.angle);
        if (fabs(Utils::Normalize(ball2Me.dir() -  ball.Vel().dir())) < 30 * Param::Math::PI / 180 && (ball.Pos() - me.Pos()).mod() < 30 + ball.Vel().mod() * 0.25 && fabs(Utils::Normalize(ball2Projection.dir() - ball.Vel().dir())) < 0.1) {
            getballTask.player.pos = ballLineProjection + Utils::Polar2Vector(-Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER, getballTask.player.angle);
        }
        if ((fabs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) < Param::Math::PI / 4) ||
                (fabs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) < Param::Math::PI / 2 && me2Ball.mod() <= 40))//追在球屁股后面，且可能撞上球
            getballTask.player.pos = getballTask.player.pos + (projection2Me / projection2Me.mod() * 40);//跑到球的侧面
        if (Utils::InTheirPenaltyArea(getballTask.player.pos,0))
            getballTask.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
        setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle, getballTask.player.flag));
    }
    /*************** chase kick **************/
    if (getBallMode == CHASEBALL) {
        if(IF_DEBUG) cout << "chase kick" << endl;
        //getballTask.player.angle = me2Target.dir();
        canForwardShoot = judgeShootMode(pVision);
        setSubTask(PlayerRole::makeItZChaseKick(robotNum, getballTask.player.angle));
        //setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle));
    }

    /************inter get ball************/
//    if (getBallMode == INTERBALL) {
//        if(IF_DEBUG) cout << "inter get ball" << endl;
//        setSubTask(PlayerRole::makeItCmuTurnKickV1(robotNum, Utils::MakeOutOfTheirPenaltyArea(targetPoint,0), flag, power, 9999));
//    }
    if (getBallMode == INTERBALL) {
        if(IF_DEBUG) cout << "inter get ball" << endl;
        CVector projection2Me = me.Pos() - ballLineProjection;
        getballTask.player.angle = me2Ball.dir();//面向球截球

        //已经贴球，且朝向球，则踢球或改变踢球方向
        if (me2Ball.mod() < 16 && fabs(Utils::Normalize(me.Dir() - me2Ball.dir())) < Param::Math::PI / 4) {
            //如果车角度正确，低速往前冲
            if (needkick && fabs(Utils::Normalize(me.Dir() - getballTask.player.angle)) < 3 * Param::Math::PI / 180) {
                getballTask.player.pos = ball.RawPos() + Utils::Polar2Vector(-5, Utils::Normalize(getballTask.player.angle));
                if (Utils::InTheirPenaltyArea(getballTask.player.pos,0))
                    getballTask.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
                setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle, getballTask.player.flag));
            }
            //如果车角度不对，需要转向
            else {
                int CLOCKWISE = -1;	//-1 顺时针
                if (Utils::Normalize(me.Dir()) < Utils::Normalize(getballTask.player.angle) && Utils::Normalize(me.Dir()) + Param::Math::PI > Utils::Normalize(getballTask.player.angle))
                    CLOCKWISE = 1;
                double newdir = me.Dir() + CLOCKWISE * Param::Math::PI / 18;//转10度
                double newdist = me2Ball.mod() +5;
                //getballTask.player.pos = CGeoPoint(ball.RawPos().x() - me2Ball.mod()*std::cos(newdir), ball.RawPos().y() - me2Ball.mod()*std::sin(newdir));
                getballTask.player.pos = CGeoPoint(ball.RawPos().x() - newdist*std::cos(newdir), ball.RawPos().y() - newdist*std::sin(newdir));
                double omega;
                //与射出角度相差小于30度
                if (me2Ball.mod() < 50 || fabs(Utils::Normalize(me.Dir() - getballTask.player.angle)) < Param::Math::PI / 6) {//角度差比较小的时候减速
                    omega = Param::Math::PI;//降低角速度
                    getballTask.player.speed_x = 20;//推着球转
                }
                else {
                    omega = Param::Math::PI * 2;//角度较大，加快转向
                    getballTask.player.speed_x = 30;
                }
                getballTask.player.speed_y = -CLOCKWISE*omega*me2Ball.mod();//车的y坐标
                getballTask.player.rotate_speed = CLOCKWISE*omega;
                setSubTask(TaskFactoryV2::Instance()->OpenSpeed(getballTask));
            }
        }
        //车到球线很近，车离球不远，车在球前，则车到截球线上等着
        else if (me.Pos().dist(ballLineProjection) < 50 && me2Ball.mod()<100 &&
            fabs(Utils::Normalize(ball2Projection.dir() - ball.Vel().dir()))<0.1) {
            if (fabs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) > Param::Math::PI / 3 * 2)//夹角小于60度直接去截球线
                getballTask.player.pos = ballLineProjection;
            else
                getballTask.player.pos = ballLineProjection + ball.Vel() * 2.5;//往前补偿
            //getballTask.player.angle = me2Ball.dir();//车朝球
            if (Utils::InTheirPenaltyArea(getballTask.player.pos,0))
                getballTask.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
            setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle, getballTask.player.flag));
        }
        //普通情况，计算接球点
        else {
            //ZSkillUtils::instance()->predictedInterTime(pVision, robotNum, testPoint, meArriveTime, 0.1);//0.2秒反应时间
            //testPoint = ZSkillUtils::instance()->getOurInterPoint(robotNum);
            CVector interPoint2Ball = ball.RawPos() - interPoint;
            getballTask.player.angle = interPoint2Ball.dir();//面向球截球

            if ((fabs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) < Param::Math::PI / 4) ||
                (fabs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) < Param::Math::PI / 2 && me2Ball.mod() <= 40))//追在球屁股后面，且可能撞上球
                getballTask.player.pos = interPoint + (projection2Me / projection2Me.mod() * 40);//跑到球的侧面
            else
                getballTask.player.pos = interPoint;
            if (Utils::InTheirPenaltyArea(getballTask.player.pos,0))
                getballTask.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
            setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle, getballTask.player.flag));
        }
    }

    /******************static get ball**************/
    if (getBallMode == STATICBALL) {
        if(IF_DEBUG) cout << "static get ball" << endl;
//        if (needkick) getballTask.player.angle = finalDir;//需要射球则朝向最终点
//        else getballTask.player.angle = me2Ball.dir();//不射则面向球
        if (needAvoidBall) {
            if (fabs(me2BallDirDiff) > Param::Math::PI / 3) {
                double avoidDir = Utils::Normalize(ball2Me.dir() + staticDir * Param::Math::PI / 4);
                getballTask.player.pos = ball.RawPos() + Utils::Polar2Vector(30, avoidDir);
            } else {
                double directDist = Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER + Param::Field::BALL_SIZE + 1;
                if (fabs(me2BallDirDiff) < 0.2) {
                    getballTask.player.pos = ball.RawPos() + Utils::Polar2Vector(directDist - 5, Utils::Normalize(finalDir - Param::Math::PI));
                } else {
                    getballTask.player.pos = ball.RawPos() + Utils::Polar2Vector(directDist, Utils::Normalize(finalDir - Param::Math::PI));
                }
            }
        } else {
            if (fabs(me2BallDirDiff) > Param::Math::PI / 2) {
                double gotoDir = Utils::Normalize(finalDir + staticDir * Param::Math::PI * 3.5 / 5);
                getballTask.player.pos = ball.RawPos() + Utils::Polar2Vector(40, gotoDir);
            } else if(fabs(me2BallDirDiff) <  15 * Param::Math::PI / 180) {
                getballTask.player.pos = ball.RawPos();
            } else {
                double directDist = Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER  + Param::Field::BALL_SIZE - 1.5;
                getballTask.player.pos = ball.RawPos() + Utils::Polar2Vector(directDist, Utils::Normalize(finalDir - Param::Math::PI));
            }
        }
        if (Utils::InTheirPenaltyArea(getballTask.player.pos,0))
            getballTask.player.pos = Utils::MakeOutOfTheirPenaltyArea(ball.Pos(),9);
        int goalieNumber = PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie());
        if (robotNum != goalieNumber && Utils::InOurPenaltyArea(getballTask.player.pos,0))
            getballTask.player.pos = Utils::MakeOutOfOurPenaltyArea(ball.Pos(),10);
        setSubTask(PlayerRole::makeItGoto(robotNum, getballTask.player.pos, getballTask.player.angle, getballTask.player.flag));

    }

    //是否吸球
    if (needdribble && me2Ball.mod() < 40) { //球在我前方则吸球
        DribbleStatus::Instance()->setDribbleCommand(robotNum, 3);
    }
    //是否射门
    if (needkick && fabs(Utils::Normalize(me.Dir() - getballTask.player.angle)) < SHOOT_ACCURACY && getBallMode != INTERBALL) {
        if(!chip) KickStatus::Instance()->setKick(robotNum, power);
        else KickStatus::Instance()->setChipKick(robotNum, power);
    }

    _lastCycle = pVision->Cycle();
    CStatedTask::plan(pVision);
}

CPlayerCommand* CGetBallV4::execute(const CVisionModule* pVision) {
    if (subTask()) return subTask()->execute(pVision);
    return NULL;
}

int CGetBallV4::getStaticDir(const CVisionModule* pVision, int staticDir) {
    const MobileVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    double ball2MeDir = (me.Pos() - ball.RawPos()).dir();
    //double finalDir = task().player.angle;
    const CVector me2Target = targetPoint - me.Pos();
    double finalDir = me2Target.dir();
    double tmp2FinalDirDiff = Utils::Normalize(ball2MeDir - finalDir);
    if (!staticDir) staticDir = tmp2FinalDirDiff > 0 ? 1 : -1;
    else {
        if (staticDir == 1) {
            if (tmp2FinalDirDiff < -0.5) staticDir = -1;
        } else if (tmp2FinalDirDiff > 0.5) staticDir = 1;
    }
    return staticDir;
}

void CGetBallV4::judgeMode(const CVisionModule * pVision) {
    const MobileVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    //const PlayerVisionT& me = pVision->OurPlayer(robotNum);

    /************** special judge *******************/
    if (isTouch) {//Touch优先级最高,进行一次判断，若不能touch，则isTouch为false
        getBallMode = TOUCH;
        return;
    }
    if (ball.Vel().mod() < MIN_BALL_MOVING_VEL) {
        getBallMode = STATICBALL;
        return;
    } else {
        getBallMode = INTERBALL; //as default
    }
    /************** normal judge *******************/
    interPoint = ZSkillUtils::instance()->getOurInterPoint(robotNum);
    interTime = ZSkillUtils::instance()->getOurInterTime(robotNum);
    CVector interPoint2target = targetPoint - interPoint;
    //CVector me2interPoint = interPoint - (me.Pos() + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER, (interPoint - me.Pos()).dir()));
    double ballBias = fabs(Utils::Normalize(ball.Vel().dir() - interPoint2target.dir()));
    // carBias = fabs(Utils::Normalize(me2interPoint.dir() - ball.Vel().dir()));
    //double normalDir = (ball.Vel().dir() - interPoint2target.dir()) / 2.0;//touch法线方向
    if(ballBias > (NORMAL_TOUCH_DIR / 180)*Param::Math::PI) { // May touch
        getBallMode = INTERTOUCH;
    } else if(ballBias < (NORMAL_CHASE_DIR / 180)*Param::Math::PI && !safeMode) { // May chase
        getBallMode = CHASEBALL;
    }
}


bool CGetBallV4::judgeShootMode(const CVisionModule * pVision) {
    const MobileVisionT& ball = pVision->Ball();
    const int robotNum = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(robotNum);
    const CVector me2Target = targetPoint - me.Pos();
    double finalDir = me2Target.dir();
    double ballVel2FinalDiff = Utils::Normalize(ball.Vel().dir() - finalDir);

    bool shootMode = fabs(ballVel2FinalDiff) < 0.5;
    return shootMode;
}
