#ifndef _BALL_ADVANCE_DECISION_H_
#define _BALL_ADVANCE_DECISION_H_

#include "singleton.h"
#include "VisionModule.h"
#include "WorldModel.h"

namespace{
    enum {
        OURBALL = 0,
        THEIRBALL,
        STANDOFF
    };
}

class CBallAdvanceDecision {
private:
    bool canShoot();
    bool canShootReceiver();
	bool canLightKick();
	bool canLightChip();
	bool canPass();
	bool canWaitTouch();
    bool isBallMovingToMe();
    bool isSafePass();
	void confirmLeader();
	int _state;
    int _ballState;
	int _leader;
	int _receiver;
	int _lastCycle;
    int _lastKickCycle;
	int _lastBallArea;
	int _stateCounter;
	int _bestPlayerCount;
    int _reGenerateCount;
    int ballStateCount[3];
    int theirBallCount;
    int standOffCount;
    bool reGenerateFlag;
	bool ballTransit;
	bool ballTransitRecord;
	const CVisionModule* _pVision;
	const void update(const CVisionModule* pVision, int meNum) {
		_leader = meNum;
		_pVision = pVision;
	}
	void generateRunPosition();
	void generateReceiveBallPosition();
    void generateTouchPassPosition();
    CGeoPoint runPointCompute(int number,const vector<CGeoPoint>& targetPoint);
    CGeoPoint receiveBallPointCompute(int number,const vector<CGeoPoint>& targetPoint);
	double robotTimeCompute(int vehicleNumber);
    int getBallArea(CGeoPoint tempPos);
	struct AreaStatus {
		vector <CGeoRectangle> location;
		vector <CGeoPoint> targetPos;
		vector <bool> status;
		double lineAmount;
		double columnAmount;
	} area;
	const int State_Counter_Num = 10;
public:
    CBallAdvanceDecision();
    ~CBallAdvanceDecision();
public:
	string generateAttackDecision(const CVisionModule* pVision, int meNum);
    string getNormalPlayBallStatus(){
        return (_ballState == OURBALL) ? "ourBall" : (_ballState == THEIRBALL) ? "theirBall" : "standOff";
    }
};

typedef NormalSingleton< CBallAdvanceDecision > BallAdvanceDecision;

#endif

