#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <QDateTime>
#include <QTimer>

class MainWindow;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker() {}
    ~Worker();

public slots:
    void start();

    void onTimeout();

private slots:
    void readPendingDatagrams();



private:
    void processData(const QByteArray &data, const QHostAddress &, quint16);
    void resetTimer();
    QUdpSocket *m_udpSocket;

    QNetworkInterface getInterfaceByIp(const QString &targetIp);


public:
    void setOwner(MainWindow *mainWindow){owner = mainWindow;}

    int inum = 0;


    int remainingCapacity = 0;
    int remainingCapacity2 = 0;

    int tx1_MofeiCumulativeNumber  = 0;
    int tx2_MofeiCumulativeNumber  = 0;





signals:
    void peiz11(int fasheji);
    void sbpeiz11(int fasheji);

    void RES_FRAMEFORMAT(int fasheji);

    void peiz13(int fasheji);
    void sbpeiz13(int fasheji);

    void RES_yaocFRAMEFORMAT(int fasheji);

    void peiz15(int fasheji);
    void sbpeiz15(int fasheji);

    void RES_ENCODING_CONFIG(int fasheji);


    void peiz17(int fasheji);
    void sbpeiz17(int fasheji);

    void RES_PCM_CONFIG(int fasheji);


    void peiz19(int fasheji);
    void sbpeiz19(int fasheji);

    void RES_ASY_CONFIG(int fasheji);


    void peiz1B(int fasheji);
    void sbpeiz1B(int fasheji);


    void peiz1f(int fasheji);
    void sbpeiz1f(int fasheji);




    void updateStatus();


    void ankongupdate();
  //  void RES_FRAMEFORMAT();

    void RES_PREADankongpeiz();

    void readRequest1(int bigreadandsender1 , int tr);
    void readRequest2(int bigreadandsender2 , int tr);

    void readtexttimer(int bigreadandsender1 , int tr);

    void readoAll(int bigreadandsender1 , int tr , int bigreadandsender2 , int tr2);

    void updateK(quint8 value , quint16 Power_amplifier1 , quint16 Power_amplifier2);


    void Failurebind(QString error);

    void timeoutSignal();

    void MachineStatusRead(quint16 Power_input_voltage ,quint16 Output_voltage_12V,
                           quint16 Power_amplifier_28V_supply_voltage,
                           quint16 Input_current_power_supply ,quint16 Output_current_12V,
                           quint16 Power_amplifier1 , quint16 Power_amplifier2,
                           quint16 Detection_voltage1 , quint16 Detection_voltage2,
                           quint8 Temperature , quint16 Version_number
                           );





private:
    bool isMulticastMode;
    MainWindow* owner;
    QByteArray numarray; //多包操作

    QTimer m_timer;
};


#endif // WORKER_H
