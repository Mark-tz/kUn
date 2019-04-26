#ifndef STATICPARAMS_H
#define STATICPARAMS_H
//change param for 2018 rule
//wait for change camera number
#include <QString>
namespace PARAM {
const bool DEBUG = false;
const int CAMERA = 4;
const int SENDROBOTNUM = 8;
const int ROBOTNUM = 12;// max allow robot on the playgroung
const int ROBOTMAXID = 12;
const int BALLNUM = 20;
const int BLUE = 0;
const int YELLOW = 1;
const int BALLMERGEDISTANCE = 140;
const int ROBOTMERGEDOSTANCE = 100;
const int TEAMS = 2;
}
namespace ZSS {
const std::string ZSS_ADDRESS = "233.233.233.233";
const std::string SSL_ADDRESS = "224.5.23.2";
const std::string REF_ADDRESS = "224.5.23.1";
const std::string LOCAL_ADDRESS = "127.0.0.1";
namespace Jupyter {
const int CONTROL_BACK_SEND = 10002;
const int CONTROL_RECEIVE = 10001;
}
namespace Medusa {
const int DEBUG_MSG_SEND[2] = {20001,20002};
}
namespace Sim {
const int SIM_RECEIVE = 30001;
const double G = 9.8;
const double PI = 3.14159265358979323846;
const int CHIP_ANGLE = 45;
const int BLUE_STATUS_PORT = 30011;
const int YELLOW_STATUS_PORT = 30012;
}
namespace Athena {
const int CONTROL_SEND[PARAM::TEAMS] = {50001, 50002};
const int CONTROL_BACK_RECEIVE[PARAM::TEAMS] = {60001, 60002};
const int VISION_SEND[PARAM::TEAMS] = {23333, 23334};
const int SEND_TO_PYTHON = 41001;
const int DEBUG_MSG_RECEIVE[2] = {20001,20002};
const int SIM_SEND = 20011;
const double FRAME_RATE = 61;
const float TOTAL_LATED_FRAME = 4.7f;
const double BALL_DELC_CHANGE_POINT = 250;
const double BALL_FAST_DEC = 360;
const double BALL_SLOW_DEC = 27.5;
}
}
#endif // STATICPARAMS_H
