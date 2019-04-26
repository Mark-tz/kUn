#include "ZPassV2.h"
#include "GDebugEngine.h"
#include "RobotSensor.h"
#include "skill/Factory.h"
#include "TaskMediator.h"
#include "SkillUtils.h"
#include <utils.h>
#include <DribbleStatus.h>
#include <ControlModel.h>
#include <VisionModule.h>
#include "Compensate.h"
#include "GDebugEngine.h"
#include <fstream>

namespace {
enum{
    TOUCH = 1,
    TURNKICK = 2,
    CMUTURN = 3,
    ZCIRCLE = 4,
    GOWAITPOS = 5
};
    int turn_mode = 2;
    int FRICTION;
    const double MIN_BALL_MOVING_VEL = 50;      // 球速小于这个值就算不在滚
    const bool verbose = false;
    const double kSafeRange = 100;
    const double NORMAL_TOUCH_DIR = 110.0;//根据球踢出后偏移的角度判断是否要touch
    int touch;
    // guarantee touch success. Higher kMaxTouch means safer touch
    const int kMaxTouch = 30;
    bool if_have_waitpos = false;
    bool if_at_waitpos = false;
    const double in_waitpos_buffer = 30;
//    const double out_waitpos_buffer = 60;

    int last_cycle;
}

void CZPassV2::plan( const CVisionModule* pVision ){
    /***************************************************************/
    /* STEP ONE: vision messsage preliminary process               */
    /***************************************************************/
    const int robot_num = task().executor;
    const CGeoPoint target = task().player.pos;
    // There is not param waitpos in misc_types, so use speed_x and speed_y
    // pass param waitpos
    const CGeoPoint waitpos(task().player.speed_x, task().player.speed_y);
    const double power = task().player.kickpower;
    const double dir = task().player.angle;
    const int flag = task().player.flag;

    needkick_ = flag & PlayerStatus::KICK;//是否需要射出球
    chip_ = flag & PlayerStatus::CHIP;//是否挑射
    needdribble_ = flag & PlayerStatus::DRIBBLE;
    safeMode_ = flag & PlayerStatus::SAFE;

    const MobileVisionT& ball = pVision->Ball();
    const PlayerVisionT& me = pVision->OurPlayer(robot_num);

    TaskT zpassv2(task());
    CGeoPoint test_point(ball.RawPos().x(), ball.RawPos().y());
    CVector me2Ball = ball.RawPos() - me.Pos();
    CVector ball2me = me.Pos() - ball.RawPos();
    CVector me2waitpos = waitpos - me.Pos();
    CGeoLine ball_line(ball.RawPos(), ball.Vel().dir());
    CVector me2ball_vector =
           Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER,
                               me.Dir());
    ZSS::ZParamManager::instance()->loadParam(FRICTION,
                                              "AlertParam/Friction",40);
    ball_line_projection_ = ball_line.projection(me.Pos() + me2ball_vector);
    CVector ball2Projection = ball_line_projection_ - ball.RawPos();

    // draw me2target line
    if (chip_){
        GDebugEngine::Instance()->gui_debug_x( CGeoPoint(target), COLOR_YELLOW );
        GDebugEngine::Instance()->gui_debug_line( CGeoPoint(me.Pos()),
                                                  CGeoPoint(target),
                                                  COLOR_YELLOW);
    }
    else{
        GDebugEngine::Instance()->gui_debug_x( CGeoPoint(target), COLOR_RED );
        GDebugEngine::Instance()->gui_debug_line( CGeoPoint(me.Pos()),
                                                  CGeoPoint(target));
    }

    /***************************************************************/
    /* STEP TWO: judge mode                                        */
    /***************************************************************/
    CGeoPoint interPoint = ZSkillUtils::instance()->getOurInterPoint(robot_num);
    CVector interPoint2target = target - interPoint;
    double ballBias = fabs(Utils::Normalize(ball.Vel().dir() -
                                            interPoint2target.dir()));

    if ( ZSkillUtils::instance()->IsInField(waitpos) ){
        if_have_waitpos = true;
    }

    JudgeMode( pVision, robot_num, target );

    bool can_intercept_ball = false;
    if(ballBias > (NORMAL_TOUCH_DIR/180)*Param::Math::PI)
        can_intercept_ball = true;
    if ( ball.Vel().mod() < MIN_BALL_MOVING_VEL )
        can_intercept_ball = false;


    if ( can_intercept_ball ) {
        touch = touch >= kMaxTouch ? kMaxTouch : touch + 1;
    }
    else {
        touch = 0;
    }

    if (touch == kMaxTouch) {
        turn_mode = TOUCH;
    }
//    turn_mode = CMUTURN;


//    cout << "[ZPassV2.cpp] last_cycle: " << last_cycle << ", now_cycle"
//         << pVision->Cycle() << endl;
    if ( if_have_waitpos ){
        if ( pVision->Cycle() - last_cycle > 6 ){
            if_at_waitpos = false;
        }
        last_cycle = pVision->Cycle();

        if (me2waitpos.mod() < in_waitpos_buffer ){
            if_at_waitpos = true;
        }
//        cout << "[ZPassV2.cpp] if_at_waitpos: " << if_at_waitpos << endl;

        if ( !if_at_waitpos ) {
            turn_mode = GOWAITPOS;
        }
    }

    /***************************************************************/
    /* STEP THREE: execution                                       */
    /***************************************************************/
    switch (turn_mode) {
    case TOUCH:{
        if (verbose) {
            GDebugEngine::Instance()->gui_debug_msg(me.Pos(),"touch",COLOR_RED);
            GDebugEngine::Instance()->
                    gui_debug_line(me.Pos(), target, COLOR_RED);
        }
        if ( dir > Param::Math::PI ){
            //默认的射门角度，加了补偿和算射门角
            if (needkick_){
                KickDirection::Instance()->
                        GenerateShootDir(robot_num, me.Pos());
                zpassv2.player.angle = KickDirection::Instance()->
                        getRealKickDir();
            }
            else
                zpassv2.player.angle = me2Ball.dir();//只截球，不射

            //不射门的情况下角度，但是没有算射门角
            if (!Utils::InTheirPenaltyArea(target, 0)){
                zpassv2.player.angle =
                        Compensate::Instance()->getKickDir(robot_num,target);
            }
        }
        else {
            zpassv2.player.angle = dir;
        }

        if (needkick_ ) {
            if(!chip_) KickStatus::Instance()->setKick(robot_num, power);
            else KickStatus::Instance()->setChipKick(robot_num, power);
        }

        // calculate run position
        CVector projection2Me = me.Pos() - ball_line_projection_;
        zpassv2.player.pos = interPoint +
                Utils::Polar2Vector(
                    -Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER,
                    zpassv2.player.angle);
        if (fabs(Utils::Normalize(ball2me.dir() -  ball.Vel().dir())) <
                30*Param::Math::PI/180 &&
                (ball.Pos() - me.Pos()).mod() < 30+ball.Vel().mod()*0.25 &&
                fabs(Utils::Normalize(ball2Projection.dir() -
                                      ball.Vel().dir()))<0.1) {

            zpassv2.player.pos = ball_line_projection_+
                    Utils::Polar2Vector(
                        -Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER,
                        zpassv2.player.angle);
        }

        //追在球屁股后面，且可能撞上球
        if ((abs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) <
             Param::Math::PI / 4) ||
            (abs(Utils::Normalize(me2Ball.dir() - ball.Vel().dir())) <
             Param::Math::PI / 2 && me2Ball.mod() <= 40))

            zpassv2.player.pos = zpassv2.player.pos +
                    (projection2Me / projection2Me.mod() * 45);//跑到球的侧面

        setSubTask(PlayerRole::makeItGoto(robot_num,
                                          zpassv2.player.pos,
                                          zpassv2.player.angle,
                                          zpassv2.player.flag));
        break;
    }
    case CMUTURN:{
        zpassv2.player.pos = target;
        zpassv2.player.flag = flag;
        zpassv2.player.kickpower = power;
        zpassv2.player.angle = dir;
        setSubTask(PlayerRole::makeItCmuTurnKickV1(robot_num,
                                                   zpassv2.player.pos,
                                                   zpassv2.player.flag,
                                                   zpassv2.player.kickpower,
                                                   zpassv2.player.angle));
        break;
    }
    case TURNKICK:{
        zpassv2.player.pos = target;
        zpassv2.player.flag = flag;
        zpassv2.player.kickpower = power;
        zpassv2.player.angle = dir;
        setSubTask(PlayerRole::makeItGoAndTurnKickV4(robot_num,
                                                     zpassv2.player.pos,
                                                     zpassv2.player.flag,
                                                     zpassv2.player.kickpower,
                                                     zpassv2.player.angle));
        break;
    }
    case GOWAITPOS:{
        if ( dir > Param::Math::PI ){
            zpassv2.player.angle = me2Ball.dir();
        }
        else {
            zpassv2.player.angle = dir;
        }
        zpassv2.player.pos = waitpos;
        zpassv2.player.flag = flag;
        zpassv2.player.kickpower = power;
        setSubTask(PlayerRole::makeItGoto(robot_num,
                                          zpassv2.player.pos,
                                          zpassv2.player.angle,
                                          zpassv2.player.flag));
        break;
    }
    }

    CStatedTask::plan(pVision);
    return;
}

CPlayerCommand* CZPassV2::execute(const CVisionModule *pVision) {
    if (subTask()){
        return subTask()->execute(pVision);
    }
    return nullptr;
}

void JudgeMode( const CVisionModule* pVision, int robot_num,
                        CGeoPoint pos ){
    const PlayerVisionT& me = pVision->OurPlayer(robot_num);
    int close_target_car_number = 0;
    int far_target_car_number = 0;
    double me2target = (me.Pos() - pos).mod();
    for( int i = 0; i < Param::Field::MAX_PLAYER; i++ ){
        if(pVision->TheirPlayer(i).Valid()){
            double enemy2target = (pVision->TheirPlayer(i).Pos() - pos).mod();
            double enemy2me = (pVision->TheirPlayer(i).Pos() -
                               pVision->OurPlayer(robot_num).Pos()).mod();
            if ( enemy2target < me2target && enemy2me < kSafeRange )
                close_target_car_number++;
            else if ( enemy2target > me2target && enemy2me < kSafeRange )
                far_target_car_number++;
        }
    }
//    if ( close_target_car_number == 0 && far_target_car_number == 0 )
//        return 0;
//    else if ( close_target_car_number >= far_target_car_number )
//        return 1;
//    else
//        return 2;
    if ( close_target_car_number >= far_target_car_number )
        turn_mode = TURNKICK;
    else
        turn_mode = CMUTURN;
}
