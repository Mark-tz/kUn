// mark - zjunlict - hzypp1995@gmail.com
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__
#include "zsplugin.hpp"
#include "Sim/sslworld.h"
#include "Vision/visionplugin.h"
//#include "Decision/decisionplugin.h"
#include "Cmd2Sim/cmd2sim.h"
#include "UDPSender/udpsender.h"
#include "UDPReceiver/udpreceiver.h"

#include "geometry.h"

#include <array>
struct FeedBack{
    std::array<double,2> state;
    double reward;
    bool done;
};
typedef std::array<double,3> Action;
class Environment : public ZSPlugin{
public:

public:
    Environment();
    Environment(unsigned int);
    ~Environment();
    FeedBack reset();
    void render();
    FeedBack step(double*,int);
    void start_all();
private:
    void run();
private:
    SSLWorld* sim;
    VisionPlugin* vm;
//    DecisionPlugin* dm_blue_left;
    Cmd2Sim* c2s_blue;
    UDPSender* vision_sender;
    UDPReceiver* handle_receiver;
private:
    void setBallAndRobot(double,double,int,bool,double,double,double dir = 0,bool turnon = true);
private:
    void getState(FeedBack& fb);
    void sendAction(const Action& action);
    CGeoPoint target;
    int cycle;
private:
    //
};
#endif // __ENVIRONMENT_H__
