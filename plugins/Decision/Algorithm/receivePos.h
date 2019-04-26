#ifndef RECEIVEPOS_H
#define RECEIVEPOS_H
#include "VisionModule.h"
#include "singleton.hpp"

/*******************************************************/
/*            generate pass pos module                 */
/*            migrated from balladvancedecison         */
/*******************************************************/

class ReceivePos
{
public:
    ReceivePos();
    void generatePassPos(const CVisionModule* pVision, const int leader);
    void generateRandomTestPos(const CVisionModule* pVision);
    void testCasePlusPlus();
    CGeoPoint receiveBallPointCompute(const CVisionModule* pVision, int number,const std::vector<CGeoPoint>& targetPoint);

    int bestReceiver() const { return _bestReceiver; }
    CGeoPoint bestPassPoint() const { return _bestPassPoint; }
private:
    struct AreaStatus {
        std::vector <CGeoRectangle> location;
        std::vector <CGeoPoint> targetPos;
        std::vector <bool> status;
        double lineAmount;
        double columnAmount;
    } area;
    int _bestReceiver;
    int _receiver;
    CGeoPoint _bestPassPoint;
};
typedef NormalSingleton<ReceivePos> ReceivePosModule;

#endif // RECEIVEPOS_H
