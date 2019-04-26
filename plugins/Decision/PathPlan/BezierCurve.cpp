#include "BezierCurve.h"
#include "GDebugEngine.h"
#include <fstream>

namespace{
    const int maxAdjustTimes = 15;
    const double adjustRateInitial = 1.3;
    const double adjustStep = 0.15;

    const double radiusOfRobot = Param::Vehicle::V2::PLAYER_SIZE / 2;

    const double thresholdToAddControlPoint = 10;
    const double zeroVelocityRate = 0.05; //不能太小，否则防抖效果会很差，容易规划失败
    const double sameLine = 0.01;

    ofstream carStates( "D://zjunlict//JSH220//States.txt" );
    const double FRAME_PERIOD = 1.0 / Param::Vision::FRAME_RATE;
}

inline double BezierCurver::combinationNumber(int n, int i) {
    if(i == n) return 1;
    double numerator = 1,denominator = 1;
    for(int k = 0; k < i; k++) {
        denominator *= k + 1;
        numerator *= n - k;
    }
    return numerator / denominator;
}

inline int BezierCurver::indexFirstCtrlPointCanBeAdjusted() {
    return zeroStartVel ? 1 : 2;
}

inline int BezierCurver::indexLastCtrlPointCanBeAdjusted() {
    return zeroTargetVel ? (bezierControlList.size() - 1) : (bezierControlList.size() - 2);
}


void BezierCurver::initControlList(const stateNew& start, const stateNew& target, const double vMax, vector<CGeoPoint> initialControlList, int curvePointNumber, ObstaclesNew obstacle, bool StartVelControlPoint) {

    this->bezierPathList.clear();
    this->bezierStateList.clear();
    this->combinationNumberList.clear();
    this->attemptControlList.clear();

    this->adjustCounter = 0;
    this->curvePointNumber = curvePointNumber;
    this->adjustRate = adjustRateInitial;
    this->lastOffDist = 0;
    this->start = start;
    this->target = target;
    this->obstacle = obstacle;
    this->arrivedNumber = 0;
    this->NCombinationNumber = 0;
    this->bezierControlList = initialControlList;

    double lengthPart = start.pos.dist(target.pos) / curvePointNumber;

    if(StartVelControlPoint)
        addStartVelCtrlPoint(vMax, lengthPart);
    addTargetVelCtrlPoint(vMax, lengthPart);
}

void BezierCurver::addStartVelCtrlPoint(double vMax, double lengthPart) {
    double adjustAngle, velocityRate, lengthenPower;
    CGeoPoint addedControlPointToStart;
    CVector direcBegin2Second, direcEnd, direcBegin2End, addedVector, direcFirstNew;

    direcBegin2End = target.pos - start.pos;
    direcBegin2Second = bezierControlList[1] - start.pos;
    direcEnd = bezierControlList[bezierControlList.size() - 2] - target.pos;

    velocityRate = start.vel.mod() / vMax;
    if(start.vel.mod() < vMax * zeroVelocityRate ) { //初速度为0，则按照开始的控制点生成方案
        zeroStartVel = true;
        direcFirstNew = direcBegin2Second;
        adjustAngle = direcBegin2Second.dir() - direcBegin2End.dir();
        if(adjustAngle > sameLine)
            direcFirstNew = direcBegin2Second.rotate(adjustAngle);
        direcFirstNew = direcFirstNew / direcFirstNew.mod() * lengthPart * 4;
        addedControlPointToStart = start.pos + direcFirstNew;
    }
    else {
        zeroStartVel = false;
        lengthenPower = velocityRate * 10 + 3;
        addedVector = start.vel / start.vel.mod() * lengthPart * lengthenPower;
        addedControlPointToStart = start.pos + addedVector;
    }
    bezierControlList.insert(bezierControlList.begin() + 1, addedControlPointToStart);
}


void BezierCurver::addTargetVelCtrlPoint(double vMax, double lengthPart) {

    double adjustAngle;
    CVector direcEnd2Begin = start.pos - target.pos;
    CVector direcEndNew = bezierControlList[bezierControlList.size() - 2] - target.pos;
    double velocityRate = target.vel.mod() / vMax;
    double lengthenPower;

    if(target.vel.mod() < vMax * zeroVelocityRate) {
        zeroTargetVel = true;
        adjustAngle = direcEndNew.dir() - direcEnd2Begin.dir();
        if(adjustAngle > sameLine)
            direcEndNew = direcEndNew.rotate(adjustAngle);
        direcEndNew = direcEndNew / direcEndNew.mod() * lengthPart * 3.5;
    }
    else {
        zeroTargetVel = false;
        lengthenPower = velocityRate * 20 + 3;
        direcEndNew = -target.vel / target.vel.mod() * lengthPart * lengthenPower;
    }
    CGeoPoint addedControlPointToEnd = target.pos + direcEndNew;
    bezierControlList.insert(bezierControlList.end() - 1, addedControlPointToEnd);
}


void BezierCurver::calculateState(const PlayerCapabilityT &capability, double& timeNeeded, stateNew& nextTarget) {

    int numberOfPathSegment, rotateCounter, maxRotateAdjust, targetVelOffsetNum;
    double* lengthOfPathSegments;
    double longestPathSegment, orientStep, curature, direcOfLastTarget, achievableTimeSegment, angle, totalDistance=0;
    double velOfNextState, velOfFirstTarget, vMax, velDiff;

    double velOfFirstStep, velOfSecondStep; //magic numbers
    CVector direcOfNextTarget, direcOfFirstTarget;
    stateNew tempState;

    numberOfPathSegment = bezierPathList.size() - 1;
    maxRotateAdjust = this->curvePointNumber;
    vMax = capability.maxSpeed;
    rotateCounter = 1;
    orientStep = Utils::Normalize(target.orient - start.orient) / maxRotateAdjust;

    velOfFirstStep = 0.7 * vMax;
    velOfSecondStep = 0.9 * vMax;
    lengthOfPathSegments = new double[numberOfPathSegment];
    arrivedNumber = 0;
    longestPathSegment = 0;

    for(int i = 0; i < numberOfPathSegment; i++) {
        lengthOfPathSegments[i] = bezierPathList[i].dist(bezierPathList[i + 1]);

        totalDistance += lengthOfPathSegments[i];
        if(lengthOfPathSegments[i] > longestPathSegment) {
            longestPathSegment = lengthOfPathSegments[i];
        }
    }
    if(totalDistance > 300) targetVelOffsetNum = 10;
    else if(totalDistance > 150) targetVelOffsetNum = 13;
    else targetVelOffsetNum = 30;
    achievableTimeSegment = longestPathSegment / vMax;

    timeNeeded = achievableTimeSegment * numberOfPathSegment;
    velOfFirstTarget = lengthOfPathSegments[0] / achievableTimeSegment;
    direcOfFirstTarget = bezierPathList[1] - bezierPathList[0];
    direcOfLastTarget = direcOfFirstTarget.dir();

    for(int i = 0; i < numberOfPathSegment - 1; i++) {

        velOfNextState = lengthOfPathSegments[i] / achievableTimeSegment;
        double offset = i + 1 + targetVelOffsetNum - numberOfPathSegment;

        if(offset > 0) { //添加末速度补偿
            velDiff = target.vel.mod() - velOfNextState;
            velOfNextState += velDiff * offset / targetVelOffsetNum;
        }

        direcOfNextTarget = bezierPathList[i + 2] - bezierPathList[i + 1];
        angle = Utils::Normalize(direcOfNextTarget.dir() - direcOfLastTarget);
        curature = fabs(angle) / lengthOfPathSegments[i];
        if(curature > 1/1.2 ) {
            velOfNextState = (velOfNextState > velOfFirstStep) ? velOfFirstStep : velOfNextState;
        }
        else if(curature > 1/2.5 ) {
            velOfNextState = (velOfNextState > velOfSecondStep) ? velOfSecondStep :velOfNextState;
        }

        tempState.vel = Utils::Polar2Vector(velOfNextState, direcOfNextTarget.dir());
        tempState.orient = start.orient + rotateCounter * orientStep;
        tempState.rotVel = 0;
        tempState.pos = bezierPathList[i + 1];
        bezierStateList.push_back(tempState);

        direcOfLastTarget = direcOfNextTarget.dir();
        rotateCounter++;
        if(rotateCounter > maxRotateAdjust) rotateCounter = maxRotateAdjust;
    }
    tempState.pos = bezierPathList[bezierPathList.size() - 1];
    tempState.vel = target.vel;
    tempState.orient = target.orient;
    bezierStateList.push_back(tempState);

    nextTarget.orient = direcOfFirstTarget.dir();
    nextTarget.vel = Utils::Polar2Vector(velOfFirstTarget, nextTarget.orient);
    nextTarget.rotVel = 0;
    nextTarget.pos = bezierPathList[1];

    delete lengthOfPathSegments;
}


int BezierCurver::findNearestPathPoint(const CGeoPoint &myPosition, bool &isArrived) {

    int indexOfNearestPathPoint;
    double nearestDist = 1e8;
    int numberOfPathPoints = bezierPathList.size();
    for(int i = 0; i < numberOfPathPoints; i++) {
        double tempDist = bezierPathList[i].dist(myPosition);
        if(tempDist < nearestDist) {
            nearestDist = tempDist;
            indexOfNearestPathPoint = i;
        }
    }
    CVector nearestPathPoint2Target = target.pos - bezierPathList[indexOfNearestPathPoint];
    CVector nearestPathPoint2Car = myPosition - bezierPathList[indexOfNearestPathPoint];
    nearestPathPoint2Target = nearestPathPoint2Target / nearestPathPoint2Target.mod(); //这两个数的点乘有时候会很大而溢出，导致程序崩溃，必须要化为单位向量
    nearestPathPoint2Car = nearestPathPoint2Car / nearestPathPoint2Car.mod();
    isArrived = (nearestPathPoint2Car * nearestPathPoint2Target >= -0.05);

    return indexOfNearestPathPoint;
}


double BezierCurver::distanceToSegment(const CGeoPoint &segStart, const CGeoPoint &segEnd, const CGeoPoint &targetPoint) {
    double x1 = segStart.x(),
            x2 = segEnd.x(),
            y1 = segStart.y(),
            y2 = segEnd.y(),
            x0 = targetPoint.x(),
            y0 = targetPoint.y();
    double k, interX, interY, result;
    if(x2 != x1) {
        k = (y2 - y1) / (x2 - x1);
        interX = (x0 / k + k * x1 + y0 - y1) / (k + 1 / k);
        interY = k * (interX - x1) + y1;
    }
    else {
        interX = x1;
        interY = y0;
    }
    CGeoPoint interPoint(interX, interY);
    CVector direc1 = interPoint - segStart,
            direc2 = interPoint - segEnd;
    if(direc1 * direc2 > 0) {
        CVector current2Start = segStart - targetPoint,
                current2End = segEnd - targetPoint;
        double d1 = current2Start.mod(),
                d2 = current2End.mod();
        result = d1 > d2 ? d2 : d1;
    }
    else {
        CVector current2InterPoint = interPoint - targetPoint;
        result = current2InterPoint.mod();
    }
    return result;
}


bool BezierCurver::pathIsValid(int &indexOfObs) {
    int numOfPathSeg = bezierPathList.size() - 1;
    int numOfObst = obstacle.obs.size();
    for(int i = 0; i < numOfPathSeg; i++) {
        for(int j = 0; j < numOfObst; j++) {
            CGeoSegment seg(bezierPathList[i], bezierPathList[i + 1]);
            if( !obstacle.obs[j].check(seg, 0.0) ) {
                indexOfObs = j;
                return false;
            }
        }
    }
    return true;
}


int BezierCurver::findNearestControlPointFromObst(const int& indexOfObs) {
    int startIter,endIter;
    CGeoPoint obsMidPoint;
    CVector start2Target, start2CP, start2Obs;
    double projectionOfObs, projectionOfCP, tempDist, indexOfNearestControlPointCanBeAdjust, nearestDistance;

    nearestDistance = 1e8;
    startIter = indexFirstCtrlPointCanBeAdjusted();
    endIter = indexLastCtrlPointCanBeAdjusted();

    obsMidPoint = obstacle.obs[indexOfObs].getEnd().midPoint(obstacle.obs[indexOfObs].getStart());
    start2Target = (target.pos - start.pos) / 100;
    start2Obs = (obsMidPoint - start.pos) / 10;
    projectionOfObs = start2Target * start2Obs;

    for(int k = startIter; k < endIter; k++) {
        start2CP = (bezierControlList[k] - start.pos) / 10;
        projectionOfCP = start2CP * start2Target;
        tempDist = fabs(projectionOfCP - projectionOfObs);

        if(tempDist < nearestDistance){
            nearestDistance = tempDist;
            indexOfNearestControlPointCanBeAdjust = k;
         }
    }

    return indexOfNearestControlPointCanBeAdjust;
}


void BezierCurver::adjust(const int &indexOfObs, bool reverse, bool isAttempt) {

    vector<CGeoPoint>& ControlLists = isAttempt ? attemptControlList : bezierControlList;
    CVector  firstToObst, secondToObst, adjustVector;
    double indexOfNearestControlPointCanBeAdjust, indexOfPath;
    bool arrived;
    CGeoPoint obsMidPoint = obstacle.obs[indexOfObs].getEnd().midPoint(obstacle.obs[indexOfObs].getStart());

    indexOfNearestControlPointCanBeAdjust = findNearestControlPointFromObst(indexOfObs);
    indexOfPath = findNearestPathPoint(obsMidPoint, arrived);
    if(!arrived && indexOfPath > 0) indexOfPath--;
    if(reverse) {
        double A, B, C;
        A = target.pos.y() - start.pos.y();
        B = start.pos.x() - target.pos.x();
        C = target.pos.x() * start.pos.y() - start.pos.x() * target.pos.y();

        bezierControlList[indexOfNearestControlPointCanBeAdjust] = symmetricPoint(A, B, C, bezierControlList[indexOfNearestControlPointCanBeAdjust]);

    }
    firstToObst = bezierPathList[indexOfPath] - obsMidPoint;
    secondToObst = bezierPathList[indexOfPath + 1] - obsMidPoint;

    adjustVector =  firstToObst / firstToObst.mod() + secondToObst / secondToObst.mod();
    adjustVector = adjustVector / adjustVector.mod();

    ControlLists[indexOfNearestControlPointCanBeAdjust] = ControlLists[indexOfNearestControlPointCanBeAdjust] + adjustVector * radiusOfRobot * adjustRate;
}


void BezierCurver::curveOnly(bool isAttempt) {
    const vector<CGeoPoint>& ControlLists = isAttempt ? attemptControlList : bezierControlList;
    int numberOfControlPoint = ControlLists.size();

    if(NCombinationNumber != numberOfControlPoint - 1) {
        combinationNumberList.reserve(numberOfControlPoint);
        for(int i = 0; i < numberOfControlPoint; i++) {
            combinationNumberList[i] = combinationNumber(numberOfControlPoint - 1, i);
        }
        NCombinationNumber = numberOfControlPoint - 1;
    }

    bezierPathList.clear();
    bezierPathList.push_back(ControlLists[0]);
    for(int i = 1; i < curvePointNumber - 1; i++) {
        double u = i * 1.0 / (curvePointNumber - 1), eu = 1 - u;
        double x = 0, y = 0;
        for(int j = 0; j < numberOfControlPoint; j++) {
            double uPower = pow(u, j), euPower = pow(eu, numberOfControlPoint - 1 - j);
            x += combinationNumberList[j] * uPower * euPower * ControlLists[j].x();
            y += combinationNumberList[j] * uPower * euPower * ControlLists[j].y();
        }
        bezierPathList.push_back(CGeoPoint(x, y));
    }
    bezierPathList.push_back( ControlLists[ControlLists.size() - 1]);
}


bool BezierCurver::curveGreatPath() {

    attemptControlList = bezierControlList;
    curveOnly(false);

    if(curveWithDirectionAttempt(false))
        return true;
    if(curveWithDirectionAttempt(true))
        return true;
    return false;
}


bool BezierCurver::curveWithDirectionAttempt(bool reverse) {
    int iterConter = 0;
    int indexOfObs;
    adjustRate = adjustRateInitial;
    while(iterConter < maxAdjustTimes) {
        if(pathIsValid(indexOfObs)) {
            bezierControlList = attemptControlList;
            return true;
        }
        adjust(indexOfObs, reverse, true);
        curveOnly(true);
        adjustRate += adjustStep;
        iterConter++;
    }
    if(pathIsValid(indexOfObs)) {
        bezierControlList = attemptControlList;
        return true;
    }
    return false;
}

CGeoPoint BezierCurver::symmetricPoint(const double A, const double B, const double C, const CGeoPoint &P0) {
    if(A == 0 && B == 0) {
        return P0;
    }
    double x0 = P0.x(), y0 = P0.y();
    double intermediate = (A * x0 + B * y0 + C) / (A * A + B * B);
    double x1 = x0 - 2 * A * intermediate;
    double y1 = y0 - 2 * B * intermediate;
    return CGeoPoint(x1, y1);
}

stateNew BezierCurver::getNextState(void) {
    if(arrivedNumber < (bezierStateList.size() - 1))
        return bezierStateList[++arrivedNumber];
    else
        return bezierStateList[bezierStateList.size() - 1];
}

bool BezierCurver::isOffLine(const CGeoPoint &currentPosition, double threshold) {
    if(bezierPathList.empty())
        return true;

    CGeoPoint start = bezierPathList[arrivedNumber],
              end = bezierPathList[arrivedNumber + 1];
    double distance = distanceToSegment(start, end, currentPosition);
    bool OffLine = distance > lastOffDist && lastOffDist > threshold;
    lastOffDist = distance;
    if(OffLine)
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(0, 0), "isOffLine", COLOR_RED);
    return OffLine;
}


