#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workerprocessing.h"
#include "databackworker.h"


#include "roundbtn.h"
#include "dialogfasheset.h"
#include "udpmanager.h"
#include "mstrut.h"
#include "udpreceiverthread.h"
#include "worker.h"
#include "mofei.h"
#include "mofeibufferwrite.h"
#include "filemacrodialog.h"
#include "logger.h"
#include <QSettings>
#include <QtGlobal>
#include "securitycontrolset.h"
#include "notifymanager.h"
#include "gnssworker.h"
#include "machinestatus.h"
#include "childworkerandparentworker.h"
#include "onlyudpsender.h"
#include "dataquery.h"
#include "txtworker.h"



constexpr qint64 BUFFER_SIZE = 5 * 1024 * 1024;  // 5MB缓冲区
constexpr qint64 CHUNK_SIZE = 1400;              // 每次消费1400字节


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPixmap removeWhiteBackground(const QPixmap &input);
    UdpComm *udpManager;


    DataQuery dataquery;

    void initsocket();
    void onerrsokcet(const QString &error);

    void saveSettings();
    void loadSettings();
    void initdaimoall(int i);

    void initGNSSfile();
    void initdatabackworker();

//    void initconnect();

    void setmaintable(QString tabdata, QString sender = "未知单位");
    int  tabrow = 0;

    void setankongjiegongK();

   ankongjiegong ankongjiegongK1;
   ankongjiegong ankongjiegongK2;
   ankongjiegong ankongjiegongK3;
   ankongjiegong ankongjiegongK4;

   QMutex m_mutex;

   bool isxiaofei = false;
   int baosu = 20;
   bool isxiaofei2 = true;
   int baosu2 = 20;
   int shuaxingbasu = 20 ;


   long long mofiCapacity1 = 1000;  //模飞文件1大小
   long long mofiCapacity2 = 1000; //模飞文件2大小

   int Alreadyfashong1 = 0;
   int Alreadyfashong2 = 0;

   int honghumachi = 0;

public:
    PPACKET_HEADER m_PPACKET_HEADER;
    PTELEMETRY_FRAME m_PTELEMETRY_FRAME;
    PTELEMETRY_FRAME_RES m_PTELEMETRY_FRAME_RES;
    PREAD_FRAMEFORMAT m_PREAD_FRAMEFORMAT;
    PREAD_FRAMEFORMAT_RES m_PREAD_FRAMEFORMAT_RES;
    PTRANSMIT_CONFIG m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;
    PTRANSMIT_CONFIG_RES m_PTRANSMIT_CONFIG_RES;


    PREAD_yaocFRAMEFORMAT m_PREAD_yaocFRAMEFORMAT;
    PREAD_yaocFRAMEFORMAT_RES m_PREAD_yaocFRAMEFORMAT_RES;
    PTELEMETRY_ENCODING_CONFIG m_PTELEMETRY_ENCODING_CONFIG;
    PTELEMETRY_ENCODING_CONFIG_RES m_PTELEMETRY_ENCODING_CONFIG_RES;
    PREAD_ENCODING_CONFIG m_PREAD_ENCODING_CONFIG;
    PREAD_ENCODING_CONFIG_RES m_PREAD_ENCODING_CONFIG_RES;
    PPCMEMBEDCONfIG m_PPCMEMBEDCONfIG;
    PPCMEMBEDCONfIG_RES m_PPCMEMBEDCONfIG_RES;
    PREAD_PCM_CONFIG m_PREAD_PCM_CONFIG;
    PREAD_PCM_CONFIG_RES m_PREAD_PCM_CONFIG_RES;
    PAsyncSourceConfig m_PAsyncSourceConfig;
    PAsyncSourceConfig_RES m_PAsyncSourceConfig_RES;
    PREAD_ASY_CONFIG m_PREAD_ASY_CONFIG;
    PREAD_ASY_CONFIG_RES m_PREAD_ASY_CONFIG_RES;


    PSecuritySourceConfig m_PSecuritySourceConfig;
    PSecuritySourceConfig_RES m_PSecuritySourceConfig_RES;


    PREADSECURITYCONTROL m_PREADSECURITYCONTROL;
    PREADSECURITYCONTROL_RES m_PREADSECURITYCONTROL_RES;
    PTransceiverConfig_RES m_PTransceiverConfig_RES;
    TransmissionDataBegin m_TransmissionDataBegin;
    PRES_TransmitterData m_RES_TransmitterData;

    PREADankongpeiz_RES m_PREADankongpeiz_RES;



    Pdaimoall m_daimoall[6];

    int fo = 100000000;
    int fo_2 = 100000000;
    QString fuzhengfangshi;
    QString zhengmazu;
    QString malv;
    QString maxing;
    QString bianmawz;
    QString mofefile;
    QString pingdian;
    QString pinpian;
    QString tiaoz;
    QString gonglv;
    QString fuzhengchang;
    QString zhenchang;
    QString tiaozhikaiguan;
    QString fuzhengfangshi2;
    QString zhengmazu2;
    QString malv2;
    QString maxing2;
    QString bianmawz2;
    QString mofefile2;
    QString pingdian2;
    QString pinpian2;
    QString tiaoz2;
    QString gonglv2;
    QString fuzhengchang2;
    QString zhenchang2;
    QString tiaozhikaiguan2;

    //系统状态数据回传
    quint32 m_tx1_freq_point;      // 频点 (4B)
    quint8 m_carrier_switch1;  // 载波开关 (bit0)
    quint8 m_modulator_switch1; // 调制开关 (bit1)
    quint16 m_tx1_buffer_capacity1;   // 模飞缓存容量 (2B)


    quint32 m_tx2_freq_point;      // 频点 (4B)
    quint8 m_carrier_switch2;  // 载波开关 (bit0)
    quint8 m_modulator_switch2; // 调制开关 (bit1)
    quint16 m_tx2_buffer_capacity2;   // 模飞缓存容量 (2B)

    quint8 m_security_recv_power;    // 安控接收功率 (1B)
    quint8 m_frame_lock;      // 安控帧锁定 (bit0)


    QString filepath1;
    QString filepath2;

    int id;
    QString daihao;
    QString txSelector;
    QString pcmmalv;
    QString subFrameLength;
    QString subFrameCount;
    QString WordConfig;
    QString featurePosition;
    QString loopSyncCode;
    QString syncCode;
    QString frameType;
    QString dataType;
    QString stepValue;
    QString initStep;
    QString FrameCalcChannel_frameCountLowByteIndex;
    QString FrameCalcChannel_notCountEnable;
    QString frameCalcChannelhigh_frameCountLowByteIndex;
    QString frameCalcChannelhigh_notCountEnable;
    QString idtreatrue;
    QString codingPosition;
    QString freq;
    QString detF;
    QString allctrl_modPolarity;
    QString allctrl_modSwitch;
    QString allctrl_carrier;
    QString allctrl_modType;
    QString powerCtrl1;
    QString codeSwitch_ldpcEnable;
    QString codeSwitch_tpcEnable;
    QString codeSwitch_rsEnable;
    QString codeSwitch_convEnable;
    QString tpcSyncCode;
    QString tpcValidFlag;


    NotifyManager notifyManager;

    QFile file;

protected:
     void closeEvent(QCloseEvent *event) override;


private slots:


    void on_Btn_setfa1_clicked();

    void on_Btn_setfa2_clicked();

    void on_Btn_setan_clicked();

    void onpeiz11(int fasheji);
    void onsbpeiz11(int fasheji);

    void onpeiz13(int fasheji);
    void onsbpeiz13(int fasheji);

    void onpeiz15(int fasheji);
    void onsbpeiz15(int fasheji);

    void onpeiz17(int fasheji);
    void onsbpeiz17(int fasheji);

    void onpeiz19(int fasheji);
    void onsbpeiz19(int fasheji);

    void onpeiz1B(int fasheji);
    void onsbpeiz1B(int fasheji);


    void onpeiz1f(int fasheji);
    void onsbpeiz1f(int fasheji);


    void onankongupdate();

    void onupdateStatus();


    void on_Btn_startFly_clicked();

    void on_Btn_startFly2_clicked();

    void on_Btn_wenjianselect1_clicked();

    void on_Btn_wenjianselect2_clicked();

    void on_Btn_file_clicked();

    void onupdateprogressBar(long long value);
    void onupdateprogressBar_2(long long value);

    void onupdateK(quint8 vulue , quint16 Power_amplifier1 , quint16 Power_amplifier2);

    void onLaunchGPS(GpsData gps);

    void onFailurebind(QString eeror);

    void onredtimeoutSignal();

    void GNSSredtimeoutSignal();

    void on_Btn_MachinestatusRead_clicked();

    void onlineedit(int count);

    void onMachineStatusRead(quint16 Power_input_voltage ,quint16 Output_voltage_12V,
                                               quint16 Power_amplifier_28V_supply_voltage,
                                               quint16 Input_current_power_supply ,quint16 Output_current_12V,
                                               quint16 Power_amplifier1 , quint16 Power_amplifier2,
                                               quint16 Detection_voltage1 , quint16 Detection_voltage2,
                                               quint8 Temperature , quint16 Version_number
                                               );

    void onsignalOn(int value);
    void onsignalOff(int value);

    void onsignalOn2(int value);
    void onsignalOff2(int value);




    void on_Btn_filedialog_clicked();

    void on_Btn_cunchu_clicked();

    void on_Btn_gonglvset_clicked();

    void on_Btn_gonglvset_2_clicked();

public:
    void updateui1();
    void updateui2();
    void initui();
    quint32 crc32(const QByteArray& array);
    quint8 reverse8(quint8 data);
    quint32 reverse32(quint32 data);
    BufferManager* m_BufferManager;

    bool getBit(quint8 byte, quint8 position);


    bool isOpenTime = true;

    void StartandQuitTransmitter(int transmitterflag1 , int transmitterflag2);
    int transmitterflag1 = 1;
    int transmitterflag2 = 1;


    QThread *workerThread;
    WorkerProcessing *workerProcessing;

    QThread *workerThread2;
    WorkerProcessing *workerProcessing2;


    QThread *senderThread;
    onlyudpsender *m_onlyudpsender;


    QThread *senderThread2;
    onlyudpsender *m_onlyudpsender2;

    SecurityControlset *m_securitycontrolset;

    Machinestatus *m_machinestatus;

    QPixmap image;
    QPixmap image2;
    QPixmap image3;

    QPixmap result;  //red light

    QPixmap result2; // green
    QPixmap result3; // yellow
    bool isgreen_K1 = false;
    bool isgreen_K2 = false;
    bool isgreen_K3 = false;
    bool isgreen_K4 = false;


    GpsData gps;

    bool mofei1_Logo = false;
    bool mofei2_Logo = false;

    QThread* parentThread;
    ParentWorker* parentWorker;


    QThread* parentThread2;
    ParentWorker* parentWorker2;

    DataBackworker* fashe1_DataBackworker;
    DataBackworker* fashe2_DataBackworker;

    txtworker* fa_txtworker;


public:
    //copy
    DEMOSET m_nDemoSet;

    QUdpSocket *m_SocketParaSet1;//10002    上位机====》便携站（10002）	流1参数配置
    QUdpSocket *m_SocketParaSet2;//10003    上位机====》便携站（10003）	流2参数配置

    //CThreadSimulator * m_pThreadSimulator;
   // CThreadSimulator * m_pThreadSimulatorTwo;

    int remainingCapacity = 0;
    int remainingCapacity2 = 0;


    int count = 0;

    bool bUI;
    bool bTest;



    void delaySomeTime(int timeSleep);
signals:

    void fashong(bool fa);

    void readRequesttext(int da , int tt);


    void startdatafile1();
    void quitdatafile1();
    void startdatafile2();
    void quitdatafile2();

    void setfilepath(QString vlaue);

    void settxtfilepath(QString vlaue,
                        QString pindian1 , QString pinpian1 ,QString tiaozhi1 ,QString gonglv1,
                        QString malv1 ,QString zhenchang1 ,QString zhenmazu1 ,QString fuzhenfangshi1 ,QString fuzhenchang1,
                        QString maxing1 ,QString bianmaweizhi1,
                        QString pindian2 , QString pinpian2 ,QString tiaozhi2 ,QString gonglv2,
                        QString malv2 ,QString zhenchang2 ,QString zhenmazu2 ,QString fuzhenfangshi2 ,QString fuzhenchang2,
                        QString maxing2 ,QString bianmaweizhi2);

public:
    Worker *worker;
    GNSSWorker *gnssworker;
    QMutex mofei_mutex;
    QTimer* m_timer;


    QTimer* m_GNSStimer;


private:
    Ui::MainWindow *ui;

    Controller *controller;

    Dialogfasheset* m_dialogfasheset;

    fileMacroDialog* m_fileMacroDialog;

    //PopupWidget* popup;


    QThread *thread;
    QThread *thread_2;

    //mofei *m_mofei;
    SharedBuffer* shared;
};
#endif // MAINWINDOW_H
