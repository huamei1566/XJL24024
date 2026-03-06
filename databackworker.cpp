#include "databackworker.h"

DataBackworker::DataBackworker(QObject *parent, int hostport)
                  : QObject(parent),
                    hostport(hostport)
{

}

void DataBackworker::setSavefilepath(QString value)
{
    savefilepath = value;
}

void DataBackworker::initudp()
{
    m_DataBackUdpSocket = new QUdpSocket;
    if (m_DataBackUdpSocket->bind(QHostAddress::AnyIPv4 , hostport ,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress))
    {
        m_DataBackUdpSocket->joinMulticastGroup(QHostAddress("224.1.1.4"));
        qDebug() << "Joined multicast group 224.1.1.4 on port 10004";
    }

    connect(m_DataBackUdpSocket, &QUdpSocket::readyRead, this, &DataBackworker::readPendingDatagrams);

    // 启动5秒超时定时器
    timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &DataBackworker::onTimeout);
    timeoutTimer->start(2000);

}

void DataBackworker::startfileandudp()
{
    initfile();

    timeoutTimer->start(2000);

}

void DataBackworker::readPendingDatagrams()
{
    while (m_DataBackUdpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_DataBackUdpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_DataBackUdpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        if(iswrite)
        {
         file.write(datagram);
        }

        // 收到数据，发送开启信号并重启定时器

        if(hostport == 10007)
        {
            emit signalOn(10007);
        }
        else if(hostport == 10008)
        {
            emit signalOn(10007);
        }

         timeoutTimer->start(2000);

    }
}

void DataBackworker::onTimeout()
{
    if(hostport == 10007)
    {
        emit signalOff(10007);
    }
    else if(hostport == 10008)
    {
        emit signalOff(10007);
    }

}

void DataBackworker::initfile()
{
//    // 获取程序所在目录并创建 data 文件夹
//    QString dataDir = savefilepath + +"/" +  QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");
//    QDir dir;
//    if (!dir.exists(dataDir)) {
//        dir.mkdir(dataDir);
//    }

//    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");

    if(hostport == 10007)
    {
        file.setFileName(savefilepath + "/发射机1" + ".dat");
    }
    else if(hostport == 10008)
    {
        file.setFileName(savefilepath + "/发射机2" + ".dat");
    }
    file.open(QIODevice::WriteOnly);
    txtfile.open(QIODevice::WriteOnly | QIODevice::Text);


    iswrite = true;
}

void DataBackworker::quitfile()
{

    //disconnect(m_DataBackUdpSocket, &QUdpSocket::readyRead, this, &DataBackworker::readPendingDatagrams);

    if(file.size() == 0)
    {
        file.remove();
    }
    else
    {
        file.close();
    }

    iswrite = false;

}
