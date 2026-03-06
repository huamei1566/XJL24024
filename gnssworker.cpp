#include "gnssworker.h"
#include"mainwindow.h"
#include<QNetworkInterface>
#include <QDateTime>


GNSSWorker::~GNSSWorker()
{
   m_udpSocket->leaveMulticastGroup(QHostAddress("224.1.1.4"));
   delete m_udpSocket;
   m_udpSocket = nullptr;
   qDebug() << "离开组播";
}


void GNSSWorker::start()
{
        // 创建UDP套接字
        m_udpSocket = new QUdpSocket(this);


        // 目标IP地址
        QString targetIp = "192.168.0.100";

        // 查找网络接口
        QNetworkInterface iface = getInterfaceByIp(targetIp);

        if (!iface.isValid()) {
            qCritical() << "Failed to find interface for" << targetIp;
            return;
        }


        // 加入组播组（需先绑定端口）
        if (m_udpSocket->bind(QHostAddress::AnyIPv4, 10005,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress )) {
            m_udpSocket->joinMulticastGroup(QHostAddress("224.1.1.4") , iface);
            qDebug() << "Joined multicast group 224.1.1.4 on port 10004";



    } else {
        qWarning() << "No valid network interface found!";
    }


// 连接信号
connect(m_udpSocket, &QUdpSocket::readyRead, this, &GNSSWorker::readPendingDatagrams);

}

void GNSSWorker::readPendingDatagrams()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        // 处理数据
        processData(datagram, sender, senderPort);
    }
}

void GNSSWorker::onTimeout()
{
    emit timeoutSignal();
    //qDebug() << "onTimeout";






}

void GNSSWorker::Inquiry()
{
    m_mutex.lock();
    QRegularExpression regex("\\$G[BNPLA]GSA[^\\*]+\\*([0-9A-Fa-f]{2})");
    if(stringbuffer.contains(regex))   //pdop
    {
        qDebug() << "进入$GNGSA解析";
        //QRegularExpression regex("\\$G[BNPLA]GSA[^\\*]+\\*([0-9A-Fa-f]{2})");

        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);

        int matchCount = 0;

            // 步骤2: 遍历所有匹配
            while (iterator.hasNext()) {
                QRegularExpressionMatch match = iterator.next();
                QString matchedString = match.captured(0);  // 整个匹配的字符串
                   QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

                   if (fields.size() < 2)
                   {
                           return ;
                   }


                   if(fields[2] == "1")
                   {
                       m_SelfLocFrameHeader.positioningStatus = 0b0010;
                   }
                   else
                   {
                       m_SelfLocFrameHeader.positioningStatus = 0b0000;
                   }
                   m_SelfLocFrameHeader.pdop = qToLittleEndian(fields[15].toDouble() * 100);


    }
            stringbuffer.remove(regex);
    }

    regex.setPattern("\\$G[BNPLA]RMC[^\\*]+\\*[0-9A-Fa-f]{2}");
    if(stringbuffer.contains(regex))
    {

        //QRegularExpression regex("\\$GNRMC[^\\*]+\\*[0-9A-Fa-f]{2}");
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);


        int matchCount = 0;

            // 步骤2: 遍历所有匹配
            while (iterator.hasNext()) {
                QRegularExpressionMatch match = iterator.next();
                QString matchedString = match.captured(0);  // 整个匹配的字符串
                   QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

                   if (fields.size() < 2)
                   {
                           return ;
                   }

                   if(fields[12] == "A")
                   {
                      m_SelfLocFrameHeader.gnssFrequencies.bits.method = 0x000;
                   }
                   else
                   {
                       m_SelfLocFrameHeader.gnssFrequencies.bits.method = 0x100;
                   }
                   if(fields[13] == "V")
                   {
                      m_SelfLocFrameHeader.positioningStatus = 0x0010;
                   }
                   else
                   {
                       m_SelfLocFrameHeader.positioningStatus = 0x0000;
                   }



            }

            stringbuffer.remove(regex);
    }

    regex.setPattern("\\$G[BNPLA]DTM[^\\*]+\\*[0-9A-Fa-f]{2}");
    if(stringbuffer.contains(regex))
    {
        qDebug() << "进入$GNDTM解析";
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);

        int matchCount = 0;

            // 步骤2: 遍历所有匹配
            while (iterator.hasNext()) {
                QRegularExpressionMatch match = iterator.next();
                QString matchedString = match.captured(0);  // 整个匹配的字符串
                   QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

                   if (fields.size() < 2)
                   {
                           return ;
                   }


                   if(fields[1] == "W84")
                   {
                       m_SelfLocFrameHeader.coordinateSystem = 0;
                       m_ReferenceStationInfoFrame.coordinateSystemType  = 0;
                   }
                   else if(fields[1] == "P90")
                   {
                       m_SelfLocFrameHeader.coordinateSystem = 1;
                       m_ReferenceStationInfoFrame.coordinateSystemType  = 1;
                   }
                   else
                   {
                       m_SelfLocFrameHeader.coordinateSystem = 2;
                       m_ReferenceStationInfoFrame.coordinateSystemType  = 2;
                   }

    }

            stringbuffer.remove(regex);
    }

    regex.setPattern("\\$G[BNPLA]GGA[^\\*]+\\*[0-9A-Fa-f]{2}");
    if(stringbuffer.contains(regex))
    {
        qDebug() << "进入$GPGGA解析";
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);

        int matchCount = 0;

            // 步骤2: 遍历所有匹配
            while (iterator.hasNext()) {
                QRegularExpressionMatch match = iterator.next();
                QString matchedString = match.captured(0);  // 整个匹配的字符串
                QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字

    }

            stringbuffer.remove(regex);
    }


    if(stringbuffer.contains("#GPSEPHA"))  //钟差 钟漂
    {
        qDebug() << "进入#GPSEPHA解析";
        // 注意：这个校验和是8位十六进制，不是2位
        QRegularExpression regex("#GPSEPHA[^\\*]+\\*[0-9A-Fa-f]{8}");
        // 在清理后的字符串上进行匹配
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);

        // 步骤2: 遍历所有匹配
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString matchedString = match.captured(0);  // 整个匹配的字符串
               QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

               m_SelfLocFrameHeader.clockBias = qToLittleEndian(fields[27].toInt() * 10);
               m_SelfLocFrameHeader.clockDrift = qToLittleEndian(fields[29].toInt() * 10);

        }

        int matchCount = 0;

        // 步骤2: 遍历所有匹配
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString matchedString = match.captured(0);  // 整个匹配的字符串
               QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

               m_SelfLocFrameHeader.clockBias = qToLittleEndian(fields[27].toInt() * 10);
               m_SelfLocFrameHeader.clockDrift = qToLittleEndian(fields[29].toInt() * 10);

        }

        stringbuffer.remove(regex);
    }

    if(stringbuffer.contains("\\$G[BNPLA]ZDA[^\\*]+\\*[0-9A-Fa-f]{2}"))  //年月日，秒
    {
        qDebug() << "进入$GNZDA解析";
        QRegularExpression regex("\\$G[BNPLA]ZDA[^\\*]+\\*[0-9A-Fa-f]{2}");
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);

        int matchCount = 0;

            // 步骤2: 遍历所有匹配
            while (iterator.hasNext()) {
                QRegularExpressionMatch match = iterator.next();
                QString matchedString = match.captured(0);  // 整个匹配的字符串

                   QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

                   m_SelfLocFrameHeader.year = qToLittleEndian(fields[4].toInt());
                   m_SelfLocFrameHeader.month = fields[3].toInt();
                   m_SelfLocFrameHeader.day = fields[2].toInt();
                   double secondsOfDay = convertUtcToSecondsOfDay(fields[1]);
                   m_SelfLocFrameHeader.secondOfDay = qToLittleEndian(secondsOfDay*10);
                   m_SelfLocFrameHeader.timeSystemId = 4;

            }

            stringbuffer.remove(regex);
}
    if(stringbuffer.contains("#SATSINFOA")) //卫星号 ，  卫星信噪比
    {
        qDebug() << "进入#SATSINFOA解析";

        QRegularExpression regex("\\#SATSINFOA[^\\*]+\\*([0-9A-Fa-f]{8})");
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);



        // 步骤2: 遍历所有匹配
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString matchedString = match.captured(0);  // 整个匹配的字符串

            // 找到分号的位置，分割主数据和卫星数据
            int semicolonIndex = matchedString.indexOf(';');
            if (semicolonIndex == -1) {
                qDebug() << "Error: No semicolon found in data";
                //return;
            }

            // 获取分号前的部分
            QString mainPart = matchedString.mid(0, semicolonIndex);

            // 获取分号后的部分（不包括CRC）
            int crcIndex = matchedString.indexOf('*');
            if (crcIndex == -1) {
                qDebug() << "Error: No CRC separator found";
                //return;
            }

            QString satPart = matchedString.mid(semicolonIndex + 1, crcIndex - semicolonIndex - 1);
            QString crcStr = matchedString.mid(crcIndex + 1);

            // 解析主数据部分
            QStringList mainFields = satPart.split(',', QString::KeepEmptyParts);
            //qDebug() << "satPart:" << satPart;
            if (mainFields.size() < 10) {  // 至少需要10个字段
                qDebug() << "Error: Main data part has insufficient fields";
                //return;
            }


            // 解析CRC
            bool ok;
            m_SATSINFOData.crc = crcStr.toUInt(&ok, 16);
            if (!ok) {
                qDebug() << "Error: Invalid CRC format";
                //return;
            }


            SatparseData(mainFields);

            int index = 0;
            for (const SatelliteInfo &satellite : m_SATSINFOData.satellites) {



                if(m_SATSINFOData.satellites[index].sysStatus  == 0)
                  {
                    if(m_SATSINFOData.satellites[index].freqStatus == 0)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.gps_l1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 9)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.gps_l2 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 3)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.gps_l1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 11)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.gps_l1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 6)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.gps_l5 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 14)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.gps_l5 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 17)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.gps_l2 = 1;
                    }
                  }

                else if(m_SATSINFOData.satellites[index].sysStatus  == 4)
                {
                    if(m_SATSINFOData.satellites[index].freqStatus == 0)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 4)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 8)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 23)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 5)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b2 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 17)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b2 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 12)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b2 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 28)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b2 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 6)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b3 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 21)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b3 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 13)
                    {
                        m_SelfLocFrameHeader.gnssFrequencies.bits.bds_b2 = 1;
                    }

                }

                else if(m_SATSINFOData.satellites[index].sysStatus  == 1)
                {
                    if(m_SATSINFOData.satellites[index].freqStatus == 0)
                    {
                         m_SelfLocFrameHeader.gnssFrequencies.bits.glonass_g1 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 5)
                    {
                         m_SelfLocFrameHeader.gnssFrequencies.bits.glonass_g2 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 6)
                    {
                         m_SelfLocFrameHeader.gnssFrequencies.bits.glonass_g3 = 1;
                    }
                    else if(m_SATSINFOData.satellites[index].freqStatus == 7)
                    {
                         m_SelfLocFrameHeader.gnssFrequencies.bits.glonass_g3 = 1;
                    }
                }


            }





    }

    m_SelfLocFrameHeader.validChannelCount =  m_SATSINFOData.satNumber;

    for(int i = 0 ; i < m_SelfLocFrameHeader.validChannelCount ; i++)
    {
       Channel1SatelliteParams newChannel1SatelliteParams;
       newChannel1SatelliteParams.satelliteNumber  = m_SATSINFOData.satellites[i].prn;
       newChannel1SatelliteParams.CTStatusWord.codeLoopSync   =1;
       newChannel1SatelliteParams.CTStatusWord.carrierLoopSync=1;
       newChannel1SatelliteParams.CTStatusWord.bitSync=1;
       newChannel1SatelliteParams.CTStatusWord.frameSync=1;
       newChannel1SatelliteParams.CTStatusWord.raimFault=1;
       newChannel1SatelliteParams.CTStatusWord.participateInPositioning=1;
       newChannel1SatelliteParams.CTStatusWord.frequencyType=1;
       newChannel1SatelliteParams.CTStatusWord.codeType = CodeType::CoarseCode;
       newChannel1SatelliteParams.signalToNoiseRatio = m_SATSINFOData.satellites[i].snr;

       Channel1SatelliteParamsVector.append(newChannel1SatelliteParams);

    }
    stringbuffer.remove(regex);

    }
    //OBSVM
    if(stringbuffer.contains("#OBSVMA"))
    {
        qDebug() << "进入#OBSVMA解析";
        QRegularExpression regex("\\#OBSVMA[^\\*]+\\*([0-9A-Fa-f]{8})");
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);



        // 步骤2: 遍历所有匹配
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString matchedString = match.captured(0);  // 整个匹配的字符串
            //qDebug() << "SATSINFOA_matchedString:  " << matchedString;

            // 找到分号的位置，分割主数据和卫星数据
            int semicolonIndex = matchedString.indexOf(';');
            if (semicolonIndex == -1) {
                qDebug() << "Error: No semicolon found in data";
                //return;
            }

            // 获取分号前的部分
            QString mainPart = matchedString.mid(0, semicolonIndex);
            qDebug() << "分号前的部分:  " <<  mainPart;
            // 获取分号后的部分（不包括CRC）
            int crcIndex = matchedString.indexOf('*');
            if (crcIndex == -1) {
                qDebug() << "Error: No CRC separator found";
                //return;
            }

            QString satPart = matchedString.mid(semicolonIndex + 1, crcIndex - semicolonIndex - 1);
            QString crcStr = matchedString.mid(crcIndex + 1);

            // 解析主数据部分
            QStringList mainFields = satPart.split(',', QString::KeepEmptyParts);
            frameparseData(mainFields);

        }
        stringbuffer.remove(regex);
    }

    if(stringbuffer.contains("#GLOEPHA"))
    {
        qDebug() << "进入#GLOEPHA解析";
        QRegularExpression regex("\\#GLOEPHA[^\\*]+\\*([0-9A-Fa-f]{8})");
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);



        // 步骤2: 遍历所有匹配
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString matchedString = match.captured(0);  // 整个匹配的字符串
            QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

            m_SelfLocFrameHeader.posX = qToLittleEndian(fields[13].toDouble()* 10);
            m_SelfLocFrameHeader.posY = qToLittleEndian(fields[14].toDouble()* 10);
            m_SelfLocFrameHeader.posZ = qToLittleEndian(fields[15].toDouble()* 10);
            m_SelfLocFrameHeader.velX = qToLittleEndian(fields[16].toDouble()* 10);
            m_SelfLocFrameHeader.velY = qToLittleEndian(fields[17].toDouble()* 10);
            m_SelfLocFrameHeader.velZ = qToLittleEndian(fields[18].toDouble()* 10);


        }
        stringbuffer.remove(regex);
    }

    //#AGRICA
    if(stringbuffer.contains("#AGRICA"))
    {
        qDebug() << "进入#AGRICA解析";
        QRegularExpression regex("\\#AGRICA[^\\*]+\\*([0-9A-Fa-f]{8})");
        QRegularExpressionMatchIterator iterator = regex.globalMatch(stringbuffer);



        // 步骤2: 遍历所有匹配
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString matchedString = match.captured(0);  // 整个匹配的字符串


            // 找到分号的位置，分割主数据和卫星数据
            int semicolonIndex = matchedString.indexOf(';');
            if (semicolonIndex == -1) {
                qDebug() << "Error: No semicolon found in data";
                return;
            }

            // 获取分号后的部分（不包括CRC）
            int crcIndex = matchedString.indexOf('*');
            if (crcIndex == -1) {
                qDebug() << "Error: No CRC separator found";
                return;
            }

            QString satPart = matchedString.mid(semicolonIndex + 1, crcIndex - semicolonIndex - 1);
            QString crcStr = matchedString.mid(crcIndex + 1);

            // 解析主数据部分
            QStringList mainFields = satPart.split(',', QString::KeepEmptyParts);
            //qDebug() << "satPart:" << satPart;
            if (mainFields.size() < 10) {  // 至少需要10个字段
                qDebug() << "Error: Main data part has insufficient fields";
                return;
            }

            m_ReferenceStationInfoFrame.coordinateX = mainFields[32].toDouble() * 1000;
            m_ReferenceStationInfoFrame.coordinateY = mainFields[33].toDouble() * 1000;
            m_ReferenceStationInfoFrame.coordinateZ = mainFields[34].toDouble() * 1000;


        }
        stringbuffer.remove(regex);
    }


    m_gnss_generic_frame_header_t.data_length = qToLittleEndian(sizeof(SelfLocFrameHeader) + m_SelfLocFrameHeader.validChannelCount *sizeof(Channel1SatelliteParams));


    QByteArray satarray;
    m_gnss_generic_frame_header_t.frame_type = 0;
    satarray.append(reinterpret_cast<const char*>(&m_gnss_generic_frame_header_t)  ,sizeof(gnss_generic_frame_header_t));
    satarray.append(reinterpret_cast<const char*>(&m_SelfLocFrameHeader) ,  sizeof(SelfLocFrameHeader));
    satarray.append(byteArrayToSatelliteParams(Channel1SatelliteParamsVector));
    QByteArray crcArray = extractMiddlePart(satarray);

    quint32 m_crc32 = crc32(crcArray);

    m_FrameTail.crc = qToLittleEndian(m_crc32);
    satarray.append(reinterpret_cast<const char*>(&m_FrameTail) ,  sizeof(FrameTail));
    owner->udpManager->senderSocket->writeDatagram(satarray, QHostAddress("224.1.1.4"), 10006);


    QByteArray Referencearray;
    m_gnss_generic_frame_header_t.frame_type = 4;
    Referencearray.append(reinterpret_cast<const char*>(&m_gnss_generic_frame_header_t)  ,sizeof(gnss_generic_frame_header_t));
    Referencearray.append(reinterpret_cast<const char*>(&m_ReferenceStationInfoFrame) ,  sizeof(ReferenceStationInfoFrame));

    crcArray = extractMiddlePart(Referencearray);
    m_crc32 = crc32(crcArray);
    m_FrameTail.crc = qToLittleEndian(m_crc32);
    Referencearray.append(reinterpret_cast<const char*>(&m_FrameTail) ,  sizeof(FrameTail));

    //owner->udpManager->sendDatagram(Referencearray);
    owner->udpManager->senderSocket->writeDatagram(Referencearray, QHostAddress("224.1.1.4"), 10006);


//    if(bufferclear_count == 14)
//    {
//        qDebug() << "开始stringbuffer" << stringbuffer.size();
//        stringbuffer.clear();
//        qDebug() << "结束stringbuffer" << stringbuffer.size();
//        bufferclear_count = 0;
//    }
//    bufferclear_count++;

    Channel1SatelliteParamsVector.clear();
    m_SATSINFOData.satellites.clear();
    m_SelfLocFrameHeader.validChannelCount = 0;
    m_SelfLocFrameHeader.positioningStatus = 0;
    m_gnss_generic_frame_header_t.data_length = 0;
    m_ReferenceStationInfoFrame.coordinateSystemType = 0;
    m_ReferenceStationInfoFrame.coordinateX = 0;
    m_ReferenceStationInfoFrame.coordinateY = 0;
    m_ReferenceStationInfoFrame.coordinateZ = 0;
    m_mutex.unlock();
}

void GNSSWorker::processData(const QByteArray &data, const QHostAddress &, quint16)
{
    QString asciiString = QString::fromLatin1(data.constData(), data.size());
        QRegularExpression regex(R"(\$(G[BNPLA]GGA|GNGGA)[^$]+\*[0-9A-Fa-f]{2})");
        // 在清理后的字符串上进行匹配
        QRegularExpressionMatchIterator iterator = regex.globalMatch(asciiString);


        // 步骤2: 遍历所有匹配
        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            QString matchedString = match.captured(0);  // 整个匹配的字符串
              // QStringList fields = matchedString.split(',', QString::KeepEmptyParts); // 保留空字段

               gps = parseGGA(matchedString);

               owner->m_GNSStimer->start();
               emit LaunchGPS(gps);

        }


    m_mutex.lock();
  //  QString asciiString = QString::fromLatin1(data.constData(), data.size());
    stringbuffer.append(asciiString);
    m_mutex.unlock();

}

QNetworkInterface GNSSWorker::getInterfaceByIp(const QString &targetIp)
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

GpsData GNSSWorker::parseGGA(const QString &nmeaSentence)
{
        GpsData data;

        // 验证基础格式
        if(!nmeaSentence.startsWith("$GNGGA") &&
           !nmeaSentence.startsWith("$GPGGA") && !nmeaSentence.startsWith("$GBGGA")) {
            qWarning() << "Invalid GGA prefix";
            return data;
        }


        data.GPS = getGGAType(nmeaSentence);




        // 分割语句字段
        QStringList fields = nmeaSentence.split(',');
        if(fields.size() < 15) {
            qWarning() << "Incomplete GGA sentence";
            return data;
        }

        qDebug() << fields;
        if(fields[6] == "0")
        {
            data.altitude = 0.0;
            data.latitude = 0.0;
            data.longitude = 0.0;
            return data;
        }

        // 解析时间 (字段1: "hhmmss.ss")
        bool ok;
        double timeField = fields[1].toDouble(&ok);
        if(!ok) {
            qWarning() << "Invalid time format";
            return data;
        }

        // 提取UTC时间（无时区调整）
        int hours = static_cast<int>(timeField) / 10000;
        int minutes = (static_cast<int>(timeField) % 10000) / 100;
        double seconds = fmod(timeField, 100.0);
        int milliseconds = static_cast<int>((seconds - floor(seconds)) * 1000);

        // 获取当前UTC日期
        QDateTime currentUtc = QDateTime::currentDateTimeUtc();
        QDate utcDate = currentUtc.date();

        // 创建UTC时间的QDateTime对象
        QDateTime utcTime = QDateTime(
            utcDate,
            QTime(hours, minutes, static_cast<int>(seconds), milliseconds),
            Qt::UTC
        );

        // 正确转换为东八区时间
        QTimeZone east8TimeZone(8 * 3600); // UTC+8
        data.time = utcTime.toTimeZone(east8TimeZone);

        // 解析纬度 (字段2 + 字段3)
        double latDM = fields[2].toDouble(&ok);
        if(!ok) {
            qWarning() << "Invalid latitude format";
            return data;
        }

        int latDeg = static_cast<int>(latDM) / 100;
        double latMin = latDM - latDeg * 100.0;
        data.latitude = latDeg + latMin / 60.0;
        if(fields[3] == "S") data.latitude *= -1;  // 南纬为负值

        // 解析经度 (字段4 + 字段5)
        double lonDM = fields[4].toDouble(&ok);
        if(!ok) {
            qWarning() << "Invalid longitude format";
            return data;
        }

        int lonDeg = static_cast<int>(lonDM) / 100;
        double lonMin = lonDM - lonDeg * 100.0;
        data.longitude = lonDeg + lonMin / 60.0;
        if(fields[5] == "W") data.longitude *= -1;  // 西经为负值


        data.PRNCount = fields[7];
        if(!ok) {
            qWarning() << "Invalid altitude format";
            return data;
        }

        // 解析海拔高度 (字段9)
        data.altitude = fields[9].toDouble(&ok);
        if(!ok) {
            qWarning() << "Invalid altitude format";
            return data;
        }

        return data;
}

RmcData GNSSWorker::parseGNRMC(const QString &nmeaSentence)
{
    RmcData data;

        // 基础验证
        if (!nmeaSentence.startsWith("$GNRMC")) {
            qWarning() << "无效的GNRMC语句";
            return data;
        }

        // 分割字段
        QStringList fields = nmeaSentence.split(',');
        if (fields.size() < 13) {
            qWarning() << "不完整的GNRMC语句";
            return data;
        }

        // 字段解析
        try {
            // 1. 定位状态 (字段2)
            data.status = fields[2];

            // 如果状态无效，跳过其他解析
            if (data.status != "A") {
                return data;
            }

            // 2. UTC时间 (字段1)
            QString timeStr = fields[1];
            if (timeStr.length() >= 6) {
                int hours = timeStr.mid(0, 2).toInt();
                int minutes = timeStr.mid(2, 2).toInt();
                double seconds = timeStr.mid(4).toDouble();
                int secInt = static_cast<int>(seconds);
                int msec = static_cast<int>((seconds - secInt) * 1000);

                // 3. UTC日期 (字段9)
                QString dateStr = fields[9];
                if (dateStr.length() == 6) {
                    int day = dateStr.mid(0, 2).toInt();
                    int month = dateStr.mid(2, 2).toInt();
                    int year = 2000 + dateStr.mid(4, 2).toInt(); // 假设2000年后

                    QDate date(year, month, day);
                    QTime time(hours, minutes, secInt, msec);
                    data.datetime = QDateTime(date, time, Qt::UTC);
                }
            }

            // 4. 纬度解析 (字段3 + 字段4)
            if (!fields[3].isEmpty() && !fields[4].isEmpty()) {
                double latDM = fields[3].toDouble();
                int latDeg = static_cast<int>(latDM) / 100;
                double latMin = latDM - latDeg * 100.0;
                data.latitude = latDeg + latMin / 60.0;
                if (fields[4] == "S") data.latitude *= -1;
            }

            // 5. 经度解析 (字段5 + 字段6)
            if (!fields[5].isEmpty() && !fields[6].isEmpty()) {
                double lonDM = fields[5].toDouble();
                int lonDeg = static_cast<int>(lonDM) / 100;
                double lonMin = lonDM - lonDeg * 100.0;
                data.longitude = lonDeg + lonMin / 60.0;
                if (fields[6] == "W") data.longitude *= -1;
            }

            // 6. 地面速率 (字段7)
            if (!fields[7].isEmpty()) {
                data.speed = fields[7].toDouble();
            }

            // 7. 航向 (字段8)
            if (!fields[8].isEmpty()) {
                data.course = fields[8].toDouble();
            }

            // 8. 磁偏角 (字段10 + 字段11)
            if (!fields[10].isEmpty() && !fields[11].isEmpty()) {
                data.magneticVariation = fields[10] + fields[11];
            }

            // 9. 模式指示 (字段12)
            if (!fields[12].isEmpty()) {
                // 移除校验和部分
                QString modeField = fields[12].split('*').first();
                data.mode = modeField;
            }
        }
        catch (...) {
            qWarning() << "解析过程中发生异常";
        }

        return data;
}

double GNSSWorker::convertUtcToSecondsOfDay(const QString &timeStr)
{
    // 验证字符串长度：格式为 "hhmmss.ss"，总长度应为 9 个字符
       if (timeStr.length() != 9) {
           qDebug() << "错误：时间字符串长度无效。期望格式：hhmmss.ss（例如 123045.50）。";
           return -1;
       }

       // 提取小时、分钟和秒部分
       QString hourStr = timeStr.mid(0, 2);   // 前两个字符：小时
       QString minuteStr = timeStr.mid(2, 2); // 中间两个字符：分钟
       QString secondStr = timeStr.mid(4);    // 剩余字符：秒（包括小数点）

       // 转换为数值
       bool conversionOk;
       int hours = hourStr.toInt(&conversionOk);
       if (!conversionOk || hours < 0 || hours > 23) {
           qDebug() << "错误：小时部分无效。应为 00-23 的整数。";
           return -1;
       }

       int minutes = minuteStr.toInt(&conversionOk);
       if (!conversionOk || minutes < 0 || minutes > 59) {
           qDebug() << "错误：分钟部分无效。应为 00-59 的整数。";
           return -1;
       }

       double seconds = secondStr.toDouble(&conversionOk);
       if (!conversionOk || seconds < 0 || seconds >= 60) {
           qDebug() << "错误：秒部分无效。应为 00.00-59.99 的浮点数。";
           return -1;
       }

       // 计算日中秒
       double totalSeconds = hours * 3600 + minutes * 60 + seconds;
       return totalSeconds;
}

void GNSSWorker::SatparseData(const QStringList &dataFields)
{
    QVector<SatelliteInfo> satellites;
    int index = 0;
    int dataSize = dataFields.size();





 //  m_SATSINFOData.header = dataFields[index++].toInt();
    m_SATSINFOData.satNumber = dataFields[index++].toInt();

//           qDebug() << m_SATSINFOData.satNumber;
    m_SATSINFOData.version = dataFields[index++].toInt();
    m_SATSINFOData.reserve1 = dataFields[index++].toInt();
    m_SATSINFOData.reserve2 = dataFields[index++].toInt();
    m_SATSINFOData.reserve3 = dataFields[index++].toInt();
    m_SATSINFOData.frqFlag = dataFields[index++].toInt();


//    qDebug() << m_SATSINFOData.satNumber;
//    qDebug() << m_SATSINFOData.version;
//    qDebug() << m_SATSINFOData.reserve1;
//    qDebug() << m_SATSINFOData.reserve2;
//    qDebug() << m_SATSINFOData.reserve3;
//    qDebug() << m_SATSINFOData.frqFlag;




    while (index < dataSize) {
        SatelliteInfo sat;

        // 解析卫星基本信息
        sat.prn = dataFields[index++].toInt();         // PRN号
        sat.azimuth = dataFields[index++].toInt(); // 方位角（2个字节）
        sat.elevation = dataFields[index++].toInt();   // 高度角
        sat.sysStatus = dataFields[index++].toInt();   // 系统标识
        sat.snr = dataFields[index++].toInt();         // 信噪比
        sat.freqStatus = dataFields[index++].toInt();  // 频点标识
        sat.freqCount = dataFields[index++].toInt();   // 频点数量



        // 清空频点列表
        sat.freqs.clear();

        // 解析频点信息
        for (int i = 1; i < sat.freqCount; i++) {
            if (index + 3 >= dataSize) {
                qWarning() << "Insufficient data for frequency info";
                break;
            }

            FreqInfo freq;
            freq.freqNo = dataFields[index++].toInt();    // 频点编号
            freq.snr = dataFields[index++].toInt();       // 频点信噪比
            freq.status = dataFields[index++].toInt();    // 频点状态
            freq.trackState = dataFields[index++].toInt();// 跟踪状态

            sat.freqs.append(freq);

        }

        satellites.append(sat);
    }

    m_SATSINFOData.satellites.append(satellites);
}

void GNSSWorker::frameparseData(const QStringList &dataFields)
{
    int index = 0;
    int dataSize = dataFields.size();
    qDebug() <<"frameparseData: " << dataFields;

    m_ObsvmMessage.obsCount = dataFields[index++].toUInt();

    for(int i = 0 ; i < m_ObsvmMessage.obsCount ; i++)
    {
        ObsDataBlock TemporaryObsDataBlock;
        TemporaryObsDataBlock.systemFreq = dataFields[index++].toUInt();
        TemporaryObsDataBlock.prnSlot = dataFields[index++].toUInt();
        TemporaryObsDataBlock.psr = dataFields[index++].toUInt();
        TemporaryObsDataBlock.adr = dataFields[index++].toUInt();
        TemporaryObsDataBlock.psrStd = dataFields[index++].toUInt();
        TemporaryObsDataBlock.adrStd = dataFields[index++].toUInt();
        TemporaryObsDataBlock.dopp = dataFields[index++].toUInt();
        TemporaryObsDataBlock.cn0 = dataFields[index++].toUInt();
        TemporaryObsDataBlock.reserved = dataFields[index++].toUInt();
        TemporaryObsDataBlock.locktime = dataFields[index++].toUInt();
        bool ok;
        TemporaryObsDataBlock.ch_trstatus.value = dataFields[index++].toUInt(&ok, 16);
        qDebug() << QString::number(TemporaryObsDataBlock.ch_trstatus.value , 2);

        if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 0
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 0 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 3 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 11))
        {
            TemporaryObsDataBlock.Satellite_type = 0xE1;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 0
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 9 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 17))

        {
            TemporaryObsDataBlock.Satellite_type = 0xE2;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 0
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 6 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 14))

        {
            TemporaryObsDataBlock.Satellite_type = 0xE3;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 1
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 0))
        {
            TemporaryObsDataBlock.Satellite_type = 0xE4;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 1
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 5 ))
        {
            TemporaryObsDataBlock.Satellite_type = 0xE5;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 1
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 6 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 7))
        {
            TemporaryObsDataBlock.Satellite_type = 0xE6;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 4
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 0 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 4 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 8 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 23))
        {
            TemporaryObsDataBlock.Satellite_type = 0xF1;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 4
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 5 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 17||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 12||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 28||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 13))

        {
            TemporaryObsDataBlock.Satellite_type = 0xF2;
        }
        else if(TemporaryObsDataBlock.ch_trstatus.bits.satellite_system == 4
                && (TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 6 ||
                    TemporaryObsDataBlock.ch_trstatus.bits.signal_type == 21))
        {
            TemporaryObsDataBlock.Satellite_type = 0xF3;
        }
        m_ObsvmMessage.obsData.append(TemporaryObsDataBlock);
    }


    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();  // 获取当前UTC时间

    // 计算GPS系统
    TimeResult gpsResult = calculateTimeWeekAndSecond(SatelliteSystem::GPS, currentDateTime);

    // 计算GLONASS系统
    TimeResult glonassResult = calculateTimeWeekAndSecond(SatelliteSystem::GLONASS, currentDateTime);

    // 计算BDS系统
    TimeResult bdsResult = calculateTimeWeekAndSecond(SatelliteSystem::BDS, currentDateTime);

    QMap<int,int>valueCountMap;  // 使用 QMap 存储值和计数
    for (int i = 0; i < m_ObsvmMessage.obsData.size(); ++i)
    {
        int prnSlot = m_ObsvmMessage.obsData[i].prnSlot;
        if (valueCountMap.contains(prnSlot))
        {
            valueCountMap[prnSlot]++;  // 递增计数
        }
        else
        {
            valueCountMap.insert(prnSlot, 1);  // 首次出现
        }
    }

    QVector<int> vec;
    int flag = 0;  //第几个ascii解析
    //ChildFrame childframe;

    ChildFrame m_ChildFrame_E1;
    ChildFrame m_ChildFrame_E2;
    ChildFrame m_ChildFrame_E3;
    ChildFrame m_ChildFrame_E4;
    ChildFrame m_ChildFrame_E5;
    ChildFrame m_ChildFrame_E6;
    ChildFrame m_ChildFrame_E7;
    ChildFrame m_ChildFrame_E8;
    ChildFrame m_ChildFrame_E9;

    while(flag < m_ObsvmMessage.obsData.size())
    {


         if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xE1)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E1.channels.append(T_channel);
         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xE2)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E2.channels.append(T_channel);

         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xE3)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E3.channels.append(T_channel);

         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xE4)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E4.channels.append(T_channel);

         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xE5)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E5.channels.append(T_channel);

         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xE6)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E6.channels.append(T_channel);

         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xF1)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E7.channels.append(T_channel);

         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xF2)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E8.channels.append(T_channel);

         }
         else if(m_ObsvmMessage.obsData[flag].Satellite_type == 0xF3)
         {
             ChannelData T_channel;
             T_channel.satelliteNumber = m_ObsvmMessage.obsData[flag].prnSlot;
             T_channel.frequencyNumber = m_ObsvmMessage.obsData[flag].systemFreq;
             T_channel.Cseudorange = m_ObsvmMessage.obsData[flag].psrStd;
             T_channel.Pseudorange = 0x00;
             T_channel.carrierDoppler = m_ObsvmMessage.obsData[flag].dopp;
             T_channel.carrierSNR = m_ObsvmMessage.obsData[flag].cn0 * 25;
             T_channel.Ctracking_time = m_ObsvmMessage.obsData[flag].locktime;
             m_ChildFrame_E9.channels.append(T_channel);

         }

         flag++;
    }


    if(!m_ChildFrame_E1.channels.isEmpty())
    {
        m_ChildFrame_E1.subframeType = 0xE1;
        m_ChildFrame_E1.subframeSyncCode = tongbuCount;
        m_ChildFrame_E1.validChannelCount = m_ChildFrame_E1.channels.size();
        m_ChildFrame_E1.time1 = gpsResult.weekOrDays;
        m_ChildFrame_E1.time2 = gpsResult.second;
        m_ChildFrame_E1.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E1));
        m_SubFrame.childframe.append(m_ChildFrame_E1);
    }
    if(!m_ChildFrame_E2.channels.isEmpty())
    {
        m_ChildFrame_E2.subframeType = 0xE2;
        m_ChildFrame_E2.subframeSyncCode = tongbuCount;
        m_ChildFrame_E2.validChannelCount = m_ChildFrame_E2.channels.size();
        m_ChildFrame_E2.time1 = gpsResult.weekOrDays;
        m_ChildFrame_E2.time2 = gpsResult.second;
        m_ChildFrame_E2.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E2));
        m_SubFrame.childframe.append(m_ChildFrame_E2);
    }
    if(!m_ChildFrame_E3.channels.isEmpty())
    {
        m_ChildFrame_E3.subframeType = 0xE3;
        m_ChildFrame_E3.subframeSyncCode = tongbuCount;
        m_ChildFrame_E3.validChannelCount = m_ChildFrame_E3.channels.size();
        m_ChildFrame_E3.time1 = gpsResult.weekOrDays;
        m_ChildFrame_E3.time2 = gpsResult.second;
        m_ChildFrame_E3.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E3));
        m_SubFrame.childframe.append(m_ChildFrame_E3);
    }
    if(!m_ChildFrame_E4.channels.isEmpty())
    {
        m_ChildFrame_E4.subframeType = 0xE4;
        m_ChildFrame_E4.subframeSyncCode = tongbuCount;
        m_ChildFrame_E4.validChannelCount = m_ChildFrame_E4.channels.size();
        m_ChildFrame_E4.time1 = glonassResult.weekOrDays;
        m_ChildFrame_E4.time2 = glonassResult.second;
        m_ChildFrame_E4.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E4));
        m_SubFrame.childframe.append(m_ChildFrame_E4);
    }
    if(!m_ChildFrame_E5.channels.isEmpty())
    {
        m_ChildFrame_E5.subframeType = 0xE5;
        m_ChildFrame_E5.subframeSyncCode = tongbuCount;
        m_ChildFrame_E5.validChannelCount = m_ChildFrame_E5.channels.size();
        m_ChildFrame_E5.time1 = glonassResult.weekOrDays;
        m_ChildFrame_E5.time2 = glonassResult.second;
        m_ChildFrame_E5.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E5));
        m_SubFrame.childframe.append(m_ChildFrame_E5);
    }
    if(!m_ChildFrame_E6.channels.isEmpty())
    {
        m_ChildFrame_E6.subframeType = 0xE6;
        m_ChildFrame_E6.subframeSyncCode = tongbuCount;
        m_ChildFrame_E6.validChannelCount = m_ChildFrame_E6.channels.size();
        m_ChildFrame_E6.time1 = glonassResult.weekOrDays;
        m_ChildFrame_E6.time2 = glonassResult.second;
        m_ChildFrame_E6.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E6));
        m_SubFrame.childframe.append(m_ChildFrame_E6);
    }
    if(!m_ChildFrame_E7.channels.isEmpty())
    {
        m_ChildFrame_E7.subframeType = 0xF1;
        m_ChildFrame_E7.subframeSyncCode = tongbuCount;
        m_ChildFrame_E7.validChannelCount = m_ChildFrame_E7.channels.size();
        m_ChildFrame_E7.time1 = bdsResult.weekOrDays;
        m_ChildFrame_E7.time2 = bdsResult.second;
        m_ChildFrame_E7.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E7));
        m_SubFrame.childframe.append(m_ChildFrame_E7);
    }
    if(!m_ChildFrame_E8.channels.isEmpty())
    {
        m_ChildFrame_E8.subframeType = 0xF2;
        m_ChildFrame_E8.subframeSyncCode = tongbuCount;
        m_ChildFrame_E8.validChannelCount = m_ChildFrame_E8.channels.size();
        m_ChildFrame_E8.time1 = bdsResult.weekOrDays;
        m_ChildFrame_E8.time2 = bdsResult.second;
        m_ChildFrame_E8.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E8));
        m_SubFrame.childframe.append(m_ChildFrame_E8);
    }
    if(!m_ChildFrame_E9.channels.isEmpty())
    {
        m_ChildFrame_E9.subframeType = 0xF3;
        m_ChildFrame_E9.subframeSyncCode = tongbuCount;
        m_ChildFrame_E9.validChannelCount = m_ChildFrame_E9.channels.size();
        m_ChildFrame_E9.time1 = bdsResult.weekOrDays;
        m_ChildFrame_E9.time2 = bdsResult.second;
        m_ChildFrame_E9.crcChecksum = crc32(childFrameToByteArray(m_ChildFrame_E9));
        m_SubFrame.childframe.append(m_ChildFrame_E9);
    }

    tongbuCount++;


    printSubFrame(m_SubFrame);

    m_SubFrame.frame_number = m_SubFrame.childframe.size();

    QByteArray Referencearray;
    m_gnss_generic_frame_header_t.frame_type = 1;
    Referencearray.append(reinterpret_cast<const char*>(&m_gnss_generic_frame_header_t)  ,sizeof(gnss_generic_frame_header_t));

    QByteArray Referencearra2 = serializeSubFrameToQByteArray(m_SubFrame);

    Referencearray.append(Referencearra2);
    QByteArray crcArray = extractMiddlePart(Referencearray);
    quint32 m_crc32 = crc32(crcArray);
    m_FrameTail.crc = qToLittleEndian(m_crc32);
    Referencearray.append(reinterpret_cast<const char*>(&m_FrameTail) ,  sizeof(FrameTail));


    owner->udpManager->senderSocket->writeDatagram(Referencearray, QHostAddress("224.1.1.4"), 10006);



    m_ObsvmMessage.obsData.clear();
    m_SubFrame.childframe.clear();

}

quint32 GNSSWorker::crc32(const QByteArray &array)
{
    quint32 crc = 0xFFFFFFFF;                     // 初始值
     const quint8 *addr = reinterpret_cast<const quint8*>(array.constData());
     int num = array.size();

     for (; num > 0; num--) {
         quint8 byte = *addr++;
         byte = reverse8(byte);                    // 字节反转
         crc ^= (static_cast<quint32>(byte) << 24); // 与crc高8位异或

         for (int i = 0; i < 8; i++) {             // 循环处理8位
             if (crc & 0x80000000) {               // 最高位为1
                 crc = (crc << 1) ^ 0x04C11DB7;    // 左移后异或多项式
             } else {
                 crc <<= 1;                        // 直接左移
             }
         }
     }

     crc = reverse32(crc);                         // 反转32位
     crc ^= 0xFFFFFFFF;                            // 异或结果值
     return crc;
}

quint8 GNSSWorker::reverse8(quint8 data)
{
    quint8 i;
    quint8 temp = 0;
    for (i = 0; i < 8; i++)	    				// 8 bit反转
        temp |= ((data >> i) & 0x01) << (7 - i);
    return temp;
}

quint32 GNSSWorker::reverse32(quint32 data)
{
    quint8 i;
    quint32 temp = 0;
    for (i = 0; i < 32; i++)					// 32 bit反转
        temp |= ((data >> i) & 0x01) << (31 - i);
    return temp;
}

bool GNSSWorker::getBit(quint8 byte, quint8 position)
{
    return (byte >> position) & 0x1;
}

QByteArray GNSSWorker::extractMiddlePart(const QByteArray &data)
{
    // 使用mid()方法提取指定部分
    return data.mid(4);
}

bool GNSSWorker::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

QDate GNSSWorker::findLastLeapYear(const QDate &date)
{
    int year = date.year();
        // 从当前年份开始向前查找，直到找到闰年
        while (!isLeapYear(year)) {
            --year;
        }
        return QDate(year, 1, 1);  // 返回该闰年的1月1日
}

TimeResult GNSSWorker::calculateTimeWeekAndSecond(SatelliteSystem system, const QDateTime &inputDateTime)
{
    TimeResult result = {0, 0};
        qint64 secondsInWeek = 604800;  // 一周的秒数：7 * 24 * 3600
        qint64 secondsInDay = 86400;    // 一天的秒数：24 * 3600

        // 确保输入日期时间为UTC时区，因为卫星系统时间通常基于UTC
        QDateTime utcDateTime = inputDateTime.toUTC();

        switch (system) {
        case SatelliteSystem::GPS: {
            // GPS时间起点：1980年1月6日 00:00:00 UTC
            QDateTime gpsEpoch(QDate(1980, 1, 6), QTime(0, 0, 0), Qt::UTC);
            qint64 secondsSinceEpoch = gpsEpoch.secsTo(utcDateTime);
            if (secondsSinceEpoch < 0) {
                qWarning() << "GPS时间计算错误：输入时间早于GPS时间起点。";
                return result;
            }
            result.weekOrDays = secondsSinceEpoch / secondsInWeek;  // 时间周（周数）
            result.second = (secondsSinceEpoch % secondsInWeek) * 1000;       // 周秒（周内秒数）
            break;
        }
        case SatelliteSystem::GLONASS: {
            // GLONASS：计算自最近一次闰年至今的累积日和日内秒
            QDate lastLeapYearStart = findLastLeapYear(utcDateTime.date());
            QDateTime glonassEpoch(lastLeapYearStart, QTime(0, 0, 0), Qt::UTC);
            qint64 secondsSinceLeapYear = glonassEpoch.secsTo(utcDateTime);
            if (secondsSinceLeapYear < 0) {
                // 这种情况理论上不会发生，因为最近一次闰年早于或等于当前日期
                qWarning() << "GLONASS时间计算错误：输入时间早于最近一次闰年。";
                return result;
            }
            result.weekOrDays = secondsSinceLeapYear / secondsInDay;  // 时间周（累积日数）
            result.second = utcDateTime.time().hour() * 3600 +
                            utcDateTime.time().minute() * 60 +
                            utcDateTime.time().second() * 1000;  // 周秒（日内累积秒数）
            break;
        }
        case SatelliteSystem::BDS: {
            // BDS时间起点：2006年1月1日 00:00:00 UTC
            QDateTime bdsEpoch(QDate(2006, 1, 1), QTime(0, 0, 0), Qt::UTC);
            qint64 secondsSinceEpoch = bdsEpoch.secsTo(utcDateTime);
            if (secondsSinceEpoch < 0) {
                qWarning() << "BDS时间计算错误：输入时间早于BDS时间起点。";
                return result;
            }
            result.weekOrDays = secondsSinceEpoch / secondsInWeek;  // 时间周（周数）
            result.second = (secondsSinceEpoch % secondsInWeek) * 1000;       // 周秒（周内秒数）
            break;
        }
        default:
            qWarning() << "未知卫星系统。";
            break;
        }

        return result;
}

QByteArray GNSSWorker::serializeSubFrameToQByteArray(const SubFrame &subFrame)
{
    QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::BigEndian);  // 设置大端序，根据你的需求调整

        // 1. 序列化 frame_number
        stream << subFrame.frame_number;

        // 2. 遍历并序列化每个ChildFrame
        for (const auto& childFrame : subFrame.childframe)
        {
            // 序列化ChildFrame的固定字段
            stream << childFrame.frameHeader;
            stream << childFrame.subframeType;
            stream << childFrame.subframeSyncCode;
            stream << childFrame.validChannelCount;
            stream << childFrame.time1;
            stream << childFrame.time2;
            stream << childFrame.reserved1;
            stream << childFrame.reserved2;

            // 序列化channels数组
            quint8 channelCount = childFrame.channels.size();
            for (quint8 i = 0; i < channelCount; ++i)
            {
                const ChannelData& channel = childFrame.channels[i];

                // 使用QDataStream直接写入各个字段
                stream << channel.satelliteNumber;
                stream.writeRawData(reinterpret_cast<const char*>(&channel.frequencyNumber), 1);
                stream << channel.Cseudorange;
                stream << channel.Pseudorange;
                stream << channel.carrierDoppler;
                stream.writeRawData(reinterpret_cast<const char*>(&channel.carrierSNR), 1);
                stream << channel.Ctracking_time;
            }

            // 序列化CRC和帧尾
            stream << childFrame.crcChecksum;
            stream << childFrame.frameTail1;
            stream << childFrame.frameTail2;
        }

        return byteArray;
}

QByteArray GNSSWorker::childFrameToByteArray(const ChildFrame &frame)
{
    QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);

        // 设置小端字节序
        stream.setByteOrder(QDataStream::LittleEndian);

        // 写入帧头
        stream << frame.frameHeader;

        // 写入子帧类型
        stream << frame.subframeType;

        // 写入子帧同步码
        stream << frame.subframeSyncCode;

        // 写入有效通道数
        stream << frame.validChannelCount;

        // 写入时间1
        stream << frame.time1;

        // 写入时间2
        stream << frame.time2;

        // 写入保留字节
        stream << frame.reserved1;
        stream << frame.reserved2;

        // 写入通道数据
        for (int i = 0; i < frame.channels.size(); ++i) {
            const ChannelData& channel = frame.channels[i];

            // 写入卫星号
            stream << channel.satelliteNumber;

            // 写入卫星频率编号
            stream << static_cast<int8_t>(channel.frequencyNumber);

            // 写入C码伪距
            stream << channel.Cseudorange;

            // 写入P码伪距
            stream << channel.Pseudorange;

            // 写入瞬时载波多普勒
            stream << channel.carrierDoppler;

            // 写入载波信噪比
            stream << channel.carrierSNR;

            // 写入连续跟踪时间
            stream << channel.Ctracking_time;
        }

        return byteArray;
}

QByteArray GNSSWorker::byteArrayToSatelliteParams(QVector<Channel1SatelliteParams> &params)
{
    if (params.isEmpty()) {
            return QByteArray();
        }

        // 计算总大小
        int elementSize = sizeof(Channel1SatelliteParams);
        int totalSize = elementSize * params.size();

        // 创建 QByteArray
        QByteArray byteArray(totalSize, 0);

        // 使用内存拷贝
        char* data = byteArray.data();
        for (int i = 0; i < params.size(); ++i) {
            const Channel1SatelliteParams& param = params[i];
            char* dest = data + (i * elementSize);
            memcpy(dest, &param, elementSize);
        }

        return byteArray;
}

quint32 GNSSWorker::calculateChildFrameSize(const ChildFrame &childFrame)
{
    // 固定部分大小
        const quint32 fixedSize = 24; // 如上述计算的固定字段总和

        // 通道数据部分大小
        const quint32 channelDataSize = 16; // 每个 ChannelData 的大小
        const quint32 channelsSize = childFrame.channels.size() * channelDataSize;

        return fixedSize + channelsSize;
}

quint32 GNSSWorker::calculateSubFrameSize(const SubFrame &subFrame)
{
    // frame_number 字段大小
        quint32 totalSize = 1;

        // 遍历所有子帧，累加大小
        for (const ChildFrame& childFrame : subFrame.childframe) {
            totalSize += calculateChildFrameSize(childFrame);
        }

        return totalSize;
}

void GNSSWorker::printSubFrame(const SubFrame &subFrame)
{
    qDebug() << "帧数量:" << static_cast<int>(subFrame.frame_number);
        qDebug() << "Number of ChildFrames:" << subFrame.childframe.size();
        for (int i = 0; i < subFrame.childframe.size(); ++i) {
            qDebug() << "ChildFrame" << i << ":";
            printChildFrame(subFrame.childframe[i]);
        }
}

void GNSSWorker::printChildFrame(const ChildFrame &frame)
{
        qDebug() << "  Frame Header:" << QString("0x%1").arg(frame.frameHeader, 2, 16, QChar('0')).toUpper();
        qDebug() << "  Subframe Type:" << static_cast<int>(frame.subframeType);
        qDebug() << "  Subframe Sync Code:" << static_cast<int>(frame.subframeSyncCode);
        qDebug() << "  Valid Channel Count:" << static_cast<int>(frame.validChannelCount);
        qDebug() << "  Time1:" << frame.time1;
        qDebug() << "  Time2:" << frame.time2 << " (0.1μs)";
        qDebug() << "  Reserved1:" << static_cast<int>(frame.reserved1);
        qDebug() << "  Reserved2:" << static_cast<int>(frame.reserved2);

        qDebug() << "  Channels (count:" << frame.channels.size() << "):";
        for (int i = 0; i < frame.channels.size(); ++i) {
            qDebug() << "    Channel" << i << ":";
            printChannelData(frame.channels[i]);
        }

        qDebug() << "  CRC Checksum:" << frame.crcChecksum;
        qDebug() << "  Frame Tail1:" << QString("0x%1").arg(frame.frameTail1, 2, 16, QChar('0')).toUpper();
        qDebug() << "  Frame Tail2:" << QString("0x%1").arg(frame.frameTail2, 2, 16, QChar('0')).toUpper();
}

void GNSSWorker::printChannelData(const ChannelData &channel)
{
        qDebug() << "    Satellite Number:" << channel.satelliteNumber;
        // frequencyNumber 是 int8_t（有符号），转换为 int 打印
        qDebug() << "    Frequency Number:" << static_cast<int>(channel.frequencyNumber);
        qDebug() << "    C Pseudorange:" << channel.Cseudorange << " (0.01m)";
        qDebug() << "    Pseudorange:" << channel.Pseudorange << " (0.01m)";
        // carrierDoppler 是 int32_t（有符号），直接打印
        qDebug() << "    Carrier Doppler:" << channel.carrierDoppler << " (0.01Hz)";
        // carrierSNR 是 uint8_t，转换为 int 打印
        qDebug() << "    Carrier SNR:" << static_cast<int>(channel.carrierSNR) << " (0.25dBHz)";
}

void GNSSWorker::printObsvmMessage(const ObsvmMessage &msg)
{
    qDebug() << "========== OBSVM 消息数据 ==========";
        qDebug() << "观测信息个数:" << msg.obsCount;
        qDebug() << "===================================";

        // 打印每个观测数据块
        for (int i = 0; i < msg.obsData.size(); ++i)
        {
            const ObsDataBlock& obs = msg.obsData[i];

            qDebug() << QString("\n--- 观测数据块 %1 ---").arg(i + 1);
            qDebug() << "  GLONASS卫星频点号:" << obs.systemFreq;
            qDebug() << "  卫星PRN号:" << obs.prnSlot;
            qDebug().nospace() << "  码伪距测量值: " << QString::number(obs.psr, 'f', 6) << " m";
            qDebug().nospace() << "  载波相位: " << QString::number(obs.adr, 'f', 6) << " 度";
            qDebug() << "  码伪距标准差:" << (obs.psrStd / 100.0) << "m";
            qDebug() << "  载波相位标准差:" << (obs.adrStd / 10000.0) << "度";
            qDebug().nospace() << "  瞬时多普勒: " << QString::number(obs.dopp, 'f', 2) << " Hz";
            qDebug() << "  载噪比:" << (obs.cn0 / 100.0) << "dB-Hz";
            qDebug() << "  保留字段: 0x" <<  obs.reserved;
            qDebug().nospace() << "  连续跟踪时间: " << QString::number(obs.locktime, 'f', 3) << " s";
            qDebug() << "  跟踪状态: 0x" <<  obs.ch_trstatus.value;



        qDebug() << "\n===================================";
        qDebug() << "CRC32校验值: 0x"
                 << QString("%1").arg(msg.crc32, 8, 16, QLatin1Char('0'));
        qDebug().nospace() << "语句结束符: 0x" << QString::number(static_cast<uint8_t>(msg.endMarker), 16)
                          << " ('" << (QChar(msg.endMarker).isPrint() ? QChar(msg.endMarker) : QChar('.'))
                          << "')";
        qDebug() << "===================================";

        // 验证数据
        qDebug() << "\n数据验证：";
        qDebug() << "obsData向量大小:" << msg.obsData.size();
        if (msg.obsData.size() != static_cast<int>(msg.obsCount))
        {
            qDebug() << "警告: obsCount与obsData大小不匹配！";
        }

        // 打印结构体大小信息
        qDebug() << "ObsDataBlock结构体大小:" << ObsDataBlock::size() << "字节";
}

}

QString GNSSWorker::getGGAType(const QString &str)
{
    if (str.contains("GNGGA")) return "GNGGA";
      if (str.contains("GPGGA")) return "GPGGA";
      if (str.contains("GBGGA")) return "GBGGA";
      return QString();
}


void GNSSWorker::setOwner(MainWindow *mainWindow)
{
    owner = mainWindow;
}
