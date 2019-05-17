// mark - zjunlict - hzypp1995@gmail.com
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__
#include "zsplugin.hpp"
#include "Sim/sslworld.h"
#include "Vision/visionplugin.h"
#include "Decision/decisionplugin.h"
#include "Cmd2Sim/cmd2sim.h"
#include "UDPSender/udpsender.h"
#include "UDPReceiver/udpreceiver.h"
class Environment : public ZSPlugin{
public:
    Environment();
    Environment(unsigned int);
    ~Environment();
    void reset();
    void render();
    void step();
    void run();
private:
    void start_all();
private:
    SSLWorld* sim;
    VisionPlugin* vm;
    DecisionPlugin* dm_blue_left;
    Cmd2Sim* c2s_blue;
    UDPSender* vision_sender;
};
#endif // __ENVIRONMENT_H__
