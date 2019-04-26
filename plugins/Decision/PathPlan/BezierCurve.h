#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H
#include "ObstacleNew.h"
#include <vector>

using namespace std;
class BezierCurver {
    vector<CGeoPoint> bezierPathList;
    vector<CGeoPoint> bezierControlList;
    vector<CGeoPoint> attemptControlList;
    vector<stateNew> bezierStateList;
    vector<double> combinationNumberList;
    ObstaclesNew obstacle;

    stateNew start;
    stateNew target;

    int NCombinationNumber;
    int arrivedNumber;
    int curvePointNumber;
    int adjustCounter;
    float adjustRate;

    bool zeroStartVel;
    bool zeroTargetVel;
    double lastOffDist;
public:
    BezierCurver() {}
    void initControlList(const stateNew& start, const stateNew& target, const double vMax, vector<CGeoPoint> initialControlList, int curvePointNumber, ObstaclesNew obstacle, bool StartVelControlPoint = true);
    void addStartVelCtrlPoint(double vMax, double lengthPart);
    void addTargetVelCtrlPoint(double vMax, double lengthPart);

    bool curveGreatPath(void);
    void curveOnly(bool isAttempt);
    bool curveWithDirectionAttempt(bool reverse);
    void calculateState( const PlayerCapabilityT &capability, double& timeNeeded, stateNew& nextTarget);
    int indexFirstCtrlPointCanBeAdjusted(void);
    int indexLastCtrlPointCanBeAdjusted(void);
    void adjust(const int& indexOfObs, bool reverse, bool isAttempt);
    CGeoPoint symmetricPoint(const double A, const double B, const double C, const CGeoPoint& P0);

    bool pathIsValid(int& indexOfObs);
    bool isOffLine(const CGeoPoint& currentPosition, double threshold);

    int findNearestControlPointFromObst(const int& indexOfObs);
    double distanceToSegment(const CGeoPoint& segStart, const CGeoPoint& segEnd, const CGeoPoint& targetPoint);
    int findNearestPathPoint(const CGeoPoint& myPosition, bool &isArrived);
    int getArrivedNumber(void) const {return arrivedNumber;}
    stateNew getNextState(void);
    vector<CGeoPoint> getPathList(void) const { return bezierPathList; }
    vector<CGeoPoint> getControlList(void) const {return bezierControlList;}
    inline double combinationNumber(int n, int i);
};

#endif // BEZIER_CURVE_H
