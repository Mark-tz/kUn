#include "BezierMotion.h"
#include "CMmotion.h"
#include <iostream>
#include <GDebugEngine.h>

namespace {
        const double FRAME_PERIOD = 1.0 / Param::Vision::FRAME_RATE;
        const double zeroVel = 0;
        const double PI = 3.14159265359;
}



void BezierMotion::bezierMotion1d(double x0, double v0, double v1, double aMax, double dMax, double vMax, double &trajAccel, double &trajTime, double &trajTimeAcc, double &trajTimeDec, double &trajTimeFlat) {
    if(x0 == 0 && v0 == v1) {
        trajTime = trajTimeAcc = trajTimeDec = trajAccel = trajTimeFlat = 0;
        return;
    }
    double aMaxOri = aMax;
    double dMaxOri = dMax;
    aMax = aMax / (isMovePlanner ? moveAccelFactor : rotateAccelFactor);
    dMax = dMax / (isMovePlanner ? moveAccelFactor : rotateAccelFactor);
    double flatVel = 0.2 * vMax;

    double period = 1 / 40.0; //参考CMmotion中的那个值，处理运动到目标点附近时的加速度
    double accelTimeToV1 = fabs(v1 - v0) / aMax;
    double accelDistToV1 = fabs((v1 + v0) / 2.0) * accelTimeToV1;
    double decelTimeToV1 = fabs(v1 - v0) / dMax;
    double decelDistToV1 = fabs((v0 + v1) / 2.0) * decelTimeToV1;

    if(v0 * x0 < 0 || (fabs(v0) > fabs(v1) && decelDistToV1 > fabs(x0))) {
        double timeToStop = fabs(v0) / dMax;
        double distToStop = v0 * v0 /(2.0 * dMax);

        bezierMotion1d(x0 + copysign(distToStop, v0), 0, v1, aMaxOri, dMaxOri, vMax, trajAccel, trajTime, trajTimeAcc, trajTimeDec, trajTimeFlat);

        trajTime += timeToStop;
        if(trajTime < period) {
            if(fabs(v0) / dMax > FRAME_PERIOD) trajAccel = copysign(dMaxOri, -v0);
            else trajAccel = copysign(fabs(v0) / FRAME_PERIOD , -v0);
        }
        else if(timeToStop < period) {
            trajAccel = timeToStop / period * copysign(dMaxOri, -v0) + (1.0 - timeToStop / period) * copysign(trajAccel, -v0);
        }
        else {
            trajAccel = copysign(dMaxOri, -v0);
        }
        return;
    }
    //后面是初速度和目标点同向的情况,即不存在反向的情况，末速度可达
    if(fabs(v0) >= fabs(v1)) {
        if(fabs(v0) >= flatVel) {//较大速度不小于平动速度，此时用较大速度平动，然后减速到目标速度；
            flatVel = fabs(v0);
            trajTimeAcc = 0;
            trajTimeFlat = (fabs(x0) - decelDistToV1) / fabs(v0);
            trajTimeDec = decelTimeToV1;  //考虑方向的减速时间,可能末速度与位移反向
        }
        else { //较大速度小于平动设定速度，此时先加速到平动速度，再平动、减速到目标速度
            double distToFlatVel = (flatVel * flatVel - v0 * v0) / aMax;
            double distToV2 = (flatVel * flatVel - v1 * v1) / dMax;
            if(distToFlatVel + distToV2 <= fabs(x0)) { //可以达到flatVel
                trajTimeAcc = (flatVel - fabs(v0)) / aMax;
                trajTimeDec = fabs(copysign(flatVel, v0) - v1) / dMax;
                trajTimeFlat = (fabs(x0) - distToFlatVel - distToV2) / flatVel;
            }
            else { //不可达flatVel，说明位移很短了,改用三角规划
                trajTimeAcc = (sqrt((v0 * v0 + 2 * aMax * fabs(x0)) / (1 + aMax / dMax)) - fabs(v0)) / aMax;
                flatVel = fabs(v0) + trajTimeAcc * aMax;
                trajTimeFlat = 0;
                trajTimeDec = (trajTimeAcc * aMax + fabs(v0) - fabs(v1)) / dMax;
            }
        }
    }
    //初速度小于末速度
    else {
        flatVel = fabs(v1);
        if(accelDistToV1 > fabs(x0)) { //即使一直加速也无法到达目标速度
            trajTimeAcc = (sqrt(v0 * v0 + 2 * aMax * fabs(x0)) - fabs(v0)) / aMax;
            trajTimeDec = trajTimeFlat = 0;
        }
        else { //可以加速到目标速度，先加速到目标速度，再匀速运动
            trajTimeAcc = accelTimeToV1;
            trajTimeFlat = (fabs(x0) - accelDistToV1) / fabs(v1);
            trajTimeDec = 0;
        }
    }
//根据上面的时间计算速度，考虑抖动问题： 抖动要分较大速度大于flatV和较大速度小于flatV两种情况；

    double accelToV1AtX0 = fabs(v0 * v0 - v1 * v1) / (2 * fabs(x0));
    double timeToV1 = fabs(v1 - v0) / accelToV1AtX0;
    if(timeToV1 < period) { //先判断快到达目标点的情况，要求稳定到点
        trajTime = timeToV1;
        trajAccel = copysign(accelToV1AtX0 * moveAccelFactor, -v0);
        return;
    }
    if(fabs(v0) + aMax * FRAME_PERIOD > flatVel && trajTimeFlat > period) {
        trajTime = trajTimeFlat + trajTimeDec;
        trajAccel = 0;
    }
    else if(trajTimeAcc < period && trajTimeDec == 0) {
        trajTime = trajTimeAcc;
        trajAccel = copysign(aMaxOri, v0);
    }
    else if(trajTimeAcc < period && trajTimeFlat < period && trajTimeDec > 0) {
        trajTime = trajTimeDec;
        trajAccel = copysign(dMaxOri, -v0);
    }
    else {
        trajTime = trajTimeAcc + trajTimeDec + trajTimeFlat;
        trajAccel = copysign(aMaxOri, v0);
    }
}

void BezierMotion::bezierMotion2d(const stateNew &start, const stateNew &target, const PlayerCapabilityT &capability, CVector &trajAccel, double &time) {
    CVector v0 = start.vel;
    CVector v1 = target.vel;
    CVector x0 = target.pos - start.pos;
    double vMax = capability.maxSpeed;
    double aMax = capability.maxAccel;
    double dMax = capability.maxDec;
    double xTime, xTimeAcc, xTimeDec, xTimeFlat;
    double yTime, yTimeAcc, yTimeDec, yTimeFlat;
    double coordinataAdjustAngle;
    double trajAccelX, trajAccelY;
    if(v1.mod() == 0)
        coordinataAdjustAngle = x0.dir();
    else coordinataAdjustAngle = v1.dir();

    x0 = x0.rotate(-coordinataAdjustAngle);
    v0 = v0.rotate(-coordinataAdjustAngle);
    v1 = v1.rotate(-coordinataAdjustAngle);

    bezierMotion1d(x0.x(), v0.x(), v1.x(), aMax, dMax, vMax, trajAccelX, xTime, xTimeAcc, xTimeDec, xTimeFlat);
    bezierMotion1d(x0.y(), v0.y(), v1.y(), aMax, dMax, vMax, trajAccelY, yTime, yTimeAcc, yTimeDec, yTimeFlat);

    trajAccel = CVector(trajAccelX, trajAccelY);
    if(trajAccel.mod()) {
        trajAccel = trajAccel.rotate(coordinataAdjustAngle);
    }
    if(xTime < 1e-5 || xTime > 50) xTime = 0;
    if(yTime < 1e-5 || yTime > 50) yTime = 0;
    time = xTime > yTime ? xTime : yTime;
}

void BezierMotion::bezierGotoPoint(const stateNew &start, const stateNew &target, const PlayerCapabilityT &capability, const double &accelFactor, const double &angleAccFactor, stateNew &nextFrame) {
    CVector trajAcel;
    double time;
    double deltaAngle = Utils::Normalize(target.orient - start.orient);
    double angleVel0 = start.rotVel;
    double angleVel1 = target.rotVel;
    double maxAngleVel = capability.maxAngularSpeed;
    double maxAngleAccel = capability.maxAngularAccel;
    double maxAngleDec = capability.maxAngularDec;
    double timeRotate, timeRotateAccel, timeRotateDec, timeRotateFlat, rotateAccel;
    this->moveAccelFactor = accelFactor;
    this->rotateAccelFactor = angleAccFactor;
    if(fabs(deltaAngle) < PI && start.rotVel > 0.7 * maxAngleVel)
        maxAngleVel *= 0.7;
    else if(fabs(deltaAngle) < PI / 2 && start.rotVel > 0.5 * maxAngleVel)
        maxAngleVel *= 0.5;


    isMovePlanner = true;
    bezierMotion2d(start, target, capability, trajAcel, time);
//    compute_motion_2d(start.pos - target.pos, start.vel, target.vel, capability.maxAccel,capability.maxDec, capability.maxSpeed, accelFactor, trajAcel, time);
    isMovePlanner = false;
    compute_motion_1d(-deltaAngle, angleVel0, angleVel1, maxAngleAccel, maxAngleDec, maxAngleVel, angleAccFactor, rotateAccel, timeRotate, timeRotateAccel, timeRotateDec, timeRotateFlat);

//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200,300),"GotoPoint", COLOR_RED);

    CVector vel = start.vel + trajAcel * FRAME_PERIOD;
    double angleVel = angleVel0 + rotateAccel * FRAME_PERIOD;
    if(vel.mod() > capability.maxSpeed) {
        vel = vel * capability.maxSpeed * vel.mod();
    }
    if(angleVel > maxAngleVel) {
        angleVel = maxAngleVel;
    }
    else if(angleVel < -maxAngleVel) {
        angleVel = -maxAngleVel;
    }
    CGeoPoint nextPosition = start.pos + Utils::Polar2Vector(vel.mod() * FRAME_PERIOD, vel.dir());
    double nextAngle = start.orient + angleVel * FRAME_PERIOD;
//    double t = std::max(time, timeRotate);

    nextFrame.orient = nextAngle;
    nextFrame.pos = nextPosition;
    nextFrame.rotVel = angleVel;
    nextFrame.vel = vel;
}
