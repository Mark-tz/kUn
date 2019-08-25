#ifdef USE_CUDA_MODULE
#include "CUDAModule.h"
#include <cuda.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include <vector>
#include <QDebug>
#include <GDebugEngine.h>
#include <geometry.h>
#include "parammanager.h"
#include "zsplugin.hpp"
#include "PlayInterface.h"
#include "TaskMediator.h"
#include "ShootRangeList.h"
extern Semaphore vision_to_cuda;
const double PI = 3.14159265359;
const double BallLineValidThreadhold = 30;

const double wDefenDist = -0.2;
const double wVel = 0.0002;
const double wShootAngle = 1;
const double wDist = 0;
const double wRefracAngle = -0.2;

const double THEIR_ROBOT_INTER_THREADHOLD = 30;

extern "C" {
    void BestPass(Player*, Point*, rType* result);
}


namespace {
    bool show_pass_points = false;
    bool show_pass_lines = false;
}
CUDAModule::CUDAModule() : leader(1), bestFlatPassVel(0), bestChipPassVel(0) {
    pVision = nullptr;
    thread = nullptr;
    ZSS::ZParamManager::instance()->loadParam(show_pass_points,"Alert/ShowPassPoints",false);
    ZSS::ZParamManager::instance()->loadParam(show_pass_lines,"Alert/ShowPassLines",false);
    cudaMallocManaged((void**)&players, 2 * 12 * sizeof(Player));
    cudaMallocManaged((void**)&ball, sizeof(Point));
}

CUDAModule::~CUDAModule() {
    cudaFree(players);
    cudaFree(ball);
}

void CUDAModule::initialize(const CVisionModule *pVision) {
    this->pVision = pVision;
//    thread = new std::thread([ = ] {run();});
//    thread->detach();
}

ZSS_THREAD_FUNCTION void CUDAModule::run() {
//    while(true) {
//        vision_to_cuda.wait();
//        ZCUDAModule::instance()->calculateBestPass();
//    }
}

CGeoPoint CUDAModule::getBestFlatPass(){
    return bestFlatPass;
}

CGeoPoint CUDAModule::getBestChipPass(){
    return bestChipPass;
}
int CUDAModule::getBestFlatPassNum(){
    return bestFlatPassNum;
}
int CUDAModule::getBestChipPassNum(){
    return bestChipPassNum;
}

void CUDAModule::calculateBestPass() {
    static rType result[12 * 16 * 128 * 2];
    CGeoPoint ballPos = pVision->OurPlayer(leader+1).Pos();
    passPoints.clear();
    chipPoints.clear();

    for(int i = 0; i < Param::Field::MAX_PLAYER_NUM; i++) {
        players[i].Pos.x = this->pVision->OurPlayer(i + 1).Pos().x();
        players[i].Pos.y = this->pVision->OurPlayer(i + 1).Pos().y();
        players[i].Vel.x = this->pVision->OurPlayer(i + 1).VelX();
        players[i].Vel.y = this->pVision->OurPlayer(i + 1).VelY();
        players[i].isValid = this->pVision->OurPlayer(i + 1).Valid();
        //判断禁区和后卫
        if(players[i].isValid && Utils::InOurPenaltyArea(CGeoPoint(players[i].Pos.x, players[i].Pos.y), 20))
            players[i].isValid = false;

    }
    for(int i = 0; i < Param::Field::MAX_PLAYER_NUM; i++) {
        players[i + Param::Field::MAX_PLAYER_NUM].Pos.x = this->pVision->TheirPlayer(i + 1).Pos().x();
        players[i + Param::Field::MAX_PLAYER_NUM].Pos.y = this->pVision->TheirPlayer(i + 1).Pos().y();
        players[i + Param::Field::MAX_PLAYER_NUM].Vel.x = this->pVision->TheirPlayer(i + 1).VelX();
        players[i + Param::Field::MAX_PLAYER_NUM].Vel.y = this->pVision->TheirPlayer(i + 1).VelY();
        players[i + Param::Field::MAX_PLAYER_NUM].isValid = this->pVision->TheirPlayer(i + 1).Valid();
        //判断禁区和后卫
        if(players[i + Param::Field::MAX_PLAYER_NUM].isValid && Utils::InTheirPenaltyArea(CGeoPoint(players[i + Param::Field::MAX_PLAYER_NUM].Pos.x, players[i + Param::Field::MAX_PLAYER_NUM].Pos.y), 0))
            players[i + Param::Field::MAX_PLAYER_NUM].isValid = false;

    }
    players[leader].isValid = false;
    int goalie = PlayInterface::Instance()->getNumbByRealIndex(TaskMediator::Instance()->goalie());
    players[goalie-1].isValid = false;

    ball->x = pVision->OurPlayer(leader+1).Pos().x();
    ball->y = pVision->OurPlayer(leader+1).Pos().y();

    BestPass(players, ball, result);

    double max_q = -99999;
    double max_q_x, max_q_y;
    double max_q_Chip = -99999;
    double max_q_x_Chip, max_q_y_Chip;
    max_q_x = max_q_y = 9999;
    max_q_x_Chip = max_q_y_Chip = 9999;

    double bestDefDist = 0;
    double bestVel = 0;
    double bestShootAngle = 0;
    double bestDist = 0;
    double bestRefracAngle = 0;
    for(int i = 0; i < 12 * 16 * 128; i++) {
        if(result[i].interTime < 10 && result[i].interTime > 0) {
            CGeoPoint p0(result[i].interPos.x, result[i].interPos.y), p1(600, -60), p2(600, 60);
            if(!isValidPassLine(p0, ballPos)) continue;
            passPoints.push_back(result[i]);
            CVector v1 = p1 - p0,
                    v2 = p2 - p0;
            // 計算有效射門角度 from world model@canShootOnBallPos
            double shootAngle = 0;
            bool _canshootonballpos = false;
            CShootRangeList shootRangeList(pVision, 1, p0);
            const CValueRangeList& shootRange = shootRangeList.getShootRange();
            if (shootRange.size() > 0) {
                auto bestRange = shootRange.getMaxRangeWidth();
                if(bestRange)
                    shootAngle = bestRange->getWidth();
                if (bestRange && bestRange->getWidth() > Param::Field::BALL_SIZE + 5) {	// 要求射门空档足够大
                    _canshootonballpos = true;
                }
            }

            double dist = p0.dist(p1.midPoint(p2));
            v1 = ballPos - p0;
            v2 = p1.midPoint(p2) - p0;
            double refracAngle = fabs(Utils::Normalize(v1.dir() - v2.dir()));
            double defDist = fabs(p0.dist(CGeoPoint(300, 0)) - 150);
            result[i].Q = wDefenDist * defDist +  wVel * result[i].Vel + wShootAngle * shootAngle / PI + wDist * dist / 300 + wRefracAngle * refracAngle / PI;

            if (result[i].Q > max_q) {
                max_q = result[i].Q;
                max_q_x = result[i].interPos.x;
                max_q_y = result[i].interPos.y;
                bestFlatPassNum = result[i].playerIndex;
                bestFlatPassVel = result[i].Vel;
                //DEBUG INFO
                bestDefDist = wDefenDist * defDist;
                bestVel = wVel * result[i].Vel;
                bestShootAngle = wShootAngle * shootAngle / PI;
                bestDist = wDist * dist / 300;
                bestRefracAngle = wRefracAngle * refracAngle / PI;
            }
        }
    }
//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(max_q_x, max_q_y), QString("%1 %2 %3 %4 %5").arg(bestDefDist).arg(bestVel).arg(bestShootAngle).arg(bestDist).arg(bestRefracAngle).toLatin1(), COLOR_CYAN);
    for(int i = 12 * 16 * 128; i < 12 * 16 * 128 * 2; i++) {
        if(result[i].interTime < 10 && result[i].interTime > 0) {
            CGeoPoint p0(result[i].interPos.x, result[i].interPos.y), p1(600, -60), p2(600, 60);
            chipPoints.push_back(result[i]);
            CVector v1 = p1 - p0,
                    v2 = p2 - p0;
            // 計算有效射門角度 from world model@canShootOnBallPos
            double shootAngle = 0;
            bool _canshootonballpos = false;
            CShootRangeList shootRangeList(pVision, 1, p0);
            const CValueRangeList& shootRange = shootRangeList.getShootRange();
            if (shootRange.size() > 0) {
                auto bestRange = shootRange.getMaxRangeWidth();
                if(bestRange){
                    shootAngle = bestRange->getWidth();
                    if (bestRange->getWidth() > Param::Field::BALL_SIZE + 5) {	// 要求射门空档足够大
                        _canshootonballpos = true;
                    }
                }
            }

            double dist = p0.dist(p1.midPoint(p2));
            v1 = ballPos - p0;
            v2 = p1.midPoint(p2) - p0;
            double refracAngle = fabs(Utils::Normalize(v1.dir() - v2.dir()));
            double defDist = fabs(p0.dist(CGeoPoint(300, 0)) - 150);
            result[i].Q = wDefenDist * defDist +  wVel * result[i].Vel + wShootAngle * shootAngle / PI + wDist * dist / 300 + wRefracAngle * refracAngle / PI;

            if (result[i].Q > max_q_Chip) {
                max_q_Chip = result[i].Q;
                max_q_x_Chip = result[i].interPos.x;
                max_q_y_Chip = result[i].interPos.y;
                bestChipPassNum = result[i].playerIndex;
                bestChipPassVel = result[i].Vel;
                //DEBUG INFO
                bestDefDist = wDefenDist * defDist;
                bestVel = wVel * result[i].Vel;
                bestShootAngle = wShootAngle * shootAngle / PI;
                bestDist = wDist * dist / 300;
                bestRefracAngle = wRefracAngle * refracAngle / PI;
            }
        }
    }
//    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(max_q_x, max_q_y), QString("%1 %2 %3 %4 %5").arg(bestDefDist).arg(bestVel).arg(bestShootAngle).arg(bestDist).arg(bestRefracAngle).toLatin1(), COLOR_ORANGE);

    bestFlatPass = CGeoPoint(max_q_x, max_q_y);
    bestChipPass = CGeoPoint(max_q_x_Chip, max_q_y_Chip);
    if (show_pass_lines){
        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(max_q_x, max_q_y), COLOR_GREEN);
        GDebugEngine::Instance()->gui_debug_line(this->pVision->Ball().Pos(), CGeoPoint(max_q_x, max_q_y), COLOR_GREEN);
        GDebugEngine::Instance()->gui_debug_line(CGeoPoint(max_q_x, max_q_y),CGeoPoint(600, 0), COLOR_GREEN);

        GDebugEngine::Instance()->gui_debug_x(CGeoPoint(max_q_x_Chip, max_q_y_Chip), COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_line(this->pVision->Ball().Pos(), CGeoPoint(max_q_x_Chip, max_q_y_Chip), COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_line(CGeoPoint(max_q_x_Chip, max_q_y_Chip),CGeoPoint(600, 0), COLOR_YELLOW);
    }
    if (show_pass_points){
//        for(int i = 0; i < passPoints.size(); i += 4) {
//            GDebugEngine::Instance()->gui_debug_x(CGeoPoint(passPoints[i].interPos.x, passPoints[i].interPos.y), COLOR_CYAN);
//        }

//        for(int i = 0; i < chipPoints.size(); i += 4) {
//            GDebugEngine::Instance()->gui_debug_x(CGeoPoint(chipPoints[i].interPos.x, chipPoints[i].interPos.y), COLOR_ORANGE);
//        }
        std::vector<CGeoPoint> points;
        for(int i = 0; i < passPoints.size(); i += 5) {
            points.push_back(CGeoPoint(passPoints[i].interPos.x, passPoints[i].interPos.y));
        }
        GDebugEngine::Instance()->gui_debug_points(points, COLOR_CYAN);
        points.clear();
        for(int i = 0; i < chipPoints.size(); i += 5){
            points.push_back(CGeoPoint(chipPoints[i].interPos.x, chipPoints[i].interPos.y));
        }
        GDebugEngine::Instance()->gui_debug_points(points, COLOR_ORANGE);
    }
}

bool CUDAModule::isValidPassLine(const CGeoPoint& p1, const CGeoPoint& p2) {
    double x1 = p1.x(),
            x2 = p2.x(),
            y1 = p1.y(),
            y2 = p2.y();
    double k, interX, interY, result, x0, y0;
    result = -9999;
    for(int i = 0; i < Param::Field::MAX_PLAYER_NUM; i++) {
        if(!pVision->TheirPlayer(i + 1).Valid())
            continue;

        CGeoPoint targetPoint = pVision->TheirPlayer(i + 1).Pos();
        x0 = targetPoint.x();
        y0 = targetPoint.y();
        if(fabs(x2 - x1) > 0.1) {
            k = (y2 - y1) / (x2 - x1);
            interX = (x0 + k * k * x1 + k * (y0 - y1)) / (1 + k * k);
            interY = k * (interX - x1) + y1;
        }
        else {
            interX = x1;
            interY = y0;
        }
        CGeoPoint interPoint(interX, interY);
        CVector direc1 = interPoint - p1,
                direc2 = interPoint - p2;
        if(direc1 * direc2 > 0) {
            CVector current2Start = p1 - targetPoint,
                    current2End = p2 - targetPoint;
            double d1 = current2Start.mod(),
                    d2 = current2End.mod();
            result = d1 > d2 ? d2 : d1;
        }
        else {
            CVector current2InterPoint = interPoint - targetPoint;
            result = current2InterPoint.mod();
        }
        if(result < THEIR_ROBOT_INTER_THREADHOLD) {
            return false;
        }
    }
    return true;
}

#endif // USE_CUDA_MODULE