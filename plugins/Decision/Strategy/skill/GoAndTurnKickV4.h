#pragma once
#include <skill/PlayerTask.h>
#include "VisionModule.h"

class CGoAndTurnKickV4 : public CStatedTask
{
public:
    CGoAndTurnKickV4();
    ~CGoAndTurnKickV4();
    virtual void plan(const CVisionModule* pVision);
    virtual	CPlayerCommand *execute(const CVisionModule* pVision);
protected:
    virtual void toStream(std::ostream& os) const { os << "GoAndTurnKick\n"; }

private:
    bool needdribble = false;
    bool needkick = false;
    bool chip = false;
    bool safeMode = false;
    int _new_status;
//    int _last_status;
    int getStaticDir(const CVisionModule * pVision, int staticDir);
};
