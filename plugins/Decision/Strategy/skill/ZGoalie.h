#ifndef __Z_GOALIE_H__
#define __Z_GOALIE_H__
#include <skill/PlayerTask.h>

class CZGoalie : public CStatedTask{
public:
    CZGoalie();
    virtual void plan(const CVisionModule* pVision);
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
    virtual bool isEmpty()const { return false; }
protected:
    virtual void toStream(std::ostream& os) const { os << "Goalie 2018"; }
private:
    int _lastCycle;
//    bool judgeInterPoint(const CVisionModule*);
};

#endif // __Z_GOALIE_H_
