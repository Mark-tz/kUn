#include "ZGoalie.h"
#include "VisionModule.h"
#include "parammanager.h"
#include "geometry.h"
#include "Factory.h"
#include "param.h"
#include "SkillUtils.h"
#include "BallSpeedModel.h"
#include "BestPlayer.h"
#include "GDebugEngine.h"
namespace{

    const static int MIN_X = -Param::Field::PITCH_LENGTH/2;
    const static int MAX_X = -Param::Field::PITCH_LENGTH/2 + Param::Field::PENALTY_AREA_DEPTH;
    const static int MIN_Y = -Param::Field::PENALTY_AREA_WIDTH/2;
    const static int MAX_Y = Param::Field::PENALTY_AREA_WIDTH/2;

    const CGeoPoint LEFT_GOAL_POST(-Param::Field::PITCH_LENGTH/2,-Param::Field::GOAL_WIDTH/2);
    const CGeoPoint RIGHT_GOAL_POST(-Param::Field::PITCH_LENGTH/2,Param::Field::GOAL_WIDTH/2);
    const CGeoSegment GOAL_LINE(LEFT_GOAL_POST,RIGHT_GOAL_POST);

    const double PENALTY_PADDING = 0;//2*Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER;
    const CGeoPoint PENALTY_LEFT_UP(MAX_X-PENALTY_PADDING,MIN_Y+PENALTY_PADDING);
    const CGeoPoint PENALTY_RIGHT_DOWN(MIN_X+PENALTY_PADDING,MAX_Y-PENALTY_PADDING);
    const CGeoRectangle PENALTY(PENALTY_LEFT_UP,PENALTY_RIGHT_DOWN);

    const double TOP_PADDING = Param::Vehicle::V2::PLAYER_SIZE*1.5;// after calculation
    const double Y_PADDING = Param::Vehicle::V2::PLAYER_SIZE*2.5;//after calculation
    const double BOTTOM_PADDING = Param::Vehicle::V2::PLAYER_SIZE;
    const CGeoPoint ATTACK_LEFT_UP(MAX_X-TOP_PADDING,MIN_Y+Y_PADDING);
    const CGeoPoint ATTACK_RIGHT_DOWN(MIN_X + BOTTOM_PADDING,MAX_Y-Y_PADDING);
    const CGeoRectangle ATTACK_RECTANGLE(ATTACK_LEFT_UP,ATTACK_RIGHT_DOWN);

    //bool in_back_of_penalty(const CGeoPoint& pos);
    bool in_our_penalty(const CGeoPoint& pos,double padding = 0);
    double get_defence_direction(const CGeoPoint&);

    bool DEBUG = false;

    const double SAFE_ARRIVED_TIME = 0.05;
    const double ARRIVED_TIME = 0.2;

    PlayerCapabilityT GOALIE_CAPABILITY;
}
CZGoalie::CZGoalie(){
    ZSS::ZParamManager::instance()->loadParam(DEBUG,"Debug/ZGoalie",false);
    ZSS::ZParamManager::instance()->loadParam(GOALIE_CAPABILITY.maxAccel        ,"CGotoPositionV2/MGoalieAcc"   ,600);
    ZSS::ZParamManager::instance()->loadParam(GOALIE_CAPABILITY.maxSpeed        ,"CGotoPositionV2/MGoalieSpeed" ,300);
    ZSS::ZParamManager::instance()->loadParam(GOALIE_CAPABILITY.maxAngularAccel ,"CGotoPositionV2/RotationAcc"  ,15 );
    ZSS::ZParamManager::instance()->loadParam(GOALIE_CAPABILITY.maxAngularSpeed ,"CGotoPositionV2/RotationSpeed",15 );
    ZSS::ZParamManager::instance()->loadParam(GOALIE_CAPABILITY.maxDec          ,"CGotoPositionV2/MGoalieDec"   ,600);
    ZSS::ZParamManager::instance()->loadParam(GOALIE_CAPABILITY.maxAngularDec   ,"CGotoPositionV2/RotationAcc"  ,15 );
}
void CZGoalie::plan(const CVisionModule* pVision){
    int player = task().executor;
    int power = task().player.kickpower;
    int flag = task().player.flag;
    auto& pos = task().player.pos;

    CGeoPoint our_goal(-Param::Field::PITCH_LENGTH/2,0);

    auto& ball = pVision->Ball().Valid() ? pVision->Ball().RawPos() : pVision->Ball().Pos();
    auto ball_vel = pVision->Ball().Vel().mod();
    auto ball_vel_dir = pVision->Ball().Vel().dir();
    CGeoSegment ball_line(ball,BallSpeedModel::Instance()->posForTime(9999,pVision));
    auto& self = pVision->OurPlayer(player);
    auto& self_pos = self.Pos();

    CGeoEllipse stand_ellipse(our_goal,Param::Field::PENALTY_AREA_DEPTH/2,Param::Field::GOAL_WIDTH/2);
    CGeoLineEllipseIntersection stand_intersection(CGeoLine(ball,get_defence_direction(ball)),stand_ellipse);
    CGeoPoint stand_pos;
    if(stand_intersection.intersectant()){
        if(ball.dist2(stand_intersection.point1())<ball.dist2(stand_intersection.point2()))
            stand_pos = stand_intersection.point1();
        else
            stand_pos = stand_intersection.point2();
        if(stand_pos.x() < MIN_X + Param::Vehicle::V2::PLAYER_SIZE)
            stand_pos.setX(MIN_X + Param::Vehicle::V2::PLAYER_SIZE);
    }else{
        stand_pos = CGeoPoint(-Param::Field::PITCH_LENGTH/2+Param::Vehicle::V2::PLAYER_SIZE,0);
    }
    double stand_dir = (ball-stand_pos).dir();

    CGeoLineRectangleIntersection intersection(ball_line,PENALTY);
    auto& intersection_point1 = intersection.point1();
    auto& intersection_point2 = intersection.point2();
    CGeoPoint projection_pos = ball_line.projection(self_pos);
    bool projection_inside_penalty = in_our_penalty(projection_pos) && (ball_vel_dir - (projection_pos - ball).dir()) < Param::Math::PI/18;
    CGeoPoint target_pos = stand_pos;
    double target_dir = 0;
    if(projection_inside_penalty){
        target_pos = projection_pos;
    }else if(intersection.intersectant()){
        if(projection_pos.dist2(intersection_point1) < projection_pos.dist2(intersection_point2))
            target_pos = (ball_vel_dir - (intersection_point1 - ball).dir() < Param::Math::PI/18) ? intersection_point1 : intersection_point2;
        else
            target_pos = (ball_vel_dir - (intersection_point2 - ball).dir() < Param::Math::PI/18) ? intersection_point2 : intersection_point1;
    }else{
        target_pos = stand_pos;
    }
    if(DEBUG) GDebugEngine::Instance()->gui_debug_x(target_pos,0);
    bool target_on_ball_line = ball_line.IsPointOnLineOnSegment(target_pos);
    double time_ball_point = BallSpeedModel::Instance()->timeForDist(ball.dist(target_pos),pVision);
    if(time_ball_point < 0) time_ball_point = 9999;
    double time_player_point = predictedTime(self, target_pos);
    bool can_inter = intersection.intersectant() && target_on_ball_line && (time_ball_point - time_player_point > SAFE_ARRIVED_TIME || time_player_point < ARRIVED_TIME);

    CVector target_vel;
    predictRushSpeed(self,target_pos,time_ball_point-SAFE_ARRIVED_TIME,GOALIE_CAPABILITY,target_vel);

    CGeoLineLineIntersection danger_intersection(ball_line,GOAL_LINE);
    bool danger_to_our_goal = danger_intersection.Intersectant() && ball_line.IsPointOnLineOnSegment(danger_intersection.IntersectPoint()) && GOAL_LINE.IsPointOnLineOnSegment(danger_intersection.IntersectPoint()) && (ball_vel_dir - (danger_intersection.IntersectPoint() - ball).dir()) < Param::Math::PI/18;
    bool need_clear = in_our_penalty(ball,-10) && ball_vel < 50;

    const auto& enemy = pVision->TheirPlayer(BestPlayer::Instance()->getTheirBestPlayer());
    const auto& enemy_projection = ball_line.projection(enemy.Pos());
    const auto& enemy_dist_to_ball = (enemy_projection - enemy.Pos()).mod();
    bool enemy_danger = ball_line.IsPointOnLineOnSegment(enemy_projection);
    bool need_defense = enemy_danger && in_our_penalty(enemy.Pos(),-100) && !danger_to_our_goal && ball_vel > 50;
    bool need_attack = in_our_penalty(enemy.Pos(),-100) && ball_vel <= 50 && (ball - enemy.Pos()).mod() < 50;
    bool need_stand_closer = need_defense || need_attack;
    CGeoLineRectangleIntersection attack_intersection(CGeoLine(enemy.Pos(),get_defence_direction(enemy.Pos())),ATTACK_RECTANGLE);
    CGeoPoint attack_pos;
    if(attack_intersection.intersectant()){
        if(enemy.Pos().dist2(attack_intersection.point1())<enemy.Pos().dist2(attack_intersection.point2()))
            attack_pos = attack_intersection.point1();
        else
            attack_pos = attack_intersection.point2();
    }else{
        attack_pos = stand_pos;
    }
    double attack_dir = (ball-attack_pos).dir();

    // zero velocity to inter the ball
    if(can_inter){
        if(DEBUG) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500,-160),"ZERO_INTER",0);
        target_dir = ball_vel_dir + Param::Math::PI;
        setSubTask(PlayerRole::makeItSimpleGoto(player,target_pos,target_dir));
    }
    // none zero velocity to save
    else if(danger_to_our_goal){
        if(DEBUG) {
            GDebugEngine::Instance()->gui_debug_x(danger_intersection.IntersectPoint(),3);
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500,-160),"NONE_ZERO_SAVE",0);
        }
        setSubTask(PlayerRole::makeItSimpleGoto(player,target_pos,target_dir,target_vel,0));
    }
    // clear ball
    else if(need_clear){
        if(DEBUG) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500,-160),"CLEAR_BALL",0);
        setSubTask(PlayerRole::makeItGetBallV4(player,flag,pos,CGeoPoint(-9999,-9999),power));
    }
    // attack stand
    else if(need_stand_closer){
        if(DEBUG) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500,-160),"ATTACK_STAND",0);
        setSubTask(PlayerRole::makeItSimpleGoto(player,attack_pos,attack_dir));
    }
    // normal stand
    else{
        if(DEBUG) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-500,-160),"NORMAL_STAND",0);
        setSubTask(PlayerRole::makeItSimpleGoto(player,stand_pos,stand_dir));
    }


    _lastCycle = pVision->Cycle();
    CStatedTask::plan(pVision);
}
CPlayerCommand* CZGoalie::execute(const CVisionModule* pVision){
    if (subTask()) return subTask()->execute(pVision);
    return nullptr;
}
namespace{
// padding positive means smaller area, padding negative means larger area
bool in_our_penalty(const CGeoPoint& pos,double padding){
    if(pos.x() > MIN_X + padding && pos.x() < MAX_X - padding && pos.y() > MIN_Y + padding && pos.y() < MAX_Y - padding)
        return true;
    return false;
}
double get_defence_direction(const CGeoPoint & pos){
    double leftPostToBallDir = (pos - LEFT_GOAL_POST).dir();
    double rightPostToBallDir = (pos - RIGHT_GOAL_POST).dir();
    if(DEBUG){
        GDebugEngine::Instance()->gui_debug_line(pos,LEFT_GOAL_POST,6);
        GDebugEngine::Instance()->gui_debug_line(pos,RIGHT_GOAL_POST,6);
    }
    return Utils::Normalize((leftPostToBallDir + rightPostToBallDir) / 2 + Param::Math::PI);
}
//bool in_back_of_penalty(const CGeoPoint& pos){
//    if(pos.x())
//}
}
