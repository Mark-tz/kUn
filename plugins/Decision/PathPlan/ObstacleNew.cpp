#include "ObstacleNew.h"
#include "utils.h"
#include "GDebugEngine.h"
#include <iostream>
#include "PlayInterface.h"
#include "TaskMediator.h"


namespace {
    const double MAX_PROB_VEL = 500;
    const double MAX_DEC = 650;
    const double ZERO_VEL = 20;
    const double ROBOT_RADIUS = Param::Vehicle::V2::PLAYER_SIZE / 2;
    const double FRAME_PERIOD = 1.0 / Param::Vision::FRAME_RATE;
    const double START_AVOID_DIST = 50.0f;
    const double TEAMMATE_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 4.0f;
    const double OPP_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 2.5f;
    const double BALL_AVOID_DIST = Param::Field::BALL_SIZE + 1.5f;
}

//====================================================================//
//    Obstacle class implementation
//====================================================================//

double ObstacleNew::closestDist(CGeoPoint p) const {
    if (_type == OBS_DEFENCE_NEW) { // defence area
        CGeoRectangle tmpRect(_segStart, _segEnd);
        return tmpRect.dist2Point(p);
    }
    else if ((_segStart - _segEnd).mod() > EPSILON) { // long circle
        CGeoSegment tmpSeg(_segStart, _segEnd);
        return tmpSeg.dist2Point(p);
    }
    else { // circle
        return (_segStart - p).mod();
    }
}

double ObstacleNew::closestDist(CGeoSegment s) const {
    if (_type == OBS_DEFENCE_NEW) {
        CGeoRectangle tmpRect(_segStart, _segEnd);
        if (tmpRect.dist2Point(s.point1()) == 0 || tmpRect.dist2Point(s.point2()) == 0) return 0;
        CGeoLineRectangleIntersection tmpInter(s, tmpRect);
        if (tmpInter.intersectant() && s.IsPointOnLineOnSegment(tmpInter.point1())) return 0;
        else return min(tmpRect.dist2Point(s.point1()), tmpRect.dist2Point(s.point2()));
    }
    else return s.dist2Segment(CGeoSegment(_segStart, _segEnd));
}


void ObstacleNew::setParameters(ObstacleNew obst) {
    this->_robotRadius = obst.getRobotRadius();
    this->_obsRadius = obst.getRadius();
    this->_vel = obst.getVel();
    this->_segStart = obst.getStart();
    this->_segEnd = obst.getEnd();
    this->_dynamic = obst.isDynamic();
    this->_valid = obst.isValid();
    this->_type = obst.getType();
}

// return false if there will be collision
bool ObstacleNew::check(const CGeoPoint& p, double minDist) {
    return closestDist(p) - _obsRadius - _robotRadius - minDist > 0;
}

bool ObstacleNew::check(const CGeoSegment& s, double minDist) {
    return closestDist(s) - _obsRadius - _robotRadius - minDist > 0;
}

//====================================================================//
//    Obstacles class implementation
//====================================================================//

void ObstaclesNew::addObs(const CVisionModule * pVision, const TaskT & task) {
    int rolenum = task.executor;
    const PlayerVisionT& me = pVision->OurPlayer(rolenum);
    int flags = task.player.flag;
    int shootCar = task.ball.Sender;
    CGeoPoint targetPos = task.player.pos;

    // opp defence area
//    addDefence(CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2),
//               CGeoPoint(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2),
//               OPP_AVOID_DIST * 3);

    // avoid shooting line
    if (flags & PlayerStatus::AVOID_SHOOTLINE) {
        const PlayerVisionT& shooter = pVision->OurPlayer(shootCar);
        // center of the gate
        addLongCircle(shooter.Pos(), CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0.0f), CVector(0.0f, 0.0f), 3.0f, OBS_NORMAL_NEW);
        // left gate post
        addLongCircle(shooter.Pos(), CGeoPoint(Param::Field::PITCH_LENGTH / 2, Param::Field::GOAL_WIDTH / 2.0), CVector(0.0f, 0.0f), 3.0f, OBS_NORMAL_NEW);
        // right gate post
        addLongCircle(shooter.Pos(), CGeoPoint(Param::Field::PITCH_LENGTH / 2, -Param::Field::GOAL_WIDTH / 2.0), CVector(0.0f, 0.0f), 3.0f, OBS_NORMAL_NEW);
    }

    // set up teammates as obstacles
//    if (!(flags & PlayerStatus::NOT_AVOID_OUR_VEHICLE)) {
//        for (int i = 1; i <= Param::Field::MAX_PLAYER; ++i) {
//            const PlayerVisionT& teammate = pVision->OurPlayer(i);
//            if ((i != rolenum) && teammate.Valid()) {
//                addCircle(teammate.Pos(), teammate.Vel(), TEAMMATE_AVOID_DIST, OBS_CAR);
//            }
//        }
//    }

    // set up opponents as obstacles
    if (!(flags & PlayerStatus::NOT_AVOID_THEIR_VEHICLE)) {
        for (int i = 1; i <= Param::Field::MAX_PLAYER; ++i) {
            const PlayerVisionT& opp = pVision->TheirPlayer(i);
            if (opp.Valid()) {
                if ((false && (flags & PlayerStatus::IGNORE_PLAYER_CLOSE_TO_TARGET) &&
                    (targetPos.dist(opp.Pos()) < Param::Field::MAX_PLAYER_SIZE / 2))) {
                    continue;
                }
                else {
                    addCircle(opp.Pos(), opp.Vel(), OPP_AVOID_DIST, OBS_CAR_NEW);
                }
            }
        }
    }

    // our defence area
//	if ((true || flags & PlayerStatus::DODGE_OUR_DEFENSE_BOX) && (task.executor != PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie()))) {
//        addDefence(CGeoPoint(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2),
//                   CGeoPoint(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2),
//                   OPP_AVOID_DIST * 3);
//	}

    // ball
    if (flags & PlayerStatus::DODGE_BALL) {
        const MobileVisionT& ball = pVision->Ball();
        addCircle(ball.Pos(), ball.Vel(), BALL_AVOID_DIST, OBS_NORMAL_NEW);
    }

    if (flags & PlayerStatus::DODGE_REFEREE_AREA) {
        const MobileVisionT& ball = pVision->Ball();
        addCircle(ball.Pos(), CVector(0.0f, 0.0f), 50.0f, OBS_NORMAL_NEW);
    }
    stateNew currentState(me.Pos(), me.Dir(), me.Vel(), me.RotVel());
    changeWorld(currentState, MAX_DEC);
}

void ObstaclesNew::addLongCircle(const CGeoPoint& x0, const CGeoPoint& x1, const CVector& v, double r, int type, bool isDynamic) {
    if (obs.size() > MAX_OBSTACLESNEW) return;
    ObstacleNew obst;
    obst.setPos(x0, x1);
    obst.setType(type);
    obst.setVel(v);
    obst.setObsRadius(r);
    obst.setDynamic(isDynamic);
    obst.setRobotRadius(robotRadius);
    obst.setValid(true);
    obs.push_back(obst);
}

void ObstaclesNew::addCircle(const CGeoPoint& x0, const CVector& v, float r, int type, bool isDynamic) {
    if (obs.size() > MAX_OBSTACLESNEW) return;
    ObstacleNew obst;
    obst.setPos(x0);
    obst.setType(type);
    obst.setVel(v);
    obst.setObsRadius(r);
    obst.setDynamic(isDynamic);
    obst.setRobotRadius(robotRadius);
    obst.setValid(true);
    obs.push_back(obst);
}

void ObstaclesNew::addDefence(const CGeoPoint& x0, const CGeoPoint& x1, double r) {
    if (obs.size() > MAX_OBSTACLESNEW) return;
    ObstacleNew obst;
    obst.setPos(x0, x1);
    obst.setType(OBS_DEFENCE_NEW);
    obst.setVel(CVector(0, 0));
    obst.setObsRadius(r);
    obst.setDynamic(false);
    obst.setRobotRadius(robotRadius);
    obst.setValid(true);
    obs.push_back(obst);
}

// return true if there will be collision
bool ObstaclesNew::check(const CGeoPoint& p) {
    for (ObstacleNew obst : obs) {
        if (!obst.check(p)) return false;
    }
    return true;
}

bool ObstaclesNew::check(const CGeoPoint& p, int & id) {
    for (int i = 0; i < obs.size(); i++) {
        if (!obs[i].check(p)) {
            id = i;
            return false;
        }
    }
    return true;
}

bool ObstaclesNew::check(const CGeoPoint& p1, const CGeoPoint& p2) {
    CGeoSegment tmpSeg(p1, p2);
    for (ObstacleNew obst : obs) {
        if (!obst.check(tmpSeg)) return false;
    }
    return true;
}

bool ObstaclesNew::check(const CGeoPoint &p1, const CGeoPoint &p2, int &id) {
    CGeoSegment tmpSeg(p1, p2);
    for (int i = 0; i < obs.size(); i++) {
        if (!obs[i].check(tmpSeg)) {
            id = i;
            return false;
        }
    }
    return true;
}

void ObstaclesNew::changeWorld(const stateNew &curState, double dMax) {
    int numOfObs = obs.size();
    double distToStop, distWithObs;
    double scale = 5;
    double obstacalMove, obstacleLength;
    CGeoPoint segStartNew, segEndNew;
    double uncertainDist = 2.0;
    for(int i = 0; i < numOfObs; i++) {
        CVector obstacleVel = obs[i].getVel();
        double obstacleSpeed = obs[i].getVel().mod();
        distWithObs = obs[i].getStart().dist(curState.pos);
        if(obs[i].getType() == OBS_CAR_NEW) {
            if(curState.vel.mod() > ZERO_VEL /*&& curState.vel.mod() < MAX_PROB_VEL*/) { //自身速度不为零，距离很近的障碍物变形
                distToStop = curState.vel.mod2() / (2 * dMax);
                if(distToStop > distWithObs - obs[i].getRadius() - ROBOT_RADIUS) {
                    segStartNew = obs[i].getStart();
                    segEndNew = segStartNew + (-curState.vel) / (curState.vel.mod() * distToStop);
                    obs[i].setPos(segStartNew, segEndNew);
                }
            }
            if(obstacleSpeed > ZERO_VEL /*&& curState.vel.mod() < MAX_PROB_VEL*/) { //障碍物速度不为零，对障碍物未来的位置进行预测，作为新的障碍物加入
                obstacalMove = obstacleSpeed * FRAME_PERIOD * scale;
                segStartNew = obs[i].getStart() + Utils::Polar2Vector(obstacalMove, obs[i].getVel().dir());
                segEndNew = obs[i].getEnd() + Utils::Polar2Vector(obstacalMove, obs[i].getVel().dir());
                obs[i].setPos(segStartNew, segEndNew);
                obstacleLength = obstacalMove + uncertainDist;
                addLongCircle(segStartNew + (-obstacleVel / obstacleVel.mod() * obstacleLength / 4), segEndNew + (obstacleVel / obstacleVel.mod() * obstacleLength * 2.5), CVector(0, 0), obs[i].getRadius(), OBS_CAR_NEW);
            }
        }
    }
}
