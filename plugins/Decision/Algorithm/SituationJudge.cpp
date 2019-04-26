#include "SituationJudge.h"
#include "VisionModule.h"
#include "BallAdvanceDecision.h"

using namespace std;
CSituationJudge::CSituationJudge() {

}

CSituationJudge::~CSituationJudge() {
	
}

int CSituationJudge::checkAttackerAmount(const CVisionModule* pVision) {
	const MobileVisionT& ball = pVision->Ball();
    string ballStatus = BallAdvanceDecision::Instance()->getNormalPlayBallStatus();
    const int frontX = 200;
    const int backX = -200;
    const int slack = 100;
	static int field = BackField;
	int attackerAmount;
	switch (field) {
	case FrontField:
		if (ball.X() < backX) {
			field = BackField;
		}
		else if (ball.X() < frontX - slack) {
			field = MiddleField;
		}
		break;
	case MiddleField:
        if (ball.X() > frontX) {
			field = FrontField;
		}
		else if (ball.X() < backX - slack) {
			field = BackField;
		}
		break;
	case BackField:
		if (ball.X() > frontX) {
			field = FrontField;
		}
        else if (ball.X() > backX) {
			field = MiddleField;
		}
		break;
	}

    switch (field) {
    case FrontField:
        attackerAmount = (ballStatus == "ourBall") ? 4 : (ballStatus == "standOff") ? 3 : 2;
        break;
    case MiddleField:
        attackerAmount = (ballStatus == "ourBall") ? 4 : (ballStatus == "standOff") ? 2 : 2;
        break;
    case BackField:
        attackerAmount = (ballStatus == "ourBall") ? 4 : (ballStatus == "standOff") ? 2 : 2;
        break;
    }
    return attackerAmount;
}
