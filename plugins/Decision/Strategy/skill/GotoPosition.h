#ifndef _GOTO_POSITION_V2_H_
#define _GOTO_POSITION_V2_H_
#include <skill/PlayerTask.h>
#include <geometry.h>
/************************************************************************/
/*                     CGotoPositionV2 / 跑位                           */
/************************************************************************/

struct PlayerCapabilityT;

class CGotoPositionV2 : public CPlayerTask{
public:
	CGotoPositionV2();
	virtual void plan(const CVisionModule* pVision);
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
	virtual bool isEmpty() const { return false; }
	const CGeoPoint& reTarget() const { return _target; }
protected:
	virtual void toStream(std::ostream& os) const;
	void LeavePenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target);
	void LeaveTheirPenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target);
	bool canGoto(const CVisionModule* pVision, const int player, const CGeoPoint& target);
private:
	CGeoPoint _target;
};

#endif
