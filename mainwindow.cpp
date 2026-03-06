#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QObject>
#include <QTimer>
#include <QDateTime>

Q_DECLARE_METATYPE(GpsData) // 在全局作用域声明


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


     //connect(worker , &Worker::RES_FRAMEFORMAT  ,this , &Dialogfasheset::onRES_FRAMEFORMAT);


    initGNSSfile();

    this->setStyleSheet(

                " {"
                "    color: white; "/* 标题文字颜色 */
                "   font: 14px "
                "  padding-left: 40px;"/* 留出图标空间 */
                "}"
                );

    ui->Btn_file->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "   padding: 8px 15px;"           // 内边距
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_setan->setStyleSheet(
        "QPushButton {"
        "   background-color: #285C2E;"  // 主背景色（深绿）
        "   border: 1px solid #4FBFC2;"   // 边框（浅青）
        "   border-radius: 5px;"          // 圆角
        "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
        "   padding: 8px 15px;"           // 内边距
        "}"
        "QPushButton:hover {"
        "   background-color: #459E4F;"   // 悬停时亮青
        "}"
        "QPushButton:pressed {"
        "   background-color: #1D4221;"   // 按下时暗青"
        "}"
    );

    ui->Btn_setfa1->setStyleSheet(
        "QPushButton {"
        "   background-color: #285C2E;"  // 主背景色（深绿）
        "   border: 1px solid #4FBFC2;"   // 边框（浅青）
        "   border-radius: 5px;"          // 圆角
        "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
        "   padding: 8px 15px;"           // 内边距
        "}"
        "QPushButton:hover {"
        "   background-color: #459E4F;"   // 悬停时亮青
        "}"
        "QPushButton:pressed {"
        "   background-color: #1D4221;"   // 按下时暗青"
        "}"
    );

    ui->Btn_setfa2->setStyleSheet(
        "QPushButton {"
        "   background-color: #285C2E;"  // 主背景色（深绿）
        "   border: 1px solid #4FBFC2;"   // 边框（浅青）
        "   border-radius: 5px;"          // 圆角
        "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
        "   padding: 8px 15px;"           // 内边距
        "}"
        "QPushButton:hover {"
        "   background-color: #459E4F;"   // 悬停时亮青
        "}"
        "QPushButton:pressed {"
        "   background-color: #1D4221;"   // 按下时暗青"
        "}"
    );


    ui->Btn_startFly->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "   padding: 8px 15px;"           // 内边距
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_startFly2->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "   padding: 8px 15px;"           // 内边距
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    // 设置表格列数和表头标签
    ui->tableWidget->setColumnCount(4); // 必须与图片中的4列对应
    QStringList headers;
    headers << "信息类型" << "时间" << "信息来源" << "信息内容"; // 严格按图片顺序排列
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    //QSettings   settings(strtdbname,QSettings::IniFormat);

    bTest == true ;

    // 设置表头样式（代码方式）
    QFont headerFont;
    headerFont.setBold(true); // 加粗
    headerFont.setPointSize(10); // 字体大小

    ui->tableWidget->horizontalHeader()->setFont(headerFont);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter); // 居中对齐
    ui->tableWidget->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "   background-color: #f0f0f0;" // 浅灰色背景（类似常见表格风格）
        "   padding: 4px;" // 内边距
        "   border: 1px solid #d0d0d0;" // 边框颜色
        "}"
    );

    // 设置列宽策略
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); // 信息类型列自适应
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive);      // 时间列允许手动调整
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);         // 信息来源列自动拉伸
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);         // 信息内容列自动拉伸

    ui->tableWidget->setColumnWidth(1, 200);  // 第二列150px

    ui->lineEdit_zhenchang1->setReadOnly(true);
    ui->lineEdit_gonglv->setReadOnly(true);
    ui->lineEdit_pingdian->setReadOnly(true);
    ui->lineEdit_pinpian->setReadOnly(true);
    ui->lineEdit_malv->setReadOnly(true);
    ui->lineEdit_bianmawz->setReadOnly(true);
    ui->lineEdit_zhengmazu->setReadOnly(true);
    ui->lineEdit_fuzhengfs1->setReadOnly(true);
    ui->lineEdit_tiaoz->setReadOnly(true);
    ui->lineEdit_maxing->setReadOnly(true);
    ui->lineEdit_fuzhengchang->setReadOnly(true);

    ui->lineEdit_zhenchang2->setReadOnly(true);
    ui->lineEdit_gonglv_2->setReadOnly(true);
    ui->lineEdit_pingdian_2->setReadOnly(true);
    ui->lineEdit_pinpian_2->setReadOnly(true);
    ui->lineEdit_malv_2->setReadOnly(true);
    ui->lineEdit_bianmawz_2->setReadOnly(true);
    ui->lineEdit_zhengmazu_2->setReadOnly(true);
    ui->lineEdit_fuzhengfs1_2->setReadOnly(true);
    ui->lineEdit_tiaoz_2->setReadOnly(true);
    ui->lineEdit_maxing_2->setReadOnly(true);
    ui->lineEdit_fuzhengchang_2->setReadOnly(true);

    ui->lineEdit_GNSStime->setReadOnly(true);
    ui->lineEdit_GNSSlongitude->setReadOnly(true);
    ui->lineEdit_GNSSlatitude->setReadOnly(true);
    ui->lineEdit_GNSSheight->setReadOnly(true);
    ui->lineEdit_savepath->setReadOnly(true);

    ui->label_61->hide();
    ui->label_69->hide();
    ui->lineEdit_Output_voltage_12V->hide();
    ui->lineEdit_Output_current_12V->hide();



    image.load("qrc/crc.png");
    result = removeWhiteBackground(image); // 阈值可调
    result = result.scaled(
            30,
            30,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
        );


    image2.load("qrc/green.png");
    result2 = removeWhiteBackground(image2); // 阈值可调
    result2 = result2.scaled(
            30,
            30,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
        );

    image3.load("qrc/yellow.png");
    result3 = removeWhiteBackground(image3); // 阈值可调
    result3 = result3.scaled(
            30,
            30,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
        );



    ui->label_pixmapGNSS->setPixmap(result);
    ui->label_pixmapjiqi->setPixmap(result);
    ui->label_pixmapjiqi_2->setPixmap(result);
//    ui->label_pixmap3->setPixmap(result2);

    ui->label_pixmapK1->setPixmap(result);
    ui->label_pixmapK2->setPixmap(result);
    ui->label_pixmapK3->setPixmap(result);
    ui->label_pixmapK4->setPixmap(result);

    ui->label_pixmapfashe1->setPixmap(result);
    ui->label_pixmapfashe2->setPixmap(result);


//    ui->progressBar->setMaximum(0); // 这样设置后，50就代表50%
//    ui->progressBar->setMaximum(mofiCapacity1); // 这样设置后，50就代表50%

    ui->Btn_wenjianselect1->setStyleSheet(
                "QPushButton {"
                "   background-color: #4CAF50; /* 背景色 */"
                "   color: white;"                // 文字颜色
                    "   border: 2px solid #388E3C;"    // 边框
                    "   border-radius: 4px;"           // 圆角

                "}"
                "QPushButton:hover {"
                "   background-color: #45a049; /* 鼠标悬停时的背景色 */"
                "}"
                "QPushButton:pressed {"
                "   background-color: #3d8b40; /* 按钮按下时的背景色 */"
                "}"
            );



    ui->Btn_wenjianselect2->setStyleSheet(
                "QPushButton {"
                "   background-color: #4CAF50; /* 背景色 */"
                "   color: white;"                // 文字颜色
                    "   border: 2px solid #388E3C;"    // 边框
                    "   border-radius: 4px;"           // 圆角

                "}"
                "QPushButton:hover {"
                "   background-color: #45a049; /* 鼠标悬停时的背景色 */"
                "}"
                "QPushButton:pressed {"
                "   background-color: #3d8b40; /* 按钮按下时的背景色 */"
                "}"
            );

    ui->Btn_MachinestatusRead->setStyleSheet( "QPushButton {"
                                              "   background-color: #285C2E;"  // 主背景色（深绿）
                                              "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                                              "   border-radius: 5px;"          // 圆角
                                              "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                                              "   padding: 8px 15px;"           // 内边距
                                              "}"
                                              "QPushButton:hover {"
                                              "   background-color: #459E4F;"   // 悬停时亮青
                                              "}"
                                              "QPushButton:pressed {"
                                              "   background-color: #1D4221;"   // 按下时暗青"
                                              "}");


    loadSettings();
    updateui1();
    updateui2();

    setankongjiegongK();

    initsocket();
    //m_RES_TransmitterData = new RES_TransmitterData;

    initdatabackworker();

    setWindowTitle("模拟器监控软件");


}

MainWindow::~MainWindow()
{

            file.close();
            // 步骤1: 请求线程退出
            senderThread->quit();  // 退出线程的事件循环
            senderThread->requestInterruption(); // Qt 5.2+ 新增的中断机制

            // 步骤2: 等待线程结束（设置合理超时时间）
            if (!senderThread->wait(2000)) {  // 等待2秒
                qWarning() << "Thread not finished, forcing termination";
                senderThread->terminate();    // 强制终止（最后手段）
                senderThread->wait();         // 再次等待
            }

            // 步骤3: 清理资源（注意删除顺序）
            delete m_onlyudpsender;    // 先删除工作对象
            m_onlyudpsender = nullptr;

            delete senderThread;        // 再删除线程对象
            senderThread = nullptr;

            // 1. 停止定时器（通过线程安全的方式）
            QMetaObject::invokeMethod(m_timer, "stop", Qt::QueuedConnection);

            // 2. 断开所有相关信号槽
            worker->disconnect();
            m_timer->disconnect();

            // 3. 请求线程退出
            thread->quit();

            // 4. 等待线程完全结束
            thread->wait();  // 可选：如果需立即回收资源

            // 5. 安全删除对象（通过deleteLater）
            QMetaObject::invokeMethod(worker, "deleteLater", Qt::QueuedConnection);
            QMetaObject::invokeMethod(m_timer, "deleteLater", Qt::QueuedConnection);

            // 6. 删除线程对象
            delete thread;  // 在父线程直接删除







    // ========== DataBackworker 安全退出 ==========
    // 1. 先调用 quitfile 停止文件写入
    if (fashe1_DataBackworker) {
        QMetaObject::invokeMethod(fashe1_DataBackworker, "quitfile", Qt::QueuedConnection);
    }
    if (fashe2_DataBackworker) {
        QMetaObject::invokeMethod(fashe2_DataBackworker, "quitfile", Qt::QueuedConnection);
    }

    // 2. 退出并等待 workerThread2 线程
    if (workerThread2) {
        workerThread2->quit();
        if (!workerThread2->wait(2000)) {
            workerThread2->terminate();
            workerThread2->wait();
        }
    }

    // 3. 清理 DataBackworker
    if (fashe1_DataBackworker) {
        QThread* fashe1Thread = fashe1_DataBackworker->thread();
        if (fashe1Thread && fashe1Thread != QThread::currentThread()) {
            fashe1Thread->quit();
            if (!fashe1Thread->wait(2000)) {
                fashe1Thread->terminate();
                fashe1Thread->wait();
            }
            delete fashe1Thread;
        }
        fashe1_DataBackworker->deleteLater();
        fashe1_DataBackworker = nullptr;
    }
    if (fashe2_DataBackworker) {
        QThread* fashe2Thread = fashe2_DataBackworker->thread();
        if (fashe2Thread && fashe2Thread != QThread::currentThread()) {
            fashe2Thread->quit();
            if (!fashe2Thread->wait(2000)) {
                fashe2Thread->terminate();
                fashe2Thread->wait();
            }
            delete fashe2Thread;
        }
        fashe2_DataBackworker->deleteLater();
        fashe2_DataBackworker = nullptr;
    }

    delete ui;
}

QPixmap MainWindow::removeWhiteBackground(const QPixmap &input)
{
    // 转换为支持Alpha通道的QImage
       QImage image = input.toImage().convertToFormat(QImage::Format_ARGB32);

       // 遍历所有像素
       for (int y = 0; y < image.height(); ++y) {
           QRgb *pixel = reinterpret_cast<QRgb*>(image.scanLine(y));
           for (int x = 0; x < image.width(); ++x) {
               QColor color(*pixel);

               // 判断是否在白色范围内（RGB分量均高于阈值）
               if (color.red() >= 240 &&
                   color.green() >= 240 &&
                   color.blue() >= 240)
               {
                   // 设置完全透明
                   color.setAlpha(0);
                   *pixel = color.rgba();
               }
               ++pixel;
           }
       }

       return QPixmap::fromImage(image);
}

void MainWindow::initsocket()
{
    udpManager = new UdpComm(this);


    thread = new QThread;
    worker = new Worker;
    worker->setOwner(this);
    worker->moveToThread(thread);

    m_timer = new QTimer;  // 在主线程创建定时器
    m_timer->moveToThread(thread);  // 移动到子线程
    m_timer->setInterval(3000);  // 在主线程设置间隔是安全的

    connect(m_timer, &QTimer::timeout, worker, &Worker::onTimeout);


    connect(thread, &QThread::started, [this]() {
        m_timer->start();  // 在子线程上下文中启动
    });


    connect(thread, &QThread::started, worker, &Worker::start);
    thread->start();

    connect(worker  ,&Worker::Failurebind , this , &MainWindow::onFailurebind);

    connect(worker  ,&Worker::timeoutSignal , this , &MainWindow::onredtimeoutSignal);



    connect(worker , &Worker::peiz11 , this , &MainWindow::onpeiz11);
    connect(worker , &Worker::peiz13 , this , &MainWindow::onpeiz13);
    connect(worker , &Worker::peiz15 , this , &MainWindow::onpeiz15);
    connect(worker , &Worker::peiz17 , this , &MainWindow::onpeiz17);
    connect(worker , &Worker::peiz19 , this , &MainWindow::onpeiz19);
    connect(worker , &Worker::peiz1B , this , &MainWindow::onpeiz1B);
    connect(worker , &Worker::sbpeiz11 , this , &MainWindow::onsbpeiz11);
    connect(worker , &Worker::sbpeiz13 , this , &MainWindow::onsbpeiz13);
    connect(worker , &Worker::sbpeiz15 , this , &MainWindow::onsbpeiz15);
    connect(worker , &Worker::sbpeiz17 , this , &MainWindow::onsbpeiz17);
    connect(worker , &Worker::sbpeiz19 , this , &MainWindow::onsbpeiz19);
    connect(worker , &Worker::sbpeiz1B , this , &MainWindow::onsbpeiz1B);
    connect(worker , &Worker::peiz1f , this , &MainWindow::onpeiz1f);

    connect(worker , &Worker::MachineStatusRead  ,this , &MainWindow::onMachineStatusRead);

    connect(worker , &Worker::ankongupdate  ,this , &MainWindow::onankongupdate);

    connect(worker , &Worker::updateStatus , this , &MainWindow::onupdateStatus);

    connect(worker , &Worker::updateK  ,this , &MainWindow::onupdateK);




    m_onlyudpsender = new onlyudpsender(1);
    senderThread = new QThread;
    m_onlyudpsender->setowner(this);
    m_onlyudpsender->moveToThread(senderThread);


    senderThread->start();


    m_onlyudpsender2 = new onlyudpsender(2);
    senderThread2 = new QThread;
    m_onlyudpsender2->setowner(this);
    m_onlyudpsender2->moveToThread(senderThread2);


    senderThread2->start();



//    thread_2->start();
    qRegisterMetaType<GpsData>("GpsData");

    thread_2 = new QThread;
    gnssworker = new GNSSWorker;
    gnssworker->setOwner(this);
    gnssworker->moveToThread(thread_2);

    m_GNSStimer = new QTimer;  // 在主线程创建定时器

    m_GNSStimer->setInterval(5000);  // 在主线程设置间隔是安全的

    m_GNSStimer->moveToThread(thread_2);  // 移动到子线程




    connect(m_GNSStimer, &QTimer::timeout, gnssworker, &GNSSWorker::onTimeout);


    connect(thread_2, &QThread::started, [this]() {
        m_GNSStimer->start();  // 在子线程上下文中启动
    });
    connect(gnssworker, &GNSSWorker::LaunchGPS, this, &MainWindow::onLaunchGPS);

    connect(gnssworker  ,&GNSSWorker::timeoutSignal , this , &MainWindow::GNSSredtimeoutSignal);


    connect(thread_2, &QThread::started, gnssworker, &GNSSWorker::start);
    thread_2->start();

    //connect(gnssworker  ,&GNSSWorker::Failurebind , this , &MainWindow::onFailurebind);










}

void MainWindow::onerrsokcet(const QString &error)
{
    QMessageBox::information(this , "jingao" , error);
}

void MainWindow::saveSettings()
{
            QSettings settings("settings.ini", QSettings::IniFormat);

            settings.beginGroup("MainSettings");
            settings.setValue("fuzhengfangshi", fuzhengfangshi);
            settings.setValue("zhengmazu", zhengmazu);
            settings.setValue("malv", malv);
            settings.setValue("maxing", maxing);
            settings.setValue("bianmawz", bianmawz);
            settings.setValue("mofefile", mofefile);
            settings.setValue("pingdian", pingdian);
            settings.setValue("pinpian", pinpian);
            settings.setValue("tiaoz", tiaoz);
            settings.setValue("gonglv", gonglv);
            settings.setValue("fuzhengchang", fuzhengchang);
            settings.setValue("zhenchang", zhenchang);
            settings.setValue("tiaozhikaiguan", tiaozhikaiguan);
            settings.endGroup();

            settings.beginGroup("AdvancedSettings");
            settings.setValue("fuzhengfangshi2", fuzhengfangshi2);
            settings.setValue("zhengmazu2", zhengmazu2);
            settings.setValue("malv2", malv2);
            settings.setValue("maxing2", maxing2);
            settings.setValue("bianmawz2", bianmawz2);
            settings.setValue("mofefile2", mofefile2);
            settings.setValue("pingdian2", pingdian2);
            settings.setValue("pinpian2", pinpian2);
            settings.setValue("tiaoz2", tiaoz2);
            settings.setValue("gonglv2", gonglv2);
            settings.setValue("fuzhengchang2", fuzhengchang2);
            settings.setValue("zhenchang2", zhenchang2);
            settings.setValue("tiaozhikaiguan2", tiaozhikaiguan2);
            settings.endGroup();


            // 加载主设置
            settings.beginGroup("MainWentID");
            settings.setValue("fo", fo);
            settings.setValue("fo_2", fo_2);
            settings.endGroup();


            settings.setValue("savepath", ui->lineEdit_savepath->text());
}

void MainWindow::loadSettings()
{
            QSettings settings("settings.ini", QSettings::IniFormat);

            // 加载主设置
            settings.beginGroup("MainWentID");
            fo = settings.value("fo", 100000000).toInt();
            fo_2 = settings.value("fo_2", 32000000).toInt();
            settings.endGroup();


            // 加载主设置
            settings.beginGroup("MainSettings");
            fuzhengfangshi = settings.value("fuzhengfangshi", "无副帧").toString();
            zhengmazu = settings.value("zhengmazu", "EB90").toString();
            malv = settings.value("malv", "10000").toString();
            maxing = settings.value("maxing", "NRZ-L").toString();
            bianmawz = settings.value("bianmawz", "10").toString();
            mofefile = settings.value("mofefile", "default.mod").toString();
            pingdian = settings.value("pingdian", "150.5").toString();
            pinpian = settings.value("pinpian", "0.5").toString();
            tiaoz = settings.value("tiaoz", "QPSK调制").toString();
            gonglv = settings.value("gonglv", "45").toString();
            fuzhengchang = settings.value("fuzhengchang", "16").toString();
            zhenchang = settings.value("zhenchang", "128").toString();
            tiaozhikaiguan = settings.value("tiaozhikaiguan", "关").toString();
            settings.endGroup();

            // 加载高级设置
            settings.beginGroup("AdvancedSettings");
            fuzhengfangshi2 = settings.value("fuzhengfangshi2", "无副帧").toString();
            zhengmazu2 = settings.value("zhengmazu2", "EB90").toString();
            malv2 = settings.value("malv2", "10000").toString();
            maxing2 = settings.value("maxing2", "NRZ-L").toString();
            bianmawz2 = settings.value("bianmawz2", "10").toString();
            mofefile2 = settings.value("mofefile2", "adv.mod").toString();
            pingdian2 = settings.value("pingdian2", "160.5").toString();
            pinpian2 = settings.value("pinpian2", "0.5").toString();
            tiaoz2 = settings.value("tiaoz2", "QPSK调制").toString();
            gonglv2 = settings.value("gonglv2", "45").toString();
            fuzhengchang2 = settings.value("fuzhengchang2", "16").toString();
            zhenchang2 = settings.value("zhenchang2", "128").toString();
            tiaozhikaiguan2 = settings.value("tiaozhikaiguan2", "关").toString();
            settings.endGroup();

            ui->lineEdit_savepath->setText(settings.value("savepath", "/data").toString());
}

void MainWindow::initdaimoall(int i)
{
    QString inifilename =  QString("dabaosetting%1").arg(i);
    QSettings settings(inifilename, QSettings::IniFormat);


    id = settings.value("id", "方式A").toInt();
    daihao= settings.value("daihao", "方式A").toString();
    txSelector= settings.value("txSelector", "方式A").toString();
    pcmmalv= settings.value("pcmmalv", "方式A").toString();
    subFrameLength= settings.value("subFrameLength", "ZM001").toString();
    subFrameCount= settings.value("subFrameCount", "方式A").toString();
    WordConfig= settings.value("WordConfig", "方式A").toString();
    featurePosition= settings.value("featurePosition", "方式A").toString();
    loopSyncCode= settings.value("loopSyncCode", "方式A").toString();
    syncCode= settings.value("syncCode", "方式A").toString();
    frameType= settings.value("frameType", "方式A").toString();
    dataType= settings.value("dataType", "方式A").toString();
    stepValue= settings.value("stepValue", "方式A").toString();
    initStep= settings.value("initStep", "方式A").toString();
    FrameCalcChannel_frameCountLowByteIndex= settings.value("FrameCalcChannel_frameCountLowByteIndex", "方式A").toString();
    FrameCalcChannel_notCountEnable= settings.value("FrameCalcChannel_notCountEnable", "方式A").toString();
    frameCalcChannelhigh_frameCountLowByteIndex= settings.value("frameCalcChannelhigh_frameCountLowByteIndex", "方式A").toString();
    frameCalcChannelhigh_notCountEnable= settings.value("frameCalcChannelhigh_notCountEnable", "方式A").toString();
    idtreatrue= settings.value("idtreatrue", "方式A").toString();
    codingPosition= settings.value("codingPosition", "方式A").toString();
    freq= settings.value("freq", "方式A").toString();
    detF= settings.value("detF", "方式A").toString();
    allctrl_modPolarity= settings.value("allctrl_modPolarity", "方式A").toString();
    allctrl_modSwitch= settings.value("allctrl_modSwitch", "方式A").toString();
    allctrl_carrier= settings.value("allctrl_carrier", "方式A").toString();
    allctrl_modType= settings.value("allctrl_modType", "方式A").toString();
    powerCtrl1= settings.value("powerCtrl1", "方式A").toString();
    codeSwitch_ldpcEnable= settings.value("codeSwitch_ldpcEnable", "方式A").toString();
    codeSwitch_tpcEnable= settings.value("codeSwitch_tpcEnable", "方式A").toString();
    codeSwitch_rsEnable= settings.value("codeSwitch_rsEnable", "方式A").toString();
    codeSwitch_convEnable= settings.value("codeSwitch_convEnable", "方式A").toString();
    tpcSyncCode= settings.value("tpcSyncCode", "方式A").toString();
    tpcValidFlag= settings.value("tpcValidFlag", "方式A").toString();


}

void MainWindow::initGNSSfile()
{
   // QString time = QDateTime::currentDateTime().toUTC().toString();
  //  file.setFileName(QString("启动%1安控记录.txt").arg(time));
    file.setFileName(QString("启动安控记录.txt"));
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
}

void MainWindow::initdatabackworker()
{
    fashe1_DataBackworker = new DataBackworker(this , 10007);
    fashe2_DataBackworker = new DataBackworker(this , 10008);

    fa_txtworker = new txtworker;

    QThread* fashe1thread = new QThread;
    QThread* fashe2thread = new QThread;
    QThread* txtworkerthread = new QThread;

    fashe1_DataBackworker->moveToThread(fashe1thread);
    fashe2_DataBackworker->moveToThread(fashe2thread);
    fa_txtworker->moveToThread(txtworkerthread);

//    fashe1_DataBackworker = new DataBackworker(this , 10007);
//    fashe2_DataBackworker = new DataBackworker(this , 10008);

//    QThread* fashe1thread = new QThread;
//    QThread* fashe2thread = new QThread;

//    fashe1_DataBackworker->moveToThread(fashe1thread);
//    fashe2_DataBackworker->moveToThread(fashe2thread);

    connect(fashe1thread , &QThread::started , fashe1_DataBackworker , &DataBackworker::initudp);
    connect(fashe1thread , &QThread::started , fashe2_DataBackworker , &DataBackworker::initudp);

    connect(this , &MainWindow::setfilepath , fashe1_DataBackworker , &DataBackworker::setSavefilepath);
    connect(this , &MainWindow::setfilepath , fashe2_DataBackworker , &DataBackworker::setSavefilepath);
    connect(this , &MainWindow::settxtfilepath , fa_txtworker , &txtworker::starting);

    connect(this , &MainWindow::quitdatafile1 , fashe1_DataBackworker , &DataBackworker::quitfile);
    connect(this , &MainWindow::quitdatafile2 , fashe2_DataBackworker , &DataBackworker::quitfile);

    connect(fashe1_DataBackworker , &DataBackworker::signalOn , this , &MainWindow::onsignalOn);
    connect(fashe2_DataBackworker , &DataBackworker::signalOn , this , &MainWindow::onsignalOn2);
    connect(fashe1_DataBackworker , &DataBackworker::signalOff , this , &MainWindow::onsignalOff);
    connect(fashe2_DataBackworker , &DataBackworker::signalOff , this , &MainWindow::onsignalOff2);

    connect(this , &MainWindow::startdatafile1 , fashe1_DataBackworker , &DataBackworker::startfileandudp);
    connect(this , &MainWindow::startdatafile2 , fashe2_DataBackworker , &DataBackworker::startfileandudp);
    //startfileandudp

    fashe1thread->start();
    fashe2thread->start();
    txtworkerthread->start();

}

void MainWindow::setmaintable(QString tabdata, QString sender)
{
    // 增加行数
       tabrow++;
       ui->tableWidget->setRowCount(tabrow);

       // 设置时间列（第2列）到新增加的行
       int newRowIndex = tabrow - 1; // 因为行数从0开始，新行的索引是tabrow-1

       // 创建时间列
       QTableWidgetItem* Item = new QTableWidgetItem;
       QString DeBug = QString("info");
       Item->setText(DeBug);
       ui->tableWidget->setItem(newRowIndex, 0, Item);

       QTableWidgetItem* timeItem2 = new QTableWidgetItem;
       QString time = QDateTime::currentDateTime().toString();
       timeItem2->setText(time);
       ui->tableWidget->setItem(newRowIndex, 1, timeItem2); // 时间列索引为1

       QTableWidgetItem* Item3 = new QTableWidgetItem;

       Item3->setText(sender);
       ui->tableWidget->setItem(newRowIndex, 2, Item3);

       QTableWidgetItem* Item4 = new QTableWidgetItem;
       Item4->setText(tabdata);
       ui->tableWidget->setItem(newRowIndex, 3, Item4);


}

void MainWindow::setankongjiegongK()
{
    bool ok;
    QSettings settings("settings.ini", QSettings::IniFormat);

    settings.beginGroup("Kkezhi");
    ankongjiegongK1.addressCode = static_cast<quint8>(settings.value("K1_dizhi", "1234").toString().toInt(&ok ,16)); // 默认值示例
    ankongjiegongK1.functionCode = static_cast<quint16>(settings.value("K1_gongneng", "1234").toString().toInt(&ok ,16));
    ankongjiegongK1.padding = static_cast<quint8>(settings.value("K1_tianchong", "1234").toString().toInt(&ok ,16));


    ankongjiegongK2.addressCode = static_cast<quint8>(settings.value("K2_dizhi", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.functionCode = static_cast<quint16>(settings.value("K2_gongneng", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.padding = static_cast<quint8>(settings.value("K2_tianchong", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.addressCode = static_cast<quint8>(settings.value("K3_dizhi", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.functionCode = static_cast<quint16>(settings.value("K3_gongneng", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.padding = static_cast<quint8>(settings.value("K3_tianchong", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.addressCode = static_cast<quint8>(settings.value("K4_dizhi", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.functionCode = static_cast<quint16>(settings.value("K4_gongneng", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.padding = static_cast<quint8>(settings.value("K4_tianchong", "1234").toString().toInt(&ok ,16));
    settings.endGroup();


    settings.beginGroup("Kziling");
    ankongjiegongK1.chars[0] = static_cast<quint16>(settings.value("K1_1", "1234").toString().toInt(&ok ,16));
    ankongjiegongK1.chars[1] = static_cast<quint16>(settings.value("K1_2", "1234").toString().toInt(&ok ,16));
    ankongjiegongK1.chars[2] = static_cast<quint16>(settings.value("K1_3", "1234").toString().toInt(&ok ,16));
    ankongjiegongK1.chars[3] = static_cast<quint16>(settings.value("K1_4", "1234").toString().toInt(&ok ,16));
    ankongjiegongK1.chars[4] = static_cast<quint16>(settings.value("K1_5", "1234").toString().toInt(&ok ,16));
    ankongjiegongK1.chars[5] = static_cast<quint16>(settings.value("K1_6", "1234").toString().toInt(&ok ,16));
    ankongjiegongK1.chars[6] = static_cast<quint16>(settings.value("K1_7", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.chars[0] = static_cast<quint16>(settings.value("K2_1", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.chars[1] = static_cast<quint16>(settings.value("K2_2", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.chars[2] = static_cast<quint16>(settings.value("K2_3", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.chars[3] = static_cast<quint16>(settings.value("K2_4", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.chars[4] = static_cast<quint16>(settings.value("K2_5", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.chars[5] = static_cast<quint16>(settings.value("K2_6", "1234").toString().toInt(&ok ,16));
    ankongjiegongK2.chars[6] = static_cast<quint16>(settings.value("K2_7", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.chars[0] = static_cast<quint16>(settings.value("K3_1", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.chars[1] = static_cast<quint16>(settings.value("K3_2", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.chars[2] = static_cast<quint16>(settings.value("K3_3", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.chars[3] = static_cast<quint16>(settings.value("K3_4", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.chars[4] = static_cast<quint16>(settings.value("K3_5", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.chars[5] = static_cast<quint16>(settings.value("K3_6", "1234").toString().toInt(&ok ,16));
    ankongjiegongK3.chars[6] = static_cast<quint16>(settings.value("K3_7", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.chars[0] = static_cast<quint16>(settings.value("K4_1", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.chars[1] = static_cast<quint16>(settings.value("K4_2", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.chars[2] = static_cast<quint16>(settings.value("K4_3", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.chars[3] = static_cast<quint16>(settings.value("K4_4", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.chars[4] = static_cast<quint16>(settings.value("K4_5", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.chars[5] = static_cast<quint16>(settings.value("K4_6", "1234").toString().toInt(&ok ,16));
    ankongjiegongK4.chars[6] = static_cast<quint16>(settings.value("K4_7", "1234").toString().toInt(&ok ,16));
    settings.endGroup();

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}


void MainWindow::on_Btn_setfa1_clicked()
{
    disconnect(worker , &Worker::RES_FRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_FRAMEFORMAT);
    disconnect(worker , &Worker::RES_yaocFRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_yaocFRAMEFORMAT);
    disconnect(worker , &Worker::RES_ENCODING_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ENCODING_CONFIG);
    disconnect(worker , &Worker::RES_PCM_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_PCM_CONFIG);
    disconnect(worker , &Worker::RES_ASY_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ASY_CONFIG);

   m_dialogfasheset = new  Dialogfasheset(1 , this);
   m_dialogfasheset->setOwner(this);
   m_dialogfasheset->show();
   m_dialogfasheset->setAttribute(Qt::WA_DeleteOnClose);
   m_dialogfasheset->setWindowModality(Qt::WindowModal); // 阻止父窗口及顶层窗口
   m_dialogfasheset->setFixedSize(1360, 820);

   connect(worker , &Worker::RES_FRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_FRAMEFORMAT);
   connect(worker , &Worker::RES_yaocFRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_yaocFRAMEFORMAT);
   connect(worker , &Worker::RES_ENCODING_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ENCODING_CONFIG);
   connect(worker , &Worker::RES_PCM_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_PCM_CONFIG);
   connect(worker , &Worker::RES_ASY_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ASY_CONFIG);

   // connect( )RES_ASY_CONFIG
}

void MainWindow::on_Btn_setfa2_clicked()
{
    disconnect(worker , &Worker::RES_FRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_FRAMEFORMAT);
    disconnect(worker , &Worker::RES_yaocFRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_yaocFRAMEFORMAT);
    disconnect(worker , &Worker::RES_ENCODING_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ENCODING_CONFIG);
    disconnect(worker , &Worker::RES_PCM_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_PCM_CONFIG);
    disconnect(worker , &Worker::RES_ASY_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ASY_CONFIG);

    m_dialogfasheset = new  Dialogfasheset(2 , this);
    m_dialogfasheset->setOwner(this);
    m_dialogfasheset->show();
    m_dialogfasheset->setAttribute(Qt::WA_DeleteOnClose);
    m_dialogfasheset->setWindowModality(Qt::WindowModal); // 阻止父窗口及顶层窗口
    m_dialogfasheset->setFixedSize(1360, 820);

     connect(worker , &Worker::RES_FRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_FRAMEFORMAT);
     connect(worker , &Worker::RES_yaocFRAMEFORMAT  ,m_dialogfasheset , &Dialogfasheset::onRES_yaocFRAMEFORMAT);
     connect(worker , &Worker::RES_ENCODING_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ENCODING_CONFIG);
     connect(worker , &Worker::RES_PCM_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_PCM_CONFIG);
     connect(worker , &Worker::RES_ASY_CONFIG  ,m_dialogfasheset , &Dialogfasheset::onRES_ASY_CONFIG);

}

void MainWindow::on_Btn_setan_clicked()
{

    disconnect(worker , &Worker::RES_PREADankongpeiz  ,m_securitycontrolset , &SecurityControlset::on_RES_PREADankongpeiz);
    m_securitycontrolset = new SecurityControlset(this);
    m_securitycontrolset->setOwner(this);
    connect(worker , &Worker::RES_PREADankongpeiz  ,m_securitycontrolset , &SecurityControlset::on_RES_PREADankongpeiz);
    m_securitycontrolset->setFixedSize(900,620);
    m_securitycontrolset->show();



}

void MainWindow::onpeiz11(int fasheji)
{
    //QMessageBox::information(this , "提示" , "下传成功");
    notifyManager.notify("信息", "帧格式下发回传:下传成功" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("帧格式下发回传:下传成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("帧格式下发回传:下传成功" , "发射机2");
    }
}

void MainWindow::onsbpeiz11(int fasheji)
{
//    popup = new PopupWidget("操作成功！这是一个右下角弹出通知");
//    popup->show();
    notifyManager.notify("信息", "帧格式下发回传:下传失败" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("帧格式下发回传:下传失败" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("帧格式下发回传:下传失败" , "发射机2");
    }

}

void MainWindow::onpeiz13(int fasheji)
{
    notifyManager.notify("信息", "射频参数下发回传:下发成功" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("射频参数下发回传:下发成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("射频参数下发回传:下发成功" , "发射机2");
    }

}

void MainWindow::onsbpeiz13(int fasheji)
{
    notifyManager.notify("信息", "射频参数下发回传:下传失败" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("射频参数下发回传:下传失败" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("射频参数下发回传:下传失败" , "发射机2");
    }
}

void MainWindow::onpeiz15(int fasheji)
{
    notifyManager.notify("信息", "信道编码下发回传:下发成功" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("信道编码下发回传:下发成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("信道编码下发回传:下发成功" , "发射机2");
    }
}

void MainWindow::onsbpeiz15(int fasheji)
{
    notifyManager.notify("信息", "信道编码下发回传:下传失败" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("信道编码下发回传:下传失败" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("信道编码下发回传:下传失败" , "发射机2");
    }
}

void MainWindow::onpeiz17(int fasheji)
{
    notifyManager.notify("信息", "pcm下发回传:下发成功" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("pcm下发回传:下发成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("pcm下发回传:下发成功" , "发射机2");
    }
}

void MainWindow::onsbpeiz17(int fasheji)
{
    notifyManager.notify("信息", "pcm下发回传:下传失败" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("pcm下发回传:下传失败" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("pcm下发回传:下传失败" , "发射机2");
    }
}

void MainWindow::onpeiz19(int fasheji)
{
    notifyManager.notify("信息", "异步源下发回传:下传成功" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("异步源下发回传:下传成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("异步源下发回传:下传成功" , "发射机2");
    }
}

void MainWindow::onsbpeiz19(int fasheji)
{
    notifyManager.notify("信息", "异步源下发回传:下传失败" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("异步源下发回传:下传失败" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("异步源下发回传:下传失败" , "发射机2");
    }
}

void MainWindow::onpeiz1B(int fasheji)
{
    notifyManager.notify("信息", "安控接收配置:下传成功" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("安控接收配置:下传成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("安控接收配置:下传成功" , "发射机2");
    }
}

void MainWindow::onsbpeiz1B(int fasheji)
{
    notifyManager.notify("信息", "安控接收配置:下传失败" , "qrc:/qrc/5.png", "");

    if(fasheji == 1)
    {
        setmaintable("安控接收配置:下传失败" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("安控接收配置:下传失败" , "发射机2");
    }
}

void MainWindow::onpeiz1f(int fasheji)
{
    honghumachi++;

    if(honghumachi > 2)
    {
        notifyManager.notify("信息", "用户码下发回传:下发成功" , "qrc:/qrc/5.png", "");
        honghumachi = 0;
    }

    if(fasheji == 1)
    {
        setmaintable("用户码下发回传:下发成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("用户码下发回传:下发成功" , "发射机2");
    }
}

void MainWindow::onsbpeiz1f(int fasheji)
{
    notifyManager.notify("信息", "用户码下发回传:下传失败" , "://resourse/images/PNG/15.png", "");

    if(fasheji == 1)
    {
        setmaintable("用户码下发回传:下传失败" , "发射机1");
    }
    else if(fasheji == 2)
    {
        setmaintable("用户码下发回传:下传失败" , "发射机2");
    }
}

void MainWindow::onankongupdate()
{
//    ui->lineEdit_k1->setText(QString::number(ankongjiegongK1.kValue));
//    ui->lineEdit_k2->setText(QString::number(ankongjiegongK2.kValue));
//    ui->lineEdit_k3->setText(QString::number(ankongjiegongK3.kValue));
//    ui->lineEdit_k4->setText(QString::number(ankongjiegongK4.kValue));

}

void MainWindow::onupdateStatus()
{

    m_mutex.lock();

    //系统状态数据回传
    m_tx1_freq_point = m_PTransceiverConfig_RES->tx1_freq;      // 频点 (4B)
    m_carrier_switch1 = m_PTransceiverConfig_RES->tx1_bits.tx1_carrier;  // 载波开关 (bit0)
    m_modulator_switch1 = m_PTransceiverConfig_RES->tx1_bits.tx1_mod; // 调制开关 (bit1)
    m_tx1_buffer_capacity1 = m_PTransceiverConfig_RES->tx1_cache_size;   // 模飞缓存容量 (2B)


    m_tx2_freq_point = m_PTransceiverConfig_RES->tx2_freq;      // 频点 (4B)
    m_carrier_switch2 = m_PTransceiverConfig_RES->tx2_bits.tx2_carrier;  // 载波开关 (bit0)
    m_modulator_switch2 = m_PTransceiverConfig_RES->tx2_bits.tx2_mod; // 调制开关 (bit1)
    m_tx2_buffer_capacity2 = m_PTransceiverConfig_RES->tx2_cache_size;   // 模飞缓存容量 (2B)

    m_security_recv_power = m_PTransceiverConfig_RES->sec_rx_power;    // 安控接收功率 (1B)
    m_frame_lock = m_PTransceiverConfig_RES->sec_bits.frame_lock;      // 安控帧锁定 (bit0)

    m_mutex.unlock();


}





void MainWindow::updateui1()
{
    ui->lineEdit_fuzhengfs1->setText(QString(fuzhengfangshi));
    ui->lineEdit_zhengmazu->setText(QString(zhengmazu));

    ui->lineEdit_malv->setText(QString(malv));
    ui->lineEdit_maxing->setText(QString(maxing));
    ui->lineEdit_bianmawz->setText(QString(bianmawz));

    ui->lineEdit_pingdian->setText(QString(pingdian));
    ui->lineEdit_pinpian->setText(QString(pinpian));
    ui->lineEdit_tiaoz->setText(QString(tiaoz));
    ui->lineEdit_gonglv->setText(QString(gonglv));

    ui->lineEdit_fuzhengchang->setText(QString(fuzhengchang));

    ui->lineEdit_zhenchang1->setText(QString(zhenchang));
    //ui->lineEdit_tiaozhikaiguan->setText(QString(tiaozhikaiguan));



}

void MainWindow::updateui2()
{
    ui->lineEdit_fuzhengfs1_2->setText(QString(fuzhengfangshi2));
    ui->lineEdit_zhengmazu_2->setText(QString(zhengmazu2));
    ui->lineEdit_malv_2->setText(QString(malv2));
    ui->lineEdit_maxing_2->setText(QString(maxing2));
    ui->lineEdit_bianmawz_2->setText(QString(bianmawz2));

    ui->lineEdit_pingdian_2->setText(QString(pingdian2));
    ui->lineEdit_pinpian_2->setText(QString(pinpian2));
    ui->lineEdit_tiaoz_2->setText(QString(tiaoz2));
    ui->lineEdit_gonglv_2->setText(QString(gonglv2));

    ui->lineEdit_fuzhengchang_2->setText(QString(fuzhengchang2));



    ui->lineEdit_zhenchang2->setText(QString(zhenchang2));
    //ui->lineEdit_tiaozhikaiguan2->setText(QString(tiaozhikaiguan2));

}

void MainWindow::initui()
{

}

quint32 MainWindow::crc32(const QByteArray &array)
{
    quint32 crc = 0xFFFFFFFF;                     // 初始值
     const quint8 *addr = reinterpret_cast<const quint8*>(array.constData());
     int num = array.size();

     for (; num > 0; num--) {
         quint8 byte = *addr++;
         byte = reverse8(byte);                    // 字节反转
         crc ^= (static_cast<quint32>(byte) << 24); // 与crc高8位异或

         for (int i = 0; i < 8; i++) {             // 循环处理8位
             if (crc & 0x80000000) {               // 最高位为1
                 crc = (crc << 1) ^ 0x04C11DB7;    // 左移后异或多项式
             } else {
                 crc <<= 1;                        // 直接左移
             }
         }
     }

     crc = reverse32(crc);                         // 反转32位
     crc ^= 0xFFFFFFFF;                            // 异或结果值
     return crc;
}

quint8 MainWindow::reverse8(quint8 data)
{
    quint8 i;
    quint8 temp = 0;
    for (i = 0; i < 8; i++)	    				// 8 bit反转
        temp |= ((data >> i) & 0x01) << (7 - i);
    return temp;
}

quint32 MainWindow::reverse32(quint32 data)
{
    quint8 i;
    quint32 temp = 0;
    for (i = 0; i < 32; i++)					// 32 bit反转
        temp |= ((data >> i) & 0x01) << (31 - i);
    return temp;
}

bool MainWindow::getBit(quint8 byte, quint8 position)
{
    return (byte >> position) & 0x1;
}

void MainWindow::StartandQuitTransmitter(int transmitterflag1, int transmitterflag2)
{
    m_PPACKET_HEADER = new PACKET_HEADER;
    m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    m_PPACKET_HEADER->functionCode = 0x20;
    m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x09);
    m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

    m_TransmissionDataBegin.bits.bit0 = transmitterflag1;
    m_TransmissionDataBegin.bits.bit1 = transmitterflag2;

    QByteArray array;
    array.append(reinterpret_cast<const char*>(m_PPACKET_HEADER),
                                                   sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(&m_TransmissionDataBegin),
                                                 sizeof(TransmissionDataBegin));//    quint8  txSelector;        // 发射机选择 [1B]

    quint32 m_crc32 = crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    udpManager->sendDatagram(array);

    qDebug() << array.toHex();

}


void MainWindow::on_Btn_startFly_clicked()
{
  if(ui->Btn_startFly->text() == "开始模飞")
  {
      if(ui->lineEdit_mofeifile1->text().isEmpty())
      {
          QMessageBox::information(this , "提示" , "文件路径为空");
          return;
      }


      m_PPACKET_HEADER = new PACKET_HEADER;
      m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
      m_PPACKET_HEADER->functionCode = 0x01;
      m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
      m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
      m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

      m_PTELEMETRY_FRAME = new TELEMETRY_FRAME;

      QSettings settings("settings.ini", QSettings::IniFormat);


      m_PTELEMETRY_FRAME->txSelector = 0x01;

      settings.beginGroup("SyncCoding");
      double malv = settings.value("Malv", "10000").toString().toDouble();
      quint32 byteValue32 = static_cast<quint32>(malv * 1000   * 4294967296 / fo); // 0x01
      m_PTELEMETRY_FRAME->pcmRate = qToLittleEndian<quint32>(byteValue32);
      settings.endGroup();


     quint16 byteValue16;
     quint8 byteValue8;

     settings.beginGroup("BasicParameters");
     byteValue16 = static_cast<quint16>(settings.value("zhenchang", "256").toString().toInt() - 1);

     m_PTELEMETRY_FRAME->subFrameLength.bit.length = qToLittleEndian<quint16>(byteValue16);
     m_PTELEMETRY_FRAME->subFrameLength.bit.moFeiFlag = 1;
     settings.endGroup();


     settings.beginGroup("Modulation");
     if(settings.value("fuzhenfanshi", "2FSK").toString() == "无副帧")
     {
         byteValue8 = 0x00;
     }
     else
     {
         byteValue8 = static_cast<quint8>(settings.value("fuzhenchangdu", "128").toString().toInt() - 1);

     }

     byteValue8 = static_cast<quint8>(settings.value("fuzhenchangdu", "128").toString().toInt() - 1); // 0x01
     m_PTELEMETRY_FRAME->subFrameCount = qToLittleEndian<quint16>(byteValue8);
     settings.endGroup();

     settings.beginGroup("BasicParameters");
     m_PTELEMETRY_FRAME->WordConfig.bits.wordLengthMinusOne = static_cast<quint8>(settings.value("zichang", "1000").toString().toInt() -1);
     quint8 codeType;
     settings.endGroup();

     settings.beginGroup("Modulation");
     QString maxing  = settings.value("maxing", "RZ").toString();

     if (maxing == "NRZ-L")
     {
         m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000000;
     }

     else if (maxing == "WRZ-M")
     {
         m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000010;
     }

     else if (maxing == "NRZ-S")
     {
         m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000011;
     }
     else if (maxing == "BIφ-L")
     {
         m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000100;
     }

     else if (maxing == "BIφ-M")
     {
         m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000110;
     }


     else if (maxing == "BIφ-S")
     {
         m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000111;
     }


     else if (maxing == "RNRZ-L")
     {
         m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00001000;
     }

     settings.endGroup();
     settings.beginGroup("Sequences");

     byteValue16 = settings.value("fuzhenlvxu", "0").toString().toInt() - 1 ; //ID码副帧时, 副帧的ID码所在路序-1。循环码副帧时，副帧特征字在子帧的路序-1
     m_PTELEMETRY_FRAME->featurePosition = qToLittleEndian<quint16>(byteValue16);
     settings.endGroup();
     settings.beginGroup("Sequences");
     bool convertOk;
     QString processed = settings.value("zhenmazhu", "0").toString().trimmed().toUpper();
     quint64 byteValue64 = processed.toULongLong(&convertOk , 16);
     m_PTELEMETRY_FRAME->syncCode = qToLittleEndian<quint64>(byteValue64);
     settings.endGroup();
     settings.beginGroup("SyncCoding");
     processed =  settings.value("xhfztongbuma", "1010").toString().trimmed().toUpper();
     byteValue16 = processed.toULongLong(&convertOk , 16);
     m_PTELEMETRY_FRAME->loopSyncCode = qToLittleEndian<quint16>(byteValue16);
     settings.endGroup();

      quint8 subframeType ;
      quint8 bitLengthMinusOne;
      settings.beginGroup("Modulation");

     if(settings.value("fuzhenfanshi", "2FSK").toString() == "无副帧")
     {
         subframeType = 0 ;
     }

     else if(settings.value("fuzhenfanshi", "2FSK").toString() == "反码副帧")

     {
         subframeType = 2 ;
     }

     else if(settings.value("fuzhenfanshi", "2FSK").toString() == "循环副帧")
     {
         subframeType = 1 ;
     }

     else if(settings.value("fuzhenfanshi", "2FSK").toString() == "ID副帧")
     {
         subframeType = 3 ;
     }
     settings.endGroup();
     settings.beginGroup("Sequences");
     bitLengthMinusOne = settings.value("zhenmazhu", "0").toString().size() * 4 - 1;


     byteValue8 = (subframeType << 6) | bitLengthMinusOne ;

     m_PTELEMETRY_FRAME->frameType = byteValue8;


     for(int i = 0 ; i < 5 ; i++)
     {

         m_PTELEMETRY_FRAME->reserved1[i] = 0x00;
     }
     settings.endGroup();
     settings.beginGroup("BasicParameters");
     if( settings.value("xinhaoneixing", "QPSK").toString() == "台阶码")
     {
         byteValue8 = 0x00;
     }
     else
     {
         byteValue8 = 0x01;
     }
     m_PTELEMETRY_FRAME->dataType = qToLittleEndian<quint8>(byteValue8);
     settings.endGroup();
     // 步进控制组
     settings.beginGroup("StepControl");
     byteValue16 = settings.value("tjmbujin", "1").toString().toInt();
     m_PTELEMETRY_FRAME->stepValue = qToLittleEndian<quint8>(byteValue16);


     byteValue16 = settings.value("tjmchushizi", "0").toString().toInt();
     m_PTELEMETRY_FRAME->initStep = qToLittleEndian<quint16>(byteValue16);
     settings.endGroup();


     settings.beginGroup("Relay");
     if(settings.value("bujielow", "1").toInt() == 0)
     {
         m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 0x01;
     }
     else if(settings.value("bujielow", "1").toInt() == 1)
     {
         m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 0x00;
     }

     if(settings.value("bujiehigh", "1").toInt() == 0)
     {
         m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 0x01;
     }
     else if(settings.value("bujiehigh", "1").toInt() == 1)
     {
         m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 0x00;
     }

     byteValue16 = settings.value("zjsdzjbodao", "1").toString().toInt();
     m_PTELEMETRY_FRAME->FrameCalcChannel.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;


     byteValue16 = settings.value("zjsgzjbodao", "2").toString().toInt();
     m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;
     settings.endGroup();
     for(int i = 0 ; i < 4 ; i++)
     {
         m_PTELEMETRY_FRAME->reserved2[i] = 0x00;
     }





     // ID管理组
     settings.beginGroup("Identification");
     if(settings.value("IDzijishufangshi", "0").toString() == "加计数")
     {
         m_PTELEMETRY_FRAME->bits.bit1 = 0x00;
     }
     else if(settings.value("IDzijishufangshi", "0").toString() == "减计数")
     {
         m_PTELEMETRY_FRAME->bits.bit1 = 0x01;
     }

     if(settings.value("IDzijizhi", "127").toString() == "0开始")
     {
         m_PTELEMETRY_FRAME->bits.bit0 = 0x00;
     }
     else if(settings.value("IDzijizhi", "127").toString() == "1开始")
     {
         m_PTELEMETRY_FRAME->bits.bit0 = 0x01;
     }
    m_PTELEMETRY_FRAME->bits.reserved = 0x00;
    settings.endGroup();


    settings.beginGroup("SyncCoding");
    if(settings.value("Bianmaweizhi", "5").toString() == "编码前")
    {
        m_PTELEMETRY_FRAME->codingPosition = 0x01;

    }
    else if(settings.value("Bianmaweizhi", "5").toString() == "编码后")
    {
        m_PTELEMETRY_FRAME->codingPosition = 0x00;
    }
    settings.endGroup();

     for(int i = 0 ; i < 22 ; i++)
     {
         m_PTELEMETRY_FRAME->reserved3[i] = 0x00;
     }


         QByteArray array;
         array.append(reinterpret_cast<const char*>(m_PPACKET_HEADER),
                                                        sizeof(PACKET_HEADER));
         array.append(reinterpret_cast<const char*>(m_PTELEMETRY_FRAME),
                                                      sizeof(TELEMETRY_FRAME));//    quint8  txSelector;        // 发射机选择 [1B]

         quint32 m_crc32 = crc32(array);  // 确保 crc32 返回栈变量
         m_crc32 = qToLittleEndian<quint32>(m_crc32);
         array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

         int i  = 1 ;
         for (quint8 byte : array) {
                       QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                       qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                   }

         udpManager->sendDatagram(array);



         QString filePath = ui->lineEdit_mofeifile1->text();
         int zhengchang1 = ui->lineEdit_zhenchang1->text().toInt();

         QFileInfo fileInfo(filePath);

         // 检查文件是否存在且是普通文件（非目录）
         if (fileInfo.exists() && fileInfo.isFile()) {
             mofiCapacity1 = fileInfo.size(); // 获取文件长度
             mofiCapacity1 = mofiCapacity1 / (zhengchang1 + 8);
             mofiCapacity1 = mofiCapacity1 * zhengchang1;
             qDebug() << mofiCapacity1;

             // 检查是否可读
             if (fileInfo.isReadable()) {
                 // 尝试实际打开文件以确认
                 QFile file(filePath);
                 if (file.open(QIODevice::ReadOnly)) {
                     // 文件可以成功打开
                     qDebug() << "文件可以打开";
                     file.close();
                 } else {
                     // 文件存在但无法打开（可能被占用）
                     QMessageBox::information(this , "错误", "文件存在但无法打开：" + file.errorString());
                     return;
                 }
             }
             else {
                 // 文件不可读（权限问题）
                 QMessageBox::information(this , "错误", "文件不可读（权限不足）");
                 return;
             }
         } else {
             // 文件不存在或是目录
              QMessageBox::information(this , "错误", "文件不存在或不是普通文件");
              return;
         }


         QByteArray* m_array1 = new QByteArray;
         QByteArray* m_array2 = new QByteArray;





         parentThread = new QThread;
         parentWorker = new ParentWorker(m_array1 , m_array2 , filePath , zhengchang1);
         parentWorker->setsharedMutex(&mofei_mutex);
         parentWorker->setzhengchang(zhengchang1);
         parentWorker->moveToThread(parentThread);



         connect(worker, &Worker::readRequest1,
         parentWorker, &ParentWorker::read_tx1_buffer_capacity
                 , Qt::QueuedConnection);



         connect(parentWorker, &ParentWorker::progressting,
         this, &MainWindow::onupdateprogressBar);

         transmitterflag1 = 0;
         StartandQuitTransmitter(transmitterflag1,transmitterflag2);
         quitdatafile1();

         parentThread->start();

         ui->Btn_startFly->setText("停止模飞");

  }

  else if(ui->Btn_startFly->text() == "停止模飞")
  {

      disconnect(worker, &Worker::readRequest1,
      parentWorker, &ParentWorker::read_tx1_buffer_capacity);

      disconnect(parentWorker, &ParentWorker::progressting,
      this, &MainWindow::onupdateprogressBar);


      parentThread->quit();

      // 等待线程安全退出（最多等待2秒）
      if (!parentThread->wait(2000)) {
          // 如果线程未响应，则终止（谨慎使用）
          qWarning() << "Thread not responding, terminating";
          parentThread->terminate();
          parentThread->wait();
      }

        parentWorker->deleteLater();
        parentWorker = nullptr;
        transmitterflag1 = 1;
        StartandQuitTransmitter(transmitterflag1,transmitterflag2);
        //emit startdatafile1();
        ui->Btn_startFly->setText("开始模飞");

        QMessageBox::information(this , "提示" , "停止成功");

  }



}




void MainWindow::on_Btn_startFly2_clicked()
{
//    disconnect(worker, &Worker::readoAll,
//    workerProcessing, &WorkerProcessing::on_read_buffer);
    if(ui->Btn_startFly2->text() == "开始模飞")
    {

        if(ui->lineEdit_mofeifile2->text().isEmpty())
        {
            QMessageBox::information(this , "提示" , "文件路径为空");
            return;
        }


        m_PPACKET_HEADER = new PACKET_HEADER;
        m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
        m_PPACKET_HEADER->functionCode = 0x01;
        m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
        m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
        m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

        m_PTELEMETRY_FRAME = new TELEMETRY_FRAME;

        QSettings settings("settings.ini", QSettings::IniFormat);


        m_PTELEMETRY_FRAME->txSelector = 0x02;

        settings.beginGroup("SyncCoding2");
        double malv = settings.value("Malv2", "10000").toDouble();
        quint32 byteValue32 = static_cast<quint32>(malv * 1000   * 4294967296 / fo); // 0x01
        m_PTELEMETRY_FRAME->pcmRate = qToLittleEndian<quint32>(byteValue32);
        settings.endGroup();


       quint16 byteValue16;
       quint8 byteValue8;

       settings.beginGroup("BasicParameters2");
       byteValue16 = static_cast<quint16>(settings.value("zhenchang2", "256").toString().toInt() - 1);

       m_PTELEMETRY_FRAME->subFrameLength.bit.length = qToLittleEndian<quint16>(byteValue16);
       m_PTELEMETRY_FRAME->subFrameLength.bit.moFeiFlag = 1;
       settings.endGroup();


       settings.beginGroup("Modulation2");
       if(settings.value("fuzhenfanshi2", "2FSK").toString() == "无副帧")
       {
           byteValue8 = 0x00;
       }
       else
       {
           byteValue8 = static_cast<quint8>(settings.value("fuzhenchangdu2", "128").toString().toInt() - 1);

       }

       byteValue8 = static_cast<quint8>(settings.value("fuzhenchangdu2", "128").toString().toInt() - 1); // 0x01
       m_PTELEMETRY_FRAME->subFrameCount = qToLittleEndian<quint16>(byteValue8);
       settings.endGroup();

       settings.beginGroup("BasicParameters2");
       m_PTELEMETRY_FRAME->WordConfig.bits.wordLengthMinusOne = static_cast<quint8>(settings.value("zichang", "1000").toString().toInt() -1);
       quint8 codeType;
       settings.endGroup();

       settings.beginGroup("Modulation2");
       QString maxing  = settings.value("maxing", "RZ").toString();

       if (maxing == "NRZ-L")
       {
           m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000000;
       }

       else if (maxing == "WRZ-M")
       {
           m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000010;
       }

       else if (maxing == "NRZ-S")
       {
           m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000011;
       }
       else if (maxing == "BIφ-L")
       {
           m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000100;
       }

       else if (maxing == "BIφ-M")
       {
           m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000110;
       }


       else if (maxing == "BIφ-S")
       {
           m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000111;
       }


       else if (maxing == "RNRZ-L")
       {
           m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00001000;
       }
       settings.endGroup();
       settings.beginGroup("Sequences2");
       //    fuzhenlvxu = settings.value("fuzhenlvxu", "0").toString();

       byteValue16 = settings.value("fuzhenlvxu2", "0").toString().toInt() - 1 ; //ID码副帧时, 副帧的ID码所在路序-1。循环码副帧时，副帧特征字在子帧的路序-1
       m_PTELEMETRY_FRAME->featurePosition = qToLittleEndian<quint16>(byteValue16);
       settings.endGroup();
       settings.beginGroup("Sequences2");
       bool convertOk;
       QString processed = settings.value("zhenmazhu2", "0").toString().trimmed().toUpper();
       quint64 byteValue64 = processed.toULongLong(&convertOk , 16);
       m_PTELEMETRY_FRAME->syncCode = qToLittleEndian<quint64>(byteValue64);
       settings.endGroup();
       settings.beginGroup("SyncCoding2");
       processed =  settings.value("xhfztongbuma2", "1010").toString().trimmed().toUpper();
       byteValue16 = processed.toULongLong(&convertOk , 16);
       m_PTELEMETRY_FRAME->loopSyncCode = qToLittleEndian<quint16>(byteValue16);
       settings.endGroup();

        quint8 subframeType ;
        quint8 bitLengthMinusOne;
        settings.beginGroup("Modulation2");

       if(settings.value("fuzhenfanshi2", "2FSK").toString() == "无副帧")
       {
           subframeType = 0 ;
       }

       else if(settings.value("fuzhenfanshi2", "2FSK").toString() == "反码副帧")

       {
           subframeType = 2 ;
       }

       else if(settings.value("fuzhenfanshi2", "2FSK").toString() == "循环副帧")
       {
           subframeType = 1 ;
       }

       else if(settings.value("fuzhenfanshi2", "2FSK").toString() == "ID副帧")
       {
           subframeType = 3 ;
       }
       settings.endGroup();
       settings.beginGroup("Sequences2");
       bitLengthMinusOne = settings.value("zhenmazhu2", "0").toString().size() * 4 - 1;


       byteValue8 = (subframeType << 6) | bitLengthMinusOne ;

       m_PTELEMETRY_FRAME->frameType = byteValue8;


       for(int i = 0 ; i < 5 ; i++)
       {

           m_PTELEMETRY_FRAME->reserved1[i] = 0x00;
       }
       settings.endGroup();
       settings.beginGroup("BasicParameters2");
       if( settings.value("xinhaoneixing2", "QPSK").toString() == "台阶码")
       {
           byteValue8 = 0x00;
       }
       else
       {
           byteValue8 = 0x01;
       }
       m_PTELEMETRY_FRAME->dataType = qToLittleEndian<quint8>(byteValue8);
       settings.endGroup();
       // 步进控制组
       settings.beginGroup("StepControl2");
       byteValue16 = settings.value("tjmbujin2", "1").toString().toInt();
       m_PTELEMETRY_FRAME->stepValue = qToLittleEndian<quint8>(byteValue16);


       byteValue16 = settings.value("tjmchushizi2", "0").toString().toInt();
       m_PTELEMETRY_FRAME->initStep = qToLittleEndian<quint16>(byteValue16);
       settings.endGroup();


       settings.beginGroup("Relay2");
       if(settings.value("bujielow2", "1").toInt() == 0)
       {
           m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 0x01;
       }
       else if(settings.value("bujielow2", "1").toInt() == 1)
       {
           m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 0x00;
       }

       if(settings.value("bujiehigh2", "1").toInt() == 0)
       {
           m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 0x01;
       }
       else if(settings.value("bujiehigh2", "1").toInt() == 1)
       {
           m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 0x00;
       }

       byteValue16 = settings.value("zjsdzjbodao2", "1").toString().toInt();
       m_PTELEMETRY_FRAME->FrameCalcChannel.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;


       byteValue16 = settings.value("zjsgzjbodao2", "2").toString().toInt();
       m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;
       settings.endGroup();
       for(int i = 0 ; i < 4 ; i++)
       {
           m_PTELEMETRY_FRAME->reserved2[i] = 0x00;
       }





       // ID管理组
       settings.beginGroup("Identification2");
       if(settings.value("IDzijishufangshi2", "0").toString() == "加计数")
       {
           m_PTELEMETRY_FRAME->bits.bit1 = 0x00;
       }
       else if(settings.value("IDzijishufangshi2", "0").toString() == "减计数")
       {
           m_PTELEMETRY_FRAME->bits.bit1 = 0x01;
       }

       if(settings.value("IDzijizhi2", "127").toString() == "0开始")
       {
           m_PTELEMETRY_FRAME->bits.bit0 = 0x00;
       }
       else if(settings.value("IDzijizhi2", "127").toString() == "1开始")
       {
           m_PTELEMETRY_FRAME->bits.bit0 = 0x01;
       }
      m_PTELEMETRY_FRAME->bits.reserved = 0x00;
      settings.endGroup();


      settings.beginGroup("SyncCoding2");
      if(settings.value("Bianmaweizhi2", "5").toString() == "编码前")
      {
          m_PTELEMETRY_FRAME->codingPosition = 0x01;

      }
      else if(settings.value("Bianmaweizhi2", "5").toString() == "编码后")
      {
          m_PTELEMETRY_FRAME->codingPosition = 0x00;
      }
      settings.endGroup();

       for(int i = 0 ; i < 22 ; i++)
       {
           m_PTELEMETRY_FRAME->reserved3[i] = 0x00;
       }


           QByteArray array;
           array.append(reinterpret_cast<const char*>(m_PPACKET_HEADER),
                                                          sizeof(PACKET_HEADER));
           array.append(reinterpret_cast<const char*>(m_PTELEMETRY_FRAME),
                                                        sizeof(TELEMETRY_FRAME));//    quint8  txSelector;        // 发射机选择 [1B]

           quint32 m_crc32 = crc32(array);  // 确保 crc32 返回栈变量
           m_crc32 = qToLittleEndian<quint32>(m_crc32);
           array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

           int i  = 1 ;
           for (quint8 byte : array) {
                         QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                         qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                     }

           udpManager->sendDatagram(array);


           QString filePath = ui->lineEdit_mofeifile2->text();
           int zhengchang2 = ui->lineEdit_zhenchang2->text().toInt();

           QFileInfo fileInfo(filePath);



           // 检查文件是否存在且是普通文件（非目录）
           if (fileInfo.exists() && fileInfo.isFile()) {
               mofiCapacity2 = fileInfo.size(); // 获取文件长度
               mofiCapacity2 = mofiCapacity2 / (zhengchang2 + 8);
               mofiCapacity2 = mofiCapacity2 * zhengchang2;

               // 检查是否可读
               if (fileInfo.isReadable()) {
                   // 尝试实际打开文件以确认
                   QFile file(filePath);
                   if (file.open(QIODevice::ReadOnly)) {
                       // 文件可以成功打开
                       qDebug() << "文件可以打开";
                       file.close();
                   } else {
                       // 文件存在但无法打开（可能被占用）
                       QMessageBox::information(this , "错误", "文件存在但无法打开：" + file.errorString());
                       return;
                   }
               }
               else {
                   // 文件不可读（权限问题）
                   QMessageBox::information(this , "错误", "文件不可读（权限不足）");
                   return;
               }
           } else {
               // 文件不存在或是目录
                QMessageBox::information(this , "错误", "文件不存在或不是普通文件");
                return;
           }



           QByteArray* m_array1 = new QByteArray;
           QByteArray* m_array2 = new QByteArray;

           parentThread2 = new QThread;
           parentWorker2 = new ParentWorker(m_array1 , m_array2 , filePath , zhengchang2);
           parentWorker2->setzhengchang(zhengchang2);
           parentWorker2->setsharedMutex(&mofei_mutex);
           parentWorker2->moveToThread(parentThread2);


           connect(worker, &Worker::readRequest2,
           parentWorker2, &ParentWorker::read_tx2_buffer_capacity
                   , Qt::QueuedConnection);



           connect(parentWorker2, &ParentWorker::progressting,
           this, &MainWindow::onupdateprogressBar_2
                   , Qt::QueuedConnection);

           transmitterflag2 = 0;
           StartandQuitTransmitter(transmitterflag1,transmitterflag2);
           quitdatafile2();


           parentThread2->start();

             ui->Btn_startFly2->setText("停止模飞");





    }

    else if(ui->Btn_startFly2->text() == "停止模飞")
    {
        disconnect(worker, &Worker::readRequest2,
        parentWorker2, &ParentWorker::read_tx2_buffer_capacity);

        disconnect(parentWorker2, &ParentWorker::progressting,
        this, &MainWindow::onupdateprogressBar_2);


        parentThread2->quit();

        // 等待线程安全退出（最多等待2秒）
        if (!parentThread2->wait(2000)) {
            // 如果线程未响应，则终止（谨慎使用）
            qWarning() << "Thread not responding, terminating";
            parentThread2->terminate();
            parentThread2->wait();
        }

          parentWorker2->deleteLater();
          parentWorker2 = nullptr;

          transmitterflag2 = 1;
          StartandQuitTransmitter(transmitterflag1,transmitterflag2);
          //emit startdatafile2();
             ui->Btn_startFly2->setText("开始模飞");

             QMessageBox::information(this , "提示" , "停止成功");
    }

}

void  MainWindow::delaySomeTime(int timeSleep)
{
    //    QEventLoop eventLoop;
    //    QTimer::singleShot(timeSleep,&eventLoop,SLOT(quit()));
    //    eventLoop.exec();

    QTimer::singleShot(timeSleep, [=]() {
        //        qDebug() << "使用lambda表达式在"+QString::number(timeSleep)+"毫秒后执行";
    });


    //    QEventLoop eventLoop;

    //    QTimer timer;
    //    QObject::connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    //    timer.start(timeSleep);

    //    eventLoop.exec(); // 进入事件循环，直到timer超时

    //    timer.stop(); // 停止定时器

}


void MainWindow::on_Btn_wenjianselect1_clicked()
{

    QSettings settings("settings.ini", QSettings::IniFormat);
    filepath1 = settings.value("lastPath1", QDir::homePath()).toString();



    QString fileName = QFileDialog::getOpenFileName(
        Q_NULLPTR, // 父窗口
        tr("Open File"), // 对话框标题
        filepath1, // 初始目录
        tr("Files (*.dat);;Text Files (*.txt)")); // 文件过滤器

    if (!fileName.isEmpty()) {
            // 提取目录路径
             filepath1 = QFileInfo(fileName).absolutePath();
            // 保存新路径
            settings.setValue("lastPath1", filepath1);
                             }

    ui->lineEdit_mofeifile1->setText(fileName);

    QFile file(fileName);


    mofiCapacity1 = file.size();

}

void MainWindow::on_Btn_wenjianselect2_clicked()
{
    QSettings settings("settings.ini", QSettings::IniFormat);
    filepath2 = settings.value("lastPath2", QDir::homePath()).toString();



    QString fileName = QFileDialog::getOpenFileName(
        Q_NULLPTR, // 父窗口
        tr("Open File"), // 对话框标题
        filepath2,
        tr("Files (*.dat);;Text Files (*.txt)")); // 文件过滤器

    ui->lineEdit_mofeifile2->setText(fileName);

    if (!fileName.isEmpty()) {
            // 提取目录路径
             filepath2 = QFileInfo(fileName).absolutePath();
            // 保存新路径
            settings.setValue("lastPath2", filepath2);
                             }

    QFile file(fileName);


    mofiCapacity2 = file.size();
}

void MainWindow::on_Btn_file_clicked()
{
    m_fileMacroDialog = new fileMacroDialog(this);
    m_fileMacroDialog->setOwner(this);
    m_fileMacroDialog->setFixedSize(520 ,640);

    m_fileMacroDialog->show();


}



void MainWindow::onupdateprogressBar(long long value)
{
    double temp = static_cast<double>(value) / mofiCapacity1;  // 改为浮点除法
    double percent = temp * 100.0;                            // 转换为百分比值
    int progressValue = static_cast<int>(std::round(percent)); // 四舍五入到整数

    qDebug() << mofiCapacity1 << value << percent << progressValue;

    ui->progressBar->setValue(progressValue);

    if(temp >= 1.00)
    {
        disconnect(worker, &Worker::readRequest1,
        parentWorker, &ParentWorker::read_tx1_buffer_capacity);

        disconnect(parentWorker, &ParentWorker::progressting,
        this, &MainWindow::onupdateprogressBar);


        parentThread->quit();

        // 等待线程安全退出（最多等待2秒）
        if (!parentThread->wait(2000)) {
            // 如果线程未响应，则终止（谨慎使用）
            qWarning() << "Thread not responding, terminating";
            parentThread->terminate();
            parentThread->wait();
        }

          parentWorker->deleteLater();
          parentWorker = nullptr;

             ui->Btn_startFly->setText("开始模飞");

        //ui->Btn_startFly->setText("开始模飞");

        QMessageBox::information(this , "提示" , "模飞完成");
    }
}

void MainWindow::onupdateprogressBar_2( long long value)
{

    double temp = static_cast<double>(value) / mofiCapacity2;  // 改为浮点除法
    double percent = temp * 100.0;                            // 转换为百分比值
    int progressValue = static_cast<int>(std::round(percent)); // 四舍五入到整数

    qDebug() << mofiCapacity2 << value << percent << progressValue;


    ui->progressBar_5->setValue(progressValue);


    if(temp >= 1.00)
    {
        disconnect(worker, &Worker::readRequest2,
        parentWorker2, &ParentWorker::read_tx2_buffer_capacity);

        disconnect(parentWorker2, &ParentWorker::progressting,
        this, &MainWindow::onupdateprogressBar_2);


        parentThread2->quit();

        // 等待线程安全退出（最多等待2秒）
        if (!parentThread2->wait(2000)) {
            // 如果线程未响应，则终止（谨慎使用）
            qWarning() << "Thread not responding, terminating";
            parentThread2->terminate();
            parentThread2->wait();
        }

          parentWorker2->deleteLater();
          parentWorker2 = nullptr;

             ui->Btn_startFly2->setText("开始模飞");

        //ui->Btn_startFly2->setText("开始模飞");

        QMessageBox::information(this , "提示" , "模飞完成");
    }

}

void MainWindow::onupdateK(quint8 value, quint16 Power_amplifier1 , quint16 Power_amplifier2)
{
    bool bit0 = getBit(value, 0);
    bool bit1 = getBit(value, 1);
    bool bit2 = getBit(value, 2);
    bool bit3 = getBit(value, 3);

    QString time = QDateTime::currentDateTime().toString();


    if(bit0 == false)
    {
        ui->label_pixmapK1->setPixmap(result);
        isgreen_K1 = false;
    }

    else if(bit0 == true && isgreen_K1 == false)
    {
        ui->label_pixmapK1->setPixmap(result2);
        file.write(QString("K1点亮:" + time + "\n").toUtf8());
        isgreen_K1 = true;
    }

    else if(bit0 == true && isgreen_K1 == true)
    {
        ui->label_pixmapK1->setPixmap(result2);
    }

    if(bit2 == false)
    {
        ui->label_pixmapK2->setPixmap(result);
        isgreen_K2 = false;
    }

    else if(bit2 == true && isgreen_K2 == false)
    {
        ui->label_pixmapK2->setPixmap(result2);
        file.write(QString("K3点亮:" + time + "\n").toUtf8());
        isgreen_K2 = true;
    }

    else if(bit2 == true && isgreen_K2 == true)
    {
        ui->label_pixmapK2->setPixmap(result2);
    }

    if(bit1 == false)
    {
        ui->label_pixmapK3->setPixmap(result);
        isgreen_K3 = false;
    }

    else if(bit1 == true && isgreen_K3 == false)
    {
        ui->label_pixmapK3->setPixmap(result2);
        file.write(QString("K2点亮:" + time + "\n").toUtf8());
        isgreen_K3 = true;
    }
    else if(bit1 == true && isgreen_K3 == true)
    {
        ui->label_pixmapK3->setPixmap(result2);
    }

    if(bit3 == false)
    {
        ui->label_pixmapK4->setPixmap(result);
        isgreen_K4 = false;
    }

    else if(bit3 == true && isgreen_K4 == false)
    {
        ui->label_pixmapK4->setPixmap(result2);
        file.write(QString("K4点亮:" + time + "\n").toUtf8());
        isgreen_K4 = true;
    }
    else if(bit3 == true && isgreen_K4 == true)
    {
        ui->label_pixmapK4->setPixmap(result2);

    }

    double Power_amplifier1double =Power_amplifier1 / 10.0;
    double Power_amplifier2double =Power_amplifier2 / 10.0;

    if(Power_amplifier1double > 1.55 && tiaozhikaiguan == "开")
    {
        ui->label_pixmapjiqi->setPixmap(result2);
    }
    else if(Power_amplifier1double > 1.4 && ui->lineEdit_gonglv->text().toInt() <= 8 && ui->lineEdit_gonglv->text().toInt() >= 6 && tiaozhikaiguan == "开")
    {
        ui->label_pixmapjiqi->setPixmap(result2);
    }
    else
    {
       ui->label_pixmapjiqi->setPixmap(result3);
    }



    if(Power_amplifier2double > 1.55 && tiaozhikaiguan2 == "开")
    {
        ui->label_pixmapjiqi_2->setPixmap(result2);
    }
    else if(Power_amplifier2double > 1.4 && ui->lineEdit_gonglv_2->text().toInt() <= 8 && ui->lineEdit_gonglv->text().toInt() >= 6  && tiaozhikaiguan2 == "开")
    {
        ui->label_pixmapjiqi_2->setPixmap(result2);
    }
    else
    {
       ui->label_pixmapjiqi_2->setPixmap(result3);
    }



}




void MainWindow::onLaunchGPS(GpsData gps)
{
    if(gps.longitude == 0.0 && gps.latitude == 0.0 && gps.altitude == 0.0)
    {
      ui->label_pixmapGNSS->setPixmap(result3);
    }
    else
    {
        ui->lineEdit_GNSStime->setText(gps.time.toString("yyyy-MM-dd hh:mm:ss"));
        ui->lineEdit_GNSSlongitude->setText(QString::number(gps.longitude, 'f', 8) + "°");
        ui->lineEdit_GNSSlatitude->setText(QString::number(gps.latitude, 'f', 8) + "°");
        ui->lineEdit_GNSSheight->setText(QString::number(gps.altitude, 'f', 2) + "M");
        ui->lineEdit_GPSweixing->setText(gps.GPS + " 卫星数: " + gps.PRNCount);


        // 合理性检查
        bool isValid = true;
        QString errorMsg;

        // 1. 检查时间
        QDateTime minTime = QDateTime::fromString("1980-01-01T00:00:00", Qt::ISODate);
        if (!gps.time.isValid() || gps.time < minTime) {
            isValid = false;
            errorMsg = "Invalid time: " + gps.time.toString();
        }

        // 2. 检查纬度
        if (gps.latitude < -90.0 || gps.latitude > 90.0) {
            isValid = false;
            errorMsg = QString("Latitude out of range: %1").arg(gps.latitude);
        }

        // 3. 检查经度
        if (gps.longitude < -180.0 || gps.longitude > 180.0) {
            isValid = false;
            errorMsg = QString("Longitude out of range: %1").arg(gps.longitude);
        }

        // 4. 检查高度（可根据实际需求调整范围）
        if (gps.altitude < -1000.0 || gps.altitude > 10000.0) {
            isValid = false;
            errorMsg = QString("Altitude out of range: %1").arg(gps.altitude);
        }


        ui->label_pixmapGNSS->setPixmap(result2);
    }



}

void MainWindow::onFailurebind(QString eeror)
{
    QMessageBox::information(this  ,"提示" , eeror);
}

void MainWindow::onredtimeoutSignal()
{
    ui->label_pixmapjiqi->setPixmap(result);
    ui->label_pixmapjiqi_2->setPixmap(result);
}

void MainWindow::GNSSredtimeoutSignal()
{
    ui->label_pixmapGNSS->setPixmap(result);
}

void MainWindow::on_Btn_MachinestatusRead_clicked()
{

    if(isOpenTime)
    {
        disconnect(worker , &Worker::MachineStatusRead  ,m_machinestatus , &Machinestatus::onMachineStatusRead);
        m_machinestatus = new Machinestatus(this);
        m_machinestatus->setOwner(this);
        connect(worker , &Worker::MachineStatusRead  ,m_machinestatus , &Machinestatus::onMachineStatusRead);
        m_machinestatus->setFixedSize(325,523);

        m_machinestatus->show();
        isOpenTime = false;
    }
    else
    {
        QMessageBox::information(this , "提示" , "已打开,请勿重复打开");
    }

}

void MainWindow::onlineedit(int count)
{
    //  ui->lineEdit_dataCountsize->setText(QString::number(count));
}

void MainWindow::onMachineStatusRead(quint16 Power_input_voltage, quint16 Output_voltage_12V, quint16 Power_amplifier_28V_supply_voltage, quint16 Input_current_power_supply, quint16 Output_current_12V, quint16 Power_amplifier1, quint16 Power_amplifier2, quint16 Detection_voltage1, quint16 Detection_voltage2, quint8 Temperature, quint16 Version_number)
{
    double value;

    value =Power_input_voltage / 10.0;
    ui->lineEdit_Power_input_voltage->setText(QString::number(value, 'f', 2) + "V");

    value =Output_voltage_12V / 10.0;
    ui->lineEdit_Output_voltage_12V->setText(QString::number(value, 'f', 2)+ "V");

    value =Power_amplifier_28V_supply_voltage / 10.0;
    ui->lineEdit_Power_amplifier_28V_supply_voltage->setText(QString::number(value, 'f', 2)+ "V");

    value =Input_current_power_supply / 10.0;
    ui->lineEdit_Input_current_power_supply->setText(QString::number(value, 'f', 2) + "A");

    value =Output_current_12V / 10.0;
    ui->lineEdit_Output_current_12V->setText(QString::number(value, 'f', 2) + "A");

    value =Power_amplifier1 / 10.0;
    ui->lineEdit_Power_amplifier2->setText(QString::number(value, 'f', 2) + "A");

    value =Power_amplifier2 / 10.0;
    ui->lineEdit_Power_amplifier1->setText(QString::number(value, 'f', 2) + "A");

    value =Detection_voltage1 / 10.0;
    ui->lineEdit_Detection_voltage1->setText(QString::number(value, 'f', 2) + "V");

    value =Detection_voltage2 / 10.0;
    ui->lineEdit_Detection_voltage2->setText(QString::number(value, 'f', 2) + "V");

    value = Temperature;
    ui->lineEdit_Temperature->setText(QString::number(value) + "℃");




}

void MainWindow::onsignalOn(int value)
{

        ui->label_pixmapfashe1->setPixmap(result2);

}

void MainWindow::onsignalOff(int value)
{

        ui->label_pixmapfashe1->setPixmap(result);

}

void MainWindow::onsignalOn2(int value)
{
    ui->label_pixmapfashe2->setPixmap(result2);
}

void MainWindow::onsignalOff2(int value)
{
    ui->label_pixmapfashe2->setPixmap(result);
}


void MainWindow::on_Btn_cunchu_clicked()
{
    if(ui->Btn_cunchu->text() == "进行存储")
    {
        transmitterflag1 = 1;
        transmitterflag2 = 1;
        StartandQuitTransmitter(transmitterflag1,transmitterflag2);

        // 获取程序所在目录并创建 data 文件夹
        QString dataDir = ui->lineEdit_savepath->text() +"/" +  QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");
        QDir dir;
        if (!dir.exists(dataDir)) {
            dir.mkdir(dataDir);
        }


        emit setfilepath(dataDir);
        emit settxtfilepath(dataDir , ui->lineEdit_pingdian->text(),
                            ui->lineEdit_pinpian->text(),ui->lineEdit_tiaoz->text(),
                            ui->lineEdit_gonglv->text() ,ui->lineEdit_malv->text(),
                            ui->lineEdit_zhenchang1->text() , ui->lineEdit_zhengmazu->text(),
                            ui->lineEdit_fuzhengfs1->text() , ui->lineEdit_fuzhengchang->text(),
                            ui->lineEdit_maxing->text() , ui->lineEdit_bianmawz->text(),
                            ui->lineEdit_pingdian_2->text(),
                            ui->lineEdit_pinpian_2->text(),ui->lineEdit_tiaoz_2->text(),
                            ui->lineEdit_gonglv_2->text() ,ui->lineEdit_malv_2->text(),
                            ui->lineEdit_zhenchang2->text() , ui->lineEdit_zhengmazu_2->text(),
                            ui->lineEdit_fuzhengfs1_2->text() , ui->lineEdit_fuzhengchang_2->text(),
                            ui->lineEdit_maxing_2->text() , ui->lineEdit_bianmawz_2->text());
        emit startdatafile1();
        emit startdatafile2();


        ui->Btn_cunchu->setText("停止存储");
    }
    else if(ui->Btn_cunchu->text() == "停止存储")
    {
        transmitterflag1 = 0;
        transmitterflag2 = 0;
        StartandQuitTransmitter(transmitterflag1,transmitterflag2);


        emit quitdatafile1();
        emit quitdatafile2();

        ui->Btn_cunchu->setText("进行存储");
    }



}

void MainWindow::on_Btn_filedialog_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this,
        tr("选择目录"),
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );


    ui->lineEdit_savepath->setText(dirPath);



}

void MainWindow::on_Btn_gonglvset_clicked()
{
    if(ui->lineEdit_miangonglv->text().toInt() > 10 &&  ui->Box_zaibo->currentText() == "载波:开")
    {
        QMessageBox::information(this , "提示" , "输出功率较大，请确认天线已连接");
    }


    QSettings settings("settings.ini", QSettings::IniFormat);


    // 调制组
    settings.beginGroup("Modulation");
    QString maxing = settings.value("maxing", "NRZ-L").toString();
    QString fuzhenfanshi = settings.value("fuzhenfanshi", "无副帧").toString();
    QString fuzhenchangdu = settings.value("fuzhenchangdu", "16").toString();
    QString tzfzweizhi = settings.value("tzfzweizhi", "10").toString();
    QString tiao1 = settings.value("tiao1", "50").toString();
    QString zai1 = settings.value("zai1", "40").toString();
    QString tiaokai1 = settings.value("tiaokai1", "1").toString();
    QString tiaoji1 = settings.value("tiaoji1", "2").toString();
    settings.endGroup();


    // 跳频组
    settings.beginGroup("FrequencyHopping");
    QString tzbinpian = settings.value("tzbinpian", "3500").toString();
    settings.endGroup();

    // 功率控制组
    settings.beginGroup("PowerControl");
    QString fsygonglvkongz = settings.value("fsygonglvkongz", "0").toString();
    settings.endGroup();


    settings.beginGroup("BasicParameters");
    QString zichang = settings.value("zichang", "8").toString(); // 默认值示例
    QString xinhaoneixing = settings.value("xinhaoneixing", "随机码").toString();
    QString zhenchang = settings.value("zhenchang", "128").toString();
    QString fspinlv = settings.value("fspinlv", "2400").toString();
    settings.endGroup();

    QByteArray array;

    m_PPACKET_HEADER = new PACKET_HEADER;
    //owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;

    m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    m_PPACKET_HEADER->functionCode = 0x03;
    m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

    m_PTRANSMIT_CONFIG->txSelector = 0x01;
    double texttodub = fspinlv.toDouble();
    m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));

    qDebug() << m_PTRANSMIT_CONFIG->freq1;

    //texttoint = ui->lineEdit_tzbinpian->text().toInt();
    int  texttoint = (fo == 0) ? 0 :
                                        static_cast<quint32>(
                                            tzbinpian.toDouble() * 1000.0 * 4294967296.0 / fo
                                        );
    m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
    m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
    quint8 tiaozhifangshiint;
    quint8 modPolarity1int;
    quint8 modSwitch1int;
    quint8 carrier1int;
    if(tiao1 == "FM调制")
    {
        tiaozhifangshiint =0b0000;
    }
    else if(tiao1 == "BPSK调制")
    {
        tiaozhifangshiint =0b0001;
    }
    else if(tiao1 == "QPSK调制")
    {
        tiaozhifangshiint =0b0010;
    }

    if(ui->Box_zaibo->currentText() == "载波:开")
    {
        carrier1int = 1;
    }
    else if(ui->Box_zaibo->currentText() == "载波:关")
    {
        carrier1int = 0;
    }

    if(tiaokai1 == "开")
    {
        modSwitch1int = 1;
    }
    else if(tiaokai1 == "关")
    {
        modSwitch1int = 0;
    }

    if(tiaoji1 == "正")
    {
        modPolarity1int = 0;
    }
    else if(tiaoji1 == "负")
    {
        modPolarity1int = 1;
    }
    m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
    m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
    m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
    m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
    m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;

    double y = ui->lineEdit_miangonglv->text().toDouble();
    int x = ui->lineEdit_miangonglv->text().toInt();
    if(x < 6)
    {
       x = 6;
    }

    double result;

        QString appDir = QCoreApplication::applicationDirPath();
        qDebug() << "Application file path:" << appDir;
        if (dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
            dataquery.printDataRange();

            result = dataquery.interpolate(y*1000, x);
            qDebug() << "插值结果:" << result;}




    m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
    m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_miangonglv->text().toInt()));

    for(int i= 0 ; i < 50 ; i++)
    {
        m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
    }

    m_PPACKET_HEADER->dataLength = sizeof(TRANSMIT_CONFIG) + 12;


    array.append(reinterpret_cast<const char*>(m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(m_PTRANSMIT_CONFIG),
                                               sizeof(TRANSMIT_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

    quint32 m_crc32 = crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


    int i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    udpManager->sendDatagram(array);

    Logger::info("发射机1:配置射频参数下发");
    setmaintable("发射机1:配置射频参数下发", "上位机");
    array.clear();

    // 功率控制组
    settings.beginGroup("PowerControl");
    settings.setValue("fsygonglvkongz", ui->lineEdit_miangonglv->text());
    settings.endGroup();

    gonglv = ui->lineEdit_miangonglv->text();

    ui->lineEdit_gonglv->setText(ui->lineEdit_miangonglv->text());

}

void MainWindow::on_Btn_gonglvset_2_clicked()
{
    if(ui->lineEdit_miangonglv_2->text().toInt() > 10 &&  ui->Box_zaibo2->currentText() == "载波:开")
    {
        QMessageBox::information(this , "提示" , "输出功率较大，请确认天线已连接");
    }

    QSettings settings("settings.ini", QSettings::IniFormat);
    // 调制组
    settings.beginGroup("Modulation2");
    QString maxing = settings.value("maxing2", "NRZ-L").toString();
    QString fuzhenfanshi = settings.value("fuzhenfanshi2", "无副帧").toString();
    QString fuzhenchangdu = settings.value("fuzhenchangdu2", "16").toString();
    QString tzfzweizhi = settings.value("tzfzweizhi2", "10").toString();
    QString tiao1 = settings.value("tiao12", "50").toString();
    QString zai1 = settings.value("zai12", "40").toString();
    QString tiaokai1 = settings.value("tiaokai12", "1").toString();
    QString tiaoji1 = settings.value("tiaoji12", "2").toString();
    settings.endGroup();


    // 跳频组
    settings.beginGroup("FrequencyHopping2");
    QString tzbinpian = settings.value("tzbinpian2", "3500").toString();
    settings.endGroup();

    // 功率控制组
    settings.beginGroup("PowerControl2");
    QString fsygonglvkongz = settings.value("fsygonglvkongz2", "0").toString();
    settings.endGroup();


    settings.beginGroup("BasicParameters2");
    QString zichang = settings.value("zichang2", "8").toString(); // 默认值示例
    QString xinhaoneixing = settings.value("xinhaoneixing2", "随机码").toString();
    QString zhenchang = settings.value("zhenchang2", "128").toString();
    QString fspinlv = settings.value("fspinlv2", "2400").toString();
    settings.endGroup();




    QByteArray array;

    m_PPACKET_HEADER = new PACKET_HEADER;
    //owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;

    m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    m_PPACKET_HEADER->functionCode = 0x03;
    m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

    m_PTRANSMIT_CONFIG->txSelector = 0x02;
    double texttodub = fspinlv.toDouble();
    m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));

    qDebug() << m_PTRANSMIT_CONFIG->freq1;

    //texttoint = ui->lineEdit_tzbinpian->text().toInt();
    int  texttoint = (fo == 0) ? 0 :
                                        static_cast<quint32>(
                                            tzbinpian.toDouble() * 1000.0 * 4294967296.0 / fo
                                        );
    m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
    m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
    quint8 tiaozhifangshiint;
    quint8 modPolarity1int;
    quint8 modSwitch1int;
    quint8 carrier1int;
    if(tiao1 == "FM调制")
    {
        tiaozhifangshiint =0b0000;
    }
    else if(tiao1 == "BPSK调制")
    {
        tiaozhifangshiint =0b0001;
    }
    else if(tiao1 == "QPSK调制")
    {
        tiaozhifangshiint =0b0010;
    }

    if(ui->Box_zaibo2->currentText() == "载波:开")
    {
        carrier1int = 1;
    }
    else if(ui->Box_zaibo2->currentText() == "载波:关")
    {
        carrier1int = 0;
    }

    if(tiaokai1 == "开")
    {
        modSwitch1int = 1;
    }
    else if(tiaokai1 == "关")
    {
        modSwitch1int = 0;
    }

    if(tiaoji1 == "正")
    {
        modPolarity1int = 0;
    }
    else if(tiaoji1 == "负")
    {
        modPolarity1int = 1;
    }
    m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
    m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
    m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
    m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
    m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;

    double y = ui->lineEdit_miangonglv->text().toDouble();
    int x = ui->lineEdit_miangonglv->text().toInt();
    if(x < 6)
    {
       x = 6;
    }

    double result;

        QString appDir = QCoreApplication::applicationDirPath();
        qDebug() << "Application file path:" << appDir;
        if (dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
            dataquery.printDataRange();

            result = dataquery.interpolate(y*1000, x);
            qDebug() << "插值结果:" << result;}




    m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
    m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_miangonglv->text().toInt()));

    for(int i= 0 ; i < 50 ; i++)
    {
        m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
    }

    m_PPACKET_HEADER->dataLength = sizeof(TRANSMIT_CONFIG) + 12;


    array.append(reinterpret_cast<const char*>(m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(m_PTRANSMIT_CONFIG),
                                               sizeof(TRANSMIT_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

    quint32 m_crc32 = crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


    int i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    udpManager->sendDatagram(array);

    Logger::info("发射机1:配置射频参数下发");
    setmaintable("发射机1:配置射频参数下发", "上位机");
    array.clear();

    // 功率控制组
    settings.beginGroup("PowerControl2");
    settings.setValue("fsygonglvkongz2", ui->lineEdit_miangonglv_2->text());
    settings.endGroup();


    gonglv2 = ui->lineEdit_miangonglv_2->text();

    ui->lineEdit_gonglv_2->setText(ui->lineEdit_miangonglv_2->text());

}
