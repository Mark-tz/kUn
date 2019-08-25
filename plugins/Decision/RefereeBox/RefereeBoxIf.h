#ifndef _REFEREE_BOX_IF_H_
#define _REFEREE_BOX_IF_H_
#include <QUdpSocket>
#include <MultiThread.h>
#include <singleton.h>
#include <QMutex>
/*
 *	CRefereeBoxInterface.
 *  和RefereeBox的接口
 */
class COptionModule;
class RefereeBoxInterface{
public:
    static RefereeBoxInterface* Instance(COptionModule *pOption);
	void start();
	void stop();
    inline int getPlayMode(){refereeMutex.lock(); int result = _playMode;refereeMutex.unlock();return result;}
    inline int getBlueGoalNum(){refereeMutex.lock(); int result = _blueGoalNum;refereeMutex.unlock();return result;}
    inline int getYellowGoalNum(){refereeMutex.lock(); int result = _yellowGoalNum;refereeMutex.unlock();return result;}
    inline int getRemainTime(){refereeMutex.lock(); int result = _remainTime;refereeMutex.unlock();return result;}
    inline int getBlueGoalie(){refereeMutex.lock(); int result = _blueGoalie;refereeMutex.unlock();return result;}
    inline int getYellowGoalie(){refereeMutex.lock(); int result = _yellowGoalie;refereeMutex.unlock();return result;}
    inline float getBallPlacementPosX(){ refereeMutex.lock();float result = ballPlacementX;refereeMutex.unlock();return result;}
    inline float getBallPlacementPosY(){ refereeMutex.lock();float result = ballPlacementY;refereeMutex.unlock();return result;}
protected:
	void receivingLoop();
    RefereeBoxInterface(COptionModule *pOption);
    ~RefereeBoxInterface();
private:
    static RefereeBoxInterface* _instance;
	QUdpSocket receiveSocket;
	bool _alive;
	// 现在的裁判盒指令
	int _playMode;
	// 蓝方的进球数
	int _blueGoalNum;
	// 黄方的进球数
	int _yellowGoalNum;
	// 这个半场所剩的时间(sec)
	int _remainTime;
	// 蓝方守门员车号
	int _blueGoalie;
	// 黄方守门员车号
	int _yellowGoalie;
    // Ball Placement Position
    float ballPlacementX,ballPlacementY;
    QMutex refereeMutex;
};
#endif
