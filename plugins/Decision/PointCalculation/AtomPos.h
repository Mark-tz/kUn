#ifndef _ATOM_POS_H_
#define _ATOM_POS_H_

#include "geometry.h"

namespace Pos{
	const CGeoPoint invalidPos = CGeoPoint(9999,9999); ///<默认的错误点
}

class CVisionModule;
class CAtomPos
{
public:
	CAtomPos();
	virtual ~CAtomPos();
	CGeoPoint getPos();
	void setPos(const CGeoPoint& pos);
    void clearPos();
	virtual bool isAvailable();
	virtual void printDebug();
	virtual CGeoPoint generatePos(const CVisionModule* pVision) = 0;
private:
	CGeoPoint _pos;
};

#endif //_ATOM_POS_H_
