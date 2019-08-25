#ifndef __UDP_RECEIVER_H__
#define __UDP_RECEIVER_H__
#include "zsplugin.hpp"
#include <string>
class QUdpSocket;
class UDPReceiver : public ZSPlugin {
public:
	UDPReceiver(const std::string&,const std::string&,const unsigned int);
	UDPReceiver(const std::string&,const unsigned int);
	~UDPReceiver();
	void run();
private:
	QUdpSocket * socket;
	std::string msg;
};
#endif // __UDP_RECEIVER_H__