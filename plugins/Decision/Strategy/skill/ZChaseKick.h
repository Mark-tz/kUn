#ifndef __ZCHASE_KICK_H__
#define __ZCHASE_KICK_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: ZChaseKick
* Description: 修改自极难维护但好用的ChaseKickV2
* Author: Wang Yunkai
* E-mail: w615349118@gmail.com
* Created Date: 2018.5.23
***********************************************************/

class CZChaseKick :public CStatedTask {
public:
	CZChaseKick();
	virtual void plan(const CVisionModule* pVision); 
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: ZChaseKick\n"; }

private:
	CPlayerCommand* _directCommand;	//直接发送命令
	int _lastCycle;
	int _stateCounter;
	int _goKickCouter;
	double _compensateDir;
};

#endif //__ZCHASE_KICK_H__