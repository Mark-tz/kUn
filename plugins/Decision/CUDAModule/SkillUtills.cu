#include <cuda.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include <math_functions.h>
#include <math.h>
#include <stdio.h>

#define FRAME_PERIOD (1 / 60.0)
#define ZERO_NUM (1e-8)
#define A_FACTOR (1.5)
#define OUR_MAX_ACC (450)
#define OUR_MAX_DEC (450)
#define OUR_MAX_VEL (300)
#define THEIR_MAX_ACC (500)
#define THEIR_MAX_DEC (500)
#define THEIR_MAC_VEL (350)
#define PI (3.14159265359)
#define G (9.8)
#define SQRT_2 (1.414)
#define TIME_FOR_OUR (0)
#define TIME_FOR_OUR_BOTH_KEEP (-0.2)
#define TIME_FOR_THEIR_BOTH_KEEP (-0.4)
#define TIME_FOR_THEIR (-0.6)
#define TIME_FOR_JUDGE_HOLDING (0.5)

#define FRICTION (87)
#define PLAYER_CENTER_TO_BALL_CENTER (60)
#define MAX_PLAYER_NUM (12)
#define THREAD_NUM (128)
#define BLOCK_X (16)
#define BLOCK_Y (MAX_PLAYER_NUM * 2)
#define MAX_BALL_SPEED (650)
#define MIN_BALL_SPEED (50)
#define BALL_SPEED_UNIT ((MAX_BALL_SPEED - MIN_BALL_SPEED) / BLOCK_X)
#define MIN_DELTA_TIME (0.2)

#define MAX_CHIP_SPEED (650)
#define MIN_CHIP_SPEED (100)
#define CHIP_SPEED_UNIT ((MAX_CHIP_SPEED - MIN_CHIP_SPEED) / BLOCK_X)

namespace  {
    const int FIELD_LENGTH = 1200;
    const int FIELD_WIDTH  = 900;
    const int PENALTY_LENGTH = 120;
    const int PENALTY_WIDTH = 240;
}

typedef struct {
    double x, y;
} Vector;

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point Pos;
    Vector Vel;
    bool isValid;
} Player;

typedef struct {
    Point interPos;
    double interTime;
    double Vel;
    float dir;
    int playerIndex;
    double deltaTime;
    double Q;
} rType;

__device__ bool if_finite(double a) {
    return fabs(a) < 9999;
}

__device__ bool IsInField(Point p, double buffer=10) {
    return (p.x > -FIELD_LENGTH / 2 + buffer && p.x < FIELD_LENGTH / 2 - buffer
            && p.y < FIELD_WIDTH / 2 - buffer && p.y > -FIELD_WIDTH / 2 + buffer);
}

__device__ bool IsInPenalty(Point p, double buffer=20) {
    return (p.x < -FIELD_LENGTH/2 + PENALTY_LENGTH && p.x > -FIELD_LENGTH/2 && p.y > -PENALTY_WIDTH/2 && p.y < PENALTY_WIDTH/2)
            || (p.x > FIELD_LENGTH/2 - PENALTY_LENGTH && p.x < FIELD_LENGTH/2 && p.y > -PENALTY_WIDTH/2 && p.y < PENALTY_WIDTH/2);
}

__device__ void CUDA_compute_motion_1d(double x0, double v0, double v1,
    double a_max, double d_max, double v_max, double a_factor,
    double &traj_accel, double &traj_time, double &traj_time_acc, double &traj_time_dec, double &traj_time_flat)
{
    if (x0 == 0 && v0 == v1) {
        traj_accel = 0;
        traj_time_acc = traj_time_dec = 0;
        return;
    }

    if (!if_finite(x0) || !if_finite(v0) || !if_finite(v1)) {
        traj_accel = 0;
        traj_time_acc = traj_time_dec = 0;
        return;
    }

    a_max /= a_factor;
    d_max /= a_factor;

    double accel_time_to_v1 = fabs(v1 - v0) / a_max;
    double accel_dist_to_v1 = fabs((v1 + v0) / 2.0) * accel_time_to_v1;
    double decel_time_to_v1 = fabs(v0 - v1) / d_max;
    double decel_dist_to_v1 = fabs((v0 + v1) / 2.0) * decel_time_to_v1;

    double period = 1 / 40.0;

    if (v0 * x0 > 0 || (fabs(v0) > fabs(v1) && decel_dist_to_v1 > fabs(x0))) {
        double time_to_stop = fabs(v0) / (d_max);
        double x_to_stop = v0 * v0 / (2.0 * d_max);

        CUDA_compute_motion_1d(x0 + copysign(x_to_stop, v0), 0, v1, a_max * a_factor, d_max * a_factor,
            v_max, a_factor, traj_accel, traj_time, traj_time_acc, traj_time_dec, traj_time_flat);
        traj_time += time_to_stop;
        traj_time /= 1.25;
        traj_accel = 0;

        return;
    }

    if (fabs(v0) > fabs(v1)) {
        traj_time_acc = (sqrt((d_max * v0 * v0 + a_max * (v1 * v1 + 2 * d_max * fabs(x0))) / (a_max + d_max)) - fabs(v0)) / a_max;

        if (traj_time_acc < 0.0)
            traj_time_acc = 0;
        traj_time_dec = ((fabs(v0) - fabs(v1)) + a_max * traj_time_acc) / d_max;
    }

    else if (accel_dist_to_v1 > fabs(x0)) {
        traj_time_acc = (sqrt(v0 * v0 + 2 * a_max * fabs(x0)) - fabs(v0)) / a_max;
        traj_time_dec = 0.0;
    }

    else {
        traj_time_acc = (sqrt((d_max * v0 * v0 + a_max * (v1 * v1 + 2 * d_max * fabs(x0))) / (a_max + d_max)) - fabs(v0)) / a_max;
        if (traj_time_acc < 0.0)
            traj_time_acc = 0;
        traj_time_dec = ((fabs(v0) - fabs(v1)) + a_max * traj_time_acc) / d_max;
    }


    if (traj_time_acc * a_max + fabs(v0) > v_max) {
        double dist_without_flat = (v_max * v_max - v0 * v0) / (2 * a_max) + (v_max * v_max - v1 * v1) / (2 * d_max);
        traj_time_flat = (fabs(x0) - dist_without_flat) / v_max;
    }
    else {
        traj_time_flat = 0;
    }


    double a_to_v1_at_x0 = fabs(v0 * v0 - v1 * v1) / (2 * fabs(x0));
    double t_to_v1_at_x0 = (-fabs(v0) + sqrt(v0 * v0 + 2 * fabs(a_to_v1_at_x0) * fabs(x0))) / fabs(a_to_v1_at_x0);
    if (t_to_v1_at_x0 < period) {
        traj_accel = -copysign(a_to_v1_at_x0, v0);
        return;
    }

    if (FRAME_PERIOD * a_max + fabs(v0) > v_max && traj_time_flat > period) {
        traj_time = traj_time_flat + traj_time_dec;
        traj_accel = 0;
    }
    else if (traj_time_acc < period && traj_time_dec == 0.0) {
        traj_time = traj_time_acc;
        traj_accel = copysign(a_max * a_factor, -x0);
    }
    else if (traj_time_acc < period && traj_time_dec > 0.0) {
        traj_time = traj_time_dec;
        traj_accel = copysign(d_max * a_factor, -v0);

    }
    else {
        traj_time = traj_time_acc + traj_time_flat / 1.1 + traj_time_dec / 1.1;
        traj_accel = copysign(a_max * a_factor, -x0);
    }
}

__device__ double CUDA_predictedTime(double x0, double y0, double x1, double y1, double vx, double vy) {
    double timeX, timeXAcc, timeXDec, timeXFlat, acc;
    double timeY, timeYAcc, timeYDec, timeYFlat;
    double x = x0 - x1;
    double y = y0 - y1;
    double newVelAngle = atan2(vy, vx) - atan2(y, x);
    double length = sqrt(vx * vx + vy * vy);
    x = sqrt(x * x + y * y);
    y = 0.0;
    vx = length * cospi(newVelAngle);
    vy = length * sinpi(newVelAngle);
    CUDA_compute_motion_1d(x, vx, 0, 450, 450, 300, 1.5, acc, timeX, timeXAcc, timeXDec, timeXFlat);
    CUDA_compute_motion_1d(y, vy, 0, 450, 450, 300, 1.5, acc, timeY, timeYAcc, timeYDec, timeYFlat);
    if (timeX < 1e-5 || timeX > 50) timeX = 0;
    if (timeY < 1e-5 || timeY > 50) timeY = 0;
    return (timeX > timeY ? timeX : timeY);
}

__device__ double CUDA_predictedTheirTime(double x0, double y0, double x1, double y1, double vx, double vy) {
    double timeX, timeXAcc, timeXDec, timeXFlat, acc;
    double timeY, timeYAcc, timeYDec, timeYFlat;
    double x = x0 - x1;
    double y = y0 - y1;
    double newVelAngle = atan2(vy, vx) - atan2(y, x);
    double length = sqrt(vx * vx + vy * vy);
    x = sqrt(x * x + y * y);
    y = 0.0;
    vx = length * cospi(newVelAngle);
    vy = length * sinpi(newVelAngle);
    CUDA_compute_motion_1d(x, vx, 0, 500, 500, 350, 1.5, acc, timeX, timeXAcc, timeXDec, timeXFlat);
    CUDA_compute_motion_1d(y, vy, 0, 500, 500, 350, 1.5, acc, timeY, timeYAcc, timeYDec, timeYFlat);
    if (timeX < 1e-5 || timeX > 50) timeX = 0;
    if (timeY < 1e-5 || timeY > 50) timeY = 0;
    return (timeX > timeY ? timeX : timeY);
}

__device__ bool CUDA_predictedInterTime(Point mePoint, Point ballPoint, Vector meVel, Vector ballVel, Point* interceptPoint, double* interTime, double responseTime) {
    if(sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) < 40){
        *interceptPoint = ballPoint;
        *interTime = CUDA_predictedTime(mePoint.x, mePoint.y, interceptPoint->x, interceptPoint->y, meVel.x, meVel.y);
        return true;
    }
    const double ballAcc = FRICTION / 2;
    double ballArriveTime = 0;
    double meArriveTime = 9999;
    const double stepTime = 0.1;
    double testBallLength = 0;
    Point testPoint = ballPoint;
    double testVel = sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
    double max_time = sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) / ballAcc;

    bool canInter = true;
    for (ballArriveTime = 0; ballArriveTime < max_time; ballArriveTime += stepTime ) {
        testVel = sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) - ballAcc*ballArriveTime;//v_0-at
        testBallLength = PLAYER_CENTER_TO_BALL_CENTER + (sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) + testVel)*ballArriveTime / 2;
        Vector direc;
        direc.x = testBallLength * ballVel.x / sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
        direc.y = testBallLength * ballVel.y / sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
        testPoint.x = ballPoint.x + direc.x;
        testPoint.y = ballPoint.y + direc.y;
        meArriveTime = CUDA_predictedTime(mePoint.x, mePoint.y, testPoint.x, testPoint.y, meVel.x, meVel.y);
        if(meArriveTime < 0.15) meArriveTime = 0;
        if(IsInPenalty(testPoint)) continue;
        if (!IsInField(testPoint)) {
            canInter = false;
            break;
        }
        if(meArriveTime + responseTime < ballArriveTime) break;
    }
    if(!canInter || ballArriveTime >= max_time) {
        interceptPoint->x = 9999;
        interceptPoint->y = 9999;
        *interTime = 9999;
        return false;
    }
    *interceptPoint = testPoint;
    *interTime = CUDA_predictedTime(mePoint.x, mePoint.y, interceptPoint->x, interceptPoint->y, meVel.x, meVel.y);
    return true;
}

__device__ bool CUDA_predictedChipInterTime(Point mePoint, Point ballPoint, Vector meVel, Vector ballVel, Point* interceptPoint, double* interTime, double responseTime) {
    double chipVel = sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
    double meArriveTime = 9999;
    double ballAcc = FRICTION / 2.0;
    double stepTime = 0.1;
    double testBallLength = 0;
    Point testPoint = ballPoint;

    double factor_1 = 0.2;
    double factor_2 = 0.1;

    double time_1 = SQRT_2 * chipVel / 100.0 / G;
    double time_2 = SQRT_2 * chipVel * factor_1 / 100.0 / G;

    double length_1 = chipVel * time_1 / SQRT_2;
    double length_2 = chipVel * time_2 * factor_1 / SQRT_2;


    double moveVel = chipVel / SQRT_2 * factor_2;

    bool canInter = true;
    double ballDropTime = time_1 + time_2;
    double max_time = moveVel / ballAcc + ballDropTime;
    double afterArrivedTime = 0;
    while (afterArrivedTime < max_time) {

        Vector direc;
        testBallLength = length_1 + length_2 + (moveVel * afterArrivedTime - 0.5 * ballAcc * afterArrivedTime * afterArrivedTime);

        direc.x = testBallLength * ballVel.x / sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
        direc.y = testBallLength * ballVel.y / sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
        testPoint.x = ballPoint.x + direc.x;
        testPoint.y = ballPoint.y + direc.y;
        meArriveTime = CUDA_predictedTime(mePoint.x, mePoint.y, testPoint.x, testPoint.y, meVel.x, meVel.y);
        if(meArriveTime < 0.10) meArriveTime = 0;

        if(IsInPenalty(testPoint)) {
            afterArrivedTime += stepTime;
            continue;
        }
        if (!IsInField(testPoint)) {
            canInter = false;
            break;
        }
        if(meArriveTime + responseTime < ballDropTime + afterArrivedTime) break;
        afterArrivedTime += stepTime;
    }

    if(!canInter || afterArrivedTime >= max_time) {
        interceptPoint->x = 9999;
        interceptPoint->y = 9999;
        *interTime = 9999;
        return false;
    }

    *interceptPoint = testPoint;
    *interTime = CUDA_predictedTime(mePoint.x, mePoint.y, interceptPoint->x, interceptPoint->y, meVel.x, meVel.y);
    return true;
}

__device__ bool CUDA_predictedTheirInterTime(Point mePoint, Point ballPoint, Vector meVel, Vector ballVel, Point* interceptPoint, double* interTime, double responseTime) {
    if(sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) < 40){
        *interceptPoint = ballPoint;
        *interTime = CUDA_predictedTheirTime(mePoint.x, mePoint.y, interceptPoint->x, interceptPoint->y, meVel.x, meVel.y);
        return true;
    }
    const double ballAcc = FRICTION / 2;
    double ballArriveTime = 0;
    double meArriveTime = 9999;
    const double stepTime = 0.1;
    double testBallLength = 0;
    Point testPoint = ballPoint;
    double testVel = sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
    double max_time = sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) / ballAcc;

    bool canInter = true;
    for (ballArriveTime = 0; ballArriveTime < max_time; ballArriveTime += stepTime ) {
        testVel = sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) - ballAcc*ballArriveTime;//v_0-at
        testBallLength = PLAYER_CENTER_TO_BALL_CENTER + (sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y) + testVel)*ballArriveTime / 2;
        Vector direc;
        direc.x = testBallLength * ballVel.x / sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
        direc.y = testBallLength * ballVel.y / sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
        testPoint.x = ballPoint.x + direc.x;
        testPoint.y = ballPoint.y + direc.y;
        meArriveTime = CUDA_predictedTheirTime(mePoint.x, mePoint.y, testPoint.x, testPoint.y, meVel.x, meVel.y);
        if(meArriveTime < 0.15) meArriveTime = 0;
        if(IsInPenalty(testPoint)) continue;
        if (!IsInField(testPoint)) {
            canInter = false;
            break;
        }
        if(meArriveTime + responseTime < ballArriveTime) break;
    }
    if(!canInter) {
        interceptPoint->x = 9999;
        interceptPoint->y = 9999;
        *interTime = 9999;
        return false;
    }
    *interceptPoint = testPoint;
    *interTime = CUDA_predictedTime(mePoint.x, mePoint.y, interceptPoint->x, interceptPoint->y, meVel.x, meVel.y);
    return true;
}

__global__ void calculateAllInterInfo(Player* players, Point* ballPos, rType* bestPass) {
    int angleIndex = threadIdx.x;
    int speedIndex = blockIdx.x;
    int playerNum =  blockIdx.y;

    Vector ballVel;
    ballVel.x = (speedIndex * BALL_SPEED_UNIT + MIN_BALL_SPEED) * cospi(2*PI* angleIndex / THREAD_NUM);
    ballVel.y = (speedIndex * BALL_SPEED_UNIT + MIN_BALL_SPEED) * sinpi(2*PI* angleIndex / THREAD_NUM);

    double interTime;
    Point interPoint;
    interTime = 9999;
    interPoint.x = 9999;
    interPoint.y = 9999;
    if( players[playerNum].isValid && playerNum < 12)
         CUDA_predictedInterTime(players[playerNum].Pos, *ballPos, players[playerNum].Vel, ballVel, &interPoint, &interTime, 0);
    else if(players[playerNum].isValid)
         CUDA_predictedTheirInterTime(players[playerNum].Pos, *ballPos, players[playerNum].Vel, ballVel, &interPoint, &interTime, 0);

    int offset = blockIdx.y + gridDim.y * (threadIdx.x + blockIdx.x * blockDim.x);
    bestPass[offset].interPos = interPoint;
    bestPass[offset].interTime = interTime;
    bestPass[offset].playerIndex = playerNum;
    bestPass[offset].dir = 2*PI* angleIndex / THREAD_NUM;
    bestPass[offset].Vel = speedIndex * BALL_SPEED_UNIT + MIN_BALL_SPEED;
//    /***************** chip *******************/
    interTime = 9999;
    interPoint.x = 9999;
    interPoint.y = 9999;
    ballVel.x = (speedIndex * CHIP_SPEED_UNIT + MIN_CHIP_SPEED) * cospi(2 * PI * angleIndex / THREAD_NUM);
    ballVel.y = (speedIndex * CHIP_SPEED_UNIT + MIN_CHIP_SPEED) * sinpi(2 * PI * angleIndex / THREAD_NUM);

    if( players[playerNum].isValid && playerNum < 12)
         CUDA_predictedChipInterTime(players[playerNum].Pos, *ballPos, players[playerNum].Vel, ballVel, &interPoint, &interTime, 0);
      else if(players[playerNum].isValid)
         CUDA_predictedChipInterTime(players[playerNum].Pos, *ballPos, players[playerNum].Vel, ballVel, &interPoint, &interTime, 0);


    offset += BLOCK_X * BLOCK_Y * THREAD_NUM;
    bestPass[offset].interPos = interPoint;
    bestPass[offset].interTime = interTime;
    bestPass[offset].playerIndex = playerNum;
    bestPass[offset].dir = 2 * PI * angleIndex / THREAD_NUM;
    bestPass[offset].Vel = speedIndex * CHIP_SPEED_UNIT + MIN_CHIP_SPEED;
    __syncthreads();
}

__global__ void getBest(rType* passPoints) {
    __shared__ rType iP[BLOCK_Y];
    int blockId = blockIdx.y * gridDim.x + blockIdx.x;
    int playerNum = threadIdx.x;
    iP[playerNum] = passPoints[blockId * blockDim.x + playerNum];
    __syncthreads();
    bool even = true;
    for(int i = 0; i < blockDim.x; i++) {
        if(playerNum < blockDim.x - 1 && even && iP[playerNum].interTime > iP[playerNum + 1].interTime) {
            rType temp;
            temp = iP[playerNum + 1];
            iP[playerNum + 1] = iP[playerNum];
            iP[playerNum] = temp;
        }
        else if(playerNum > 0 && !even && iP[playerNum].interTime < iP[playerNum - 1].interTime) {
            rType temp;
            temp = iP[playerNum];
            iP[playerNum] = iP[playerNum - 1];
            iP[playerNum - 1] = temp;
        }
        even = !even;
        __syncthreads();
    }
    passPoints[blockId * blockDim.x + playerNum] = iP[playerNum];

    /************************/
    __shared__ rType iP2[BLOCK_Y];
    iP2[playerNum] = passPoints[blockId * blockDim.x + playerNum + BLOCK_X * BLOCK_Y * THREAD_NUM];
    __syncthreads();
    even = true;
    for(int i = 0; i < blockDim.x; i++) {
        if(playerNum < blockDim.x - 1 && even && iP2[playerNum].interTime > iP2[playerNum + 1].interTime) {
            rType temp;
            temp = iP2[playerNum + 1];
            iP2[playerNum + 1] = iP2[playerNum];
            iP2[playerNum] = temp;
        }
        else if(playerNum > 0 && !even && iP2[playerNum].interTime < iP2[playerNum - 1].interTime) {
            rType temp;
            temp = iP2[playerNum];
            iP2[playerNum] = iP2[playerNum - 1];
            iP2[playerNum - 1] = temp;
        }
        even = !even;
        __syncthreads();
    }
    passPoints[blockId * blockDim.x + playerNum + BLOCK_X * BLOCK_Y * THREAD_NUM] = iP2[playerNum];
    __syncthreads();
}


extern "C" void BestPass(Player* players, Point* ball, rType* result) {
    rType *bestPass;

    cudaMallocManaged((void**)&bestPass, 2 * BLOCK_X * BLOCK_Y * THREAD_NUM * sizeof(rType));

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);

    dim3 bolcks(BLOCK_X, BLOCK_Y);
    calculateAllInterInfo <<< bolcks, THREAD_NUM >>> (players, ball, bestPass);

    dim3 blocks2(BLOCK_X, THREAD_NUM);
    getBest<<< blocks2, BLOCK_Y >>> (bestPass);

    cudaError_t cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess){
        printf("CUDA ERROR: %d\n", (int)cudaStatus);
        printf("Error Name: %s\n", cudaGetErrorName(cudaStatus));
        printf("Description: %s\n", cudaGetErrorString(cudaStatus));
    }

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    printf("Time: %.5f ms\n", milliseconds);

    rType defaultPlayer;
    defaultPlayer.dir = 9999;
    defaultPlayer.interPos.x = 9999;
    defaultPlayer.interPos.y = 9999;
    defaultPlayer.interTime = 9999;
    defaultPlayer.Vel = 9999;
    defaultPlayer.deltaTime = -9999;
    for(int i = 0; i < BLOCK_X * BLOCK_Y * THREAD_NUM; i += BLOCK_Y) {
        int playerNum = 0;
        for(int j = 0; j < MAX_PLAYER_NUM; j++) {
            if(bestPass[i + j].playerIndex > 11) {
                while(playerNum < MAX_PLAYER_NUM) {
                    result[i / 2 + playerNum] = defaultPlayer;
                    playerNum++;
                }
                for(int k = 0; k < j; k++) {
                    result[i / 2 + k].deltaTime = bestPass[i + j].interTime - result[i / 2 + k].interTime;
                    if(result[i / 2 + k].deltaTime < MIN_DELTA_TIME)
                        result[i / 2 + k] = defaultPlayer;
                }
                break;
            }
            else {
                result[i / 2 + playerNum] = bestPass[i + j];
                playerNum++;
            }
        }
    }
    for(int i = BLOCK_X * BLOCK_Y * THREAD_NUM; i < 2 * BLOCK_X * BLOCK_Y * THREAD_NUM; i += BLOCK_Y) {
        int playerNum = 0;

        for(int j = 0; j < MAX_PLAYER_NUM; j++) {

            if(bestPass[i + j].playerIndex > 11) {
                while(playerNum < MAX_PLAYER_NUM) {
                    result[i / 2 + playerNum] = defaultPlayer;
                    playerNum++;
                }
                for(int k = 0; k < j; k++) {
                    result[i / 2 + k].deltaTime = bestPass[i + j].interTime - result[i / 2 + k].interTime;
                    if(result[i / 2 + k].deltaTime < MIN_DELTA_TIME)
                        result[i / 2 + k] = defaultPlayer;
                }
                break;
            }
            else {
                result[i / 2 + playerNum] = bestPass[i + j];
                playerNum++;
            }
        }
    }
    cudaFree(bestPass);
}

