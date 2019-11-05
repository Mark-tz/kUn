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

#include <vector>
#define OBS_SPACE 4
#define ACC 1.5
#define FPS 75
struct FeedBack{
    std::vector<double> state;
    double reward;
    bool done;
};
class VelocityModel{
public:
    void reset(){
        velocity.setVector(0,0);
    }
    void update(double ax,double ay){
        double x = velocity.x();
        double y = velocity.y();
        velocity.setVector(x+ax*ACC/FPS,y+ay*ACC/FPS);
//        std::cout << x << ' ' << y << std::endl;
    }
    double x(){
        return velocity.x();
    }
    double y(){
        return velocity.y();
    }
    CVector velocity;
};
typedef std::array<double,3> Action;
class Environment : public ZSPlugin{
public:
    Environment();
    Environment(unsigned int);
    ~Environment();
    FeedBack reset();
    void render();
    FeedBack step();
    void start_all();
private:
    void run();
private:
    SSLWorld& sim;
    VisionPlugin* vm;
//    DecisionPlugin* dm_blue_left;
    Cmd2Sim* c2s_blue;
    UDPSender* vision_sender;
    UDPReceiver* handle_receiver;
private:
    void setBallAndRobot(const CGeoPoint&,const CVector&,int,bool,double,double,double dir = 0,bool turnon = true);
private:
    void getState(FeedBack& fb);
    void sendAction(const Action& action);
//    CGeoPoint target;
//    CVector velocity;
//    VelocityModel robot_vel;
//    double orientation;
    int cycle;
    FeedBack feedback;
private:
    //
};
#endif // __ENVIRONMENT_H__
