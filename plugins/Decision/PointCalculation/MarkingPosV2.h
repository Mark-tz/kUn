#ifndef __MARKING_POS_V2_H__
#define __MARKING_POS_V2_H__

#include "AtomPos.h"
#include "singleton.h"
#include "DefPos1G2D.h"
#include <vector>

using namespace std;

namespace NameSpaceMarkingPosV2{
	extern bool DENY_LOG[Param::Field::MAX_PLAYER+1];
	extern bool BACK_LOG[Param::Field::MAX_PLAYER+1];
};

class CVisionModule;
class CMarkingPosV2 :public CDefPos1G2D
{
public:
	CMarkingPosV2();
	~CMarkingPosV2();
    virtual CGeoPoint generatePos(const CVisionModule* pVision);
	CGeoPoint getMarkingPos(const CVisionModule* pVision , const int pri);
	CGeoPoint getMarkingPosByAbsolutePri(const CVisionModule* pVision , const int pri);
	CGeoPoint getMarkingPosByNum(const CVisionModule* pVision , const int num);
	bool isNearestBallReceiverBeDenied(const CVisionModule* pVision);
	bool isInSpecialAreaBackLineMode(const CVisionModule *pVision,const int num);
	bool checkInSpecialArea_A(const CGeoPoint p,const CGeoPoint ballPos);
	void checkAllMarkingPos(const CVisionModule *pVision);
private:
	int oppPriority;
	int oppNum;
	int _logCycle;
	int logCycle[Param::Field::MAX_PLAYER+1];
	CGeoPoint markingPoint[Param::Field::MAX_PLAYER+1];
	vector<int> areaList;
};

typedef NormalSingleton< CMarkingPosV2 > MarkingPosV2;

#endif //_MARKING_POS_H_
