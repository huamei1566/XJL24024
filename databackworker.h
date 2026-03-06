#ifndef DATABACKWORKER_H
#define DATABACKWORKER_H

#include <QObject>
#include <QFile>
#include <QUdpSocket>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QCoreApplication>

class DataBackworker : public QObject    //发频数据_回归
{
    Q_OBJECT
public:
    explicit DataBackworker(QObject *parent = 0 ,
                            int hostport = 1);

    int hostport;
    QFile file;
    QFile txtfile;

    QUdpSocket *m_DataBackUdpSocket;

    bool iswrite = false;
    QTimer *timeoutTimer;





private:
    QString savefilepath;

public slots:
    void initudp();
    void startfileandudp();

    void readPendingDatagrams();

    void initfile();

    void quitfile();

    void onTimeout();


    void setSavefilepath(QString value);

signals:
    void signalOn(int value);   // 收到数据时发送开启信号
    void signalOff(int value);  // 超时未收到数据时发送关闭信号

};

#endif // DATABACKWORKER_H
