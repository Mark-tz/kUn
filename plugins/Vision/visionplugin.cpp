#include "visionplugin.h"
#include "staticparams.h"
#include "setthreadname.h"
VisionPlugin::VisionPlugin() {
    declare_receive("ssl_vision");
    declare_publish("sim_signal");
    declare_publish("zss_vision");
}
VisionPlugin::~VisionPlugin() {
}
VisionPlugin::VisionPlugin(const VisionPlugin&){}
void VisionPlugin::updateVel(OriginMessage& message) {
    if (message.ballSize > 0) {
        updateBallVel(message);
    }
    updateRobotVel(PARAM::BLUE, message);
    updateRobotVel(PARAM::YELLOW, message);
}
void VisionPlugin::updateRobotVel(int team, OriginMessage& message) {
    for (auto i = 0; i < message.robotSize[team]; i++) {
        Robot & robot = message.robot[team][i];
        auto & playerPosVel = _robotPosFilter[team][robot.id].update(robot.pos.x(), robot.pos.y());
        CGeoPoint filtPoint (playerPosVel(0, 0), playerPosVel(1, 0));
        CVector PlayVel(playerPosVel(2, 0), playerPosVel(3, 0));

        auto &playerRotVel = _robotDirFilter[team][robot.id].update(std::cos(robot.angle), std::sin(robot.angle));
        double filterDir = std::atan2(playerRotVel(1, 0), playerRotVel(0, 0));
        double rotVel = playerRotVel(2, 0) * std::cos(90 * 3.1416 / 180 + filterDir)
                        + playerRotVel(3, 0) * std::sin(90 * 3.1416 / 180 + filterDir);
        robot.angle = filterDir;
        robot.rotateVel = rotVel * ZSS::Athena::FRAME_RATE;
        robot.pos = filtPoint;
        robot.velocity = PlayVel * ZSS::Athena::FRAME_RATE;
    }
}

void VisionPlugin::updateBallVel(OriginMessage & message) {
    auto & tempMatrix = ballKalmanFilter.update(message.ball[0].pos);
    CGeoPoint filtPoint(tempMatrix(0, 0), tempMatrix(1, 0));
    CVector ballVel(tempMatrix(2, 0)* ZSS::Athena::FRAME_RATE, tempMatrix(3, 0)*ZSS::Athena::FRAME_RATE);
    message.ball[0].fill(filtPoint.x(), filtPoint.y(), ballVel);
}

void VisionPlugin::parseVisionMessage(SSL_WrapperPacket& packet, OriginMessage& message) {
    const SSL_DetectionFrame& detection = packet.detection();
    int ballSize = detection.balls_size();
    int blueSize = detection.robots_blue_size();
    int yellowSize = detection.robots_yellow_size();

//    std::cout << "ballsize : " << ballSize << " blue : " << blueSize << " yellow : " << yellowSize << std::endl;
    for (int i = 0; i < ballSize; i++) {
        const SSL_DetectionBall& ball = detection.balls(i);
        message.addBall(CGeoPoint(ball.x(), ball.y()));
    }
    for (int i = 0; i < blueSize; i++) {
        const SSL_DetectionRobot& robot = detection.robots_blue(i);
        if (robot.robot_id() < PARAM::ROBOTMAXID) {
            message.addRobot(BLUE, robot.robot_id(), CGeoPoint(robot.x(), robot.y()), robot.orientation());
        }
    }
    for (int i = 0; i < yellowSize; i++) {
        const SSL_DetectionRobot& robot = detection.robots_yellow(i);
        if (robot.robot_id() < PARAM::ROBOTMAXID) {
            message.addRobot(YELLOW, robot.robot_id(), CGeoPoint(robot.x(), robot.y()), robot.orientation());
        }
    }
}

void VisionPlugin::encodeMessage(Vision_DetectionFrame &detectionFrame, OriginMessage & message) {
    Vision_DetectionBall* detectionBall;
    Vision_DetectionRobot* detectionRobot[2][PARAM::ROBOTMAXID];
    if (message.ballSize > 0) {
        detectionBall = detectionFrame.mutable_ball();
        detectionBall->set_x(message.ball[0].pos.x());
        detectionBall->set_y(message.ball[0].pos.y());//to fix a role match bug 2018.6.15
        CVector TransferVel(message.ball[0].velocity.x(), message.ball[0].velocity.y());
        detectionBall->set_vel_x(TransferVel.x());
        detectionBall->set_vel_y(TransferVel.y());
    }
    for (int i = 0; i < message.robotSize[PARAM::BLUE]; i++) {
        detectionRobot[PARAM::BLUE][i] = detectionFrame.add_robots_blue();
        detectionRobot[PARAM::BLUE][i]->set_x(message.robot[PARAM::BLUE][i].pos.x());
        detectionRobot[PARAM::BLUE][i]->set_y(message.robot[PARAM::BLUE][i].pos.y());
        detectionRobot[PARAM::BLUE][i]->set_orientation(message.robot[PARAM::BLUE][i].angle);
        detectionRobot[PARAM::BLUE][i]->set_robot_id(message.robot[PARAM::BLUE][i].id);
        CVector TransferVel(message.robot[PARAM::BLUE][i].velocity.x(), message.robot[PARAM::BLUE][i].velocity.y());
        detectionRobot[PARAM::BLUE][i]->set_vel_x(TransferVel.x());
        detectionRobot[PARAM::BLUE][i]->set_vel_y(TransferVel.y());
        detectionRobot[PARAM::BLUE][i]->set_rotate_vel(message.robot[PARAM::BLUE][i].rotateVel);
    }
    for (int i = 0; i < message.robotSize[PARAM::YELLOW]; i++) {
        if (i == PARAM::SENDROBOTNUM) break;
        detectionRobot[PARAM::YELLOW][i] = detectionFrame.add_robots_yellow();
        detectionRobot[PARAM::YELLOW][i]->set_x(message.robot[PARAM::YELLOW][i].pos.x());
        detectionRobot[PARAM::YELLOW][i]->set_y(message.robot[PARAM::YELLOW][i].pos.y());
        detectionRobot[PARAM::YELLOW][i]->set_orientation(message.robot[PARAM::YELLOW][i].angle);
        detectionRobot[PARAM::YELLOW][i]->set_robot_id(message.robot[PARAM::YELLOW][i].id);
        CVector TransferVel(message.robot[PARAM::YELLOW][i].velocity.x(), message.robot[PARAM::YELLOW][i].velocity.y());
        detectionRobot[PARAM::YELLOW][i]->set_vel_x(TransferVel.x());
        detectionRobot[PARAM::YELLOW][i]->set_vel_y(TransferVel.y());
        detectionRobot[PARAM::YELLOW][i]->set_rotate_vel(message.robot[PARAM::YELLOW][i].rotateVel);
    }
}



void VisionPlugin::run() {
    SetThreadName("VisionPlugin");
    std::cout << "Vision plugin start!" << std::endl;
    ZSData data,sendData;
    SSL_WrapperPacket packet;
    Vision_DetectionFrame detectionFrame;
    while(true) {
        receive("ssl_vision", data);
        //Parse
        packet.ParseFromArray(data.data(), data.size());
        OriginMessage message;
        if (packet.has_detection()) {
            parseVisionMessage(packet, message);
        }
        updateVel(message);
        encodeMessage(detectionFrame, message);

        auto size = detectionFrame.ByteSize();
        sendData.resize(size);
        detectionFrame.SerializeToArray(sendData.ptr(), size);
        publish("zss_vision", sendData.ptr(), size);
        detectionFrame.Clear();
    }
}
