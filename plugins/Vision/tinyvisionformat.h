#ifndef __MESSAGEFORMAT_H__
#define __MESSAGEFORMAT_H__
#include "staticparams.h"
#include <iostream>
#include "geometry.h"
/************************************************************************/
/*                 Basic Vision Classes                                 */
/************************************************************************/
namespace {

struct Ball {
    CGeoPoint pos;
    CVector velocity;
    Ball(): pos() {}
    bool fill(double x, double y, CVector vel = CVector(0, 0)) {
        this->pos.setX(x);
        this->pos.setY(y);
        this->velocity = vel;
        return true;
    }
    bool fill(const Ball& ball) {
        return fill(ball.pos.x(), ball.pos.y(), ball.velocity);
    }
};
struct Robot {
    unsigned short id;
    CGeoPoint pos;
    CGeoPoint predict_pos;
    double angle;
    CVector velocity;
    double rotateVel;
    Robot(): id(-1) {}
    Robot(double _x, double _y, double _angle, double _id = -1) {
        pos.setX(_x);
        pos.setY(_y);
        angle = _angle;
        id = _id;
    }
    bool fill(unsigned short id, double _x, double _y, double angel, CVector vel = CVector(0, 0)) {
        this->id = id;
        pos.setX(_x);
        pos.setY(_y);
        this->angle = angel;
        this->velocity = vel;
        return true;
    }
    bool fill(const Robot& robot) {
        return fill(robot.id, robot.pos.x(), robot.pos.y(), robot.angle, robot.velocity);
    }
    bool setPos(CGeoPoint pos) {
        this->pos = pos;
        return true;
    }
    bool setPredictPos(CGeoPoint prePos) {
        this->predict_pos = prePos;
        return true;
    }
};


const int BLUE = 0;
const int YELLOW = 1;
//* Robot store the data, Index and Size exist for the index search for robots;
//* Index : -1 means not exist, or it means the index in Robot Array;
//* VisionMessage use for the final processed vision data.
class OriginMessage {
  public:
    unsigned short robotSize[2];
    unsigned short ballSize;
    Robot robot[2][PARAM::ROBOTNUM];
    Ball ball[PARAM::BALLNUM];
    OriginMessage(): ballSize(0) {
        robotSize[BLUE] = robotSize[YELLOW] = 0;
    }
    bool addRobot(int color, unsigned short id, double x, double y, double angel) {
        if(robotSize[color] >= PARAM::ROBOTNUM)
            return false;
        return robot[color][robotSize[color]++].fill(id, x, y, angel);
    }
    bool addRobot(int color, unsigned short id, CGeoPoint point, double angel) {
        if(robotSize[color] >= PARAM::ROBOTNUM)
            return false;
        return robot[color][robotSize[color]++].fill(id, point.x(), point.y(), angel);
    }
    bool addRobot(int color, const Robot& r) {
        if(robotSize[color] >= PARAM::ROBOTNUM)
            return false;
        return robot[color][robotSize[color]++].fill(r);
    }
    bool addBall(const Ball& b) {
        return ballSize >= PARAM::BALLNUM ? false : ball[ballSize++].fill(b);
    }
    bool addBall(const CGeoPoint& p) {
        return ballSize >= PARAM::BALLNUM ? false : ball[ballSize++].fill(p.x(), p.y());
    }
};
}


#endif // __MESSAGEFORMAT_H__
