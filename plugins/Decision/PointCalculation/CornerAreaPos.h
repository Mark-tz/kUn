#ifndef _CORNER_AREA_POS_H_
#define _CORNER_AREA_POS_H_

#include <singleton.h>
#include "DefPos1G2D.h"

class CVisionModule;
class CCornerAreaPos:public CDefPos1G2D
{
public:
	CCornerAreaPos();
	~CCornerAreaPos();	
	virtual CGeoPoint generatePos(const CVisionModule* pVision);
	CGeoPoint getCornerAreaPos(const CVisionModule* pVision);

private:
    CGeoPoint _CAPos;
    CGeoPoint _lastCAPos;
	int _lastCycle;
};

typedef NormalSingleton< CCornerAreaPos > CornerAreaPos;

#endif //_CORNER_AREA_POS_H_
