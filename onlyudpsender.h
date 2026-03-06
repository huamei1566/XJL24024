#ifndef ONLYUDPSENDER_H
#define ONLYUDPSENDER_H

#include <QThread>
#include <QUdpSocket>
#include <QMutex>

class MainWindow;




class onlyudpsender : public QObject
{
public:
    onlyudpsender(int pattern);

public slots:
    void onlyudpsend(QByteArray data ,int port);
    void setowner(MainWindow * mainwindow)
    {
        owner = mainwindow;
    }

private:
    QUdpSocket* udpsocket;

    MainWindow* owner;

    QMutex* m_mutex;

};

#endif // ONLYUDPSENDER_H
