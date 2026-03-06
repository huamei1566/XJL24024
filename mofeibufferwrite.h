// 使用宏保护
#ifndef MOFEIBUFFERWRITE_H
#define MOFEIBUFFERWRITE_H
#include <QObject>
#include <QByteArray>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QUdpSocket>
#include <QDateTime>
#include <QDebug>

class ProducerTask;
class ConsumerTask;
class MainWindow;

class BufferManager : public QObject
{
    Q_OBJECT
public:
    explicit BufferManager(const QString& filename, QObject* parent = nullptr);
    ~BufferManager();

    void start();
    void waitForFinish();

    friend class ProducerTask;
    friend class ConsumerTask;

    void setOwner(MainWindow * mainwindow);


private:
    void initialize();

    QString m_filename;

    // 双缓冲区结构 - 每个缓冲区有自己的锁
    struct Buffer {
        QByteArray data;
        QMutex mutex;
        QWaitCondition dataAvailable;
        QWaitCondition spaceAvailable;
        bool active = false;
    } m_buffers[2];

    int m_currentWriteIndex = 0;   // 当前写入的缓冲区索引
    int m_currentReadIndex = -1;   // 当前读取的缓冲区索引
    bool m_productionFinished = false;
    qint64 m_bufferSizeLimit = 5 * 1024 * 1024;

    // UDP发送设置
    QUdpSocket* m_udpSender = nullptr;
    QHostAddress m_multicastAddress;
    quint16 m_multicastPort = 0;

    // 缓冲区切换锁
    QMutex m_switchMutex;

    // 工作线程
    QThread m_producerThread;
    QThread m_consumerThread;

    // 内部任务
    ProducerTask* m_producerTask = nullptr;
    ConsumerTask* m_consumerTask = nullptr;
    MainWindow* owner;
};


// 生产者任务
class ProducerTask : public QObject
{
    Q_OBJECT
public:
    explicit ProducerTask(BufferManager* manager) : m_manager(manager) {}

public slots:
    void run();

private:
    BufferManager* m_manager;
};

// 消费者任务
class ConsumerTask : public QObject
{
    Q_OBJECT
public:
    explicit ConsumerTask(BufferManager* manager) : m_manager(manager) {}

public slots:
    void run();

private:
    BufferManager* m_manager;
};


#endif // MOFEIBUFFERWRITE_H
