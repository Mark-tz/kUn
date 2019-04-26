#ifndef _GET_BALL_V4_H__
#define _GET_BALL_V4_H__
#include <skill/PlayerTask.h>

/**********************************************************
* Skill: GetBallV4
* Description:拿球第四版
***********************************************************/

class CGetBallV4 :public CStatedTask {
public:
	CGetBallV4();
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty()const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	int getStaticDir(const CVisionModule* pVision, int staticDir);
	void judgeMode(const CVisionModule* pVision);
	bool canShootBall(const CVisionModule* pVision);
	bool judgeShootMode(const CVisionModule* pVision);
protected:
	virtual void toStream(std::ostream& os) const { os << "Skill: GetBallV4\n"; }

private:
	int _lastCycle;
	int getBallMode;
    int lastGetBallMode;
	int cnt = 0;
	bool needdribble = false;
	bool needkick = false;
	bool chip = false;
	bool safeMode = false;
	bool isTouch = false;
	CGeoPoint targetPoint;
	CGeoPoint waitPoint;
    CGeoPoint ballLineProjection;
    //double meArriveTime = 9999;
    CGeoPoint interPoint;
    double interTime = 9999;
	double last_speed = 0;
};

#endif //_GET_BALL_V4_H__
