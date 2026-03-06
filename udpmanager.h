#ifndef UDPMANAGER_H
#define UDPMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class UdpComm : public QObject
{
    Q_OBJECT
public:
    explicit UdpComm(QObject *parent = nullptr);
    ~UdpComm();

   // void initReceiver();  // 初始化接收器
    void sendDatagram(const QByteArray &data);  // 发送数据

    QNetworkInterface getInterfaceByIp(const QString &targetIp);
signals:
    void dataReceived(const QByteArray &data);  // 数据接收信号

public slots:
    void processPendingDatagrams();  // 处理接收到的数据报

public:
    QUdpSocket *receiverSocket = nullptr;  // UDP接收套接字
    QUdpSocket *senderSocket = nullptr;    // UDP发送套接字

    const QHostAddress MULTICAST_GROUP = QHostAddress("224.1.1.4");  // 组播地址
    const QHostAddress LOCAL_HOST = QHostAddress("192.168.0.100");    // 本机IP
    const QHostAddress REMOTE_HOST = QHostAddress("192.168.0.106");   // 下位机IP

    const quint16 RECV_PORT = 10004;  // 本机接收端口
    const quint16 TARGET_PORT = 10001; // 下位机接收端口
};

#endif // UDPMANAGER_H


