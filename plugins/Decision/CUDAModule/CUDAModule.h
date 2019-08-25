#ifdef USE_CUDA_MODULE
/**************************************
* CUDA C acceleration module
* Author: Wang Yun Kai
* Created Date: 2019/3/17
**************************************/
#ifndef __CUDA_MODULE_H__
#define __CUDA_MODULE_H__

#include "singleton.hpp"
#include "VisionModule.h"
#include <MultiThread.h>
#include "geometry.h"

typedef struct {
    double x, y;
} Vector;

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point Pos;
    Vector Vel;
    bool isValid;
} Player;

typedef struct {
    Point interPos;
    double interTime;
    double Vel;
    float dir;
    int playerIndex;
    double deltaTime;
    double Q;
} rType;

class CUDAModule{
public:
    CUDAModule();
    ~CUDAModule();
    void initialize(const CVisionModule *);
    ZSS_THREAD_FUNCTION void run();
    std::vector<rType> getPassPoints(void) const { return passPoints; }
    std::vector<rType> getChipPoints(void) const { return chipPoints; }
    CGeoPoint getBestFlatPass();
    CGeoPoint getBestChipPass();
    int getBestFlatPassNum();
    int getBestChipPassNum();
    double getBestFlatPassVel() { return bestFlatPassVel; }
    double getBestChipPassVel() { return bestChipPassVel; }
    void calculateBestPass();
    void setLeader(int _leader) { leader = _leader; }
private:
    CGeoPoint bestFlatPass;
    CGeoPoint bestChipPass;
    int bestFlatPassNum;
    int bestChipPassNum;
    double bestFlatPassVel;
    double bestChipPassVel;
    int leader;
    Player *players;
    Point *ball;
    const CVisionModule* pVision;
    std::thread *thread;
    std::vector<rType> passPoints;
    std::vector<rType> chipPoints;
    bool isValidPassLine(const CGeoPoint& p1, const CGeoPoint& p2);
};
typedef Singleton<CUDAModule> ZCUDAModule;
#endif //__CUDA_MODULE_H__
#endif // USE_CUDA_MODULE