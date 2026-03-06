#include "sendermanger.h"

sendermanger::sendermanger(QObject *parent) : QObject(parent)
{
    m_Sender = new QUdpSocket;
    m_Sender->bind(QHostAddress("192.168.0.100"), 10004,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress );
}

void sendermanger::onreadRequest(int count, int port)
{

}
