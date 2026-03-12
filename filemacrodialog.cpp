#include "filemacrodialog.h"
#include "ui_filemacrodialog.h"
#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "CustomDialog.h"



fileMacroDialog::fileMacroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileMacroDialog)
{
    ui->setupUi(this);


    QStringList horizontalHeaders2;
    ui->tableWidget_renwu->setColumnCount(3);
    horizontalHeaders2 << "序号" << "名称" << "保存时间";
    ui->tableWidget_renwu->setHorizontalHeaderLabels(horizontalHeaders2);
    ui->tableWidget_renwu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_renwu->verticalHeader()->setDefaultSectionSize(60);

    ui->tableWidget_renwu->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
   // ui->tableWidget_renwu->model()->setHeaderData(1, Qt::Horizontal, QVariant(false), Qt::EditRole);

    // 使用方式：
    MultiColumnNonEditableDelegate *delegate = new MultiColumnNonEditableDelegate({0, 2}, this); // 设置第1列不可编辑
    ui->tableWidget_renwu->setItemDelegate(delegate);



    // 设置autoExclusive为false，这样它们就不会互斥
        ui->Btn_fayi1->setAutoExclusive(false);
        //ui->Btn_fayi1->setAutoExclusive(false);

        setWindowTitle("任务宏");

        ui->Btn_save->setStyleSheet(
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

        ui->Btn_delete->setStyleSheet(
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


        ui->Btn_newsave->setStyleSheet(
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

        ui->Btn_take->setStyleSheet(
                    "QPushButton {"
                    "   background-color: #285C2E;"  // 主背景色（深绿）
                    "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                    "   border-radius: 5px;"          // 圆角
                    "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                    "   padding: 4px 8px;"           // 内边距
                    "}"
                    "QPushButton:hover {"
                    "   background-color: #459E4F;"   // 悬停时亮青
                    "}"
                    "QPushButton:pressed {"
                    "   background-color: #1D4221;"   // 按下时暗青"
                    "}"
                );



        ui->Btn_fayi1->setChecked(true);
        ui->Btn_fayi2->setChecked(true);
        ui->checkBox_geshi->setChecked(true);
        ui->checkBox_geshi_2->setChecked(true);
        ui->checkBox_sheping->setChecked(true);
        ui->checkBox_sheping_2->setChecked(true);
        ui->checkBox_xindao->setChecked(true);
        ui->checkBox_xindao_2->setChecked(true);
        ui->checkBox_pcm->setChecked(true);
        ui->checkBox_pcm_2->setChecked(true);
        ui->checkBox_yibu->setChecked(true);
        ui->checkBox_yibu_2->setChecked(true);
        ui->checkBox_ankong->setChecked(true);


        updatetable();


    ui->Btn_fayi1->hide();
    ui->Btn_fayi2->hide();
    ui->checkBox_geshi->hide();
    ui->checkBox_geshi_2->hide();
    ui->checkBox_sheping->hide();
    ui->checkBox_sheping_2->hide();
    ui->checkBox_xindao->hide();
    ui->checkBox_xindao_2->hide();
    ui->checkBox_pcm->hide();
    ui->checkBox_pcm_2->hide();
    ui->checkBox_yibu->hide();
    ui->checkBox_yibu_2->hide();
    ui->checkBox_ankong->hide();

}



fileMacroDialog::~fileMacroDialog()
{
    delete ui;
}

void fileMacroDialog::setOwner(MainWindow *mainwindow)
{
    owner = mainwindow;
}

void fileMacroDialog::closeEvent(QCloseEvent *event)
{
    for(int i = 0 ; i < tablecol ; i++)
    {
        saveSettings(i);
    }
}

void fileMacroDialog::saveSettings(int i)
{
    QString filename = QString("dabaosetting%1.ini").arg(i);
    QSettings settings(filename, QSettings::IniFormat);

    settings.beginGroup("Bianhao");
    settings.setValue("id", i);  // 固定值
    settings.setValue("daihao", ui->tableWidget_renwu->item(i,1)->text());
    //qDebug()  << ui->tableWidget_renwu->item(i,1)->text(); // 固定值
    settings.setValue("time", ui->tableWidget_renwu->item(i,2)->text());
    settings.endGroup();


}

void fileMacroDialog::loadSettings(int i)
{
    QString filename = QString("dabaosetting%1.ini").arg(i);
    QSettings settings(filename, QSettings::IniFormat);

    settings.beginGroup("Bianhao");

    id = settings.value("id", "方式A").toInt();
    daihao= settings.value("daihao", "未命名").toString();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    savetime = settings.value("time", "未保存").toString();
    settings.endGroup();




    onupdatetablewidget(i);
   // updatewidget(i);


}

void fileMacroDialog::onupdatetablewidget(int i)
{
    QTableWidgetItem* item = new QTableWidgetItem;
    item->setText(QString("%1").arg(i + 1));
    ui->tableWidget_renwu->setItem(i , 0 , item);
    QTableWidgetItem* item2 = new QTableWidgetItem;
    item2->setText(daihao);
    ui->tableWidget_renwu->setItem(i , 1 , item2);

    QTableWidgetItem* item3 = new QTableWidgetItem;
    item3->setText(savetime);
    ui->tableWidget_renwu->setItem(i , 2 , item3);
}

quint16 fileMacroDialog::updateankong(QString ankong)
{
    QString input = ankong;
    // 将字符映射为数值（0-15）
    QVector<int> positions;
    for (QChar c : input) {
        int value;
        if (c >= '0' && c <= '9') {
            value = c.unicode() - '0';
        } else if (c >= 'A' && c <= 'F') {
            value = 10 + (c.unicode() - 'A');
        } else if (c >= 'a' && c <= 'f') {
            value = 10 + (c.unicode() - 'a');
        } else {
            qDebug() << "Invalid character:" << c;
            return value;
        }
        positions.append(value);
    }

    // 初始化16位二进制状态（全0）
    unsigned short binary = 0;

    // 设置二进制中对应的位为1
    for (int pos : positions) {
        if (pos >= 0 && pos <= 15) {
            binary |= (1 << pos); // 设置对应位为1
        }
    }

    // 转换为16进制字符串
    QString hex = QString("%1").arg(binary, 4, 16, QLatin1Char('0')).toUpper();
    qDebug() << "Result:" << hex;

    // 转换为 quint16
    bool ok;
    quint16 value = hex.toUShort(&ok, 16);  // 去掉 "0x" 前缀后转换
    return value;
}

void fileMacroDialog::doWorkWithDelay(int ms)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    qDebug() << time;

    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec(); // 阻塞直到定时器触发


    time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    qDebug() << time;

}

void fileMacroDialog::updatetable()
{
    QString taskConfigPath = QCoreApplication::applicationDirPath() + "/TaskMacro";
    QDir taskDir(taskConfigPath);

    // 检查文件夹是否存在
    if (!taskDir.exists())
    {
        QMessageBox::information(this , "错误" , "TaskMacro文件夹不存在");
        return ;
    }

    // 设置过滤器，只显示文件（不包含文件夹）并且以.ini结尾
    taskDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    taskDir.setNameFilters(QStringList() << "*.ini");

    // 获取文件列表
    QStringList fileList = taskDir.entryList();
    tablecol = fileList.size();

    qDebug() << "找到" << tablecol << "个INI文件";

    ui->tableWidget_renwu->setRowCount(tablecol);

    for (int i = 0; i < tablecol; ++i)
    {
            QString entry = fileList[i];
            QStringList parts = entry.split("_");

            for(int j = 0; j < parts.size(); j++) {
                daihao = parts[0];
                savetime = parts[1];
            }

            onupdatetablewidget(i);
    }
}

void fileMacroDialog::copySettings(const QSettings &source, QSettings &target)
{
    // 获取源设置的所有键
     QStringList allKeys = source.allKeys();

     // 遍历并复制每个键值对
     for (const QString& key : allKeys) {
         QVariant value = source.value(key);
         target.setValue(key, value);
     }

     // 立即同步到存储介质
     target.sync();
}


void fileMacroDialog::on_Btn_PeiAll_clicked()
{


      owner->m_PPACKET_HEADER = new PACKET_HEADER;


      owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
      owner->m_PPACKET_HEADER->functionCode = 0x05;
      owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
      owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
      owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);





      QByteArray array;
      array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                    sizeof(PACKET_HEADER));
      if(ui->Btn_fayi1->isChecked())
      {
          m_daimoall[danqianint]->txSelector = 0x01;
      }
      else
      {
          m_daimoall[danqianint]->txSelector = 0x02;
      }
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->txSelector),
                                                    sizeof(quint8));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->pcmRate),
                                                    sizeof(quint32));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->subFrameLength.rawValue),
                                                    sizeof(quint16));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->subFrameCount),
                                                    sizeof(quint8));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->WordConfig.raw),
                                                    sizeof(quint8));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->featurePosition),
                                                    sizeof(quint16));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->loopSyncCode),
                                                    sizeof(quint16));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->syncCode),
                                                    sizeof(quint64));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->frameType.bit),
                                                    sizeof(quint8));

      for(int i = 0 ; i < 5 ; i++)
      {
          m_daimoall[danqianint]->reserved1[i] = 0;
          array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->reserved1[i]),
                                                        sizeof(quint8));

      }


      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->dataType),
                                                    sizeof(quint8));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->stepValue),
                                                    sizeof(quint16));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->initStep),
                                                    sizeof(quint16));

      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->FrameCalcChannel.value),
                                                    sizeof(quint16));

      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->frameCalcChannelhigh.value),
                                                    sizeof(quint16));

      for(int i = 0 ; i < 4 ; i++)
      {
          m_daimoall[danqianint]->reserved2[i] = 0;
          array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->reserved2[i]),
                                                        sizeof(quint8));

      }

      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->idtreatrue.raw),
                                                    sizeof(quint8));

      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->codingPosition),
                                                    sizeof(quint8));

      for(int i = 0 ; i < 22 ; i++)
      {
          m_daimoall[danqianint]->reserved3[i] = 0;
          array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->reserved3[i]),
                                                        sizeof(quint8));

      }

      quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
      m_crc32 = qToLittleEndian<quint32>(m_crc32);
      array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


      int i  = 1 ;
      for (quint8 byte : array) {
                    QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                    qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                }



      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->freq),
                                                    sizeof(quint32));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->detF),
                                                    sizeof(quint32));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->alltiaoz.ctrl),
                                                    sizeof(quint8));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->powerCtrl),
                                                    sizeof(quint8));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->codeSwitch.codeSwitchValue),
                                                    sizeof(quint8));
      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->tpcSyncCode),
                                                    sizeof(quint32));

      array.append(reinterpret_cast<const char*>(&m_daimoall[danqianint]->tpcValidFlag),
                                                    sizeof(quint16));





}




void fileMacroDialog::on_Btn_zhancun_clicked()
{
    int i = danqianint;


    quint8  dpskFmPreamble[3];    // 前导码 [3B] 默认{0xFF,0xFF,0xFF}





    saveSettings(i);
}

void fileMacroDialog::on_Btn_save_clicked()
{

     QList<QTableWidgetItem*> selectedItems = ui->tableWidget_renwu->selectedItems();
     QString taskConfigPath;
     QString filePath;
     QString filename;

     if (!selectedItems.isEmpty()) {
         // 获取第一个选中的项（如果允许多选，请注意处理多个）
         QTableWidgetItem* selectedItem = selectedItems.first();

         taskConfigPath = QCoreApplication::applicationDirPath() + "/TaskMacro";
         QDir taskDir(taskConfigPath);


         filename = QString("%1_%2").arg(selectedItems[1]->text()).arg(selectedItems[2]->text());

         // 构建文件路径
         filePath = taskDir.absoluteFilePath(filename);

         int row = selectedItem->row();
         int column = selectedItem->column();
         danqianint = row;
      }


     if(ui->tableWidget_renwu->item(danqianint , 2)->text() != "未保存")
     {
         // 在某个函数中
         int ret = QMessageBox::question(this, tr("确认"), tr("已有保存,是否覆盖"),
                                        QMessageBox::Yes | QMessageBox::No);

         if(ret == QMessageBox::No)
             return;
     }



     QFile file(filePath);
     QString currenttime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
     filename = QString("%1_%2.ini").arg(selectedItems[1]->text()).arg(currenttime);
     // 重命名文件
         if (file.rename(taskConfigPath + "/"+filename)) {
             qDebug() << "文件重命名成功:";
         } else {
             qDebug() << "文件重命名失败:" << file.errorString();
         }
     file.close();


     QSettings settings1("settings.ini", QSettings::IniFormat);
     QSettings settings2(QString(taskConfigPath + "/"+filename), QSettings::IniFormat);

     copySettings(settings1 , settings2);


     updatetable();
}

void fileMacroDialog::on_Btn_take_clicked()
{
    // 在某个函数中
    int fashong = QMessageBox::question(this, tr("确认"), tr("是否载入参数？"),
                                   QMessageBox::Yes | QMessageBox::No);
    if(fashong == QMessageBox::No)
        return;

    QSettings settings2("settings.ini", QSettings::IniFormat);

    QList<QTableWidgetItem*> selectedItems = ui->tableWidget_renwu->selectedItems();

    // 获取两个文本框的值
    QString mingzi;
    QString time;
    QString taskConfigPath;
    QString filename;

    if (!selectedItems.isEmpty()) {
        // 获取第一个选中的项（如果允许多选，请注意处理多个）
        QTableWidgetItem* selectedItem = selectedItems.first();

        // 获取行号和列号
        int row = selectedItem->row();
        int column = selectedItem->column();

        danqianint = row;

        mingzi = selectedItems[1]->text();
        time = selectedItems[2]->text();
     }

    taskConfigPath = QCoreApplication::applicationDirPath() + "/TaskMacro";
    QDir taskDir(taskConfigPath);


    filename = QString("%1_%2").arg(selectedItems[1]->text()).arg(selectedItems[2]->text());

    QSettings settings4(taskConfigPath + "/" + filename , QSettings::IniFormat);



    // 获取源文件的所有键值对
    QStringList keys = settings4.allKeys();

    // 遍历并复制所有设置
    for (const QString &key : keys) {
        QVariant value = settings4.value(key);
        settings2.setValue(key, value);
    }

    // 确保所有更改立即写入磁盘
    settings2.sync();


    // 在某个函数中
    int ret = QMessageBox::question(this, tr("确认"), tr("装载成功 ,是否立即下发？"),
                                   QMessageBox::Yes | QMessageBox::No);

    if(ret == QMessageBox::Yes)
    {





    owner->m_PPACKET_HEADER = new PACKET_HEADER;
    owner->m_PTELEMETRY_FRAME = new TELEMETRY_FRAME;
    owner->m_PREAD_FRAMEFORMAT = new READ_FRAMEFORMAT;
    //owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;
    owner->m_PTELEMETRY_ENCODING_CONFIG = new TELEMETRY_ENCODING_CONFIG;
    owner->m_PPCMEMBEDCONfIG = new PCMEMBEDCONfIG;
    owner->m_PAsyncSourceConfig = new AsyncSourceConfig;
    owner->m_PSecuritySourceConfig = new SecuritySourceConfig;

    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);


    owner->m_PPACKET_HEADER->functionCode = 0x01;

    QByteArray array;


   // QSettings settings3(QString("dabaosetting%1.ini").arg(danqianint), QSettings::IniFormat);
        // 基本参数组
        settings2.beginGroup("BasicParameters");
        zichang = settings2.value("zichang", "1000").toString(); // 默认值示例
        xinhaoneixing = settings2.value("xinhaoneixing", "QPSK").toString();
        zhenchang = settings2.value("zhenchang", "256").toString();
        fspinlv = settings2.value("fspinlv", "2400").toString();
        settings2.endGroup();

        // 同步与编码组
        settings2.beginGroup("SyncCoding");
        xhfztongbuma = settings2.value("xhfztongbuma", "1010").toString();
        Bianma = settings2.value("Bianma", "NRZ").toString();
        Bianmaweizhi = settings2.value("Bianmaweizhi", "5").toString();
        Malv = settings2.value("Malv", "9600").toString();
        TPCtongbuma = settings2.value("TPCtongbuma", "11110000").toString();
        youxiaobiaozi = settings2.value("youxiaobiaozi", "1").toString();
        settings2.endGroup();

        // 调制组
        settings2.beginGroup("Modulation");
        maxing = settings2.value("maxing", "RZ").toString();
        fuzhenfanshi = settings2.value("fuzhenfanshi", "2FSK").toString();
        fuzhenchangdu = settings2.value("fuzhenchangdu", "128").toString();
        tzfzweizhi = settings2.value("tzfzweizhi", "10").toString();
        tiao1 = settings2.value("tiao1", "50").toString();
        zai1 = settings2.value("zai1", "40").toString();
        tiaokai1 = settings2.value("tiaokai1", "1").toString();
        tiaoji1 = settings2.value("tiaoji1", "2").toString();
        settings2.endGroup();

        // ID管理组
        settings2.beginGroup("Identification");
        IDmafztz = settings2.value("IDmafztz", "AAFF").toString();
        IDzijizhi = settings2.value("IDzijizhi", "127").toString();
        IDzijishufangshi = settings2.value("IDzijishufangshi", "0").toString();
        Fuzhentezheng = settings2.value("Fuzhentezheng", "00").toString();
        ismofei = settings2.value("ismofei", "00").toInt();
        settings2.endGroup();

        // 跳频组
        settings2.beginGroup("FrequencyHopping");
        tzbinpian = settings2.value("tzbinpian", "20").toString();
        settings2.endGroup();

        // 功率控制组
        settings2.beginGroup("PowerControl");
        fsygonglvkongz = settings2.value("fsygonglvkongz", "80").toString();
        settings2.endGroup();

        // 通道编码组
        settings2.beginGroup("ChannelCoding");
        bianmakai = settings2.value("bianmakai").toString();
        LDPC = settings2.value("LDPC", "1").toString();
        TPC = settings2.value("TPC", "0").toString();
        RS = settings2.value("RS", "1").toString();
        juanji = settings2.value("juanji", "3").toString();
        settings2.endGroup();



        // 步进控制组
        settings2.beginGroup("StepControl");
        tjmbujin = settings2.value("tjmbujin", "1").toString();
        tjmchushizi = settings2.value("tjmchushizi", "0").toString();
        settings2.endGroup();

        // 中继组
        settings2.beginGroup("Relay");
        zjsdzjbodao = settings2.value("zjsdzjbodao", "1").toString();
        bujielow    = settings2.value("bujielow", "1").toInt();
        zjsgzjbodao = settings2.value("zjsgzjbodao", "2").toString();
        bujiehigh   = settings2.value("bujiehigh", "1").toInt();
        settings2.endGroup();

        // 序列组
        settings2.beginGroup("Sequences");
        fuzhenlvxu = settings2.value("fuzhenlvxu", "0").toString();
        zhenmazhu = settings2.value("zhenmazhu", "0").toString();
        settings2.endGroup();




        // 基本参数组2
        settings2.beginGroup("BasicParameters2");
        zichang_2 = settings2.value("zichang2", "1000").toString();
        xinhaoneixing_2 = settings2.value("xinhaoneixing2", "QPSK").toString();
        zhenchang_2 = settings2.value("zhenchang2", "256").toString();
        fspinlv_2 = settings2.value("fspinlv2", "2400").toString();
        settings2.endGroup();

        // 同步与编码组2
        settings2.beginGroup("SyncCoding2");
        xhfztongbuma_2 = settings2.value("xhfztongbuma2", "1010").toString();
        Bianma_2 = settings2.value("Bianma2", "NRZ").toString();
        Bianmaweizhi_2 = settings2.value("Bianmaweizhi2", "5").toString();
        Malv_2 = settings2.value("Malv2", "9600").toString();
        TPCtongbuma_2 = settings2.value("TPCtongbuma2", "11110000").toString();
        youxiaobiaozi_2 = settings2.value("youxiaobiaozi2", "1").toString();
        settings2.endGroup();

        // 调制组2
        settings2.beginGroup("Modulation2");
        maxing_2 = settings2.value("maxing2", "RZ").toString();
        fuzhenfanshi_2 = settings2.value("fuzhenfanshi2", "2FSK").toString();
        fuzhenchangdu_2 = settings2.value("fuzhenchangdu2", "128").toString();
        tzfzweizhi_2 = settings2.value("tzfzweizhi2", "10").toString();
        tiao1_2 = settings2.value("tiao12", "50").toString();
        zai1_2 = settings2.value("zai12", "40").toString();
        tiaokai1_2 = settings2.value("tiaokai12", "1").toString();
        tiaoji1_2 = settings2.value("tiaoji12", "2").toString();
        settings2.endGroup();

        // ID管理组2
        settings2.beginGroup("Identification2");
        IDmafztz_2 = settings2.value("IDmafztz2", "AAFF").toString();
        IDzijizhi_2 = settings2.value("IDzijizhi2", "127").toString();
        IDzijishufangshi_2 = settings2.value("IDzijishufangshi2", "0").toString();
        Fuzhentezheng_2 = settings2.value("Fuzhentezheng2", "00").toString();
        ismofei_2 = settings2.value("ismofei_2", "00").toInt();
        settings2.endGroup();

        // 跳频组2
        settings2.beginGroup("FrequencyHopping2");
        tzbinpian_2 = settings2.value("tzbinpian2", "20").toString();
        settings2.endGroup();

        // 功率控制组2
        settings2.beginGroup("PowerControl2");
        fsygonglvkongz_2 = settings2.value("fsygonglvkongz2", "80").toString();
        settings2.endGroup();

        // 通道编码组2
        settings2.beginGroup("ChannelCoding2");
        bianmakai_2 = settings2.value("bianmakai2").toString();
        LDPC_2 = settings2.value("LDPC2", "1").toString();
        TPC_2 = settings2.value("TPC2", "0").toString();
        RS_2 = settings2.value("RS2", "1").toString();
        juanji_2 = settings2.value("juanji2", "3").toString();
        settings2.endGroup();

        // 步进控制组2
        settings2.beginGroup("StepControl2");
        tjmbujin_2 = settings2.value("tjmbujin2", "1").toString();
        tjmchushizi_2 = settings2.value("tjmchushizi2", "0").toString();
        settings2.endGroup();

        // 中继组2
        settings2.beginGroup("Relay2");
        zjsdzjbodao_2 = settings2.value("zjsdzjbodao2", "1").toString();
        bujielow_2    = settings2.value("bujielow_2", "1").toInt();
        zjsgzjbodao_2 = settings2.value("zjsgzjbodao2", "2").toString();
        bujiehigh_2   = settings2.value("bujiehigh_2", "1").toInt();
        settings2.endGroup();

        // 序列组2
        settings2.beginGroup("Sequences2");
        fuzhenlvxu_2 = settings2.value("fuzhenlvxu2", "0").toString();
        zhenmazhu_2 = settings2.value("zhenmazhu2", "0").toString();
        settings2.endGroup();



              owner->fuzhengfangshi = fuzhenfanshi;
              owner->zhengmazu = zhenmazhu;
              owner->malv = Malv;
              owner->maxing = maxing;
              owner->bianmawz = Bianmaweizhi;
              owner->fuzhengchang = fuzhenchangdu;
              owner->zhenchang = zhenchang;
         //     owner->tiaozhikaiguan = zai1;
              owner->gonglv = fsygonglvkongz;

              owner->pingdian = fspinlv;
              owner->pinpian = tzbinpian;
              owner->tiaoz = tiao1;

              owner->zaibokaiguan = tiaokai1;
              owner->updateui1();

              owner->fuzhengfangshi2 = fuzhenfanshi_2;
              owner->zhengmazu2 = zhenmazhu_2;
              owner->malv2 = Malv_2;
              owner->maxing2 = maxing_2;
              owner->bianmawz2 = Bianmaweizhi_2;
              owner->fuzhengchang2 = fuzhenchangdu_2;
              owner->zhenchang2 = zhenchang_2;
              owner->zaibokaiguan2 = zai1;
              owner->gonglv2 = fsygonglvkongz_2;

              owner->pingdian2 = fspinlv_2;
              owner->pinpian2 = tzbinpian_2;
              owner->tiaoz2 = tiao1_2;

              owner->zaibokaiguan2 = tiaokai1_2;
              owner->updateui2();




        quint32 byteValue32;
        quint16 byteValue16;
        quint8 byteValue8;
        quint64 byteValue64;
        quint32 m_crc32;


    if(ui->Btn_fayi1->isChecked())
    {
        if(ui->checkBox_geshi->isChecked())
        {

            byteValue32 = static_cast<quint32>(Malv.toDouble() * 1000 * 4294967296 / owner->fo); // 0x01
            owner->m_PTELEMETRY_FRAME->txSelector = 0x01;
            owner->m_PTELEMETRY_FRAME->pcmRate = qToLittleEndian<quint32>(byteValue32);


            byteValue16 = static_cast<quint16>(zhenchang.toInt()  - 1);

            owner->m_PTELEMETRY_FRAME->subFrameLength.bit.length = qToLittleEndian<quint16>(byteValue16);

            owner->m_PTELEMETRY_FRAME->subFrameLength.bit.moFeiFlag = ismofei;


            if(fuzhenfanshi == "无副帧")
            {
                byteValue8 = 0x00;
            }
            else
            {
                byteValue8 = static_cast<quint8>(fuzhenchangdu.toInt() - 1);

            }

            owner->m_PTELEMETRY_FRAME->subFrameCount = qToLittleEndian<quint8>(byteValue8);

            owner->m_PTELEMETRY_FRAME->WordConfig.bits.wordLengthMinusOne = static_cast<quint8>(zichang.toInt() - 1);
            quint8 codeType;

            if (maxing == "NRZ-L")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000000;
            }

            else if (maxing == "NRZ-M")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000010;
            }

            else if (maxing == "NRZ-S")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000011;
            }
            else if (maxing == "BIφ-L")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000100;
            }

            else if (maxing == "BIφ-M")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000110;
            }


            else if (maxing == "BIφ-S")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000111;
            }


            else if (maxing == "RNRZ-L")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00001000;
            }




            byteValue16 = fuzhenlvxu.toInt() - 1 ; //ID码副帧时, 副帧的ID码所在路序-1。循环码副帧时，副帧特征字在子帧的路序-1
            owner->m_PTELEMETRY_FRAME->featurePosition = qToLittleEndian<quint16>(byteValue16);

            bool convertOk;
            QString processed = zhenmazhu.trimmed().toUpper();
            byteValue64 = processed.toULongLong(&convertOk , 16);
            owner->m_PTELEMETRY_FRAME->syncCode = qToLittleEndian<quint64>(byteValue64);

            processed = xhfztongbuma.trimmed().toUpper();
            byteValue16 = processed.toULongLong(&convertOk , 16);
            owner->m_PTELEMETRY_FRAME->loopSyncCode = qToLittleEndian<quint16>(byteValue16);


             quint8 subframeType ;
             quint8 bitLengthMinusOne;
            if(fuzhenfanshi == "无副帧")
            {
                subframeType = 0 ;
            }

            else if(fuzhenfanshi == "反码副帧")

            {
                subframeType = 2 ;
            }

            else if(fuzhenfanshi == "循环副帧")
            {
                subframeType = 1 ;
            }

            else if(fuzhenfanshi == "ID副帧")
            {
                subframeType = 3 ;
            }

            bitLengthMinusOne = zhenmazhu.size() * 4 - 1;


            byteValue8 = (subframeType << 6) | bitLengthMinusOne ;

            owner->m_PTELEMETRY_FRAME->frameType = byteValue8;


            for(int i = 0 ; i < 5 ; i++)
            {

                owner->m_PTELEMETRY_FRAME->reserved1[i] = 0x00;
            }

            if(xinhaoneixing == "台阶码")
            {
                byteValue8 = 0x00;
            }
            else if(xinhaoneixing == "随机码")
            {
                byteValue8 = 0x01;
            }
            else if (xinhaoneixing == "用户码")
            {
                byteValue8 = 0x02;
            }
            owner->m_PTELEMETRY_FRAME->dataType = qToLittleEndian<quint8>(byteValue8);


            byteValue16 = tjmbujin.toInt();
            owner->m_PTELEMETRY_FRAME->stepValue = qToLittleEndian<quint8>(byteValue16);


            byteValue16 = tjmchushizi.toInt();
            owner->m_PTELEMETRY_FRAME->initStep = qToLittleEndian<quint16>(byteValue16);

            owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = ~bujielow;
            owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = ~bujiehigh;



            byteValue16 = zjsdzjbodao.toInt();
            owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;


            byteValue16 = zjsgzjbodao.toInt();
            owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;

            for(int i = 0 ; i < 4 ; i++)
            {
                owner->m_PTELEMETRY_FRAME->reserved2[i] = 0x00;
            }





            if(IDzijishufangshi == "加计数")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x00;
            }
            else if(IDzijishufangshi == "减计数")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x01;
            }

            if(IDzijizhi == "0开始")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x00;
            }
            else if(IDzijizhi == "1开始")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x01;
            }
           owner->m_PTELEMETRY_FRAME->bits.reserved = 0x00;


           if(Bianmaweizhi == "编码前")
           {
               owner->m_PTELEMETRY_FRAME->codingPosition = 0x01;

           }
           else if(Bianmaweizhi == "编码后")
           {
               owner->m_PTELEMETRY_FRAME->codingPosition = 0x00;
           }


            for(int i = 0 ; i < 22 ; i++)
            {
                owner->m_PTELEMETRY_FRAME->reserved3[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->functionCode = 0x01;
            owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_FRAME) + 12;

            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_FRAME),
                                                         sizeof(TELEMETRY_FRAME));


            quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


            int i  = 0 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);

            Logger::info("发射机1:配置帧格式下发");
            owner->setmaintable("发射机1:配置帧格式下发" , "上位机");

            array.clear();
        }

    
        if(ui->checkBox_sheping->isChecked())
        {

            owner->m_PTRANSMIT_CONFIG->txSelector = 0x01;
            double texttoint = fspinlv.toDouble();
            owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint * 1000));

            //texttoint = ui->lineEdit_tzbinpian->text().toInt();
            texttoint = static_cast<quint32>(tzbinpian.toDouble() * 1000 * 4294967296 / owner->fo);
            owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
            owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
            quint8 tiaozhifangshiint;
            quint8 modPolarity1int;
            quint8 modSwitch1int;
            quint8 carrier1int;

            if(tiao1 == "FSK调制")
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

            if(zai1 == "开")
            {
                carrier1int = 1;
            }
            else if(zai1 == "关")
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
            owner->m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
            owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
            owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;


            double y = fspinlv.toDouble();
            int x = fsygonglvkongz.toInt();
            if(x < 6)
            {
                x = 6;
            }
            double result;
            QString appDir = QCoreApplication::applicationDirPath();
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt"))
            {
               owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}


            owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
            owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(fsygonglvkongz.toInt()));




            for(int i= 0 ; i < 50 ; i++)
            {
                owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->functionCode = 0x03;

            owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_FRAME) + 12;

            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PTRANSMIT_CONFIG),
                                                         sizeof(TRANSMIT_CONFIG));


            m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


            int i  = 0 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);

            Logger::info("发射机1:配置射频参数下发");
            owner->setmaintable("发射机1:配置射频参数下发" , "上位机");

            array.clear();
        }

    
        if(ui->checkBox_xindao->isChecked())
        {



            owner->m_PTELEMETRY_ENCODING_CONFIG->txSelector = 0x01;

            if(bianmakai == "LDPC")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai == "TPC")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai == "RS")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai == "卷积")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai == "关闭")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }


            for(int i = 0 ; i < 3 ; i++)
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->reserved[i] = 0;
            }
            quint32 Btyevalue32;
            quint16 Btyevalue16;

            bool convertOk;
            QString processed;

            quint64 byteValue64;


            if(TPCtongbuma.isEmpty())
            {
                Btyevalue32 = 0x1ACFFC1D;
            }
            else
            {
                processed = TPCtongbuma.trimmed().toUpper();
                Btyevalue32 = processed.toULongLong(&convertOk , 16);

            }

            if(youxiaobiaozi.isEmpty())
            {
                Btyevalue16 = 0xFFFF;
            }
            else
            {

                processed = youxiaobiaozi.trimmed().toUpper();
                Btyevalue16 = processed.toULongLong(&convertOk , 16);
            }


             owner->m_PTELEMETRY_ENCODING_CONFIG->tpcSyncCode =  qToLittleEndian<quint32>(static_cast<quint32>(Btyevalue32));
             owner->m_PTELEMETRY_ENCODING_CONFIG->tpcValidFlag=  qToLittleEndian<quint16>(static_cast<quint16>(Btyevalue16));


             for(int i = 0 ;  i < 53 ; i++)
             {
                 owner->m_PTELEMETRY_ENCODING_CONFIG->padding[i] = 0x00;
             }


             owner->m_PPACKET_HEADER->functionCode = 0x05;

             owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_ENCODING_CONFIG) + 12;


             //QByteArray array;
             array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                          sizeof(PACKET_HEADER));
             array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_ENCODING_CONFIG),
                                                                      sizeof(TELEMETRY_ENCODING_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

             m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
             m_crc32 = qToLittleEndian<quint32>(m_crc32);
             array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


             int i  = 0 ;
             for (quint8 byte : array) {
                           QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                           qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                       }

             owner->udpManager->sendDatagram(array);


             Logger::info("发射机1:配置信道编码下发");
             owner->setmaintable("发射机1:配置信道编码下发" , "上位机");

             array.clear();







        }

        if(ui->checkBox_pcm->isChecked())
        {
            settings2.beginGroup("fa1pcmtab");

            owner->m_PPACKET_HEADER->functionCode = 0x07;

            owner->m_PPCMEMBEDCONfIG = new PCMEMBEDCONfIG;

            owner->m_PPCMEMBEDCONfIG->txSelector = 0x01;
            owner->m_PPCMEMBEDCONfIG->entryCount = settings2.value("anysum", 0).toUInt();


            for(int i =0 ; i < owner->m_PPCMEMBEDCONfIG->entryCount ; i++)
            {
                if(settings2.value(QString("zhenmoshi%1").arg(i), 0).toString() == "子帧模式")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x00;

                }
                else if(settings2.value(QString("zhenmoshi%1").arg(i), 0).toString() == "副帧模式")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x01;

                }

                owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos = settings2.value(QString("fuzhenweizhi%1").arg(i), 0).toInt() - 1;
                owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.reserved = 0x00;


                owner->m_PPCMEMBEDCONfIG->entries[i].childFramePos = settings2.value(QString("zizhenweizhi%1").arg(i), 0).toInt() - 1;

                if(settings2.value(QString("datafrom%1").arg(i), 0).toString() == "异步源")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x01;
                }
                else if(settings2.value(QString("datafrom%1").arg(i), 0).toString() == "GNSS")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x02;
                }
                else if(settings2.value(QString("datafrom%1").arg(i), 0).toString() == "安控")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x03;
                }
                owner->m_PPCMEMBEDCONfIG->entries[i].entryReserved = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].dataLength = settings2.value(QString("fangzhiLength%1").arg(i), 0).toInt();



            }

            for(int i = owner->m_PPCMEMBEDCONfIG->entryCount ; i < 10 ; i++)
            {
                owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.reserved = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].childFramePos = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].entryReserved = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].dataLength = 0x00;
            }

            for(int i = 0 ; i< 46 ; i++)
            {
                owner->m_PPCMEMBEDCONfIG->baoli[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->dataLength = sizeof(PCMEMBEDCONfIG) + 12;


            QByteArray array;
            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PPCMEMBEDCONfIG),
                                                         sizeof(PCMEMBEDCONfIG));//    quint8  txSelector;        // 发射机选择 [1B]

            quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

            int i  = 1 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);


            settings2.endGroup();

            Logger::info("发射机1:配置pcm下发");
            owner->setmaintable("发射机1:配置pcm下发" , "上位机");


        }


        if(ui->checkBox_yibu->isChecked())
        {

            owner->m_PPACKET_HEADER->functionCode = 0x09;

            settings2.beginGroup("fa1yibuyuantab");

            owner->m_PAsyncSourceConfig = new AsyncSourceConfig;

            owner->m_PAsyncSourceConfig->txSelector = 0x01;
            owner->m_PAsyncSourceConfig->entryCount = settings2.value("asynum", 0).toUInt();


            for(int i = 0 ; i < owner->m_PAsyncSourceConfig->entryCount ; i++)
            {
                owner->m_PAsyncSourceConfig->entries[i].frameLength = settings2.value(QString("zhenmoshi%1").arg(i), 0).toInt() - 1;

                if(settings2.value(QString("ankonglocation%1").arg(i), 0).toInt() == 0)
                {
                    owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = 0;
                }
                else
                {
                    owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = settings2.value(QString("ankonglocation%1").arg(i), 0).toInt() - 1;
                }

                if(settings2.value(QString("shujuliexing%1").arg(i), 0).toString() == "台阶码")
                {
                      owner->m_PAsyncSourceConfig->entries[i].dataType = 0x00;
                }
                else if(settings2.value(QString("shujuliexing%1").arg(i), 0).toString() == "随机码")
                {
                      owner->m_PAsyncSourceConfig->entries[i].dataType = 0x01;
                }
                else if(settings2.value(QString("shujuliexing%1").arg(i), 0).toString() == "用户码")
                {
                      owner->m_PAsyncSourceConfig->entries[i].dataType = 0x02;
                }


                owner->m_PAsyncSourceConfig->entries[i].stepIncrement = settings2.value(QString("taijiemabujin%1").arg(i), 0).toInt() ;
                owner->m_PAsyncSourceConfig->entries[i].initialValue = settings2.value(QString("taijiemainit%1").arg(i), 0).toInt();
                bool conversionOk;
                owner->m_PAsyncSourceConfig->entries[i].syncCode = settings2.value(QString("tongbuma%1").arg(i), 0).toString().trimmed().toUpper().toUInt(&conversionOk , 16);
                owner->m_PAsyncSourceConfig->entries[i].syncCodeLength = settings2.value(QString("tongbumalength%1").arg(i), 0).toInt();
                owner->m_PAsyncSourceConfig->entries[i].frameCounterLength = settings2.value(QString("zhenjishulength%1").arg(i), 0).toInt() - 1;
                owner->m_PAsyncSourceConfig->entries[i].zhenlv = settings2.value(QString("zhenlv%1").arg(i), 0).toInt();



            }

            for(int i = owner->m_PAsyncSourceConfig->entryCount ; i < 10 ; i++)
            {
                owner->m_PAsyncSourceConfig->entries[i].frameLength = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].dataType = 0x00;

                owner->m_PAsyncSourceConfig->entries[i].stepIncrement = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].initialValue = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].syncCode = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].syncCodeLength = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].frameCounterLength = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].zhenlv = 0x00;

            }

            for(int i = 0 ; i< 6 ; i++)
            {
                owner->m_PAsyncSourceConfig->baoli[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->dataLength = sizeof(AsyncSourceConfig) + 12;

            QByteArray array;
            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PAsyncSourceConfig),
                                                         sizeof(AsyncSourceConfig));//    quint8  txSelector;        // 发射机选择 [1B]

            quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

            int i  = 0 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);

            settings2.endGroup();


            Logger::info("发射机1:配置异步源下发");
            owner->setmaintable("发射机1:配置配置异步源下发下发" , "上位机");




            array.clear();
        }

        doWorkWithDelay(500);
        if(ui->checkBox_sheping->isChecked())
        {

            owner->m_PTRANSMIT_CONFIG->txSelector = 0x01;
            double texttoint = fspinlv.toDouble();
            owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint * 1000));

            //texttoint = ui->lineEdit_tzbinpian->text().toInt();
            texttoint = static_cast<quint32>(tzbinpian.toDouble() * 1000 * 4294967296 / owner->fo);
            owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
            owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
            quint8 tiaozhifangshiint;
            quint8 modPolarity1int;
            quint8 modSwitch1int;
            quint8 carrier1int;

            if(tiao1 == "FSK调制")
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

            if(zai1 == "开")
            {
                carrier1int = 1;
            }
            else if(zai1 == "关")
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
            owner->m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
            owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
            owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;


            double y = fspinlv.toDouble();
            int x = fsygonglvkongz.toInt();
            if(x < 6)
            {
                x = 6;
            }
            double result;
            QString appDir = QCoreApplication::applicationDirPath();
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt"))
            {
               owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}


            owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
            owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(fsygonglvkongz.toInt()));




            for(int i= 0 ; i < 50 ; i++)
            {
                owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->functionCode = 0x03;

            owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_FRAME) + 12;

            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PTRANSMIT_CONFIG),
                                                         sizeof(TRANSMIT_CONFIG));


            m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


            int i  = 0 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);

            Logger::info("发射机1:配置射频参数下发");
            owner->setmaintable("发射机1:配置射频参数下发" , "上位机");

            array.clear();
        }


    



    }



    if(ui->Btn_fayi2->isChecked())
    {
        if(ui->checkBox_geshi_2->isChecked())
        {
            byteValue32 = static_cast<quint32>(Malv_2.toDouble() * 1000 * 4294967296 / owner->fo); // 0x01
            owner->m_PTELEMETRY_FRAME->txSelector = 0x02;
            owner->m_PTELEMETRY_FRAME->pcmRate = qToLittleEndian<quint32>(byteValue32);


            byteValue16 = static_cast<quint16>(zhenchang_2.toInt()  - 1);

            owner->m_PTELEMETRY_FRAME->subFrameLength.bit.length = qToLittleEndian<quint16>(byteValue16);

            owner->m_PTELEMETRY_FRAME->subFrameLength.bit.moFeiFlag = ismofei;


            if(fuzhenfanshi_2 == "无副帧")
            {
                byteValue8 = 0x00;
            }
            else
            {
                byteValue8 = static_cast<quint8>(fuzhenchangdu_2.toInt() - 1);

            }

            owner->m_PTELEMETRY_FRAME->subFrameCount = qToLittleEndian<quint8>(byteValue8);

            owner->m_PTELEMETRY_FRAME->WordConfig.bits.wordLengthMinusOne = static_cast<quint8>(zichang_2.toInt() - 1);
            quint8 codeType;

            if (maxing_2 == "NRZ-L")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000000;
            }

            else if (maxing_2 == "NRZ-M")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000010;
            }

            else if (maxing_2 == "NRZ-S")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000011;
            }
            else if (maxing_2 == "BIφ-L")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000100;
            }

            else if (maxing_2 == "BIφ-M")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000110;
            }


            else if (maxing_2 == "BIφ-S")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000111;
            }


            else if (maxing_2 == "RNRZ-L")
            {
                owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00001000;
            }




            byteValue16 = fuzhenlvxu_2.toInt() - 1 ; //ID码副帧时, 副帧的ID码所在路序-1。循环码副帧时，副帧特征字在子帧的路序-1
            owner->m_PTELEMETRY_FRAME->featurePosition = qToLittleEndian<quint16>(byteValue16);

            bool convertOk;
            QString processed = zhenmazhu_2.trimmed().toUpper();
            byteValue64 = processed.toULongLong(&convertOk , 16);
            owner->m_PTELEMETRY_FRAME->syncCode = qToLittleEndian<quint64>(byteValue64);

            processed = xhfztongbuma_2.trimmed().toUpper();
            byteValue16 = processed.toULongLong(&convertOk , 16);
            owner->m_PTELEMETRY_FRAME->loopSyncCode = qToLittleEndian<quint16>(byteValue16);


             quint8 subframeType ;
             quint8 bitLengthMinusOne;
            if(fuzhenfanshi_2 == "无副帧")
            {
                subframeType = 0 ;
            }

            else if(fuzhenfanshi_2 == "反码副帧")

            {
                subframeType = 2 ;
            }

            else if(fuzhenfanshi_2 == "循环副帧")
            {
                subframeType = 1 ;
            }

            else if(fuzhenfanshi_2 == "ID副帧")
            {
                subframeType = 3 ;
            }

            bitLengthMinusOne = zhenmazhu_2.size() * 4 - 1;


            byteValue8 = (subframeType << 6) | bitLengthMinusOne ;

            owner->m_PTELEMETRY_FRAME->frameType = byteValue8;


            for(int i = 0 ; i < 5 ; i++)
            {

                owner->m_PTELEMETRY_FRAME->reserved1[i] = 0x00;
            }

            if(xinhaoneixing_2 == "台阶码")
            {
                byteValue8 = 0x00;
            }
            else if(xinhaoneixing_2 == "随机码")
            {
                byteValue8 = 0x01;
            }
            else if (xinhaoneixing_2 == "用户码")
            {
                byteValue8 = 0x02;
            }
            owner->m_PTELEMETRY_FRAME->dataType = qToLittleEndian<quint8>(byteValue8);


            byteValue16 = tjmbujin_2.toInt();
            owner->m_PTELEMETRY_FRAME->stepValue = qToLittleEndian<quint8>(byteValue16);


            byteValue16 = tjmchushizi_2.toInt();
            owner->m_PTELEMETRY_FRAME->initStep = qToLittleEndian<quint16>(byteValue16);

            owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = ~bujielow_2;
            owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = ~bujiehigh_2;




            byteValue16 = zjsdzjbodao_2.toInt();
            owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;


            byteValue16 = zjsgzjbodao_2.toInt();
            owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;

            for(int i = 0 ; i < 4 ; i++)
            {
                owner->m_PTELEMETRY_FRAME->reserved2[i] = 0x00;
            }





            if(IDzijishufangshi_2 == "加计数")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x00;
            }
            else if(IDzijishufangshi_2 == "减计数")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x01;
            }

            if(IDzijizhi_2 == "0开始")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x00;
            }
            else if(IDzijizhi_2 == "1开始")
            {
                owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x01;
            }
           owner->m_PTELEMETRY_FRAME->bits.reserved = 0x00;


           if(Bianmaweizhi_2 == "编码前")
           {
               owner->m_PTELEMETRY_FRAME->codingPosition = 0x01;

           }
           else if(Bianmaweizhi_2 == "编码后")
           {
               owner->m_PTELEMETRY_FRAME->codingPosition = 0x00;
           }


            for(int i = 0 ; i < 22 ; i++)
            {
                owner->m_PTELEMETRY_FRAME->reserved3[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->functionCode = 0x01;
            owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_FRAME) + 12;

            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_FRAME),
                                                         sizeof(TELEMETRY_FRAME));


            quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


            int i  = 1 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);

            Logger::info("发射机2:配置帧格式下发");
            owner->setmaintable("发射机2:配置帧格式下发" , "上位机");

            array.clear();
        }

    
        if(ui->checkBox_sheping_2->isChecked())
        {

            owner->m_PTRANSMIT_CONFIG->txSelector = 0x02;
            double texttoint = fspinlv_2.toDouble();
            owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint * 1000));


            //texttoint = ui->lineEdit_tzbinpian->text().toInt();
            texttoint = static_cast<quint32>(tzbinpian_2.toDouble() * 1000 * 4294967296 / owner->fo);
            owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
            owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));

            quint8 tiaozhifangshiint;
            quint8 modPolarity1int;
            quint8 modSwitch1int;
            quint8 carrier1int;
            if(tiao1_2 == "FSK调制")
            {
                tiaozhifangshiint =0b0000;
            }
            else if(tiao1_2 == "BPSK调制")
            {
                tiaozhifangshiint =0b0001;
            }
            else if(tiao1_2 == "QPSK调制")
            {
                tiaozhifangshiint =0b0010;
            }

            if(zai1_2 == "开")
            {
                carrier1int = 1;
            }
            else if(zai1_2 == "关")
            {
                carrier1int = 0;
            }

            if(tiaokai1_2 == "开")
            {
                modSwitch1int = 1;
            }
            else if(tiaokai1_2 == "关")
            {
                modSwitch1int = 0;
            }

            if(tiaoji1_2 == "正")
            {
                modPolarity1int = 0;
            }
            else if(tiaoji1_2 == "负")
            {
                modPolarity1int = 1;
            }
            owner->m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
            owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
            owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;


            double y = fspinlv_2.toDouble();
            int x = fsygonglvkongz_2.toInt();
            if(x < 6)
            {
                x = 6;
            }
            double result;

            QString appDir = QCoreApplication::applicationDirPath();
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
               owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}


            owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
            owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(fsygonglvkongz.toInt()));


            for(int i= 0 ; i < 51 ; i++)
            {
                owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->functionCode = 0x03;

            owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_FRAME) + 12;

            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PTRANSMIT_CONFIG),
                                                         sizeof(TRANSMIT_CONFIG));


            m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


            int i  = 0 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);

            Logger::info("发射机2:配置射频参数下发");
            owner->setmaintable("发射机2:配置射频参数下发" , "上位机");

            array.clear();
        }
    
        if(ui->checkBox_xindao_2->isChecked())
        {



            owner->m_PTELEMETRY_ENCODING_CONFIG->txSelector = 0x02;

            if(bianmakai_2 == "LDPC")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai_2 == "TPC")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai_2 == "RS")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai_2 == "卷积")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 1;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }
            else if(bianmakai_2 == "关闭")
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
                owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
            }


            for(int i = 0 ; i < 3 ; i++)
            {
                owner->m_PTELEMETRY_ENCODING_CONFIG->reserved[i] = 0;
            }
            quint32 Btyevalue32;
            quint16 Btyevalue16;

            bool convertOk;
            QString processed;

            quint64 byteValue64;


            if(TPCtongbuma_2.isEmpty())
            {
                Btyevalue32 = 0x1ACFFC1D;
            }
            else
            {
                processed = TPCtongbuma_2.trimmed().toUpper();
                Btyevalue32 = processed.toULongLong(&convertOk , 16);

            }

            if(youxiaobiaozi_2.isEmpty())
            {
                Btyevalue16 = 0xFFFF;
            }
            else
            {

                processed = youxiaobiaozi_2.trimmed().toUpper();
                Btyevalue16 = processed.toULongLong(&convertOk , 16);
            }


             owner->m_PTELEMETRY_ENCODING_CONFIG->tpcSyncCode =  qToLittleEndian<quint32>(static_cast<quint32>(Btyevalue32));
             owner->m_PTELEMETRY_ENCODING_CONFIG->tpcValidFlag=  qToLittleEndian<quint16>(static_cast<quint16>(Btyevalue16));


             for(int i = 0 ;  i < 53 ; i++)
             {
                 owner->m_PTELEMETRY_ENCODING_CONFIG->padding[i] = 0x00;
             }
             owner->m_PPACKET_HEADER->functionCode = 0x05;
             owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_ENCODING_CONFIG) + 12;


             //QByteArray array;
             array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                          sizeof(PACKET_HEADER));
             array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_ENCODING_CONFIG),
                                                                      sizeof(TELEMETRY_ENCODING_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

             m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
             m_crc32 = qToLittleEndian<quint32>(m_crc32);
             array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


             int i  = 0 ;
             for (quint8 byte : array) {
                           QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                           qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                       }

             owner->udpManager->sendDatagram(array);


             Logger::info("发射机2:配置信道编码下发");
             owner->setmaintable("发射机2:配置信道编码下发" , "上位机");

             array.clear();








        }


        if(ui->checkBox_pcm_2->isChecked())
        {
            settings2.beginGroup("fa2pcmtab");

            owner->m_PPACKET_HEADER->functionCode = 0x07;

            owner->m_PPCMEMBEDCONfIG = new PCMEMBEDCONfIG;

            owner->m_PPCMEMBEDCONfIG->txSelector = 0x02;
            owner->m_PPCMEMBEDCONfIG->entryCount = settings2.value("anysum", 0).toUInt();


            for(int i =0 ; i < owner->m_PPCMEMBEDCONfIG->entryCount ; i++)
            {
                if(settings2.value(QString("zhenmoshi%1").arg(i), 0).toString() == "子帧模式")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x00;
                }
                else if(settings2.value(QString("zhenmoshi%1").arg(i), 0).toString() == "副帧模式")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x01;
                    //owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos = settings3.value(QString("fuzhenweizhi%1").arg(i), 0).toInt() - 1;
                }

                owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos = settings2.value(QString("fuzhenweizhi%1").arg(i), 0).toInt() - 1;
                owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.reserved = 0x00;


                owner->m_PPCMEMBEDCONfIG->entries[i].childFramePos = settings2.value(QString("zizhenweizhi%1").arg(i), 0).toInt() - 1;

                if(settings2.value(QString("datafrom%1").arg(i), 0).toString() == "异步源")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x01;
                }
                else if(settings2.value(QString("datafrom%1").arg(i), 0).toString() == "GNSS")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x02;
                }
                else if(settings2.value(QString("datafrom%1").arg(i), 0).toString() == "安控")
                {
                    owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x03;
                }
                owner->m_PPCMEMBEDCONfIG->entries[i].entryReserved = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].dataLength = settings2.value(QString("fangzhiLength%1").arg(i), 0).toInt();



            }

            for(int i = owner->m_PPCMEMBEDCONfIG->entryCount ; i < 10 ; i++)
            {
                owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.reserved = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].childFramePos = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].entryReserved = 0x00;
                owner->m_PPCMEMBEDCONfIG->entries[i].dataLength = 0x00;
            }

            for(int i = 0 ; i< 46 ; i++)
            {
                owner->m_PPCMEMBEDCONfIG->baoli[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->dataLength = sizeof(PCMEMBEDCONfIG) + 12;

            QByteArray array;
            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PPCMEMBEDCONfIG),
                                                         sizeof(PCMEMBEDCONfIG));//    quint8  txSelector;        // 发射机选择 [1B]

            quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

            int i  = 1 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);


            settings2.endGroup();

            Logger::info("发射机2:配置pcm下发");
            owner->setmaintable("发射机2:配置pcm下发" , "上位机");
        }


        if(ui->checkBox_yibu_2->isChecked())
        {
            owner->m_PPACKET_HEADER->functionCode = 0x09;

            settings2.beginGroup("fa2yibuyuantab");

            owner->m_PAsyncSourceConfig = new AsyncSourceConfig;

            owner->m_PAsyncSourceConfig->txSelector = 0x02;
            owner->m_PAsyncSourceConfig->entryCount = settings2.value("asynum", 0).toUInt();


            for(int i = 0 ; i < owner->m_PAsyncSourceConfig->entryCount ; i++)
            {
                owner->m_PAsyncSourceConfig->entries[i].frameLength = settings2.value(QString("zhenmoshi%1").arg(i), 0).toInt() - 1;

                if(settings2.value(QString("ankonglocation%1").arg(i), 0).toInt() == 0)
                {
                    owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = 0;
                }
                else
                {
                    owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = settings2.value(QString("ankonglocation%1").arg(i), 0).toInt() - 1;
                }



                if(settings2.value(QString("shujuliexing%1").arg(i), 0).toString() == "台阶码")
                {
                      owner->m_PAsyncSourceConfig->entries[i].dataType = 0x00;
                }
                else if(settings2.value(QString("shujuliexing%1").arg(i), 0).toString() == "随机码")
                {
                      owner->m_PAsyncSourceConfig->entries[i].dataType = 0x01;
                }
                else if(settings2.value(QString("shujuliexing%1").arg(i), 0).toString() == "用户码")
                {
                      owner->m_PAsyncSourceConfig->entries[i].dataType = 0x02;
                }


                owner->m_PAsyncSourceConfig->entries[i].stepIncrement = settings2.value(QString("taijiemabujin%1").arg(i), 0).toInt() ;
                owner->m_PAsyncSourceConfig->entries[i].initialValue = settings2.value(QString("taijiemainit%1").arg(i), 0).toInt();
                bool conversionOk;
                owner->m_PAsyncSourceConfig->entries[i].syncCode = settings2.value(QString("tongbuma%1").arg(i), 0).toString().trimmed().toUpper().toUInt(&conversionOk , 16);
                owner->m_PAsyncSourceConfig->entries[i].syncCodeLength = settings2.value(QString("tongbumalength%1").arg(i), 0).toInt();
                owner->m_PAsyncSourceConfig->entries[i].frameCounterLength = settings2.value(QString("zhenjishulength%1").arg(i), 0).toInt() - 1;
                owner->m_PAsyncSourceConfig->entries[i].zhenlv = settings2.value(QString("zhenlv%1").arg(i), 0).toInt();



            }

            for(int i = owner->m_PAsyncSourceConfig->entryCount ; i < 10 ; i++)
            {
                owner->m_PAsyncSourceConfig->entries[i].frameLength = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].dataType = 0x00;

                owner->m_PAsyncSourceConfig->entries[i].stepIncrement = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].initialValue = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].syncCode = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].syncCodeLength = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].frameCounterLength = 0x00;
                owner->m_PAsyncSourceConfig->entries[i].zhenlv = 0x00;

            }

            for(int i = 0 ; i< 6 ; i++)
            {
                owner->m_PAsyncSourceConfig->baoli[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->dataLength = sizeof(AsyncSourceConfig) + 12;

            QByteArray array;
            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PAsyncSourceConfig),
                                                         sizeof(AsyncSourceConfig));//    quint8  txSelector;        // 发射机选择 [1B]

            quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

            int i  = 0 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);


               Logger::info("发射机2:配置异步源下发");
               owner->setmaintable("发射机2:配置异步源下发" , "上位机");

               settings2.endGroup();



            array.clear();
        }

        doWorkWithDelay(500);
        if(ui->checkBox_sheping_2->isChecked())
        {

            owner->m_PTRANSMIT_CONFIG->txSelector = 0x02;
            double texttoint = fspinlv_2.toDouble();
            owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint * 1000));


            //texttoint = ui->lineEdit_tzbinpian->text().toInt();
            texttoint = static_cast<quint32>(tzbinpian_2.toDouble() * 1000 * 4294967296 / owner->fo);
            owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
            owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));

            quint8 tiaozhifangshiint;
            quint8 modPolarity1int;
            quint8 modSwitch1int;
            quint8 carrier1int;
            if(tiao1_2 == "FSK调制")
            {
                tiaozhifangshiint =0b0000;
            }
            else if(tiao1_2 == "BPSK调制")
            {
                tiaozhifangshiint =0b0001;
            }
            else if(tiao1_2 == "QPSK调制")
            {
                tiaozhifangshiint =0b0010;
            }

            if(zai1_2 == "开")
            {
                carrier1int = 1;
            }
            else if(zai1_2 == "关")
            {
                carrier1int = 0;
            }

            if(tiaokai1_2 == "开")
            {
                modSwitch1int = 1;
            }
            else if(tiaokai1_2 == "关")
            {
                modSwitch1int = 0;
            }

            if(tiaoji1_2 == "正")
            {
                modPolarity1int = 0;
            }
            else if(tiaoji1_2 == "负")
            {
                modPolarity1int = 1;
            }
            owner->m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
            owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
            owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
            owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;


            double y = fspinlv_2.toDouble();
            int x = fsygonglvkongz_2.toInt();
            if(x < 6)
            {
                x = 6;
            }
            double result;

            QString appDir = QCoreApplication::applicationDirPath();
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
               owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}


            owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
            owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(fsygonglvkongz.toInt()));


            for(int i= 0 ; i < 51 ; i++)
            {
                owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
            }

            owner->m_PPACKET_HEADER->functionCode = 0x03;

            owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_FRAME) + 12;

            array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                           sizeof(PACKET_HEADER));
            array.append(reinterpret_cast<const char*>(owner->m_PTRANSMIT_CONFIG),
                                                         sizeof(TRANSMIT_CONFIG));


            m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
            m_crc32 = qToLittleEndian<quint32>(m_crc32);
            array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


            int i  = 0 ;
            for (quint8 byte : array) {
                          QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                          qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                      }

            owner->udpManager->sendDatagram(array);

            Logger::info("发射机2:配置射频参数下发");
            owner->setmaintable("发射机2:配置射频参数下发" , "上位机");

            array.clear();






        }
    }
    if(ui->checkBox_ankong->isChecked())
    {
        // 基本参数组
        settings2.beginGroup("ankongpeiz");

        byteValue32 = static_cast<quint32>(settings2.value("zaibopinlv", "1000").toInt()); // 0x01
        owner->m_PSecuritySourceConfig->carrierFrequency = qToLittleEndian<quint32>(byteValue32);


        byteValue32 = static_cast<quint32>(settings2.value("fuzaibopinlv", "1000").toInt()* 4294967296 / owner->fo_2); // 0x01
        owner->m_PSecuritySourceConfig->subcarrierFrequency = qToLittleEndian<quint32>(byteValue32);

        if(settings2.value("ankongmoshi").toString()  == "DPSK-FM")
        {
            byteValue8 = 0x00;
        }
        else if(settings2.value("ankongmoshi").toString()  == "主字母")
        {
            byteValue8 = 0x01;
        }
       owner->m_PSecuritySourceConfig->modeBits.modeSelect = qToLittleEndian<quint16>(byteValue8);
       owner->m_PSecuritySourceConfig->modeBits.reserved = 0x00;

       //byteValue8 = static_cast<quint8>(ui->lineEdit_DPSK_daikuan->text().toInt());

       owner->m_PSecuritySourceConfig->dpskFmBandwidth = 0x00;

       byteValue32 = static_cast<quint32>(settings2.value("DPSK_FMzilinmalv").toInt()* 4294967296 / owner->fo_2);
       owner->m_PSecuritySourceConfig->dpskFmInstructionRate = qToLittleEndian<quint32>(byteValue32);

       byteValue16 = static_cast<quint16>(settings2.value("DPSK_FM_zilingLength").toInt() - 1);
       owner->m_PSecuritySourceConfig->dpskFmInstructionLength = qToLittleEndian<quint16>(byteValue16);

//       if(ui->comboBox_ankongmoshi->currentText() == "DPSK-FM")
//       {
//           if(ui->comboBox->currentText().toInt() > 2400)
//           {
//               owner->m_PSecuritySourceConfig->dpskFmBandwidth = 1;
//           }
//           else if(ui->comboBox->currentText().toInt() <= 600)
//           {
//               owner->m_PSecuritySourceConfig->dpskFmBandwidth = 3;
//           }
//           else
//           {
//               owner->m_PSecuritySourceConfig->dpskFmBandwidth = 0;
//           }
//       }
//       else
//       {
//           owner->m_PSecuritySourceConfig->dpskFmBandwidth = 0;
//       }

     if(settings2.value("ankongmoshi").toString() == "DPSK-FM")
     {

       if(settings2.value("DPSK_FMzilinmalv").toInt() > 2400)
       {
           owner->m_PSecuritySourceConfig->dpskFmBandwidth = 1;
       }
       else if(settings2.value("DPSK_FMzilinmalv").toInt() <= 600)
       {
           owner->m_PSecuritySourceConfig->dpskFmBandwidth = 3;
       }
       else
       {
           owner->m_PSecuritySourceConfig->dpskFmBandwidth = 0;
       }
     }
     else
     {
         owner->m_PSecuritySourceConfig->dpskFmBandwidth = 0;
     }


       if(settings2.value("DPSK_FM_qiandaoma").toString().isEmpty())
       {
           owner->m_PSecuritySourceConfig->dpskFmPreamble[0]  = 0xFF;
           owner->m_PSecuritySourceConfig->dpskFmPreamble[1]  = 0xFF;
           owner->m_PSecuritySourceConfig->dpskFmPreamble[2]  = 0xFF;
       }
       else
       {
           bool ok;
           byteValue32 = static_cast<quint32>(settings2.value("DPSK_FM_qiandaoma").toString().toInt(&ok ,16));
           quint8 byte1 = static_cast<quint8>(byteValue32 & 0xFF);// 最低有效字节
           quint8 byte2 = static_cast<quint8>((byteValue32 >> 8) & 0xFF);  // 中间字节
           quint8 byte3 = static_cast<quint8>((byteValue32 >> 16) & 0xFF); // 最高有效字节

           owner->m_PSecuritySourceConfig->dpskFmPreamble[0]  = byte1;
           owner->m_PSecuritySourceConfig->dpskFmPreamble[1]  = byte2;
           owner->m_PSecuritySourceConfig->dpskFmPreamble[2]  = byte3;

       }

       if(settings2.value("DPSK_FM_tongbu").toString().isEmpty())
       {
           owner->m_PSecuritySourceConfig->dpskFmInstructionSyncCode = qToLittleEndian<quint16>(0xEB90);
       }
       else
       {
           bool ok;
           byteValue16 = static_cast<quint16>(settings2.value("DPSK_FM_tongbu").toString().toInt(&ok ,16));
           owner->m_PSecuritySourceConfig->dpskFmInstructionSyncCode = qToLittleEndian<quint16>(byteValue16);
       }



       if(settings2.value("maxing").toString() == "NRZ-L")
       {
           owner->m_PSecuritySourceConfig->codeBits.codeScheme = 0b0000;
       }
       else if(settings2.value("maxing").toString() == "NRZ-M")
       {
           owner->m_PSecuritySourceConfig->codeBits.codeScheme = 0b0010;
       }
       else if(settings2.value("maxing").toString() == "NRZ-S")
       {
           owner->m_PSecuritySourceConfig->codeBits.codeScheme = 0b0011;
       }

       qDebug() << owner->m_PSecuritySourceConfig->subcarrierFrequency
                << owner->m_PSecuritySourceConfig->dpskFmInstructionRate;

       owner->m_PSecuritySourceConfig->subcarrierTocoderate = owner->m_PSecuritySourceConfig->subcarrierFrequency
                                                            / owner->m_PSecuritySourceConfig->dpskFmInstructionRate - 1;

//       owner->m_PSecuritySourceConfig->subcarrierTocoderate = 2;



       owner->m_PSecuritySourceConfig->codeBits.reserved = static_cast<quint8>(0x00);

       settings2.endGroup();


        // 基本参数组
        settings2.beginGroup("Kkezhi");

        bool ok;
        byteValue8 = static_cast<quint8>(settings2.value("K1_dizhi").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K1_Address_Code = qToLittleEndian<quint8>(byteValue8);

        byteValue16 = static_cast<quint16>(settings2.value("K1_gongneng").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K1_Function_Code = qToLittleEndian<quint16>(byteValue16);

        byteValue8 = static_cast<quint8>(settings2.value("K1_tianchong", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K1_Fill_Code = qToLittleEndian<quint8>(byteValue8);


        byteValue8 = static_cast<quint8>(settings2.value("K2_dizhi", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K2_Address_Code = qToLittleEndian<quint8>(byteValue8);

        byteValue16 = static_cast<quint16>(settings2.value("K2_gongneng", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K2_Function_Code = qToLittleEndian<quint16>(byteValue16);

        byteValue8 = static_cast<quint8>(settings2.value("K2_tianchong", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K2_Fill_Code = qToLittleEndian<quint8>(byteValue8) ;

        byteValue8 = static_cast<quint8>(settings2.value("K3_dizhi", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K3_Address_Code = qToLittleEndian<quint8>(byteValue8);

        byteValue16 = static_cast<quint16>(settings2.value("K3_gongneng", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K3_Function_Code = qToLittleEndian<quint16>(byteValue16);

        byteValue8 = static_cast<quint8>(settings2.value("K3_tianchong", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K3_Fill_Code = qToLittleEndian<quint8>(byteValue8) ;

        byteValue8 = static_cast<quint8>(settings2.value("K4_dizhi", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K4_Address_Code = qToLittleEndian<quint8>(byteValue8);

        byteValue16 = static_cast<quint16>(settings2.value("K4_gongneng", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K4_Function_Code = qToLittleEndian<quint16>(byteValue16);

        byteValue8 = static_cast<quint8>(settings2.value("K4_tianchong", "12").toString().toInt(&ok ,16));
        owner->m_PSecuritySourceConfig->DPSK_K4_Fill_Code = qToLittleEndian<quint8>(byteValue8);
        settings2.endGroup();


        // 基本参数组
        settings2.beginGroup("Kziling");

        owner->m_PSecuritySourceConfig->MainLetter_Self_check[0] = qToBigEndian<quint16>(updateankong(settings2.value("K1_1").toString()));
        qDebug() << owner->m_PSecuritySourceConfig->MainLetter_Self_check[0]
                 << settings2.value("K1_1").toString();
        owner->m_PSecuritySourceConfig->MainLetter_Self_check[1] = qToBigEndian<quint16>(updateankong(settings2.value("K1_2").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_check[2] = qToBigEndian<quint16>(updateankong(settings2.value("K1_3").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_check[3] = qToBigEndian<quint16>(updateankong(settings2.value("K1_4").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_check[4] = qToBigEndian<quint16>(updateankong(settings2.value("K1_5").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_check[5] = qToBigEndian<quint16>(updateankong(settings2.value("K1_6").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_check[6] = qToBigEndian<quint16>(updateankong(settings2.value("K1_7").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Reset[0] = qToBigEndian<quint16>(updateankong(settings2.value("K2_1").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Reset[1] = qToBigEndian<quint16>(updateankong(settings2.value("K2_2").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Reset[2] = qToBigEndian<quint16>(updateankong(settings2.value("K2_3").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Reset[3] = qToBigEndian<quint16>(updateankong(settings2.value("K2_4").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Reset[4] = qToBigEndian<quint16>(updateankong(settings2.value("K2_5").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Reset[5] = qToBigEndian<quint16>(updateankong(settings2.value("K2_6").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Reset[6] = qToBigEndian<quint16>(updateankong(settings2.value("K2_7").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Unlocked[0] = qToBigEndian<quint16>(updateankong(settings2.value("K3_1").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Unlocked[1] = qToBigEndian<quint16>(updateankong(settings2.value("K3_2").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Unlocked[2] = qToBigEndian<quint16>(updateankong(settings2.value("K3_3").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Unlocked[3] = qToBigEndian<quint16>(updateankong(settings2.value("K3_4").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Unlocked[4] = qToBigEndian<quint16>(updateankong(settings2.value("K3_5").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Unlocked[5] = qToBigEndian<quint16>(updateankong(settings2.value("K3_6").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Unlocked[6] = qToBigEndian<quint16>(updateankong(settings2.value("K3_7").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[0] = qToBigEndian<quint16>(updateankong(settings2.value("K4_1").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[1] = qToBigEndian<quint16>(updateankong(settings2.value("K4_2").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[2] = qToBigEndian<quint16>(updateankong(settings2.value("K4_3").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[3] = qToBigEndian<quint16>(updateankong(settings2.value("K4_4").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[4] = qToBigEndian<quint16>(updateankong(settings2.value("K4_5").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[5] = qToBigEndian<quint16>(updateankong(settings2.value("K4_6").toString()));
        owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[6] = qToBigEndian<quint16>(updateankong(settings2.value("K4_7").toString()));
        settings2.endGroup();


        for(int i = 0 ; i < 33 ; i++ )
        {
            owner->m_PSecuritySourceConfig->baliu2[i] = 0x00;
        }




        owner->m_PPACKET_HEADER->functionCode = 0x0B;
        array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                       sizeof(PACKET_HEADER));
        array.append(reinterpret_cast<const char*>(owner->m_PSecuritySourceConfig),
                                                       sizeof(PCMEMBEDCONfIG));


        m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
        m_crc32 = qToLittleEndian<quint32>(m_crc32);
        array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


        int i  = 1 ;
        for (quint8 byte : array) {
                      QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                      qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                  }

        owner->udpManager->sendDatagram(array);

        array.clear();
    }




    }


}

void fileMacroDialog::on_Btn_newsave_clicked()
{

    // 创建自定义对话框
       CustomDialog dialog(this);
       // 获取两个文本框的值
       QString mingzi;
       QString time;


       // 显示对话框，并等待用户操作
       if (dialog.exec() == QDialog::Accepted)
       {
           // 获取两个文本框的值
           mingzi = dialog.getText1();
           time = dialog.getText2();

           // 在文本编辑框中显示
           QString displayText = QString("文本框1: %1\n文本框2: %2").arg(mingzi).arg(time);
           qDebug() << displayText;
       }


    ++tablecol;

    ui->tableWidget_renwu->setRowCount(tablecol);

    QString taskConfigPath = QCoreApplication::applicationDirPath() + "/TaskMacro";
    QDir taskDir(taskConfigPath);


    QString filename = QString("%1_%2.ini").arg(mingzi).arg(time);

    // 构建文件路径
    QString filePath = taskDir.absoluteFilePath(filename);

    QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "错误: 无法创建文件:" << file.errorString();
            return;
        }

        file.close();


    updatetable();

    //loadSettings(tablecol - 1);


}

void fileMacroDialog::on_Btn_delete_clicked()
{
    int isdelete = QMessageBox::information(this , "提示" ,"是否删除选中的任务宏",QMessageBox::Yes | QMessageBox::No);

    if(isdelete == QMessageBox::No)
    {
       return;
    }




    QList<QTableWidgetItem*> selectedItems = ui->tableWidget_renwu->selectedItems();

    QString mingzi;
    QString time;

    mingzi = selectedItems[1]->text();
    time = selectedItems[2]->text();

    QString taskConfigPath = QCoreApplication::applicationDirPath() + "/TaskMacro";
    QDir taskDir(taskConfigPath);
    QString filename = QString("%1_%2").arg(mingzi).arg(time);
    QString filePath = taskDir.absoluteFilePath(filename);

    QFile file(filePath);

        if (!file.exists()) {
            qDebug() << "File does not exist:" << filePath;
            return ;
        }

        if (file.remove())
        {
            qDebug() << "File deleted successfully:" << filePath;

        }

        updatetable();

}

void fileMacroDialog::on_Btn_fayi1_toggled(bool checked)
{
    if(checked == true)
    {
       ui->checkBox_geshi->setChecked(true);
       ui->checkBox_sheping->setChecked(true);
       ui->checkBox_xindao->setChecked(true);
       ui->checkBox_pcm->setChecked(true);
       ui->checkBox_yibu->setChecked(true);
    }
    else if(checked == false)
    {
       ui->checkBox_geshi->setChecked(false);
       ui->checkBox_sheping->setChecked(false);
       ui->checkBox_xindao->setChecked(false);
       ui->checkBox_pcm->setChecked(false);
       ui->checkBox_yibu->setChecked(false);
    }
}

void fileMacroDialog::on_Btn_fayi2_toggled(bool checked)
{
    if(checked == true)
    {
       ui->checkBox_geshi_2->setChecked(true);
       ui->checkBox_sheping_2->setChecked(true);
       ui->checkBox_xindao_2->setChecked(true);
       ui->checkBox_pcm_2->setChecked(true);
       ui->checkBox_yibu_2->setChecked(true);
    }
    else if(checked == false)
    {
       ui->checkBox_geshi_2->setChecked(false);
       ui->checkBox_sheping_2->setChecked(false);
       ui->checkBox_xindao_2->setChecked(false);
       ui->checkBox_pcm_2->setChecked(false);
       ui->checkBox_yibu_2->setChecked(false);
    }
}
