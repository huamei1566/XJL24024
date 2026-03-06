#ifndef MOFEI_H
#define MOFEI_H


#include <QMutex>
#include <QWaitCondition>
#include <QByteArray>
#include <QFile>
#include <QThread>
#include <QString>
#include <QUdpSocket>


class MainWindow;



class SharedBuffer {
public:
    static const qint64 BUFFER_SIZE = 20 * 1024 * 1024; // 5MB

    SharedBuffer();

    QByteArray buffer;
    QMutex mutex;
    QWaitCondition bufferNotFull;   // 生产者等待条件
    QWaitCondition bufferNotEmpty;  // 消费者等待条件
    bool producerFinished = false;

    quint32 crc32(const QByteArray& array);
    quint8 reverse8(quint8 data);
    quint32 reverse32(quint32 data);

    // 检查是否有足够空间写入
    bool canWrite(int size) const;
};


class Producer1 : public QThread
{
public:
    Producer1(SharedBuffer *shared, const QString &filePath);
    void run() override;

    void setOwner(MainWindow *owner);

private:
    void initialFill(QFile &file);
    void processFile(QFile &file);
    void processChunk(QFile &file);

    SharedBuffer *shared;
    QString filePath;

    MainWindow* m_owner;

    
};

class Consumer2 : public QThread
{
public:
    Consumer2(SharedBuffer *shared);
    void run() override;

    void setOwner(MainWindow *owner);

private:
    SharedBuffer *shared;
    MainWindow* m_owner;
    QUdpSocket* m_sendudp;
};


#endif // MOFEI_H
