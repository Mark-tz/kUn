#ifndef __ZSS_SERVER_H__
#define __ZSS_SERVER_H__
#include "param.h"
#include "geometry.h"
struct PosT {
    PosT(): valid(0), x(0), y(0) {}
    int valid;
    float x;
    float y;
    void setValid(int _value) {
        valid = _value;
    }
};

struct VehicleInfoT {
    VehicleInfoT(): dir(0), type(0),dirvel(0) {}
    PosT pos;
    CVector vel;
    float dir;//radius
    float dirvel;
    int type;
};
enum ballState {received, touched, kicked, struggle, chip_pass, flat_pass};

struct VisualInfoT {
    VisualInfoT(): cycle(0), BallState(received), BallLastTouch(0), mode(0) {}
    int cycle;
    VehicleInfoT player[ 2 * Param::Field::MAX_PLAYER_NUM];//前一半永远存放我方车
    PosT ball;
    CVector BallVel;
    ballState BallState;
    int BallLastTouch;
    int mode;
    unsigned char ourRobotIndex[ Param::Field::MAX_PLAYER_NUM];
    //unsigned char ourRobotIndexBefore[ Param::Field::MAX_PLAYER_NUM] = {};
    int before_cycle[ 2 * Param::Field::MAX_PLAYER_NUM] = {};
    unsigned char theirRobotIndex[ Param::Field::MAX_PLAYER_NUM] = {};
    // unsigned char theirRobotIndexBefore[ Param::Field::MAX_PLAYER_NUM] = {};
    //PosT imageBall;
    PosT ballPlacePosition;
};
#endif // __ZSS_SERVER_H__
