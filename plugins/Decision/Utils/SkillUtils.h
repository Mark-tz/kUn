/**************************************
* Skill 通用函数模块
* Author: Wang
* Created Date: 2018/5/2
**************************************/
#ifndef _SKILL_UTILS_
#define _SKILL_UTILS_

#include "VisionModule.h"
#include <CMmotion.h>
#include <iostream>
#include "utils.h"
#include "singleton.hpp"
namespace ZBallState{
    const int Our = 0;
    const int Their = 1;
    const int Both = 2;
    const int OurHolding = 3;
    const int TheirHolding = 4;
    const int BothHolding = 5;
    const std::string toStr[6] = {"Our","Their","Both","OurHolding","TheirHolding","BothHolding"};
}
typedef int BallStateVar;
class SkillUtils{
public:
    SkillUtils();
    ~SkillUtils();

    //摩擦
    double FRICTION;

    //判断点是否在场地内, 第二个参数为边界缓冲
    bool IsInField(const CGeoPoint p, double buffer = 0);

    //判断点是否在场地内, 且不在禁区内， 第二个参数为边界缓冲
    bool IsInFieldV2(const CGeoPoint p, double buffer = 0);

    //判断球是否能走那么远距离
    bool IsBallReachable(double ballVel, double length, double friction);

    //获得我方车的截球时间
    double getOurInterTime(int);

    //获得敌方车的截球时间
    double getTheirInterTime(int);

    //获得我方车的截球点
    CGeoPoint getOurInterPoint(int);

    //获得敌方车的截球点
    CGeoPoint getTheirInterPoint(int);

    //假设自己以ballVel速度射出球到target点，计算是否有对方车能截到球
    bool isSafeShoot(const CVisionModule* pVision, double ballVel, CGeoPoint target);

    //获得敌方车预测截球时间
    double getPredictTime(int);

    //获得敌方车预测截球点
    CGeoPoint getPredictPoint(int);

    //计算截球信息和预测信息
    void run(const CVisionModule* pVision);

    //计算某辆车的截球时间和截球点,返回true代表能截球，返回false代表无法截球,responseTime为车截球缓冲时间，默认为0
    bool predictedInterTime(const CVisionModule* pVision, int robotNum, CGeoPoint& interceptPoint, double& interTime, double responseTime = 0);

    //计算敌方某辆车的截球时间和截球点
    bool predictedTheirInterTime(const CVisionModule* pVision, int robotNum, CGeoPoint& interceptPoint, double& interTime, double responseTime = 0);

    //计算对方某辆车的截球时间和截球点
    CGeoPoint predictedTheirInterPoint(CGeoPoint enemy, CGeoPoint ball);

    //
    double getOurBestInterTime();

    //
    double getTheirBestInterTime();

    //
    int getOurBestPlayer();

    //
    int getTheirBestPlayer();

    //
    std::string getBallStatus(){
        return ZBallState::toStr[ballState];
    }

    //计算immortalRush时间
    double getImmortalRushTime(const CVisionModule* pVision, int robotNum, CGeoPoint targetPos, double targetDir = 0);

    //计算marking 阻挡跑位点
    CGeoPoint getMarkingPoint(CGeoPoint markingPos, CVector markingVel, double aMax, double dMax, double aRotateMax, double vMax,CGeoPoint protectPos);

private:
    void calculateBallBelongs();

    //每帧获取inter有关的信息
    void generateInterInformation(const CVisionModule* pVision);

    //生成预测截球的有关信息
    void generatePredictInformation(const CVisionModule* pVision);

    //帧数
    int _lastCycle = 0;

    //所有我方车的截球点
    CGeoPoint ourInterPoint[Param::Field::MAX_PLAYER + 1];

    //所有我方截球时间
    double ourInterTime[Param::Field::MAX_PLAYER + 1];

    //所有敌方车的截球点
    CGeoPoint theirInterPoint[Param::Field::MAX_PLAYER + 1];

    //所有敌方截球时间
    double theirInterTime[Param::Field::MAX_PLAYER + 1];

    //预测静止球以最大速度射出、敌方车最大速度加速的截球时间
    double predictTheirInterTime[Param::Field::MAX_PLAYER + 1];

    //预测静止球以最大速度射出、敌方车最大速度加速的截球点
    CGeoPoint predictTheirInterPoint[Param::Field::MAX_PLAYER + 1];

    int ourBestInterRobot,theirBestInterRobot;

    BallStateVar ballState;
};
typedef Singleton<SkillUtils> ZSkillUtils;
#endif
