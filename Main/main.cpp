#include <iostream>
#include <thread>
#include "dllexport.h"
#include "sslworld.h"
#include "visionmodule.h"
using namespace std;
int main(){
    auto sim = SSLWorld::instance();
    VisionModule vm;
    sim.link(&vm,"ssl_vision");
    vm.link(&sim,"sim_signal");
    std::thread t1([&]{sim.run();});
    std::thread t2([&]{vm.run();});
    t1.join();
    t2.join();
	return 0;
}
