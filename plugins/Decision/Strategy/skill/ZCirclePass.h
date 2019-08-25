/***************************************
吸球晃人射门
add by Wang in 2018/06/08
***************************************/
#ifndef _Z_CIRCLE_PASS_H_
#define _Z_CIRCLE_PASS_H_
#include <skill/PlayerTask.h>

class CZCirclePass : public CStatedTask {
public:
	virtual void plan(const CVisionModule* pVision);
	virtual bool isEmpty() const { return false; }
	virtual CPlayerCommand* execute(const CVisionModule* pVision);
protected:
    virtual void toStream(std::ostream& os) const { os << "Skill: ZPass\n" << std::endl; }
private:
	int _lastCycle;
    int oppNum;
};


#endif // !_Z_CIRCLE_PASS_H_
