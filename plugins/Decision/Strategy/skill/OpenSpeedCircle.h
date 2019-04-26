#ifndef OPENSPEEDCIRCLE_H
#define OPENSPEEDCIRCLE_H

#include <skill/PlayerTask.h>

/************************************************************************/
/*              COpenSpeedCircle  OpenSpeed 4 Circle                    */
/************************************************************************/
class COpenSpeedCircle : public CPlayerTask {
public:
    COpenSpeedCircle();
    virtual void plan(const CVisionModule* pVision) {}
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
    virtual bool isEmpty() const { return false; }
};

#endif // OPENSPEEDCIRCLE_H
