#ifndef _ZMARKING_H_
#define _ZMARKING_H_
#include <skill/PlayerTask.h>

/************************************************************************/
/*盯人																    */
/* Modify by Wang in 2018.05.18																*/
/************************************************************************/
class CZMarking : public CStatedTask{
public:
	CZMarking();
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
protected:
	virtual void toStream(std::ostream& os) const { os << "Marking Defense"; }

private:
	int _lastCycle;
	int enemyNum;

private:
	bool needToUpdateTheirKicker;
	bool isMeCloserToBall;
	bool isTheirKickerPosSafe;
	bool isBallToEnemy;
};
#endif //_ZMARKING_H_