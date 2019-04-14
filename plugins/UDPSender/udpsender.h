#ifndef __UDP_SENDER_H__
#define __UDP_SENDER_H__
#include "zsplugin.hpp"
#include <string>
class QUdpSocket;
class UDPSender : public ZSPlugin {
public:
	UDPSender(const std::string& msg,const std::string& address,const unsigned int port);
	UDPSender(const std::string& msg,const unsigned int port);
	~UDPSender();
	void run();
private:
	QUdpSocket * socket;
	std::string address;
	std::string msg;
	unsigned int  port;
	bool multicast;
};
#endif // __UDP_SENDER_H__