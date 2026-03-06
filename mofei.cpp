#include "mofei.h"

#include "mainwindow.h"

SharedBuffer::SharedBuffer()
{
    buffer.reserve(BUFFER_SIZE + 2048);
}

quint32 SharedBuffer::crc32(const QByteArray &array)
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

quint8 SharedBuffer::reverse8(quint8 data)
{
    quint8 i;
    quint8 temp = 0;
    for (i = 0; i < 8; i++)	    				// 8 bit反转
        temp |= ((data >> i) & 0x01) << (7 - i);
    return temp;
}

quint32 SharedBuffer::reverse32(quint32 data)
{
    quint8 i;
    quint32 temp = 0;
    for (i = 0; i < 32; i++)					// 32 bit反转
        temp |= ((data >> i) & 0x01) << (31 - i);
    return temp;
}

bool SharedBuffer::canWrite(int size) const
{
    return (buffer.size() + size) <= BUFFER_SIZE;
}

#include <QFile>
#include <QDebug>

Producer::Producer(SharedBuffer *shared, const QString &filePath)
    : shared(shared), filePath(filePath)
{

}

//void Producer::run()
//{
//    QFile inFile(filePath);
//    if (!inFile.open(QIODevice::ReadOnly)) {
//        qWarning() << "Producer: Unable to open file";
//        return;
//    }

//    // 阶段1: 填充缓冲区至5MB
//    initialFill(inFile);
//    // 阶段2: 处理剩余文件内容
//    processFile(inFile);

//    inFile.close();
//}

void Producer::setOwner(MainWindow *owner)
{
    m_owner = owner;
}

void Producer::initialFill(QFile &file)
{
    shared->mutex.lock();
    while (!file.atEnd() && shared->buffer.size() < SharedBuffer::BUFFER_SIZE) {
        processChunk(file);
    }
    shared->mutex.unlock();
}

void Producer::processFile(QFile &file)
{
    while (!file.atEnd()) {
        shared->mutex.lock();
        // 等待缓冲区有空间
        while (!shared->canWrite(128) && !file.atEnd()) {
            shared->bufferNotFull.wait(&shared->mutex);
        }
        if (file.atEnd()) {
            break;
        }
        processChunk(file);
        shared->mutex.unlock();
        // 通知有新数据可用
        shared->bufferNotEmpty.wakeAll();
    }

//    // 设置完成标志
//    QMutexLocker locker(&shared->mutex);
    shared->producerFinished = true;
    shared->bufferNotEmpty.wakeAll();
}

void Producer::processChunk(QFile &file)
{
    QByteArray chunk = file.read(136);
    if (chunk.size() == 136) {
        // 移除前8字节
        shared->buffer.append(chunk.mid(8));
        qDebug() << "生产:"  << "128";
    }
}

Consumer::Consumer(SharedBuffer *shared)
    : shared(shared)
{
    m_sendudp = new QUdpSocket;
    m_sendudp->bind(QHostAddress("192.168.0.100"), 10004, QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress);

}

//void Consumer::run()
//{

////    QMutexLocker locker(&shared->mutex);
////    QByteArray senddata;
////    int bytesSent;
////    while (true) {

////        for(int i = 0  ;i < m_owner->baosu ; i++)
////        {

////            // 等待缓冲区有足够数据或生产者结束
////            while (shared->buffer.size() < 1400 && !shared->producerFinished) {
////                shared->bufferNotEmpty.wait(&shared->mutex);
////            }

////            // 退出条件: 生产者结束且剩余数据不足1400
////            if (shared->producerFinished && shared->buffer.size() < 1400) {
////                bytesSent = m_sendudp->writeDatagram(shared->buffer, QHostAddress("224.1.1.4"), 10002);
////                qDebug() << bytesSent + "发送结束";
////                break;
////            }

////            // 如果缓冲区有至少1400字节，就消费1400字节
////            if (shared->buffer.size() >= 1400) {

////                bytesSent = m_sendudp->writeDatagram(shared->buffer.left(1400), QHostAddress("224.1.1.4"), 10002);
////                shared->buffer.remove(0, 1400);
////                qDebug() << bytesSent;

////            }
////            locker.unlock();
////        }

////        // 通知缓冲区有新空间
////        shared->bufferNotFull.wakeAll();
////    }

//        QByteArray senddata;
//        int bytesSent = 1;
//        QByteArray removedDatatest;

//        for(int i = 0 ; i < 1400 ; i++)
//        {
//            removedDatatest.append(reinterpret_cast<const char*>(&bytesSent), sizeof(quint32));
//        }

//    while (true) {


//            for(int i = 0 ; i < m_owner->baosu ; i++)
//            {

//            QMutexLocker locker(&shared->mutex);
//                // 等待缓冲区有足够数据或生产者结束
//                while (shared->buffer.size() < 1400 && !shared->producerFinished) {
//                    shared->bufferNotEmpty.wait(&shared->mutex);
//                }

//                // 退出条件: 生产者结束且剩余数据不足1400
//                if (shared->producerFinished && shared->buffer.size() < 1400) {
//                    bytesSent = m_sendudp->writeDatagram(shared->buffer, QHostAddress("224.1.1.4"), 10002);
//                    qDebug() << bytesSent + "发送结束";
//                    break;
//                }
//                QByteArray removedData = QByteArray::fromHex("55AA91EF0e");
//                quint32 baosize = shared->buffer.left(1400).size() + 12;
//                removedData.append(reinterpret_cast<const char*>(&baosize), sizeof(quint32));
//                removedData.append(QByteArray::fromHex("0100000001000000"));
//                removedData.append(shared->buffer.left(1400)); // 仅用于示例，实际可能不需要
//                quint32 m_crc32 = shared->crc32(removedData);
//                removedData.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));
//                bytesSent = m_sendudp->writeDatagram(removedData, QHostAddress("224.1.1.4"), 10002);
//                // 移除前1400字节

//                qDebug() << "发送了:" << bytesSent;

////                removedDatatest.append(QByteArray::fromHex("55AA91EF0e"));
////                quint32 baosize = shared->buffer.left(1400).size() + 12;
////                removedDatatest.append(reinterpret_cast<const char*>(&baosize), sizeof(quint32));
////                removedDatatest.append(QByteArray::fromHex("0100000001000000"));
////                removedDatatest.append(shared->buffer.left(1400)); // 仅用于示例，实际可能不需要
////                quint32 m_crc32 = shared->crc32(removedDatatest);
////                removedDatatest.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));
////                bytesSent = m_sendudp->writeDatagram(removedDatatest, QHostAddress("224.1.1.4"), 10002);
////                shared->buffer.remove(0, 1400);
////                qDebug() << bytesSent;
////                // 通知缓冲区有新空间

//                locker.unlock();
//                shared->bufferNotFull.wakeAll();

//            }


//     m_owner->baosu = 0;
//        }
//}

void Consumer::setOwner(MainWindow *owner)
{
    m_owner = owner;
}
