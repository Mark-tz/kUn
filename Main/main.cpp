#include <iostream>
#include <thread>
#include "dllexport.h"
#include "Sim/sslworld.h"
#include "Vision/visionmodule.h"
#include "Decision/decisionmodule.h"
using namespace std;
SSLWorld* sim;
int main(){
    sim = SSLWorld::instance();
    VisionModule vm;
    DecisionModule dm;
    sim->link(&vm,"ssl_vision");
    vm.link(sim,"sim_signal");
    sim->start();
    vm.start();
    dm.start();
    while(true){}
	return 0;
}
