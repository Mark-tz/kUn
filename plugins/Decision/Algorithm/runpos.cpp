#include "runpos.h"
#include <QRandomGenerator>
#include "param.h"
#include "GDebugEngine.h"

namespace {
    const double areaLength = Param::Field::PITCH_LENGTH/4 - 50;
    const double areaWidth = Param::Field::PITCH_WIDTH/4 - 50;
    const CGeoRectangle attackArea[] = {
        CGeoRectangle(0, 0, 0, 0),
        // 1-4
        CGeoRectangle(areaLength, -2*areaWidth, 2*areaLength, -areaWidth),
        CGeoRectangle(areaLength, -areaWidth, 2*areaLength, 0),
        CGeoRectangle(areaLength, 0, 2*areaLength, areaWidth),
        CGeoRectangle(areaLength, areaWidth, 2*areaLength, 2*areaWidth),
        // 5-8
        CGeoRectangle(0, -2*areaWidth, areaLength, -areaWidth),
        CGeoRectangle(0, -areaWidth, areaLength, 0),
        CGeoRectangle(0, 0, areaLength, areaWidth),
        CGeoRectangle(0, areaWidth, areaLength, 2*areaWidth),
        // 9-12
        CGeoRectangle(-areaLength, -2*areaWidth, 0, -areaWidth),
        CGeoRectangle(-areaLength, -areaWidth, 0, 0),
        CGeoRectangle(-areaLength, 0, 0, areaWidth),
        CGeoRectangle(-areaLength, areaWidth, 0, 2*areaWidth),
        // 13-16
        CGeoRectangle(-2*areaLength, -2*areaWidth, -areaLength, -areaWidth),
        CGeoRectangle(-2*areaLength, -areaWidth, -areaLength, 0),
        CGeoRectangle(-2*areaLength, 0, -areaLength, areaWidth),
        CGeoRectangle(-2*areaLength, areaWidth, -areaLength, 2*areaWidth),
    };
    const int attackAreaChoice[4] = {6, 7, 1, 4};

    // 评估函数各项的阈值
    const double maxDistToGoal = sqrt(pow(Param::Field::PITCH_LENGTH, 2) + pow(Param::Field::PITCH_WIDTH, 2));
    const double minShootAngle = 0;
    const double maxShootAngle = Param::Math::PI/2;
    const double maxDistToBall = sqrt(pow(Param::Field::PITCH_LENGTH, 2) + pow(Param::Field::PITCH_WIDTH, 2));
    const double minDistToPassLine = 10.0;
    const double maxDistToPassLine = sqrt(pow(Param::Field::PITCH_LENGTH, 2) + pow(Param::Field::PITCH_WIDTH, 2));
    const double minDistToEnemy = 30.0;
    const double maxDistToEnemy = sqrt(pow(Param::Field::PITCH_LENGTH, 2) + pow(Param::Field::PITCH_WIDTH, 2));
    // 评估函数各项的权重
    const double weight1 = 0.5;// 1.距离对方球门的距离
    const double weight2 = 0.8;// 2.射门有效角度
    const double weight3 = 0.5;// 3.跟球的距离
    const double weight4 = 0.3;// 4.对方车到传球线的距离
    const double weight5 = 0.5;// 5.对方车到接球点的距离
}

RunPos::RunPos() : _pVision(nullptr)
{
    // initialize run pos
    for (int i = 0; i < 4; ++i) {
        _runPos[i] = CGeoPoint(9999, 9999);
    }
}

// basic idea: epsilon greedy
// in the probability of epsilon, select a random pos in an attack area
// in the probability of 1 - epsilon, select the most threatening pos in an attack area
void RunPos::generateRunPos(const CVisionModule* pVision, double epsilon)
{
    // 更新图像信息
    _pVision = pVision;
//    GDebugEngine::Instance()->gui_debug_x(attackArea[16]._point[0]);
//    GDebugEngine::Instance()->gui_debug_x(attackArea[16]._point[1]);
//    GDebugEngine::Instance()->gui_debug_x(attackArea[16]._point[2]);
//    GDebugEngine::Instance()->gui_debug_x(attackArea[16]._point[3]);

    for (int i=0; i<4; i++){
        int area = attackAreaChoice[i];
        int left = int(std::min(attackArea[area]._point[0].x(), attackArea[area]._point[2].x()));
        int right = int(std::max(attackArea[area]._point[0].x(), attackArea[area]._point[2].x()));
        int top = int(std::max(attackArea[area]._point[0].y(), attackArea[area]._point[2].y()));
        int down = int(std::min(attackArea[area]._point[0].y(), attackArea[area]._point[2].y()));

        int randNumber = QRandomGenerator::global()->generate() % 100;

        if (randNumber <= 100 - 100*epsilon)
        {
            // attack threat degree how to evaluate???
            CGeoPoint bestCandidate = CGeoPoint(999, 999);
            double bestScore = -9999;
            for (int i=1; i<=3; i++) {
                for (int j=1; j<=3; j++) {
                    int candidate_x = left + (right - left)/4*i;
                    int candidate_y = down + (top - down)/4*i;
                    CGeoPoint candidate = CGeoPoint(candidate_x, candidate_y);
                    double score = evaluateFunc(candidate);
                    // qDebug() << score;
                    if(score > bestScore){
                        bestScore = score;
                        bestCandidate = candidate;
                    }
                }
            }
            if(bestScore > -9999)
                _runPos[i] = bestCandidate;
        }
        else
        {
            // random Pos
            int random_x = left + QRandomGenerator::global()->generate() % (right - left);
            int random_y = down + QRandomGenerator::global()->generate() % (top - down);
            _runPos[i] = CGeoPoint(random_x, random_y);
//            GDebugEngine::Instance()->gui_debug_x(_runPos[i]);
        }
//        qDebug() << "run Pos " << i << " " << _runPos[i].x() << ", " << _runPos[i].y();
    }
}

// attack threat Evaluation Function for Run Pos
// # attack
// 1.距离对方球门的距离 2.射门有效角度 3.跟球的距离 4.对方车到传球线的距离 5.对方车到接球点的距离
// # defence
//
double RunPos::evaluateFunc(CGeoPoint candidate)
{
    double score = -9999;

    // 1.距离对方球门的距离
    CGeoPoint goal = CGeoPoint(600, 0);
    double distToGoal = (candidate - goal).mod();

    // 2.射门有效角度
    CGeoPoint leftGoalPost = CGeoPoint(600, -60);
    CGeoPoint rightGoalPost = CGeoPoint(600, 60);
    double leftDir = (candidate - leftGoalPost).dir();
    double rightDir = (candidate - rightGoalPost).dir();
    double shootAngle = fabs(leftDir - rightDir);
    shootAngle = shootAngle > Param::Math::PI ? 2*Param::Math::PI - shootAngle : shootAngle;
//    qDebug() << "shootAngle: " << shootAngle;

    // 3.跟球的距离
    const MobileVisionT& ball = _pVision->Ball();
    double distToBall = (candidate - ball.Pos()).mod();

    // 4.对方车到传球线的距离
    CGeoLine passLine = CGeoLine(candidate, ball.Pos());
    double distToPassLine = 9999;
    for (int i=0; i<Param::Field::MAX_PLAYER; i++) {
        const PlayerVisionT& enemy = _pVision->TheirPlayer(i);
        if(enemy.Valid()){
            CGeoPoint projection = passLine.projection(enemy.Pos());
            // 判断是否在线段之间
            if(projection.x() > std::min(ball.Pos().x(), candidate.x()) && projection.x() < std::max(ball.Pos().x(), candidate.x())){
                double dist = (projection - enemy.Pos()).mod();
                if(dist < distToPassLine)
                    distToPassLine = dist;
            }
        }
    }

    // 5.对方车到接球点的距离
    double distToEnemy = 9999;
    for (int i=0; i<Param::Field::MAX_PLAYER; i++) {
        const PlayerVisionT& enemy = _pVision->TheirPlayer(i);
        if(enemy.Valid()){
            double dist = (candidate - enemy.Pos()).mod();
            if(dist < distToEnemy)
                distToEnemy = dist;
        }
    }

    // 当满足最低要求时计算得分
//    qDebug() << (distToGoal < maxDistToGoal) << (shootAngle >= minShootAngle) << (distToBall < maxDistToBall)
//             << (distToPassLine >= minDistToPassLine) << (distToEnemy >= minDistToEnemy);
    if(distToGoal < maxDistToGoal && shootAngle >= minShootAngle && distToBall < maxDistToBall
            && distToPassLine >= minDistToPassLine && distToEnemy >= minDistToEnemy){
//        qDebug() << "calculate";
        // 归一化处理
        distToGoal = 1 - distToGoal/maxDistToGoal;
        shootAngle = shootAngle/maxShootAngle;
        distToBall = 1 - distToBall/maxDistToBall;
        distToPassLine = distToPassLine/maxDistToPassLine;
        distToEnemy = distToEnemy/maxDistToEnemy;

        // 计算得分
        score = weight1*distToGoal + weight2*shootAngle + weight3*distToBall + weight4*distToPassLine + weight5*distToEnemy;
    }
    return score;
}
