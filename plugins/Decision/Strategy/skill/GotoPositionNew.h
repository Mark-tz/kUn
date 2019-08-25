#ifndef _GOTO_POSITION_NEW_H_
#define _GOTO_POSITION_NEW_H_
#include <skill/PlayerTask.h>
#include <geometry.h>
/************************************************************************/
/*                     CGotoPositionNew / 跑位                          */
/************************************************************************/

struct PlayerCapabilityT;

class CGotoPositionNew : public CPlayerTask{
public:
    CGotoPositionNew();
    virtual void plan(const CVisionModule* pVision);
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
    virtual bool isEmpty() const { return false; }
    const CGeoPoint& reTarget() const { return _target; }
protected:
    virtual void toStream(std::ostream& os) const;
    bool canGoto(const CVisionModule* pVision, const int player, const CGeoPoint& target);
    PlayerCapabilityT setCapability(const CVisionModule* pVision);
private:
    CGeoPoint _target;
};

#endif
