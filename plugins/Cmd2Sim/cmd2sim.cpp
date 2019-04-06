#include "cmd2sim.h"
#include "staticparams.h"
#include "zss_cmd.pb.h"
#include "grSim_Packet.pb.h"
#include "geometry.h"
namespace{
    float trans_dribble(float dribble) {
        return dribble / 3.0;
    }
    float trans_length(float v) {
        return v / 100.0;
    }
    float trans_r(float v) {
        return v;
    }
}
Cmd2Sim::Cmd2Sim(bool isTeamYellow):isTeamYellow(isTeamYellow){}
void Cmd2Sim::run(){
    ZSData data,sendData;
    Robots_Command zss_cmds;
    grSim_Packet packet;
    auto sim_cmds = packet.mutable_commands();
    while(true){
        // pre
        sim_cmds->Clear();
        sim_cmds->set_timestamp(0);
        sim_cmds->set_isteamyellow(isTeamYellow);

        // receive & parse with `ZSData`
        receive("zss_cmds",data);
        zss_cmds.ParseFromArray(data.data(),data.size());

        // main part
        auto commandSize = zss_cmds.command_size();
        for(int i=0;i<commandSize;i++){
            auto zss_cmd = zss_cmds.command(i);
            auto sim_cmd = sim_cmds->add_robot_commands();
            sim_cmd->set_id(zss_cmd.robot_id());
            sim_cmd->set_wheelsspeed(false);
            sim_cmd->set_spinner(zss_cmd.dribbler_spin()>0.1);
            sim_cmd->set_wheelsspeed(false);
            //set flatkick or chipkick
            if (!zss_cmd.kick()) {
                sim_cmd->set_kickspeedz(0);
                sim_cmd->set_kickspeedx(trans_length(zss_cmd.power()));
            } else {
                double radian = ZSS::Sim::CHIP_ANGLE * ZSS::Sim::PI / 180.0;
                double vx = sqrt(trans_length(zss_cmd.power()) * ZSS::Sim::G / 2.0 / tan(radian));
                double vz = vx * tan(radian);
                sim_cmd->set_kickspeedz(vx);
                sim_cmd->set_kickspeedx(vz);
            }
            //set velocity and dribble
            double vx = zss_cmd.velocity_x();
            double vy = zss_cmd.velocity_y();
            double vr = zss_cmd.velocity_r();
            double dt = 1. / 60;
            double theta = - vr * dt;
            CVector v(vx, vy);
            v = v.rotate(theta);
            if (fabs(theta) > 0.00001) {
                v = v * theta / (2 * sin(theta / 2));
                vx = v.x();
                vy = v.y();
            }
            sim_cmd->set_veltangent(trans_length(vx));
            sim_cmd->set_velnormal(-trans_length(vy));
            sim_cmd->set_velangular(-trans_r(vr));
            sim_cmd->set_spinner(trans_dribble(zss_cmd.dribbler_spin()));
        }

        // serialize & send with `ZSData`
        auto size = packet.ByteSize();
        sendData.resize(size);
        packet.SerializeToArray(sendData.ptr(),size);
        publish("sim_cmds",sendData);
    }
}
