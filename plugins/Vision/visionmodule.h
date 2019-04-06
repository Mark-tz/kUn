#ifndef __VISION_MODULE_H__
#define __VISION_MODULE_H__
#include "zsplugin.hpp"
#include "staticparams.h"
#include "dllexport.h"
#include "kalmanfilter.h"
#include "tinyvisionformat.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "vision_detection.pb.h"

class VisionModule: public ZSPlugin {
  public:
    DLL_EXPORT VisionModule();
    DLL_EXPORT ~VisionModule();
    virtual void run() override;

  private:
    virtual void updateVel(OriginMessage& message);
    virtual void updateRobotVel(int team, OriginMessage& message);
    virtual void updateBallVel(OriginMessage& message);
    virtual void parseVisionMessage(SSL_WrapperPacket&, OriginMessage&);
    virtual void encodeMessage(Vision_DetectionFrame &, OriginMessage&);

    KalmanFilter ballKalmanFilter, _robotPosFilter[2][PARAM::ROBOTMAXID], _robotDirFilter[2][PARAM::ROBOTMAXID];

};
#endif // __VISION_MODULE_H__
