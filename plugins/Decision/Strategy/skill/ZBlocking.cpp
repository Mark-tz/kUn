#include "ZBlocking.h"
#include <skill/Factory.h>
#include "BestPlayer.h"
#include "VisionModule.h"
#include "utils.h"
#include "GDebugEngine.h"
#include "geometry.h"
#include "WorldModel.h"
#include "defence/DefenceInfo.h"
#include "MarkingPosV2.h"
#include "SkillUtils.h"
#include "TaskMediator.h"


CZBlocking::CZBlocking(){
    _lastCycle = 0;
}

void CZBlocking::plan(const CVisionModule* pVision){
    static bool is_first = true;
    //内部状态进行重置
    if ( pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1 )
        setState(BEGINNING);

    int vecNumber = task().executor;
    int enemyNum = task().ball.Sender;
    CGeoPoint defPos = task().player.pos; //要防守的目标点

//    CGeoPoint defPos = ZSkillUtils::instance()->getTheirInterPoint(enemyNum);
    const PlayerVisionT& me = pVision->OurPlayer(vecNumber);
    const PlayerVisionT& enemy = pVision->TheirPlayer(enemyNum);
    CGeoPoint enemyPos = enemy.Pos();
    CGeoPoint mePos = me.Pos();

    TaskT BlockingTask(task());

    BlockingTask.player.pos = ZSkillUtils::instance()->getMarkingPoint(enemyPos, enemy.Vel(), 450, 450, 450, 300, defPos);
    BlockingTask.player.angle = CVector(CGeoPoint(Param::Field::PITCH_LENGTH/2.0,0) - me.Pos()).dir();
    BlockingTask.player.is_specify_ctrl_method = true;
    BlockingTask.player.specified_ctrl_method = CMU_TRAJ;

    GDebugEngine::Instance()->gui_debug_line(mePos, enemyPos, COLOR_WHITE);
    GDebugEngine::Instance()->gui_debug_line(BlockingTask.player.pos, enemyPos, COLOR_RED);

    setSubTask(TaskFactoryV2::Instance()->SmartGotoPosition(BlockingTask));

    _lastCycle = pVision->Cycle();
    CStatedTask::plan(pVision);
}


CPlayerCommand* CZBlocking::execute(const CVisionModule* pVision){
    if( subTask() ) return subTask()->execute(pVision);
    return NULL;
}
