#include "ShootRangeList.h"
#include "SituationJudge.h"
#include "BallStatus.h"
#include "GDebugEngine.h"
#include "gpuBestAlgThread.h"
#include <CMmotion.h>
#include <RobotCapability.h>
//#include <minwindef.h>
#include "BallAdvanceDecision.h"
#include "parammanager.h"
#include "SkillUtils.h"
#include "RobotSensor.h"

using namespace std;
namespace {
    bool PPDEBUG = false;
    bool NEW_MODE = true;
    bool SAFE_PASS = true;
    bool USE_TOUCH = true;
    bool USE_FORCESHOOT = true;
    bool USE_PANNINGSHOOT = true;
    bool USE_CIRCLEPASS = false;//true;
    bool USE_ZPASS = false;
	enum {
		BEGINNING = 1,
        ADVANCE,
		RUSH_TO_BALL,
		COMPUTE,
		LIGHT_KICK,
		LIGHT_CHIP,
		PASS,
		RECEIVEPASS,
        CIRCLEPASS,
        ZPASS,
        RECEIVE,
        SHOOT,
		RECEIVESHOOT,
        CIRCLESHOOT,
        PANNINGSHOOT,
        WAITTOUCH
	};
	const double CM_PREDICT_FACTOR = 1.5;

    const double weight1 = 0.25;//敌方到传球线距离的权值
    const double weight2 = 0.15;//敌方到接球点距离的权值
    const double weight3 = 0;//敌方到射门线距离的权值
    const double weight4 = 300;//射门角度的权值
    const double weight5 = -100;//接球射门角度的权值
	//阀值
    const double thresholdForEnemy2PassLineDist = 300;
    const double thresholdForEnemy2ShootLineDist = 300;
    const double thresholdForEnemy2PointDist = 300;
    const double thresholdForEnemy2MeDist = 300;
    const double slack = 0.5;
    const int maxStopBallSpeed = 650;
	CGeoPoint* runPos = GPUBestAlgThread::Instance()->runPos;
	CGeoPoint* confirmPos = GPUBestAlgThread::Instance()->confirmPos;
	int* vehicleNumber = GPUBestAlgThread::Instance()->number;
	CGeoPoint& passPos = GPUBestAlgThread::Instance()->shootPos;
    CGeoPoint& secondPassPos = GPUBestAlgThread::Instance()->assisterPos;
	bool& changeLeaderFlag = GPUBestAlgThread::Instance()->changeLeaderFlag;
	const CGeoRectangle* runArea = GPUBestAlgThread::Instance()->getRunArea();
	bool& changeLeaderOverFlag = GPUBestAlgThread::Instance()->changeLeaderOverFlag;
    int& kickPower = GPUBestAlgThread::Instance()->chipPower;
    int formation[13][3] = { {3,7,9},{8,4,9},{1,9,7},{3,8,9},{1,8,3},{1,8,7},{1,9,3},{1,3,9},{3,7,1},{5,7,9},{1,9,5},{4,5,6},{3,7,5} };
    double FRICTION;
    double powerRatio;
    bool TEST_PASS;
    bool IS_SIMULATION;
}

CBallAdvanceDecision::CBallAdvanceDecision(){
    if (IS_SIMULATION)
        ZSS::ZParamManager::instance()->loadParam(FRICTION,"AlertParam/Friction",80);
    else
        ZSS::ZParamManager::instance()->loadParam(FRICTION,"AlertParam/Friction4Sim",152);

    ZSS::ZParamManager::instance()->loadParam(TEST_PASS,"Test/NormalPlayPassTestPass",false);
    ZSS::ZParamManager::instance()->loadParam(IS_SIMULATION,"Alert/IsSimulation",false);

    powerRatio = IS_SIMULATION ? 1.4 : 1.7;
	const double areaLength = 50;
    const double minX = -100;
	const double maxX = 600;
	const double minY = -450;
	const double maxY = 450;
	const double lineAmount = (maxX - minX) / areaLength;
	const double columnAmount = (maxY - minY) / areaLength;
	area.location.push_back(CGeoRectangle(0, 0, 0, 0));
	area.targetPos.push_back(CGeoPoint(0,0));
	area.status.push_back(false);
	area.lineAmount = lineAmount;
	area.columnAmount = columnAmount;
	double x = maxX;
	double y = minY;
	for (int i = 1; i <= lineAmount; i++) {
		for (int j = 1; j <= columnAmount; j++) {
			area.location.push_back(CGeoRectangle(x, y, x - areaLength, y + areaLength));
			area.targetPos.push_back(CGeoPoint((2 * x - areaLength) / 2, (2 * y + areaLength) / 2));
			area.status.push_back(false);
			y += areaLength;
		}
		x -= areaLength;
		y = minY;
	}
    if (!USE_TOUCH)
        secondPassPos = CGeoPoint(600,0);
	ballTransit = true;
	changeLeaderOverFlag = false;
	_receiver = 999;
	_stateCounter = 0;
    for (int i = 0; i < 3; i++){
         ballStateCount[i] = 0;
    }
    theirBallCount = 0;
    standOffCount = 0;
	_lastCycle = 0;
    _lastKickCycle = 0;
    _lastBallArea = 1;
    reGenerateFlag = false;
}

CBallAdvanceDecision::~CBallAdvanceDecision() { 

}

string CBallAdvanceDecision::generateAttackDecision(const CVisionModule* pVision, int meNum) {
    //cout << vehicleNumber[0] << " " << vehicleNumber[1] << " " << vehicleNumber[2] << " " << vehicleNumber[3] << " " << vehicleNumber[4] << " " << vehicleNumber[5] << vehicleNumber[6] << " " << vehicleNumber[7] << endl;
	update(pVision, meNum);
	const MobileVisionT& ball = _pVision->Ball();
	const PlayerVisionT& me = _pVision->OurPlayer(_leader);
//	bool isBallNearMe = ball.Pos().dist(me.Pos()) < 35;
	bool needRushToBall = me.Pos().dist(ball.Pos()) > 60;
	bool ballIsKickedOut = false;
    double leaderTime;
    double minTime;
    int bestPlayer = ZSkillUtils::instance()->getOurBestPlayer();
    int ballArea = 999;
//    int reGenerateCount = 0;
    bool reset = false;
    string ballStatus = ZSkillUtils::instance()->getBallStatus();
    bool frared = RobotSensor::Instance()->IsInfraredOn(_leader);
    bool ourBall = (ballStatus == "Our" || ballStatus == "OurHolding");
    bool theirBall = (ballStatus == "Their" || ballStatus == "TheirHolding" || ballStatus == "Both");
//    bool standOff = !ourBall && !theirBall;
    int currentBallState = ourBall ? OURBALL : theirBall ? THEIRBALL : STANDOFF;
    int maxBallStateCount[3] = {15,15,15};
    //cout<<"currentBallState "<<currentBallState<<endl;
    if (NEW_MODE){
        for (int i = OURBALL ; i <= STANDOFF; i++){
            ballStateCount[i] = (currentBallState == i) ? 1 + ballStateCount[i] : 0;
            ballStateCount[i] = min(ballStateCount[i],maxBallStateCount[i]);
            if (ballStateCount[i] >= maxBallStateCount[i] && _ballState != i && _state!= RECEIVE && _state != RECEIVEPASS){
                if (PPDEBUG){
                    string state = (i == OURBALL) ? "OurBall" : (i == THEIRBALL) ? "TheirBall" : "StandOff";
                    cout<<"ballState change to "<< state <<endl;
                }
                reset = true;
                _ballState = i;
            }
        }
//        if (_ballState == OurBall && currentBallState != OurBall && _state != RUSH_TO_BALL && _state != ADVANCE){
//            theirBallCount++;
//            if (theirBallCount >= 15){
//                _ballState = THEIRBALL;
//                reset = true;
//                if (PPDEBUG){
//                    cout<<"ballState change to TheirBall*"<< endl;
//                }
//                theirBallCount = 0;
//            }
//        }
//        else{
//            theirBallCount = 0;
//        }
    }
    //cout<<ballStateCount[0]<<" "<<ballStateCount[1]<<" "<<ballStateCount[2]<<endl;
    //cout<<"currentBallState "<<currentBallState<<endl;
    if (changeLeaderOverFlag) {
        changeLeaderOverFlag = false;
        changeLeaderFlag = false;
    }
    leaderTime = ZSkillUtils::instance()->getOurInterTime(_leader);//robotTimeCompute(_leader);
    minTime = ZSkillUtils::instance()->getOurBestInterTime();
    int ourGoalie = vehicleNumber[7];
    if (leaderTime > minTime*1.2 && _state != RECEIVE && _state != RECEIVEPASS && bestPlayer != ourGoalie)
		_bestPlayerCount++;
	else
		_bestPlayerCount = 0;
    if (_bestPlayerCount >= 30) {
		reset = true;
	}
    if (reset) {
        if (PPDEBUG){
            cout << "reset bestPlayer is " << bestPlayer - 1 <<endl;
        }
        //cout<<ZSkillUtils::instance()->getOurInterTime(_leader)<<" "<< ZSkillUtils::instance()->getOurInterTime(bestPlayer) <<endl;
        _state = BEGINNING;
        _bestPlayerCount = 0;
        _reGenerateCount = 0;
        _receiver = 999;
        ballIsKickedOut = true;
        ballTransitRecord = false;
        _receiver = bestPlayer;
        theirBallCount = 0;
        standOffCount = 0;
        confirmLeader();
    }
	//cout << "out3 " << _leader << endl;
	// cout << "333bestplayer " << bestPlayer << endl;
	//cout << _bestPlayerCount << "_bestPlayerCount" << endl;
    if (_pVision->Cycle() <= Param::Vision::FRAME_RATE * 0.1 + 1){
        _state = BEGINNING;
        _ballState = OURBALL;
        _lastCycle = 0;
    }
	if ((_pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1)) {
		_state = BEGINNING;
		_bestPlayerCount = 0;
        _reGenerateCount = 0;
		_receiver = 999;
        ballIsKickedOut = true;
		ballTransitRecord = false;
		changeLeaderFlag = false;
        changeLeaderOverFlag = false;
        _lastBallArea = getBallArea(ball.Pos());
        theirBallCount = 0;
        standOffCount = 0;
        //generateRunPosition();
	}
    ballArea = getBallArea(ball.Pos());
    if (ballArea != _lastBallArea &&  (_state == RUSH_TO_BALL || _state == COMPUTE)){
        _reGenerateCount ++;
        if (_reGenerateCount >= 60){
            if (PPDEBUG)
                cout<<"regen "<<"ballArea "<<ballArea<<" _lastBallArea "<<_lastBallArea<<" _state "<<_state<<endl;
            reGenerateFlag = true;
            generateRunPosition();
            _reGenerateCount = 0;
        }
    }else{
        _reGenerateCount = 0;
    }
    ballTransit = BallStatus::Instance()->IsBallKickedOut(_leader) && (ball.Vel().mod() > 100);
	if (!ballTransit)
		ballTransitRecord = true;
    if (ballTransitRecord && ballTransit && _pVision->Cycle() - _lastKickCycle > 30) {
        ballIsKickedOut = true;
		ballTransitRecord = false;
        _lastKickCycle = _pVision->Cycle();
	}
    if (ballIsKickedOut) {
        if (PPDEBUG)
            cout << "ball is kickedout " <<_pVision->Cycle()<<endl;
        if (_state == RECEIVEPASS)
            passPos = secondPassPos;
        generateRunPosition();
    }
	int new_state = _state;
	switch (new_state) {
	case BEGINNING:
        new_state = COMPUTE;
		break;
    case ADVANCE:
        if (currentBallState == STANDOFF){
            standOffCount++;
        }
        else{
            standOffCount = 0;
        }
        if (standOffCount > 5 && me.Pos().x() > -200){
            generateReceiveBallPosition();
            if (USE_CIRCLEPASS && frared && canPass()){
                new_state = CIRCLEPASS;
            }
            else if (USE_PANNINGSHOOT && frared){
                new_state = PANNINGSHOOT;
            }
            standOffCount = 0;
            _stateCounter = 0;
        }
        break;
	case RUSH_TO_BALL:
        if (ballStatus == "OurHolding")
			new_state = COMPUTE;
		break;
	case COMPUTE:
        if (_ballState == OURBALL || !NEW_MODE){
            if (ballStatus != "OurHolding")
                new_state = RUSH_TO_BALL;
            else if (!canShoot()) {
                if (canLightKick())
                    new_state = LIGHT_KICK;
                else if (canLightChip())
                    new_state = LIGHT_CHIP;
                else {
                    generateReceiveBallPosition();
                    if (canPass()) {
                        if (!isSafePass()){
                            if (USE_CIRCLEPASS)
                                new_state = CIRCLEPASS;
                            else if (USE_ZPASS)
                                new_state = ZPASS;
                            else
                                new_state = PASS;
                        }
                        else{
                            new_state = PASS;
                        }
                        _stateCounter = 0;
                    }
                    else {
                        if (me.Pos().x() > 0){
                            new_state = PANNINGSHOOT;
                        }
                        else
                            new_state = LIGHT_CHIP;
                    }
                }
            }
            else
                new_state = SHOOT;
        }
        else if (_ballState == THEIRBALL){
            new_state = RUSH_TO_BALL;
            standOffCount = 0;
        }
        else{
            new_state = ADVANCE;
            standOffCount = 0;
        }
		break;
	case SHOOT:
		if (ballIsKickedOut) {
			new_state = COMPUTE;
			_stateCounter = 0;
		}

//		else if (!canShoot()) {
//			new_state = COMPUTE;
//		}
		break;
	case LIGHT_KICK:
		if (ballIsKickedOut) {
			new_state = COMPUTE;
			_stateCounter = 0;
		}
		else if (needRushToBall) {
			new_state = RUSH_TO_BALL;
		}
		break;
	case LIGHT_CHIP:
		if (ballIsKickedOut) {
			new_state = COMPUTE;
			_stateCounter = 0;
		}
		else if (needRushToBall) {
			new_state = RUSH_TO_BALL;
		}
		break;
	case PASS:
		if (ballIsKickedOut) {
            if (fabs(Utils::Normalize(me.Dir() - (passPos - me.Pos()).dir()) < 4 * Param::Math::PI / 180)) {
                int attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision);
                int receiveNumber;
                for (int i = 1; i < attackerAmount; i++){
                    if (_receiver == vehicleNumber[i]){
                        receiveNumber = i;
                        break;
                    }
                }
                //runPos[receiveNumber - 1] = passPos;
            }
           if (canWaitTouch() && canShootReceiver()) {
				new_state = WAITTOUCH;
				_stateCounter = 0;
			}
			else {
				new_state = RECEIVE;
				_stateCounter = 0;
			}
			confirmLeader();
		}
		else if (needRushToBall) {
			new_state = COMPUTE;
		}
        //else if (me.Pos().dist(_pVision->OurPlayer(_receiver).Pos()) < 150){
            //generateReceiveBallPosition();
        //}
		break;
    case ZPASS:
        if (ballIsKickedOut) {
//            if (fabs(Utils::Normalize(me.Dir() - (passPos - me.Pos()).dir()) < 4 * Param::Math::PI / 180)) {
//                int attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision, _leader);
//                int receiveNumber;
//                for (int i = 1; i < attackerAmount; i++){
//                    if (_receiver == vehicleNumber[i]){
//                        receiveNumber = i;
//                        break;
//                    }
//                }
//                //runPos[receiveNumber - 1] = passPos;
//            }
           if (canWaitTouch() && canShootReceiver()) {
                new_state = WAITTOUCH;
                _stateCounter = 0;
            }
            else {
                new_state = RECEIVE;
                _stateCounter = 0;
            }
            confirmLeader();
        }
        else if (needRushToBall) {
            new_state = COMPUTE;
        }
        break;
    case CIRCLEPASS:
        if (ballIsKickedOut) {
           if (canWaitTouch() && canShootReceiver()) {
                new_state = WAITTOUCH;
                _stateCounter = 0;
            }
            else {
                new_state = RECEIVE;
                _stateCounter = 0;
            }
            confirmLeader();
        }
        else if (needRushToBall) {
            new_state = COMPUTE;
        }
        break;
	case RECEIVE:
        if (!canShoot() && USE_TOUCH) {
            generateTouchPassPosition();
            if (canPass()){
                new_state = RECEIVEPASS;
                _stateCounter = 0;
            }
        }
        if (!isBallMovingToMe()) {
            if (ballStatus == "OurHolding") {
				if (canShoot()) {
                    new_state = SHOOT;
					_stateCounter = 0;
				}
				else {
					generateReceiveBallPosition();
					if (canPass()) {
                        if (isSafePass()){
                            new_state = PASS;
                            _stateCounter = 0;
                        }
                        else if (USE_ZPASS){
                            new_state = ZPASS;
                            _stateCounter = 0;
                        }
                        else if (USE_CIRCLEPASS){
                            new_state = CIRCLEPASS;
                            _stateCounter = 0;
                        }
                        else{
                            new_state = PASS;
                            _stateCounter = 0;
                        }
					}
                    else{
                        new_state = COMPUTE;
                    }
				}
			}
			else{
				new_state = COMPUTE;
			}
		}
		break;
	case RECEIVEPASS:
        if (ballIsKickedOut) {
            if (canWaitTouch() && canShootReceiver()) {
                new_state = WAITTOUCH;
                _stateCounter = 0;
            }
            else {
                new_state = RECEIVE;
                _stateCounter = 0;
            }
            confirmLeader();
        }
        else if (!isBallMovingToMe() && needRushToBall){
            new_state = COMPUTE;
        }
		break;
	case RECEIVESHOOT:
		if (ballIsKickedOut) {
			new_state = COMPUTE;
			_stateCounter = 0;
		}
//		else if (!canShoot()) {
//			new_state = COMPUTE;
//		}
		break;
	case WAITTOUCH:
        if (!canShoot()  && USE_TOUCH && false) {
            generateTouchPassPosition();
            if (canPass()){
                new_state = RECEIVEPASS;
                _stateCounter = 0;
            }else{
                new_state = RECEIVE;
            }
		}
        if (ballIsKickedOut || !isBallMovingToMe()) {
			new_state = COMPUTE;
			_stateCounter = 0;
		}
		break;
    case PANNINGSHOOT:
        if (ballIsKickedOut) {
//           if (canWaitTouch() && canShootReceiver()) {
//                new_state = WAITTOUCH;
//                _stateCounter = 0;
//            }
//            else {
//                new_state = RECEIVE;
//                _stateCounter = 0;
//            }
//            confirmLeader();
            new_state = COMPUTE;
            _stateCounter = 0;
        }
        else if (!frared) {
            new_state = COMPUTE;
        }
        break;
	default:
		new_state = COMPUTE;
		break;	
	}
	if (_state == BEGINNING) {
		_state = new_state;
	}
	else {
		if (_stateCounter == 0) {
			if (PPDEBUG)
				cout << "change to " << new_state << endl;
			_state = new_state;
			_stateCounter++;
		}
		else {
			if (new_state == _state) {
				_stateCounter = min(State_Counter_Num, _stateCounter + 1);
			}
			else {
				_stateCounter = max(0, _stateCounter - 1);
			}
		}
	}
	string decision;
	switch (_state) {
	case BEGINNING:
		decision = "RUSH_TO_BALL";
		break;
    case ADVANCE:
        decision = "Advance";
        break;
	case RUSH_TO_BALL:
		decision = "GetBall";
		break;
	case COMPUTE:
		decision = "Compute";
		break;
	case SHOOT:
		decision = "Shoot";
		break;
	case LIGHT_KICK:
		decision = "LightKick";
		break;
	case LIGHT_CHIP:
		decision = "LightChip";
		break;
	case PASS:
		decision = "Pass";
		break;
    case ZPASS:
        decision = "ZPass";
        break;
    case CIRCLEPASS:
        decision = "CirclePass";
        break;
	case RECEIVE:
		decision = "Receive";
		break;
	case RECEIVEPASS:
		decision = "ReceivePass";
		break;
	case RECEIVESHOOT:
		decision = "ReceiveShoot";
		break;
	case WAITTOUCH:
		decision = "WaitTouch";
		break;
    case PANNINGSHOOT:
        decision = "PanningShoot";
        break;
	default:
		decision = "Shoot";
		break;
	}
    //f (ballIsKickedOut && !changeLeaderFlag) {
        //generateRunPosition();
    //}
	_lastCycle = _pVision->Cycle();
	return decision;
}

bool CBallAdvanceDecision::canShoot() {
    if (TEST_PASS)
		return false;
    const PlayerVisionT& me = _pVision->OurPlayer(_leader);
    CGeoPoint goal = CGeoPoint(600,0);
    CGeoPoint leftGoal = CGeoPoint(600,-60);
    CGeoPoint rightGoal = CGeoPoint(600,60);
    double meToGoal = me.Pos().dist(goal);
    double meToLeftGoal = (me.Pos() - leftGoal).dir();
    double meToRightGoal = (me.Pos() - rightGoal).dir();
    double shootDir = fabs(Utils::Normalize(meToLeftGoal - meToRightGoal));
	const MobileVisionT& ball = _pVision->Ball();
    CShootRangeList shootRangeList(_pVision, _leader, _pVision->OurPlayer(_leader).Pos());
    const CValueRange* bestRange = NULL;
    const CValueRangeList& shootRange = shootRangeList.getShootRange();
    const double minShootDir = 5 * Param::Math::PI / 180;
	double sizeOfDir;
	if (shootRange.size() > 0 && ball.X()>0) {
		bestRange = shootRange.getMaxRangeWidth();
		sizeOfDir = bestRange->getSize();
		if (sizeOfDir > minShootDir) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
        if (shootDir >= 0.6 && meToGoal <= 300 && USE_FORCESHOOT)
            return true;
		return false;
	}
}

bool CBallAdvanceDecision::canShootReceiver() {
    if (TEST_PASS)
        return false;
//    const PlayerVisionT& me = _pVision->OurPlayer(_receiver);
    const MobileVisionT& ball = _pVision->Ball();
    CShootRangeList shootRangeList(_pVision, _receiver, _pVision->OurPlayer(_receiver).Pos());
    const CValueRange* bestRange = NULL;
    const CValueRangeList& shootRange = shootRangeList.getShootRange();
    const double minShootDir = 6 * Param::Math::PI / 180;
    double sizeOfDir;
    if (shootRange.size() > 0 && ball.X()>0) {
        bestRange = shootRange.getMaxRangeWidth();
        sizeOfDir = bestRange->getSize();
        if (sizeOfDir > minShootDir) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

bool CBallAdvanceDecision::canWaitTouch() {
    //if (TEST_PASS)
        //return false;
	CShootRangeList shootRangeList(_pVision, _receiver, passPos);
	const CValueRange* bestRange = NULL;
	const CValueRangeList& shootRange = shootRangeList.getShootRange();
    CGeoPoint theirGoal = CGeoPoint(600, 0);
    double _raw_kick_dir = (theirGoal - passPos).dir();
	double determindir;
	if (shootRange.size() > 0) {
		bestRange = shootRange.getMaxRangeWidth();
		if (bestRange && bestRange->getWidth() > 0) {	// 要求射门空档足够大
			_raw_kick_dir = bestRange->getMiddle();
		}
		double metoballdir = (_pVision->Ball().Pos() - passPos).dir();
		determindir = fabs(Utils::Normalize(metoballdir - _raw_kick_dir));
	}
    if ((determindir * 180 / Param::Math::PI) < 65) {
		return true;
	}
	else
		return false;
}

void CBallAdvanceDecision:: confirmLeader() {
//    if (PPDEBUG){
//        cout<<_leader - 1 <<" change  to "<<_receiver-1<<endl;
//    }
    double receiverDist = 9999;
    if (_state == PASS)
        receiverDist = _pVision->OurPlayer(_receiver).Pos().dist(passPos);
    else if (_state == RECEIVEPASS)
        receiverDist = _pVision->OurPlayer(_receiver).Pos().dist(secondPassPos);

    for (int i = 1; i <= 3; i++) {
        const PlayerVisionT& me = _pVision->OurPlayer(vehicleNumber[i]);
        if (vehicleNumber[i] != _receiver && me.Valid())
        {
            double myDist = 9999;
            if (_state == PASS)
                myDist = me.Pos().dist(passPos);
            else if (_state == RECEIVEPASS)
                myDist = me.Pos().dist(secondPassPos);

            if (myDist < receiverDist){
                receiverDist = myDist;
                _receiver = vehicleNumber[i];
            }
        }
    }
	confirmPos[0] = _pVision->OurPlayer(_receiver).Pos();
	int count = 1;
    int attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision);
    for (int i = 0; i < attackerAmount; i++) {
		if (confirmPos[0].dist(_pVision->OurPlayer(vehicleNumber[i]).Pos()) > 10) {
			confirmPos[count] = _pVision->OurPlayer(vehicleNumber[i]).Pos();
			count++;  
		}
	}
	changeLeaderFlag = true;
}

bool CBallAdvanceDecision::canLightKick() {
	return false;
	const MobileVisionT& ball = _pVision->Ball();
	const int frontLineX = 100;
//	bool excuteLightKick = true;
	if (ball.X() < frontLineX) {
//		const MobileVisionT& ball = _pVision->Ball();
		const PlayerVisionT& me = _pVision->OurPlayer(_leader);
		const double determindist = 100;
		double closestDist = 9999;
		for (int i = 1; i <= Param::Field::MAX_PLAYER; i++) {
			if (_pVision->TheirPlayer(i).Valid()) {
				double dirMe2Goal = (CGeoPoint(Param::Field::PITCH_LENGTH / 2.0, 0) - me.Pos()).dir();
//				double dirMe2Ball = (ball.Pos() - me.Pos()).dir();
				double dirMe2Enemy = (_pVision->TheirPlayer(i).Pos() - me.Pos()).dir();
				double different1 = fabs(Utils::Normalize(dirMe2Goal - dirMe2Enemy));
//				double different2 = fabs(Utils::Normalize(dirMe2Ball - dirMe2Enemy));
				closestDist = me.Pos().dist(_pVision->TheirPlayer(i).Pos());
				if (different1 <= Param::Math::PI / 2) {
					if (closestDist < determindist) {
						return false;
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool CBallAdvanceDecision::canLightChip() {
	return false;
}

bool CBallAdvanceDecision::canPass() {
	if (_receiver >= 1 && _receiver <= Param::Field::MAX_PLAYER) {
		return true;
	}
	/*int attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision, _leader);
	if (_receiver >= 1 && _receiver <= Param::Field::MAX_PLAYER) {
		runPos[0] = _pVision->OurPlayer(_receiver).Pos();
		int count = 1;
		for (int i = 0; i < attackerAmount; i++) {
			if (i != _receiver) {
				runPos[count] = _pVision->OurPlayer(vehicleNumber[i]).Pos();
				count++;
			}
		}
		//generateRunPosition();
		return true;
	}*/
	return false;
}

bool CBallAdvanceDecision::isBallMovingToMe() {
	// 判断球是否向我而来
	const MobileVisionT& ball = _pVision->Ball();
    const PlayerVisionT& me = _pVision->OurPlayer(_leader);
	const CGeoPoint& ballPos = ball.Pos();
	const double MIN_BALL_MOVING_VEL = 40;
	const double ballVelMod = ball.Vel().mod();
	const double ballVelDir = ball.Vel().dir();
    const double passPosToBallDir = (passPos - ballPos).dir();
    const double meToBallDir = (me.Pos() - ballPos).dir();
    const double diffBetweenBallVelDirAndPassPosToBallDir = Utils::Normalize(ballVelDir - passPosToBallDir);
    const double diffBetweenBallVelDirAndMeToBallDir = Utils::Normalize(ballVelDir - meToBallDir);
	bool isBallMovingToMe = false;
    if (ballVelMod > MIN_BALL_MOVING_VEL && (fabs(diffBetweenBallVelDirAndPassPosToBallDir) < Param::Math::PI / 2 || fabs(diffBetweenBallVelDirAndMeToBallDir) < Param::Math::PI / 2))
		isBallMovingToMe = true;
	//if (!isBallMovingToMe)
		//cout << isBallMovingToMe << "isBallMovingToMe" << diffBetweenBallVelDirAndMeToBallDir <<"diffBetweenBallVelDirAndMeToBallDir"<<endl;
	//cout << "moving to me ： " << isBallMovingToMe << endl;
	return isBallMovingToMe;
}

bool CBallAdvanceDecision::isSafePass() {
    double theirInterTime = ZSkillUtils::instance()->getTheirBestInterTime();
    return theirInterTime > 0.8;
}

void CBallAdvanceDecision::generateReceiveBallPosition() {
    if (PPDEBUG)
		cout << "generateReceivePos" << endl;
	const MobileVisionT& ball = _pVision->Ball();
    const int minPassDist = 150;
	vector <CGeoPoint> tempPoint;
	vector <CGeoPoint> receivePoint;
    int attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision);
    double maxPlayerScore = -99999;
	int maxPointSize = -1;
	int pointCount;
	_receiver = 999;
    //cout << vehicleNumber[0]-1 << "  " << vehicleNumber[1]-1<< "  " << vehicleNumber[2]-1 << "  " << vehicleNumber[3]-1 << endl;
	if (attackerAmount == 1 && PPDEBUG)
		cout << "attackerAmount is " << attackerAmount << endl;
	for (int i = 1; i < attackerAmount; i++) {
        bool canSafePass = true;
		pointCount = 0;
        const PlayerVisionT& me = _pVision->OurPlayer(vehicleNumber[i]);
        if (me.Valid()){
            for (int j = 1; j < area.location.size(); j++) {
                bool bestToPoint = true;
                double myTime = predictedTime(me, area.targetPos[j]);
//                for(int k = 1; k < attackerAmount; k++){
//                    const PlayerVisionT& teamMate = _pVision->OurPlayer(vehicleNumber[k]);
//                    double teamMateTime = predictedTime(teamMate, area.targetPos[j]);
//                    if (teamMateTime < myTime){
//                        bestToPoint = false;
//                        break;
//                    }
//                }
                double myDist = me.Pos().dist(area.targetPos[j]);
                for(int k = 1; k < attackerAmount; k++){
                    const PlayerVisionT& teamMate = _pVision->OurPlayer(vehicleNumber[k]);
                    double teamMateDist = teamMate.Pos().dist(area.targetPos[j]);
                    if (teamMateDist < myDist){
                        bestToPoint = false;
                        break;
                    }
                }
                if (bestToPoint){
                    double minAnemyTime = 9999;// = ZSkillUtils::instance()->getTheirBestInterTime();
                    for (int k = 1; k <= Param::Field::MAX_PLAYER; k++) {
                        const PlayerVisionT& anemy = _pVision->TheirPlayer(k);
                        if (anemy.Valid()) {
                            double anemyTime = predictedTime(anemy, area.targetPos[j]);
                            if (anemyTime < minAnemyTime)
                                minAnemyTime = anemyTime;
                            /*(CGeoSegment passLine = CGeoSegment(ball.Pos(), me.Pos());
                            if (passLine.IsPointOnLineOnSegment(passLine.projection(anemy.Pos()))) {
                                double dist = anemy.Pos().dist(passLine.projection(anemy.Pos()));
                                if (dist < 50) {
                                    canFlatPassTo = false;
                                }
                            }*/
                        }
                    }
                    double ball2Target = ball.Pos().dist(area.targetPos[j]);
                    /*double ballspeed = ball2Target * 1 + 100;
                    if (ballspeed < 200) {
                        ballspeed = 200;
                    }
                    else if (ballspeed > 550) {
                        ballspeed = 550;
                    }
                    double ballPassTime;
                    if (ballspeed * ballspeed - FRICTION * ball2Target > 0) {
                        ballPassTime = 2 * (-ballspeed + sqrt(ballspeed * ballspeed - FRICTION * ball2Target)) / (-FRICTION);
                    }
                    else {
                        ballPassTime = -1;
                    }*/
                    double ballPassTime = myTime + slack;
                    double acc = (-FRICTION) / 2;
                    double ballSpeed = (ball2Target - acc * ballPassTime * ballPassTime / 2) / ballPassTime * powerRatio;
                    bool canNotPass = false;
                    if (ballSpeed > maxStopBallSpeed){
                        ballSpeed = 650;
                        if (ballSpeed * ballSpeed - FRICTION * ball2Target > 0) {
                            ballPassTime = 2 * (-ballSpeed + sqrt(ballSpeed * ballSpeed - FRICTION * ball2Target)) / (-FRICTION);
                        }
                        else {
                            ballPassTime = 9999;
                        }
                        ballPassTime += slack;
                    }
                    if (ballPassTime * ballPassTime > -2 * acc * ball2Target){
                       canNotPass = true;
                    }
                    //cout<<"ballSpeed "<<ballSpeed<<endl;
                    canSafePass = ZSkillUtils::instance()->isSafeShoot(_pVision,ballSpeed,area.targetPos[j]);
                    if (SAFE_PASS && !canSafePass){
                       canNotPass = true;
                    }
//                    if (ballPassTime >= minAnemyTime){
//                        cout<< "1 j= "<<j<< " number= "<< vehicleNumber[i] -1 <<endl;
//                    }
//                    if (Utils::InTheirPenaltyArea(area.targetPos[j], 10)){
//                        cout<<"3 j= "<<j<< " number= "<< vehicleNumber[i] -1 <<endl;
//                    }
//                    if (Utils::OutOfField(area.targetPos[j])){
//                        cout<<"4 j= "<<j<< " number= "<< vehicleNumber[i] -1 <<endl;
//                    }
//                    if (ball.Pos().dist(area.targetPos[j]) <= minPassDist){
//                         cout<<"5 j= "<<j<< " number= "<< vehicleNumber[i] -1 <<endl;
//                    }
//                    if (canNotPass){
//                         cout<<"6 j= "<<j<< " number= "<< vehicleNumber[i] -1 <<endl;
//                    }
                    if ((ballPassTime < minAnemyTime * 0.9) && !Utils::InTheirPenaltyArea(area.targetPos[j], 10) && !Utils::OutOfField(area.targetPos[j]) && ball.Pos().dist(area.targetPos[j]) > minPassDist && !canNotPass) {
                        area.status[j] = true;
                        tempPoint.push_back(area.targetPos[j]);
                        //GDebugEngine::Instance()->gui_debug_x(area.targetPos[j],0);
                        //GDebugEngine::Instance()->gui_debug_x(area.targetPos[j],1);
                        pointCount++;
                    }
                    else {
                        area.status[j] = false;
                    }
                }
            }
            if ((int)tempPoint.size()) {
                CGeoPoint theirGoal = CGeoPoint(600, 0);
                double meToTheirGoal = me.Pos().dist(theirGoal);
                double ballPassDist = me.Pos().dist(ball.Pos());
                double playerScore = pointCount * 10 - meToTheirGoal * 2 / 3 - ballPassDist * 2 / 4.5;
                //cout<<"pointCount "<<pointCount<<" meToTheirGoal "<<meToTheirGoal<<" canFlatPassTo "<<canFlatPassTo<<" ballPassDist "<<ballPassDist<<endl;
                //cout<<"playerScore "<<playerScore<< " "<<vehicleNumber[i]-1 <<endl;
                if (playerScore > maxPlayerScore) {
                    if (ball.Pos().dist(_pVision->OurPlayer(vehicleNumber[i]).Pos()) > minPassDist) {
                        //cout << vehicleNumber[_receiver]<<" " <<_pVision->OurPlayer(vehicleNumber[_receiver]).Pos().dist(theirGoal) << " last dist " << vehicleNumber[vehicleNumber[i]] << " " << _pVision->OurPlayer(vehicleNumber[i]).Pos().dist(theirGoal) << " current dist" << endl;
                        receivePoint = tempPoint;
                        _receiver = i;
                        maxPointSize = pointCount;
                        maxPlayerScore = playerScore;
                        //cout << pointCount << " pointCount " << maxPointSize << endl;
                        //cout << "change "<<_receiver << " to " << vehicleNumber[i] << endl;
                    }
                }
            }
        }
        //cout << pointCount << " pointCount " << vehicleNumber[i] - 1 << endl;
		tempPoint.clear();
	}
	//cout << "-------------------------------" << endl;
	int receiver = 1;
	if (_receiver != 999) {
//        if (true)
//            cout << "generateReceiver " << vehicleNumber[_receiver]-1 << endl;
		receiver = _receiver;
        runPos[receiver - 1] = receiveBallPointCompute(vehicleNumber[receiver], receivePoint);
        passPos = runPos[receiver - 1];
//        GDebugEngine::Instance()->gui_debug_msg(passPos, "D", COLOR_BLUE);
//        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100,100), QString("%1 %2").arg(passPos.x()).arg(passPos.y()).toLatin1());
//        qDebug() << "Best receive pos: " << runPos->x() << " " << runPos->y();
        //cout<<"make it "<<vehicleNumber[receiver] - 1<<" "<<runPos[receiver - 1]<<endl;
        //passPos = receiveBallPointCompute(vehicleNumber[receiver], receivePoint);
		_receiver = vehicleNumber[_receiver];
        double myTime = predictedTime(_pVision->OurPlayer(_receiver), passPos);
        double ball2Target = ball.Pos().dist(passPos);
        double ballPassTime = myTime + slack;
        double acc = (-FRICTION) / 2;
        double ballspeed = (ball2Target - acc * ballPassTime * ballPassTime / 2) / ballPassTime;
        kickPower = (ballspeed * powerRatio > maxStopBallSpeed) ? 650 : ballspeed * powerRatio;
        //cout<<"kickPower "<<kickPower<<endl;
//        bool canSafePassTo = ZSkillUtils::instance()->isSafeShoot(_pVision,kickPower,passPos);
	}
	else {
        CGeoPoint theirGoal = CGeoPoint(600,0);
//        qDebug() << "Goal is (600,0)";
        passPos = theirGoal;
        kickPower = 650;
	}
    //secondPassPos = CGeoPoint(600,0);
	//_receiver = vehicleNumber[_receiver];
	/*runPos[receiver-1] = receiveBallPointCompute(vehicleNumber[receiver], receivePoint);
	passPos = runPos[receiver];
	for (int i = 0; i < attackerAmount - 1; i++) {
	//if (i != _receiver)
	//runPos[i] = _pVision->OurPlayer(vehicleNumber[i]).Pos();
	}*/
}

CGeoPoint CBallAdvanceDecision::receiveBallPointCompute(int number,const vector<CGeoPoint>& targetPoint) {
    if (!(int) targetPoint.size()) return CGeoPoint(600, 0);
	const PlayerVisionT& me = _pVision->OurPlayer(number);
    const MobileVisionT& ball = _pVision->Ball();
	int bestPointNumber;
    double maxPointScore = -0xffff;
	for (int i = 0; i < targetPoint.size(); i++) {
		//射门角，接球角大小
        CShootRangeList shootRangeList(_pVision, number, targetPoint[i]);
        const CValueRange* bestRange = NULL;
        const CValueRangeList& shootRange = shootRangeList.getShootRange();
        double sizeOfDir;
        double kick_dir;
        double determindir;
        double metoballdir = (ball.Pos() - targetPoint[i]).dir();
//        double ball2PointDist = ball.Pos().dist(targetPoint[i]);
		if (shootRange.size() > 0) {
			bestRange = shootRange.getMaxRangeWidth();
			sizeOfDir = bestRange->getSize();
			kick_dir = bestRange->getMiddle();
			determindir = fabs(Utils::Normalize(metoballdir - kick_dir));
		}
		else {
			sizeOfDir = 0;
			kick_dir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0) - targetPoint[i]).dir();
			determindir = fabs(Utils::Normalize(metoballdir - kick_dir));
		}
		//
        double dist;
		double enemy2PointDist, enemy2MeDist, enemy2ShootLineDist, enemy2PassLineDist;
		enemy2PointDist = enemy2MeDist = enemy2ShootLineDist = enemy2PassLineDist = 9999;
		int enemyNumRecord;
		CGeoLine shootLine(targetPoint[i], kick_dir);
		for (int j = 1; j <= Param::Field::MAX_PLAYER; j++) {
			if (_pVision->TheirPlayer(j).Valid()) {
				dist = _pVision->TheirPlayer(j).Pos().dist(targetPoint[i]);
				if (dist < enemy2PointDist)  enemy2PointDist = dist;//敌方到点距离
				dist = me.Pos().dist(_pVision->TheirPlayer(j).Pos());
				if (dist < enemy2MeDist) {
					enemy2MeDist = dist;//敌方到我的距离
					enemyNumRecord = j;
				}
				dist = _pVision->TheirPlayer(j).Pos().dist(shootLine.projection(_pVision->TheirPlayer(j).Pos()));
				if (dist < enemy2ShootLineDist) {
					enemy2ShootLineDist = dist;//敌方到射门线的距离
				}
				CGeoSegment passLine = CGeoSegment(ball.Pos(), targetPoint[i]);
				if (passLine.IsPointOnLineOnSegment(passLine.projection(_pVision->TheirPlayer(j).Pos()))) {
					dist = _pVision->TheirPlayer(j).Pos().dist(passLine.projection(_pVision->TheirPlayer(j).Pos()));
					if (dist < enemy2PassLineDist)
						enemy2PassLineDist = dist;//敌方到传球线的距离
				}
			}
		}
		enemy2PassLineDist = enemy2PassLineDist > thresholdForEnemy2PassLineDist ? thresholdForEnemy2PassLineDist : enemy2PassLineDist;
		enemy2ShootLineDist = enemy2ShootLineDist > thresholdForEnemy2ShootLineDist ? thresholdForEnemy2ShootLineDist : enemy2ShootLineDist;
		enemy2PointDist = enemy2PointDist > thresholdForEnemy2PointDist ? thresholdForEnemy2PointDist : enemy2PointDist;
        double pointToTheirGoalDist = targetPoint[i].dist(CGeoPoint(600,0));
        double score = enemy2PassLineDist * weight1 + enemy2PointDist * weight2 + enemy2ShootLineDist * weight3 + sizeOfDir * weight4 + determindir * weight5 + pointToTheirGoalDist * (-0.3);
        if (score > maxPointScore) {
            //cout<<"sizeOfDir" <<sizeOfDir<<" "<<i<<endl;
            //cout<<score<<" "<<i<<" "<<meToTheirGoalDist<<" "<<number<<endl;          
			maxPointScore = score;
			bestPointNumber = i;
		}
	}
    //GDebugEngine::Instance()->gui_debug_x(targetPoint[bestPointNumber], COLOR_YELLOW);
    //cout<<"bestPointNumber "<<bestPointNumber<<endl;
	return targetPoint[bestPointNumber];
}

void CBallAdvanceDecision::generateRunPosition() {
    if (PPDEBUG)
		cout << "generateRunPos" << endl;
	const MobileVisionT& ball = _pVision->Ball();
//	int attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision, _leader);
	int ballArea = 999;
	CGeoPoint tempPos;
    vector <CGeoPoint> targetPos;
    if (reGenerateFlag){
        tempPos = ball.Pos();
        reGenerateFlag = false;
    }
    else if (_receiver >= 0  && _receiver <= Param::Field::MAX_PLAYER){
		tempPos = _pVision->OurPlayer(_receiver).Pos();
    }
    else{
		tempPos = ball.Pos();
    }
    ballArea = getBallArea(tempPos);
    _lastBallArea = ballArea;
	if (PPDEBUG) {
		cout << "ballArea " << ballArea << endl;
		cout << "The runArea is ";
	}
    if (false){
        int myarea = 1;
        if (_pVision->OurPlayer(_receiver).Pos().x()>300){
            if (_pVision->OurPlayer(_receiver).Pos().y()>0){
                myarea = 3;
            }
            else{
                myarea = 1;
            }
        }
        else{
            if (_pVision->OurPlayer(_receiver).Pos().y()>0){
                myarea = 9;
            }
            else{
                myarea = 7;
            }
        }
        cout<<"myarea "<<myarea<<endl;
        for (int i = 0; i < 3; i++) {
            GPUBestAlgThread::Instance()->generateRunPos(formation[myarea - 1][i],targetPos);
            runPos[i] = runPointCompute(vehicleNumber[i+1], targetPos);
            if (PPDEBUG)
                cout << formation[myarea - 1][i] << " ";
        }
    }
    else{
        for (int i = 0; i < 3; i++) {
            GPUBestAlgThread::Instance()->generateRunPos(formation[ballArea - 1][i],targetPos);
            runPos[i] = runPointCompute(vehicleNumber[i+1], targetPos);
            if (PPDEBUG)
                cout << formation[ballArea - 1][i] << " ";
        }
    }
	if (PPDEBUG)
        cout << endl;
}

CGeoPoint CBallAdvanceDecision::runPointCompute(int number,const vector <CGeoPoint>& targetPoint) {
    if ((int) targetPoint.size() == 0) return CGeoPoint(600, 0);
    const PlayerVisionT& leader = _pVision->OurPlayer(_leader);
    const PlayerVisionT& me = _pVision->OurPlayer(number);
    const MobileVisionT& ball = _pVision->Ball();
    int bestPointNumber = 999;
    double maxPointScore = -0xffff;
    CGeoSegment passLine[3];
    for (int i = 0; i < targetPoint.size(); i++) {
        int count = 0;
        for (int j = 0; j <= 2; j++){
            if (number != vehicleNumber[j]){
                passLine[count++] = CGeoSegment(leader.Pos(),_pVision->OurPlayer(vehicleNumber[j]).Pos());
            }
        }
        CGeoSegment runLine = CGeoSegment(me.Pos(),targetPoint[i]);
        bool tooCloseToOtherRunPos = false;
        for (int j = 0; j <= 2; j++){
            if (number == vehicleNumber[j+1]){
                for (int k = 0; k < j; k++){
                    if (targetPoint[i].dist(runPos[k]) < 160)
                        tooCloseToOtherRunPos = true;
                }
            }
        }
        if (!runLine.IsSegmentsIntersect(passLine[0]) && !runLine.IsSegmentsIntersect(passLine[1]) && !tooCloseToOtherRunPos){
            //射门角，接球角大小
            CShootRangeList shootRangeList(_pVision, 0, targetPoint[i]);
            const CValueRange* bestRange = NULL;
            const CValueRangeList& shootRange = shootRangeList.getShootRange();
            double sizeOfDir;
            double kick_dir;
            double determindir;
            double metoballdir = (ball.Pos() - targetPoint[i]).dir();
//            double ball2PointDist = ball.Pos().dist(targetPoint[i]);
            if (shootRange.size() > 0) {
                bestRange = shootRange.getMaxRangeWidth();
                sizeOfDir = bestRange->getSize();
                kick_dir = bestRange->getMiddle();
                determindir = fabs(Utils::Normalize(metoballdir - kick_dir));
            }
            else {
                sizeOfDir = 0;
                kick_dir = (CGeoPoint(Param::Field::PITCH_LENGTH / 2, 0) - targetPoint[i]).dir();
                determindir = fabs(Utils::Normalize(metoballdir - kick_dir));
            }
            //
            double dist;
            double enemy2PointDist, enemy2MeDist, enemy2ShootLineDist, enemy2PassLineDist;
            enemy2PointDist = enemy2MeDist = enemy2ShootLineDist = enemy2PassLineDist = 9999;
            int enemyNumRecord;
            CGeoLine shootLine(targetPoint[i], kick_dir);
            for (int j = 1; j <= Param::Field::MAX_PLAYER; j++) {
                if (_pVision->TheirPlayer(j).Valid()) {
                    dist = _pVision->TheirPlayer(j).Pos().dist(targetPoint[i]);
                    if (dist < enemy2PointDist)  enemy2PointDist = dist;//敌方到点距离
                    dist = me.Pos().dist(_pVision->TheirPlayer(j).Pos());
                    if (dist < enemy2MeDist) {
                        enemy2MeDist = dist;//敌方到我的距离
                        enemyNumRecord = j;
                    }
                    dist = _pVision->TheirPlayer(j).Pos().dist(shootLine.projection(_pVision->TheirPlayer(j).Pos()));
                    if (dist < enemy2ShootLineDist) {
                        enemy2ShootLineDist = dist;//敌方到射门线的距离
                    }
                    CGeoSegment passLine = CGeoSegment(ball.Pos(), targetPoint[i]);
                    if (passLine.IsPointOnLineOnSegment(passLine.projection(_pVision->TheirPlayer(j).Pos()))) {
                        dist = _pVision->TheirPlayer(j).Pos().dist(passLine.projection(_pVision->TheirPlayer(j).Pos()));
                        if (dist < enemy2PassLineDist)
                            enemy2PassLineDist = dist;//敌方到传球线的距离
                    }
                }
            }
            enemy2PassLineDist = enemy2PassLineDist > thresholdForEnemy2PassLineDist ? thresholdForEnemy2PassLineDist : enemy2PassLineDist;
            enemy2ShootLineDist = enemy2ShootLineDist > thresholdForEnemy2ShootLineDist ? thresholdForEnemy2ShootLineDist : enemy2ShootLineDist;
            enemy2PointDist = enemy2PointDist > thresholdForEnemy2PointDist ? thresholdForEnemy2PointDist : enemy2PointDist;
            double pointToTheirGoalDist = targetPoint[i].dist(CGeoPoint(600,0));
            double score = enemy2PassLineDist * weight1 + enemy2PointDist * weight2 + enemy2ShootLineDist * weight3 + sizeOfDir * weight4 + determindir * weight5 + pointToTheirGoalDist * (-0.4);
            if (score > maxPointScore) {
                //cout<<score<<" "<<i<<" "<<meToTheirGoalDist<<" "<<number<<endl;
                maxPointScore = score;
                bestPointNumber = i;
            }
        }
    }
    if (bestPointNumber == 999){
        return me.Pos();
    }
    else{
        //GDebugEngine::Instance()->gui_debug_x(targetPoint[bestPointNumber], COLOR_YELLOW);
        return targetPoint[bestPointNumber];
    }
}

void CBallAdvanceDecision::generateTouchPassPosition() {
    if (PPDEBUG)
        cout << "generateTouchPassPos" << endl;
    const MobileVisionT& ball = _pVision->Ball();
    const PlayerVisionT& leader = _pVision->OurPlayer(_leader);
    const CRobotCapability* robotCap = RobotCapFactory::Instance()->getRobotCap(_pVision->Side(), _leader);
    const double MaxAcceleration = robotCap->maxAcceleration(CVector(0, 0), 0);
    const double MaxSpeed = robotCap->maxSpeed(0);
    const double slack = 0;
    const int minPassDist = 150;
    vector <CGeoPoint> tempPoint;
    vector <CGeoPoint> receivePoint;
    vector <CGeoPoint> rushPoint;
    CGeoPoint theirGoal = CGeoPoint(600, 0);
    int attackerAmount = SituationJudge::Instance()->checkAttackerAmount(_pVision);
    double maxPlayerScore = -99999;
    int maxPointSize = -1;
    int pointCount;
    _receiver = 999;
    //cout<<"before1 "<< runPos[0]<<" "<<runPos[1]<<" "<<runPos[2]<<" "<<runPos[3]<<endl;
    if (attackerAmount == 1 && PPDEBUG)
        cout << "attackerAmount is " << attackerAmount << endl;
    for (int i = 1; i < attackerAmount; i++) {
//        bool canFlatPassTo = true;
        pointCount = 0;
        const PlayerVisionT& me = _pVision->OurPlayer(vehicleNumber[i]);
        if (vehicleNumber[i]!=0){
            for (int j = 1; j < area.location.size(); j++) {//CHANGED!!!
                //double myTime = predictedTime(me, area.targetPos[j]);
                bool bestToPoint = true;
                /*for(int k = 1; k < attackerAmount; k++){
                    const PlayerVisionT& teamMate = _pVision->OurPlayer(vehicleNumber[k]);
                    double teamMateTime = predictedTime(teamMate, area.targetPos[j]);
                    if (teamMateTime < myTime){
                        bestToPoint = false;
                        break;
                    }
                }*/
                double myDist = me.Pos().dist(area.targetPos[j]);
                for(int k = 1; k < attackerAmount; k++){
                    const PlayerVisionT& teamMate = _pVision->OurPlayer(vehicleNumber[k]);
                    double teamMateDist = teamMate.Pos().dist(area.targetPos[j]);
                    if (teamMateDist < myDist){
                        bestToPoint = false;
                        break;
                    }
                }
                if (bestToPoint){
                    double minAnemyTime = 9999;
                    for (int k = 1; k <= Param::Field::MAX_PLAYER; k++) {
                        const PlayerVisionT& anemy = _pVision->TheirPlayer(k);
                        if (anemy.Valid()) {
                            //double anemyTime = expectedCMPathTime(anemy, area.targetPos[j], 580, 350, CM_PREDICT_FACTOR);
                            double anemyTime = predictedTime(anemy, area.targetPos[j]);
                            if (anemyTime < minAnemyTime)
                                minAnemyTime = anemyTime;
//                            CGeoSegment passLine = CGeoSegment(area.targetPos[j], me.Pos());
//                            if (passLine.IsPointOnLineOnSegment(passLine.projection(anemy.Pos()))) {
//                                double dist = anemy.Pos().dist(passLine.projection(anemy.Pos()));
//                                if (dist < 14) {
//                                    canFlatPassTo = false;
//                                }
//                            }
                        }
                    }
                    //cout << *vehicleNumber << endl;
                    //double myTime = expectedCMPathTime(me, area.targetPos[j], MaxAcceleration, MaxSpeed, CM_PREDICT_FACTOR);
                    double myTime = predictedTime(me, area.targetPos[j]);
                    double ball2Target = passPos.dist(area.targetPos[j]);
//                    double ballspeed = ball2Target * 0.8 + 100;
//                    if (ballspeed < 200) {
//                        ballspeed = 200;
//                    }
//                    else if (ballspeed > 550) {
//                        ballspeed = 550;
//                    }
//                    //if (_pVision->OurPlayer(vehicleNumber[i]).X() > 0)
//                        //tempPoint.push_back(_pVision->OurPlayer(vehicleNumber[i]).Pos());
//                    double ballPassTime;
//                    if (ballspeed * ballspeed - FRICTION * ball2Target > 0) {
//                        ballPassTime = 2 * (-ballspeed + sqrt(ballspeed * ballspeed - FRICTION * ball2Target)) / (-FRICTION);
//                    }
//                    else {
//                        ballPassTime = -1;
//                    }
                    double ballPassTime = myTime + slack;
                    double acc = (-FRICTION) / 2;
                    double ballSpeed = (ball2Target - acc * ballPassTime * ballPassTime / 2) / ballPassTime * powerRatio;
                    bool canNotPass = false;
                    if (ballSpeed > maxStopBallSpeed){
                        ballSpeed = maxStopBallSpeed;
                        if (ballSpeed * ballSpeed - FRICTION * ball2Target > 0) {
                            ballPassTime = 2 * (-ballSpeed + sqrt(ballSpeed * ballSpeed - FRICTION * ball2Target)) / (-FRICTION);
                        }
                        else {
                            ballPassTime = 9999;
                        }
                        ballPassTime += slack;
                    }
                    if (ballPassTime * ballPassTime > -2 * acc * ball2Target){
                       canNotPass = true;
                    }
                    if ((ballPassTime < minAnemyTime) && !Utils::InTheirPenaltyArea(area.targetPos[j], 10) && !Utils::OutOfField(area.targetPos[j]) && !canNotPass) {
                        //cout<<"myTime "<<myTime<<" ballPassTime "<<ballPassTime<<endl;
                        if (myTime < ballPassTime * 0.9) {
                            double passdir = (area.targetPos[j] - leader.Pos()).dir();
                            double leadertoballdir = (ball.Pos() -  leader.Pos()).dir();
                            double  determindir = fabs(Utils::Normalize(leadertoballdir - passdir));
                            bool canWaitTouch = false;
                            if ((determindir * 180 / Param::Math::PI) < 70) {
                                //cout<<determindir * 180 / Param::Math::PI <<" "<<vehicleNumber[i]-1<<endl;
                                canWaitTouch = true;
                            }
                            if (canWaitTouch){
                                area.status[j] = true;
                                tempPoint.push_back(area.targetPos[j]);
                                pointCount++;
                            }
                            //GDebugEngine::Instance()->gui_debug_x(area.targetPos[j]);
                        }
                        //GDebugEngine::Instance()->gui_debug_x(area.targetPos[j]);
                    }
                    else {
                        area.status[j] = false;
                    }
                }
            }
            if (pointCount > 0) {
                double meToTheirGoal = me.Pos().dist(theirGoal);
                double ballPassDist = me.Pos().dist(ball.Pos());
                double playerScore = pointCount * 5 - meToTheirGoal * 1 / 3 - ballPassDist * 2.5 / 4.5;
                //cout<<"pointCount "<<pointCount<<" meToTheirGoal "<<meToTheirGoal<<" canFlatPassTo "<<canFlatPassTo<<" ballPassDist "<<ballPassDist<<endl;
                //cout<<"playerScore "<<playerScore<< " "<<vehicleNumber[i]-1 <<endl;
                if (playerScore > maxPlayerScore) {
                    if (ball.Pos().dist(_pVision->OurPlayer(vehicleNumber[i]).Pos()) > minPassDist) {
                        //cout << vehicleNumber[_receiver]<<" " <<_pVision->OurPlayer(vehicleNumber[_receiver]).Pos().dist(theirGoal) << " last dist " << vehicleNumber[vehicleNumber[i]] << " " << _pVision->OurPlayer(vehicleNumber[i]).Pos().dist(theirGoal) << " current dist" << endl;
                        receivePoint = tempPoint;
                        _receiver = i;
                        maxPointSize = pointCount;
                        maxPlayerScore = playerScore;
                        //cout << pointCount << " pointCount " << maxPointSize << endl;
                        //cout << "change "<<_receiver << " to " << vehicleNumber[i] << endl;
                    }
                }
            }
        }
        //cout << pointCount << " pointCount " << vehicleNumber[i] << endl;
        tempPoint.clear();
    }
    //cout << "-------------------------------" << endl;
    int receiver = 1;
    if (_receiver != 999) {
        receiver = _receiver;
        _receiver = vehicleNumber[_receiver];
        if (PPDEBUG)
            cout << "touchpass to " << _receiver - 1 << endl;
        //cout<<"pick "<<receiver<<endl;
        int myarea = 1;
        if (_pVision->OurPlayer(_receiver).Pos().x()>300){
            if (_pVision->OurPlayer(_receiver).Pos().y()>0){
                myarea = 3;
            }
            else{
                myarea = 1;
            }
        }
        else{
            if (_pVision->OurPlayer(_receiver).Pos().y()>0){
                myarea = 9;
            }
            else{
                myarea = 7;
            }
        }
        int leaderarea = 1;
        if (_pVision->OurPlayer(_leader).Pos().x()>300){
            if (_pVision->OurPlayer(_leader).Pos().y()>0){
                leaderarea = 3;
            }
            else{
                leaderarea = 1;
            }
        }
        else{
            if (_pVision->OurPlayer(_leader).Pos().y()>0){
                leaderarea = 9;
            }
            else{
                leaderarea = 7;
            }
        }
        //cout<<"leaderarea "<<leaderarea<<" myarea "<<myarea<<endl;
        int generateArea[4] = {1,3,7,9};
        vector <CGeoPoint> targetPos;
        for (int i = 0; i <= 2; i++) {
            if ((receiver - 1) != i){
                for (int j = 0; j <= 3; j++){
                    if (generateArea[j] != leaderarea && generateArea[j] != myarea && generateArea[j] != 999){
                        GPUBestAlgThread::Instance()->generateRunPos(generateArea[j],targetPos);
                        runPos[i] = runPointCompute(vehicleNumber[i+1], targetPos);
                        generateArea[j] = 999;
                        //cout<<"runPos "<<i<<" is done"<<endl;
                        break;
                    }
                }
            }
        }
        //cout<< vehicleNumber[0] - 1<<" "<< vehicleNumber[1] -1 <<" "<< vehicleNumber[2] -1 <<" "<< vehicleNumber[3] - 1<<" "<< _state<<endl;
        //cout << "touchpass to " << _receiver - 1 << endl;
        //cout<<"before2 "<< runPos[0]<<" "<<runPos[1]<<" "<<runPos[2]<<" "<<runPos[3]<<endl;
        runPos[receiver - 1] = receiveBallPointCompute(vehicleNumber[receiver], receivePoint);
        //cout<<"after "<< runPos[0]<<" "<<runPos[1]<<" "<<runPos[2]<<" "<<runPos[3]<<endl;
        //cout<< secondPassPos<<endl;
        //cout<<"runPos "<<receiver - 1<<" is done"<<endl;
        //passPos = secondPassPos;
        secondPassPos = runPos[receiver - 1];
        double myTime = predictedTime(_pVision->OurPlayer(_receiver), secondPassPos);
        double ball2Target = passPos.dist(secondPassPos);
        double ballPassTime = myTime + slack;
        double acc = (-FRICTION) / 2;
        double ballspeed = (ball2Target - acc * ballPassTime * ballPassTime / 2) / ballPassTime;
        kickPower = (ballspeed * powerRatio > maxStopBallSpeed) ? maxStopBallSpeed : ballspeed * powerRatio;
//        bool canSafePassTo = ZSkillUtils::instance()->isSafeShoot(_pVision,kickPower,passPos);
        //cout<<"_leader is "<<_leader<<endl;
        //cout<<"receiver is "<<_receiver<<endl;
    }
    else {
        CGeoPoint theirGoal = CGeoPoint(600,0);
        secondPassPos = theirGoal;
    }
    //changeLeaderOverFlag = false;
    //changeLeaderFlag = false;
    //_receiver = vehicleNumber[_receiver];
    /*runPos[receiver-1] = receiveBallPointCompute(vehicleNumber[receiver], receivePoint);
    passPos = runPos[receiver];
    for (int i = 0; i < attackerAmount - 1; i++) {
    //if (i != _receiver)
    //runPos[i] = _pVision->OurPlayer(vehicleNumber[i]).Pos();
    }*/
}

int CBallAdvanceDecision::getBallArea(CGeoPoint tempPos) {
    int ballArea = 999;
    for (int i = 1; i <= 9; i++) {
        if (runArea[i].HasPoint(tempPos)) {
            ballArea = i;
            break;
        }
    }
    if (ballArea == 999) {
        if (tempPos.x() > 0) {
            if (tempPos.y() > 0) {
                ballArea = 3;
            }
            else {
                ballArea = 1;
            }
        }
        else {
            if (tempPos.y() < -150) {
                ballArea = 11;
            }
            else if (tempPos.y() < 150) {
                ballArea = 12;
            }
            else {
                ballArea = 13;
            }
        }
    }
    return ballArea;
}

double CBallAdvanceDecision::robotTimeCompute(int vehicleNumber) {
	if (vehicleNumber<1 || vehicleNumber>Param::Field::MAX_PLAYER || !_pVision->OurPlayer(vehicleNumber).Valid()) {
		//cout << "vehicleNumber error" << endl;
		return 999;
	}
	const MobileVisionT& ball = _pVision->Ball();
	const PlayerVisionT& me = _pVision->OurPlayer(vehicleNumber);
	CGeoPoint ball_predict_pos = ball.Pos();
	const double STEP_TIME = 1.0 / Param::Vision::FRAME_RATE;
	const int increase_step = 5;
	long predict_cycle = 0;
	double ball_time = 0;
	double robot_time = 0;
//	double robot_time2 = 0;
	const double robot_ahead_slack = 0.2;
//    const CRobotCapability* robotCap = RobotCapFactory::Instance()->getRobotCap(_pVision->Side(), vehicleNumber);
//	const double MaxSpeed = robotCap->maxSpeed(0);								//speed
//	const double MaxAcceleration = robotCap->maxAcceleration(CVector(0, 0), 0);	//acceleration;
	const double MAX_TIME = 5;
	if (ball.Vel().mod() > 1) {
		do {
			ball_predict_pos = BallSpeedModel::Instance()->posForTime(predict_cycle, _pVision);
			predict_cycle += increase_step;
			ball_time += increase_step*STEP_TIME;
			CGeoPoint tmpPoint = ball_predict_pos + Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER, Utils::Normalize(_pVision->OurPlayer(vehicleNumber).Dir() + Param::Math::PI));
			//robot_time = expectedCMPathTime(me, tmpPoint, MaxAcceleration, MaxSpeed, CM_PREDICT_FACTOR) + STEP_TIME*Param::Latency::TOTAL_LATED_FRAME;
			robot_time = predictedTime(me, tmpPoint);
			//cout << "debug " << vehicleNumber << endl;
		} while (robot_time + robot_ahead_slack > ball_time && !Utils::OutOfField(ball_predict_pos)
			&& robot_time <= MAX_TIME && ball_time <= MAX_TIME);
	}
	else {
		robot_time = predictedTime(me, ball.Pos());
	}
	// cout << "number : " << vehicleNumber << "\ttime : " << robot_time << endl;
	return robot_time;
}	
