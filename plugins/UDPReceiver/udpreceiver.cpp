#include <QUdpSocket>
#include "udpreceiver.h"
UDPReceiver::UDPReceiver(const std::string& msg,const std::string& address,const unsigned int port):msg(msg),socket(new QUdpSocket()){
	declare_publish(msg);
	if(!(socket->bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress) &&
		socket->joinMulticastGroup(QHostAddress(QString::fromStdString(address)))))
		std::cerr << "ERROR: socket bind error! " << msg << " " << address << " " << port << std::endl;
}
UDPReceiver::UDPReceiver(const std::string& msg,const unsigned int port):msg(msg),socket(new QUdpSocket()){
	declare_publish(msg);
	if(!socket->bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress))
		std::cerr << "ERROR: socket bind error! " << msg << " " << port << std::endl;
}

UDPReceiver::~UDPReceiver(){
	delete socket;
}
void UDPReceiver::run(){
	ZSData data;
	while(true){
		std::this_thread::sleep_for(std::chrono::microseconds(1));
		while (socket->state() == QUdpSocket::BoundState && socket->hasPendingDatagrams()) {
			data.resize(socket->pendingDatagramSize());
			socket->readDatagram((char*)data.ptr(),data.size());
			publish(this->msg,data);
		}
	}
}