/************************************************************************/
/* file created by shengyu, 2005.3.23                                   */
/************************************************************************/
#ifndef __VISION_RECEIVER_H__
#define __VISION_RECEIVER_H__

#include "vision_detection.pb.h"
#include <MultiThread.h>
#include <singleton.h>
#include <ServerInterface.h>
//#include "VisionLog.h"
class COptionModule;
class QUdpSocket;
class VisionReceiver {
  public:
    static VisionReceiver* instance(COptionModule *pOption = NULL);
    static void destruct();
  public:
    bool getVisionInfo(CServerInterface::VisualInfo& info, RefRecvMsg& msg) const;
    ZSS_THREAD_FUNCTION void getMessage();
    QUdpSocket* visionSocket;
  private:
    VisionReceiver(COptionModule *pOption);
    ~VisionReceiver(void);
    void ReceiveVision();
    static void InitInfo(CServerInterface::VisualInfo& info);
    Vision_DetectionFrame detectionFrame;
    static VisionReceiver* _instance;
    CServerInterface::VisualInfo _info, temp;
    RefRecvMsg _recvMsg;

    bool _threadAlive;
};

#endif
