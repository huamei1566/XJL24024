#ifndef MOFEIUDPBIG_H
#define MOFEIUDPBIG_H

#include <QObject>
#include <QUdpSocket>
#include <QMutex>
#include <QThread>

class MainWindow;

class mofeiudpbig : public QObject
{
    Q_OBJECT
public:
    explicit mofeiudpbig(QObject *parent = 0);

    QByteArray* onebuffer; // 一级缓冲区
    QByteArray* twobuffer; // 二级缓冲区

    QByteArray datawrite; // 写入数据

    QString PathANDName;

    MainWindow* owner;
    void setOwner(MainWindow* mainwindow);


    int mo1farong;
    int mo2farong;


public slots:
    void Sentprogress1(int value);
    void Sentprogress2(int value);



public:
//    Producer3 m_Producer3;
//    Consumer3 m_Consumer3;
    int data_size = 256 + 8;

    int buffer_size = 10 * 1024 * 1024;
    int MY_CONSUME_SIZE = 1400;

    int baosu = 5;
    QMutex mutex;

    bool isdelete =false;

    bool flag_fashong = false;
    int fashongbaosu = 10;


};



/**
 * @brief 生产者线程类
 *
 * 负责从文件读取数据，处理后写入缓冲区


 */
class Producer4 : public QThread
{
    Q_OBJECT
public:
    explicit Producer4(mofeiudpbig *mofeiudpbig ,QObject *parent = nullptr);

protected:
    void run() override; //进入循环
    quint8 pattern = 0;

public:
    mofeiudpbig *m_mofeiudpbig;
    QMutex mutex;
};


/**
 * @brief 消费者线程类
 *
 */
class Consumer4 : public QThread
{
    Q_OBJECT
public:
    explicit Consumer4(mofeiudpbig *mofeiudpbig,int sig ,  QObject *parent = nullptr);

    quint16 TargetPort;
    quint8 pattern = 0;

protected:
    void run() override; //进入循环

public:
    mofeiudpbig *m_mofeiudpbig;
    QUdpSocket* m_senderudp;
    QMutex mutex;

};





#endif // MOFEIUDPBIG_H
