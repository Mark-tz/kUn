#include "GoImmortalRush.h"
#include <utils.h>
#include "skill/Factory.h"
#include <CommandFactory.h>
#include <sstream>
#include <TaskMediator.h>
#include <ControlModel.h>
#include <robot_power.h>
#include <DribbleStatus.h>
#include "PlayInterface.h"
#include <GDebugEngine.h>
#include "DynamicsSafetySearch.h"
#include "CMmotion.h"
#include <fstream>
#include "SkillUtils.h"


namespace {
	/// 调试开关
    bool verbose = true;
	bool DSS_AVOID = true;

	/// 用于解决到点晃动的问题
	const double DIST_REACH_CRITICAL = 2;	// [unit : cm]
    const double SlowFactor = 0.5;
    const double FastFactor = 1.2;

    /// 底层运动控制参数 ： 默认增大平动的控制性能
    double MAX_RUSH_TRANSLATION_ACC;
    double MAX_RUSH_TRANSLATION_SPEED;
    double MAX_RUSH_ROTATE_ACC;
    double MAX_RUSH_ROTATE_SPEED;
    double MAX_RUSH_MIDROTATE_SPEED;

    int startedFlag[Param::Field::MAX_PLAYER];
    int rushFlag[Param::Field::MAX_PLAYER];
    int arrivedFlag[Param::Field::MAX_PLAYER];
    double rushTime[Param::Field::MAX_PLAYER];
    int SAO_ACTION;
    const double penaltyAvoidDist = Param::Vehicle::V2::PLAYER_SIZE;
}
using namespace Param::Vehicle::V2;

/// 构造函数 ： 参数初始化
CGoImmortalRush::CGoImmortalRush()
{
    ZSS::ZParamManager::instance()->loadParam(MAX_RUSH_TRANSLATION_ACC, "CGotoPositionV2/MRushTranslationAcc", 800);
    ZSS::ZParamManager::instance()->loadParam(MAX_RUSH_TRANSLATION_SPEED, "CGotoPositionV2/MRushTranslationSpeed", 400);
    ZSS::ZParamManager::instance()->loadParam(MAX_RUSH_ROTATE_ACC, "CGotoPositionV2/MRushRotateAcc", 50);
    ZSS::ZParamManager::instance()->loadParam(MAX_RUSH_ROTATE_SPEED, "CGotoPositionV2/MRushRotateSpeed", 50);
    ZSS::ZParamManager::instance()->loadParam(MAX_RUSH_MIDROTATE_SPEED, "CGotoPositionV2/MRushMidRotateSpeed", 5);
    ZSS::ZParamManager::instance()->loadParam(DSS_AVOID,"CGotoPositionV2/DssAvoid",true);
    ZSS::ZParamManager::instance()->loadParam(SAO_ACTION,"Alert/SaoAction",0);
	_lastCycle = 0;
}

/// 输出流 ： 参数显示
void CGoImmortalRush::toStream(std::ostream& os) const
{
	os << "Going to " << task().player.pos << " angle:" << task().player.angle;
}

/// 规划入口
void CGoImmortalRush::plan(const CVisionModule* pVision)
{
	return;
}

/// 执行接口
CPlayerCommand* CGoImmortalRush::execute(const CVisionModule* pVision)
{
	if (pVision->Cycle() - _lastCycle > Param::Vision::FRAME_RATE * 0.1) {
        startedFlag[task().executor] = 0;
        rushFlag[task().executor] = 0;
        arrivedFlag[task().executor] = 0;
	}

	const int vecNumber = task().executor;
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	CGeoPoint target = task().player.pos;							// 目标的位置
    double dist = (target - self.Pos()).mod();
    const int playerFlag = task().player.flag;
    const double targetDir = task().player.angle;
    const CVector targetVel = task().player.vel;
    const int goalieNum = PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie());
    bool isGoalie = (vecNumber == goalieNum);

    if (isnan(target.x()) || isnan(target.y())) {
		target = self.Pos();
        cout << "Immortal Rush Target Pos is NaN, vecNumber is : " << vecNumber << endl;
	}

    double thisPenaltyAvoidDist = penaltyAvoidDist;
    if ((playerFlag & PlayerStatus::FREE_KICK) == 1) {
        thisPenaltyAvoidDist *= 4;
    }

    if (!(playerFlag & PlayerStatus::OUR_BALL_PLACEMENT)) target = Utils::MakeInField(target, -thisPenaltyAvoidDist);

    bool isMeInOurPenaltyArea = Utils::InOurPenaltyArea(self.Pos(), thisPenaltyAvoidDist);
    bool isTargetInOurPenaltyArea = Utils::InOurPenaltyArea(target, thisPenaltyAvoidDist);
    if ( !(playerFlag & PlayerStatus::OUR_BALL_PLACEMENT) && !isGoalie ) {	// 非自动放球状态下，非门将队员在禁区里面 : 离开禁区
        if (isMeInOurPenaltyArea == true) {//我在禁区
//            LeavePenaltyArea(pVision, self.Pos(), target);
            LeavePenaltyArea(pVision, vecNumber);
            target = reTarget();
        }
        else if (isTargetInOurPenaltyArea == true) {//目标在禁区
                double extra_out_dist = thisPenaltyAvoidDist;
                while (extra_out_dist < 200) {
                    target = Utils::MakeOutOfOurPenaltyArea(target, extra_out_dist);
                    bool checkOk = true;

                for (int teammate = 1; teammate <= Param::Field::MAX_PLAYER; ++teammate) {
                    if (teammate != vecNumber) {
                        if (pVision->OurPlayer(teammate).Pos().dist(target) < thisPenaltyAvoidDist * 4) {
                            checkOk = false;
                            break;
                        }
                    }
                }
                    if (checkOk == true)
                        break;
                    extra_out_dist += 2 * thisPenaltyAvoidDist;
                }
        }
    }
        // 所有车都不能进对方禁区
    bool isMeInTheirPenaltyArea = Utils::InTheirPenaltyArea(self.Pos(), thisPenaltyAvoidDist);
    bool isTargetInTheirPenaltyArea = Utils::InTheirPenaltyArea(target, thisPenaltyAvoidDist);
    if (!(playerFlag & PlayerStatus::OUR_BALL_PLACEMENT)){      //非放球状态下
        if (isMeInTheirPenaltyArea == true) {
//            LeaveTheirPenaltyArea(pVision, self.Pos(), target);
            LeaveTheirPenaltyArea(pVision, vecNumber);
            target = reTarget();
        }
        else if (isTargetInTheirPenaltyArea == true) {
            double extraOutDist = thisPenaltyAvoidDist;
            while (extraOutDist < 200) {
                target = Utils::MakeOutOfTheirPenaltyArea(target, extraOutDist);
                bool checkOk = true;
                for (int teammate = 1; teammate <= Param::Field::MAX_PLAYER; ++teammate) {
                    if (teammate != vecNumber) {
                        if (pVision->OurPlayer(teammate).Pos().dist(target) < thisPenaltyAvoidDist * 4) {
                            checkOk = false;
                            break;
                        }
                    }
                }
                if (checkOk == true)
                    break;
                extraOutDist += thisPenaltyAvoidDist * 2;
            }
        }
    }

    _target = target;

	// 记录当前的规划执行目标点
    GDebugEngine::Instance()->gui_debug_x(target, COLOR_CYAN);
    GDebugEngine::Instance()->gui_debug_line(self.Pos(), target, COLOR_CYAN);

	CCommandFactory* pCmdFactory = CmdFactory::Instance();					// 指向CommandFactoryV2的指针
    _capability = setCapability(pVision);
    unsigned char set_power = DribbleStatus::Instance()->getDribbleCommand(vecNumber);
	CVector nextVel;
	double nextRotVel;
	double nextAngle;

    calcZeroRush(pVision, nextVel, nextRotVel, nextAngle);

    int priority = 1;

    double usedtime = expectedCMPathTime(self, _target, _capability.maxAccel, _capability.maxSpeed, 1.5);

    double trajTime = ZSkillUtils::instance()->getImmortalRushTime(pVision, task().executor, task().player.pos, task().player.angle);
    static int cnt;
    static double lastTime = trajTime;
//    cout << cnt++ << " " << lastTime - trajTime << " " << trajTime << " " << self.Vel() << " " << self.Pos() << endl;
    lastTime = trajTime;
    if (DSS_AVOID && ((playerFlag & PlayerStatus::ALLOW_DSS))) {
        CVector tempVel = DynamicSafetySearch::Instance()->SafetySearch(vecNumber, nextVel, pVision, priority, _target, task().player.flag, usedtime, _capability.maxAccel);
        nextVel = tempVel;
    }

    double alpha = 1.0;
    if (dist <= DIST_REACH_CRITICAL) {
        alpha *= sqrt(dist / DIST_REACH_CRITICAL);
    }
    CVector localVel = (nextVel*alpha).rotate(-self.Dir());

	_lastCycle = pVision->Cycle();
    return pCmdFactory->newCommand(CPlayerSpeedV2(vecNumber, localVel.x(), localVel.y(), nextRotVel, set_power, 1));
}

void CGoImmortalRush::calcZeroRush(const CVisionModule *pVision, CVector &nextVel, double &nextRotVel, double &nextAngle) {
    const PlayerVisionT& self = pVision->OurPlayer(task().executor);
    if (!startedFlag[task().executor] && !rushFlag[task().executor]  && (self.Pos() - _target).mod() > 20) {
        if (abs(Utils::Normalize((_target - self.Pos()).dir() + Param::Math::PI) - self.Dir()) < 0.8) startedFlag[task().executor] = 1;
        arrivedFlag[task().executor] = 0;
        if (verbose) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-580, 430), "START", COLOR_PURPLE);
        getStartRotate(pVision, nextVel, nextRotVel, nextAngle);
    } else if ((!arrivedFlag[task().executor] && (_target - self.Pos()).mod() > 15)){
        if (verbose) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-580, 430), "RUSH", COLOR_PURPLE);
        rushFlag[task().executor] = 1;
        getMiddleRush(pVision, nextVel, nextRotVel, nextAngle);
    } else { // arrived
        if (verbose) GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-580, 430), "ARRIVED", COLOR_PURPLE);
        rushFlag[task().executor] = 0;
        startedFlag[task().executor] = 0;
        arrivedFlag[task().executor] = 1;
        getArrivedRotate(pVision, nextVel, nextRotVel, nextAngle);
    }
}

void CGoImmortalRush::calcNoneZeroRush(const CVisionModule *pVision, CVector &nextVel, double &nextRotVel, double &nextAngle) {}

void CGoImmortalRush::getStartRotate(const CVisionModule *pVision, CVector &nextVel, double &nextRotVel, double &nextAngle) {
    const PlayerVisionT& self = pVision->OurPlayer(task().executor);
    double targetDir = (self.Pos() - _target).dir();
    nextAngle = Utils::Normalize(targetDir - self.Dir());
    PlayerPoseT final;
    final.SetPos(self.Pos());
    final.SetDir(targetDir);
    PlayerPoseT nextStep;
    goto_point_omni(self, final, _capability, 1.5, 1.5, nextStep, _capability.maxSpeed);
//    nextVel = nextStep.Vel();
    nextRotVel = nextStep.RotVel();
}

void CGoImmortalRush::getMiddleRush(const CVisionModule *pVision, CVector &nextVel, double &nextRotVel, double &nextAngle) {
    const PlayerVisionT& self = pVision->OurPlayer(task().executor);
    CGeoPoint target = task().player.pos;
//    cout << self.Vel().mod() << endl;
    double targetDir = (self.Pos() - _target).dir();//Utils::Normalize((_target - self.Pos()).dir() + Param::Math::PI);//(self.Pos() - target).dir();
    CVector targetVel = Utils::Polar2Vector(task().player.vel.mod(), (_target - self.Pos()).dir());
    PlayerPoseT final;
    final.SetPos(target);
    final.SetDir(targetDir);
    final.SetVel(targetVel);
    PlayerPoseT nextStep;
    _capability.maxAngularSpeed = MAX_RUSH_MIDROTATE_SPEED;
    goto_point_omni(self, final, _capability, 1.5, 1.5, nextStep, _capability.maxSpeed);
    nextVel = nextStep.Vel();
    nextRotVel = nextStep.RotVel();
//    nextVel = CVector(0, 0);
//    nextRotVel = 0;
//    cout << nextVel.mod() << endl;
}

void CGoImmortalRush::getArrivedRotate(const CVisionModule *pVision, CVector &nextVel, double &nextRotVel, double &nextAngle) {
    const PlayerVisionT& self = pVision->OurPlayer(task().executor);
    CGeoPoint target = task().player.pos;
    double targetDir = task().player.angle;
    nextAngle = Utils::Normalize(targetDir - self.Dir());
    PlayerPoseT final;
    final.SetPos(target);
    final.SetDir(targetDir);
    PlayerPoseT nextStep;
    goto_point_omni(self, final, _capability, 1.5, 1.5, nextStep, _capability.maxSpeed);
    nextVel = nextStep.Vel();
    nextRotVel = nextStep.RotVel();
}

double calcImmortalTime(const CVisionModule *pVision, const int robotNum, const CGeoPoint targetPos, const double targetDir, const int mode) {
    PlayerVisionT self = pVision->OurPlayer(robotNum);
    double trajTime = 0.0;
    PlayerPoseT rushStart;
    rushStart.SetPos(self.Pos());
    rushStart.SetDir((self.Pos() - targetPos).dir());
    PlayerPoseT arriveStart;
    arriveStart.SetPos(targetPos);
    arriveStart.SetDir((self.Pos() - targetPos).dir());
    if (mode == 1) {
        trajTime = predictedTime1d(self.Dir(), self.RotVel(), rushStart.Dir(), MAX_RUSH_ROTATE_ACC, MAX_RUSH_ROTATE_SPEED, 1.5)
                + predictedTime2d(self, targetPos, MAX_RUSH_TRANSLATION_ACC, MAX_RUSH_TRANSLATION_SPEED, 1.5)
                + predictedTime1d(arriveStart.Dir(), 0, targetDir, MAX_RUSH_ROTATE_ACC, MAX_RUSH_ROTATE_SPEED, 1.5);
    }
    else if (mode == 2) {
        trajTime = predictedTime2d(self, targetPos, MAX_RUSH_TRANSLATION_ACC, MAX_RUSH_TRANSLATION_SPEED, 1.5)
                + predictedTime1d(arriveStart.Dir(), 0, targetDir, MAX_RUSH_ROTATE_ACC, MAX_RUSH_ROTATE_SPEED, 1.5);
    }
    else {
        trajTime = predictedTime1d(self.Dir(), self.RotVel(), targetDir, MAX_RUSH_ROTATE_ACC, MAX_RUSH_ROTATE_SPEED, 1.5);
    }
    return trajTime;
//    return predictedTime2d(self, targetPos, MAX_RUSH_TRANSLATION_ACC, MAX_RUSH_TRANSLATION_SPEED, 1.5);
}

bool CGoImmortalRush::canGoto(const CVisionModule* pVision, const int player, const CGeoPoint& target)
{
	if (target.x() < -Param::Field::PITCH_LENGTH / 2 || target.x() > Param::Field::PITCH_LENGTH / 2) {
		return false;
	}
	bool _canGo = true;
	_canGo = Utils::canGo(pVision, player, target, 0, 0);
	if (_canGo) {
		_target = target;
		return true;
	}
	return false;
}

PlayerCapabilityT CGoImmortalRush::setCapability(const CVisionModule* pVision) {
    int playerFlag = task().player.flag;
	PlayerCapabilityT capability;

    // Traslation 确定平动运动参数
    capability.maxSpeed = MAX_RUSH_TRANSLATION_SPEED;
    capability.maxAccel = MAX_RUSH_TRANSLATION_ACC;
    capability.maxDec = MAX_RUSH_TRANSLATION_ACC;

	// Rotation	  确定转动运动参数
    capability.maxAngularSpeed = MAX_RUSH_ROTATE_SPEED;
    capability.maxAngularAccel = MAX_RUSH_ROTATE_ACC;
    capability.maxAngularDec = MAX_RUSH_ROTATE_ACC;

	if (WorldModel::Instance()->CurrentRefereeMsg() == "GameStop") {
		const MobileVisionT ball = pVision->Ball();
		if (ball.Pos().x() < -240 && abs(ball.Pos().y()) > 150) {
			capability.maxSpeed = 100;
		}
		else {
			capability.maxSpeed = 150;
		}
	}

    if (playerFlag & PlayerStatus::SLOWLY) {
        capability.maxSpeed = 140;
        capability.maxAccel *= SlowFactor;
        capability.maxDec *= SlowFactor;
        capability.maxAngularSpeed *= SlowFactor;
        capability.maxAngularAccel *= SlowFactor;
        capability.maxAngularDec *= SlowFactor;
    }
	return capability;
}

//void CGoImmortalRush::LeavePenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target)
//{
//    double dis_buff = 15;
//    CGeoPoint left_top(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + dis_buff, -Param::Field::PENALTY_AREA_WIDTH/2 - dis_buff);
//    CGeoPoint right_top(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + dis_buff, Param::Field::PENALTY_AREA_WIDTH / 2 + dis_buff);
//    double top_dis = -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH - myPos.x();//到上边距离
//    double left_dis = myPos.y() + Param::Field::PENALTY_AREA_WIDTH / 2;//到左边距离
//    double right_dis = Param::Field::PENALTY_AREA_WIDTH / 2 - myPos.y();//到右边距离
//    if (Utils::InOurPenaltyArea(target, Param::Vehicle::V2::PLAYER_SIZE)) {//目标点还在禁区内
//        if (target.y() > 0) _target = right_top;
//        else _target = left_top;
//        return;
//    }
//    if (target.x() > -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH) {//1.目标点在上方
//        if (top_dis <= left_dis && top_dis <= right_dis) //1.1距离上边近
//            _target = target;
//        else if (left_dis <= right_dis)//1.2距离左边近
//            _target = left_top;
//        else //1.3距离右边近
//            _target = right_top;
//    }
//    else if (target.y() > 0) {//2.目标点在右侧
//        if (top_dis <= left_dis && top_dis <= right_dis) //2.1距离上边近
//            _target = right_top;
//        else if (left_dis <= right_dis)//2.2距离左边近
//            _target = left_top;
//        else //2.3距离右边近
//            _target = target;
//    }
//    else {//3.目标点在左侧
//        if (top_dis <= left_dis && top_dis <= right_dis) //3.1距离上边近
//            _target = left_top;
//        else if (left_dis <= right_dis)//3.2距离左边近
//            _target = target;
//        else //3.3距离右边近
//            _target = right_top;
//    }
//}

//void CGoImmortalRush::LeaveTheirPenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target)
//{
//    double dis_buff = 30;
//    CGeoPoint left_bottom(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - dis_buff, -Param::Field::PENALTY_AREA_WIDTH / 2 - dis_buff);
//    CGeoPoint right_bottom(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - dis_buff, Param::Field::PENALTY_AREA_WIDTH / 2 + dis_buff);
//    double bottom_dis = myPos.x()-(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH);//到下边距离
//    double left_dis = myPos.y() + Param::Field::PENALTY_AREA_WIDTH / 2;//到左边距离
//    double right_dis = Param::Field::PENALTY_AREA_WIDTH / 2 - myPos.y();//到右边距离
//    if (Utils::InTheirPenaltyArea(target, Param::Vehicle::V2::PLAYER_SIZE)) {//目标点还在禁区内
//        if (target.y() > 0) _target = right_bottom;
//        else _target = left_bottom;
//        return;
//    }
//    if (target.x() < Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH) {//1.目标点在下方
//        if (bottom_dis <= left_dis && bottom_dis <= right_dis) //1.1距离下边近
//            _target = target;
//        else if (left_dis <= right_dis)//1.2距离左边近
//            _target = left_bottom;
//        else //1.3距离右边近
//            _target = right_bottom;
//    }
//    else if (target.y() > 0) {//2.目标点在右侧
//        if (bottom_dis <= left_dis && bottom_dis <= right_dis) //2.1距离下边近
//            _target = right_bottom;
//        else if (left_dis <= right_dis)//2.2距离左边近
//            _target = left_bottom;
//        else //2.3距离右边近
//            _target = target;
//    }
//    else {//3.目标点在左侧
//        if (bottom_dis <= left_dis && bottom_dis <= right_dis) //3.1距离下边近
//            _target = left_bottom;
//        else if (left_dis <= right_dis)//3.2距离左边近
//            _target = target;
//        else //3.3距离右边近
//            _target = right_bottom;
//    }
//}

void CGoImmortalRush::LeavePenaltyArea(const CVisionModule* pVision, const int player)
{
    const CGeoPoint& vecPos = pVision->OurPlayer(player).Pos();
    const double keepDistance = Param::Field::MAX_PLAYER_SIZE + 10;
    if( Utils::InOurPenaltyArea(vecPos, Param::Field::MAX_PLAYER_SIZE) ){
        // 在我方禁区里面,在禁区线上找一些点，找距离最近的挡不住的路线
        const CGeoPoint ourGoal(-Param::Field::PITCH_LENGTH/2, 0);
        const CVector goal2player(vecPos - ourGoal);
        const double goal2playerDir = goal2player.dir();
        CGeoPoint leaveTarget;
        if( Param::Rule::Version == 2003 ){
            leaveTarget = ourGoal +  CVector(Param::Field::PITCH_MARGIN + Param::Field::PENALTY_AREA_DEPTH + keepDistance, vecPos.y());
        }else if (Param::Rule::Version == 2004){
            leaveTarget = ourGoal + Utils::Polar2Vector(Param::Field::PENALTY_AREA_WIDTH/2 + keepDistance, goal2playerDir);
        }else if (Param::Rule::Version == 2008 || Param::Rule::Version == 2019){
            leaveTarget = Utils::GetOutSidePenaltyPos(goal2playerDir,keepDistance,ourGoal);
        }
        if( canGoto(pVision, player,leaveTarget) ){
            return;
        }
        const double angleStep = Param::Math::PI/12 * Utils::Sign(vecPos.y());
        const double distStep = 15 * Utils::Sign(vecPos.y());
        for( int i=1; i<3; ++i ){
            if( Param::Rule::Version == 2003 ){
                leaveTarget = ourGoal + CVector(Param::Field::PITCH_MARGIN + Param::Field::PENALTY_AREA_DEPTH + keepDistance, vecPos.y() + i * distStep);
            }else if(Param::Rule::Version == 2004){
                leaveTarget = ourGoal + Utils::Polar2Vector(Param::Field::PENALTY_AREA_WIDTH/2 + keepDistance, goal2playerDir + i * angleStep);
            }else if (Param::Rule::Version == 2008 || Param::Rule::Version == 2019){
                leaveTarget = Utils::GetOutSidePenaltyPos(goal2playerDir + i * angleStep,keepDistance,ourGoal);
            }
            if( canGoto(pVision, player, leaveTarget) ){
                return;
            }

            if( Param::Rule::Version == 2003 ){
                leaveTarget = ourGoal + CVector(Param::Field::PITCH_MARGIN + Param::Field::PENALTY_AREA_DEPTH + keepDistance, vecPos.y() - i * distStep);
            }else if(Param::Rule::Version == 2004){
                leaveTarget = ourGoal + Utils::Polar2Vector(Param::Field::PENALTY_AREA_WIDTH/2 + keepDistance, goal2playerDir - i * angleStep);
            }else if (Param::Rule::Version == 2008 || Param::Rule::Version == 2019){
                leaveTarget = Utils::GetOutSidePenaltyPos(goal2playerDir - i * angleStep,keepDistance,ourGoal);
            }
            if( canGoto(pVision, player, leaveTarget) ){
                return;
            }
        }
        if( Param::Rule::Version == 2003 ){
            leaveTarget = ourGoal + CVector(Param::Field::PITCH_MARGIN + Param::Field::PENALTY_AREA_DEPTH + keepDistance, vecPos.y());
        }else if(Param::Rule::Version == 2004){
            _target = ourGoal + Utils::Polar2Vector(Param::Field::PENALTY_AREA_WIDTH/2 + keepDistance, goal2playerDir); // 只能向前冲
        }else if(Param::Rule::Version == 2008 || Param::Rule::Version == 2019){
            _target = Utils::GetOutSidePenaltyPos(goal2playerDir,keepDistance,ourGoal);
        }
    }else{
        _target = vecPos; // 不动
    }
}


void CGoImmortalRush::LeaveTheirPenaltyArea(const CVisionModule* pVision,
                                            const int player) {
    const CGeoPoint& vecPos = pVision->OurPlayer(player).Pos();
    // 在对方禁区里面,在禁区线上找一些点，找距离最近的挡不住的路线
    CGeoPoint theirGoal(Param::Field::PITCH_LENGTH/2, 0);
    CVector goal2player(vecPos - theirGoal);
    double goal2playerDir = goal2player.dir();
    double angleStep = Param::Math::PI / 12 * Utils::Sign(vecPos.y());
//	double distStep = 15 * Utils::Sign(vecPos.y());
    double keepDistance = Param::Field::MAX_PLAYER_SIZE*1.5;

    for (int i = 0;  i < 3; ++i) {
        CGeoPoint leaveTarget =
                Utils::GetOutTheirSidePenaltyPos(goal2playerDir + i*angleStep,
                                                 keepDistance, theirGoal);
        if (Utils::canGo(pVision, player, leaveTarget, 0, 0) == true
                && leaveTarget.x() > -Param::Field::PITCH_LENGTH/2
                && leaveTarget.x() < Param::Field::PITCH_LENGTH/2) {
            _target = leaveTarget;
            return;
        }
        leaveTarget =
                Utils::GetOutTheirSidePenaltyPos(goal2playerDir - i*angleStep,
                                                 keepDistance,
                                                 theirGoal);
        if (Utils::canGo(pVision, player, leaveTarget, 0, 0) == true
                && leaveTarget.x() > -Param::Field::PITCH_LENGTH/2
                && leaveTarget.x() < Param::Field::PITCH_LENGTH/2) {
            _target = leaveTarget;
            return;
        }
    }
    _target = Utils::GetOutTheirSidePenaltyPos(goal2playerDir, keepDistance, theirGoal);
}
