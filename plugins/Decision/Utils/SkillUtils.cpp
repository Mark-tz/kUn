#include "SkillUtils.h"
#include "parammanager.h"
#include "GDebugEngine.h"
#include "param.h"
#include <cmath>
#include "GoImmortalRush.h"
namespace{
    bool DEBUG = false;
    double TIME_FOR_OUR = 0;
    double TIME_FOR_OUR_BOTH_KEEP = -0.2;
    double TIME_FOR_THEIR_BOTH_KEEP = -0.4;
    double TIME_FOR_THEIR = -0.6;
    double TIME_FOR_JUDGE_HOLDING = 0.5;
}
SkillUtils::SkillUtils(){
    bool isSimulation;
    ZSS::ZParamManager::instance()->loadParam(isSimulation,"Alert/IsSimulation",false);
    if(isSimulation)
        ZSS::ZParamManager::instance()->loadParam(FRICTION,"AlertParam/Friction4Sim",152.0);
    else
        ZSS::ZParamManager::instance()->loadParam(FRICTION,"AlertParam/Friction4Real",80.0);
    ZSS::ZParamManager::instance()->loadParam(DEBUG,"Debug/InterTimeDisplay",false);
}
SkillUtils::~SkillUtils(){
}

bool SkillUtils::predictedInterTime(const CVisionModule* pVision, int robotNum, CGeoPoint& interceptPoint, double& interTime, double responseTime) {
    const MobileVisionT ball = pVision->Ball();//获得球
    const PlayerVisionT me = pVision->OurPlayer(robotNum);//获得车
    if (!me.Valid()) {//车不存在
        interTime = 99999;
        interceptPoint = CGeoPoint(999, 999);
        return false;
    }
    if(ball.Vel().mod() < 40){
        interceptPoint = ball.Pos();//截球点
        interTime = predictedTime(me, interceptPoint);//截球时间
        return true;
    }
    double ballAcc = FRICTION / 2;//球减速度
    double ballArriveTime = 0;
    double meArriveTime = 9999;
    int testMinFrame = 1;//最少帧数
    double testBallLength = 0;//球移动距离
    CGeoPoint testPoint = ball.Pos();
    double testVel = ball.Vel().mod();
    double max_time = ball.Vel().mod() / ballAcc;
    CGeoLine ballLine(ball.Pos(), ball.Vel().dir());
    CGeoPoint ballLineProjection = ballLine.projection(me.Pos());
    CVector projection2me = me.Pos() - ballLineProjection;
    double me2projectionTime = predictedTime(me, ballLineProjection);

    double width = projection2me.mod() < Param::Vehicle::V2::PLAYER_SIZE ? projection2me.mod() : Param::Vehicle::V2::PLAYER_SIZE;
    //cout <<"width:"<<width<<"\tme2projectionTime:"<<me2projectionTime<<endl;
    for (ballArriveTime = 0; ballArriveTime < max_time; ballArriveTime += testMinFrame * 1.0 / 60.0 ) {
        testVel = ball.Vel().mod() - ballAcc*ballArriveTime;//v_0-at
        testBallLength = Param::Vehicle::V2::PLAYER_CENTER_TO_BALL_CENTER + (ball.Vel().mod() + testVel)*ballArriveTime / 2;//梯形法计算球移动距离
        testPoint = ball.Pos() + Utils::Polar2Vector(testBallLength, ball.Vel().dir());
        meArriveTime = predictedTime(me, testPoint + Utils::Polar2Vector(width, projection2me.dir()));//我到截球点的时间
        if(meArriveTime < 0.15) meArriveTime = 0;
        //meArriveTime = predictedTime(me, testPoint);
        //cout <<"meArriveTime!!!!!!!!!!!!!!!!"<<meArriveTime<<endl;
        //cout << "testPoint:"<<testPoint<<"\tmeArriveTime"<<meArriveTime<<"\tballArriveTime"<<ballArriveTime<<endl;
        if (!IsInField(testPoint) || (meArriveTime + responseTime) < ballArriveTime) {
            break;
        }
    }
    interceptPoint = testPoint;//截球点
    interTime = predictedTime(me, interceptPoint);//截球时间
//    cout << interTime <<endl;
    /*
    if(me2projectionTime > interTime && me2projectionTime - interTime < 0.2){//到垂足更近，且比球先到
        interceptPoint = ballLineProjection;
        interTime = me2projectionTime;
    }
    */
    //cout << " ballArriveTime:"<<ballArriveTime<<" meArriveTime:"<<meArriveTime<<" interTime" <<interTime<< endl;
    return true;
}

bool SkillUtils::predictedTheirInterTime(const CVisionModule* pVision, int robotNum, CGeoPoint& interceptPoint, double& interTime, double responseTime) {
    const MobileVisionT ball = pVision->Ball();//获得球
    const PlayerVisionT me = pVision->TheirPlayer(robotNum);//获得车
    if (!me.Valid()) {//车不存在
        interTime = 99999;
        interceptPoint = CGeoPoint(999, 999);
        return false;
    }
    //double maxArriveTime = 5;//车最多移动时间
    double ballAcc = FRICTION / 2;//球减速度
    double ballArriveTime = 0;
    double meArriveTime = 9999;
    int testMinFrame = 5;//最少帧数
    double testBallLength = 0;//球移动距离
    CGeoPoint testPoint = ball.RawPos();
    double testVel = ball.Vel().mod();
    double max_time = ball.Vel().mod() / ballAcc;
    for (ballArriveTime = 0; ballArriveTime < max_time; ballArriveTime += testMinFrame * 1.0 / 60.0 ) {
        testVel = ball.Vel().mod() - ballAcc*ballArriveTime;//v_0-at
        testBallLength = (ball.Vel().mod() + testVel)*ballArriveTime / 2;//梯形法计算球移动距离
        testPoint = ball.RawPos() + Utils::Polar2Vector(testBallLength, ball.Vel().dir());
        meArriveTime = predictedTheirTime(me, testPoint);//我到截球点的时间
        if (!IsInField(testPoint) || (meArriveTime + responseTime) < ballArriveTime) {
            break;
        }
    }
    interceptPoint = testPoint;//截球点
    interTime = predictedTheirTime(me, interceptPoint);//截球时间
    return true;
}

CGeoPoint SkillUtils::predictedTheirInterPoint(CGeoPoint enemy, CGeoPoint ball) {
    double ballAcc = FRICTION;//球减速度
    double carAcc = 400;
    double maxBallSpeed = 650;
    double dist = (enemy - ball).mod();
    double delta = maxBallSpeed*maxBallSpeed + 2 * (carAcc - ballAcc)*dist;
    double t = (std::sqrt(delta) - maxBallSpeed)/(carAcc - ballAcc);
    double enemy2point = 0.5 * carAcc * t * t;
    return enemy + Utils::Polar2Vector(enemy2point, (ball - enemy).dir());
}

bool SkillUtils::IsInField(const CGeoPoint p, double buffer){
    return (p.x() > buffer - Param::Field::PITCH_LENGTH / 2 && p.x() < Param::Field::PITCH_LENGTH / 2 - buffer &&
        p.y() > buffer - Param::Field::PITCH_WIDTH / 2 && p.y() < Param::Field::PITCH_WIDTH / 2 - buffer);
}

bool SkillUtils::IsInFieldV2(const CGeoPoint p, double buffer) {
    return (IsInField(p, buffer) && !Utils::InOurPenaltyArea(p, buffer) && !Utils::InTheirPenaltyArea(p, buffer));
}

bool SkillUtils::IsBallReachable(double ballVel, double length, double friction) {
    double max_dist = ballVel * ballVel / (2 * friction);
    if (length < max_dist) return true;
    else return false;
}

void SkillUtils::generateInterInformation(const CVisionModule* pVision){
    for(int robotNum = 1; robotNum<= Param::Field::MAX_PLAYER_NUM; robotNum++){
        predictedInterTime(pVision, robotNum, ourInterPoint[robotNum], ourInterTime[robotNum], 0);
        predictedTheirInterTime(pVision, robotNum, theirInterPoint[robotNum], theirInterTime[robotNum], 0);
    }
    return;
}

double SkillUtils::getOurInterTime(int num){
    return ourInterTime[num];
}

double SkillUtils::getTheirInterTime(int num){
    return theirInterTime[num];
}

CGeoPoint SkillUtils::getOurInterPoint(int num){
    return ourInterPoint[num];
}

CGeoPoint SkillUtils::getTheirInterPoint(int num){
    return theirInterPoint[num];
}

bool SkillUtils::isSafeShoot(const CVisionModule* pVision, double ballVel, CGeoPoint target){
    const MobileVisionT ball = pVision->Ball();//获得球
    const CGeoPoint ballPos = ball.RawPos();
    const CVector ball2target = target - ballPos;
    double ballAcc = FRICTION;//球减速度
    int testMinFrame = 5;//最少帧数

    for(int robotNum = 1; robotNum <= Param::Field::MAX_PLAYER_NUM; robotNum++){
        PlayerVisionT me = pVision->TheirPlayer(robotNum);//获得车
        if (!me.Valid()) {//车不存在
            continue;//无车，查看下一辆
        }
        double ballArriveTime = 0;
        double meArriveTime = 9999;
        double testBallLength = 0;//球移动距离
        CGeoPoint testPoint(ballPos.x(), ballPos.y());
        double testVel = ballVel;
        while (true) {
            ballArriveTime += testMinFrame * 1.0 / 60.0;//每隔5帧计算一次
            testVel = ballVel - ballAcc*ballArriveTime;//v_0-at
            if (testVel < 0) testVel = 0;//球已静止
            testBallLength = (ballVel + testVel)*ballArriveTime / 2;//梯形法计算球移动距离
            testPoint.setX(ballPos.x() + testBallLength * std::cos(ball2target.dir()));//截球点坐标
            testPoint.setY(ballPos.y() + testBallLength * std::sin(ball2target.dir()));
            meArriveTime = predictedTime(me, testPoint);//对方车到截球点的时间
            if (!IsInField(testPoint)) {
                break;//该车无法在场内截球，跳出循环
            }
            if (meArriveTime < ballArriveTime) {//该车可在场内截球
                if(testBallLength < ball2target.mod())
                    return false;//能在球线上截到球
                else break;//不能在球线上截到球，跳出循环
            }
        }
    }
    return true;//for循环中所有车都不能截球，没有return false
}

void SkillUtils::generatePredictInformation(const CVisionModule* pVision){
    CGeoPoint ball = pVision->Ball().RawPos();//获得球
    double ballAcc = FRICTION;//球减速度
    double carAcc = 500;
    double maxBallSpeed = 650;
    for(int enemyNum = 1; enemyNum< Param::Field::MAX_PLAYER_NUM +1; enemyNum++){
        PlayerVisionT enemy = pVision->TheirPlayer(enemyNum);//获得车
        if (!enemy.Valid()) {//车不存在
            predictTheirInterTime[enemyNum] = 99999;
            predictTheirInterPoint[enemyNum] = CGeoPoint(999, 999);
            continue;
        }
        CGeoPoint enemyPoint = enemy.Pos();
        double dist = (enemyPoint - ball).mod();
        double delta = maxBallSpeed*maxBallSpeed + 2 * (carAcc - ballAcc)*dist;
        double t = (std::sqrt(delta) - maxBallSpeed)/(carAcc - ballAcc);
        double enemy2point = 0.5 * carAcc * t * t;
        predictTheirInterTime[enemyNum] = t;
        predictTheirInterPoint[enemyNum] = enemyPoint + Utils::Polar2Vector(enemy2point, (ball - enemyPoint).dir());
    }
}

double SkillUtils::getPredictTime(int num){
    return predictTheirInterTime[num];
}

CGeoPoint SkillUtils::getPredictPoint(int num){
    return predictTheirInterPoint[num];
}

void SkillUtils::run(const CVisionModule* pVision){
    _lastCycle = pVision->Cycle();
    ourBestInterRobot = theirBestInterRobot = 1;
    generateInterInformation(pVision);
    generatePredictInformation(pVision);

    calculateBallBelongs();
    if(DEBUG){
        for(int i=1;i<=Param::Field::MAX_PLAYER_NUM;i++){
            GDebugEngine::Instance()->gui_debug_x(theirInterPoint[i]);
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200,-300 + i*30),QString("%1 %2").arg(i).arg(theirInterTime[i]).toLatin1());
            GDebugEngine::Instance()->gui_debug_x(ourInterPoint[i],COLOR_WHITE);
            GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-200,-300 + i*30),QString("%1 %2").arg(i).arg(ourInterTime[i]).toLatin1(),COLOR_WHITE);
        }
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-200,200),QString("OurBest : %1").arg(ourBestInterRobot).toLatin1(),COLOR_WHITE);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(200,200),QString("TheirBest : %1").arg(theirBestInterRobot).toLatin1());
    }
    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0,-Param::Field::PITCH_WIDTH/2-5),ZBallState::toStr[ballState].c_str(),COLOR_CYAN);
}
void SkillUtils::calculateBallBelongs(){
    for(int i=1;i<=Param::Field::MAX_PLAYER;i++){
        if(ourInterTime[i] < ourInterTime[ourBestInterRobot])
            ourBestInterRobot = i;
        if(theirInterTime[i] < theirInterTime[theirBestInterRobot])
            theirBestInterRobot = i;
    }
    double ourTimeAdvantage = (theirInterTime[theirBestInterRobot] - ourInterTime[ourBestInterRobot]);
    bool our = ourTimeAdvantage > TIME_FOR_OUR;
    bool their = ourTimeAdvantage < TIME_FOR_THEIR;
    bool ourKeep = !our && ourTimeAdvantage > TIME_FOR_OUR_BOTH_KEEP;
    bool theirKeep = !their && ourTimeAdvantage < TIME_FOR_THEIR_BOTH_KEEP;
    //cout << "Time : ourTimeAdvantage : " << ourTimeAdvantage << endl;
    if(our)
        ballState = ZBallState::Our;
    else if(their)
        ballState = ZBallState::Their;
    else if(ourKeep)
        ballState = (ballState == ZBallState::Our ? ZBallState::Our : ZBallState::Both);
    else if(theirKeep)
        ballState = (ballState == ZBallState::Their ? ZBallState::Their : ZBallState::Both);
    else
        ballState = ZBallState::Both;

    if(ballState == ZBallState::Our && ourInterTime[ourBestInterRobot] < TIME_FOR_JUDGE_HOLDING)
        ballState = ZBallState::OurHolding;
    if(ballState == ZBallState::Their && theirInterTime[theirBestInterRobot] < TIME_FOR_JUDGE_HOLDING)
        ballState = ZBallState::TheirHolding;
    if(ballState == ZBallState::Both && (ourInterTime[ourBestInterRobot] < TIME_FOR_JUDGE_HOLDING || theirInterTime[theirBestInterRobot] < TIME_FOR_JUDGE_HOLDING))
        ballState = ZBallState::BothHolding;


    GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(150,-Param::Field::PITCH_WIDTH/2-5),QString("OurBest %1 TheirBest %2").arg(ourBestInterRobot-1).arg(theirBestInterRobot-1).toLatin1());
//    if(bothHolding)
//        ballState = ZBallState::BothHolding;
//    else if(ourHolding)
//        ballState = ZBallState::OurHolding;
//    else if(theirHolding)
//        ballState = ZBallState::TheirHolding;

}

double SkillUtils::getOurBestInterTime(){
    return getOurInterTime(ourBestInterRobot);
}

double SkillUtils::getTheirBestInterTime(){
    return getTheirInterTime(theirBestInterRobot);
}

int SkillUtils::getOurBestPlayer(){
    return ourBestInterRobot;
}

int SkillUtils::getTheirBestPlayer(){
    return theirBestInterRobot;
}

// CANNOT USE!!!!!!!
// CANNOT USE!!!!!!!
// CANNOT USE!!!!!!!
double SkillUtils::getImmortalRushTime(const CVisionModule *pVision, int robotNum, CGeoPoint targetPos, double targetDir) {
    PlayerVisionT me = pVision->OurPlayer(robotNum);
    int mode = 0;
    if ((me.Pos() - targetPos).mod() < 15) { //almost arrived
        mode = 3;
    }
    else if ((me.Pos() - targetPos).mod() > 20 && Utils::Normalize(me.Dir() - (me.Pos() - targetPos).dir()) > 0.5) {
        mode = 1;
    }
    else {
        mode = 2;
    }
    return calcImmortalTime(pVision, robotNum, targetPos, targetDir, mode);
}


CGeoPoint SkillUtils::getMarkingPoint (CGeoPoint markingPos, CVector markingVel, double aMax, double dMax, double aRotateMax, double vMax,CGeoPoint protectPos) {
    if(markingVel.mod() == 0) {
        CVector defDirec = protectPos - markingPos;
        CGeoPoint runPoint = markingPos + defDirec * 0.3;
        return runPoint;
    }
    CVector adjustDirec = protectPos - markingPos;
    CVector D2T_Direc = adjustDirec / adjustDirec.mod();

    double safetyDistL, safetyDistS;
//    if(markingVel * D2T_Direc > 0) {
//        safetyDistL = Param::Vehicle::V2::PLAYER_SIZE * (markingVel * D2T_Direc / vMax * 8); //前向安全距离
//        safetyDistS = Param::Vehicle::V2::PLAYER_SIZE * (markingVel * D2T_Direc / vMax * 8); //侧向安全距离
//    }
//    else {
        safetyDistL = safetyDistS = Param::Vehicle::V2::PLAYER_SIZE * 4;
//    }

    double stopDist = markingVel.mod2() / (2 * dMax);
    double stopTime = markingVel.mod() / dMax;
    double vM = markingVel.mod() + aMax * stopTime;
    double accDist;
    if(vM < vMax) {
        accDist = markingVel.mod() * stopTime + 0.5 * aMax * pow(stopTime, 2);
    }
    else
        accDist = (vMax * vMax - markingVel.mod2()) /(2 * aMax) + vMax * (stopTime - (vMax - vM) / aMax);

    CVector velDirec = markingVel / markingVel.mod();
    CVector direc1(velDirec.y(), -velDirec.x());
    CVector direc2 = -direc1;
    double R = markingVel.mod2() / aRotateMax;
    double theta1 = markingVel.mod() * stopTime / R;

    CVector direcToTarget = protectPos - markingPos;
    CGeoPoint stopPoint = markingPos + velDirec * stopDist;
    CGeoPoint appPoint = stopPoint + direcToTarget * 0.3;
    CGeoPoint accPoint = markingPos + velDirec * accDist;
    CGeoPoint leftPoint = markingPos + direc1 * R * (1 - cos(theta1)) + velDirec * R * sin(theta1);
    CGeoPoint rightPoint = markingPos + direc2 * R * (1 - cos(theta1)) + velDirec * R * sin(theta1);

    CGeoPoint runPoint;
    if(appPoint.dist(protectPos) < leftPoint.dist(protectPos)) {
        runPoint = appPoint.dist(protectPos) < rightPoint.dist(protectPos) ? stopPoint : rightPoint;
    }
    else {
        runPoint = leftPoint.dist(protectPos) < rightPoint.dist(protectPos) ? leftPoint : rightPoint;
    }
//根据不同的跑位点情况对跑位点进行安全距离修正；
    if(runPoint == stopPoint && runPoint.dist(markingPos) < safetyDistL)
        runPoint = runPoint + adjustDirec / adjustDirec.mod() * safetyDistL;
    else if(runPoint.dist(markingPos) < safetyDistS)
        runPoint = runPoint + adjustDirec / adjustDirec.mod() * safetyDistS;

    //处理被防守车往反方向运动的情况
    direc1 = runPoint - markingPos;
    direc2 = protectPos - markingPos;
    if(direc1 * direc2 / (direc1.mod() * direc2.mod()) < 0) {
        if(direc2.mod() > Param::Vehicle::V2::PLAYER_SIZE * 4)
            runPoint = markingPos + direc2 / direc2.mod() * Param::Vehicle::V2::PLAYER_SIZE * 16;
        else
            runPoint = markingPos + direc2 * 0.5;
    }

    return runPoint;
}

