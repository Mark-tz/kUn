#ifndef HOLDBALL_H
#define HOLDBALL_H
#include <skill/PlayerTask.h>

/****************************************************/
/*                   holdball                       */
/****************************************************/

class CHoldBall : public CStatedTask
{
public:
    CHoldBall();
    virtual void plan(const CVisionModule* pVision);
    virtual bool isEmpty() const { return false; }
    virtual CPlayerCommand* execute(const CVisionModule* pvision);
protected:
    virtual void toStream(std::ostream& os) const { os << "Skill: HoldBall\n";}
private:
    int _lastCycle;
    CPlayerCommand* _directCommand;
};

#endif // HOLDBALL_H
