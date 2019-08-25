#include "GotoPosition.h"
#include <utils.h>
#include "skill/Factory.h"
#include <CommandFactory.h>
#include <VisionModule.h>
#include <RobotCapability.h>
#include <sstream>
#include <TaskMediator.h>
#include <ControlModel.h>
#include <robot_power.h>
#include <DribbleStatus.h>
#include "PlayInterface.h"
#include <GDebugEngine.h>
//#include <LeavePenaltyArea.h>
#include "DynamicsSafetySearch.h"
#include "CMmotion.h"
#include <fstream>
#include "parammanager.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace{
	/// 调试开关
	bool DRAW_TARGET = false;
	bool DSS_AVOID = true;

	/// 用于解决到点晃动的问题
	const double DIST_REACH_CRITICAL = 2;	// [unit : cm]
	const double SlowFactor = 0.5;
	const double FastFactor = 1.2;

	/// 底层运动控制参数 ： 默认增大平动的控制性能
	double MAX_TRANSLATION_SPEED = 400;		// [unit : cm/s]
	double MAX_TRANSLATION_ACC = 600;		// [unit : cm/s2]
	double MAX_ROTATION_SPEED = 5;			// [unit : rad/s]
	double MAX_ROTATION_ACC = 15;			// [unit : rad/s2]
	double TRANSLATION_ACC_LIMIT = 1000;
	double MAX_TRANSLATION_DEC = 650;
    double SPEED_TRANS_THREASHOLD = 100;

	/// 守门员专用
	double MAX_TRANSLATION_SPEED_GOALIE;
	double MAX_TRANSLATION_ACC_GOALIE;
	double MAX_TRANSLATION_DEC_GOALIE;

	/// 后卫专用
	double MAX_TRANSLATION_SPEED_BACK;
	double MAX_TRANSLATION_ACC_BACK;
	double MAX_TRANSLATION_DEC_BACK;

	/// 底层控制方法参数
	int TRAJECTORY_METHORD = 1;				// 默认使用 CMU 的轨迹控制
	int TASK_TARGET_COLOR = COLOR_CYAN;
    ofstream carVisionVel("C://Users//gayty//Desktop//Sydney//Sydney//carVisionVel.txt");
	int SAO_ACTION;

    double Y_COMPENSATE_K;
    double Y_COMPENSATE_B;
    const double penaltyAvoidDist = Param::Vehicle::V2::PLAYER_SIZE;
}
using namespace Param::Vehicle::V2;

/// 构造函数 ： 参数初始化
CGotoPositionV2::CGotoPositionV2()
{
    ZSS::ZParamManager::instance()->loadParam(SPEED_TRANS_THREASHOLD,"CGotoPositionV2/speed_trans_threashold",100);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_SPEED,"CGotoPositionV2/MNormalSpeed",300);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_ACC,"CGotoPositionV2/MNormalAcc",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_DEC,"CGotoPositionV2/MNormalDec",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_SPEED_BACK,"CGotoPositionV2/MBackSpeed",300);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_ACC_BACK,"CGotoPositionV2/MBackAcc",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_DEC_BACK,"CGotoPositionV2/MBackDec",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_SPEED_GOALIE,"CGotoPositionV2/MGoalieSpeed",300);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_ACC_GOALIE,"CGotoPositionV2/MGoalieAcc",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_TRANSLATION_DEC_GOALIE,"CGotoPositionV2/MGoalieDec",450);
    ZSS::ZParamManager::instance()->loadParam(MAX_ROTATION_SPEED,"CGotoPositionV2/RotationSpeed",15);
    ZSS::ZParamManager::instance()->loadParam(MAX_ROTATION_ACC,"CGotoPositionV2/RotationAcc",15);
    ZSS::ZParamManager::instance()->loadParam(DRAW_TARGET,"Debug/TargetPos",false);
    ZSS::ZParamManager::instance()->loadParam(DSS_AVOID,"CGotoPositionV2/DssAvoid",true);
    ZSS::ZParamManager::instance()->loadParam(TRANSLATION_ACC_LIMIT,"CGotoPositionV2/AccLimit",1400);
    ZSS::ZParamManager::instance()->loadParam(TRAJECTORY_METHORD,"CGotoPositionV2/TrajectoryMethod",1);
    ZSS::ZParamManager::instance()->loadParam(SAO_ACTION,"Alert/SaoAction",0);
    ZSS::ZParamManager::instance()->loadParam(Y_COMPENSATE_K,"CGotoPositionV2/YCompensateK",0.0035);
    ZSS::ZParamManager::instance()->loadParam(Y_COMPENSATE_B,"CGotoPositionV2/YCompensateB",-0.1042);

	//if (SAO_ACTION == 2) {
	//	MAX_TRANSLATION_SPEED *= 1.5;
	//	MAX_TRANSLATION_ACC *= 1.5;
	//	MAX_TRANSLATION_DEC *= 1.5;
	//	MAX_TRANSLATION_SPEED_GOALIE *= 1.5;
	//	MAX_TRANSLATION_ACC_GOALIE *= 1.5;
	//	MAX_TRANSLATION_DEC_GOALIE *= 1.5;
	//	MAX_TRANSLATION_SPEED_BACK *= 1.5;
	//	MAX_TRANSLATION_ACC_BACK *= 1.5;
	//	MAX_TRANSLATION_DEC_BACK *= 1.5;
	//}
}

/// 输出流 ： 参数显示
void CGotoPositionV2::toStream(std::ostream& os) const
{
	os << "Going to " << task().player.pos<<" angle:"<<task().player.angle;
}

/// 规划入口
void CGotoPositionV2::plan(const CVisionModule* pVision)
{
	return ;
}

/// 执行接口
CPlayerCommand* CGotoPositionV2::execute(const CVisionModule* pVision)
{
	/************************************************************************/
	/* 任务参数解析                                                         */
	/************************************************************************/
	const int vecNumber = task().executor;
	const PlayerVisionT& self = pVision->OurPlayer(vecNumber);
	const CGeoPoint& vecPos = self.Pos();							// 小车的位置
//	const double vecDir = self.Dir();								// 小车的身体角度
	CGeoPoint target = task().player.pos;							// 目标的位置
	const int goalieNum = PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie());
	const bool isGoalie = (vecNumber == goalieNum);
	const int playerFlag = task().player.flag;
	/*cout<<"goalie= "<<goalieNum<<endl;*/
	//cout << self.RotVel() <<" "<< task().player.rotvel << endl;
	/************************************************************************/
	/* 修正非法目标点输入                                                   */
	/************************************************************************/
    if (isnan(target.x()) || isnan(target.y())) {
		target = self.Pos();
		cout << "Target Pos is NaN, vecNumber is : " << vecNumber << endl;
	}

    double thisPenaltyAvoidDist = penaltyAvoidDist;
    if ((playerFlag & PlayerStatus::FREE_KICK) == 1) {
        thisPenaltyAvoidDist *= 4;
    }

    if (!(playerFlag & PlayerStatus::OUR_BALL_PLACEMENT) && !isGoalie) target = Utils::MakeInField(target, -thisPenaltyAvoidDist);

	// 关于我方禁区的判断 : 除门将外其他球员都不能进入禁区
    bool isMeInOurPenaltyArea = Utils::InOurPenaltyArea(vecPos, thisPenaltyAvoidDist);
    bool isTargetInOurPenaltyArea = Utils::InOurPenaltyArea(target, thisPenaltyAvoidDist);
    if ( !(playerFlag & PlayerStatus::OUR_BALL_PLACEMENT) && !isGoalie ) {	// 非自动放球状态下，非门将队员在禁区里面 : 离开禁区
		if (isMeInOurPenaltyArea == true) {//我在禁区
            LeavePenaltyArea(pVision, vecPos, target);
//            LeavePenaltyArea(pVision, vecNumber);
			target = reTarget();

		}
        else if (isTargetInOurPenaltyArea == true) {//目标在禁区
                double extra_out_dist = thisPenaltyAvoidDist * 2;
                while (extra_out_dist < 200) {
                    //target = Utils::MakeOutOfOurPenaltyArea(task().player.pos, extra_out_dist);
                    //cout << "X:" << target.x() << "Y:" << target.y() << endl;
                    target = Utils::MakeOutOfOurPenaltyArea(target, extra_out_dist);
                    //cout << "X:" << target.x() << "Y:" << target.y()<<endl;
                    bool checkOk = true;
					
                    for (int teammate = 1; teammate <= Param::Field::MAX_PLAYER; ++teammate) {
                        if (teammate != vecNumber) {
                            if (pVision->OurPlayer(teammate).Pos().dist(target) < thisPenaltyAvoidDist * 8) {
                                checkOk = false;
                                break;
                            }
                        }
                    }
                    if (checkOk == true)
                        break;
                    extra_out_dist += 4 * thisPenaltyAvoidDist;
                }
        }
    }
		// 所有车都不能进对方禁区
    bool isMeInTheirPenaltyArea = Utils::InTheirPenaltyArea(vecPos, thisPenaltyAvoidDist);
    bool isTargetInTheirPenaltyArea = Utils::InTheirPenaltyArea(target, thisPenaltyAvoidDist);
		//bool isBallInTheirPenaltyArea = Utils::InTheirPenaltyArea(pVision->Ball().Pos(), Param::Vehicle::V2::PLAYER_SIZE);
    if (!(playerFlag & PlayerStatus::OUR_BALL_PLACEMENT)){      //非放球状态下
        if (isMeInTheirPenaltyArea == true) {
            //cout << "Me In Their Penalty Area " << endl;
            LeaveTheirPenaltyArea(pVision, vecPos, target);
//            LeaveTheirPenaltyArea(pVision, vecNumber);
			target = reTarget();
		}
		//modified by Wang in 2018/4/3
        else if (isTargetInTheirPenaltyArea == true) {
            //else if (isBallInTheirPenaltyArea == true) {
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
            //target = Utils::MakeOutOfTheirPenaltyArea(target, extraOutDist);
        }
		//else
		//	cout << "Nothing In Their Penalty Area " << endl;
    }
		// 记录当前的规划执行目标点
		GDebugEngine::Instance()->gui_debug_x(target, TASK_TARGET_COLOR);
		GDebugEngine::Instance()->gui_debug_line(self.Pos(), target, TASK_TARGET_COLOR);

//		const double targetDir = task().player.angle;
		const CVector player2target = target - vecPos;
		const double dist = player2target.mod();
//		const double angleDiff = Utils::Normalize(targetDir - vecDir);
//		const double absAngleDiff = std::abs(angleDiff);
//		const double vecSpeed = self.Vel().mod();
		//const int playerFlag = task().player.flag;
		const bool dribble = playerFlag & PlayerStatus::DRIBBLING;
		unsigned char dribblePower = 0;
//		double moveDiff = Utils::Normalize(player2target.dir() - self.Dir());
		//cout << "max_acceleration : " <<  task().player.max_acceleration << endl;

		/************************************************************************/
		/* 确定运动性能参数 确定只使用OmniAuto配置标签中的参数                       */
		/************************************************************************/
		/// 判断怎么走
		CCommandFactory* pCmdFactory = CmdFactory::Instance();					// 指向CommandFactoryV2的指针
		/// 运动性能参数 ： 没太大意义，一般以xml中的设置为准 cliffyin ： TODO 各向异性约束需要以后予以考虑
		PlayerCapabilityT capability;
//		const CRobotCapability* robotCap = RobotCapFactory::Instance()->getRobotCap(pVision->Side(), vecNumber);

		// Traslation 确定平动运动参数
		if (vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie())) {
			capability.maxSpeed = MAX_TRANSLATION_SPEED_GOALIE;
			capability.maxAccel = MAX_TRANSLATION_ACC_GOALIE;
			capability.maxDec = MAX_TRANSLATION_DEC_GOALIE;
		}
		else if (TaskMediator::Instance()->leftBack() != 0 && vecNumber == TaskMediator::Instance()->leftBack()
			|| TaskMediator::Instance()->rightBack() != 0 && vecNumber == TaskMediator::Instance()->rightBack()
			|| TaskMediator::Instance()->singleBack() != 0 && vecNumber == TaskMediator::Instance()->singleBack()
			|| TaskMediator::Instance()->sideBack() != 0 && vecNumber == TaskMediator::Instance()->sideBack()) {
			capability.maxSpeed = MAX_TRANSLATION_SPEED_BACK;
			capability.maxAccel = MAX_TRANSLATION_ACC_BACK;
			capability.maxDec = MAX_TRANSLATION_DEC_BACK;
		}
		else {
			capability.maxSpeed = MAX_TRANSLATION_SPEED;
			capability.maxAccel = MAX_TRANSLATION_ACC;
			capability.maxDec = MAX_TRANSLATION_DEC;
		}
		// Rotation	  确定转动运动参数
		capability.maxAngularSpeed = MAX_ROTATION_SPEED;
		capability.maxAngularAccel = MAX_ROTATION_ACC;
		capability.maxAngularDec = MAX_ROTATION_ACC;

		if (playerFlag & PlayerStatus::SLOWLY) {
            capability.maxSpeed = 140;
			capability.maxAccel *= SlowFactor;
			capability.maxDec *= SlowFactor;
			capability.maxAngularSpeed *= SlowFactor;
			capability.maxAngularAccel *= SlowFactor;
			capability.maxAngularDec *= SlowFactor;
		}
		if (playerFlag & PlayerStatus::QUICKLY
			|| vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie())) {
			capability.maxSpeed *= FastFactor;
			capability.maxAccel *= FastFactor;
			capability.maxDec *= FastFactor;
			capability.maxAngularSpeed *= FastFactor;
			capability.maxAngularAccel *= FastFactor;
			capability.maxAngularDec *= FastFactor;
		}

		if (playerFlag & PlayerStatus::QUICKLY
			|| vecNumber == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie())) {
		}

		//if (vision->OurPlayer(vecNumber).Vel().mod() > 100){
		//	capability.maxAccel = -1*vision->OurPlayer(vecNumber).Vel().mod()+750;
		//	if(vision->OurPlayer(vecNumber).Vel().mod() > 300){
		//		capability.maxAccel = 450;
		//		capability.maxDec = 450;
		//	}
		//}
		/*capability.maxAccel = 900;
		capability.maxDec = 300;*/

		if (task().player.max_acceleration > 1) { // 2014-03-26 修改, 因为double数不能进行相等判断
			capability.maxAccel = task().player.max_acceleration > TRANSLATION_ACC_LIMIT ? TRANSLATION_ACC_LIMIT : task().player.max_acceleration;
			capability.maxDec = capability.maxAccel;
		}
        /// added rotation acceleration limit by gjy 2018.6.9
        if (task().player.max_rot_acceleration > 1) {
            capability.maxAngularAccel = task().player.max_rot_acceleration;
            capability.maxAngularDec = task().player.max_rot_acceleration;
        }
        if (task().player.max_speed > 1) {
            capability.maxSpeed = task().player.max_speed;
        }
        if (task().player.max_rot_speed > 1) {
            capability.maxAngularSpeed = task().player.max_rot_speed;
        }
//		if (WorldModel::Instance()->CurrentRefereeMsg() == "GameStop") {
//			const MobileVisionT ball = pVision->Ball();
//			if (ball.Pos().x() < -240 && abs(ball.Pos().y()) > 150) {
//				capability.maxSpeed = 100;
//			}
//			else {
//				capability.maxSpeed = 150;
//			}
//		}

		/************************************************************************/
		/* 确定初末状态 结合 选取的控制方式生成运动指令                  */
		/************************************************************************/
		/// 设定目标状态
		PlayerPoseT final;
        final.SetPos(target);
		final.SetDir((playerFlag & (PlayerStatus::POS_ONLY | PlayerStatus::TURN_AROUND_FRONT)) ? self.Dir() : task().player.angle);
		final.SetVel(task().player.vel);
		final.SetRotVel(task().player.rotvel);
		/// 调用控制方法
		CControlModel control;
		float usedtime = target.dist(self.Pos()) / capability.maxSpeed / 1.414;	// 单位：秒
		/// 进行轨迹生成并记录理想执行时间
		if (playerFlag & PlayerStatus::DO_NOT_STOP) {											// 一般不会执行 ： cliffyin
			if (CMU_TRAJ == TRAJECTORY_METHORD) {		//CMU的运动控制方法，可以非零速度到点
				final.SetVel(Utils::Polar2Vector(1.0, player2target.dir())*self.Vel().mod());
                control.makeCmTrajectory(self, final, capability, SPEED_TRANS_THREASHOLD);
			}
			else {
				control.makeFastPath(self, final, capability);
				control.makeZeroFinalVelocityTheta(self, final, capability);
			}
		}
		else {																						// 真正执行部分 ： cliffyin
			int Current_Trajectory_Method = TRAJECTORY_METHORD;
			if (task().player.is_specify_ctrl_method) {// 指定的运动控制方式
				Current_Trajectory_Method = task().player.specified_ctrl_method;
			}
			switch (Current_Trajectory_Method) {
			case CMU_TRAJ:
                control.makeCmTrajectory(self, final, capability, SPEED_TRANS_THREASHOLD);					// CMU 非零速到点
				break;
			case ZERO_FINAL:
				control.makeZeroFinalVelocityPath(self, final, capability);			// Bangbang 零速到点
				break;
			case ZERO_TRAP:
				control.makeTrapezoidalVelocityPath(self, final, capability);			// ZJUNlict 零速到点 : 存在问题，先不用
				break;
			case NONE_TRAP:
				control.makeNoneTrapezoidalVelocityPath(self, final, capability);	// ZJUNlict 非零速到点
				break;
			default:
				control.makeZeroFinalVelocityPath(self, final, capability);			// Bangbang 零速到点
				break;
			}
		}

		const vector< vector<double> >& fullPath = control.getFullPath();
		const double time_factor = 1.5;
		if (!fullPath.empty()) {
			usedtime = fullPath.size() / Param::Vision::FRAME_RATE;
        } else {
            usedtime = expectedCMPathTime(self, final.Pos(), capability.maxAccel, capability.maxSpeed, time_factor);
        }

		bool fullPathSafe = true;
		const int fullPathCheckIndex = 0.5*Param::Vision::FRAME_RATE;
		if (fullPath.size() > 5) {	// 进行轨迹检查
			for (int i = 0; i < fullPath.size(); i++) {
				if (i >= fullPathCheckIndex) {
					break;
				}

				CGeoPoint realPoint = CGeoPoint(fullPath[i][1] + self.Pos().x(), fullPath[i][2] + self.Pos().y());
				GDebugEngine::Instance()->gui_debug_x(realPoint, COLOR_RED);
				if ((isGoalie == false && Utils::InOurPenaltyArea(realPoint, 0))
					|| Utils::InTheirPenaltyArea(realPoint, 0)) {
					fullPathSafe = false;
					cout << vecNumber << " : unsafe^^^^^^^^^^^^^^^^^^^^^^^" << endl;
					break;
				}
			}
		}


		/************************************************************************/
		/* 调用动态避障模块（DSS），对轨迹生成模块运动指令进行避碰检查	*/
		/************************************************************************/
		// 获取轨迹生成模块在全局坐标系中的速度指令
		CVector globalVel = control.getNextStep().Vel();
		//deleted by Wang in 2018/3/22
		/*
		if (fullPathSafe == false) {	// 检查结果：非门将球员会进入禁区，停车
			if (isMeInOurPenaltyArea == false) {
				//deleted by Wang in 2018/3/22
				globalVel = CVector(0.0, 0.0);
			//	control.makeCmTrajectory(self,final,capability);
				cout << vecNumber << " : make zero^^^^^^^^^^^^^^^^^^^^^^^" << endl;
			}
		}
		*/
		//CUsecTimer t1;
		//t1.start();
		int priority = 0;
        if (DSS_AVOID && (playerFlag & PlayerStatus::ALLOW_DSS)) {
            //cout << "DSS" << endl;
            CVector tempVel = DynamicSafetySearch::Instance()->SafetySearch(vecNumber, globalVel, pVision, priority, target, task().player.flag, usedtime, task().player.max_acceleration);
            if (WorldModel::Instance()->CurrentRefereeMsg() == "GameStop" && tempVel.mod() > 150) { // 不加这个在stop的时候车可能会冲出去
                //cout << tempVel.mod() << endl;
            }
            else {
                globalVel = tempVel;
            }
        }
		//t1.stop();
		//cout << t1.time() << endl;

		/************************************************************************/
		/* 处理最后的指令                                                       */
		/************************************************************************/
		// 靠近系数调整，用于解决到点晃动的问题 [7/2/2011 cliffyin]
		double alpha = 1.0;
		if (dist <= DIST_REACH_CRITICAL) {
			alpha *= sqrt(dist / DIST_REACH_CRITICAL);
		}


		// 坐标转换 : 全局转局部, 得到需要下发的小车坐标系速度 <vx,vy,w>
		//cout << "global:"<<globalVel.x()<<" "<<globalVel.y()<< endl;
        CVector localVel = (globalVel*alpha).rotate(-self.Dir());		// 车自己坐标系里面的速度
        double rotVel = control.getNextStep().RotVel();				// 旋转速度
//        double robotXVel = localVel.x();
//        double robotYVel = localVel.y();
//        double RATIO = 0.4;
//        double compensateR = RATIO*(Y_COMPENSATE_K * robotYVel + Y_COMPENSATE_B);
//        cout << localVel << " " << compensateR << endl;
//        if (fabs(robotXVel) < fabs(robotYVel)) {
//            rotVel += compensateR;
//        }
//        else if (fabs(robotXVel/robotYVel) < 2) {
//            rotVel += compensateR * (2 - fabs(robotXVel / robotYVel));
//        }

		//if (vecNumber == 2) {
	//		cout << localVel.x() << " " << localVel.y() << endl;
	//		cout << rotVel << endl;
		//}
		/// add by cliffyin : angular control bug fix

//MARKFIX
        if ((fabs(Utils::Normalize(final.Dir() - self.Dir())) <= Param::Math::PI * 5 / 180)) {
            //用前者会小幅抖动，用后三句会很稳
            //CControlModel cmu_control;
            //cmu_control.makeCmTrajectory(self,final,capability);
            //rotVel = cmu_control.getNextStep().RotVel();
            rotVel /= 2;
        }

		// 控球
		unsigned char set_power = DribbleStatus::Instance()->getDribbleCommand(vecNumber);

		if (set_power > 0) {
			dribblePower = set_power;
		}
		else {
			dribblePower = DRIBBLE_DISABLED;
		}

		if (dribble) {
			dribblePower = DRIBBLE_NORAML;
		}

		static PlayerVisionT meLast = self;
        carVisionVel << (self.RawPos().x() - meLast.RawPos().x()) * Param::Vision::FRAME_RATE << " " << (self.RawPos().y() - meLast.RawPos().y()) * Param::Vision::FRAME_RATE << endl;
		meLast = self;

		/// 生成并返回控制指令
		return pCmdFactory->newCommand(CPlayerSpeedV2(vecNumber, localVel.x(), localVel.y(), rotVel, dribblePower));
	}

//modified by Wang in 2018/3/22
void CGotoPositionV2::LeavePenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target)
{
    double dis_buff = 50;
    CGeoPoint left_top(/*200*/-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + dis_buff, -Param::Field::PENALTY_AREA_WIDTH/2 - dis_buff);
    CGeoPoint right_top(/*200*/-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH + dis_buff, Param::Field::PENALTY_AREA_WIDTH / 2 + dis_buff);
    double top_dis = -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH - myPos.x();//到上边距离
    double left_dis = myPos.y() + Param::Field::PENALTY_AREA_WIDTH / 2;//到左边距离
    double right_dis = Param::Field::PENALTY_AREA_WIDTH / 2 - myPos.y();//到右边距离
    if (Utils::InOurPenaltyArea(target, Param::Vehicle::V2::PLAYER_SIZE)) {//目标点还在禁区内
        if (target.y() > 0) _target = right_top;
        else _target = left_top;
        return;
    }
    if (target.x() > -Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH) {//1.目标点在上方
        if (top_dis <= left_dis && top_dis <= right_dis) //1.1距离上边近
            _target = target;
        else if (left_dis <= right_dis)//1.2距离左边近
            _target = left_top;
        else //1.3距离右边近
            _target = right_top;
    }
    else if (target.y() > 0) {//2.目标点在右侧
        if (top_dis <= left_dis && top_dis <= right_dis) //2.1距离上边近
            _target = right_top;
        else if (left_dis <= right_dis)//2.2距离左边近
            _target = left_top;
        else //2.3距离右边近
            _target = target;
    }
    else {//3.目标点在左侧
        if (top_dis <= left_dis && top_dis <= right_dis) //3.1距离上边近
            _target = left_top;
        else if (left_dis <= right_dis)//3.2距离左边近
            _target = target;
        else //3.3距离右边近
            _target = right_top;
    }
}


void CGotoPositionV2::LeaveTheirPenaltyArea(const CVisionModule* pVision, CGeoPoint myPos, CGeoPoint target)
{
    double dis_buff = 50;
    CGeoPoint left_bottom(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - dis_buff, -Param::Field::PENALTY_AREA_WIDTH / 2 - dis_buff);
    CGeoPoint right_bottom(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - dis_buff, Param::Field::PENALTY_AREA_WIDTH / 2 + dis_buff);
    double bottom_dis = myPos.x()-(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH);//到下边距离
    double left_dis = myPos.y() + Param::Field::PENALTY_AREA_WIDTH / 2;//到左边距离
    double right_dis = Param::Field::PENALTY_AREA_WIDTH / 2 - myPos.y();//到右边距离
    if (Utils::InTheirPenaltyArea(target, Param::Vehicle::V2::PLAYER_SIZE)) {//目标点还在禁区内
        if (target.y() > 0) _target = right_bottom;
        else _target = left_bottom;
        return;
    }
    if (myPos.x() < Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH) {//1.目标点在下方
        if (bottom_dis <= left_dis && bottom_dis <= right_dis) //1.1距离下边近
            _target = target;
        else if (left_dis <= right_dis)//1.2距离左边近
            _target = left_bottom;
        else //1.3距离右边近
            _target = right_bottom;
    }
    else if (myPos.y() > 0) {//2.目标点在右侧
        if (bottom_dis <= left_dis && bottom_dis <= right_dis) //2.1距离下边近
            _target = right_bottom;
        else if (left_dis <= right_dis)//2.2距离左边近
            _target = left_bottom;
        else //2.3距离右边近
            _target = target;
    }
    else {//3.目标点在左侧
        if (bottom_dis <= left_dis && bottom_dis <= right_dis) //3.1距离下边近
            _target = left_bottom;
        else if (left_dis <= right_dis)//3.2距离左边近
            _target = target;
        else //3.3距离右边近
            _target = right_bottom;
    }
}

bool CGotoPositionV2::canGoto(const CVisionModule* pVision, const int player, const CGeoPoint& target)
{
	if( target.x() < -Param::Field::PITCH_LENGTH/2 || target.x() > Param::Field::PITCH_LENGTH/2 || target.y() < -Param::Field::PITCH_WIDTH / 2 || target.y() > Param::Field::PITCH_WIDTH / 2){
		return false;
	}
	bool _canGo = true;
	_canGo = Utils::canGo(pVision, player, target, 0, 0);
	if( _canGo ){
		_target = target;
		return true;
	}
	return false;
}
