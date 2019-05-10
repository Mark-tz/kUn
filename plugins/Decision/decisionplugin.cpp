#include "decisionplugin.h"

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

#include "vision_detection.pb.h"

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
Semaphore new_vision_event;

COptionModule *option;
VisionReceiver *receiver;
CDecisionModule *decision;
CActionModule *action;
CServerInterface::VisualInfo visionInfo;
std::mutex visionInfoMutex;
RefRecvMsg refRecvMsg;
// for receive from Kun Framework
}

DecisionPlugin::DecisionPlugin(bool ifYellow,bool ifRight){
    declare_publish("zss_cmds");
    declare_receive("zss_vision");
    declare_receive("ssl_referee");
    option = new COptionModule(ifYellow,ifRight);
}
DecisionPlugin::~DecisionPlugin(){}
void DecisionPlugin::run(){
    qDebug() << "decision start";
    std::thread vision_thread([=]{ getVision(); });
#ifdef USE_PYTHON_MODULE
    PythonModule::instance();
#endif
    ZSS::ZParamManager::instance()->loadParam(IS_SIMULATION, "Alert/IsSimulation", false);
    initializeSingleton();
    CCommandInterface::instance(option);
    receiver = VisionReceiver::instance(option);
    decision = new CDecisionModule(vision);
    action = new CActionModule(vision, decision);
    vision->registerOption(option);
    WORLD_MODEL->registerVision(vision);
    _best_visiondata_copy_mutex = new std::mutex();
    _value_getter_mutex = new std::mutex();
    GPUBestAlgThread::Instance()->initialize(VisionModule::Instance());
    CollisionDetect::Instance()->initialize(VisionModule::Instance());
    RefereeBoxInterface::Instance(option);
#ifdef USE_CUDA_MODULE
    ZCUDAModule::instance()->initialize(VisionModule::Instance());
#endif
	while(true){
//        get vision and referee message
        new_vision_event.wait();
        visionInfoMutex.lock();
        vision->SetRefRecvMsg(refRecvMsg);
        vision->SetNewVision(visionInfo);
        visionInfoMutex.unlock();
        decisionMutex->lock();
#ifdef USE_PYTHON_MODULE
        PythonModule::instance()->run();
#endif
        qDebug() << "get new vision from decision plugin";
        decision->DoDecision(false);
//        send commands
//        action->sendAction(visionInfo.ourRobotIndex);
        decisionMutex->unlock();
        GDebugEngine::Instance()->send(option->MyColor() == TEAM_BLUE);
	}
}
namespace{
void initInfo(CServerInterface::VisualInfo &temp) {
    for (int i = 0; i <  Param::Field::MAX_PLAYER_NUM; i++) {
        temp.ourRobotIndex[i] = 0;
        temp.player[i].dir = 0;
        temp.player[i].pos.valid = false;
        temp.player[i].pos.x = -999999;
        temp.player[i].pos.y = -999999;
        temp.theirRobotIndex[i] = 0;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].dir = 0;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].pos.valid = false;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].pos.x = -999999;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].pos.y = -999999;
    }
}
}
void ZSS_THREAD_FUNCTION DecisionPlugin::getVision(){
    ZSData vision_data,referee_data;
    Vision_DetectionFrame vision_frame;
    auto& temp = visionInfo;
    auto& _pOption = option;
    while(true){
        receive("zss_vision",vision_data);
        vision_frame.ParseFromArray(vision_data.data(),vision_data.size());
//        auto res = try_receive("ssl_referee",referee_data);
        auto robots_blue_n = std::min(vision_frame.robots_blue_size(), Param::Field::MAX_PLAYER_NUM);
        auto robots_yellow_n = std::min(vision_frame.robots_yellow_size(),Param::Field::MAX_PLAYER_NUM);
        visionInfoMutex.lock();
        initInfo(temp);
        bool ballFound = vision_frame.has_ball();
        if (ballFound) {
            auto & ball = vision_frame.ball();
            if (ball.x() < -30000 && ball.y() < -30000) {
                //理论上不应该进入这个if
                temp.ball.x = -32768;
                temp.ball.x = -32768;
                temp.ball.valid = false;
            } else {
                temp.ball.x = ball.x() / 10;
                temp.ball.y = -ball.y() / 10;
                temp.ball.valid = true;
                temp.BallState = (ballState)ball.ball_state();
                temp.BallLastTouch = ball.last_touch();
                temp.BallVel.setVector(ball.vel_x() / 10, -ball.vel_y() / 10);
            }
        } else {
            temp.ball.x = -32768;
            temp.ball.x = -32768;
            temp.ball.valid = false;
        }
        int index;
        _pOption->MyColor() == TEAM_BLUE ? index = 0 : index = Param::Field::MAX_PLAYER_NUM;
        for (int i = 0; i < robots_blue_n; i++) {
            auto& robot = vision_frame.robots_blue(i);
            auto id = robot.robot_id();
            if (id >= 0 && id < Param::Field::MAX_PLAYER_NUM) {
                index = _pOption->MyColor() == TEAM_BLUE ? id : id + Param::Field::MAX_PLAYER_NUM;
                _pOption->MyColor() == TEAM_BLUE ? temp.ourRobotIndex[index] = id + 1 :
                        temp.theirRobotIndex[index - Param::Field::MAX_PLAYER_NUM] = id + 1;
                temp.player[index].pos.x = robot.x() / 10;
                temp.player[index].pos.y = -robot.y() / 10;
                temp.player[index].pos.valid = true;
                temp.player[index].dir = -robot.orientation();
                temp.player[index].vel.setVector(robot.vel_x() / 10, -robot.vel_y() / 10);
                temp.player[index].dirvel = -robot.rotate_vel();
            }
        }
        _pOption->MyColor() == TEAM_BLUE ? index = Param::Field::MAX_PLAYER_NUM : index = 0;
        for (int i = 0; i < robots_yellow_n; i++) {
            auto& robot = vision_frame.robots_yellow(i);
            auto id = robot.robot_id();
            if (id >= 0 && id < Param::Field::MAX_PLAYER_NUM) {
                index = _pOption->MyColor() == TEAM_YELLOW ? id : id + Param::Field::MAX_PLAYER_NUM;
                _pOption->MyColor() == TEAM_YELLOW ? temp.ourRobotIndex[index] = id + 1 :
                        temp.theirRobotIndex[index - Param::Field::MAX_PLAYER_NUM] = id + 1;
                temp.player[index].pos.x = robot.x() / 10;
                temp.player[index].pos.y = -robot.y() / 10;
                temp.player[index].pos.valid = true;
                temp.player[index].dir = -robot.orientation();
                temp.player[index].vel.setVector(robot.vel_x() / 10, -robot.vel_y() / 10);
                temp.player[index].dirvel = -robot.rotate_vel();
            }
        }
        visionInfoMutex.unlock();
        new_vision_event.signal();
    }
}
