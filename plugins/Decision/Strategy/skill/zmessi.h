#ifndef ZMESSI_H
#define ZMESSI_H
#include <skill/PlayerTask.h>

class CZMessi : public CStatedTask {
public:
    explicit CZMessi();
    virtual void plan(const CVisionModule* pVision);
    virtual bool isEmpty() const { return false; }
    virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
    virtual void toStream(std::ostream& os) const { os << "Skill: ZMessi\n" << std::endl; }
private:
    int _lastCycle;
};

#endif // ZMESSI_H
