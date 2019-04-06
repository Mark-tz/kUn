#ifndef __VISION_MODULE_H__
#define __VISION_MODULE_H__
#include "zsplugin.hpp"
#include "staticparams.h"
#include "dllexport.h"
#include "kalmanfilter.h"
#include "messageformat.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "vision_detection.pb.h"

class VisionModule:public ZSPlugin{
public:
	DLL_EXPORT VisionModule();
	DLL_EXPORT ~VisionModule();
    virtual void run() override;
	
private:
	virtual void updateVel(ReceiveVisionMessage& message);
	virtual void updateRobotVel(int team, ReceiveVisionMessage& message);
	virtual void updateBallVel(ReceiveVisionMessage& message);
	virtual void parseVisionMessage(SSL_WrapperPacket& , ReceiveVisionMessage&);
	virtual void encodeMessage(Vision_DetectionFrame &, ReceiveVisionMessage&);

	KalmanFilter ballKalmanFilter, _robotPosFilter[2][PARAM::ROBOTMAXID], _robotDirFilter[2][PARAM::ROBOTMAXID];

};
#endif // __VISION_MODULE_H__
