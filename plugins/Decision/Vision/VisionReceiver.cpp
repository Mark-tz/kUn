#define WIN32_LEAN_AND_MEAN
#include "VisionReceiver.h"
#include <CommandInterface.h>
#include <OptionModule.h>
#include <RefereeBoxIf.h>
#include <playmode.h>
#include "parammanager.h"
#include "staticparams.h"
#include <thread>
#include <mutex>
#include "zsplugin.hpp"
#include "game_state.h"

Semaphore visionEvent;
Semaphore vision_receive_semaphore(0);
VisionReceiver* VisionReceiver::_instance = 0;
std::mutex* decisionMutex = new std::mutex(); ///<用来线程互斥，决策线程和图像获取后唤醒，同上 visionEvent 配合使用
extern Semaphore vision_semaphore;
Semaphore vision_finish_semaphore(0);

namespace {
std::thread *_thread = nullptr;
std::thread *_thread2 = nullptr;
bool DEBUG_MODE = false;
COptionModule *_pOption = 0;
CRefereeBoxInterface *_referee = 0; //裁判盒
std::mutex* visionMutex = 0; ///<用来线程互斥，保证数据完整
const int VISION_PORT = 12345;
const int _RecentLogLength =  30; //seconds
bool isYellow = false;
}

VisionReceiver::VisionReceiver(COptionModule *pOption): _threadAlive(false) {
    _pOption = pOption;
    _info.cycle = 0;


    ///> 启动裁判盒
    _referee = RefereeBoxInterface::Instance();
    _referee->start();

    ///> 初始化互斥锁
    visionMutex = new std::mutex();

    ///> 启动视觉接收线程
    _thread = new std::thread([ = ] {getMessage();});
    _thread->detach();
    _threadAlive = true;

    //配置vision接收端口
    ZSS::ZParamManager::instance()->loadParam(isYellow, "ZAlert/IsYellow", false);
    int port = ZSS::Athena::VISION_SEND[isYellow ? PARAM::YELLOW : PARAM::BLUE];
    visionSocket = new QUdpSocket();
    visionSocket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress);

    _thread2 = new std::thread([ = ] {ReceiveVision();});

}

VisionReceiver::~VisionReceiver(void) {
    if(visionMutex)
        delete visionMutex;
    if(_thread)
        delete _thread;
    if(_thread2)
        delete _thread2;
}

VisionReceiver* VisionReceiver::instance(COptionModule *pOption) {
    if(_instance == 0)
        _instance = new VisionReceiver(pOption);
    return _instance;
}

void VisionReceiver::destruct() {
    delete _instance;
}

void VisionReceiver::InitInfo(CServerInterface::VisualInfo &temp) {
    for (int i = 0; i <  Param::Field::MAX_PLAYER_NUM; i++) {
        temp.ourRobotIndex[i] = 0;
        temp.player[i].dir = 0;
        temp.player[i].pos.valid = false;
        temp.player[i].pos.x = -999999;
        temp.player[i].pos.y = -999999;
        temp.theirRobotIndex[i] = 0;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].dir = 0;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].pos.valid = false;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].pos.x = -999999;
        temp.player[i + Param::Field::MAX_PLAYER_NUM].pos.y = -999999;
    }
}

void VisionReceiver::ReceiveVision() {
    int i;
    QByteArray buffer;
    int robots_blue_n, robots_yellow_n;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        while (visionSocket->state() == QUdpSocket::BoundState && visionSocket->hasPendingDatagrams()) {
            buffer.resize(visionSocket->pendingDatagramSize());
            visionSocket->readDatagram(buffer.data(), buffer.size());
            detectionFrame.ParseFromArray(buffer, buffer.size());

            robots_blue_n = std::min(detectionFrame.robots_blue_size(), 8);
            robots_yellow_n = std::min(detectionFrame.robots_yellow_size(), 8);
            InitInfo(temp);

            bool ballFound = detectionFrame.has_ball();
            if (ballFound) {
                auto & ball = detectionFrame.ball();
                if (ball.x() < -30000 && ball.y() < -30000) {
                    //理论上不应该进入这个if
                    temp.ball.x = -32768;
                    temp.ball.x = -32768;
                    temp.ball.valid = false;
                } else {
                    temp.ball.x = ball.x() / 10;
                    temp.ball.y = -ball.y() / 10;
                    temp.ball.valid = true;
                    temp.BallState = (ballState)ball.ball_state();
                    temp.BallLastTouch = ball.last_touch();
                    temp.BallVel.setVector(ball.vel_x() / 10, -ball.vel_y() / 10);
                }
            } else {
                std::cout << "Ball not Found!!!" << std::endl;
            }
            int index;
            _pOption->MyColor() == TEAM_BLUE ? index = 0 : index = Param::Field::MAX_PLAYER_NUM;
            for (i = 0; i < robots_blue_n; i++) {
                auto& robot = detectionFrame.robots_blue(i);
                auto id = robot.robot_id();
//                if (id >= 0 && id < Param::Field::MAX_PLAYER_NUM) {
//                    _pOption->MyColor() == TEAM_BLUE ? temp.ourRobotIndex[index] = id + 1 :
//                            temp.theirRobotIndex[index - Param::Field::MAX_PLAYER_NUM] = id + 1;
//                    temp.player[index].pos.x = robot.x() / 10;
//                    temp.player[index].pos.y = -robot.y() / 10;
//                    temp.player[index].pos.valid = true;
//                    temp.player[index].dir = -robot.orientation();
//                    temp.player[index].vel.setVector(robot.vel_x() / 10, -robot.vel_y() / 10);
//                    temp.player[index].dirvel = -robot.rotate_vel();
//                    index++;
//                }
                if (id >= 0 && id < Param::Field::MAX_PLAYER_NUM) {
                    index = _pOption->MyColor() == TEAM_BLUE ? id : id + Param::Field::MAX_PLAYER_NUM;
                    _pOption->MyColor() == TEAM_BLUE ? temp.ourRobotIndex[index] = id + 1 :
                            temp.theirRobotIndex[index - Param::Field::MAX_PLAYER_NUM] = id + 1;
                    temp.player[index].pos.x = robot.x() / 10;
                    temp.player[index].pos.y = -robot.y() / 10;
                    temp.player[index].pos.valid = true;
                    temp.player[index].dir = -robot.orientation();
                    temp.player[index].vel.setVector(robot.vel_x() / 10, -robot.vel_y() / 10);
                    temp.player[index].dirvel = -robot.rotate_vel();
//                    index++;
                }
            }
            _pOption->MyColor() == TEAM_BLUE ? index = Param::Field::MAX_PLAYER_NUM : index = 0;
            for (i = 0; i < robots_yellow_n; i++) {
                auto& robot = detectionFrame.robots_yellow(i);
                auto id = robot.robot_id();
//                if (id >= 0 && id < Param::Field::MAX_PLAYER_NUM) {
//                    _pOption->MyColor() == TEAM_YELLOW ? temp.ourRobotIndex[index] = id + 1 :
//                            temp.theirRobotIndex[index - Param::Field::MAX_PLAYER_NUM] = id + 1;
//                    temp.player[index].pos.x = robot.x() / 10;
//                    temp.player[index].pos.y = -robot.y() / 10;
//                    temp.player[index].pos.valid = true;
//                    temp.player[index].dir = -robot.orientation();
//                    temp.player[index].vel.setVector(robot.vel_x() / 10, -robot.vel_y() / 10);
//                    temp.player[index].dirvel = -robot.rotate_vel();
//                    index++;
//                }
                if (id >= 0 && id < Param::Field::MAX_PLAYER_NUM) {
                    index = _pOption->MyColor() == TEAM_YELLOW ? id : id + Param::Field::MAX_PLAYER_NUM;
                    _pOption->MyColor() == TEAM_YELLOW ? temp.ourRobotIndex[index] = id + 1 :
                            temp.theirRobotIndex[index - Param::Field::MAX_PLAYER_NUM] = id + 1;
                    temp.player[index].pos.x = robot.x() / 10;
                    temp.player[index].pos.y = -robot.y() / 10;
                    temp.player[index].pos.valid = true;
                    temp.player[index].dir = -robot.orientation();
                    temp.player[index].vel.setVector(robot.vel_x() / 10, -robot.vel_y() / 10);
                    temp.player[index].dirvel = -robot.rotate_vel();
//                    index++;
                }
            }
            vision_receive_semaphore.signal();
        }
    }
}

ZSS_THREAD_FUNCTION void VisionReceiver::getMessage() {
    ///> 接受图像周期
    static unsigned int cycle = 0;

    ///> 图像信息接受，需要锁的配合，并进入循环
    while (true) {
        //cout << "1 : receiver " << endl;
        //CServerInterface::VisualInfo temp = {};
        RefRecvMsg tempRefMsg;
        vision_receive_semaphore.wait();
        //(VisionReceiver::_visionMessage)->message2VisionInfo(temp);	// 图像接受线程转换图像数据
        temp.mode = _referee->getPlayMode();		// 裁判盒命令接受线程得到裁判盒指令,并设置相应mode
        temp.ballPlacePosition.x = _referee->getBallPlacementPosX();
        temp.ballPlacePosition.y = _referee->getBallPlacementPosY();
        temp.ballPlacePosition.setValid(true);
        tempRefMsg.blueGoal = _referee->getBlueGoalNum();
        tempRefMsg.yellowGoal = _referee->getYellowGoalNum();
        tempRefMsg.timeRemain = _referee->getRemainTime();
        tempRefMsg.blueGoalie = _referee->getBlueGoalie();
        tempRefMsg.yellowGoalie = _referee->getYellowGoalie();

        decisionMutex->lock();		// 决策加锁

        visionMutex->lock();		// 图像加锁
        VisionReceiver::instance()->_info = temp;
        VisionReceiver::instance()->_recvMsg = tempRefMsg;
        VisionReceiver::instance()->_info.cycle = ++cycle;  // 暂时这么代替，fix me!!! 没有用到图像里面的cycle,而是策略自己记录cycle,收到一个图像便加1;

        visionMutex->unlock();		// 图像解锁
        vision_finish_semaphore.signal();
        visionEvent.signal();
        decisionMutex->unlock();	// 决策解锁
    }

    ///> 退出
    VisionReceiver::instance()->_threadAlive = false;
    visionEvent.signal();

    return;
}

bool VisionReceiver::getVisionInfo(CServerInterface::VisualInfo & info, RefRecvMsg & msg) const {
    if(_threadAlive) {
        visionMutex->lock();		// 图像加锁
        info = this->_info;			// 将得到的图像数据输出给info
        msg  = this->_recvMsg;
        visionMutex->unlock();		// 图像解锁
    }

    return _threadAlive;
}
