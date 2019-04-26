#include "decisionmodule.h"

#include <iostream>
#include <fstream>

#ifdef USE_PYTHON_MODULE
#include "PythonModule/PythonModule.h"
#endif

#ifdef USE_CUDA_MODULE
#include "CUDAModule/CUDAModule.h"
#endif

#include <ServerInterface.h>
#include <weerror.h>
#include <WorldModel.h>
#include "DecisionModule.h"
#include <VisionReceiver.h>

#include <GDebugEngine.h>
#include "bayes/MatchState.h"
#include "gpuBestAlgThread.h"
#include "Global.h"
#include "DefendUtils.h"
#include "Compensate.h"
#include <mutex>
#include "CollisionDetect.h"
#include "CommandInterface.h"
#include "parammanager.h"
#include "zss_debug.pb.h"
#include "zsplugin.hpp"
#include "RefereeBoxIf.h"
#include "ActionModule.h"
#include <QCoreApplication>
/*! \mainpage Zeus - Run for number one
*
* \section Introduction
*
*	ZJUNlict is robot soccer team of Robocup in Small Size League.
*
* \section Strategy
*	Frame : GameState -> Play -> Agent -> Skill -> Motion Control -> Wireless
*
* \subsection step1: GameState
* \subsection step2: Play
* \subsection step3: Agent
* \subsection step4: Skill
* \subsection step5: Motion Control : PathPlan and Trajectory Generation
*
* etc...
*/

extern Semaphore visionEvent;
extern std::mutex *decisionMutex;
/// <summary> For GPU. </summary>
std::mutex* _best_visiondata_copy_mutex = 0;
std::mutex* _value_getter_mutex = 0;

using Param::Latency::TOTAL_LATED_FRAME;

bool VERBOSE_MODE = true;
bool IS_SIMULATION = false;
bool wireless_off = false;
bool record_run_pos_on = false;
namespace {
COptionModule *option;
VisionReceiver *receiver;
CDecisionModule *decision;
CActionModule *action;
CServerInterface::VisualInfo visionInfo;
RefRecvMsg refRecvMsg;
}

DecisionModule::DecisionModule(){}
DecisionModule::~DecisionModule(){}
void DecisionModule::run(){
#ifdef USE_PYTHON_MODULE
    PythonModule::instance();
#endif
    ZSS::ZParamManager::instance()->loadParam(IS_SIMULATION, "Alert/IsSimulation", false);
    initializeSingleton();
    option = new COptionModule();
    CCommandInterface::instance(option);
    receiver = VisionReceiver::instance(option);
    decision = new CDecisionModule(vision);
    action = new CActionModule(vision, decision);
    vision->registerOption(option);
    WORLD_MODEL->registerVision(vision);
    MATCH_STATE->initialize(option, vision);
    _best_visiondata_copy_mutex = new std::mutex();
    _value_getter_mutex = new std::mutex();
    GPUBestAlgThread::Instance()->initialize(VisionModule::Instance());
    CollisionDetect::Instance()->initialize(VisionModule::Instance());
    RefereeBoxInterface::Instance();
#ifdef USE_CUDA_MODULE
    ZCUDAModule::instance()->initialize(VisionModule::Instance());
#endif
	while(true){
		visionEvent.wait();
        decisionMutex->lock();
        if (! receiver->getVisionInfo(visionInfo, refRecvMsg)) {
            std::cout << "no vision input" << std::endl;
        }
        vision->SetRefRecvMsg(refRecvMsg);
        vision->SetNewVision(visionInfo);
#ifdef USE_PYTHON_MODULE
        PythonModule::instance()->run();
#endif
        decision->DoDecision(false);
        if (! wireless_off) {
            action->sendAction(visionInfo.ourRobotIndex);
        } else {
            action->sendNoAction(visionInfo.ourRobotIndex);
        }
        decisionMutex->unlock();
//        GDebugEngine::Instance()->send(IS_SIMULATION && option->MyColor() == TEAM_YELLOW); // Simulation Yellow no debug messages
        GDebugEngine::Instance()->send(option->MyColor() == TEAM_BLUE); //Show two teams debug messages
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}