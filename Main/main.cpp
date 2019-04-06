#include <iostream>
#include <thread>
#include "dllexport.h"
#include "sslworld.h"
#include "visionmodule.h"
using namespace std;
DLL_IMPORT extern SSLWorld* _w;
int main(){
    _w = new SSLWorld();
    VisionModule vm;
    _w->link(&vm,"ssl_vision");
    vm.link(_w,"sim_signal");
    std::thread t1([&]{_w->run();});
    std::thread t2([&]{vm.run();});
    t1.join();
    t2.join();
	return 0;
}
