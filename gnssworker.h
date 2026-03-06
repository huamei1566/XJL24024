#ifndef GNSSWORKER_H
#define GNSSWORKER_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <QDateTime>
#include "mstrut.h"
#include <QMutex>

class MainWindow;

class GNSSWorker : public QObject
{
    Q_OBJECT
public:
    GNSSWorker()
    {
        buffer_jianchatimer = new QTimer;
        buffer_jianchatimer->setInterval(1000);  // 1秒触发一次

        // 5. 连接超时信号
        connect(buffer_jianchatimer, &QTimer::timeout, this, &GNSSWorker::Inquiry);

        buffer_jianchatimer->start();
    }
    ~GNSSWorker();

public slots:
    void start();

    void onTimeout();
    void Inquiry();
private slots:
    void readPendingDatagrams();



private:
    void processData(const QByteArray &data, const QHostAddress &, quint16);

    QUdpSocket *m_udpSocket;
    QTimer* buffer_jianchatimer;


    QNetworkInterface getInterfaceByIp(const QString &targetIp);

    GpsData parseGGA(const QString& nmeaSentence);
    RmcData parseGNRMC(const QString& nmeaSentence);


    QString stringbuffer;

    double convertUtcToSecondsOfDay(const QString &timeStr);
    void SatparseData(const QStringList& dataFields);
    void frameparseData(const QStringList& dataFields);

    quint32 crc32(const QByteArray& array);
    quint8 reverse8(quint8 data);
    quint32 reverse32(quint32 data);
    bool getBit(quint8 byte, quint8 position);
    QByteArray extractMiddlePart(const QByteArray& data);

    // 辅助函数：判断是否为闰年
    bool isLeapYear(int year);
    // 辅助函数：找到最近一次闰年的1月1日（对于给定日期）
    QDate findLastLeapYear(const QDate &date);
    // 主计算函数：根据系统和日期时间计算时间周和周秒
    TimeResult calculateTimeWeekAndSecond(SatelliteSystem system, const QDateTime &inputDateTime);

    QMutex m_mutex;

    quint8 tongbuCount = 0;

    quint8 bufferclear_count = 0;

    QByteArray serializeSubFrameToQByteArray(const SubFrame& subFrame);
    QByteArray childFrameToByteArray(const ChildFrame& frame);
    QByteArray byteArrayToSatelliteParams(QVector<Channel1SatelliteParams>& params);


    quint32 calculateChildFrameSize(const ChildFrame& childFrame);
    quint32 calculateSubFrameSize(const SubFrame& subFrame);


    void printSubFrame(const SubFrame& subFrame);
    void printChildFrame(const ChildFrame& frame);
    void printChannelData(const ChannelData& channel);
    void printObsvmMessage(const ObsvmMessage& msg);

    QString getGGAType(const QString& str);


signals:
    void LaunchGPS(GpsData gps);

    void timeoutSignal();

public:
    void setOwner(MainWindow *mainWindow);
    GpsData gps;
    RmcData rmc;

    MainWindow* owner;


    SelfLocFrameHeader m_SelfLocFrameHeader;

    SATSINFOData m_SATSINFOData;

    gnss_generic_frame_header_t m_gnss_generic_frame_header_t;
    QVector<Channel1SatelliteParams> Channel1SatelliteParamsVector;
    FrameTail m_FrameTail;
    MeasurementFrame m_MeasurementFrame;
    SubFrame m_SubFrame;
    ObsvmMessage m_ObsvmMessage;
    ReferenceStationInfoFrame m_ReferenceStationInfoFrame;



};

#endif // GNSSWORKER_H
