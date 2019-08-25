#include "RRTPathPlanner.h"
#include <cmu/obstacle.h>
#include <cmu/path_planner.h>
#include <cmu/constants.h>
#include <param.h>
#include <utils.h>
#include <GDebugEngine.h>
#include "cmu/vector.h"
#include <math.h>
#include "PlayInterface.h"
#include <TaskMediator.h>

namespace{
	const double TEAMMATE_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 4.0f; // 2014/03/13 修改，为了减少stop的时候卡住的概率 yys
    const double OPP_AVOID_DIST = Param::Vehicle::V2::PLAYER_SIZE + 5.5f;
	const double BALL_AVOID_DIST = Param::Field::BALL_SIZE + 5.0f;
	//const double VELMIN = 1.0f; //最小速度
	path_planner pathPlanner[Param::Field::MAX_PLAYER * 2];  //ERRT算法实例
}

CRRTPathPlanner::CRRTPathPlanner(const CVisionModule* pVision, const TaskT& task, const double avoidLength) {
	int player = task.executor;
	CGeoPoint target = task.player.pos; // 全局目标跑位点
	int flags = task.player.flag;
	int shootCar = task.ball.Sender; // 出球者号码

	obstacles obs(avoidLength);  // 障碍物
	vector2f playerPos(pVision->OurPlayer(player).X(), pVision->OurPlayer(player).Y());
	vector2f playerVel(pVision->OurPlayer(player).VelX(), pVision->OurPlayer(player).VelY());


    if (flags & PlayerStatus::FREE_KICK) {
        obs.add_rectangle(vector2f(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH/2 - OPP_AVOID_DIST * 3),
                          vector2f(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH - OPP_AVOID_DIST * 3, Param::Field::PENALTY_AREA_WIDTH / 2 + OPP_AVOID_DIST * 3), 1);
    }
    else {
        obs.add_rectangle(vector2f(Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH/2),
                          vector2f(Param::Field::PITCH_LENGTH / 2 - Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2), 1);
    }

	// 如果是躲避射门
	if (flags & PlayerStatus::AVOID_SHOOTLINE) {
		const PlayerVisionT& shooter = pVision->OurPlayer(shootCar);
		// 球门中心
		obs.add_long_circle(vector2f(shooter.Pos().x(), shooter.Pos().y()), vector2f(Param::Field::PITCH_LENGTH/2, 0.0f), vector2f(0.0f, 0.0f), 3.0f, 1);
		// 球门左门柱
		obs.add_long_circle(vector2f(shooter.Pos().x(), shooter.Pos().y()), vector2f(Param::Field::PITCH_LENGTH/2, Param::Field::GOAL_WIDTH/2.0), vector2f(0.0f, 0.0f), 3.0f, 1);
		// 球门右门柱
		obs.add_long_circle(vector2f(shooter.Pos().x(), shooter.Pos().y()), vector2f(Param::Field::PITCH_LENGTH/2, -Param::Field::GOAL_WIDTH/2.0), vector2f(0.0f, 0.0f), 3.0f, 1);
	}

	// set up teammates as obstacles
    if (!(flags & PlayerStatus::NOT_AVOID_OUR_VEHICLE)) {
        for(int i = 1; i <= Param::Field::MAX_PLAYER; ++i) {
            const PlayerVisionT& teammate = pVision->OurPlayer(i);
            if((i != player) && teammate.Valid()) {
                if(i == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->rightBack()) || i == PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->leftBack()))
                    obs.add_circle(vector2f(teammate.Pos().x(), teammate.Pos().y()), vector2f(teammate.Vel().x(), teammate.Vel().y()), Param::Vehicle::V2::PLAYER_SIZE, 1);
                else
                    obs.add_circle(vector2f(teammate.Pos().x(), teammate.Pos().y()), vector2f(teammate.Vel().x(), teammate.Vel().y()), TEAMMATE_AVOID_DIST, 1);
            }
        }
    }

	// set up opponents as obstacles
	if (!(flags & PlayerStatus::NOT_AVOID_THEIR_VEHICLE)) {
		for(int i=1; i<=Param::Field::MAX_PLAYER; ++i) {
			const PlayerVisionT& opp = pVision->TheirPlayer(i);
			if(opp.Valid()) {
				if( (false && (flags & PlayerStatus::IGNORE_PLAYER_CLOSE_TO_TARGET) && (target.dist(opp.Pos()) < Param::Field::MAX_PLAYER_SIZE / 2)) /*|| opp.Vel().mod() > VELMIN */) {
					continue;
				}
				else {
                    obs.add_circle(vector2f(opp.Pos().x(), opp.Pos().y()), vector2f(opp.Vel().x(), opp.Vel().y()), OPP_AVOID_DIST, 1);
				}
			}
		}
	}

	// 禁区 和 门柱
    if((true || flags & PlayerStatus::DODGE_OUR_DEFENSE_BOX) && (task.executor != PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie()))) {
           // 我方禁区modified by Wang in 2018/3/21
           obs.add_rectangle(vector2f(-Param::Field::PITCH_LENGTH / 2, -Param::Field::PENALTY_AREA_WIDTH / 2),
                             vector2f(-Param::Field::PITCH_LENGTH / 2 + Param::Field::PENALTY_AREA_DEPTH, Param::Field::PENALTY_AREA_WIDTH / 2), 1);

    }
    // ball
	if(flags & PlayerStatus::DODGE_BALL) {
		const MobileVisionT& ball = pVision->Ball();
		obs.add_circle(vector2f(ball.Pos().x(), ball.Pos().y()), vector2f(ball.Vel().x(), ball.Vel().y()), BALL_AVOID_DIST, 1);
	}

	if(flags & PlayerStatus::DODGE_REFEREE_AREA) {
		const MobileVisionT& ball = pVision->Ball();
		obs.add_circle(vector2f(ball.Pos().x(), ball.Pos().y()), vector2f(0.0f, 0.0f), 50.0f, 1);
	}

	obs.set_mask(1);

    // set initial state
    state initial;
    state goal;
    vector<state> result;
    initial.pos = playerPos;
    goal.pos = vector2f(target.x(), target.y());

	pathPlanner[player - 1].init(400, 150, 0.05, 0.55, Param::Field::MAX_PLAYER_SIZE / 2, initial);
	result= pathPlanner[player - 1].plan(&obs, 1, initial, playerVel, goal);
    _path.clear();

    for (int i = 1; i < result.size(); i++) {
        _path.push_back(CGeoPoint(result[i].pos.x, result[i].pos.y)); // ?? ?…￥è·ˉ?????1
    }
}
