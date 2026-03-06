#include "onlyudpsender.h"
#include "mainwindow.h"

onlyudpsender::onlyudpsender(int pattern)
{
   udpsocket = new QUdpSocket();
    if(pattern == 1)
    {
       udpsocket->bind(QHostAddress("192.168.0.100"), 10005,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress);
    }
    else if(pattern == 2)
    {
        udpsocket->bind(QHostAddress("192.168.0.100"), 10006,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress);
    }



   m_mutex = new QMutex;
}

void onlyudpsender::onlyudpsend(QByteArray data, int port)
{

    m_mutex->lock();

    int ret =  udpsocket->writeDatagram(data , QHostAddress("224.1.1.4") , port);

    m_mutex->unlock();

    qDebug() << ret;

}
