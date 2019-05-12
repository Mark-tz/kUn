#include <iostream>
#include <thread>
#include "dllexport.h"
#include "Sim/sslworld.h"
#include "Vision/visionplugin.h"
#include "Decision/decisionplugin.h"
#include "Cmd2Sim/cmd2sim.h"
#include "UDPSender/udpsender.h"
#include "UDPReceiver/udpreceiver.h"
using namespace std;
SSLWorld* sim;
int main(){
    sim = SSLWorld::instance();
    VisionPlugin vm;
    DecisionPlugin dm_blue_left(false,false);
//    DecisionPlugin dm_right_yellow(true,true);
    Cmd2Sim c2s_blue(false);
//    Cmd2Sim c2s_yellow(true);
    UDPSender vision_sender("ssl_vision",10666);
//    UDPReceiver sim_packet_receiver("sim_packet",20011);
//    UDPSender blue_status("blue_status",30011);
//    UDPSender yellow_status("blue_status",30012);
    sim->link(&vm,"ssl_vision");
    sim->link(&vision_sender,"ssl_vision");
//    sim_packet_receiver.link(sim,"sim_packet");
    c2s_blue.link(sim,"sim_signal");
    vm.link(&dm_blue_left,"zss_vision");
//    vm.link(&dm_right_yellow,"zss_vision");
    dm_blue_left.link(&c2s_blue,"zss_cmds");
//    dm_right_yellow.link(&c2s_yellow,"zss_cmds");
    c2s_blue.link(sim,"sim_packet");
//    c2s_yellow.link(sim,"sim_packet");
    sim->start();
    vm.start();
    vision_sender.start();
    dm_blue_left.start();
//    dm_right_yellow.start();
    c2s_blue.start();
//    c2s_yellow.start();
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
	return 0;
}
