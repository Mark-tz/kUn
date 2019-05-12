#ifndef __DECISION_H__
#define __DECISION_H__
#include "zsplugin.hpp"
#include "OptionModule.h"
#include "DecisionModule.h"
#include "ActionModule.h"
#include "ServerInterface.h"
class DecisionPlugin : public ZSPlugin {
public:
    DecisionPlugin(bool ifYellow, bool ifRight);
    ~DecisionPlugin();
	void run();
    void getVision();

    bool IS_SIMULATION = false;
    Semaphore new_vision_event;
    COptionModule *option = nullptr;
    CDecisionModule *decision = nullptr;
    CActionModule *action = nullptr;
    CServerInterface::VisualInfo visionInfo;
    std::mutex visionInfoMutex;
    RefRecvMsg refRecvMsg;

    std::mutex* _best_visiondata_copy_mutex = nullptr;
    std::mutex* _value_getter_mutex = nullptr;
};
#endif // __DECISION_H__
