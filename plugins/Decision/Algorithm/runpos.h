#ifndef RUNPOS_H
#define RUNPOS_H
#include "singleton.h"
#include "geometry.h"
#include "VisionModule.h"

/*************************************************/
/*            calculate run pos module           */
/*************************************************/


class RunPos
{
public:
    RunPos();
    CGeoPoint runPos(int index) { return _runPos[index]; }
    void generateRunPos(const CVisionModule* pVision, double epsilon=0.1);
    double evaluateFunc(CGeoPoint candidate);
private:
    CGeoPoint _runPos[4];
    const CVisionModule* _pVision;
};
typedef NormalSingleton<RunPos> RunPosModule;
#endif // RUNPOS_H
