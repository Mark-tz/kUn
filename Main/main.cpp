#include <iostream>
#include <thread>
#include "dllexport.h"
#include <cstdio>
#include <chrono>
#include "zsplugin.hpp"

Semaphore a2b;
void a(){
    while(true){
        std::cout << "a2b start signal" << std::endl;
        a2b.signal();
        std::cout << "a2b end signal" << std::endl;
    }
}

void b(){
    while(true){
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "a2b start wait" << std::endl;
        a2b.wait();
        std::cout << "a2b end wait" << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(){
    std::cout << "start all" << std::endl;
    std::thread aa(a);
    std::thread bb(b);
    aa.join();
    bb.join();
    return 0;
}

//#include <Environment/environment.h>
//int main(){
//   std::vector<double> temp{0.2,0.0};
//   Environment env(10666);
//   env.start_all();
//   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//   env.reset();
//   while(true){
//       std::this_thread::sleep_for(std::chrono::microseconds(10000));
//       env.step(temp);
//   }
//	return 0;
//}

// #include "zsplugin.hpp"
// #include "Sim/sslworld.h"
// #include "Vision/visionplugin.h"
// #include "Decision/decisionplugin.h"
// #include "Cmd2Sim/cmd2sim.h"
// #include "UDPSender/udpsender.h"
// #include "UDPReceiver/udpreceiver.h"
// int main(){
//     SSLWorld& sim = SSLWorld::instance();
//     VisionPlugin* vm = new VisionPlugin();
//     Cmd2Sim* c2sb = new Cmd2Sim(false);
//     // DecisionPlugin* dm = new DecisionPlugin(false,false);
//     sim.link(vm,"ssl_vision");
//     // vm->link(dm,"zss_vision");
//     // dm->link(c2sb,"sim_packet");
//     c2sb->link(&sim,"sim_packet");
//     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//     while(true){
//         std::this_thread::sleep_for(std::chrono::microseconds(10000));
//     }
//     return 0;
// }

