#ifndef _GO_IMMORTAL_RUSH_H_
#define _GO_IMMORTAL_RUSH_H_
#include <skill/PlayerTask.h>
#include <RobotCapability.h>
#include <VisionModule.h>
#include <geometry.h>
/************************************************************************/
/*                     CGoImmortalRush / 跑位                           */
/************************************************************************/

struct PlayerCapabilityT;
double calcImmortalTime(const CVisionModule* pVision, const int robotNum, const CGeoPoint targetPos, const double targetDir, const int mode);

class CGoImmortalRush : public CPlayerTask {
public:
	CGoImmortalRush();
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	virtual bool isEmpty() const { return false; }
	const CGeoPoint& reTarget() const { return _target; }
protected:
	virtual void toStream(std::ostream& os) const;
	bool canGoto(const CVisionModule* pVision, const int player, const CGeoPoint& target);
	PlayerCapabilityT setCapability(const CVisionModule* pVision);
    void calcNoneZeroRush(const CVisionModule* pVision, CVector& nextVel, double& nextRotVel, double& nextAngle);
    void calcZeroRush(const CVisionModule* pVision, CVector& nextVel, double& nextRotVel, double& nextAngle);
    void getArrivedRotate(const CVisionModule* pVision, CVector& nextVel, double& nextRotVel, double& nextAngle);
    void getStartRotate(const CVisionModule* pVision, CVector& nextVel, double& nextRotVel, double& nextAngle);
    void getMiddleRush(const CVisionModule* pVision, CVector& nextVel, double& nextRotVel, double& nextAngle);
//    void LeavePenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target);
    void LeavePenaltyArea(const CVisionModule* pVision, const int player);
//    void LeaveTheirPenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target);
    void LeaveTheirPenaltyArea(const CVisionModule* pVision, const int player);
private:
    PlayerCapabilityT _capability;
	CGeoPoint _target;
	int _lastCycle;
};

#endif
