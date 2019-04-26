#include <iostream>
#include <math.h>
#include <stdio.h>
#include <CMmotion.h>
#include <utils.h>
#include <fstream>
#include "GDebugEngine.h"
#include "parammanager.h"


using namespace std;

namespace {
    const double min_max_angle_speed = 2;
    const double min_max_angle_acc = 2;

    const double FRAME_PERIOD = 1.0 / Param::Vision::FRAME_RATE;
    bool CARCONTROL = false;
    bool hasSetted = 0;
    ofstream carControlCommand("D://zjunlict//zeus2017ap//bin//play_books//carControlCommand.txt");
    bool xFlag = false;

}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// @fn	void compute_motion_1d(double x0, double v0, double v1, double a_max, double v_max,
 /// 		double a_factor, double &traj_accel, double &traj_time)
 ///
 /// @brief	一维状态下计算运动过程，给定初始速度和末速度，最大加速度和最大速度，返回加速时间和过程时间
 ///
 /// @author	Song Zhibai( Song Zhibai Zju.edu.cn)
 /// @date		2010-4-2
 ///
 /// @param	x0				初始位置
 /// @param	v0				初速度
 /// @param	v1				末速度
 /// @param	a_max			最大加速度
 /// @param	v_max			最大速度
 /// @param	a_factor		常数，影响加速度的因子
 /// @param	traj_accel		计算得加速度
 /// @param	traj_time		计算得加速时间
 ////////////////////////////////////////////////////////////////////////////////////////////////////



void compute_motion_1d(double x0, double v0, double v1,
    double a_max, double d_max, double v_max, double a_factor,
    double &traj_accel, double &traj_time, double &traj_time_acc, double &traj_time_dec, double &traj_time_flat)
{
    if (x0 == 0. && v0 == v1) {
        traj_accel = 0;
        traj_time_acc = traj_time_dec = 0;
        return;
    }

    if(!finite(x0) || !finite(v0) || !finite(v1)) {

        traj_accel = 0;
        traj_time_acc = traj_time_dec = 0;
        return;
    }

    a_max /= a_factor;
    d_max /= a_factor;

    double accel_time_to_v1 = fabs(v1 - v0) / a_max;                                                  // 最大加速度加速到末速度的时间
    double accel_dist_to_v1 = fabs((v1 + v0) / 2.0) * accel_time_to_v1;                               // 单一加速到末速度时的位移
    double decel_time_to_v1 = fabs(v0 - v1) / d_max;                                                  // 最大减速度减速到末速度的时间
    double decel_dist_to_v1 = fabs((v0 + v1) / 2.0) * decel_time_to_v1;                               // 单一减速到末速度时的位移

    // 这个时间很关键，设得较大则定位精度将大大降低 by qxz
    double period = 1 / 40.0; // 一段很小的时间，处理运动到目标点附近时加速度，稳定到点，防止超调

    // 计算时间部分

    // 从x0运动到零点
    // 初速和目标点反向 或 初速大于目标速来不及减速到目标速
    // 全程减速
    if (v0 * x0 > 0 || (fabs(v0) > fabs(v1) && decel_dist_to_v1 > fabs(x0))) {
        // 停下后到达的时间 + 停下所用时间
        double time_to_stop = fabs(v0) / (d_max);                                                       // 停下时间
        double x_to_stop = v0 * v0 / (2.0 * d_max);                                                   // 停止时运动距离

        compute_motion_1d(x0 +  copysign(x_to_stop, v0), 0, v1, a_max * a_factor, d_max * a_factor,
            v_max, a_factor, traj_accel, traj_time, traj_time_acc, traj_time_dec, traj_time_flat);    // 递归运算直到跳出这一条件
        traj_time += time_to_stop;                                                                    // 加上路径规划时间
        traj_time /= 1.25;
        // 减速
        if (traj_time < period) {
            traj_accel = compute_stop(v0, d_max * a_factor); // 很快就要到了，计算一个合适的加速度
        }
        if (time_to_stop < period) {
            traj_accel = time_to_stop / period * - copysign(d_max * a_factor, v0) + (1.0 - time_to_stop / period) * traj_accel;
        }
        else {
            traj_accel = - copysign(d_max * a_factor, v0);
        }

        return;
    }

    // 初速和目标点同向
    if (fabs(v0) > fabs(v1)) {                                                                          // 初速度大于目标速，但可以减速到目标速 先加速再减速
        traj_time_acc = (sqrt((d_max * v0 * v0 + a_max * (v1 * v1 + 2 * d_max * fabs(x0))) / (a_max + d_max)) - fabs(v0)) / a_max;

        if (traj_time_acc < 0.0)
            traj_time_acc = 0;
        traj_time_dec = ((fabs(v0) - fabs(v1)) + a_max * traj_time_acc) / d_max;
    }

    else if (accel_dist_to_v1 > fabs(x0)) {                                                             // 初速度小于目标速，且不可加速到目标速 全程加速
        traj_time_acc = (sqrt(v0 * v0 + 2 * a_max * fabs(x0)) - fabs(v0)) / a_max;
        traj_time_dec = 0.0;
    }

    else {                                                                                              // 初速度小于目标速，且可以加速到目标速 先加速再减速
        traj_time_acc = (sqrt((d_max * v0 * v0 + a_max * (v1 * v1 + 2 * d_max * fabs(x0))) / (a_max + d_max)) - fabs(v0)) / a_max;
        if (traj_time_acc < 0.0)
            traj_time_acc = 0;
        traj_time_dec = ((fabs(v0) - fabs(v1)) + a_max * traj_time_acc) / d_max;
    }

    // 计算所得车速可能超过车最大速度，会有一段匀速运动

    if (traj_time_acc * a_max + fabs(v0) > v_max) {                                                     // 匀速运动的时间
        double dist_without_flat = (v_max * v_max - v0 * v0) / (2 * a_max) + (v_max * v_max - v1 * v1) / (2 * d_max);
        traj_time_flat = (fabs(x0) - dist_without_flat) / v_max;
    }
    else {
        traj_time_flat = 0;
    }

    // 分配加速度部分

    double a_to_v1_at_x0 = fabs(v0 * v0 - v1 * v1) / (2 * fabs(x0));
    double t_to_v1_at_x0 = (-fabs(v0) + sqrt(v0 * v0 + 2 * fabs(a_to_v1_at_x0) * fabs(x0))) / fabs(a_to_v1_at_x0);
    if (t_to_v1_at_x0 < period) {
        traj_accel = - copysign(a_to_v1_at_x0, v0);
        return;
    }

    if (FRAME_PERIOD * a_max + fabs(v0) > v_max && traj_time_flat > period) {                           // 匀速运动阶段
        traj_time = traj_time_flat + traj_time_dec;
        traj_accel = 0;
    }
    else if (traj_time_acc < period && traj_time_dec == 0.0) {                                          // 加速到点
        traj_time = traj_time_acc;
        traj_accel =  copysign(a_max * a_factor, -x0);
    }
    else if (traj_time_acc < period && traj_time_dec > 0.0) {                                           // 加速接近结束且需减速
        traj_time = traj_time_dec;
        if (xFlag) traj_accel =  copysign(d_max * a_factor, -v0);
        else traj_accel =  copysign(d_max * a_factor, -v0);
    }
    else {
        traj_time = traj_time_acc + traj_time_flat / 1.1 + traj_time_dec / 1.1;
        traj_accel =  copysign(a_max * a_factor, -x0);
    }
}

 ////////////////////////////////////////////////////////////////////////////////////////////////////
 /// @fn	void compute_motion_2d(CVector x0, CVector v0, CVector v1, double a_max, double v_max,
 /// 		double a_factor, CVector &traj_accel, double &time)
 ///
 /// @brief 在二维下计算运动过程，给定初始速度向量和最终速度向量，以及最大加速度，最大速度
 ///
 /// @author	Song Zhibai( Song Zhibai Zju.edu.cn)
 /// @date		2010-4-2
 ///
 /// @param	x0						initial coordinate
 /// @param	v0						initial velocities
 /// @param	v1						final velocities
 /// @param	a_max					maxium of accelerate
 /// @param	v_max					maxium of velocities
 /// @param	a_factor				factor of accelerate
 /// @param [in,out]	traj_accel	the traj accel.
 /// @param [in,out]	time		the time.
 ////////////////////////////////////////////////////////////////////////////////////////////////////

void compute_motion_2d(CVector x0, CVector v0, CVector v1,
                    double a_max, double d_max, double v_max,
                    double a_factor, CVector &traj_accel, double &time)
{
  double time_x, time_x_acc, time_x_dec, time_x_flat;
  double time_y, time_y_acc, time_y_dec, time_y_flat;
  double rotangle;
  double traj_accel_x;
  double traj_accel_y;
  if (v1.mod() == 0)
    rotangle = x0.dir();
  else rotangle = v1.dir();

  x0 = x0.rotate(-rotangle);
  v0 = v0.rotate(-rotangle);
  v1 = v1.rotate(-rotangle); //坐标系转换，转换到末速度方向为x轴的坐标系中

  compute_motion_1d(x0.x(), v0.x(), v1.x(), a_max, d_max, v_max, a_factor,
            traj_accel_x, time_x, time_x_acc, time_x_dec, time_x_flat);
  compute_motion_1d(x0.y(), v0.y(), v1.y(), a_max, d_max, v_max, a_factor,
            traj_accel_y, time_y, time_y_acc, time_y_dec, time_y_flat);//两轴同样的最大速度、加速度独立考虑求两轴运动时间

  traj_accel = CVector(traj_accel_x,traj_accel_y);
  if (traj_accel.mod())
    traj_accel = traj_accel.rotate(rotangle);
  if(time_x < 1e-5 || time_x > 50) time_x = 0;
  if(time_y < 1e-5 || time_y > 50) time_y = 0;
  if(time_x < time_y) time = time_y;
  else time = time_x;
}

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @fn	double compute_stop(double v, double max_a)
  ///
  /// @brief	Calculates the stop.
  ///
  /// @author	Song Zhibai( Song Zhibai Zju.edu.cn)
  /// @date		2010-4-2
  ///
  /// @param	v		The v.
  /// @param	max_a	The maximum a.
  ///
  /// @return	The calculated stop.
  ////////////////////////////////////////////////////////////////////////////////////////////////////

double compute_stop(double v, double max_a)
{
    if (fabs(v) > max_a * FRAME_PERIOD) return  copysign(max_a, -v); // 如果一帧内不能减速到0，就用最大加速度
    else return -v / FRAME_PERIOD; // 如果能减到0，加速度就用速度除以一帧的时间即可
}

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// @fn	void goto_point_omni( const PlayerPoseT& start, const PlayerPoseT& final,
  /// 		const PlayerCapabilityT& capability, const double& accel_factor,
  /// 		const double& angle_accel_factor, PlayerPoseT& nextStep)
  ///
  /// @brief	给定初始坐标，结束坐标及小车性能，计算小车可能的轨迹，更新下一个位置的机器人状态
  ///
  /// @author	Song Zhibai( Song Zhibai Zju.edu.cn)
  /// @date		2010-4-2
  ///
  /// @param	start				The start.
  /// @param	final				The final.
  /// @param	capability			The capability.
  /// @param	accel_factor		The accel factor.
  /// @param	angle_accel_factor	The angle accel factor.
  /// @param [in,out]	nextStep	the next step.
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  void goto_point_omni( const PlayerPoseT& start,
      const PlayerPoseT& final,
      const PlayerCapabilityT& capability,
      const double& accel_factor,
      const double& angle_accel_factor,
      PlayerPoseT& nextStep,
      double speed_trans_threashold)
  {
      CGeoPoint target_pos = final.Pos();
      CVector x = start.Pos() - target_pos;
      CVector v = start.Vel();
      double ang = Utils::Normalize(start.Dir() - final.Dir());
      double ang_v = start.RotVel();
      CVector target_vel = final.Vel();
      double max_accel = capability.maxAccel;
      double max_decel = capability.maxDec;
      double max_speed = capability.maxSpeed;

      double max_angle_speed = capability.maxAngularSpeed;
      double max_angle_accel = capability.maxAngularAccel;
      double max_angle_decel = capability.maxAngularDec;
      CVector a;
      double ang_a, factor_a;
      double time_a, time_a_acc, time_a_dec, time_a_flat, time;
//	  if (x.mod() < 5) {
//		  max_accel /= 2;
//		  max_decel /= 2;
//	  }
      xFlag = true;
      compute_motion_2d(x, v, target_vel, max_accel, max_decel, max_speed, accel_factor, a, time);
      xFlag = false;
      factor_a = 1;

      double rotateFactor;
      if(capability.maxSpeed == 0)
          rotateFactor = 1;
      else
        rotateFactor = (1 - start.Vel().mod() / capability.maxSpeed);
      max_angle_speed = min_max_angle_speed + (capability.maxAngularSpeed - min_max_angle_speed) * rotateFactor;
      max_angle_accel = max_angle_decel = min_max_angle_acc + (capability.maxAngularAccel - min_max_angle_acc) * rotateFactor;

      compute_motion_1d(ang, ang_v, 0.0, max_angle_accel, max_angle_decel, max_angle_speed, angle_accel_factor, ang_a, time_a, time_a_acc, time_a_dec, time_a_flat);

      v = v + a * FRAME_PERIOD;
      ang_v += ang_a * FRAME_PERIOD;
      double delta_ang = ang_v * FRAME_PERIOD;
      v.rotate(-delta_ang);
      if (v.mod() > max_speed)
          v = v* max_speed/v.mod();
      if (ang_v>max_angle_speed)
      {
          ang_v = max_angle_speed;
      }
      else if (ang_v<-max_angle_speed)
      {
          ang_v = -max_angle_speed;
      }
      CGeoPoint next_pos = start.Pos()+Utils::Polar2Vector(v.mod()*FRAME_PERIOD,v.dir());
      double next_angle = start.Dir()+ang_v*FRAME_PERIOD;
      double t =  std::max(time,time_a);
      static double t_last;
      static int tmpCnt;
//      cout << ++tmpCnt << " " << t << " " << t_last - t << " " << x.dir() << endl;
      t_last = t;
      nextStep.SetValid(true);
      nextStep.SetPos(next_pos);
      nextStep.SetDir(next_angle);
      nextStep.SetVel(v);
      carControlCommand << v.x() << " " << v.y() << endl;
      nextStep.SetRotVel(ang_v);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn	double expectedCMPathTime(const PlayerPoseT& start, const CGeoPoint& final,
/// 	double maxAccel, double maxVelocity, double accel_factor)
///
/// @brief	调用 compute_motion_2d
///
/// @author	Song Zhibai( Song Zhibai Zju.edu.cn)
/// @date	2010-4-2
///
/// @param	start			The start.
/// @param	final			The final.
/// @param	maxAccel		The maximum accel.
/// @param	maxVelocity		The maximum velocity.
/// @param	accel_factor	The accel factor.
///
/// @return	.
////////////////////////////////////////////////////////////////////////////////////////////////////

double expectedCMPathTime(const PlayerPoseT& start, const CGeoPoint& final, double maxAccel, double maxVelocity, double accel_factor)
{
    CGeoPoint target_pos = final;
    CVector x = start.Pos() - target_pos;
    CVector v = start.Vel();
    CVector target_vel = CVector(0,0);
    CVector a;
    double time;
    xFlag = true;
    compute_motion_2d(x, v, target_vel,
        maxAccel,
        maxAccel,
        maxVelocity,
        accel_factor,
        a, time);
    xFlag = false;
    return time;
}

double predictedTime(const PlayerVisionT& start, const CGeoPoint & Target, const CVector& targetVel)
{
    CVector x = start.Pos() - Target;
    CVector v = (start.Vel().mod() < 2.5) ? CVector(0, 0) : start.Vel();
    double time;
    CVector a;
    xFlag = true;
    compute_motion_2d(x, v, targetVel, 400, 400, 250, 1.5, a, time);
    xFlag = false;
    return time;
}

double predictedTheirTime(const PlayerVisionT& start, const CGeoPoint & Target, const CVector& targetVel)
{
    double max_acc = 500;
    double max_speed = 350;
//    ZSS::ZParamManager::instance()->loadParam(max_acc, "Enemy/MaxAcc", 600);
//    ZSS::ZParamManager::instance()->loadParam(max_speed, "Enemy/MaxSpeed", 400);
    CVector x = start.Pos() - Target;
    CVector v = start.Vel();
    double time;
    CVector a;
    xFlag = true;
    compute_motion_2d(x, v, targetVel, max_acc, max_acc, max_speed, 1.5, a, time);
    xFlag = false;
    return time;
}

double predictedTime2d(const PlayerVisionT& start, const CGeoPoint& final, double maxAccel, double maxVelocity, double accel_factor) {
    CVector x0 = start.Pos() - final;
    CVector trajAcc;
    double trajTime;
    compute_motion_2d(x0, start.Vel(), CVector(0, 0), maxAccel, maxAccel, maxVelocity, accel_factor, trajAcc, trajTime);
    return trajTime;
}

double predictedTime1d(const double &start, const double &end, const double &startVel, const double &maxAccel, const double &maxVelocity, const double endVel) {
    double trajTime, trajAcc, accTime, flatTime, decTime;
    compute_motion_1d(start - end, startVel, endVel, maxAccel, maxAccel, maxVelocity, 1.5, trajAcc, trajTime, accTime, flatTime, decTime);
    return trajTime;
}

bool predictRushSpeed(const PlayerVisionT& start, const CGeoPoint& final, const double& time, const PlayerCapabilityT& capability, CVector& targetVel) {
    CVector x = start.Pos() - final;
    CVector v = start.Vel();
    double zeroTime;
    double fullTime;
    CVector a;
    xFlag = true;
    compute_motion_2d(x, v, CVector(0, 0), capability.maxAccel, capability.maxDec, capability.maxSpeed, 1.5, a, zeroTime);
    if (zeroTime < time) {
        targetVel = CVector(0, 0);
        return true;
    }
    else {
        compute_motion_2d(x, v, Utils::Polar2Vector(capability.maxSpeed, (final - start.Pos()).dir()), capability.maxAccel, capability.maxDec, capability.maxSpeed, 1.5, a, fullTime);
        if (fullTime < time) {
            double triangleDist = pow(capability.maxSpeed, 2) / (2 * capability.maxAccel);
            double triangleTime = capability.maxSpeed / capability.maxAccel;
            double restDist = x.mod() - triangleDist;
            double restTime = time - triangleTime;
            double decTime = sqrt(2 * (capability.maxSpeed * restTime - restDist) / capability.maxAccel);
            targetVel = Utils::Polar2Vector(capability.maxSpeed - decTime * capability.maxAccel, (final - start.Pos()).dir());
            return true;
        }
        else {
            targetVel = Utils::Polar2Vector(capability.maxSpeed, (final - start.Pos()).dir());
            return false;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn	double openSpeedCircle(const PlayerPoseT& start, const double dist2Center, const double dirDiff,
///  const double finalAngle, PlayerPoseT& nextStep)
///
/// @param	start			The start.
/// @param  dist2Center     The rotate radius.
/// @param  dirDiff         The direcition diff between robot angle and circle tangent.
/// @param  finalAngle      The final angle u want the robot finish at.
/// @param  nextStep        The return trajectory.
///
/// @return	.
////////////////////////////////////////////////////////////////////////////////////////////////////

void openSpeedCircle(const PlayerPoseT& start, const double dist2Center, const int rotateMethod, const double finalAngle, PlayerPoseT& nextStep, const double dirDiff) {
    CGeoPoint startPos = start.Pos();
    double startRotVel = start.RotVel();

    double startDir, finalDir;
    if (rotateMethod == 1 || rotateMethod == 4) {
        startDir = Utils::Normalize(start.Dir() + dirDiff);
        finalDir = Utils::Normalize(finalAngle + dirDiff);
    }
    else {
        startDir = Utils::Normalize(start.Dir() - dirDiff);
        finalDir = Utils::Normalize(finalAngle - dirDiff);
    }

    double posDirDiff = abs(Utils::Normalize(startDir - finalDir));
//    cout << start.Dir() << " " << startDir << " " << posDirDiff << " " << rotateMethod << endl;

    double rotAcc, rotTime, rotAccTime, rotDecTime, rotFlatTime;

    if (rotateMethod == 1 || rotateMethod == 4) {
        compute_motion_1d(posDirDiff, start.RotVel(), 0, 15, 5, 5, 1.5, rotAcc, rotTime, rotAccTime, rotDecTime, rotFlatTime);
    }
    else {
        compute_motion_1d(-posDirDiff, start.RotVel(), 0, 15, 5, 5, 1.5, rotAcc, rotTime, rotAccTime, rotDecTime, rotFlatTime);
    }

    double rotVel = startRotVel + rotAcc / Param::Vision::FRAME_RATE;
    double velMod = abs(rotVel * dist2Center);
    CVector vel;
    if (rotateMethod == 1 || rotateMethod == 3) {
        vel = Utils::Polar2Vector(velMod, startDir);
    }
    else {
        vel = Utils::Polar2Vector(velMod, Utils::Normalize(startDir + Param::Math::PI));
    }

    CVector localVel = vel.rotate(- start.Dir());
    //cout << rotVel << " " << localVel << endl;
    CGeoPoint nextPos = startPos + vel / Param::Vision::FRAME_RATE;
    double nextDir = startDir + rotVel / Param::Vision::FRAME_RATE;

    nextStep.SetValid(true);
    nextStep.SetPos(nextPos);
    nextStep.SetDir(nextDir);
    nextStep.SetVel(localVel);
    nextStep.SetRotVel(rotVel);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// @fn	double openSpeedCircle(const PlayerPoseT& start, const double dist2Center, const double dirDiff,
///  const double finalAngle, PlayerPoseT& nextStep)
///
/// @brief  special for GoAndTurnKickV4 CmuTurnKickV1. It is faster.
///
/// @param	start			The start.
/// @param  dist2Center     The rotate radius.
/// @param  dirDiff         The direcition diff between robot angle and circle tangent.
/// @param  finalAngle      The final angle u want the robot finish at.
/// @param  nextStep        The return trajectory.
///
/// @return	.
////////////////////////////////////////////////////////////////////////////////////////////////////


void openSpeedCircleV2(const PlayerPoseT& start, const double dist2Center,
                       const int rotateMethod, const double finalAngle,
                       PlayerPoseT& nextStep, const double dirDiff) {
    CGeoPoint startPos = start.Pos();
    double startVel = start.Vel().mod();

    double startDir, finalDir;
    if ( rotateMethod == 1 || rotateMethod == 4 ) {
        startDir = Utils::Normalize(start.Dir() + dirDiff);
        finalDir = Utils::Normalize(finalAngle + dirDiff);
    }
    else {
        startDir = Utils::Normalize(start.Dir() - dirDiff);
        finalDir = Utils::Normalize(finalAngle - dirDiff);
    }

    double posDirDiff = abs(Utils::Normalize(startDir - finalDir));

    double rotAcc, rotTime, rotAccTime, rotDecTime, rotFlatTime;

    bezierMotion1d(posDirDiff*dist2Center, startVel, 0, 600, 600, 400, rotAcc,
                   rotTime, rotAccTime, rotDecTime, rotFlatTime);

    double velMod = abs(startVel + rotAcc / Param::Vision::FRAME_RATE);
    double rotVel = velMod / dist2Center;
    CVector vel;

    vel = Utils::Polar2Vector(velMod, startDir);

    if ( rotateMethod == 1 || rotateMethod == 3 ) {
        rotVel = -rotVel;
    }

    CVector localVel = vel.rotate(- start.Dir());
    //cout << rotVel << " " << localVel << endl;
    CGeoPoint nextPos = startPos + vel / Param::Vision::FRAME_RATE;
    double nextDir = startDir + rotVel / Param::Vision::FRAME_RATE;

    nextStep.SetValid(true);
    nextStep.SetPos(nextPos);
    nextStep.SetDir(nextDir);
    nextStep.SetVel(localVel);
    nextStep.SetRotVel(rotVel);
}

void bezierMotion1d(double x0, double v0, double v1, double aMax, double dMax,
                    double vMax, double &trajAccel, double &trajTime,
                    double &trajTimeAcc, double &trajTimeDec,
                    double &trajTimeFlat) {
    if(x0 == 0 && v0 == v1) {
        trajTime = trajTimeAcc = trajTimeDec = trajAccel = trajTimeFlat = 0;
        return;
    }
    double aMaxOri = aMax;
    double dMaxOri = dMax;
    double flatVel = 0.2 * vMax;

    double period = 1 / 40.0; //参考CMmotion中的那个值，处理运动到目标点附近时的加速度
    double accelTimeToV1 = fabs(v1 - v0) / aMax;
    double accelDistToV1 = fabs((v1 + v0) / 2.0) * accelTimeToV1;
    double decelTimeToV1 = fabs(v1 - v0) / dMax;
    double decelDistToV1 = fabs((v0 + v1) / 2.0) * decelTimeToV1;

    if(v0 * x0 < 0 || (fabs(v0) > fabs(v1) && decelDistToV1 > fabs(x0))) {
        double timeToStop = fabs(v0) / dMax;
        double distToStop = v0 * v0 /(2.0 * dMax);

        bezierMotion1d(x0 + copysign(distToStop, v0), 0, v1, aMaxOri, dMaxOri,
                       vMax, trajAccel, trajTime, trajTimeAcc, trajTimeDec,
                       trajTimeFlat);

        trajTime += timeToStop;
        if(trajTime < period) {
            if ( fabs(v0) / dMax > FRAME_PERIOD )
                trajAccel = copysign( dMaxOri, -v0 );
            else trajAccel = copysign( fabs(v0) / FRAME_PERIOD , -v0 );
        }
        else if(timeToStop < period) {
            trajAccel = timeToStop / period * copysign( dMaxOri, -v0 ) +
                    ( 1.0 - timeToStop / period ) * copysign( trajAccel, -v0 );
        }
        else {
            trajAccel = copysign( dMaxOri, -v0 );
        }
        return;
    }
    //后面是初速度和目标点同向的情况,即不存在反向的情况，末速度可达
    if(fabs(v0) >= fabs(v1)) {
        //较大速度不小于平动速度，此时用较大速度平动，然后减速到目标速度；
        if(fabs(v0) >= flatVel) {
            flatVel = fabs(v0);
            trajTimeAcc = 0;
            trajTimeFlat = (fabs(x0) - decelDistToV1) / fabs(v0);
            trajTimeDec = decelTimeToV1;  //考虑方向的减速时间,可能末速度与位移反向
        }
        else { //较大速度小于平动设定速度，此时先加速到平动速度，再平动、减速到目标速度
            double distToFlatVel = (flatVel * flatVel - v0 * v0) / aMax;
            double distToV2 = (flatVel * flatVel - v1 * v1) / dMax;
            if(distToFlatVel + distToV2 <= fabs(x0)) { //可以达到flatVel
                trajTimeAcc = (flatVel - fabs(v0)) / aMax;
                trajTimeDec = fabs(copysign(flatVel, v0) - v1) / dMax;
                trajTimeFlat = (fabs(x0) - distToFlatVel - distToV2) / flatVel;
            }
            else { //不可达flatVel，说明位移很短了,改用三角规划
                trajTimeAcc = (sqrt((v0 * v0 + 2 * aMax * fabs(x0)) /
                                    (1 + aMax / dMax)) - fabs(v0)) / aMax;
                flatVel = fabs(v0) + trajTimeAcc * aMax;
                trajTimeFlat = 0;
                trajTimeDec = (trajTimeAcc * aMax + fabs(v0) - fabs(v1)) / dMax;
            }
        }
    }
    //初速度小于末速度
    else {
        flatVel = fabs(v1);
        if(accelDistToV1 > fabs(x0)) { //即使一直加速也无法到达目标速度
            trajTimeAcc = (sqrt(v0 * v0 + 2 * aMax * fabs(x0)) - fabs(v0))
                    / aMax;
            trajTimeDec = trajTimeFlat = 0;
        }
        else { //可以加速到目标速度，先加速到目标速度，再匀速运动
            trajTimeAcc = accelTimeToV1;
            trajTimeFlat = (fabs(x0) - accelDistToV1) / fabs(v1);
            trajTimeDec = 0;
        }
    }

//    根据上面的时间计算速度，考虑抖动问题： 抖动要分较大速度大于flatV和较大速度小于flatV
//    两种情况；
    double accelToV1AtX0 = fabs(v0 * v0 - v1 * v1) / (2 * fabs(x0));
    double timeToV1 = fabs(v1 - v0) / accelToV1AtX0;
    if(timeToV1 < period) { //先判断快到达目标点的情况，要求稳定到点
        trajTime = timeToV1;
        trajAccel = copysign(accelToV1AtX0, -v0);
        return;
    }
    if(fabs(v0) + aMax * FRAME_PERIOD > flatVel && trajTimeFlat > period) {
        trajTime = trajTimeFlat + trajTimeDec;
        trajAccel = 0;
    }
    else if(trajTimeAcc < period && trajTimeDec == 0) {
        trajTime = trajTimeAcc;
        trajAccel = copysign(aMaxOri, v0);
    }
    else if(trajTimeAcc < period && trajTimeFlat < period && trajTimeDec > 0) {
        trajTime = trajTimeDec;
        trajAccel = copysign(dMaxOri, -v0);
    }
    else {
        trajTime = trajTimeAcc + trajTimeDec + trajTimeFlat;
        trajAccel = copysign(aMaxOri, v0);
    }
}
