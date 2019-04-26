#pragma once
#include <skill/PlayerTask.h>
#include "VisionModule.h"

/**********************************************************
* Skill: CInterceptBallV7
* Description:change from InterceptBallV6
* Author: Wang
* Created Date: 2018/5/1
***********************************************************/
class CTouchKickV2 : public CStatedTask
{
public:
    CTouchKickV2();
    ~CTouchKickV2();
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
