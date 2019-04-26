#include "CommandInterface.h"
#include "ServerInterface.h"
#include "OptionModule.h"
#include <iostream>
#include "grSim_Packet.pb.h"
#include "zss_cmd.pb.h"
#include "staticparams.h"
#include "game_state.h"
#include "parammanager.h"
#include "param.h"
#include <cmath>
#include <QUdpSocket>
#include "RobotSensor.h"
#include <thread>
CCommandInterface* CCommandInterface::_instance = 0;
namespace {
int SIM_PORT = 0;
int SELF_PORT = 0;
int CHIP_ANGLE = 1;
int TEAM;
Robots_Command robots_command;
Robot_Command *robot_command[Param::Field::MAX_PLAYER];
std::thread *_thread = nullptr;
}

CCommandInterface::CCommandInterface(const COptionModule *pOption)
    : pOption(pOption), receiveSocket(nullptr), command_socket(nullptr) {
    bool isYellow = false;
    ZSS::ZParamManager::instance()->loadParam(SIM_PORT, "AlertPorts/SimPort", 20011);
    ZSS::ZParamManager::instance()->loadParam(SELF_PORT, "Ports/SimSelfPort", 30015);
    ZSS::ZParamManager::instance()->loadParam(CHIP_ANGLE, "Simulator/ChipAngle", 45);
    ZSS::ZParamManager::instance()->loadParam(isYellow, "ZAlert/IsYellow", false);
    TEAM = isYellow ? PARAM::YELLOW : PARAM::BLUE;
    command_socket = new QUdpSocket();
    receiveSocket = new QUdpSocket();
    receiveSocket->bind(QHostAddress::AnyIPv4, ZSS::Athena::CONTROL_BACK_RECEIVE[TEAM], QUdpSocket::ShareAddress);
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
        ::robot_command[i] = ::robots_command.add_command();
    }
    _thread = new std::thread([ = ] {receiveInformation();});
    _thread->detach();
}

CCommandInterface::~CCommandInterface(void) {
    //delete _pServerIf;
}

void CCommandInterface::setSpeed(int num, double dribble, double vx, double vy, double vr) {
    int number = num - 1;//找到+1处后可以把此处去掉，车号变回0-11
    if (number < 0 || number > Param::Field::MAX_PLAYER - 1) {
        //std::cout << "Robot Number Error in Simulator setSpeed" << number<< std::endl;
        return;
    }
    commands[number].dribble_spin = dribble;
    commands[number].velocity_x = vx;
    commands[number].velocity_y = vy;
    commands[number].velocity_r = vr;

}
void CCommandInterface::setKick(int num, double kp, double cp) {
    int number = num - 1;//找到+1处后可以把此处去掉，车号变回0-11
    if (number < 0 || number > Param::Field::MAX_PLAYER - 1) {
        //std::cout << "Robot Number Error in Simulator setKick" << std::endl;
        return;
    }
    commands[number].flat_kick = kp;
    commands[number].chip_kick = cp;
}

void CCommandInterface::sendCommands() {
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
        ::robot_command[i]->set_robot_id(i);
        ::robot_command[i]->set_velocity_x(commands[i].velocity_x);
        ::robot_command[i]->set_velocity_y(commands[i].velocity_y);
        ::robot_command[i]->set_velocity_r(commands[i].velocity_r);
        ::robot_command[i]->set_dribbler_spin(commands[i].dribble_spin);
        if(commands[i].chip_kick < 0.001) { //flat kick
            ::robot_command[i]->set_kick(false);
            ::robot_command[i]->set_power(commands[i].flat_kick);
        } else {
            ::robot_command[i]->set_kick(true);
            ::robot_command[i]->set_power(commands[i].chip_kick);
        }
    }
    int size = ::robots_command.ByteSize();
    QByteArray data(size, 0);
    ::robots_command.SerializeToArray(data.data(), size);
    command_socket->writeDatagram(data.data(), size, QHostAddress(QString::fromStdString(ZSS::LOCAL_ADDRESS)), ZSS::Athena::CONTROL_SEND[TEAM]);
    for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
        ::robot_command[i]->Clear();
        commands[i].chip_kick = 0;
        commands[i].dribble_spin = 0;
        commands[i].flat_kick = 0;
        commands[i].velocity_r = 0;
        commands[i].velocity_x = 0;
        commands[i].velocity_y = 0;
    }
}

void CCommandInterface::receiveInformation() {
    Robot_Status robot_status;
    QByteArray datagram;
    QHostAddress address;
    quint16 udp_port;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (receiveSocket->state() == QUdpSocket::BoundState && receiveSocket->hasPendingDatagrams()) {
            datagram.resize(receiveSocket->pendingDatagramSize());
            receiveSocket->readDatagram(datagram.data(), datagram.size(), &address, &udp_port);
            robot_status.ParseFromArray(datagram, datagram.size());
            auto&& id = robot_status.robot_id();
            if(!(id >= 0 && id < Param::Field::MAX_PLAYER)) {
                qDebug() << "ERROR received error robot id in command interface." << id;
                continue;
            }
            auto& msg = RobotSensor::Instance()->robotMsg[id];
            msg._mutex.lock();
            msg.infrared = robot_status.infrared();
            msg.chip_kick = robot_status.chip_kick() ? 3 : (msg.chip_kick);
            msg.flat_kick = robot_status.flat_kick() ? 3 : (msg.flat_kick);
            msg._mutex.unlock();
//            qDebug() << address << udp_port;
//            qDebug() << id << msg.infrared << RobotSensor::Instance()->robotMsg[id].infrared
//                     << msg.chip_kick
//                     << msg.flat_kick;
        }
    }
}

CCommandInterface* CCommandInterface::instance(const COptionModule *pOption) {
    if(_instance == 0)
        _instance = new CCommandInterface(pOption);
    return _instance;
}

void CCommandInterface::destruct() {
    if(_instance)
        delete _instance;
}
