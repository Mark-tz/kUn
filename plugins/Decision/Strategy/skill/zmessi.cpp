#include "zmessi.h"
#include "WorldDefine.h"
#include "SkillUtils.h"
#include "Factory.h"
#include "DribbleStatus.h"
#include "KickStatus.h"
namespace{
    enum Command{ GETBALL = 1,TURNLEFT,TURNRIGHT,KICK};
    const int R = 5;
    const int KP = 30;
}
CZMessi::CZMessi(){}
void CZMessi::plan(const CVisionModule *pVision){
//    const MobileVisionT& ball = pVision->Ball();
    const CGeoPoint target = task().player.pos;
    int vecNumber = task().executor;
//    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
//    int oppNumber = ZSkillUtils::instance()->getTheirBestPlayer();
//    const PlayerVisionT& enemy = pVision->TheirPlayer(oppNumber);
//    int c = ZGlobalControl::instance()->MessiCommand();
    int c = 0;
    switch(c){
    case GETBALL: setSubTask(PlayerRole::makeItGetBallV4(vecNumber, PlayerStatus::DRIBBLE, target, CGeoPoint(-9999, -9999), 0));
        break;
    case TURNLEFT: setSubTask(PlayerRole::makeItRun(vecNumber,0,0,R));
        break;
    case TURNRIGHT: setSubTask(PlayerRole::makeItRun(vecNumber,0,0,-R));
        break;
    case KICK: KickStatus::Instance()->setKick(vecNumber,KP);
    default:
//        setSubTask(PlayerRole::makeItRun(vecNumber,0,0,R));
        setSubTask(PlayerRole::makeItRun(vecNumber,0,0,0));
    }
    DribbleStatus::Instance()->setDribbleCommand(vecNumber,3);
    return CStatedTask::plan(pVision);
}
CPlayerCommand* CZMessi::execute(const CVisionModule* pVision) {
    if (subTask()) {
        return subTask()->execute(pVision);
    }
    return nullptr;
}
