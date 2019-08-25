#ifndef __SKILL2010_CHASE_KICK_V2_H__
#define __SKILL2010_CHASE_KICK_V2_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: ChaseKickV2
* Description: 简单的追踢，考虑球速在内
* Author: applejian
* E-mail: tangwenjian001@163.com
* Created Date: 2010.6/7 2014/3/3
***********************************************************/

class CChaseKickV2 :public CStatedTask {
public:
	CChaseKickV2();
	virtual void plan(const CVisionModule* pVision); 
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: ChaseKickV2\n"; }

private:
	CPlayerCommand* _directCommand;	//直接发送命令
	int _lastCycle;
	int _stateCounter;
	int _goKickCouter;
	double _compensateDir;
};

#endif //__SKILL2010_CHASE_KICK_V1_H__