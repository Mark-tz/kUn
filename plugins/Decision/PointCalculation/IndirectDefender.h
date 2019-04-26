#ifndef _INDIRECT_DEFENDER_H_
#define _INDIRECT_DEFENDER_H_

#include "DefPos1G2D.h"
#include <singleton.h>
#include <vector>

class CVisionModule;
using namespace std;
typedef struct{
	CGeoPoint _Left;
	CGeoPoint _Right;
	double baseDir;
	double radius;
}KickOffArea;

typedef struct{
	CGeoPoint onePos;
	CGeoPoint anotherPos;
	CGeoPoint getOnePos(){return onePos;}
	CGeoPoint getAnotherPos(){return anotherPos;}
}TwoKickPos;

class CIndirectDefender:public CDefPos1G2D
{
public:
	CIndirectDefender();
	~CIndirectDefender();
	CGeoPoint getDefPos(const CVisionModule* pVision,double radius, CGeoPoint leftUp, CGeoPoint rightDown,int mode);

	TwoKickPos getTwoDefPos(const CVisionModule* pVision,double radius1,CGeoPoint left1,CGeoPoint right1,double radius2,CGeoPoint left2,CGeoPoint right2);

	void generateTwoDefPos(const CVisionModule* pVision);
	virtual CGeoPoint generatePos(const CVisionModule* pVision);
	CGeoPoint DefendPos(const CGeoPoint ballPos,const double dir,double radius);

	void FindMinMax(int num);
private:
	int _lastCycle;
	int _lastTwoKickCycle;
	double _targetDir[Param::Field::MAX_PLAYER+1];
	CGeoPoint _leftUp;
	CGeoPoint _rightDown;
	double _radius;
	int _mode;
	int minnum;
    int maxnum;
	TwoKickPos _twoKick;
	KickOffArea _oneArea;
	KickOffArea _anotherArea;
};

typedef NormalSingleton< CIndirectDefender > IndirectDefender;

#endif
