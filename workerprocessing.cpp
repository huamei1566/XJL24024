#include "workerprocessing.h"
#include "mainwindow.h"

WorkerProcessing::WorkerProcessing(/*const QString &filePath,const QString &filePath2 ,*/ QObject *parent)
    : QObject(parent)
{

    Buffertr1[0] = new QByteArray();
    Buffertr1[0]->reserve(5 * 1024 * 1024);

    Buffertr1[1] = new QByteArray();
    Buffertr1[1]->reserve(5 * 1024 * 1024);

    Buffertr2[0] = new QByteArray();
    Buffertr2[0]->reserve(5 * 1024 * 1024);

    Buffertr2[1] = new QByteArray();
    Buffertr2[1]->reserve(5 * 1024 * 1024);

    Buffer1 = new QByteArray();
    Buffer1->reserve(5 * 1024 * 1024);

    Buffer2 = new QByteArray();
    Buffer2->reserve(5 * 1024 * 1024);

    testBuffer = new QByteArray();
    testBuffer->resize(10 * 1024 * 1024);


    udpender = new QUdpSocket();
    udpender->bind(QHostAddress("192.168.0.100"), 10004,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress );

//    QMutexLocker locker(&m_mutex);

//    // 在初始化时打开文件
//    if (!ensureFileOpen()) {
//        qWarning() << "[WorkerProcessing] 文件打开失败";
//    }

//    if (!ensureFileOpen2()) {
//        qWarning() << "[WorkerProcessing] 文件打开失败";
//    }






}

WorkerProcessing::~WorkerProcessing()
{
    closeFile();
    qDebug() << "[WorkerProcessing] 对象销毁";
}

bool WorkerProcessing::isReady() const
{
    QMutexLocker locker(&m_mutex);
    return m_file.isOpen();
}

qint64 WorkerProcessing::currentPosition() const
{
    QMutexLocker locker(&m_mutex);
    return m_file.isOpen() ? m_file.pos() : -1;
}

qint64 WorkerProcessing::fileSize() const
{
    QMutexLocker locker(&m_mutex);
    return m_file.isOpen() ? m_file.size() : -1;
}

void WorkerProcessing::FillBuffer1()
{

        while(Buffer1->size() < 5 * 1024 * 1024)
        {

            if (m_file.atEnd()) break;

                    // 读取一个块
                    QByteArray chunk = m_file.read(CHUNK_READ_SIZE);

                    if (chunk.size() < CHUNK_READ_SIZE) {
                        // 处理不完整的块
                        if (chunk.size() > CHUNK_HEADER_SIZE) {
                            // 有效数据
                            QByteArray validData = chunk.mid(CHUNK_HEADER_SIZE);
                            Buffer1->append(validData);


                        }
                        break; // 文件结束
                    }

                    // 去掉前8字节，添加有效数据
                    QByteArray validData(chunk.constData() + CHUNK_HEADER_SIZE, VALID_DATA_PER_CHUNK);
                    Buffer1->append(validData);


      // Buffer1->append(m_file.read(6 * 1024 * 1024));


        }


}

void WorkerProcessing::FillBuffer2()
{

        while(Buffer2->size() < 5 * 1024 * 1024)
        {

            if (m_file2.atEnd()) break;

                    // 读取一个块
                    QByteArray chunk = m_file2.read(CHUNK_READ_SIZE2);

                    if (chunk.size() < CHUNK_READ_SIZE2) {
                        // 处理不完整的块
                        if (chunk.size() > CHUNK_HEADER_SIZE2) {
                            // 有效数据
                            QByteArray validData = chunk.mid(CHUNK_HEADER_SIZE2);
                            Buffer2->append(validData);


                        }
                        break; // 文件结束
                    }

                    // 去掉前8字节，添加有效数据
                    QByteArray validData(chunk.constData() + CHUNK_HEADER_SIZE2, VALID_DATA_PER_CHUNK2);
                    Buffer2->append(validData);


    //   Buffer2->append(m_file.read(6 * 1024 * 1024));


        }


}

//void WorkerProcessing::FillBuffer()
//{
//    //QMutexLocker locker(&m_mutex);

//    if(Buffer->size() < 5 * 1024 * 1024)
//    {
//        while(Buffer->size() < 10 * 1024 * 1024)
//        {

//            if (m_file.atEnd()) break;

//                    // 读取一个块
//                    QByteArray chunk = m_file.read(CHUNK_READ_SIZE);

//                    if (chunk.size() < CHUNK_READ_SIZE) {
//                        // 处理不完整的块
//                        if (chunk.size() > CHUNK_HEADER_SIZE) {
//                            // 有效数据
//                            QByteArray validData = chunk.mid(CHUNK_HEADER_SIZE);
//                            Buffer->append(validData);


//                        }
//                        break; // 文件结束
//                    }

//                    // 去掉前8字节，添加有效数据
//                    QByteArray validData(chunk.constData() + CHUNK_HEADER_SIZE, VALID_DATA_PER_CHUNK);
//                    Buffer->append(validData);


////       Buffer->append(m_file.read(6 * 1024 * 1024));


//        }
//    }

//}

void WorkerProcessing::setOwner(MainWindow *mainwindow)
{
    owner = mainwindow;
}

void WorkerProcessing::setTestig(int i)
{
    testig = i;
}

void WorkerProcessing::setmofei1_ig(bool t_mofei1_ig)
{
    mofei1_ig  = t_mofei1_ig;
}

void WorkerProcessing::setmofei2_ig(bool t_mofei2_ig)
{
    mofei2_ig  = t_mofei2_ig;
}



void WorkerProcessing::read_tx1_buffer_capacity(int bigreadandsender1 ,int biaoz)
{
    QMutexLocker locker(&owner->mofei_mutex);


    // 读取数据
    //readAndSendData(bigreadandsender1 , 10002);
     int dataCount =  qMin(bigreadandsender1 ,SIZE_SIZE );

    //qDebug() << testBuffer->left(dataCount).size();
    emit dataRead(testBuffer->left(dataCount), 10002);

    //udpender->writeDatagram(testBuffer->left(dataCount) , QHostAddress("224.1.1.4") , 10002);

    emit Refreshprogress1(m_totalBytesRead);

    //FillBuffer();

}

void WorkerProcessing::read_tx2_buffer_capacity(int bigreadandsender1 , int biaoz)
{
    QMutexLocker locker(&owner->mofei_mutex);




    // 读取数据
    //readAndSendData(bigreadandsender1 , 10003);

    int dataCount =  qMin(bigreadandsender1 ,SIZE_SIZE );


    emit dataRead(testBuffer->left(dataCount), 10003);

    //udpender->writeDatagram(testBuffer->left(dataCount) , QHostAddress("224.1.1.4") , 10003);

    emit Refreshprogress2(m_totalBytesRead);

    //FillBuffer();

}

void WorkerProcessing::on_read_buffer(int bigreadandsender1, int biaoz, int bigreadandsender2, int biaoz2)
{

    qDebug() << biaoz <<" " << biaoz2;

    int dataCount =  qMin(bigreadandsender1 ,SIZE_SIZE );
    int dataCount2 =  qMin(bigreadandsender2 ,SIZE_SIZE );

    if(mofei1_ig == true)
    {
        if(mofei1wenjian == 1)
        {
           QByteArray data;
           data.append(static_cast<quint8>(itext1));
           data.append(Buffer1->left(dataCount));
           udpender->writeDatagram(data , QHostAddress("224.1.1.4") , 10002);
           Buffer1->remove(0 , dataCount);
           m_totalBytesRead += dataCount;
           itext1++;
           emit Refreshprogress1(m_totalBytesRead);
        }
//        else if(mofei1wenjian == 2 && itext1 != 0 && biaoz == itext1 - 1)
//        {
//           QByteArray data;
//           data.append(static_cast<quint8>(itext1));
//           data.append(Buffer1->left(dataCount));
//           udpender->writeDatagram(Buffer1->left(dataCount) , QHostAddress("224.1.1.4") , 10002);
//           Buffer1->remove(0 , dataCount);
//           m_totalBytesRead += dataCount;
//           itext1++;
//           emit Refreshprogress1(m_totalBytesRead);
//        }
//        else if(itext1 == 0)
//        {
//            itext1++;
//        }
//        else if(itext1 == 1)
//        {
//            QByteArray data;
//            data.append(static_cast<quint8>(itext1));
//            data.append(Buffer1->left(dataCount));
//            udpender->writeDatagram(data , QHostAddress("224.1.1.4") , 10002);
//            Buffer1->remove(0 , dataCount);
//            m_totalBytesRead += dataCount;
//            itext1++;
//            emit Refreshprogress1(m_totalBytesRead);
//        }
    }




    if(mofei2_ig == true)
    {
     if(mofei2wenjian == 1)
        {
            QByteArray data;
            data.append(static_cast<quint8>(itext2));
            data.append(Buffer1->left(dataCount));
            udpender->writeDatagram(Buffer2->left(dataCount2) , QHostAddress("224.1.1.4") , 10003);
            Buffer2->remove(0 , dataCount2);
            m_totalBytesRead2 += dataCount2;
            itext2++;
            emit Refreshprogress2(m_totalBytesRead2);
        }
//     else if(mofei2wenjian == 2 && itext2 != 0 && biaoz == itext2 - 1)
//     {
//            QByteArray data;
//            data.append(static_cast<quint8>(itext2));
//            data.append(Buffer1->left(dataCount));
//            udpender->writeDatagram(Buffer2->left(dataCount2) , QHostAddress("224.1.1.4") , 10003);
//            Buffer2->remove(0 , dataCount2);
//            m_totalBytesRead2 += dataCount2;
//            itext2++;
//            emit Refreshprogress2(m_totalBytesRead2);
//     }
//     else if(itext2 == 0)
//     {
//         itext2++;
//     }
//     else if(itext2 == 1)
//     {
//         QByteArray data;
//         data.append(static_cast<quint8>(itext2));
//         data.append(Buffer1->left(dataCount));
//         udpender->writeDatagram(data , QHostAddress("224.1.1.4") , 10002);
//         Buffer1->remove(0 , dataCount);
//         m_totalBytesRead += dataCount;
//         itext2++;
//         emit Refreshprogress1(m_totalBytesRead);
//     }
    }


//    else if()
//    {
//       udpender->writeDatagram(Buffer1->left(dataCount) , QHostAddress("224.1.1.4") , 10002);
//       udpender->writeDatagram(Buffer2->left(dataCount2) , QHostAddress("224.1.1.4") , 10003);
//       m_totalBytesRead += dataCount;
//       m_totalBytesRead2 += dataCount2;
//       emit Refreshprogress1(m_totalBytesRead);
//       emit Refreshprogress2(m_totalBytesRead2);

//       Buffer1->remove(0 , dataCount);
//       Buffer2->remove(0 , dataCount2);
//    }


    FillBuffer1();
    FillBuffer2();





}

void WorkerProcessing::resetPosition()
{
    QMutexLocker locker(&m_mutex);

    if (m_file.isOpen()) {
        if (m_file.seek(0)) {
            qDebug() << "[WorkerProcessing] 文件位置已重置到开头";
        } else {
            emit errorOccurred("无法重置文件位置");
        }
    }
}

void WorkerProcessing::closeFile()
{
    QMutexLocker locker(&m_mutex);

    if (m_file.isOpen()) {
        m_file.close();
        qDebug() << "[WorkerProcessing] 文件已关闭";
    }
}

bool WorkerProcessing::ensureFileOpen()
{
    if (m_file.isOpen()) return true;

    m_file.setFileName(m_filePath);
    if (!m_file.exists()) {
        qWarning() << "[WorkerProcessing] 文件不存在:" << m_filePath;
        return false;
    }

    if (!m_file.open(QIODevice::ReadOnly)) {
        qWarning() << "[WorkerProcessing] 无法打开文件:" << m_file.errorString();
        return false;
    }

    qDebug() << "[WorkerProcessing] 文件已打开, 大小:" << m_file.size() << "字节";
    return true;
}

bool WorkerProcessing::ensureFileOpen2()
{
    if (m_file2.isOpen()) return true;

    m_file2.setFileName(m_filePath2);
    if (!m_file2.exists()) {
        qWarning() << "[WorkerProcessing] 文件不存在:" << m_filePath2;
        return false;
    }

    if (!m_file2.open(QIODevice::ReadOnly)) {
        qWarning() << "[WorkerProcessing] 无法打开文件:" << m_file2.errorString();
        return false;
    }

    qDebug() << "[WorkerProcessing] 文件已打开, 大小:" << m_file2.size() << "字节";
    return true;
}

void WorkerProcessing::setfilepath1(QString filepath)
{
    m_filePath = filepath;
}

void WorkerProcessing::setfilepath2(QString filepath)
{
    m_filePath2 = filepath;
}



void WorkerProcessing::readAndSendData(int byteCount , int portvalue)
{
//    // 读取数据 itext
//    int dataCount =  qMin(byteCount ,SIZE_SIZE );

//    emit dataCountsize(Buffer1->size());

//    QByteArray data;
//    data.append(static_cast<quint8>(itext++));

//    if(Buffer1->size() < dataCount)
//      dataCount =  Buffer1->size();




//    data.append(Buffer1->left(dataCount));

//    qint64 bytesRead = data.size();
//    //qint64 newPosition = m_file.pos();
//    m_totalBytesRead += bytesRead;

//    // 检查读取结果
//    if (bytesRead <= 0) {
//        qDebug() << ("读取失败: " + m_file.errorString());
//        return;
//    }


//    emit dataRead(data, portvalue);
//    Buffer1->remove(0 , dataCount);



}
