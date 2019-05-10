#ifndef __DECISION_H__
#define __DECISION_H__
#include "zsplugin.hpp"
class DecisionPlugin : public ZSPlugin {
public:
    DecisionPlugin(bool ifYellow, bool ifRight);
    ~DecisionPlugin();
	void run();
    void getVision();
};
#endif // __DECISION_H__
