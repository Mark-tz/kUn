#include "udpsender.h"
#include <QUdpSocket>
UDPSender::UDPSender(const std::string& msg,const std::string& address,const unsigned int port):multicast(true),port(port),msg(msg),address(address),socket(nullptr){
	declare_receive(msg);
}
UDPSender::UDPSender(const std::string& msg,const unsigned int port):multicast(false),port(port),msg(msg),address("127.0.0.1"),socket(nullptr){
	declare_receive(msg);
}
UDPSender::~UDPSender(){
	delete socket;
}
void UDPSender::run(){
	socket = new QUdpSocket();
	if(multicast)
		socket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
	ZSData data;
	int res;
	while(true){
		receive(msg,data);
		res = socket->writeDatagram((char*)data.ptr(),data.size(),QHostAddress(QString::fromStdString(address)),port);
//		std::cout << "writen : " << res << std::endl;
	}
}
