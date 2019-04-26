#ifndef BEZIERMOTION_H
#define BEZIERMOTION_H
#include "ObstacleNew.h"
#include <vector>

class BezierMotion
{
public:

    bool isMovePlanner;
    double moveAccelFactor;
    double rotateAccelFactor;
public:
    BezierMotion() : isMovePlanner(true), moveAccelFactor(1), rotateAccelFactor(1) {}
    void bezierMotion1d(double x0, double v0, double v1, double aMax, double dMax, double vMax, double &trajAccel, double &trajTime, double &trajTimeAcc, double &trajTimeDec, double &trajTimeFlat);
    void bezierMotion2d(const stateNew& start, const stateNew& target, const PlayerCapabilityT& capability, CVector& trajAccel, double& time);
    void bezierGotoPoint(const stateNew& start, const stateNew& target, const PlayerCapabilityT& capability, const double& accelFactor, const double& angleAccFactor, stateNew& nextFrame);
};

#endif // BEZIERMOTION_H
