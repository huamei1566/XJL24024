#include "udpreceiverthread.h"
#include <QDebug>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

#include "mainwindow.h"







UdpReceiverThread::UdpReceiverThread(quint16 port, QObject *parent)
    : QThread(parent), m_port(port), m_udpSocket(nullptr),
      m_running(true), m_joinedMulticast(false)
{

    m_running =true;
}

UdpReceiverThread::UdpReceiverThread(quint16 port,
                                     const QString &multicastGroup,
                                     const QString &interfaceName,
                                     QObject *parent)
    : QThread(parent), m_port(port), m_multicastGroup(multicastGroup),
      m_interfaceName(interfaceName), m_udpSocket(nullptr),
      m_running(true), m_joinedMulticast(false)
{

    m_running =true;
}

UdpReceiverThread::~UdpReceiverThread()
{
    stop();
    if (m_udpSocket) {
        m_udpSocket->deleteLater();
    }
    wait();
}

void UdpReceiverThread::run()
{
    m_udpSocket = new QUdpSocket();

    if (!m_udpSocket->bind(QHostAddress::AnyIPv4, m_port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        qWarning() << "Failed to bind UDP socket on port" << m_port;
        return;
    }

    // 如果配置了组播地址
    if (!m_multicastGroup.isEmpty()) {
        QHostAddress multicastAddress(m_multicastGroup);

        // 验证组播地址范围 (224.0.0.0 到 239.255.255.255)
        if (!multicastAddress.isMulticast()) {
            qWarning() << "Invalid multicast address:" << m_multicastGroup;
        } else {
            // 选择网络接口
            if (!m_interfaceName.isEmpty()) {
                QNetworkInterface networkInterface = QNetworkInterface::interfaceFromName(m_interfaceName);
                if (!networkInterface.isValid()) {
                    qWarning() << "Invalid network interface:" << m_interfaceName;
                } else {
                    m_interface = networkInterface;
                }
            }

            // 加入组播组
            if (m_interface.isValid()) {
                if (m_udpSocket->joinMulticastGroup(multicastAddress, m_interface)) {
                    qDebug() << "Joined multicast group" << m_multicastGroup
                             << "on interface" << m_interface.humanReadableName()
                             << "port" << m_port;
                    m_joinedMulticast = true;
                    emit multicastJoined(m_multicastGroup);
                } else {
                    qWarning() << "Failed to join multicast group" << m_multicastGroup
                               << "on interface" << m_interface.humanReadableName();
                    emit multicastJoinError("Failed to join multicast group: " + m_multicastGroup);
                }
            } else {
                if (m_udpSocket->joinMulticastGroup(multicastAddress)) {
                    qDebug() << "Joined multicast group" << m_multicastGroup
                             << "on all interfaces, port" << m_port;
                    m_joinedMulticast = true;
                    emit multicastJoined(m_multicastGroup);
                } else {
                    qWarning() << "Failed to join multicast group" << m_multicastGroup
                               << "on all interfaces";
                    emit multicastJoinError("Failed to join multicast group: " + m_multicastGroup);
                }
            }
        }
    }

    qDebug() << "UDP receiver started on port" << m_port
             << (m_joinedMulticast ? ("in multicast group " + m_multicastGroup) : "")
             << "in thread" << QThread::currentThreadId();
   m_running = true;
    // 事件循环
    while (m_running) {
        if (m_udpSocket->waitForReadyRead(500)) { // 500ms超时
            while (m_udpSocket->hasPendingDatagrams()) {
                QByteArray datagram;

                //缓冲位置
                datagram.resize(m_udpSocket->pendingDatagramSize());

                QHostAddress sender;
                quint16 senderPort;
                qint64 bytesRead = m_udpSocket->readDatagram(
                    datagram.data(), datagram.size(), &sender, &senderPort);

                if (bytesRead > 0) {
                    // 发射信号通知主线程ReceiverThread
                    emit dataReceived(datagram, sender, senderPort);
                } else if (bytesRead < 0) {
                    qWarning() << "Error reading interfacedatagram:" << m_udpSocket->errorString();
                }
            }
        }
    }

    // 离开组播组（如果已加入）
    if (!m_multicastGroup.isEmpty() && m_joinedMulticast) {
        QHostAddress multicastAddress(m_multicastGroup);
        if (m_interface.isValid()) {
            m_udpSocket->leaveMulticastGroup(multicastAddress, m_interface);
        } else {
            m_udpSocket->leaveMulticastGroup(multicastAddress);
        }
        qDebug() << "Left multicast group" << m_multicastGroup;
    }

    m_udpSocket->close();
    qDebug() << "UDP receiver thread exiting";
}

void UdpReceiverThread::stop()
{
    m_running = false;
}

#include <QDebug>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

Controller::Controller(QObject *parent)
    : QObject(parent), receiverThread(nullptr), isMulticastMode(false)
{

}

Controller::~Controller()
{
    stop();
}

void Controller::start()
{
    if (!receiverThread) {
        // 创建接收线程（监听端口10004）
        receiverThread = new UdpReceiverThread(10004);

        // 连接信号
        connect(receiverThread, &UdpReceiverThread::dataReceived,
                this, &Controller::handleData);

        // 连接组播相关信号
        connect(receiverThread, &UdpReceiverThread::multicastJoined,
                this, &Controller::handleMulticastJoined);
        connect(receiverThread, &UdpReceiverThread::multicastJoinError,
                this, &Controller::handleMulticastJoinError);

        // 线程结束时自动删除
        connect(receiverThread, &QThread::finished,
                receiverThread, &QObject::deleteLater);
    }

    if (!receiverThread->isRunning()) {
        receiverThread->start();
        isMulticastMode = false;
    }
}

void Controller::startMulticast(const QString &group, const QString &interface)
{
    // 如果已存在接收线程，先停止它
    if (receiverThread && receiverThread->isRunning()) {
        stop();
    }

    // 创建新的接收线程用于组播
    receiverThread = new UdpReceiverThread(10004, group, interface);

    // 连接信号
    connect(receiverThread, &UdpReceiverThread::dataReceived,
            this, &Controller::handleData);

    // 连接组播相关信号
    connect(receiverThread, &UdpReceiverThread::multicastJoined,
            this, &Controller::handleMulticastJoined);
    connect(receiverThread, &UdpReceiverThread::multicastJoinError,
            this, &Controller::handleMulticastJoinError);

    // 线程结束时自动删除
    connect(receiverThread, &QThread::finished,
            receiverThread, &QObject::deleteLater);

    receiverThread->start();
    isMulticastMode = true;
}

void Controller::stop()
{
    if (receiverThread && receiverThread->isRunning()) {
        receiverThread->stop();
        receiverThread->quit();
        receiverThread->wait();
    }
    receiverThread = nullptr;
}

void Controller::handleData(const QByteArray &data, const QHostAddress &sender, quint16 port)
{
    QString mode = isMulticastMode ? "[Multicast]" : "[Unicast]";



    QByteArray array;
    array = data.toHex();

    qDebug().noquote() << mode << "Received from" << sender.toString() << ":" << port
             << "Data:" << array ; // 以十六进制显示数据
    if(        static_cast<quint8>(array[0]) == 0x55
            && static_cast<quint8>(array[1]) == 0xAA
            && static_cast<quint8>(array[2]) == 0x91
            && static_cast<quint8>(array[3]) == 0xEF)
    {
        quint32 zhongbaohao = (static_cast<quint32>(array[12]) << 24) |
                            (static_cast<quint32>(array[11]) << 16) |
                            (static_cast<quint32>(array[10]) << 8)  |
                             static_cast<quint32>(array[9]);
        quint32 dangqiangbaohao = (static_cast<quint32>(array[16]) << 24) |
                            (static_cast<quint32>(array[15]) << 16) |
                            (static_cast<quint32>(array[14]) << 8)  |
                             static_cast<quint32>(array[13]);
        if(zhongbaohao != dangqiangbaohao)
        {
            numarray.append(array);
            return ;
        }


        if(static_cast<quint8>(array[4]) == 0x11)
        {
            if(static_cast<quint8>(array[25]) == 0x00)
            {
                emit peiz11();
            }

            else
            {
                emit sbpeiz11();
            }

            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x12)
        {
            owner->m_PREAD_FRAMEFORMAT_RES= new READ_FRAMEFORMAT_RES;
            owner->m_PREAD_FRAMEFORMAT_RES->txSelector = static_cast<quint8>(array[17]);
            owner->m_PREAD_FRAMEFORMAT_RES->pcmRate = static_cast<quint32>((array[21] << 24) |
                                                      (array[20] << 16) |
                                                      (array[19] << 8)  |
                                                       array[18]);
            owner->m_PREAD_FRAMEFORMAT_RES->subFrameLength.rawValue = static_cast<quint16>((array[23] << 8) | array[22]);
            owner->m_PREAD_FRAMEFORMAT_RES->subFrameCount = static_cast<quint8>(array[24]);
            owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.raw = static_cast<quint8>(array[25]);
            owner->m_PREAD_FRAMEFORMAT_RES->featurePosition = static_cast<quint16>((array[27] << 8) | array[26]);
            owner->m_PREAD_FRAMEFORMAT_RES->loopSyncCode = static_cast<quint16>((array[29] << 8) | array[28]);

//            int i= 30;
//            owner->m_PREAD_FRAMEFORMAT_RES->syncCode =  static_cast<quint64>((static_cast(array[i+7]) << 56) |
//                                                        (static_cast(array[i+6]) << 48) |
//                                                        (static_cast(array[i+5]) << 40) |
//                                                        (static_cast(array[i+4]) << 32) |
//                                                        (static_cast(array[i+3]) << 24) |
//                                                        (static_cast(array[i+2]) << 16) |
//                                                        (static_cast(array[i+1]) << 8) |
//                                                         static_cast(array[i]));

             owner->m_PREAD_FRAMEFORMAT_RES->frameType = static_cast<quint8>(array[38]);

             for(int i = 0 ; i < 5 ;i++)
             {
                 owner->m_PREAD_FRAMEFORMAT_RES->reserved1[i] = static_cast<quint8>(array[39 + i]);
             }

             owner->m_PREAD_FRAMEFORMAT_RES->dataType = static_cast<quint8>(array[44]);
             owner->m_PREAD_FRAMEFORMAT_RES->stepValue = static_cast<quint16>((array[46] << 8) | array[45]);
             owner->m_PREAD_FRAMEFORMAT_RES->initStep = static_cast<quint16>((array[48] << 8) | array[47]);
             owner->m_PREAD_FRAMEFORMAT_RES->FrameCalcChannel.value = static_cast<quint16>((array[50] << 8) | array[49]);
             owner->m_PREAD_FRAMEFORMAT_RES->frameCalcChannelhigh.value = static_cast<quint16>((array[52] << 8) | array[51]);

             for(int i = 0 ; i < 4 ;i++)
             {
                 owner->m_PREAD_FRAMEFORMAT_RES->reserved2[i] = static_cast<quint8>(array[53 + i]);
             }
             owner->m_PREAD_FRAMEFORMAT_RES->idtreatrue.raw = static_cast<quint8>(array[57]);
             owner->m_PREAD_FRAMEFORMAT_RES->codingPosition = static_cast<quint8>(array[58]);
             for(int i = 1 ; i <= 23 ;i++)
             {
                 owner->m_PREAD_FRAMEFORMAT_RES->reserved3[i] = static_cast<quint8>(array[58 + i]);
             }
             emit RES_FRAMEFORMAT();
             numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x13)
        {
            if(static_cast<quint8>(array[25]) == 0x00)
            {
                emit peiz13();
            }

            else
            {
                emit sbpeiz13();
            }
            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x14)
        {
            owner->m_PREAD_yaocFRAMEFORMAT_RES = new READ_yaocFRAMEFORMAT_RES;
            owner->m_PREAD_yaocFRAMEFORMAT_RES->txSelector = static_cast<quint8>(array[17]);
            owner->m_PREAD_yaocFRAMEFORMAT_RES->freq1 = static_cast<quint32>((array[21] << 24) |
                                                                              (array[20] << 16) |
                                                                              (array[19] << 8)  |
                                                                               array[18]);
            owner->m_PREAD_yaocFRAMEFORMAT_RES->detF1 = static_cast<quint32>((array[25] << 24) |
                                                                             (array[24] << 16) |
                                                                             (array[23] << 8)  |
                                                                              array[22]);

            owner->m_PREAD_yaocFRAMEFORMAT_RES->reserved1 = static_cast<quint16>(array[27] << 8) | array[26];
            owner->m_PREAD_yaocFRAMEFORMAT_RES->ctrl1 = static_cast<quint8>(array[28]);
            owner->m_PREAD_yaocFRAMEFORMAT_RES->powerCtrl1 = static_cast<quint8>(array[29]);

            emit RES_yaocFRAMEFORMAT();

//            owner->m_PREAD_yaocFRAMEFORMAT_RES->freq2 = static_cast<quint32>((array[33] << 24) |
//                                                                                 (array[32] << 16) |
//                                                                                 (array[31] << 8)  |
//                                                                                  array[30]);
//            owner->m_PREAD_yaocFRAMEFORMAT_RES->detF2 = static_cast<quint32>((array[37] << 24) |
//                                                                             (array[36] << 16) |
//                                                                             (array[35] << 8)  |
//                                                                              array[34]);

//            owner->m_PREAD_yaocFRAMEFORMAT_RES->reserved2 = static_cast<quint16>(array[39] << 8) | array[38];
//            owner->m_PREAD_yaocFRAMEFORMAT_RES->ctrl2 = static_cast<quint8>(array[40]);
//            owner->m_PREAD_yaocFRAMEFORMAT_RES->powerCtrl2 = static_cast<quint8>(array[41]);

//            quint8 reserved3[39];      // 保留区域 [25B]

            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x15)
        {
            if(static_cast<quint8>(array[25]) == 0x00)
            {
                emit peiz15();
            }

            else
            {
                emit sbpeiz15();
            }
            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x16)
        {
            owner->m_PREAD_ENCODING_CONFIG_RES = new READ_ENCODING_CONFIG_RES;
            owner->m_PREAD_ENCODING_CONFIG_RES->txSelector = static_cast<quint8>(array[17]);
            owner->m_PREAD_ENCODING_CONFIG_RES->codeSwitch = static_cast<quint8>(array[18]);

            for(int i = 0 ; i < 3 ; i++)
            {
                owner->m_PREAD_ENCODING_CONFIG_RES->reserved[i] = static_cast<quint8>(array[19 + i]);
            }
            owner->m_PREAD_ENCODING_CONFIG_RES->tpcSyncCode = static_cast<quint32>((array[25] << 24) |
                                                                                   (array[24] << 16) |
                                                                                   (array[23] << 8)  |
                                                                                    array[22]);
            owner->m_PREAD_ENCODING_CONFIG_RES->tpcValidFlag = static_cast<quint16>((array[27] << 8) |
                                                                                     array[26]);



            for(int i = 0 ; i < 53 ; i++)
            {
                owner->m_PREAD_ENCODING_CONFIG_RES->padding[i] = static_cast<quint8>(array[28 + i]);
            }

            emit RES_ENCODING_CONFIG();


            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x17)
        {
            if(static_cast<quint8>(array[25]) == 0x00)
            {
                emit peiz17();
            }

            else
            {
                emit sbpeiz17();
            }
            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x18)
        {
            owner->m_PREAD_PCM_CONFIG_RES = new READ_PCM_CONFIG_RES;
            owner->m_PREAD_PCM_CONFIG_RES->txSelector = static_cast<quint8>(array[17]);
            owner->m_PREAD_PCM_CONFIG_RES->entryCount = static_cast<quint8>(array[18]);

            for(int i = 0 ; i < 10 ; i++)
            {
                owner->m_PREAD_PCM_CONFIG_RES->entries->rawCtrl= static_cast<quint8>(array[19]);
                owner->m_PREAD_PCM_CONFIG_RES->entries->subFramePos= static_cast<quint8>(array[20]);
                owner->m_PREAD_PCM_CONFIG_RES->entries->childFramePos= static_cast<quint16>((array[22] << 8) |
                                                                                            array[21]);
                owner->m_PREAD_PCM_CONFIG_RES->entries->dataSource= static_cast<quint8>(array[23]);
                owner->m_PREAD_PCM_CONFIG_RES->entries->entryReserved= static_cast<quint8>(array[24]);
                owner->m_PREAD_PCM_CONFIG_RES->entries->dataLength= static_cast<quint8>((array[26] << 8)  |
                                                                                        array[25]);

            }
              emit RES_PCM_CONFIG();

            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x19)
        {
            if(static_cast<quint8>(array[25]) == 0x00)
            {
                emit peiz19();
            }

            else
            {
                emit sbpeiz19();
            }
            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x1a)
        {
            owner->m_PREAD_ASY_CONFIG_RES = new READ_ASY_CONFIG_RES;
            owner->m_PREAD_ASY_CONFIG_RES->txSelector = static_cast<quint8>(array[17]);
            owner->m_PREAD_ASY_CONFIG_RES->entryCount = static_cast<quint8>(array[18]);

            for(int i = 0 ; i < 10 ; i++)
            {
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].frameLength = static_cast<quint16>(array[20 + i] << 8) | array[19 + i];
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].dataType = static_cast<quint8>(array[21 + i]);
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].stepIncrement = static_cast<quint8>(array[22 + i]);
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].initialValue =  static_cast<quint8>(array[23 + i]);
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].syncCode = static_cast<quint32>((array[27 + i] << 24) |
                                                                                           (array[26 + i] << 16) |
                                                                                           (array[25 + i] << 8)  |
                                                                                            array[24 + i]);
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].syncCodeLength = static_cast<quint8>(array[28 + i]);
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].frameCounterLength = static_cast<quint8>(array[29 + i]);
                owner->m_PREAD_ASY_CONFIG_RES->entries[i].zhenlv = static_cast<quint8>(array[30 + i]);
            }

            emit RES_ASY_CONFIG();

            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x1b)
        {
            if(static_cast<quint8>(array[25]) == 0x00)
            {
                emit peiz1B();
            }

            else
            {
                emit sbpeiz1B();
            }
            numarray.clear();
        }

        else if(static_cast<quint8>(array[4]) == 0x1c)
        {
            owner->m_PREADSECURITYCONTROL_RES = new READSECURITYCONTROL_RES;


                emit ankongupdate();



            }






        else if(static_cast<quint8>(array[4]) == 0x1d)
        {
            owner->m_PREADSECURITYCONTROL_RES = new READSECURITYCONTROL_RES;

//            owner->m_PREADSECURITYCONTROL_RES->commandCount = static_cast<quint16>(array[22] << 8) | array[21];
//            owner->m_PREADSECURITYCONTROL_RES->commandLength = static_cast<quint16>(array[23]);
//            owner->m_PREADSECURITYCONTROL_RES->mode = static_cast<quint16>(array[24]);
//            if(owner->m_PREADSECURITYCONTROL_RES->mode == 0)
//            {
//                owner->m_PREADSECURITYCONTROL_RES->dpskem.syncCode = static_cast<quint16>(array[26] << 8)  |
//                                                                                          array[25];
//                owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode = static_cast<quint8>(array[27]);
//                owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode = static_cast<quint8>((array[29]) << 8|  array[28]);
//                owner->m_PREADSECURITYCONTROL_RES->dpskem.padding = static_cast<quint8>(array[30]);

//                if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK1.addressCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK1.functionCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK1.padding     )
//                     {
//                             owner->ankongjiegongK1.kValue++;
//                     }
//                else if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK2.addressCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK2.functionCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK2.padding     )
//                     {
//                             owner->ankongjiegongK2.kValue++;
//                     }
//                else if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK3.addressCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK3.functionCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK3.padding     )
//                     {
//                             owner->ankongjiegongK3.kValue++;
//                     }

//                else if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK4.addressCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK4.functionCode &&
//                   owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK4.padding     )
//                     {
//                             owner->ankongjiegongK4.kValue++;
//                     }

                emit ankongupdate();



            }



        else if(static_cast<quint8>(array[4]) == 0x1e)
        {
                owner->m_RES_TransmitterData = new RES_TransmitterData;
                owner->m_RES_TransmitterData->tx1_freq_point = static_cast<quint32>((array[20] << 24) |
                                                                                 (array[19] << 16) |
                                                                                 (array[18] << 8)  |
                                                                                  array[17]);

                owner->m_RES_TransmitterData->tx1_rf_status = static_cast<quint8>(array[21]);

                owner->m_RES_TransmitterData->tx1_buffer_capacity = static_cast<quint16>((array[23] << 8) |  array[22]);


                owner->m_RES_TransmitterData->tx2_freq_point = static_cast<quint32>((array[51] << 24) |
                                                                                 (array[50] << 16) |
                                                                                 (array[49] << 8)  |
                                                                                  array[48]);

                owner->m_RES_TransmitterData->tx2_rf_status = static_cast<quint8>(array[52]);

                owner->m_RES_TransmitterData->tx2_buffer_capacity = static_cast<quint16>((array[54] << 8) |  array[53]);


                owner->m_RES_TransmitterData->security_recv_power = static_cast<quint8>(array[79]);
                owner->m_RES_TransmitterData->sec_rx_status = static_cast<quint8>(array[80]);

                if( 5 * 1024 * 1024 -  owner->m_RES_TransmitterData->tx1_buffer_capacity > 1400 )
                {
                    bool fashe = true;
                    emit read_tx1_buffer_capacity(fashe);
                }
                if( 5 * 1024 * 1024 -  owner->m_RES_TransmitterData->tx2_buffer_capacity > 1400)
                {
                    bool fashe2 = true;
                    emit read_tx2_buffer_capacity(fashe2);
                }



        }
    }



}


void Controller::handleMulticastJoined(const QString &group)
{
    qDebug() << "Successfully joined multicast group:" << group;
}

void Controller::handleMulticastJoinError(const QString &error)
{
    qWarning() << "Multicast join error:" << error;
}

//void ReceiverThread::run()
//{
//    QUdpSocket receiverSocket;

//         // 创建IPv4 UDP套接字
//         if (!receiverSocket.bind(QHostAddress::AnyIPv4, MULTICAST_PORT, QUdpSocket::ShareAddress)) {
//             emit messageReceived("接收端绑定端口失败");
//             return;
//         }

//         // 加入组播组（重要步骤！）
//         if (!receiverSocket.joinMulticastGroup(MULTICAST_ADDRESS)) {
//             emit messageReceived("加入组播组失败: " + receiverSocket.errorString());
//             return;
//         }

//         emit messageReceived("加入组播组成功");

//         while (!isInterruptionRequested()) {
//             // 等待数据报到达（超时300ms检查线程中断）
//             if (receiverSocket.waitForReadyRead(300)) {
//                 QByteArray datagram;
//                 datagram.resize(receiverSocket.pendingDatagramSize());
//                 QHostAddress senderAddress;
//                 quint16 senderPort;

//                 qint64 bytesRead = receiverSocket.readDatagram(datagram.data(), datagram.size(),
//                                                                &senderAddress, &senderPort);
//                 if (bytesRead > 0) {
//                     emit messageReceived(QString("[来自%1:%2] %3")
//                                          .arg(senderAddress.toString())
//                                          .arg(senderPort)
//                                          .arg(QString(datagram)));
//                 }
//             }
//         }

//         // 离开组播组
//         receiverSocket.leaveMulticastGroup(MULTICAST_ADDRESS);

//}
