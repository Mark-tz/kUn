#include "OpenSpeedCircle.h"
#include <CommandFactory.h>
#include "VisionModule.h"
#include "Factory.h"
#include "DribbleStatus.h"
#include "CMmotion.h"
#include <iostream>

COpenSpeedCircle::COpenSpeedCircle()
{

}

CPlayerCommand* COpenSpeedCircle::execute(const CVisionModule* pVision) {
    const PlayerVisionT& start = pVision->OurPlayer(task().executor);
    const double dist2Circle = task().player.speed_x;
    const int rotateMethod = task().player.rotdir;
    const double dirDiff = task().player.speed_y;
    const double finalAngle = task().player.angle;
    const int open_speed_version = task().player.flag;
    PlayerPoseT nextStep;
    if ( open_speed_version == 1 )
        openSpeedCircle(start, dist2Circle, rotateMethod, finalAngle, nextStep,
                        dirDiff);
    else if ( open_speed_version == 2 )
        openSpeedCircleV2(start, dist2Circle, rotateMethod, finalAngle, nextStep,
                          dirDiff);

    int num = task().executor;

    double speedX = nextStep.Vel().x(); // x方向平动速度
    double speedY = nextStep.Vel().y(); // y方向平动速度
    double speedR = nextStep.RotVel(); // 转动速度
    double dribblePower = 3;//DribbleStatus::Instance()->getDribbleCommand(num);
//     std::cout<<"num:"<<num<<" "<<dribblePower<<task().player.rotdir<<std::endl;
    return CmdFactory::Instance()->newCommand(CPlayerSpeedV2(num, speedX, speedY, speedR, dribblePower));
}
