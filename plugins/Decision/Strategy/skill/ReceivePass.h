#ifndef _RECEIVE_PASS__
#define _RECEIVE_PASS__
#include <skill/PlayerTask.h>
class CReceivePass:public CStatedTask {
public:
	CReceivePass();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: ReceivePass\n"; }

private:
	int _lastCycle;
	int _lastRunner;
	CGeoPoint _mePos;
	CPlayerCommand * _directCommand;
};

#endif //_DRIBBLE_PULL__
