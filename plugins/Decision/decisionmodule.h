#ifndef __DECISION_H__
#define __DECISION_H__
#include "zsplugin.hpp"
class DecisionModule : public ZSPlugin {
public:
	DecisionModule();
	~DecisionModule();
	void run();
};
#endif // __DECISION_H__