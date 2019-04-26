#ifndef SMARTMARKING_H
#define SMARTMARKING_H

#include <skill/PlayerTask.h>

/************************************************************************/
/*                  预测防人						  					*/
/************************************************************************/
class CZBlocking : public CStatedTask{
public:
    CZBlocking();
    virtual void plan(const CVisionModule* pVision);
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
    virtual bool isEmpty()const { return false; }
protected:
    virtual void toStream(std::ostream& os) const { os << "Marking Defense"; }

private:
    int _lastCycle;

};
#endif // SMARTMARKING_H
