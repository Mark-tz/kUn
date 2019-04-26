#ifndef MESSIDECISION_H
#define MESSIDECISION_H
#include "VisionModule.h"
#include "singleton.h"
#include "WorldModel.h"

//enum leaderState{
//    ReceiveBall = 1,
//    PassBall = 2,
//    StealBall = 3,
//};

class CMessiDecision {
  public:
    CMessiDecision();
    void generateAttackDecision(const CVisionModule* pVision);

    bool messiRun() {
        return _messiRun;
    }

    int leaderNum() {
        return _leader;
    }
    int receiverNum() {
        return _receiver;
    }
    int attackerAmount() {
        return _attackerAmount;
    }
    string nextState() {
        return _state;
    }
    CGeoPoint passPos() {
        return _passPos;
    }
    CGeoPoint receiverPos() {
        return _receiverPos;
    }
    CGeoPoint leaderPos() {
        return _leaderPos;
    }
    CGeoPoint otherPos(int i) {
        return _otherPos[i - 1];
    }
    CGeoPoint goaliePassPos();
    void setMessiRun(bool lMessiRun) {
        _messiRun = lMessiRun;
        if(!_messiRun) reset();
    }
    bool isFlat() {
        return  _isFlat;
    }
    double passVel() {
        return _passVel;
    }
  private:
    int _leader;
    int _receiver;
    int _leaderPassStateCount;
    int _leaderStealStateCount;
    int _cycle;
    int _lastChangeLeaderCycle;
    int _lastUpdateRunPosCycle;
    int _lastCanShootCycle;
    int _lastAreaNum;
    int _attackerAmount;
    double _passVel;
    bool _messiRun;
    bool _ourBall;
    bool _theirBall;
    bool _both;
    bool _frared;
    bool _isFlat;
    string _state;
    string _laststate;
    CGeoPoint _passPos;
    CGeoPoint _receiverPos;
    CGeoPoint _leaderPos;
    CGeoPoint _otherPos[4];
    const CVisionModule* _pVision;
    void judgeState();
    void judgeBallState();
    void judgeAttackerAmount();
    void generateLeaderPos();
    void confirmLeader();
    void changeLeaderToReceiver();
    void testReceivePos();
    bool needReceivePos();
    bool needRunPos();
    void generateReceiverAndPos();
    void generateOtherRunPos();
    bool canShoot();
    void reset();
    int getEnemyAmountInArea(CGeoPoint center, int radius);
};
typedef NormalSingleton<CMessiDecision> MessiDecision;
#endif // MESSIDECISION_H
