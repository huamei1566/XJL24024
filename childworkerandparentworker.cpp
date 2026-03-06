#include "childworkerandparentworker.h"
#include "childworkerandparentworker.h"

ChildWorker::ChildWorker(QByteArray *sharedData1, QByteArray *sharedData2, QString filepath,int zhengchang, QObject *parent)
    : QObject(parent),sharedData1(sharedData1),sharedData2(sharedData2),filepath(filepath),zhengchang(zhengchang + 8)
{

    m_file.setFileName(filepath);

    if (!m_file.open(QIODevice::ReadOnly)) {
        qDebug() << "文件打开失败：" << m_file.errorString();
        emit filedakaieeror();
    }





}

void ChildWorker::setbufferreadygo(bool *bufferreadygo1 , bool *bufferreadygo2)
{
    this->bufferreadygo1 = bufferreadygo1;
    this->bufferreadygo2 = bufferreadygo2;
}

void ChildWorker::setREAD_SIZE(int CHUNK_READ_SIZE)
{
    this->zhengchang = zhengchang + 8;
}

void ChildWorker::process() {
   emit update(m_file.size());
}

void ChildWorker::onSharedData1Exhausted()
{
    m_mutex.lock();

    if(m_file.atEnd())
    {
        emit anshan();
        qDebug() << "文件读取完成";
        return;
    }



    while(sharedData1->size() < 50000 * 25)
    {


            // 读取一个块
            QByteArray chunk = m_file.read(zhengchang);

            if (chunk.size() < zhengchang) {
                // 处理不完整的块
                if (chunk.size() > CHUNK_HEADER_SIZE) {
                    // 有效数据
                    QByteArray validData = chunk.mid(CHUNK_HEADER_SIZE);
                    sharedData1->append(validData);


                }
                break; // 文件结束
            }
            else
            {
                // 去掉前8字节，添加有效数据
                QByteArray validData(chunk.constData() + CHUNK_HEADER_SIZE, VALID_DATA_PER_CHUNK);
                sharedData1->append(validData);
                //qDebug() << sharedData1->size() << " " << 1 << " " << zhengchang << "   " << validData.size();
            }


        }

         *bufferreadygo1 = true;
         m_mutex.unlock();
}

void ChildWorker::onSharedData2Exhausted()
{
    m_mutex.lock();


    if(m_file.atEnd())
    {
        emit anshan();
        qDebug() << "文件读取成功";
        return;
    }



    while(sharedData2->size() < 50000 * 25)
    {

        // 读取一个块
        QByteArray chunk = m_file.read(zhengchang);

        if (chunk.size() < zhengchang) {
            // 处理不完整的块
            if (chunk.size() > CHUNK_HEADER_SIZE) {
                // 有效数据
                QByteArray validData = chunk.mid(CHUNK_HEADER_SIZE);
                sharedData2->append(validData);


            }
            break; // 文件结束
        }
        else
        {
            // 去掉前8字节，添加有效数据
            QByteArray validData(chunk.constData() + CHUNK_HEADER_SIZE, VALID_DATA_PER_CHUNK);
            sharedData2->append(validData);
            //qDebug() << sharedData2->size() << " " << 2 << zhengchang << "   " << validData.toHex();
        }


    }

    *bufferreadygo2 = true;
     m_mutex.unlock();
}

ParentWorker::ParentWorker(QByteArray *sharedData1, QByteArray *sharedData2, QString filepath, int zhengchang, QObject *parent)
    : QObject(parent),sharedData1(sharedData1),sharedData2(sharedData2),filepath(filepath),zhengchang(zhengchang + 8)
{
    qDebug() << "ParentWorker starting in thread:"
             << QThread::currentThreadId();

    m_udpsocket = new QUdpSocket;
    //m_udpsocket->bind(QHostAddress("192.168.0.100"), 10004,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress);
    m_udpsocket->bind(QHostAddress::AnyIPv4, 10004,QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress);
    childThread = new QThread(this);
    childworker = new ChildWorker(sharedData1 , sharedData2 , filepath , zhengchang);

    childworker->moveToThread(childThread);

    bufferreadygo1 = new bool(false);
    bufferreadygo2 = new bool(false);
    childworker->setbufferreadygo(bufferreadygo1 , bufferreadygo2);


    // 连接信号槽
    connect(this, &ParentWorker::SharedData1Exhausted, childworker, &ChildWorker::onSharedData1Exhausted);
    connect(this, &ParentWorker::SharedData2Exhausted, childworker, &ChildWorker::onSharedData2Exhausted);

    //connect(childworker , &ChildWorker::anshan , this , &ParentWorker::onshan);

    connect(childworker, &ChildWorker::update, this, &ParentWorker::onupdate);
    connect(childworker, &ChildWorker::filedakaieeror, this, &ParentWorker::filedakaieeror);
    connect(childThread, &QThread::start , childworker , &ChildWorker::process);

    childThread->start();

}

void ParentWorker::setzhengchang(int zhengchang)
{
    this->zhengchang = zhengchang + 8;
}

void ParentWorker::setsharedMutex(QMutex *m_sharedMutex)
{
    this->m_sharedMutex = m_sharedMutex;
}


void ParentWorker:: read_tx1_buffer_capacity(int bigreadandsender1, int biaoz)
{
    if(shiyongLogo == 0)
    {
        emit SharedData1Exhausted();
        emit SharedData2Exhausted();

        shiyongLogo = 1;
    }


    if(shiyongLogo == 1 && *bufferreadygo1 == true)
    {
        int dataCount =  qMin(bigreadandsender1 ,SIZE_SIZE);
        m_sharedMutex->lock();
        QByteArray array;
        array.append(tx++);
        array.append(sharedData1->left(dataCount));
        m_udpsocket->writeDatagram(array , QHostAddress("224.1.1.4"),10002);
        m_sharedMutex->unlock();
        //qDebug() << shiyongLogo <<" " << dataCount << sharedData1->size();
        Cumulativelength += sharedData1->left(dataCount).size();
        //qDebug() << sharedData1->left(dataCount).size() << Cumulativelength;
        sharedData1->remove(0 , dataCount);
        if(sharedData1->isEmpty())
        {
            emit SharedData1Exhausted();
            shiyongLogo = 2;
        }

        emit progressting(Cumulativelength);
    }
    else if(shiyongLogo == 2 && *bufferreadygo2 == true)
    {
        int dataCount =  qMin(bigreadandsender1 ,SIZE_SIZE);
        m_sharedMutex->lock();
        QByteArray array;
        array.append(tx++);
        array.append(sharedData2->left(dataCount));
        m_udpsocket->writeDatagram(array , QHostAddress("224.1.1.4"),10002);
        m_sharedMutex->unlock();
        Cumulativelength += sharedData2->left(dataCount).size();
        //qDebug() << sharedData2->left(dataCount).size() << Cumulativelength;
        sharedData2->remove(0 , dataCount);
        if(sharedData2->isEmpty())
        {
            emit SharedData2Exhausted();
            shiyongLogo = 1;
        }

        emit progressting(Cumulativelength);
    }

}

void ParentWorker::read_tx2_buffer_capacity(int bigreadandsender1, int biaoz)
{
    if(shiyongLogo == 0)
    {
        emit SharedData1Exhausted();
        emit SharedData2Exhausted();

        shiyongLogo = 1;
    }


    if(shiyongLogo == 1 && *bufferreadygo1 == true)
    {
        int dataCount =  qMin(bigreadandsender1 ,SIZE_SIZE);
        m_sharedMutex->lock();
        QByteArray array;
        array.append(tx++);
        array.append(sharedData1->left(dataCount));
        m_udpsocket->writeDatagram(array , QHostAddress("224.1.1.4"),10003);
        m_sharedMutex->unlock();
        //qDebug() << shiyongLogo <<" " << dataCount << sharedData1->size();
        Cumulativelength += sharedData1->left(dataCount).size();
        qDebug() << sharedData1->left(dataCount).size() << Cumulativelength;
        sharedData1->remove(0 , dataCount);
        if(sharedData1->isEmpty())
        {
            emit SharedData1Exhausted();
            shiyongLogo = 2;
        }

        emit progressting(Cumulativelength);
    }
    else if(shiyongLogo == 2 && *bufferreadygo2 == true)
    {
        int dataCount =  qMin(bigreadandsender1 ,SIZE_SIZE);
        m_sharedMutex->lock();
        QByteArray array;
        array.append(tx++);
        array.append(sharedData2->left(dataCount));
        m_udpsocket->writeDatagram(array , QHostAddress("224.1.1.4"),10003);
        m_sharedMutex->unlock();
        //qDebug() << shiyongLogo <<" " << dataCount << sharedData2->size();
        Cumulativelength += sharedData2->left(dataCount).size();
        qDebug() << sharedData2->left(dataCount).size() << Cumulativelength;
        sharedData2->remove(0 , dataCount);
        if(sharedData2->isEmpty())
        {
            emit SharedData2Exhausted();
            shiyongLogo = 1;
        }

        emit progressting(Cumulativelength);
    }
}

void ParentWorker::onupdate(long long length)
{
    Totallength = length;

    //qDebug() << Totallength;
}

void ParentWorker::onshan()
{
    qDebug() << "finsihed成功";
    emit finished();
}
