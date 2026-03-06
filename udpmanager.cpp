#include "udpmanager.h"
#include <QNetworkInterface>
#include <QDebug>

UdpComm::UdpComm(QObject *parent) : QObject(parent)
{
    // 初始化接收和发送套接字
   // receiverSocket = new QUdpSocket(this);
    senderSocket = new QUdpSocket(this);

    senderSocket->bind(QHostAddress("192.168.0.100"), 10004, QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress);

    QString targetIp = "192.168.0.100";

    // 查找网络接口
    QNetworkInterface iface = getInterfaceByIp(targetIp);



        senderSocket->joinMulticastGroup(QHostAddress("224.1.1.4") , iface);
        qDebug() << "Joined multicast group 224.1.1.4 on port 10004";




    // 初始化接收器
    //initReceiver();

    // 连接接收信号与处理槽
    // connect(senderSocket, &QUdpSocket::readyRead, this, &UdpComm::processPendingDatagrams);
}

UdpComm::~UdpComm()
{
    // 离开组播组
    if(receiverSocket) {
        receiverSocket->leaveMulticastGroup(MULTICAST_GROUP);
    }
    // 清理套接字
    delete receiverSocket;
    receiverSocket = nullptr;
    delete senderSocket;
    senderSocket = nullptr;
}

//void UdpComm::initReceiver()
//
//    // 绑定本机IP和接收端口
//    if(!receiverSocket->bind(LOCAL_HOST, RECV_PORT, QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress)) {
//        qWarning() << "Failed to bind receiver socket:" << receiverSocket->errorString();
//        return;
//    }

//    // 加入组播组
//    if(!receiverSocket->joinMulticastGroup(MULTICAST_GROUP)) {
//        qWarning() << "Failed to join multicast group:" << receiverSocket->errorString();
//        return;
//    }

//    qDebug() << "Receiver initialized. Listening on"
//             << LOCAL_HOST.toString() << ":" << RECV_PORT
//             << "Multicast group:" << MULTICAST_GROUP.toString();
//}

void UdpComm::sendDatagram(const QByteArray &data)
{
    // 发送数据到组播地址和目标端口
    qint64 bytesSent = senderSocket->writeDatagram(data, MULTICAST_GROUP, TARGET_PORT);

    if(bytesSent == -1) {
        qWarning() << "Failed to send datagram:" << senderSocket->errorString();
    } else {
        qDebug() << "Sent" << bytesSent << "bytes to multicast group"
                 << MULTICAST_GROUP.toString() << "port" << RECV_PORT;
    }
}

void UdpComm::processPendingDatagrams()
{
    while(senderSocket->hasPendingDatagrams()) {
        // 准备数据缓冲区
        QByteArray datagram;
        datagram.resize(senderSocket->pendingDatagramSize());

        // 读取数据报
        QHostAddress sender;
        quint16 senderPort;
        senderSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        // 输出接收信息
        qDebug() << "Received" << datagram.size() << "bytes from"
                 << sender.toString() << ":" << senderPort;

        // 发出数据接收信号
        emit dataReceived(datagram);
    }
}

QNetworkInterface UdpComm::getInterfaceByIp(const QString &targetIp)
{
    QHostAddress targetAddress(targetIp);

        if (targetAddress.isNull()) {
            qWarning() << "Invalid IP address:" << targetIp;
            return QNetworkInterface();
        }

        // 获取所有网络接口
        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

        // 遍历所有接口
        for (const QNetworkInterface &iface : interfaces) {
            // 跳过无效接口
            if (!iface.isValid() ||
                (iface.flags() & QNetworkInterface::IsUp) == 0) {
                continue;
            }

            // 检查所有IP地址
            for (const QNetworkAddressEntry &entry : iface.addressEntries()) {
                if (entry.ip() == targetAddress) {
                    qDebug() << "Found interface for IP" << targetIp
                             << ": " << iface.humanReadableName();
                    return iface;
                }
            }
        }

        qWarning() << "No interface found for IP:" << targetIp;
        return QNetworkInterface();
}
