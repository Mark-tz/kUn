#include "AStarPlanner.h"
#include <algorithm>

namespace {
    double step_ = 30;
    double globalG = 10;
    AStarNode* startPos;
    AStarNode* endPos;
}

vector<CGeoPoint> AStarPlanner::calcPath(CGeoPoint start, CGeoPoint end) {
    if (!obsList_.check(start) || !obsList_.check(end)) return pathList_;
    if (!makeInField(start, end)) return pathList_;

    startPos = new AStarNode(start);
    endPos = new AStarNode(end);

    openList_.push_back(startPos);

    AStarNode* current;
    while (openList_.size() > 0) {
        current = openList_[0];

        if (fabs(current->x() - endPos->x()) + fabs(current->y() - endPos->y()) < 20) {
            endPos->setFather(current);
            closeList_.push_back(endPos);
            getPath(closeList_.back());
            break;
        }

        nextStep(current);
        closeList_.push_back(current);
//        isClose_[int(current->x())][int(current->y())] = 1;
        openList_.erase(openList_.begin());
        swap(*min_element(openList_.begin(), openList_.end(), [] (AStarNode* n1, AStarNode* n2) {
                 if (n1->f() == n2->f()) return n1->h() < n2->h();
                 else return n1->f() < n2->f();
             }), openList_[0]);
    }

    trace();
    return traceList_;
}

void AStarPlanner::nextStep(AStarNode *node) {
    CGeoPoint current = node->toIntPoint();
    for (int i = 0; i < 8; i++) {
        CGeoPoint newPos = makeIntPoint(current + Utils::Polar2Vector(step_, Utils::Normalize(Param::Math::PI / 4 * i)));
        if (!obsList_.check(newPos) || !obsList_.check(newPos, current)) return;
//        if (isClose_[int(newPos.x())][int(newPos.y())] == 1) return;

        int index = findPosition(int(newPos.x()), int(newPos.y()));
        if (index == -1) { // if the pos is not in openlist, add it in
            AStarNode* pos = new AStarNode(newPos, node);
            calcGHF(pos, endPos, globalG);
            openList_.push_back(pos);
        }
        else { // if the pos is already in openlist, update G if current G is not right
            AStarNode* pos = openList_[index];
            if (pos->g() > node->g() + globalG) {
                pos->setFather(node);
                pos->setG(node->g() + globalG);
                pos->setF(pos->g() + pos->h());
            }
        }
    }
}

void AStarPlanner::trace() {
    for (int i = pathList_.size() - 1; i > 0;) {
        for (int j = i - 1; j >= 0; j--) {
            if (!obsList_.check(pathList_[i], pathList_[j])) {
                traceList_.push_back(pathList_[j + 1]);
                i = j;
            }
            if (j == 0) {
                traceList_.push_back(pathList_[0]);
                i = 0;
            }
        }
    }
}

void AStarPlanner::getPath(AStarNode *current) {
    if (current->father() != nullptr) getPath(current->father());
    pathList_.push_back(current->toCGeoPoint());
}

void AStarPlanner::calcGHF(AStarNode *sNode, AStarNode *eNode, double g) {
    double h = sqrt(pow(sNode->x() - eNode->x(), 2) + pow(sNode->y() - eNode->y(), 2));
    double currentG = sNode->father()->g() + g;
    double f = currentG + h * 0.5;
    sNode->setH(h);
    sNode->setG(currentG);
    sNode->setF(f);
}

bool AStarPlanner::makeInField(CGeoPoint start, CGeoPoint end) {
    if (fabs(start.x()) > Param::Field::PITCH_LENGTH || fabs(start.y()) > Param::Field::PITCH_WIDTH ||
            fabs(end.x()) > Param::Field::PITCH_LENGTH || fabs(end.y()) > Param::Field::PITCH_WIDTH)
        return false;
    else return true;
}

CGeoPoint AStarPlanner::makeIntPoint(CGeoPoint p) {
    return CGeoPoint(int(p.x()), int(p.y()));
}

int AStarPlanner::findPosition(int x, int y) {
    for (unsigned int i = 0; i < openList_.size(); i++) {
        if (openList_[i]->x() == x && openList_[i]->y() == y) return i;
    }
    return -1;
}
