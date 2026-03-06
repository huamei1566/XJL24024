#ifndef CHILDWORKERANDPARENTWORKER_H
#define CHILDWORKERANDPARENTWORKER_H


#include <QObject>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QUdpSocket>
#include <QMutex>

class ChildWorker : public QObject {
    Q_OBJECT
public:
    explicit ChildWorker(QByteArray* sharedData1 , QByteArray* sharedData2 , QString filepath, int zhengchang, QObject* parent = nullptr);

    void setbufferreadygo(bool* bufferreadygo1 , bool* bufferreadygo2);
    void setREAD_SIZE(int CHUNK_READ_SIZE);

public slots:
    void process();  // 子任务处理函数

    void onSharedData1Exhausted();  //响应SharedData1被消耗光函数(填充SharedData1)
    void onSharedData2Exhausted();  //响应SharedData2被消耗光函数(填充SharedData2)


signals:
    void finished(); // 添加完成信号


    void update(long long length);

    void anshan(); //文件读完了,停止模飞

    void filedakaieeror();


public:
    int zhengchang = 264;   // 每次读取的块大小
    int CHUNK_HEADER_SIZE = 8;   // 每个块要丢弃的头部大小
    int VALID_DATA_PER_CHUNK = zhengchang - CHUNK_HEADER_SIZE; // 每块有效数据

private:
    QByteArray* sharedData1;
    QByteArray* sharedData2;
    QString filepath;


    QFile m_file;
    QMutex m_mutex;


    bool *bufferreadygo1;
    bool *bufferreadygo2;

};


class ParentWorker : public QObject {
    Q_OBJECT
public:
    explicit ParentWorker(QByteArray* sharedData1 , QByteArray* sharedData2 , QString filepath ,int zhengchang = 256, QObject* parent = nullptr);

public:
    int SIZE_SIZE = 63000;
    int shiyongLogo = 0;



    long long  Totallength  = 0;
    long long  Cumulativelength = 0;


    int zhengchang;
    void setzhengchang(int zhengchang);


    void setsharedMutex(QMutex* m_sharedMutex);

public slots:
    //void startTask();  // 启动任务


    // 核心功能槽函数 - 被信号唤醒读取指定字节数
    void read_tx1_buffer_capacity(int bigreadandsender1 ,int biaoz);
    void read_tx2_buffer_capacity(int bigreadandsender1 ,int biaoz);

    void onupdate(long long length);

    void onshan();



signals:
    void finished();   // 父任务完成信号

    void SharedData1Exhausted();  //SharedData1被消耗光
    void SharedData2Exhausted();  //SharedData2被消耗光


    void progressting(long long value);

    void filedakaieeror();

private:
    QByteArray* sharedData1;
    QByteArray* sharedData2;
    QString filepath;

    QUdpSocket* m_udpsocket;
    QFile m_file;

    QMutex* m_sharedMutex;

    QThread* childThread;
    ChildWorker* childworker;

    bool *bufferreadygo1;
    bool *bufferreadygo2;

    quint8 tx = 0;
};

#endif // CHILDWORKERANDPARENTWORKER_H
