#pragma once
#include <skill/PlayerTask.h>
#include "VisionModule.h"

/**********************************************************
* Skill: CInterceptBallV7
* Description:change from InterceptBallV6
* Author: Wang
* Created Date: 2018/5/1
***********************************************************/
class CInterceptBallV7 : public CStatedTask
{
public:
	CInterceptBallV7();
	~CInterceptBallV7();
	virtual void plan(const CVisionModule* pVision);
	virtual	CPlayerCommand *execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "InterceptBallV7\n"; }

private:
	CGeoPoint waitPoint;
	int getStaticDir(const CVisionModule * pVision, int staticDir);
};

