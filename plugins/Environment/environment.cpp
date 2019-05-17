#include "environment.h"
Environment::Environment()
    :sim(SSLWorld::instance())
    ,vm(new VisionPlugin())
    ,dm_blue_left(new DecisionPlugin(false,false))
    ,c2s_blue(new Cmd2Sim(false))
    ,vision_sender(nullptr){
    declare_publish("sim_signal");

    sim->link(vm,"ssl_vision");
    vm->link(dm_blue_left,"zss_vision");
    dm_blue_left->link(c2s_blue,"zss_cmds");
    c2s_blue->link(sim,"sim_packet");
    this->link(sim,"sim_signal");
}
Environment::Environment(unsigned int port):Environment(){
    vision_sender = new UDPSender("ssl_vision","224.5.23.2",port);
    sim->link(vision_sender,"ssl_vision");
}
Environment::~Environment(){
    delete vm;
    delete dm_blue_left;
    delete c2s_blue;
    delete vision_sender;
}
void Environment::start_all(){
    sim->start();
    vm->start();
    dm_blue_left->start();
    c2s_blue->start();
    if(vision_sender)
        vision_sender->start();
}
void Environment::reset(){

}
void Environment::render(){}
int* Environment::step(int* arr,int size){
    std::cout << "array input : [";
    for(int i=0;i<size;i++){
        std::cout << arr[i] << ' ';
    }
    std::cout << ']' << std::endl;

    int* val = new int[5];
    for(int i=0;i<5;i++){
        val[i] = 5-i;
    }
    return val;
}
void Environment::run(){}
