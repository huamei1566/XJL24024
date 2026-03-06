#ifndef UDPRECEIVERTHREAD_H
#define UDPRECEIVERTHREAD_H

#include <QThread>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkInterface>

class MainWindow;

class UdpReceiverThread : public QThread
{
    Q_OBJECT
public:
    explicit UdpReceiverThread(quint16 port, QObject *parent = nullptr);
    explicit UdpReceiverThread(quint16 port,
                               const QString &multicastGroup,
                               const QString &interfaceName = QString(),
                               QObject *parent = nullptr);

    ~UdpReceiverThread();

    void run() override;
    void stop();

    bool isJoinedToMulticast() const { return m_joinedMulticast; }

signals:
    void dataReceived(const QByteArray &data, const QHostAddress &sender, quint16 port);
    void multicastJoined(const QString &group);
    void multicastJoinError(const QString &error);



private:
    quint16 m_port;
    QString m_multicastGroup;
    QString m_interfaceName;
    QUdpSocket *m_udpSocket;
    bool m_running;
    bool m_joinedMulticast;
    QNetworkInterface m_interface;
};

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    void start();
    void startMulticast(const QString &group, const QString &interface = QString());
    void stop();

    void setOwner(MainWindow* mainWindow){
                   owner =  mainWindow;
       };


private slots:
    void handleData(const QByteArray &data, const QHostAddress &sender, quint16 port);
    void handleMulticastJoined(const QString &group);
    void handleMulticastJoinError(const QString &error);

signals:
    void peiz11();
    void sbpeiz11();

    void RES_FRAMEFORMAT();

    void peiz13();
    void sbpeiz13();

    void RES_yaocFRAMEFORMAT();

    void peiz15();
    void sbpeiz15();

    void RES_ENCODING_CONFIG();


    void peiz17();
    void sbpeiz17();

    void RES_PCM_CONFIG();


    void peiz19();
    void sbpeiz19();

    void RES_ASY_CONFIG();


    void peiz1B();
    void sbpeiz1B();


    void ankongupdate();
  //  void RES_FRAMEFORMAT();

    void read_tx1_buffer_capacity(bool fashe);
    void read_tx2_buffer_capacity(bool fashe2);


private:
    UdpReceiverThread *receiverThread;
    bool isMulticastMode;
    MainWindow* owner;
    QByteArray numarray; //多包操作


};

#endif // UDPRECEIVERTHREAD_H
