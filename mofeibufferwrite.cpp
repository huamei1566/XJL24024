#include "mofeibufferwrite.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QUdpSocket>



BufferManager::BufferManager(const QString& filename, QObject* parent)
    : QObject(parent),
      m_filename(filename),
      m_multicastAddress("224.1.1.4"),  // 默认组播地址
      m_multicastPort(10002)            // 默认端口
{
    // 预分配缓冲区内存
    m_buffers[0].data.reserve(m_bufferSizeLimit);
    m_buffers[1].data.reserve(m_bufferSizeLimit);

    // 创建UDP发送器
    m_udpSender = new QUdpSocket(this);

    initialize();
}

BufferManager::~BufferManager()
{
    // 确保线程安全退出
    waitForFinish();

    if (m_udpSender) {
        m_udpSender->close();
    }
}

void BufferManager::initialize()
{
    m_producerTask = new ProducerTask(this);
    m_consumerTask = new ConsumerTask(this);

    m_producerTask->moveToThread(&m_producerThread);
    m_consumerTask->moveToThread(&m_consumerThread);

    connect(&m_producerThread, &QThread::started, m_producerTask, &ProducerTask::run);
    connect(&m_consumerThread, &QThread::started, m_consumerTask, &ConsumerTask::run);

    // 自动清理
    connect(m_producerTask, &ProducerTask::destroyed, &m_producerThread, &QThread::quit);
    connect(m_consumerTask, &ConsumerTask::destroyed, &m_consumerThread, &QThread::quit);
}

void BufferManager::start()
{
    m_producerThread.start();
    m_consumerThread.start();
}

void BufferManager::waitForFinish()
{
    if (m_producerThread.isRunning()) {
        m_producerThread.quit();
        m_producerThread.wait();
    }
    if (m_consumerThread.isRunning()) {
        m_consumerThread.quit();
        m_consumerThread.wait();
    }
}

void BufferManager::setOwner(MainWindow *mainwindow)
{
    owner = mainwindow;
}

void ProducerTask::run()
{
    QFile file(m_manager->m_filename);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << m_manager->m_filename;
        return;
    }

    const int headerSize = 8;
    const int dataSize = 126;
    const int chunkSize = 136;

    int bufferIndex = m_manager->m_currentWriteIndex;

    while (!file.atEnd()) {
        BufferManager::Buffer& buffer = m_manager->m_buffers[bufferIndex];

        // 锁定当前缓冲区
        QMutexLocker bufferLocker(&buffer.mutex);

        // 如果缓冲区已满，等待空间
        while (buffer.data.size() >= m_manager->m_bufferSizeLimit) {
            buffer.spaceAvailable.wait(&buffer.mutex);
        }

        // 读取并处理数据
        while (buffer.data.size() < m_manager->m_bufferSizeLimit && !file.atEnd()) {
            // 读取136字节数据块
            QByteArray chunk = file.read(chunkSize);
            if (chunk.size() < chunkSize) break;

            // 丢弃前8字节，保留有效数据
            QByteArray validData = chunk.mid(headerSize, dataSize);

            // 写入数据到当前缓冲区
            buffer.data.append(validData);

            // 通知消费者有新数据
            if (buffer.data.size() >= 1400) {
                buffer.dataAvailable.wakeOne();
            }

            qDebug() << "写入到 buffer" << bufferIndex
                     << " " << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                     << "当前大小" << buffer.data.size();
        }

        // 缓冲区满时切换到另一个缓冲区
        if (buffer.data.size() >= m_manager->m_bufferSizeLimit) {
            {
                // 锁定切换互斥锁
                QMutexLocker switchLocker(&m_manager->m_switchMutex);

                // 激活当前缓冲区
                buffer.active = true;

                // 设置读取索引
                if (m_manager->m_currentReadIndex == -1) {
                    m_manager->m_currentReadIndex = bufferIndex;
                }

                // 切换到另一个缓冲区
                bufferIndex = 1 - bufferIndex;
                m_manager->m_currentWriteIndex = bufferIndex;

                qDebug() << "切换到写入 buffer" << bufferIndex;
            }

            // 唤醒消费者
            buffer.dataAvailable.wakeOne();
        }
    }

    // 文件读取完成，处理剩余数据
    {
        QMutexLocker switchLocker(&m_manager->m_switchMutex);
        BufferManager::Buffer& buffer = m_manager->m_buffers[bufferIndex];

        if (!buffer.data.isEmpty()) {
            buffer.active = true;

            if (m_manager->m_currentReadIndex == -1) {
                m_manager->m_currentReadIndex = bufferIndex;
            }
        }

        // 设置生产完成标志
        m_manager->m_productionFinished = true;

        // 唤醒所有等待的消费者
        m_manager->m_buffers[0].dataAvailable.wakeOne();
        m_manager->m_buffers[1].dataAvailable.wakeOne();
    }
}

void ConsumerTask::run()
{
    const int consumptionSize = 1400;
    int bufferIndex = -1;

    while (true) {
        // 获取当前读取缓冲区索引
        {
            QMutexLocker switchLocker(&m_manager->m_switchMutex);

            // 等待有可读取的缓冲区
            while (m_manager->m_currentReadIndex == -1 &&
                  !m_manager->m_productionFinished)
            {
                // 等待缓冲区激活
                switchLocker.unlock();
                QThread::msleep(10); // 短暂休眠避免忙等待
                switchLocker.relock();
            }

            // 退出条件：生产结束且无数据可消费
            if (m_manager->m_productionFinished &&
                m_manager->m_currentReadIndex == -1)
            {
                break;
            }

            bufferIndex = m_manager->m_currentReadIndex;
        }

        BufferManager::Buffer& buffer = m_manager->m_buffers[bufferIndex];

        // 消费当前缓冲区的数据
        while (true) {
            // 锁定当前缓冲区
            QMutexLocker bufferLocker(&buffer.mutex);



            // 检查是否还有数据
            if (buffer.data.isEmpty()) {
                // 当前缓冲区已空
                {
                    QMutexLocker switchLocker(&m_manager->m_switchMutex);

                    // 重置缓冲区状态
                    buffer.active = false;

                    // 如果这是当前读取缓冲区，清除索引
                    if (m_manager->m_currentReadIndex == bufferIndex) {
                        m_manager->m_currentReadIndex = -1;
                    }

                    // 检查另一个缓冲区是否激活
                    int otherIndex = 1 - bufferIndex;
                    if (m_manager->m_buffers[otherIndex].active) {
                        m_manager->m_currentReadIndex = otherIndex;
                    }
                }

                // 通知生产者空间可用
                buffer.spaceAvailable.wakeOne();
                break;
            }

            // 获取要发送的数据
            int bytesToRemove = qMin(consumptionSize, buffer.data.size());
            QByteArray dataToSend = buffer.data.left(bytesToRemove);
            buffer.data.remove(0, bytesToRemove);
            //QThread::msleep(1);

            // 解锁缓冲区后再发送，避免阻塞
            bufferLocker.unlock();

            qDebug() << "从 buffer" << bufferIndex
                     << "写出" << bytesToRemove << "字节 "
                     << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
                     << "剩余" << buffer.data.size();


            // 等待数据可用
            while (buffer.data.size() < consumptionSize && buffer.active) {
                buffer.dataAvailable.wait(&buffer.mutex);
            }


            // 发送UDP数据
            if (m_manager->m_udpSender) {
                m_manager->m_udpSender->writeDatagram(
                    dataToSend,
                    m_manager->m_multicastAddress,
                    m_manager->m_multicastPort
                );
            }

            // 重新锁定缓冲区
            bufferLocker.relock();

            // 通知生产者空间可用
            if (buffer.data.size() < m_manager->m_bufferSizeLimit / 2) {
                buffer.spaceAvailable.wakeOne();
            }
        }
    }
}
