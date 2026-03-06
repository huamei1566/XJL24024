#include"worker.h"
#include"mainwindow.h"
#include<QNetworkInterface>
#include<QMessageBox>

Worker::~Worker()
{
   m_udpSocket->leaveMulticastGroup(QHostAddress("224.1.1.4"));
   qDebug() << "离开组播";
}

void Worker::start() {
           // 创建UDP套接字
           m_udpSocket = new QUdpSocket(this);

//           // 设置单次触发的3秒定时器
//           m_timer.setSingleShot(true);
//           m_timer.setInterval(1000);
//           // 连接定时器超时信号
//           connect(&m_timer, &QTimer::timeout,this , [this](){
//                  emit readtexttimer(50000 , 100);
//               qDebug() << 1;
//           });


//           m_timer.start();


               // 目标IP地址
               QString targetIp = "192.168.0.100";

               // 查找网络接口
               QNetworkInterface iface = getInterfaceByIp(targetIp);

               if (!iface.isValid()) {
                   qCritical() << "Failed to find interface for" << targetIp;
                   //QMessageBox::information(owner , "提示" , "未找到ipv4地址为192.168.0.100的网络接口,请检查后重启软件以尝试");
                   emit Failurebind("未找到ipv4地址为192.168.0.100的网络接口,请检查后重启软件以尝试");
                   return;
               }


               // 加入组播组（需先绑定端口）
               if (m_udpSocket->bind(QHostAddress::AnyIPv4, 10004,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress )) {
                   m_udpSocket->joinMulticastGroup(QHostAddress("224.1.1.4") , iface);
                   qDebug() << "Joined multicast group 224.1.1.4 on port 10004";



           } else {
               qWarning() << "No valid network interface found!";
               //QMessageBox::information(owner , "提示" , "没有找到有效的网络接口,可能被占用,请检查后重启软件以尝试");
               emit Failurebind("没有找到有效的网络接口,可能被占用,请检查后重启软件以尝试");
           }


    // 连接信号
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &Worker::readPendingDatagrams);



}


void Worker::readPendingDatagrams() {
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

//        QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
//        QString message = QString::fromUtf8(datagram.constData(), datagram.size());

//                            //ui->textEdit->setText(QString(timestamp + ":" + message));

//                            qDebug() << timestamp << ": " << message;

        qDebug() << "Received from" << sender << ":" << datagram;

        // 处理数据
        processData(datagram, sender, senderPort);
    }
}

void Worker::onTimeout()
{
    emit timeoutSignal();
    //qDebug() << "onTimeout";
}

void Worker::processData(const QByteArray &data, const QHostAddress &sender, quint16 Port) {
       // QString mode = isMulticastMode ? "[Multicast]" : "[Unicast]";

//        QByteArray array;
//        array = data.toHex();

//        qDebug().noquote() << mode << "Received from" << sender.toString() << ":" << Port
//                 << "Data:" << array ; // 以十六进制显示数据

//        quint8 m_quint8  = static_cast<quint8>(data[0]);
//        m_quint8  = static_cast<quint8>(data[1]);
//        m_quint8  = static_cast<quint8>(data[2]);
//        m_quint8  = static_cast<quint8>(data[3]);

        if(        static_cast<quint8>(data[0]) == 0x55
                && static_cast<quint8>(data[1]) == 0xAA
                && static_cast<quint8>(data[2]) == 0x91
                && static_cast<quint8>(data[3]) == 0xEF)
        {
            quint32 zhongbaohao = (static_cast<quint32>(data[12]) << 24) |
                                (static_cast<quint32>(data[11]) << 16) |
                                (static_cast<quint32>(data[10]) << 8)  |
                                 static_cast<quint32>(data[9]);
            quint32 dangqiangbaohao = (static_cast<quint32>(data[16]) << 24) |
                                (static_cast<quint32>(data[15]) << 16) |
                                (static_cast<quint32>(data[14]) << 8)  |
                                 static_cast<quint32>(data[13]);
            if(zhongbaohao != dangqiangbaohao)
            {
                numarray.append(data);
                return ;
            }


            if(static_cast<quint8>(data[4]) == 0x11)
            {
                int fasheji = static_cast<quint8>(data[25]);


                if(static_cast<quint8>(data[26]) == 0x00)
                {
                    emit peiz11(fasheji);
                }

                else
                {
                    emit sbpeiz11(fasheji);
                }

                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x12)
            {
                int i = 0;
                for (quint8 byte : data) {
                              QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                              qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                          }

                owner->m_PREAD_FRAMEFORMAT_RES= new READ_FRAMEFORMAT_RES;
                owner->m_PREAD_FRAMEFORMAT_RES->txSelector = static_cast<quint8>(data[17]);
                owner->m_PREAD_FRAMEFORMAT_RES->pcmRate = (static_cast<quint8>(data[21]) << 24)  |
                                                          (static_cast<quint8>(data[20]) << 16)  |
                                                          (static_cast<quint8>(data[19]) << 8)  |
                                                           static_cast<quint8>(data[18]);
                owner->m_PREAD_FRAMEFORMAT_RES->subFrameLength.rawValue = (static_cast<quint8>(data[23]) << 8)  |
                                                                           static_cast<quint8>(data[22]);

                owner->m_PREAD_FRAMEFORMAT_RES->subFrameCount = static_cast<quint8>(data[24]);
                owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.raw = static_cast<quint8>(data[25]);
                owner->m_PREAD_FRAMEFORMAT_RES->featurePosition = (static_cast<quint8>(data[27]) << 8)  |
                                                                   static_cast<quint8>(data[26]);
                owner->m_PREAD_FRAMEFORMAT_RES->loopSyncCode = (static_cast<quint8>(data[29]) << 8)  |
                                                                static_cast<quint8>(data[28]);





                i = 30;
                owner->m_PREAD_FRAMEFORMAT_RES->syncCode =  (static_cast<quint64>(static_cast<quint8>(data[i+7])) << 56) |
                        (static_cast<quint64>(static_cast<quint8>(data[i+6])) << 48) |
                        (static_cast<quint64>(static_cast<quint8>(data[i+5])) << 40) |
                        (static_cast<quint64>(static_cast<quint8>(data[i+4])) << 32) |
                        (static_cast<quint64>(static_cast<quint8>(data[i+3])) << 24) |
                        (static_cast<quint64>(static_cast<quint8>(data[i+2])) << 16) |
                        (static_cast<quint64>(static_cast<quint8>(data[i+1])) << 8) |
                         static_cast<quint64>(static_cast<quint8>(data[i]));


                 owner->m_PREAD_FRAMEFORMAT_RES->frameType = static_cast<quint8>(data[38]);

                 for(int i = 0 ; i < 5 ;i++)
                 {
                     owner->m_PREAD_FRAMEFORMAT_RES->reserved1[i] = static_cast<quint8>(data[39 + i]);
                 }

                 owner->m_PREAD_FRAMEFORMAT_RES->dataType = static_cast<quint8>(data[44]);
                 qDebug() << owner->m_PREAD_FRAMEFORMAT_RES->dataType;
                 owner->m_PREAD_FRAMEFORMAT_RES->stepValue = (static_cast<quint8>(data[46]) << 8)  |
                                                              static_cast<quint8>(data[45]);
                 owner->m_PREAD_FRAMEFORMAT_RES->initStep = (static_cast<quint8>(data[48]) << 8)  |
                                                             static_cast<quint8>(data[47]);
                 owner->m_PREAD_FRAMEFORMAT_RES->FrameCalcChannel.value = (static_cast<quint8>(data[50]) << 8)  |
                                                                           static_cast<quint8>(data[49]);
                 owner->m_PREAD_FRAMEFORMAT_RES->frameCalcChannelhigh.value = (static_cast<quint8>(data[52]) << 8)  |
                                                                               static_cast<quint8>(data[51]);

                 qDebug() << owner->m_PREAD_FRAMEFORMAT_RES->FrameCalcChannel.value
                          << owner->m_PREAD_FRAMEFORMAT_RES->frameCalcChannelhigh.value;

                 for(int i = 0 ; i < 4 ;i++)
                 {
                     owner->m_PREAD_FRAMEFORMAT_RES->reserved2[i] = static_cast<quint8>(data[53 + i]);
                 }
                 owner->m_PREAD_FRAMEFORMAT_RES->idtreatrue.raw = static_cast<quint8>(data[57]);
                 owner->m_PREAD_FRAMEFORMAT_RES->codingPosition = static_cast<quint8>(data[58]);
                 for(int i = 1 ; i <= 23 ;i++)
                 {
                     owner->m_PREAD_FRAMEFORMAT_RES->reserved3[i] = static_cast<quint8>(data[58 + i]);
                 }
                 emit RES_FRAMEFORMAT(owner->m_PREAD_FRAMEFORMAT_RES->txSelector);
                 numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x13)
            {
                int fasheji = static_cast<quint8>(data[25]);

                if(static_cast<quint8>(data[26]) == 0x00)
                {
                    emit peiz13(fasheji);
                }

                else
                {
                    emit sbpeiz13(fasheji);
                }
                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x14)
            {
//                int i = 0;
//                for (quint8 byte : data) {
//                              QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
//                              qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
//                          }

                owner->m_PREAD_yaocFRAMEFORMAT_RES = new READ_yaocFRAMEFORMAT_RES;
                owner->m_PREAD_yaocFRAMEFORMAT_RES->txSelector = static_cast<quint8>(data[17]);
                owner->m_PREAD_yaocFRAMEFORMAT_RES->freq1 =  (static_cast<quint8>(data[21]) << 24) |
                                                             (static_cast<quint8>(data[20]) << 16) |
                                                             (static_cast<quint8>(data[19]) << 8)  |
                                                              static_cast<quint8>(data[18]);

                //qDebug() << owner->m_PREAD_yaocFRAMEFORMAT_RES->freq1;


                owner->m_PREAD_yaocFRAMEFORMAT_RES->detF1 = (static_cast<quint8>(data[25]) << 24) |
                                                             (static_cast<quint8>(data[24]) << 16) |
                                                             (static_cast<quint8>(data[23]) << 8)  |
                                                             static_cast<quint8>(data[22]);

                owner->m_PREAD_yaocFRAMEFORMAT_RES->reserved1 = (static_cast<quint8>(data[27]) << 8)  |
                                                                 static_cast<quint8>(data[26]);

                owner->m_PREAD_yaocFRAMEFORMAT_RES->ctrl1 = static_cast<quint8>(data[28]);
                owner->m_PREAD_yaocFRAMEFORMAT_RES->powerCtrl1 = static_cast<quint8>(data[29]);
                owner->m_PREAD_yaocFRAMEFORMAT_RES->powerCtrl1_UI = static_cast<quint8>(data[30]);


//                qDebug() << owner->m_PREAD_yaocFRAMEFORMAT_RES->freq1
//                         << owner->m_PREAD_yaocFRAMEFORMAT_RES->detF1
//                         << owner->m_PREAD_yaocFRAMEFORMAT_RES->ctrl1
//                         << owner->m_PREAD_yaocFRAMEFORMAT_RES->powerCtrl1;


                emit RES_yaocFRAMEFORMAT(owner->m_PREAD_yaocFRAMEFORMAT_RES->txSelector);


                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x15)
            {
                int fasheji = static_cast<quint8>(data[25]);

                if(static_cast<quint8>(data[26]) == 0x00)
                {
                    emit peiz15(fasheji);
                }

                else
                {
                    emit sbpeiz15(fasheji);
                }
                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x16)
            {
//                int i = 0;
//                for (quint8 byte : data) {
//                              QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
//                              qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
//                          }

                owner->m_PREAD_ENCODING_CONFIG_RES = new READ_ENCODING_CONFIG_RES;
                owner->m_PREAD_ENCODING_CONFIG_RES->txSelector = static_cast<quint8>(data[17]);
                owner->m_PREAD_ENCODING_CONFIG_RES->codeSwitch = static_cast<quint8>(data[18]);

                for(int i = 0 ; i < 3 ; i++)
                {
                    owner->m_PREAD_ENCODING_CONFIG_RES->reserved[i] = static_cast<quint8>(data[19 + i]);
                }
                owner->m_PREAD_ENCODING_CONFIG_RES->tpcSyncCode = (static_cast<quint8>(data[25]) << 24) |
                                                                  (static_cast<quint8>(data[24]) << 16) |
                                                                  (static_cast<quint8>(data[23]) << 8)  |
                                                                   static_cast<quint8>(data[22]);

                owner->m_PREAD_ENCODING_CONFIG_RES->tpcValidFlag = (static_cast<quint8>(data[27]) << 8)  |
                                                                    static_cast<quint8>(data[26]);



                for(int i = 0 ; i < 53 ; i++)
                {
                    owner->m_PREAD_ENCODING_CONFIG_RES->padding[i] = static_cast<quint8>(data[28 + i]);
                }

                emit RES_ENCODING_CONFIG(owner->m_PREAD_ENCODING_CONFIG_RES->txSelector);


                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x17)
            {
                int fasheji = static_cast<quint8>(data[25]);
                if(static_cast<quint8>(data[26]) == 0x00)
                {
                    emit peiz17(fasheji);
                }

                else
                {
                    emit sbpeiz17(fasheji);
                }
                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x18)
            {
                int i = 0;
                for (quint8 byte : data) {
                    QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                    qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                }

                owner->m_PREAD_PCM_CONFIG_RES = new READ_PCM_CONFIG_RES;
                owner->m_PREAD_PCM_CONFIG_RES->txSelector = static_cast<quint8>(data[17]);
                owner->m_PREAD_PCM_CONFIG_RES->entryCount = static_cast<quint8>(data[18]);

                for(int i = 0 ; i < 10 ; i++)
                {
                    owner->m_PREAD_PCM_CONFIG_RES->entries[i].rawCtrl= static_cast<quint8>(data[19 + i * 8]);
                    owner->m_PREAD_PCM_CONFIG_RES->entries[i].subFramePos= static_cast<quint8>(data[20+ i * 8]);
                    owner->m_PREAD_PCM_CONFIG_RES->entries[i].childFramePos= (static_cast<quint8>(data[22 + i * 8]) << 8)  |
                                                                              static_cast<quint8>(data[21 + i * 8]);
                    owner->m_PREAD_PCM_CONFIG_RES->entries[i].dataSource= static_cast<quint8>(data[23+ i * 8]);
                    owner->m_PREAD_PCM_CONFIG_RES->entries[i].entryReserved= static_cast<quint8>(data[24+ i * 8]);
                    owner->m_PREAD_PCM_CONFIG_RES->entries[i].dataLength= (static_cast<quint8>(data[26 + i * 8]) << 8)  |
                                                                           static_cast<quint8>(data[25 + i * 8]);

                }
                  emit RES_PCM_CONFIG(owner->m_PREAD_PCM_CONFIG_RES->txSelector);

                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x19)
            {
                int fasheji = static_cast<quint8>(data[25]);
                if(static_cast<quint8>(data[26]) == 0x00)
                {
                    emit peiz19(fasheji);
                }

                else
                {
                    emit sbpeiz19(fasheji);
                }
                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x1a)
            {
                int i = 0;
                for (quint8 byte : data) {
                    QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                    qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                }

                owner->m_PREAD_ASY_CONFIG_RES = new READ_ASY_CONFIG_RES;
                owner->m_PREAD_ASY_CONFIG_RES->txSelector = static_cast<quint8>(data[17]);
                owner->m_PREAD_ASY_CONFIG_RES->entryCount = static_cast<quint8>(data[18]);




                for(int i = 0 ; i < 10 ; i++)
                {
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].frameLength = static_cast<quint8>(data[19 + i * 12]);
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].Securitycontrolposition = static_cast<quint8>(data[20 + i * 12]);
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].dataType = static_cast<quint8>(data[21 + i * 12]);
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].stepIncrement = static_cast<quint8>(data[22 + i * 12]);
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].initialValue =  static_cast<quint8>(data[23 + i * 12]);
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].syncCode = (static_cast<quint8>(data[27 + i * 12]) << 24) |
                                                                         (static_cast<quint8>(data[26 + i * 12]) << 16) |
                                                                         (static_cast<quint8>(data[25 + i * 12]) << 8)  |
                                                                          static_cast<quint8>(data[24 + i * 12]);

                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].syncCodeLength = static_cast<quint8>(data[28 + i * 12]);
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].frameCounterLength = static_cast<quint8>(data[29 + i * 12]);
                    owner->m_PREAD_ASY_CONFIG_RES->entries[i].zhenlv = static_cast<quint8>(data[30 + i * 12]);
                }

                emit RES_ASY_CONFIG(owner->m_PREAD_ASY_CONFIG_RES->txSelector);

                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x1b)
            {
                int fasheji = static_cast<quint8>(data[25]);
                if(static_cast<quint8>(data[26]) == 0x00)
                {
                    emit peiz1B(fasheji);
                }

                else
                {
                    emit sbpeiz1B(fasheji);
                }
                numarray.clear();
            }

            else if(static_cast<quint8>(data[4]) == 0x1c)
            {


                owner->m_PREADankongpeiz_RES = new READankongpeiz_RES;

                owner->m_PREADankongpeiz_RES->reserved = static_cast<quint8>(data[17]);
                owner->m_PREADankongpeiz_RES->carrierFrequency = (static_cast<quint8>(data[21]) << 24) |
                                                                 (static_cast<quint8>(data[20]) << 16) |
                                                                 (static_cast<quint8>(data[19]) << 8)  |
                                                                  static_cast<quint8>(data[18]);

                owner->m_PREADankongpeiz_RES->subcarrierFrequency = (static_cast<quint8>(data[25]) << 24) |
                                                                    (static_cast<quint8>(data[24]) << 16) |
                                                                    (static_cast<quint8>(data[23]) << 8)  |
                                                                     static_cast<quint8>(data[22]);
                owner->m_PREADankongpeiz_RES->controlMode   =     static_cast<quint8>(data[26]);

                owner->m_PREADankongpeiz_RES->dpskFmBandwidth   =     static_cast<quint8>(data[27]);

                owner->m_PREADankongpeiz_RES->dpskFmInstructionRate   =   (static_cast<quint8>(data[31]) << 24) |
                                                                          (static_cast<quint8>(data[30]) << 16) |
                                                                          (static_cast<quint8>(data[29]) << 8)  |
                                                                           static_cast<quint8>(data[28]);

                owner->m_PREADankongpeiz_RES->dpskFmInstructionLength   = (static_cast<quint8>(data[33]) << 8)  |
                                                                           static_cast<quint8>(data[32]);

                for(int i = 0 ; i < 3 ; i++)
                {
                    owner->m_PREADankongpeiz_RES->dpskFmPreamble[i] = static_cast<quint8>(data[34 + i]);
                }

                owner->m_PREADankongpeiz_RES->dpskFmInstructionSyncCode = (static_cast<quint8>(data[38]) << 8)  |
                                                                           static_cast<quint8>(data[37]);

                owner->m_PREADankongpeiz_RES->codeType = static_cast<quint8>(data[39]);

                owner->m_PREADankongpeiz_RES->DPSK_K1_Address_Code = static_cast<quint8>(data[40]);
                owner->m_PREADankongpeiz_RES->DPSK_K1_Function_Code = (static_cast<quint8>(data[42]) << 8)  |
                                                                       static_cast<quint8>(data[41]);
                owner->m_PREADankongpeiz_RES->DPSK_K1_Fill_Code = static_cast<quint8>(data[43]);
                owner->m_PREADankongpeiz_RES->DPSK_K2_Address_Code = static_cast<quint8>(data[44]);
                owner->m_PREADankongpeiz_RES->DPSK_K2_Function_Code = (static_cast<quint8>(data[46]) << 8)  |
                                                                       static_cast<quint8>(data[45]);
                owner->m_PREADankongpeiz_RES->DPSK_K2_Fill_Code = static_cast<quint8>(data[47]);
                owner->m_PREADankongpeiz_RES->DPSK_K3_Address_Code = static_cast<quint8>(data[48]);
                owner->m_PREADankongpeiz_RES->DPSK_K3_Function_Code = (static_cast<quint8>(data[50]) << 8)  |
                                                                       static_cast<quint8>(data[49]);
                owner->m_PREADankongpeiz_RES->DPSK_K3_Fill_Code = static_cast<quint8>(data[51]);
                owner->m_PREADankongpeiz_RES->DPSK_K4_Address_Code = static_cast<quint8>(data[52]);
                owner->m_PREADankongpeiz_RES->DPSK_K4_Function_Code = (static_cast<quint8>(data[54]) << 8)  |
                                                                       static_cast<quint8>(data[53]);
                owner->m_PREADankongpeiz_RES->DPSK_K4_Fill_Code = static_cast<quint8>(data[55]);


                owner->m_PREADankongpeiz_RES->MainLetter_Self_check[0] = (static_cast<quint8>(data[57]) << 8)  |
                                                                          static_cast<quint8>(data[56]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_check[1] = (static_cast<quint8>(data[59]) << 8)  |
                                                                          static_cast<quint8>(data[58]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_check[2] = (static_cast<quint8>(data[61]) << 8)  |
                                                                          static_cast<quint8>(data[60]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_check[3] = (static_cast<quint8>(data[63]) << 8)  |
                                                                          static_cast<quint8>(data[62]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_check[4] = (static_cast<quint8>(data[65]) << 8)  |
                                                                          static_cast<quint8>(data[64]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_check[5] = (static_cast<quint8>(data[67]) << 8)  |
                                                                          static_cast<quint8>(data[66]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_check[6] = (static_cast<quint8>(data[69]) << 8)  |
                                                                          static_cast<quint8>(data[68]);
                owner->m_PREADankongpeiz_RES->MainLetter_Reset[0] = (static_cast<quint8>(data[71]) << 8)  |
                                                                     static_cast<quint8>(data[70]);
                owner->m_PREADankongpeiz_RES->MainLetter_Reset[1] = (static_cast<quint8>(data[73]) << 8)  |
                                                                     static_cast<quint8>(data[72]);
                owner->m_PREADankongpeiz_RES->MainLetter_Reset[2] = (static_cast<quint8>(data[75]) << 8)  |
                                                                     static_cast<quint8>(data[74]);
                owner->m_PREADankongpeiz_RES->MainLetter_Reset[3] = (static_cast<quint8>(data[77]) << 8)  |
                                                                     static_cast<quint8>(data[76]);
                owner->m_PREADankongpeiz_RES->MainLetter_Reset[4] = (static_cast<quint8>(data[79]) << 8)  |
                                                                     static_cast<quint8>(data[78]);
                owner->m_PREADankongpeiz_RES->MainLetter_Reset[5] = (static_cast<quint8>(data[81]) << 8)  |
                                                                     static_cast<quint8>(data[80]);
                owner->m_PREADankongpeiz_RES->MainLetter_Reset[6] = (static_cast<quint8>(data[83]) << 8)  |
                                                                     static_cast<quint8>(data[82]);
                owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[0] = (static_cast<quint8>(data[85]) << 8)  |
                                                                        static_cast<quint8>(data[84]);
                owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[1] = (static_cast<quint8>(data[87]) << 8)  |
                                                                        static_cast<quint8>(data[86]);
                owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[2] = (static_cast<quint8>(data[89]) << 8)  |
                                                                        static_cast<quint8>(data[88]);
                owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[3] = (static_cast<quint8>(data[91]) << 8)  |
                                                                        static_cast<quint8>(data[90]);
                owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[4] = (static_cast<quint8>(data[93]) << 8)  |
                                                                        static_cast<quint8>(data[92]);
                owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[5] = (static_cast<quint8>(data[95]) << 8)  |
                                                                        static_cast<quint8>(data[94]);
                owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[6] = (static_cast<quint8>(data[97]) << 8)  |
                                                                        static_cast<quint8>(data[96]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[0] = (static_cast<quint8>(data[99]) << 8)  |
                                                                             static_cast<quint8>(data[98]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[1] = (static_cast<quint8>(data[101]) << 8)  |
                                                                             static_cast<quint8>(data[100]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[2] = (static_cast<quint8>(data[103]) << 8)  |
                                                                             static_cast<quint8>(data[102]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[3] = (static_cast<quint8>(data[105]) << 8)  |
                                                                             static_cast<quint8>(data[104]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[4] = (static_cast<quint8>(data[107]) << 8)  |
                                                                             static_cast<quint8>(data[106]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[5] = (static_cast<quint8>(data[109]) << 8)  |
                                                                             static_cast<quint8>(data[108]);
                owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[6] = (static_cast<quint8>(data[111]) << 8)  |
                                                                             static_cast<quint8>(data[110]);


                qDebug() << owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[3]
                         << owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[4];


                emit RES_PREADankongpeiz();


            }

            else if(static_cast<quint8>(data[4]) == 0x1d)
            {
//                int i = 0;
//                for (quint8 byte : data) {
//                              QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
//                              qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
//                          }

                owner->m_PREADSECURITYCONTROL_RES = new READSECURITYCONTROL_RES;

                owner->m_PREADSECURITYCONTROL_RES->commandCount = (static_cast<quint8>(data[22]) << 8) |
                                                                   static_cast<quint8>(data[21]);
                owner->m_PREADSECURITYCONTROL_RES->commandLength = static_cast<quint8>(data[23]);
                owner->m_PREADSECURITYCONTROL_RES->mode = static_cast<quint8>(data[24]);
                if(owner->m_PREADSECURITYCONTROL_RES->mode == 0)
                {
                    owner->m_PREADSECURITYCONTROL_RES->dpskem.syncCode = (static_cast<quint8>(data[26]) << 8) |
                                                                          static_cast<quint8>(data[25]);
                    owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode = static_cast<quint8>(data[27]);
                    owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode = (static_cast<quint8>(data[29]) << 8) |
                                                                              static_cast<quint8>(data[28]);
                    owner->m_PREADSECURITYCONTROL_RES->dpskem.padding = static_cast<quint8>(data[30]);

                    if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK1.addressCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK1.functionCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK1.padding     )
                         {
                                 owner->ankongjiegongK1.kValue++;
                         }
                    else if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK2.addressCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK2.functionCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK2.padding     )
                         {
                                 owner->ankongjiegongK2.kValue++;
                         }
                    else if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK3.addressCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK3.functionCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK3.padding     )
                         {
                                 owner->ankongjiegongK3.kValue++;
                         }

                    else if(owner->m_PREADSECURITYCONTROL_RES->dpskem.addressCode == owner->ankongjiegongK4.addressCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.functionCode == owner->ankongjiegongK4.functionCode &&
                       owner->m_PREADSECURITYCONTROL_RES->dpskem.padding == owner->ankongjiegongK4.padding     )
                         {
                                 owner->ankongjiegongK4.kValue++;
                         }

                    emit ankongupdate();



                }
                else if(owner->m_PREADSECURITYCONTROL_RES->mode == 1)
                {
                    for(int i = 0 ; i < 7 ; i++)
                    {
                         owner->m_PREADSECURITYCONTROL_RES->mainchar.chars[i] = (static_cast<quint8>(data[26 + i * 2]) << 8) |
                                                                                 static_cast<quint8>(data[25 + i * 2]);
                    }

            }




            }
            else if(static_cast<quint8>(data[4]) == 0x1e)
            {

                    owner->m_RES_TransmitterData = new RES_TransmitterData;
                    owner->m_RES_TransmitterData->tx1_freq_point = (static_cast<quint8>(data[20]) << 24) |
                                                                    (static_cast<quint8>(data[19]) << 16) |
                                                                    (static_cast<quint8>(data[18]) << 8)  |
                                                                    static_cast<quint8>(data[17]);

                    owner->m_RES_TransmitterData->tx1_rf_status = static_cast<quint8>(data[21]);

                    owner->m_RES_TransmitterData->tx1_buffer_capacity = (static_cast<quint8>(data[23]) << 8) |
                                                                         static_cast<quint8>(data[22]);

                    owner->m_RES_TransmitterData->tx1_MofeiCumulativeNumber = static_cast<quint8>(data[24]);


                    owner->m_RES_TransmitterData->tx2_freq_point = (static_cast<quint8>(data[51]) << 24) |
                                                                   (static_cast<quint8>(data[50]) << 16) |
                                                                   (static_cast<quint8>(data[49]) << 8)  |
                                                                    static_cast<quint8>(data[48]);

                    owner->m_RES_TransmitterData->tx2_rf_status = static_cast<quint8>(data[52]);

                    owner->m_RES_TransmitterData->tx2_buffer_capacity = (static_cast<quint8>(data[54]) << 8) |
                                                                         static_cast<quint8>(data[53]);

                    owner->m_RES_TransmitterData->tx2_MofeiCumulativeNumber = static_cast<quint8>(data[56]);



                    owner->m_RES_TransmitterData->security_recv_power = static_cast<quint8>(data[57]);
                    owner->m_RES_TransmitterData->sec_rx_status = static_cast<quint8>(data[58]);

                    owner->m_RES_TransmitterData->Security_control_status = static_cast<quint8>(data[59]);

                    owner->m_RES_TransmitterData->Power_input_voltage = (static_cast<quint8>(data[61]) << 8) |
                                                                         static_cast<quint8>(data[60]);

                    owner->m_RES_TransmitterData->Output_voltage_12V = (static_cast<quint8>(data[63]) << 8) |
                                                                         static_cast<quint8>(data[62]);

                    owner->m_RES_TransmitterData->Power_amplifier_28V_supply_voltage = (static_cast<quint8>(data[65]) << 8) |
                                                                                        static_cast<quint8>(data[64]);

                    owner->m_RES_TransmitterData->Input_current_power_supply = (static_cast<quint8>(data[67]) << 8) |
                                                                         static_cast<quint8>(data[66]);

                    owner->m_RES_TransmitterData->Output_current_12V = (static_cast<quint8>(data[69]) << 8) |
                                                                         static_cast<quint8>(data[68]);
                    owner->m_RES_TransmitterData->Power_amplifier1 = (static_cast<quint8>(data[71]) << 8) |
                                                                         static_cast<quint8>(data[70]);

                    owner->m_RES_TransmitterData->Power_amplifier2 = (static_cast<quint8>(data[73]) << 8) |
                                                                         static_cast<quint8>(data[72]);
                    owner->m_RES_TransmitterData->Detection_voltage1 = (static_cast<quint8>(data[75]) << 8) |
                                                                         static_cast<quint8>(data[74]);
                    owner->m_RES_TransmitterData->Detection_voltage2 = (static_cast<quint8>(data[77]) << 8) |
                                                                         static_cast<quint8>(data[76]);

                    owner->m_RES_TransmitterData->Temperature = static_cast<quint8>(data[78]);


                    owner->m_RES_TransmitterData->Version_number = (static_cast<quint8>(data[80]) << 8) |
                                                                    static_cast<quint8>(data[79]);

                    remainingCapacity = 128 * 1024 - owner->m_RES_TransmitterData->tx1_buffer_capacity* 4;
                    remainingCapacity2 = 128 * 1024 - owner->m_RES_TransmitterData->tx2_buffer_capacity* 4;


                    owner->baosu  = remainingCapacity;
                    owner->baosu2  = remainingCapacity2;

                    tx1_MofeiCumulativeNumber = owner->m_RES_TransmitterData->tx1_MofeiCumulativeNumber;
                    tx2_MofeiCumulativeNumber = owner->m_RES_TransmitterData->tx2_MofeiCumulativeNumber;

                    emit readRequest1(remainingCapacity , tx1_MofeiCumulativeNumber);
                    emit readRequest2(remainingCapacity2, tx2_MofeiCumulativeNumber);


                    emit readoAll(remainingCapacity , tx1_MofeiCumulativeNumber , remainingCapacity2, tx2_MofeiCumulativeNumber);


                    emit updateK(owner->m_RES_TransmitterData->Security_control_status,owner->m_RES_TransmitterData->Detection_voltage1,
                                 owner->m_RES_TransmitterData->Detection_voltage2);


                    emit MachineStatusRead(owner->m_RES_TransmitterData->Power_input_voltage,
                                           owner->m_RES_TransmitterData->Output_voltage_12V,
                                           owner->m_RES_TransmitterData->Power_amplifier_28V_supply_voltage,
                                           owner->m_RES_TransmitterData->Input_current_power_supply,
                                           owner->m_RES_TransmitterData->Output_current_12V,
                                           owner->m_RES_TransmitterData->Power_amplifier1,
                                           owner->m_RES_TransmitterData->Power_amplifier2,
                                           owner->m_RES_TransmitterData->Detection_voltage1,
                                           owner->m_RES_TransmitterData->Detection_voltage2,
                                           owner->m_RES_TransmitterData->Temperature,
                                           owner->m_RES_TransmitterData->Version_number);

                    owner->m_timer->start();




}
            else if(static_cast<quint8>(data[4]) == 0x1f)
            {
                int fasheji = static_cast<quint8>(data[25]);


                if(static_cast<quint8>(data[26]) == 0x00)
                {
                    emit peiz1f(fasheji);
                }

                else
                {
                    emit sbpeiz1f(fasheji);
                }

                numarray.clear();
            }


        }

}

void Worker::resetTimer()
{
     m_timer.start(); // 重新开始3秒计时
}

QNetworkInterface Worker::getInterfaceByIp(const QString &targetIp)
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


