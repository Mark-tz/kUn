#ifndef ASTARPLANNER_H
#define ASTARPLANNER_H

#include "ObstacleNew.h"


class AStarNode {
public:
    AStarNode(double x, double y, AStarNode* father=nullptr) : x_(x), y_(y), g_(0), h_(0), f_(0), father_(father) {}
    AStarNode(CGeoPoint p, AStarNode* father=nullptr) : x_(p.x() + 600), y_(p.y() + 450), g_(0), h_(0), f_(0), father_(father) {}

    double x() { return x_; }
    double y() { return y_; }
    double g() { return g_; }
    double h() { return h_; }
    double f() { return f_; }
    AStarNode* father() { return father_; }

    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    void setG(double g) { g_ = g; }
    void setH(double h) { h_ = h; }
    void setF(double f) { f_ = f; }
    void setFather(AStarNode* father) { father_ = father; }

    CGeoPoint toCGeoPoint() { return CGeoPoint(x_ - 600, y_ - 450); }
    CGeoPoint toIntPoint() { return CGeoPoint(int(x_ - 600), int(y_ - 450)); }
private:
    double x_, y_;
    double g_; // the actual cost from start pos to here
    double h_; // the cost estimation from here to the target pos
    double f_; // the estimation value
    AStarNode* father_;
};

class AStarPlanner {
public:
    AStarPlanner(double avoidDist, ObstaclesNew obsList) : avoidDist_(avoidDist), obsList_(obsList) {}
    ~AStarPlanner() {
        for (AStarNode* node : openList_) delete node;
        for (AStarNode* node : closeList_) delete node;
        vector<AStarNode*>().swap(openList_);
        vector<AStarNode*>().swap(closeList_);
    }
    vector<CGeoPoint> calcPath(CGeoPoint start, CGeoPoint end);
    void nextStep(AStarNode* node);
    void trace();

    void getPath(AStarNode* current);
    void calcGHF(AStarNode* sNode, AStarNode* eNode, double g);
    bool makeInField(CGeoPoint start, CGeoPoint end);
    int findPosition(int x, int y);
    CGeoPoint makeIntPoint(CGeoPoint p);

private:
    vector<CGeoPoint> pathList_;
    vector<CGeoPoint> traceList_;
    vector<AStarNode*> openList_;
    vector<AStarNode*> closeList_;
    double avoidDist_;
    ObstaclesNew obsList_;
//    bool isClose_[1200][900] = {0};
};

#endif // ASTARPLANNER_H
