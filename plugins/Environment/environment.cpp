#include "environment.h"
#include <random>
#include "grSim_Packet.pb.h"
#include "vision_detection.pb.h"
#include "KunDebugEngine.h"
namespace {
const double outside_meter = 4;
bool outside(const CGeoPoint& pos){
    return pos.x()>outside_meter||pos.x()<-outside_meter||pos.y()>outside_meter||pos.y()<-outside_meter;
}
double remap(const unsigned int origin_min,const unsigned int origin_max,const double target_min,const double target_max,const double input){
    const double a = double(origin_min);
    const double b = double(origin_max);
    const double c = target_min;
    const double d = target_max;
    return input*(d-c)/(b-a)+(b*c-d*a)/(b-a);
}
template<typename T>
T limitRange(T value, T minValue, T maxValue) {
    return value > maxValue ? maxValue : (value < minValue) ? minValue : value;
}
}
double Normalize(double angle)
{
    if (fabs(angle) > 10 ){
        std::cout<<angle<<" Normalize Error!!!!!!!!!!!!!!!!!!!!"<<std::endl;
        return 0;
    }
    const double M_2PI = M_PI * 2;
    // 快速粗调整
    angle -= (int)(angle / M_2PI) * M_2PI;

    // 细调整 (-PI,PI]
    while( angle > M_PI ) {
        angle -= M_2PI;
    }

    while( angle <= -M_PI ) {
        angle += M_2PI;
    }

    return angle;
}
Environment::Environment()
    :sim(SSLWorld::instance())
    ,vm(new VisionPlugin())
    ,c2s_blue(new Cmd2Sim(false))
    ,vision_sender(nullptr){
    feedback.state.resize(OBS_SPACE);
    declare_publish("sim_signal");
    declare_publish("sim_packet");
    declare_publish("zss_cmds");
    declare_receive("zss_vision");

    sim.link(vm,"ssl_vision");
    vm->link(this,"zss_vision");
    c2s_blue->link(&sim,"sim_packet");
    this->link(&sim,"sim_signal");
    this->link(&sim,"sim_packet");
}
Environment::Environment(unsigned int port):Environment(){
    vision_sender = new UDPSender("ssl_vision","224.5.23.2",port);
    handle_receiver = new UDPReceiver("sim_packet",20011);
    sim.link(vision_sender,"ssl_vision");
    handle_receiver->link(&sim,"sim_packet");
}
Environment::~Environment(){
    delete vm;
    delete c2s_blue;
    delete vision_sender;
    delete handle_receiver;
}
void Environment::start_all(){
    sim.start();
    vm->start();
    c2s_blue->start();
    if(vision_sender)
        vision_sender->start();
    if(handle_receiver)
        handle_receiver->start();

    publish("sim_signal");
}
FeedBack Environment::reset(){
//    static std::random_device rd;
//    static std::vector<double> static_action{0.0,0.0};

//    target.setX(remap(rd.min(),rd.max(),-1.0,1.0,double(rd())));
//    target.setY(remap(rd.min(),rd.max(),-1.0,1.0,double(rd())));
//    velocity.setVector(remap(rd.min(),rd.max(),-3.0,3.0,double(rd()))
//                       ,remap(rd.min(),rd.max(),-3.0,3.0,double(rd())));
//    setBallAndRobot(target,velocity,0,false,0,0);
    cycle = 0;
//    robot_vel.reset();
    std::this_thread::sleep_for(std::chrono::microseconds(10000));
    return this->step();
}
void Environment::render(){}
FeedBack Environment::step(){
    cycle++;
//    if(arr.size() != 2){
//        std::cout << "in step function : action dimention not correct : " << arr.size() << std::endl;
//        return {{0.0,0.0,0.0,0.0,0.0},0.0,true};
//    }
//    sendAction({arr[0],arr[1]});
    getState(feedback);
    publish("sim_signal");
    return feedback;
}
void Environment::run(){}
void Environment::setBallAndRobot(const CGeoPoint& p,const CVector& v,int id,bool team,double x,double y,double dir,bool turnon){
    static ZSData data;
    static grSim_Packet packet;
    auto replacement = packet.mutable_replacement();
    auto robot = replacement->add_robots();
    robot->set_x(x);
    robot->set_y(y);
    robot->set_id(id);
    robot->set_dir(dir);
    robot->set_yellowteam(team);
    robot->set_turnon(turnon);

    auto ball = replacement->mutable_ball();
    ball->set_x(p.x());
    ball->set_y(p.y());
//    ball->set_vx(v.x());
//    ball->set_vy(v.y());
    ball->set_vx(0);
    ball->set_vy(0);

    data.resize(packet.ByteSize());
    packet.SerializeToArray(data.ptr(),packet.ByteSize());
    publish("sim_packet",data);
    packet.Clear();
}
void Environment::getState(FeedBack& feedback){
    static ZSData data;
    static Vision_DetectionFrame frame;
    if(try_receive("yellow_status",data)){
        // do something
    }
    receive("zss_vision",data);
    frame.ParseFromArray(data.data(),data.size());
    int size = frame.robots_blue_size();
    if(size < 1){
        std::cout << "in getState function : robot size not correct : " << size << std::endl;
        return;
    }

    auto robot = frame.robots_blue(0);
    auto enemy = frame.robots_yellow(0);
    auto ball = frame.ball();
    CGeoPoint robotPos(robot.x()/1000.0,robot.y()/1000.0);
    CGeoPoint enemyPos(enemy.x()/1000.0,enemy.y()/1000.0);
    CGeoPoint ballPos(ball.x()/1000.0,ball.y()/1000.0);
    auto dir = double(robot.orientation());
    auto me2enemy = enemyPos-robotPos;
    auto enemyDir = me2enemy.dir();
    auto enemyDist = me2enemy.mod();
    auto me2ball = ballPos-robotPos;
    auto ballDir = me2ball.dir();
    auto ballDist = me2ball.mod();
//    feedback.reward = (-target_dist)/7*2 + (target_dist < limitRange(target_dist_max*0.2,0.1,0.3) ? 500 : 0);
//    feedback.done = (cycle > 500 || outside(pos) || target_dist < limitRange(target_dist_max*0.2,0.1,0.3));
//    feedback.state[0] = target_dist/7.0;
//    feedback.state[1] = (target_dir-dir)/M_PI;
//    feedback.state[2] = (velocity_dir-dir)/M_PI;
//    feedback.state[3] = velocity_mod/4.0;
    feedback.state[0] = enemyDist/7.0;
    feedback.state[1] = (enemyDir-dir)/M_PI;
    feedback.state[2] = ballDist/7.0;
    feedback.state[3] = (ballDir-dir)/M_PI;
    feedback.done = false;
    feedback.reward = 0;
}
//void Environment::sendAction(const Action& action){
//    static ZSData data;
//    static grSim_Packet packet;
//    auto* cmds = packet.mutable_commands();
//    cmds->set_isteamyellow(false);
//    cmds->set_timestamp(0.0);
//    auto* cmd = cmds->add_robot_commands();
//    cmd->set_id(0);
//    cmd->set_kickspeedx(0);
//    cmd->set_kickspeedz(0);
//    auto vel = CVector(action[0],action[1]);
////    std::cout << vel.mod() << std::endl;
//    auto new_vel = vel.rotate(-orientation);
//    robot_vel.update(new_vel.x(),new_vel.y());
//    cmd->set_veltangent(robot_vel.x());
//    cmd->set_velnormal(robot_vel.y());
////    cmd->set_velangular(action[2]);
//    cmd->set_velangular(0);
//    cmd->set_spinner(false);
//    cmd->set_wheelsspeed(false);
//    data.resize(packet.ByteSize());
//    packet.SerializeToArray(data.ptr(),packet.ByteSize());
//    publish("sim_packet",data);
//    packet.Clear();
//}
