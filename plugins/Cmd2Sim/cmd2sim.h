#ifndef __CMD2SIM_H__
#define __CMD2SIM_H__
#include "zsplugin.hpp"
// receive zss_cmds, and send grSim_Commands
class Cmd2Sim:public ZSPlugin{
public:
    Cmd2Sim(bool isTeamYellow);
    void run() override;
private:
    bool isTeamYellow;
};

#endif
