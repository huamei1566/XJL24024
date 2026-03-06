#include "dialogfasheset.h"
#include "ui_dialogfasheset.h"

#include "mainwindow.h"
#include "telemetrypcmset.h"
#include <QMessageBox>
#include <QMenu>
#include <QFileDialog>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"


Dialogfasheset::Dialogfasheset( int sig , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogfasheset)
{
    ui->setupUi(this);
    pattern = sig;

    setWindowModality(Qt::ApplicationModal);


    ui->Btn_peiz->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处

                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );


    ui->Btn_readpeiz->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_Application_2->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_Application->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );


    ui->Btn_new->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_new_2->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
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
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );


    ui->Btn_delete_2->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_peziall->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_zhuangzai->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_readApplication->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->Btn_readApplication_2->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );

    ui->pushButton_selsetxlsx->setStyleSheet(
                "QPushButton {"
                "   background-color: #285C2E;"  // 主背景色（深绿）
                "   border: 1px solid #4FBFC2;"   // 边框（浅青）
                "   border-radius: 5px;"          // 圆角
                "   color: #FFFFFF;"              // 文字颜色改为白色 🔴 关键修改处
                "}"
                "QPushButton:hover {"
                "   background-color: #459E4F;"   // 悬停时亮青
                "}"
                "QPushButton:pressed {"
                "   background-color: #1D4221;"   // 按下时暗青"
                "}"
            );



//    ui->comboBox_zhenmazhu->setValidator(new QRegExpValidator(QRegExp(".{4,8}"), this));

//    ui->lineEdit_tjmbujin->setValidator(new StrictIntValidator(0, 65535, this));
//    ui->lineEdit_tjmchushizi->setValidator(new StrictIntValidator(0, 65535, this));
//    ui->lineEdit_zjsdzjbodao->setValidator(new StrictIntValidator(0, 65535, this));
//    ui->lineEdit_zjsgzjbodao->setValidator(new StrictIntValidator(0, 65535, this));

//    ui->lineEdit_fsygonglvkongz->setValidator(new StrictIntValidator(6, 36 , this));

//    ui->lineEdit_fspinlv->setValidator(new StrictIntValidator(0, 2400 , this));

//    ui->lineEdit_malv->setValidator(new StrictIntValidator(0, 20000, this));
//    ui->lineEdit_zhenchang->setValidator(new StrictIntValidator(0, 8192, this));
//    ui->lineEdit_fuzhenlvxu->setValidator(new StrictIntValidator(0, 10000, this));


    //ui->lineEdit_fspinlv->setValidator(new StrictIntValidator(0, 10000, this));
//    ui->lineEdit_tzbinpian->setValidator(new StrictIntValidator(0, 10000, this));
    //ui->lineEdit_fsygonglvkongz->setValidator(new StrictIntValidator(0, 10000, this));

    setWindowTitle(QString("发射机%1下发界面").arg(pattern));


//    if(pattern == 1)
//    {
//      ControlAlignment("ControlAlignment.txt");
//    }
//    else if(pattern == 2)
//    {
//      ControlAlignment("ControlAlignment2.txt");
//    }




    loadSettings();


    settableUI();


    ui->label_73->hide();
    ui->Edit_youxiaobiaozi->hide();

    ui->label_72->hide();
    ui->Edit_TPCtongbuma->hide();

    ui->label_47->hide();
    ui->comboBox_bianmaweizhi->hide();
    ui->label_2->hide();


}

Dialogfasheset::~Dialogfasheset()
{
    saveSettings();


    delete ui;
}

void Dialogfasheset::on_Btn_peiz_clicked()
{

//    if(ui->lineEdit_fsygonglvkongz->text().toInt() < 6)
//    {
//        QMessageBox::information(this , "错误" , "发射源功率控制小于6 , 错误");
//        return;
//    }

    if(ui->lineEdit_fspinlv->text().toDouble() < 2200)
    {
        QMessageBox::information(this , "错误" , "发射频率不在合法工作范围里 , 错误");
        return;
    }

    if(ui->lineEdit_fsygonglvkongz->text().toDouble() > 10 && ui->comboBox_zai1->currentText() == "开")
    {
        QMessageBox::information(this , "提示" , "输出功率较大，请确认天线已连接");
    }



    owner->m_PPACKET_HEADER = new PACKET_HEADER;
   // owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;
   // qDebug() << QString("%1").arg(sizeof(TRANSMIT_CONFIG));

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x01;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);


    owner->m_PTELEMETRY_FRAME = new TELEMETRY_FRAME;
    if(pattern == 1)
    {
          owner->m_PTELEMETRY_FRAME->txSelector = 1;

          owner->fuzhengfangshi = ui->comboBox_fuzhenfanshi->currentText();
          owner->zhengmazu = ui->comboBox_zhenmazhu->currentText();
          owner->malv = ui->lineEdit_malv->text();
          owner->maxing = ui->comboBox_maxing->currentText();
          owner->bianmawz = ui->comboBox_bianmaweizhi->currentText();
          owner->fuzhengchang = ui->lineEdit_fuzhenchangdu->text();
          owner->zhenchang = ui->lineEdit_zhenchang->text();
          owner->tiaozhikaiguan = ui->comboBox_zai1->currentText();


          owner->updateui1();


    }
    else if(pattern == 2)
    {
          owner->m_PTELEMETRY_FRAME->txSelector = 2;

          owner->fuzhengfangshi2 = ui->comboBox_fuzhenfanshi->currentText();
          owner->zhengmazu2 = ui->comboBox_zhenmazhu->currentText();
          owner->malv2 = ui->lineEdit_malv->text();
          owner->maxing2 = ui->comboBox_maxing->currentText();
          owner->bianmawz2 = ui->comboBox_bianmaweizhi->currentText();
          owner->fuzhengchang2 = ui->lineEdit_fuzhenchangdu->text();
          owner->zhenchang2 = ui->lineEdit_zhenchang->text();
          owner->tiaozhikaiguan2 = ui->comboBox_zai1->currentText();
          owner->updateui2();
    }

   //* ui->lineEdit->text().toInt() / 4294967296

   long long int malv = ui->lineEdit_malv->text().toLongLong();
   quint32 byteValue32  = (owner->fo == 0) ? 0 :
                           static_cast<quint32>(
                            ui->lineEdit_malv->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                                        );
   owner->m_PTELEMETRY_FRAME->pcmRate = qToLittleEndian<quint32>(byteValue32);

   quint16 byteValue16;
   quint8 byteValue8;

   byteValue16 = static_cast<quint16>(ui->lineEdit_zhenchang->text().toInt() - 1);
   owner->m_PTELEMETRY_FRAME->subFrameLength.bit.length = qToLittleEndian<quint16>(byteValue16);
   owner->m_PTELEMETRY_FRAME->subFrameLength.bit.moFeiFlag = 0;


   if(ui->comboBox_fuzhenfanshi->currentText() == "无副帧")
   {
       byteValue8 = 0x00;
   }
   else
   {
       byteValue8 = static_cast<quint8>(ui->lineEdit_fuzhenchangdu->text().toInt() - 1);

   }

   byteValue8 = static_cast<quint8>(ui->lineEdit_fuzhenchangdu->text().toInt() - 1); // 0x01
   owner->m_PTELEMETRY_FRAME->subFrameCount = qToLittleEndian<quint16>(byteValue8);

   owner->m_PTELEMETRY_FRAME->WordConfig.bits.wordLengthMinusOne = static_cast<quint8>(ui->comboBox_zichang->currentText().toInt() - 1);
   quint8 codeType;
   if (ui->comboBox_maxing->currentText() == "NRZ-L")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000000;
   }

   else if (ui->comboBox_maxing->currentText() == "NRZ-M")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000010;
   }

   else if (ui->comboBox_maxing->currentText() == "NRZ-S")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000011;
   }
   else if (ui->comboBox_maxing->currentText() == "BIφ-L")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000100;
   }

   else if (ui->comboBox_maxing->currentText() == "BIφ-M")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000110;
   }


   else if (ui->comboBox_maxing->currentText() == "BIφ-S")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000111;
   }

   else if (ui->comboBox_maxing->currentText() == "RNRZ-L")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00001000;

   }




   byteValue16 = ui->lineEdit_fuzhenlvxu->text().toInt() - 1 ; //ID码副帧时, 副帧的ID码所在路序-1。循环码副帧时，副帧特征字在子帧的路序-1
   owner->m_PTELEMETRY_FRAME->featurePosition = qToLittleEndian<quint16>(byteValue16);

   //if(ui->checkBox_low)
   bool convertOk;
   QString processed = ui->comboBox_zhenmazhu->currentText().trimmed().toUpper();
   quint64 byteValue64 = processed.toULongLong(&convertOk , 16);
   owner->m_PTELEMETRY_FRAME->syncCode = qToLittleEndian<quint64>(byteValue64);

   processed = ui->lineEdit_xhfztongbuma->text().trimmed().toUpper();
   byteValue16 = processed.toULongLong(&convertOk , 16);
   owner->m_PTELEMETRY_FRAME->loopSyncCode = qToLittleEndian<quint16>(byteValue16);


    quint8 subframeType ;
    quint8 bitLengthMinusOne;
   if(ui->comboBox_fuzhenfanshi->currentText() == "无副帧")
   {
       subframeType = 0 ;
   }

   else if(ui->comboBox_fuzhenfanshi->currentText() == "反码副帧")

   {
       subframeType = 2 ;
   }

   else if(ui->comboBox_fuzhenfanshi->currentText() == "循环副帧")
   {
       subframeType = 1 ;
   }

   else if(ui->comboBox_fuzhenfanshi->currentText() == "ID副帧")
   {
       subframeType = 3 ;
   }

   bitLengthMinusOne = ui->comboBox_zhenmazhu->currentText().size() * 4 - 1;


   byteValue8 = (subframeType << 6) | bitLengthMinusOne ;

   owner->m_PTELEMETRY_FRAME->frameType = byteValue8;


   for(int i = 0 ; i < 5 ; i++)
   {

       owner->m_PTELEMETRY_FRAME->reserved1[i] = 0x00;
   }

   if( ui->comboBox_xinhaoneixing->currentText() == "台阶码")
   {
       byteValue8 = 0x00;
   }
   else if (ui->comboBox_xinhaoneixing->currentText() == "随机码")
   {
       byteValue8 = 0x01;
   }
   else if (ui->comboBox_xinhaoneixing->currentText() == "用户码")
   {
       byteValue8 = 0x02;
   }

   owner->m_PTELEMETRY_FRAME->dataType = qToLittleEndian<quint8>(byteValue8);


   byteValue16 = ui->lineEdit_tjmbujin->text().toInt();
   owner->m_PTELEMETRY_FRAME->stepValue = qToLittleEndian<quint8>(byteValue16);


   byteValue16 = ui->lineEdit_tjmchushizi->text().toInt();
   owner->m_PTELEMETRY_FRAME->initStep = qToLittleEndian<quint16>(byteValue16);


   if(ui->checkBox_low->isChecked())
   {
       owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 0;
   }
   else
   {
       owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 1;
   }

   if(ui->checkBox_high->isChecked())
   {
       owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 0;
   }
   else
   {
       owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 1;
   }


   byteValue16 = ui->lineEdit_zjsdzjbodao->text().toInt();
   owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;


   byteValue16 = ui->lineEdit_zjsgzjbodao->text().toInt();
   owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;

   for(int i = 0 ; i < 4 ; i++)
   {
       owner->m_PTELEMETRY_FRAME->reserved2[i] = 0x00;
   }

   qDebug() << owner->m_PTELEMETRY_FRAME->FrameCalcChannel.value << owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.frameCountLowByteIndex
            << owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.value << owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.frameCountLowByteIndex;



   if(ui->comboBox_IDzijishufangshi->currentText() == "加计数")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x00;
   }
   else if(ui->comboBox_IDzijishufangshi->currentText() == "减计数")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x01;
   }

   if(ui->comboBox_IDzijizhi->currentText() == "0开始")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x00;
   }
   else if(ui->comboBox_IDzijizhi->currentText() == "1开始")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x01;
   }
  owner->m_PTELEMETRY_FRAME->bits.reserved = 0x00;


  if(ui->comboBox_bianmaweizhi->currentText() == "编码前")
  {
      owner->m_PTELEMETRY_FRAME->codingPosition = 0x01;
  }
  else if(ui->comboBox_bianmaweizhi->currentText() == "编码后")
  {
      owner->m_PTELEMETRY_FRAME->codingPosition = 0x00;
  }


   for(int i = 0 ; i < 22 ; i++)
   {
       owner->m_PTELEMETRY_FRAME->reserved3[i] = 0x00;
   }

   owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_FRAME) + 12;


   QByteArray array;
   array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                  sizeof(PACKET_HEADER));
   array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_FRAME),
                                                sizeof(TELEMETRY_FRAME));//    quint8  txSelector;        // 发射机选择 [1B]

   quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
   m_crc32 = qToLittleEndian<quint32>(m_crc32);
   array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

   int i  = 0 ;
   for (quint8 byte : array) {
                 QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                 qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
             }

   owner->udpManager->sendDatagram(array);
   if(pattern == 1)
   {
      Logger::info("发射机1:配置帧格式下发");
      owner->setmaintable("发射机1:配置帧格式下发" , "上位机");
   }
   else
   {
      Logger::info("发射机2:配置帧格式下发");
      owner->setmaintable(QString("发射机2:配置帧格式下发"), "上位机");
   }

   array.clear();


   owner->m_PPACKET_HEADER = new PACKET_HEADER;
   //owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;

   owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
   owner->m_PPACKET_HEADER->functionCode = 0x03;
   owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
   owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
   owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

   if(pattern == 1)
   {
       owner->m_PTRANSMIT_CONFIG->txSelector = 0x01;
       double texttodub = ui->lineEdit_fspinlv->text().toDouble();
       owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));

       qDebug() << owner->m_PTRANSMIT_CONFIG->freq1;

       //texttoint = ui->lineEdit_tzbinpian->text().toInt();
       int  texttoint = (owner->fo == 0) ? 0 :
                                           static_cast<quint32>(
                                               ui->lineEdit_tzbinpian->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                           );
       owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
       owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
       quint8 tiaozhifangshiint;
       quint8 modPolarity1int;
       quint8 modSwitch1int;
       quint8 carrier1int;
       if(ui->comboBox_tiao1->currentText() == "FM调制")
       {
           tiaozhifangshiint =0b0000;
       }
       else if(ui->comboBox_tiao1->currentText() == "BPSK调制")
       {
           tiaozhifangshiint =0b0001;
       }
       else if(ui->comboBox_tiao1->currentText() == "QPSK调制")
       {
           tiaozhifangshiint =0b0010;
       }

       if(ui->comboBox_zai1->currentText() == "开")
       {
           carrier1int = 1;
       }
       else if(ui->comboBox_zai1->currentText() == "关")
       {
           carrier1int = 0;
       }

       if(ui->comboBox_tiaokai1->currentText() == "开")
       {
           modSwitch1int = 1;
       }
       else if(ui->comboBox_tiaokai1->currentText() == "关")
       {
           modSwitch1int = 0;
       }

       if(ui->comboBox_tiaoji1->currentText() == "正")
       {
           modPolarity1int = 0;
       }
       else if(ui->comboBox_tiaoji1->currentText() == "负")
       {
           modPolarity1int = 1;
       }
       owner->m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
       owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
       owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
       owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
       owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;

       double y = ui->lineEdit_fspinlv->text().toDouble();
       int x = ui->lineEdit_fsygonglvkongz->text().toInt();
       if(x < 6)
       {
          x = 6;
       }

       double result;
       if(pattern == 1)
       {
           QString appDir = QCoreApplication::applicationDirPath();
           qDebug() << "Application file path:" << appDir;
           if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
              owner->dataquery.printDataRange();

               result = owner->dataquery.interpolate(y*1000, x);
               qDebug() << "插值结果:" << result;}
       }
       else
       {
           QString appDir = QCoreApplication::applicationDirPath();
           qDebug() << "Application file path:" << appDir;
           if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
               owner->dataquery.printDataRange();

               result = owner->dataquery.interpolate(y*1000, x);
               qDebug() << "插值结果:" << result;}
       }



       owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
       owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_fsygonglvkongz->text().toInt()));

       qDebug() << "插值结果:" << result;

       for(int i= 0 ; i < 50 ; i++)
       {
           owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
       }


       owner->pingdian = ui->lineEdit_fspinlv->text();
       owner->pinpian = ui->lineEdit_tzbinpian->text();
       owner->tiaoz = ui->comboBox_tiao1->currentText();
       owner->gonglv = ui->lineEdit_fsygonglvkongz->text();
       owner->updateui1();

   }
   else if(pattern == 2)
   {
       owner->m_PTRANSMIT_CONFIG->txSelector = 0x02;
       double texttodub = ui->lineEdit_fspinlv->text().toDouble();
       owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));


       //texttoint = ui->lineEdit_tzbinpian->text().toInt();
       int  texttoint = (owner->fo == 0) ? 0 :
                                           static_cast<quint32>(
                                               ui->lineEdit_tzbinpian->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                           );
       owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));

       owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
       quint8 tiaozhifangshiint;
       quint8 modPolarity1int;
       quint8 modSwitch1int;
       quint8 carrier1int;
       if(ui->comboBox_tiao1->currentText() == "FM调制")
       {
           tiaozhifangshiint =0b0000;
       }
       else if(ui->comboBox_tiao1->currentText() == "BPSK调制")
       {
           tiaozhifangshiint =0b0001;
       }
       else if(ui->comboBox_tiao1->currentText() == "QPSK调制")
       {
           tiaozhifangshiint =0b0010;
       }

       if(ui->comboBox_zai1->currentText() == "开")
       {
           carrier1int = 1;
       }
       else if(ui->comboBox_zai1->currentText() == "关")
       {
           carrier1int = 0;
       }

       if(ui->comboBox_tiaokai1->currentText() == "开")
       {
           modSwitch1int = 1;
       }
       else if(ui->comboBox_tiaokai1->currentText() == "关")
       {
           modSwitch1int = 0;
       }

       if(ui->comboBox_tiaoji1->currentText() == "正")
       {
           modPolarity1int = 0;
       }
       else if(ui->comboBox_tiaoji1->currentText() == "负")
       {
           modPolarity1int = 1;
       }
       owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
       owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1 = modSwitch1int;
       owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
       owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;

       double y = ui->lineEdit_fspinlv->text().toDouble();
       int x = ui->lineEdit_fsygonglvkongz->text().toInt();
       if(x < 6)
       {
          x = 6;
       }

       double result;
       if(pattern == 1)
       {   QString appDir = QCoreApplication::applicationDirPath();
           if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
              owner->dataquery.printDataRange();

               result = owner->dataquery.interpolate(y*1000, x);
               qDebug() << "插值结果:" << result;}
       }
       else
       {
           QString appDir = QCoreApplication::applicationDirPath();
           if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
               owner->dataquery.printDataRange();

               result = owner->dataquery.interpolate(y*1000, x);
               qDebug() << "插值结果:" << result;}
       }



       owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
       owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_fsygonglvkongz->text().toInt()));



       owner->pingdian2 = ui->lineEdit_fspinlv->text();
       owner->pinpian2 = ui->lineEdit_tzbinpian->text();
       owner->tiaoz2 = ui->comboBox_tiao1->currentText();
       owner->gonglv2 = ui->lineEdit_fsygonglvkongz->text();
       owner->updateui2();


   }

   for(int i  = 0 ; i < 50 ; i++)
   {
       owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
   }


   qDebug() << owner->m_PTRANSMIT_CONFIG->freq1
            << owner->m_PTRANSMIT_CONFIG->detF1
            << owner->m_PTRANSMIT_CONFIG->ctrl1
            << owner->m_PTRANSMIT_CONFIG->powerCtrl1;

   owner->m_PPACKET_HEADER->dataLength = sizeof(TRANSMIT_CONFIG) + 12;


   array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                sizeof(PACKET_HEADER));
   array.append(reinterpret_cast<const char*>(owner->m_PTRANSMIT_CONFIG),
                                              sizeof(TRANSMIT_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

   m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
   m_crc32 = qToLittleEndian<quint32>(m_crc32);
   array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


   i  = 0 ;
   for (quint8 byte : array) {
                 QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                 qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
             }


   owner->udpManager->sendDatagram(array);
   if(pattern == 1)
   {
      Logger::info("发射机1:配置射频参数下发");
      owner->setmaintable("发射机1:配置射频参数下发", "上位机");
   }
   else
   {
      Logger::info("发射机2:配置射频参数下发");
      owner->setmaintable("发射机2:配置射频参数下发", "上位机");
   }
   array.clear();

   owner->m_PTELEMETRY_ENCODING_CONFIG = new TELEMETRY_ENCODING_CONFIG;
   owner->m_PPACKET_HEADER = new PACKET_HEADER;

   owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
   owner->m_PPACKET_HEADER->functionCode = 0x05;
   owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
   owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
   owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

   if(pattern == 1)
   {
       owner->m_PTELEMETRY_ENCODING_CONFIG->txSelector = 0x01;
   }
   else if(pattern == 2)
   {
       owner->m_PTELEMETRY_ENCODING_CONFIG->txSelector = 0x02;
   }


   if(ui->comboBox_bianma->currentText() == "LDPC")
   {
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 1;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
   }
   else if(ui->comboBox_bianma->currentText() == "TPC")
   {
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 1;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
   }
   else if(ui->comboBox_bianma->currentText() == "RS")
   {
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 1;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
   }
   else if(ui->comboBox_bianma->currentText() == "卷积")
   {
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 1;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
       owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
   }
   else if(ui->comboBox_bianma->currentText() == "关闭")
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

   //bool convertOk;
   //QString processed;

   //quint64 byteValue64;


   if(ui->Edit_TPCtongbuma->text().isEmpty())
   {
       Btyevalue32 = 0x1ACFFC1D;
   }
   else
   {
       processed = ui->Edit_TPCtongbuma->text().trimmed().toUpper();
       Btyevalue32 = processed.toULongLong(&convertOk , 16);

   }

   if(ui->Edit_youxiaobiaozi->text().isEmpty())
   {
       Btyevalue16 = 0xFFFF;
   }
   else
   {

       processed = ui->Edit_youxiaobiaozi->text().trimmed().toUpper();
       Btyevalue16 = processed.toULongLong(&convertOk , 16);
   }


    owner->m_PTELEMETRY_ENCODING_CONFIG->tpcSyncCode =  qToLittleEndian<quint32>(static_cast<quint32>(Btyevalue32));
    owner->m_PTELEMETRY_ENCODING_CONFIG->tpcValidFlag=  qToLittleEndian<quint16>(static_cast<quint16>(Btyevalue16));


    for(int i = 0 ;  i < 53 ; i++)
    {
        owner->m_PTELEMETRY_ENCODING_CONFIG->padding[i] = 0x00;
    }

    owner->m_PPACKET_HEADER->dataLength = sizeof(TELEMETRY_ENCODING_CONFIG) + 12;


    //QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_ENCODING_CONFIG),
                                                             sizeof(TELEMETRY_ENCODING_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

    m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


    i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }

    owner->udpManager->sendDatagram(array);
    if(pattern == 1)
    {
       Logger::info("发射机1:配置信道编码下发");
       owner->setmaintable("发射机1:配置信道编码下发","上位机");
    }
    else
    {
        Logger::info("发射机2:配置信道编码下发");
        owner->setmaintable("发射机2:配置信道编码下发","上位机");
    }

    fasheping(pattern);

}






void Dialogfasheset::on_Btn_readpeiz_clicked()
{
    owner->m_PREAD_FRAMEFORMAT = new READ_FRAMEFORMAT;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x02;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_FRAMEFORMAT->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_FRAMEFORMAT->fashe = 0x02;
    }

    QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_FRAMEFORMAT),
                                                 sizeof(READ_FRAMEFORMAT));
    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);

    array.clear();

    if(pattern == 1)
    {
       Logger::info("发射机1:读取帧格式下发");
       owner->setmaintable("发射机1:读取帧格式下发","上位机");
    }
    else
    {
        Logger::info("发射机2:读取帧格式下发");
        owner->setmaintable("发射机2:读取帧格式下发","上位机");
    }


//    int i  = 1 ;
//    for (quint8 byte : array) {
//                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
//                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
//              }


    owner->m_PREAD_yaocFRAMEFORMAT = new READ_yaocFRAMEFORMAT;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x04;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_yaocFRAMEFORMAT->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_yaocFRAMEFORMAT->fashe = 0x02;


    }



    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_yaocFRAMEFORMAT),
                                                  sizeof(READ_yaocFRAMEFORMAT));

    m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);

    array.clear();

    if(pattern == 1)
    {
       Logger::info("发射机1:读取射频参数下发");
       owner->setmaintable("发射机1:读取射频参数下发","上位机");
    }
    else
    {
       Logger::info("发射机2:读取射频参数下发");
       owner->setmaintable("发射机2:读取射频参数下发","上位机");
    }


    int i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    owner->m_PREAD_ENCODING_CONFIG = new READ_ENCODING_CONFIG;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x06;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_ENCODING_CONFIG->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_ENCODING_CONFIG->fashe = 0x02;


    }



    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_ENCODING_CONFIG),
                                                  sizeof(READ_ENCODING_CONFIG));

    m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);
    if(pattern == 1)
    {
       Logger::info("发射机1:读取信道编码下发");
       owner->setmaintable("发射机1:读取信道编码下发","上位机");
    }
    else
    {
       Logger::info("发射机2:读取信道编码下发");
       owner->setmaintable("发射机2:读取信道编码下发","上位机");
    }

    i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


}

void Dialogfasheset::on_Btn_readpeiz_2_clicked()
{
    owner->m_PREAD_yaocFRAMEFORMAT = new READ_yaocFRAMEFORMAT;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x04;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_yaocFRAMEFORMAT->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_yaocFRAMEFORMAT->fashe = 0x02;


    }


    QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_yaocFRAMEFORMAT),
                                                  sizeof(READ_yaocFRAMEFORMAT));

    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);

    if(pattern == 1)
    {
       Logger::info("发射机1:读取射频参数下发");
       owner->setmaintable("发射机1:读取射频参数下发","上位机");
    }
    else
    {
       Logger::info("发射机2:读取射频参数下发");
       owner->setmaintable("发射机2:读取射频参数下发","上位机");
    }


    int i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    owner->m_PREAD_ENCODING_CONFIG = new READ_ENCODING_CONFIG;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x06;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_ENCODING_CONFIG->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_ENCODING_CONFIG->fashe = 0x02;


    }



    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_ENCODING_CONFIG),
                                                  sizeof(READ_ENCODING_CONFIG));

    m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);
    if(pattern == 1)
    {
       Logger::info("发射机1:读取信道编码下发");
       owner->setmaintable("发射机1:读取信道编码下发","上位机");
    }
    else
    {
       Logger::info("发射机2:读取信道编码下发");
       owner->setmaintable("发射机2:读取信道编码下发","上位机");
    }

    i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }
}

void Dialogfasheset::on_Btn_readpeiz_3_clicked()
{
    owner->m_PREAD_ENCODING_CONFIG = new READ_ENCODING_CONFIG;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x06;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_ENCODING_CONFIG->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_ENCODING_CONFIG->fashe = 0x02;


    }


    QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_ENCODING_CONFIG),
                                                  sizeof(READ_ENCODING_CONFIG));

    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);
    if(pattern == 1)
    {
       Logger::info("发射机1:读取信道编码下发");
       owner->setmaintable("发射机1:读取信道编码下发","上位机");
    }
    else
    {
       Logger::info("发射机2:读取信道编码下发");
       owner->setmaintable("发射机2:读取信道编码下发","上位机");
    }

    int i  = 1 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }
}

void Dialogfasheset::on_Btn_readpcmpeiz_clicked()
{
    owner->m_PREAD_PCM_CONFIG = new READ_PCM_CONFIG;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x02;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_PCM_CONFIG->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_PCM_CONFIG->fashe = 0x02;


    }


    QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_PCM_CONFIG),
                                                  sizeof(READ_PCM_CONFIG));

    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);

    int i  = 1 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    if(pattern == 1)
    {
       Logger::info("发射机1:配置信道编码下发");
       owner->setmaintable("发射机1:配置信道编码下发","上位机");
    }
    else
    {
       Logger::info("发射机2:配置信道编码下发");
       owner->setmaintable("发射机2:配置信道编码下发","上位机");
    }
}

void Dialogfasheset::on_lineEdit_zhenchang_textChanged(const QString &arg1)
{
    int col = arg1.toInt();

    //ui->tableWidget->setColumnCount(col);
}

void Dialogfasheset::on_lineEdit_fuzhenchangdu_textChanged(const QString &arg1)
{
    int row = arg1.toInt();

    //ui->tableWidget->setRowCount(row);
}


void Dialogfasheset::on_Btn_pcmpeiz_clicked()
{

    owner->m_PPCMEMBEDCONfIG = new PCMEMBEDCONfIG;

    bool  yibuyuansetd = false;
    bool  GNSSsetd = false;
    bool  ankongsetd = false;
    quint8 num = 0;




//  for(int i = 0 ; i < ui->tableWidget->rowCount() ; i++)
//  {
//      for(int j = 0 ; j < ui->tableWidget->columnCount() ; j++)
//      {
//        if(ui->tableWidget->item(i , j))
//        {
//          if(ui->tableWidget->item(i , j)->text() == "异步源" && yibuyuansetd == false)
//          {
//              owner->m_PPCMEMBEDCONfIG->entries[0].ctrlBits.mode = 0;
//              owner->m_PPCMEMBEDCONfIG->entries[0].ctrlBits.reserved = 0;
//              owner->m_PPCMEMBEDCONfIG->entries[0].subFramePos = 0;
//              owner->m_PPCMEMBEDCONfIG->entries[0].childFramePos = qToLittleEndian<quint16>(j);
//              owner->m_PPCMEMBEDCONfIG->entries[0].dataSource = 1;
//              owner->m_PPCMEMBEDCONfIG->entries[0].entryReserved = 0;

//              owner->m_PPCMEMBEDCONfIG->entries[0].dataLength = ui->tableWidget->yibuyuancol;

//              yibuyuansetd = true;
//              num++;
//          }
//          else if(ui->tableWidget->item(i , j)->text() == "GNSS" && GNSSsetd == false)
//          {
//              owner->m_PPCMEMBEDCONfIG->entries[1].ctrlBits.mode = 1;
//              owner->m_PPCMEMBEDCONfIG->entries[1].subFramePos = 0;
//              owner->m_PPCMEMBEDCONfIG->entries[1].childFramePos = qToLittleEndian<quint16>(j);
//              owner->m_PPCMEMBEDCONfIG->entries[1].dataSource = 2;
//              owner->m_PPCMEMBEDCONfIG->entries[1].dataLength = 0;

//              GNSSsetd = true;
//              num++;
//          }
//          else if(ui->tableWidget->item(i , j)->text() == "安控" && ankongsetd == false)
//          {
//              owner->m_PPCMEMBEDCONfIG->entries[2].ctrlBits.mode = 1;
//              owner->m_PPCMEMBEDCONfIG->entries[2].subFramePos = 0;
//              owner->m_PPCMEMBEDCONfIG->entries[2].childFramePos = qToLittleEndian<quint16>(j);
//              owner->m_PPCMEMBEDCONfIG->entries[2].dataSource = 3;
//              owner->m_PPCMEMBEDCONfIG->entries[2].dataLength = 0;

//              ankongsetd = true;
//              num++;
//          }
//        }
//      }

      owner->m_PPACKET_HEADER = new PACKET_HEADER;
      owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
      owner->m_PPACKET_HEADER->functionCode = 0x07;
      owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
      owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
      owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
      if(pattern == 1)
      {
          owner->m_PPCMEMBEDCONfIG->txSelector = 1;
      }
      else if(pattern == 2)
      {
          owner->m_PPCMEMBEDCONfIG->txSelector = 2;
      }

       owner->m_PPCMEMBEDCONfIG->entryCount = num;

  }

  QSettings settings("settings.ini", QSettings::IniFormat);

  //settings.setValue("entryCount" , owner->m_PPCMEMBEDCONfIG->entryCount);

//  for(int i = 0 ; i < 10 ; i++)
//  {
//      settings.setValue(QString("entries%1_ctrlBits_mode").arg(i) , owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode);
//      settings.setValue(QString("entries%1_subFramePos").arg(i) , owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos);
//      settings.setValue(QString("entries%1_childFramePos").arg(i) , owner->m_PPCMEMBEDCONfIG->entries[i].childFramePos);
//      settings.setValue(QString("entries%1_dataSource").arg(i) , owner->m_PPCMEMBEDCONfIG->entries[i].dataSource);
//      settings.setValue(QString("entries%1_dataLength").arg(i) , owner->m_PPCMEMBEDCONfIG->entries[i].dataLength);
//  }






  //QByteArray array;
  //array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
  //             sizeof(PACKET_HEADER));
  //array.append(reinterpret_cast<const char*>(owner->m_PPCMEMBEDCONfIG),
  //                                              sizeof(PCMEMBEDCONfIG));

//  quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
//  m_crc32 = qToLittleEndian<quint32>(m_crc32);
//  array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));



//  int i2  = 0 ;
//  for (quint8 byte : array) {
//                QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
//                qDebug() << QString("%1").arg(i2++) << " " << hexStr.toUpper(); // 转为大写
//            }





//   owner->udpManager->sendDatagram(array);
//   if(pattern == 1)
//   {
//      Logger::debug("发射机1:配置pcm参数下发");
//      owner->setmaintable("发射机1:配置pcm参数下发","上位机");
//   }
//   else
//   {
//      Logger::debug("发射机2:配置pcm参数下发");
//      owner->setmaintable("发射机2:配置pcm参数下发","上位机");
//   }


//}

void Dialogfasheset::onRES_FRAMEFORMAT(int fasheji)
{
      // 1. 获取值并转换为64位类型
      qint64 pcmRate_val = static_cast<qint64>(owner->m_PREAD_FRAMEFORMAT_RES->pcmRate);
      qint64 fo_val = static_cast<qint64>(owner->fo);

      qint64 value1 = pcmRate_val * fo_val; // 64位计算

      // 2. 除以1000（带四舍五入）
      qint64 value2 = (value1 + (value1 > 0 ? 500 : -500)) / 1000;

      // 3. 除以4294967296（带四舍五入）并保留3位小数
      constexpr qint64 divisor = 4294967296LL;
      constexpr qint64 scaleFactor = 1000; // 用于保留3位小数

      // 放大1000倍后执行除法（确保中间计算在64位范围内）
      qint64 scaledValue = value2 * scaleFactor;
      qint64 pcmmate = scaledValue / divisor;

      // 处理余数进行四舍五入
      qint64 remainder = scaledValue % divisor;
      if (remainder != 0) {
          // 计算余数的绝对值（处理负数情况）
          qint64 absRemainder = std::abs(remainder);
          qint64 halfDivisor = divisor / 2;

          // 四舍五入规则
          if (absRemainder > halfDivisor ||
              (absRemainder == halfDivisor && (pcmmate % 2 != 0))) {
              pcmmate += (remainder > 0 ? 1 : -1);
          }
      }

      double finalValue = static_cast<double>(pcmmate) / 1000.0;

      // 4. 设置UI
      ui->lineEdit_malv->setText(QString::number(finalValue , 'f' , 3));
    ui->lineEdit_zhenchang->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->subFrameLength.rawValue + 1));
    ui->lineEdit_fuzhenchangdu->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->subFrameCount + 1));
    qDebug() << owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.wordLengthMinusOne
             << owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType;
    ui->comboBox_zichang->setCurrentText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.wordLengthMinusOne+ 1));
    if(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType == 0b00000000)
    {
        ui->comboBox_maxing->setCurrentText(QString("NRZ-L"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType == 0b00000010)
    {
        ui->comboBox_maxing->setCurrentText(QString("WRZ-M"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType == 0b00000011)
    {
        ui->comboBox_maxing->setCurrentText(QString("NRZ-S"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType == 0b00000100)
    {
        ui->comboBox_maxing->setCurrentText(QString("BIφ-L"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType == 0b00000110)
    {
        ui->comboBox_maxing->setCurrentText(QString("BIφ-M"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType == 0b00000111)
    {
        ui->comboBox_maxing->setCurrentText(QString("BIφ-S"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->WordConfig.bits.codeType == 0b00001000)
    {
        ui->comboBox_maxing->setCurrentText(QString("RNRZ-L"));
    }


    if(owner->m_PREAD_FRAMEFORMAT_RES->dataType == 0x00)
    {
        ui->comboBox_xinhaoneixing->setCurrentText(QString("台阶码"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->dataType == 0x01)
    {
        ui->comboBox_xinhaoneixing->setCurrentText(QString("随机码"));
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->dataType == 0x02)
    {
        ui->comboBox_xinhaoneixing->setCurrentText(QString("用户码"));
    }
     
    QString hexStr = QString("%1").arg(owner->m_PREAD_FRAMEFORMAT_RES->loopSyncCode, 4, 16, QChar('0')).toUpper();
    ui->lineEdit_xhfztongbuma->setText(hexStr);

    int size = sizeof(owner->m_PREAD_FRAMEFORMAT_RES->syncCode);
//    int hexDigits = size; // 每个字节两位

    // 转换
    quint64 value = static_cast<quint64>(owner->m_PREAD_FRAMEFORMAT_RES->syncCode);
    hexStr = QString("%1").arg(value, 0, 16).toUpper();

    ui->comboBox_zhenmazhu->setCurrentText(hexStr);
    
    //ui->comboBox_fuzhenfanshi->setCurrentText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->frameType));

    qDebug() << owner->m_PREAD_FRAMEFORMAT_RES->frameType
             << (owner->m_PREAD_FRAMEFORMAT_RES->frameType >> 6);
    quint8 highBits = (owner->m_PREAD_FRAMEFORMAT_RES->frameType >> 6);

    if(highBits == 0)
    {
        ui->comboBox_fuzhenfanshi->setCurrentText(QString("无副帧"));
    }
    else if(highBits == 1)
    {
        ui->comboBox_fuzhenfanshi->setCurrentText(QString("循环副帧"));
    }
    else if(highBits == 2)
    {
        ui->comboBox_fuzhenfanshi->setCurrentText(QString("反码副帧"));
    }
    else if(highBits == 3)
    {
        ui->comboBox_fuzhenfanshi->setCurrentText(QString("ID副帧"));
    }


    //ui->comboBox_xinhaoneixing->setCurrentText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->dataType));
    
    ui->lineEdit_tjmbujin->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->stepValue));
    ui->lineEdit_tjmchushizi->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->initStep));
    ui->lineEdit_zjsdzjbodao->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->FrameCalcChannel.bits.frameCountLowByteIndex + 1));
    ui->lineEdit_zjsgzjbodao->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->frameCalcChannelhigh.bits.frameCountLowByteIndex + 1));

    if(owner->m_PREAD_FRAMEFORMAT_RES->frameCalcChannelhigh.bits.notCountEnable == 0)
    {
        ui->checkBox_high->setChecked(true);
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->frameCalcChannelhigh.bits.notCountEnable == 1)
    {
        ui->checkBox_high->setChecked(false);
    }

    if(owner->m_PREAD_FRAMEFORMAT_RES->FrameCalcChannel.bits.notCountEnable == 0)
    {
        ui->checkBox_low->setChecked(true);
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->FrameCalcChannel.bits.notCountEnable == 1)
    {
        ui->checkBox_low->setChecked(false);
    }

    ui->lineEdit_fuzhenlvxu->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->featurePosition + 1));



    //ui->lineEdit_IDmafztz->setText(QString::number(owner->m_PREAD_FRAMEFORMAT_RES->bits.bit0));
    if(owner->m_PREAD_FRAMEFORMAT_RES->idtreatrue.bits.bit0 == 0x00)
    {
        ui->comboBox_IDzijizhi->setCurrentText("0开始");
    }
    else
    {
        ui->comboBox_IDzijizhi->setCurrentText("1开始");
    }

    if(owner->m_PREAD_FRAMEFORMAT_RES->idtreatrue.bits.bit1 == 0x00)
    {
        ui->comboBox_IDzijishufangshi->setCurrentText("加计数");
    }
    else
    {
        ui->comboBox_IDzijishufangshi->setCurrentText("减计数");
    }

    if(owner->m_PREAD_FRAMEFORMAT_RES->codingPosition == 0x00)
    {
        ui->comboBox_bianmaweizhi->setCurrentText("编码后");
    }
    else if(owner->m_PREAD_FRAMEFORMAT_RES->codingPosition == 0x01)
    {
        ui->comboBox_bianmaweizhi->setCurrentText("编码前");
    }


    if(fasheji == 1)
    {
        owner->setmaintable("读取帧格式成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        owner->setmaintable("读取帧格式成功" , "发射机2");
    }

    owner->notifyManager.notify("信息", "阅读帧格式下发回传:下传成功" , "qrc:/qrc/5.png", "");

}

void Dialogfasheset::onRES_yaocFRAMEFORMAT(int fasheji)
{
    //ui->lineEdit_fspinlv->setText(QString::number(owner->m_PREAD_yaocFRAMEFORMAT_RES->freq1 / 1000));

    qint64 freq1_val = static_cast<qint64>(owner->m_PREAD_yaocFRAMEFORMAT_RES->freq1);
    qint64 detF1_val = static_cast<qint64>(owner->m_PREAD_yaocFRAMEFORMAT_RES->detF1);
    qint64 fo_val = static_cast<qint64>(owner->fo);

    double freq_kHz = static_cast<double>(freq1_val) / 1000.000;
    qDebug() << freq_kHz;
    ui->lineEdit_fspinlv->setText(QString::number(freq_kHz, 'f' ,3)); // 保留3位小数

    qint64 value1 = detF1_val * fo_val; // 64位计算

    // 2. 除以1000（带四舍五入）
    qint64 value2 = (value1 + (value1 > 0 ? 500 : -500)) / 1000;

    // 3. 除以4294967296（带四舍五入）并保留3位小数
    constexpr qint64 divisor = 4294967296LL;
    constexpr qint64 scaleFactor = 1000; // 用于保留3位小数

    // 放大1000倍后执行除法（确保中间计算在64位范围内）
    qint64 scaledValue = value2 * scaleFactor;
    qint64 tzbinpian = scaledValue / divisor;

    // 处理余数进行四舍五入
    qint64 remainder = scaledValue % divisor;
    if (remainder != 0) {
        // 计算余数的绝对值（处理负数情况）
        qint64 absRemainder = std::abs(remainder);
        qint64 halfDivisor = divisor / 2;

        // 四舍五入规则
        if (absRemainder > halfDivisor ||
            (absRemainder == halfDivisor && (tzbinpian % 2 != 0))) {
            tzbinpian += (remainder > 0 ? 1 : -1);
        }
    }

    double finalValue = static_cast<double>(tzbinpian) / 1000.0;

    ui->lineEdit_fsygonglvkongz->setText(QString::number(owner->m_PREAD_yaocFRAMEFORMAT_RES->powerCtrl1_UI));

    // 4. 显示结果
    ui->lineEdit_tzbinpian->setText(QString::number(finalValue, 'f' ,3));

    if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.modType1 == 0b0000)
    {
        ui->comboBox_tiao1->setCurrentText(QString("FM调制"));
    }
    else if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.modType1 == 0b0001)
    {
        ui->comboBox_tiao1->setCurrentText(QString("BPSK调制"));
    }
    else if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.modType1 == 0b0010)
    {
        ui->comboBox_tiao1->setCurrentText(QString("QPSK调制制"));
    }
    
    if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.carrier1 == 0)
    {
        ui->comboBox_zai1->setCurrentText(QString("关"));
    }
    
    else if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.carrier1 == 1)
    {
        ui->comboBox_zai1->setCurrentText(QString("开"));
    }
    
    if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.modSwitch1 == 0)
    {
        ui->comboBox_tiaokai1->setCurrentText(QString("关"));
    }
    
    else if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.modSwitch1 == 1)
    {
        ui->comboBox_tiaokai1->setCurrentText(QString("开"));
    }
    
    if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.modPolarity1 == 0)
    {
        ui->comboBox_tiaoji1->setCurrentText(QString("正"));
    }
    
    else if(owner->m_PREAD_yaocFRAMEFORMAT_RES->bits1.modPolarity1 == 1)
    {
        ui->comboBox_tiaoji1->setCurrentText(QString("负"));
    }

    if(fasheji == 1)
    {
        owner->setmaintable("读取遥测参数成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        owner->setmaintable("读取遥测参数成功" , "发射机2");
    }


    owner->notifyManager.notify("信息", "阅读遥测参数下发回传:下传成功" , "qrc:/qrc/5.png", "");

    
}

void Dialogfasheset::onRES_ENCODING_CONFIG(int fasheji)
{  

    if(owner->m_PREAD_ENCODING_CONFIG_RES->codeBits.ldpcEnable == 1)
    {
        ui->comboBox_bianma->setCurrentText("LDPC");
    }
    else if(owner->m_PREAD_ENCODING_CONFIG_RES->codeBits.tpcEnable == 1)
    {
        ui->comboBox_bianma->setCurrentText("TPC");
    }
    else if(owner->m_PREAD_ENCODING_CONFIG_RES->codeBits.rsEnable == 1)
    {
        ui->comboBox_bianma->setCurrentText("RS");
    }
    else if(owner->m_PREAD_ENCODING_CONFIG_RES->codeBits.convEnable == 1)
    {
        ui->comboBox_bianma->setCurrentText("卷积");
    }
    else if(owner->m_PREAD_ENCODING_CONFIG_RES->codeSwitch == 0)
    {
        ui->comboBox_bianma->setCurrentText("关闭");
    }

    quint32 syncCode = owner->m_PREAD_ENCODING_CONFIG_RES->tpcSyncCode;
    ui->Edit_TPCtongbuma->setText(QString("%1").arg(syncCode, 8, 16, QLatin1Char('0')).toUpper());
    quint16 validFlag  = owner->m_PREAD_ENCODING_CONFIG_RES->tpcValidFlag;
    ui->Edit_youxiaobiaozi->setText(QString("%1").arg(validFlag, 4, 16, QLatin1Char('0')).toUpper());

    if(fasheji == 1)
    {
        owner->setmaintable("读取信道编码成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        owner->setmaintable("读取信道编码成功" , "发射机2");
    }

    owner->notifyManager.notify("信息", "阅读信道编码下发回传:下传成功" , "qrc:/qrc/5.png", "");
    
}

void Dialogfasheset::onRES_PCM_CONFIG(int fasheji)
{
    ui->tableWidget_pcm->setRowCount(owner->m_PREAD_PCM_CONFIG_RES->entryCount);

    anysum = owner->m_PREAD_PCM_CONFIG_RES->entryCount;

    for (int i = 0; i < anysum; i++) {
        // 遍历每一列（这里假设有9列，从0到8）
        for (int col = 0; col <= 5; col++) {
            // 检查单元格是否已经存在，如果不存在则创建
            if (!ui->tableWidget_pcm->item(i, col)) {
                QTableWidgetItem *item = new QTableWidgetItem();
                ui->tableWidget_pcm->setItem(i, col, item);
            }
        }
    }

   for(int i = 0 ; i < anysum ; i++)
   {
       ui->tableWidget_pcm->item(i , 0)->setText("数据块");

       if(owner->m_PREAD_PCM_CONFIG_RES->entries[i].ctrlBits.mode == 0)
       {
          ui->tableWidget_pcm->item(i , 1)->setText("子帧模式");
       }
       else if(owner->m_PREAD_PCM_CONFIG_RES->entries[i].ctrlBits.mode == 1)
       {
          ui->tableWidget_pcm->item(i , 1)->setText("副帧模式");
       }

       ui->tableWidget_pcm->item(i , 2)->setText(QString::number(owner->m_PREAD_PCM_CONFIG_RES->entries[i].subFramePos + 1));
       ui->tableWidget_pcm->item(i , 3)->setText(QString::number(owner->m_PREAD_PCM_CONFIG_RES->entries[i].childFramePos + 1));

       if(owner->m_PREAD_PCM_CONFIG_RES->entries[i].dataSource == 0x01)
       {
           ui->tableWidget_pcm->item(i , 4)->setText("异步源");
       }
       else if(owner->m_PREAD_PCM_CONFIG_RES->entries[i].dataSource == 0x02)
       {
           ui->tableWidget_pcm->item(i , 4)->setText("GNSS");
       }
       else if(owner->m_PREAD_PCM_CONFIG_RES->entries[i].dataSource == 0x03)
       {
           ui->tableWidget_pcm->item(i , 4)->setText("安控");
       }

       ui->tableWidget_pcm->item(i , 5)->setText(QString::number(owner->m_PREAD_PCM_CONFIG_RES->entries[i].dataLength));

   }

   if(fasheji == 1)
   {
       owner->setmaintable("读取pcm成功" , "发射机1");
   }
   else if(fasheji == 2)
   {
       owner->setmaintable("读取pcm成功" , "发射机2");
   }
   owner->notifyManager.notify("信息", "阅读pcm下发回传:下传成功" , "qrc:/qrc/5.png", "");
}

void Dialogfasheset::onRES_ASY_CONFIG(int fasheji)
{


       asynum = owner->m_PREAD_ASY_CONFIG_RES->entryCount;
       ui->tableWidget_yibuyuan->setRowCount(asynum);

       for (int i = 0; i < asynum; i++) {
           // 遍历每一列（这里假设有9列，从0到8）
           for (int col = 0; col <= 8; col++) {
               // 检查单元格是否已经存在，如果不存在则创建
               if (!ui->tableWidget_yibuyuan->item(i, col)) {
                   QTableWidgetItem *item = new QTableWidgetItem();
                   ui->tableWidget_yibuyuan->setItem(i, col, item);
               }
           }
       }



        for(int i =0 ; i < asynum ; i++)
        {
            ui->tableWidget_yibuyuan->item(i , 0)->setText("异步源1");

            qDebug() << owner->m_PREAD_ASY_CONFIG_RES->entries[i].syncCode;

            QString hexStr = QString("%1").arg(owner->m_PREAD_ASY_CONFIG_RES->entries[i].syncCode, 4, 16, QChar('0')).toUpper();

            ui->tableWidget_yibuyuan->item(i , 1)->setText(hexStr);

            ui->tableWidget_yibuyuan->item(i , 2)->setText(QString::number(owner->m_PREAD_ASY_CONFIG_RES->entries[i].frameLength + 1));



            ui->tableWidget_yibuyuan->item(i , 3)->setText(QString::number(owner->m_PREAD_ASY_CONFIG_RES->entries[i].Securitycontrolposition + 1));

            if(owner->m_PREAD_ASY_CONFIG_RES->entries[i].dataType == 0x00)
            {
                ui->tableWidget_yibuyuan->item(i , 4)->setText("台阶码") ;
            }
            else if(owner->m_PREAD_ASY_CONFIG_RES->entries[i].dataType == 0x01)
            {
                  ui->tableWidget_yibuyuan->item(i , 4)->setText("随机码");
            }
            else if(owner->m_PREAD_ASY_CONFIG_RES->entries[i].dataType == 0x02)
            {
                  ui->tableWidget_yibuyuan->item(i , 4)->setText("用户码");
            }

            ui->tableWidget_yibuyuan->item(i , 5)->setText(QString::number(owner->m_PREAD_ASY_CONFIG_RES->entries[i].stepIncrement));
            ui->tableWidget_yibuyuan->item(i , 6)->setText(QString::number(owner->m_PREAD_ASY_CONFIG_RES->entries[i].initialValue));
            ui->tableWidget_yibuyuan->item(i , 7)->setText(QString::number(owner->m_PREAD_ASY_CONFIG_RES->entries[i].frameCounterLength + 1));
            ui->tableWidget_yibuyuan->item(i , 8)->setText(QString::number(owner->m_PREAD_ASY_CONFIG_RES->entries[i].zhenlv));

    }



    if(fasheji == 1)
    {
        owner->setmaintable("读取异步源成功" , "发射机1");
    }
    else if(fasheji == 2)
    {
        owner->setmaintable("读取异步源成功" , "发射机2");
    }

    owner->notifyManager.notify("信息", "阅读异步源下发回传:下传成功" , "qrc:/qrc/5.png", "");
}



void Dialogfasheset::saveSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    if(pattern == 1)
    {   zichang = ui->comboBox_zichang->currentText();
        xhfztongbuma = ui->lineEdit_xhfztongbuma->text();
        tjmbujin = ui->lineEdit_tjmbujin->text();
        tjmchushizi = ui->lineEdit_tjmchushizi->text();
        zjsdzjbodao = ui->lineEdit_zjsdzjbodao->text();
        zjsgzjbodao = ui->lineEdit_zjsgzjbodao->text();
        //IDmafztz = ui->lineEdit_IDmafztz->text();
        Bianmaweizhi = ui->comboBox_bianmaweizhi->currentText();
        //Bianma = ui->comboBox_bianma->currentText();
        Malv = ui->lineEdit_malv->text();
        maxing = ui->comboBox_maxing->currentText();
        xinhaoneixing = ui->comboBox_xinhaoneixing->currentText();
        zhenchang = ui->lineEdit_zhenchang->text();
        zhenmazhu = ui->comboBox_zhenmazhu->currentText();
        fuzhenfanshi = ui->comboBox_fuzhenfanshi->currentText();
        fuzhenchangdu = ui->lineEdit_fuzhenchangdu->text();
        IDzijizhi = ui->comboBox_IDzijizhi->currentText();
        IDzijishufangshi = ui->comboBox_IDzijishufangshi->currentText();
        //Fuzhentezheng = ui->lineEdit_fuzhentezheng->text();
        fuzhenlvxu = ui->lineEdit_fuzhenlvxu->text();
        fspinlv = ui->lineEdit_fspinlv->text();
        tzbinpian = ui->lineEdit_tzbinpian->text();
        tiao1 = ui->comboBox_tiao1->currentText();
        zai1 = ui->comboBox_zai1->currentText();
        tiaokai1 = ui->comboBox_tiaokai1->currentText();
        tiaoji1 = ui->comboBox_tiaoji1->currentText();
        fsygonglvkongz = ui->lineEdit_fsygonglvkongz->text();
//        LDPC = ui->comboBox_LDPC->currentText();
//        TPC = ui->comboBox_TPC->currentText();
//        RS = ui->comboBox_RS->currentText();
//        juanji = ui->comboBox_juanji->currentText();
        TPCtongbuma = ui->Edit_TPCtongbuma->text();
        youxiaobiaozi = ui->Edit_youxiaobiaozi->text();
        bianmakai = ui->comboBox_bianma->currentText();

        if(ui->checkBox_low->isChecked())
        {
            bujielow = 1;
        }
        else
        {
            bujielow = 0;
        }

        if(ui->checkBox_high->isChecked())
        {
            bujiehigh = 1;
        }
        else
        {
            bujiehigh = 0;
        }


        ismofei = 0;

        // 基本参数组
        settings.beginGroup("BasicParameters");
        settings.setValue("zichang", zichang);
        settings.setValue("xinhaoneixing", xinhaoneixing);
        settings.setValue("zhenchang", zhenchang);
        settings.setValue("fspinlv", fspinlv);
        settings.endGroup();

        // 同步与编码组
        settings.beginGroup("SyncCoding");
        settings.setValue("xhfztongbuma", xhfztongbuma);
        settings.setValue("Bianma", Bianma);
        settings.setValue("Bianmaweizhi", Bianmaweizhi);
        settings.setValue("Malv", Malv);
        settings.setValue("TPCtongbuma", TPCtongbuma);
        settings.setValue("youxiaobiaozi", youxiaobiaozi);
        settings.endGroup();

        // 调制组
        settings.beginGroup("Modulation");
        settings.setValue("maxing", maxing);
        settings.setValue("fuzhenfanshi", fuzhenfanshi);
        settings.setValue("fuzhenchangdu", fuzhenchangdu);
        settings.setValue("tzfzweizhi", tzfzweizhi);
        settings.setValue("tiao1", tiao1);
        settings.setValue("zai1", zai1);
        settings.setValue("tiaokai1", tiaokai1);
        settings.setValue("tiaoji1", tiaoji1);
        settings.endGroup();

        // ID管理组
        settings.beginGroup("Identification");
        settings.setValue("IDmafztz", IDmafztz);
        settings.setValue("IDzijizhi", IDzijizhi);
        settings.setValue("IDzijishufangshi", IDzijishufangshi);
        settings.setValue("Fuzhentezheng", Fuzhentezheng);
        settings.setValue("ismofei", ismofei);
        settings.endGroup();
        // 跳频组
        settings.beginGroup("FrequencyHopping");
        settings.setValue("tzbinpian", tzbinpian);
        settings.endGroup();

        // 功率控制组
        settings.beginGroup("PowerControl");
        settings.setValue("fsygonglvkongz", fsygonglvkongz);
        settings.endGroup();

        // 通道编码组
        settings.beginGroup("ChannelCoding");
        settings.setValue("bianmakai" , bianmakai);
        settings.setValue("LDPC", LDPC);
        settings.setValue("TPC", TPC);
        settings.setValue("RS", RS);
        settings.setValue("juanji", juanji);
        settings.endGroup();

        // 步进控制组
        settings.beginGroup("StepControl");
        settings.setValue("tjmbujin", tjmbujin);
        settings.setValue("tjmchushizi", tjmchushizi);
        settings.endGroup();

        // 中继组
        settings.beginGroup("Relay");
        settings.setValue("zjsdzjbodao", zjsdzjbodao);
        settings.setValue("bujielow", bujielow);
        settings.setValue("zjsgzjbodao", zjsgzjbodao);
        settings.setValue("bujiehigh", bujiehigh);
        settings.endGroup();

        // 序列组
        settings.beginGroup("Sequences");
        settings.setValue("fuzhenlvxu", fuzhenlvxu);
        settings.setValue("zhenmazhu", zhenmazhu);
        settings.endGroup();

    }
    else if(pattern == 2)
        {
           zichang_2 = ui->comboBox_zichang->currentText();
           xhfztongbuma_2 = ui->lineEdit_xhfztongbuma->text();
           tjmbujin_2 = ui->lineEdit_tjmbujin->text();
           tjmchushizi_2 = ui->lineEdit_tjmchushizi->text();
           zjsdzjbodao_2 = ui->lineEdit_zjsdzjbodao->text();
           zjsgzjbodao_2 = ui->lineEdit_zjsgzjbodao->text();
           //IDmafztz_2 = ui->lineEdit_IDmafztz->text();
           Bianmaweizhi_2 = ui->comboBox_bianmaweizhi->currentText();
           //Bianma_2 = ui->comboBox_bianma->currentText();
           Malv_2 = ui->lineEdit_malv->text();
           maxing_2 = ui->comboBox_maxing->currentText();
           xinhaoneixing_2 = ui->comboBox_xinhaoneixing->currentText();
           zhenchang_2 = ui->lineEdit_zhenchang->text();
           zhenmazhu_2 = ui->comboBox_zhenmazhu->currentText();
           fuzhenfanshi_2 = ui->comboBox_fuzhenfanshi->currentText();
           fuzhenchangdu_2 = ui->lineEdit_fuzhenchangdu->text();
           IDzijizhi_2 = ui->comboBox_IDzijizhi->currentText();
           IDzijishufangshi_2 = ui->comboBox_IDzijishufangshi->currentText();
           //Fuzhentezheng_2 = ui->lineEdit_fuzhentezheng->text();
           fuzhenlvxu_2 = ui->lineEdit_fuzhenlvxu->text();
           fspinlv_2 = ui->lineEdit_fspinlv->text();
           tzbinpian_2 = ui->lineEdit_tzbinpian->text();
           tiao1_2 = ui->comboBox_tiao1->currentText();
           zai1_2 = ui->comboBox_zai1->currentText();
           tiaokai1_2 = ui->comboBox_tiaokai1->currentText();
           tiaoji1_2 = ui->comboBox_tiaoji1->currentText();
           fsygonglvkongz_2 = ui->lineEdit_fsygonglvkongz->text();
//           LDPC_2 = ui->comboBox_LDPC->currentText();
//           TPC_2 = ui->comboBox_TPC->currentText();
//           RS_2 = ui->comboBox_RS->currentText();
//           juanji_2 = ui->comboBox_juanji->currentText();
           TPCtongbuma_2 = ui->Edit_TPCtongbuma->text();
           youxiaobiaozi_2 = ui->Edit_youxiaobiaozi->text();
           bianmakai_2 = ui->comboBox_bianma->currentText();


           if(ui->checkBox_low->isChecked())
           {
               bujielow_2 = 1;
           }
           else
           {
               bujielow_2 = 0;
           }

           if(ui->checkBox_high->isChecked())
           {
               bujiehigh_2 = 1;
           }
           else
           {
               bujiehigh_2 = 0;
           }



               ismofei_2 = 0;


           // 基本参数组2
           settings.beginGroup("BasicParameters2");
           settings.setValue("zichang2", zichang_2);
           settings.setValue("xinhaoneixing2", xinhaoneixing_2);
           settings.setValue("zhenchang2", zhenchang_2);
           settings.setValue("fspinlv2", fspinlv_2);
           settings.endGroup();

           // 同步与编码组2
           settings.beginGroup("SyncCoding2");
           settings.setValue("xhfztongbuma2", xhfztongbuma_2);
           settings.setValue("Bianma2", Bianma_2);
           settings.setValue("Bianmaweizhi2", Bianmaweizhi_2);
           settings.setValue("Malv2", Malv_2);
           settings.setValue("TPCtongbuma2", TPCtongbuma_2);
           settings.setValue("youxiaobiaozi2", youxiaobiaozi_2);
           settings.endGroup();

           // 调制组2
           settings.beginGroup("Modulation2");
           settings.setValue("maxing2", maxing_2);
           settings.setValue("fuzhenfanshi2", fuzhenfanshi_2);
           settings.setValue("fuzhenchangdu2", fuzhenchangdu_2);
           settings.setValue("tzfzweizhi2", tzfzweizhi_2);
           settings.setValue("tiao12", tiao1_2);
           settings.setValue("zai12", zai1_2);
           settings.setValue("tiaokai12", tiaokai1_2);
           settings.setValue("tiaoji12", tiaoji1_2);
           settings.endGroup();

           // ID管理组2
           settings.beginGroup("Identification2");
           settings.setValue("IDmafztz2", IDmafztz_2);
           settings.setValue("IDzijizhi2", IDzijizhi_2);
           settings.setValue("IDzijishufangshi2", IDzijishufangshi_2);
           settings.setValue("Fuzhentezheng2", Fuzhentezheng_2);
           settings.setValue("ismofei_2", ismofei_2);
           settings.endGroup();

           // 跳频组2
           settings.beginGroup("FrequencyHopping2");
           settings.setValue("tzbinpian2", tzbinpian_2);
           settings.endGroup();

           // 功率控制组2
           settings.beginGroup("PowerControl2");
           settings.setValue("fsygonglvkongz2", fsygonglvkongz_2);
           settings.endGroup();

           // 通道编码组2
           settings.beginGroup("ChannelCoding2");
           settings.setValue("bianmakai2" , bianmakai_2);
           settings.setValue("LDPC2", LDPC_2);
           settings.setValue("TPC2", TPC_2);
           settings.setValue("RS2", RS_2);
           settings.setValue("juanji2", juanji_2);
           settings.endGroup();

           // 步进控制组2
           settings.beginGroup("StepControl2");
           settings.setValue("tjmbujin2", tjmbujin_2);
           settings.setValue("tjmchushizi2", tjmchushizi_2);
           settings.endGroup();

           // 中继组2
           settings.beginGroup("Relay2");
           settings.setValue("zjsdzjbodao2", zjsdzjbodao_2);
           settings.setValue("bujielow_2", bujielow_2);
           settings.setValue("zjsdzjbodao2", zjsdzjbodao_2);
           settings.setValue("bujiehigh_2", bujiehigh_2);
           settings.endGroup();

           // 序列组2
           settings.beginGroup("Sequences2");
           settings.setValue("fuzhenlvxu2", fuzhenlvxu_2);
           settings.setValue("zhenmazhu2", zhenmazhu_2);
           settings.endGroup();
    }


//    QSettings settings("settings.ini", QSettings::IniFormat);

    if(pattern == 1)
    {
        // 加载主设置
        settings.beginGroup(QString("fa1pcmtab"));

        settings.setValue("anysum",anysum);

        for(int i =0 ; i < anysum ; i++)
        {
            settings.setValue(QString("name%1").arg(i),ui->tableWidget_pcm->item(i , 0)->text());
            settings.setValue(QString("zhenmoshi%1").arg(i),ui->tableWidget_pcm->item(i , 1)->text());
            settings.setValue(QString("fuzhenweizhi%1").arg(i),ui->tableWidget_pcm->item(i , 2)->text());
            settings.setValue(QString("zizhenweizhi%1").arg(i),ui->tableWidget_pcm->item(i , 3)->text());
            settings.setValue(QString("datafrom%1").arg(i),ui->tableWidget_pcm->item(i , 4)->text());
            settings.setValue(QString("fangzhiLength%1").arg(i),ui->tableWidget_pcm->item(i , 5)->text());

        }

        settings.endGroup();
    }

    else if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2pcmtab"));

        settings.setValue("anysum",anysum);

        for(int i =0 ; i < anysum ; i++)
        {
            settings.setValue(QString("name%1").arg(i),ui->tableWidget_pcm->item(i , 0)->text());
            settings.setValue(QString("zhenmoshi%1").arg(i),ui->tableWidget_pcm->item(i , 1)->text());
            settings.setValue(QString("fuzhenweizhi%1").arg(i),ui->tableWidget_pcm->item(i , 2)->text());
            settings.setValue(QString("zizhenweizhi%1").arg(i),ui->tableWidget_pcm->item(i , 3)->text());
            settings.setValue(QString("datafrom%1").arg(i),ui->tableWidget_pcm->item(i , 4)->text());
            settings.setValue(QString("fangzhiLength%1").arg(i),ui->tableWidget_pcm->item(i , 5)->text());

        }

        settings.endGroup();
    }




    if(pattern == 1)
    {
        // 加载主设置
        settings.beginGroup(QString("fa1yibuyuantab"));

        settings.setValue("asynum",asynum);



        for(int i =0 ; i < asynum ; i++)
        {
            settings.setValue(QString("name%1").arg(i),ui->tableWidget_yibuyuan->item(i , 0)->text());
            settings.setValue(QString("tongbuma%1").arg(i),ui->tableWidget_yibuyuan->item(i , 1)->text());
            settings.setValue(QString("zhenmoshi%1").arg(i),ui->tableWidget_yibuyuan->item(i , 2)->text());
            settings.setValue(QString("ankonglocation%1").arg(i),ui->tableWidget_yibuyuan->item(i , 3)->text());
            settings.setValue(QString("shujuliexing%1").arg(i),ui->tableWidget_yibuyuan->item(i , 4)->text());
            settings.setValue(QString("taijiemabujin%1").arg(i),ui->tableWidget_yibuyuan->item(i , 5)->text());
            settings.setValue(QString("taijiemainit%1").arg(i),ui->tableWidget_yibuyuan->item(i , 6)->text());
            //settings.setValue(QString("tongbumalength%1").arg(i),ui->tableWidget_yibuyuan->item(i , 7)->text());
            settings.setValue(QString("zhenjishulength%1").arg(i),ui->tableWidget_yibuyuan->item(i , 7)->text());
            settings.setValue(QString("zhenlv%1").arg(i),ui->tableWidget_yibuyuan->item(i , 8)->text());


        }

        settings.endGroup();
    }

    else if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2yibuyuantab"));

        settings.setValue("asynum",asynum);

        for(int i =0 ; i < asynum ; i++)
        {
            settings.setValue(QString("name%1").arg(i),ui->tableWidget_yibuyuan->item(i , 0)->text());
            settings.setValue(QString("tongbuma%1").arg(i),ui->tableWidget_yibuyuan->item(i , 1)->text());
            settings.setValue(QString("zhenmoshi%1").arg(i),ui->tableWidget_yibuyuan->item(i , 2)->text());
            settings.setValue(QString("ankonglocation%1").arg(i),ui->tableWidget_yibuyuan->item(i , 3)->text());
            settings.setValue(QString("shujuliexing%1").arg(i),ui->tableWidget_yibuyuan->item(i , 4)->text());
            settings.setValue(QString("taijiemabujin%1").arg(i),ui->tableWidget_yibuyuan->item(i , 5)->text());
            settings.setValue(QString("taijiemainit%1").arg(i),ui->tableWidget_yibuyuan->item(i , 6)->text());
            //settings.setValue(QString("tongbumalength%1").arg(i),ui->tableWidget_yibuyuan->item(i , 7)->text());
            settings.setValue(QString("zhenjishulength%1").arg(i),ui->tableWidget_yibuyuan->item(i , 7)->text());
            settings.setValue(QString("zhenlv%1").arg(i),ui->tableWidget_yibuyuan->item(i , 8)->text());

        }

        settings.endGroup();
    }

}

void Dialogfasheset::loadSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

        if(pattern == 1)
        {
            // 基本参数组
            settings.beginGroup("BasicParameters");
            zichang = settings.value("zichang", "8").toString(); // 默认值示例
            xinhaoneixing = settings.value("xinhaoneixing", "随机码").toString();
            zhenchang = settings.value("zhenchang", "128").toString();
            fspinlv = settings.value("fspinlv", "2400").toString();
            settings.endGroup();

            // 同步与编码组
            settings.beginGroup("SyncCoding");
            xhfztongbuma = settings.value("xhfztongbuma", "EB90").toString();
            Bianma = settings.value("Bianma", "TPC").toString();
            Bianmaweizhi = settings.value("Bianmaweizhi", "5").toString();
            Malv = settings.value("Malv", "10000").toString();
            TPCtongbuma = settings.value("TPCtongbuma", "1ACFFC1D").toString();
            youxiaobiaozi = settings.value("youxiaobiaozi", "FFFF").toString();
            settings.endGroup();

            // 调制组
            settings.beginGroup("Modulation");
            maxing = settings.value("maxing", "NRZ-L").toString();
            fuzhenfanshi = settings.value("fuzhenfanshi", "无副帧").toString();
            fuzhenchangdu = settings.value("fuzhenchangdu", "16").toString();
            tzfzweizhi = settings.value("tzfzweizhi", "10").toString();
            tiao1 = settings.value("tiao1", "50").toString();
            zai1 = settings.value("zai1", "40").toString();
            tiaokai1 = settings.value("tiaokai1", "1").toString();
            tiaoji1 = settings.value("tiaoji1", "2").toString();
            settings.endGroup();

            // ID管理组
            settings.beginGroup("Identification");
            IDmafztz = settings.value("IDmafztz", "FFFF").toString();
            IDzijizhi = settings.value("IDzijizhi", "127").toString();
            IDzijishufangshi = settings.value("IDzijishufangshi", "FFFF").toString();
            Fuzhentezheng = settings.value("Fuzhentezheng", "00").toString();
            ismofei = settings.value("ismofei", "00").toInt();
            settings.endGroup();

            // 跳频组
            settings.beginGroup("FrequencyHopping");
            tzbinpian = settings.value("tzbinpian", "3500").toString();
            settings.endGroup();

            // 功率控制组
            settings.beginGroup("PowerControl");
            fsygonglvkongz = settings.value("fsygonglvkongz", "0").toString();
            settings.endGroup();



            // 通道编码组
            settings.beginGroup("ChannelCoding");
            bianmakai = settings.value("bianmakai", "0").toString();
            LDPC = settings.value("LDPC", "0").toString();
            TPC = settings.value("TPC", "0").toString();
            RS = settings.value("RS", "0").toString();
            juanji = settings.value("juanji", "0").toString();
            settings.endGroup();

            // 步进控制组
            settings.beginGroup("StepControl");
            tjmbujin = settings.value("tjmbujin", "1").toString();
            tjmchushizi = settings.value("tjmchushizi", "0").toString();
            settings.endGroup();

            // 中继组
            settings.beginGroup("Relay");
            zjsdzjbodao = settings.value("zjsdzjbodao", "1").toString();
            bujielow = settings.value("bujielow", "1").toInt();
            zjsgzjbodao = settings.value("zjsgzjbodao", "2").toString();
            bujiehigh = settings.value("bujiehigh", "1").toInt();
            settings.endGroup();

            // 序列组
            settings.beginGroup("Sequences");
            fuzhenlvxu = settings.value("fuzhenlvxu", "0").toString();
            zhenmazhu = settings.value("zhenmazhu", "EB90").toString();
            settings.endGroup();
        }

        else if(pattern == 2)
        {

            // 基本参数组2
            settings.beginGroup("BasicParameters2");
            zichang_2 = settings.value("zichang2", "8").toString();
            xinhaoneixing_2 = settings.value("xinhaoneixing2", "随机码").toString();
            zhenchang_2 = settings.value("zhenchang2", "128").toString();
            fspinlv_2 = settings.value("fspinlv2", "2400").toString();
            settings.endGroup();

            // 同步与编码组2
            settings.beginGroup("SyncCoding2");
            xhfztongbuma_2 = settings.value("xhfztongbuma2", "EB90").toString();
            Bianma_2 = settings.value("Bianma2", "TPC").toString();
            Bianmaweizhi_2 = settings.value("Bianmaweizhi2", "5").toString();
            Malv_2 = settings.value("Malv2", "10000").toString();
            TPCtongbuma_2 = settings.value("TPCtongbuma2", "1ACFFC1D").toString();
            youxiaobiaozi_2 = settings.value("youxiaobiaozi2", "FFFF").toString();
            settings.endGroup();

            // 调制组2
            settings.beginGroup("Modulation2");
            maxing_2 = settings.value("maxing2", "NRZ-L").toString();
            fuzhenfanshi_2 = settings.value("fuzhenfanshi2", "2FSK").toString();
            fuzhenchangdu_2 = settings.value("fuzhenchangdu2", "128").toString();
            tzfzweizhi_2 = settings.value("tzfzweizhi2", "10").toString();
            tiao1_2 = settings.value("tiao12", "50").toString();
            zai1_2 = settings.value("zai12", "40").toString();
            tiaokai1_2 = settings.value("tiaokai12", "1").toString();
            tiaoji1_2 = settings.value("tiaoji12", "2").toString();
            settings.endGroup();

            // ID管理组2
            settings.beginGroup("Identification2");
            IDmafztz_2 = settings.value("IDmafztz2", "AAFF").toString();
            IDzijizhi_2 = settings.value("IDzijizhi2", "127").toString();
            IDzijishufangshi_2 = settings.value("IDzijishufangshi2", "0").toString();
            Fuzhentezheng_2 = settings.value("Fuzhentezheng2", "00").toString();
            ismofei_2 = settings.value("ismofei_2", "00").toInt();
            settings.endGroup();

            // 跳频组2
            settings.beginGroup("FrequencyHopping2");
            tzbinpian_2 = settings.value("tzbinpian2", "3500").toString();
            settings.endGroup();

            // 功率控制组2
            settings.beginGroup("PowerControl2");
            fsygonglvkongz_2 = settings.value("fsygonglvkongz2", "0").toString();
            settings.endGroup();

            // 通道编码组2
            settings.beginGroup("ChannelCoding2");
            bianmakai_2 = settings.value("bianmakai2", "0").toString();
            LDPC_2 = settings.value("LDPC2", "1").toString();
            TPC_2 = settings.value("TPC2", "0").toString();
            RS_2 = settings.value("RS2", "1").toString();
            juanji_2 = settings.value("juanji2", "3").toString();
            settings.endGroup();

            // 步进控制组2
            settings.beginGroup("StepControl2");
            tjmbujin_2 = settings.value("tjmbujin2", "1").toString();
            tjmchushizi_2 = settings.value("tjmchushizi2", "0").toString();
            settings.endGroup();

            // 中继组2
            settings.beginGroup("Relay2");
            zjsdzjbodao_2 = settings.value("zjsdzjbodao2", "1").toString();
            bujielow_2 = settings.value("bujielow_2", "1").toInt();
            zjsgzjbodao_2 = settings.value("zjsgzjbodao2", "2").toString();
            bujiehigh_2 = settings.value("bujiehigh_2", "1").toInt();
            settings.endGroup();

            // 序列组2
            settings.beginGroup("Sequences2");
            fuzhenlvxu_2 = settings.value("fuzhenlvxu2", "0").toString();
            zhenmazhu_2 = settings.value("zhenmazhu2", "EB90").toString();
            settings.endGroup();
        }






        updateUIFromVariables();
}

void Dialogfasheset::settableUI()
{
    ui->tableWidget_pcm->setColumnCount(6);
    // 设置水平表头（列标题）
    QStringList horizontalHeaders;
    horizontalHeaders << "名称" << "帧模式" << "副帧位置" << "子帧位置" << "数据来源" << "放置长度";

    ui->tableWidget_pcm->setHorizontalHeaderLabels(horizontalHeaders);
    ui->tableWidget_pcm->resizeColumnsToContents();

    ui->tableWidget_yibuyuan->setRowCount(10);
    ui->tableWidget_yibuyuan->setColumnCount(9);

    ui->tableWidget_yibuyuan->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget_yibuyuan->resizeColumnsToContents();

    // 设置水平表头（列标题）
    QStringList horizontalHeaders2;
    horizontalHeaders2 << "名称" << "同步码(H)" << "帧长度" << "安控位置"<< "数据类型" << "台阶码步进" << "台阶码初始值"  << "帧计数位置" << "帧率";

    ui->tableWidget_yibuyuan->setHorizontalHeaderLabels(horizontalHeaders2);


    ui->tableWidget_yibuyuan->setWordWrap(true);

    ui->tableWidget_yibuyuan->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableWidget_yibuyuan->resizeColumnsToContents();

//    IntRangeDelegate *delegate1 = new IntRangeDelegate(1, 256, this);
//    ui->tableWidget_yibuyuan->setItemDelegateForColumn(9, delegate1); // 设置第一列使用该委托

//    MaxLengthDelegate *delegate2= new MaxLengthDelegate(8,this);
//    ui->tableWidget_yibuyuan->setItemDelegateForColumn(1, delegate2); // 设置第一列使用该委托




    QSettings settings("settings.ini", QSettings::IniFormat);

    if(pattern == 1)
    {

        // 加载主设置
        settings.beginGroup(QString("fa1pcmtab"));

        anysum = settings.value("anysum", 3).toInt();

        ui->tableWidget_pcm->setRowCount(anysum);

        ui->tableWidget_pcm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        for(int i =0 ; i < 10 ; i++)
        {
            ui->tableWidget_pcm->setItem(i , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(i), "数据块").toString()));
            ui->tableWidget_pcm->setItem(i , 1 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(i), "子帧模式").toString()));
            ui->tableWidget_pcm->setItem(i , 2 ,new QTableWidgetItem(settings.value(QString("fuzhenweizhi%1").arg(i), 1).toString()));
            ui->tableWidget_pcm->setItem(i , 3 ,new QTableWidgetItem(settings.value(QString("zizhenweizhi%1").arg(i), 1).toString()));
            ui->tableWidget_pcm->setItem(i , 4 ,new QTableWidgetItem(settings.value(QString("datafrom%1").arg(i), "异步源").toString()));
            ui->tableWidget_pcm->setItem(i , 5 ,new QTableWidgetItem(settings.value(QString("fangzhiLength%1").arg(i), 10).toString()));
        }

        settings.endGroup();

    }

    else if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2pcmtab"));

        anysum = settings.value("anysum", 3).toInt();

        ui->tableWidget_pcm->setRowCount(anysum);

        ui->tableWidget_pcm->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        for(int i =0 ; i < 10 ; i++)
        {
            ui->tableWidget_pcm->setItem(i , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(i), "数据块").toString()));
            ui->tableWidget_pcm->setItem(i , 1 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(i), "子帧模式").toString()));
            ui->tableWidget_pcm->setItem(i , 2 ,new QTableWidgetItem(settings.value(QString("fuzhenweizhi%1").arg(i), 1).toString()));
            ui->tableWidget_pcm->setItem(i , 3 ,new QTableWidgetItem(settings.value(QString("zizhenweizhi%1").arg(i), 1).toString()));
            ui->tableWidget_pcm->setItem(i , 4 ,new QTableWidgetItem(settings.value(QString("datafrom%1").arg(i), "异步源").toString()));
            ui->tableWidget_pcm->setItem(i , 5 ,new QTableWidgetItem(settings.value(QString("fangzhiLength%1").arg(i), 10).toString()));
        }

        settings.endGroup();
    }

    if(pattern == 1)
    {

        // 加载主设置
        settings.beginGroup(QString("fa1yibuyuantab"));

        asynum = settings.value("asynum", 3).toInt();

        ui->tableWidget_yibuyuan->setRowCount(asynum);

        ui->tableWidget_yibuyuan->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_yibuyuan->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Fixed);
        ui->tableWidget_yibuyuan->setColumnWidth(6, 80);




        for(int i =0 ; i < asynum ; i++)
        {


            ui->tableWidget_yibuyuan->setItem(i , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(i), "异步源1").toString()));
            ui->tableWidget_yibuyuan->setItem(i , 1 ,new QTableWidgetItem(settings.value(QString("tongbuma%1").arg(i), "146f").toString()));
            ui->tableWidget_yibuyuan->setItem(i , 2 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(i), 12).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 3 ,new QTableWidgetItem(settings.value(QString("ankonglocation%1").arg(i), 10).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 4 ,new QTableWidgetItem(settings.value(QString("shujuliexing%1").arg(i), "台阶码").toString()));
            ui->tableWidget_yibuyuan->setItem(i , 5 ,new QTableWidgetItem(settings.value(QString("taijiemabujin%1").arg(i), 1).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 6 ,new QTableWidgetItem(settings.value(QString("taijiemainit%1").arg(i), 3).toString()));
            //ui->tableWidget_yibuyuan->setItem(i , 7 ,new QTableWidgetItem(settings.value(QString("tongbumalength%1").arg(i), 8).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 7 ,new QTableWidgetItem(settings.value(QString("zhenjishulength%1").arg(i), 10).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 8 ,new QTableWidgetItem(settings.value(QString("zhenlv%1").arg(i), 100).toString()));

        }

        settings.endGroup();

    }

    else if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2yibuyuantab"));

        asynum = settings.value("asynum", 3).toInt();

        ui->tableWidget_yibuyuan->setRowCount(asynum);

        ui->tableWidget_yibuyuan->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_yibuyuan->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Fixed);
        ui->tableWidget_yibuyuan->setColumnWidth(6, 80);

        for(int i =0 ; i < asynum ; i++)
        {
            ui->tableWidget_yibuyuan->setItem(i , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(i), "异步源1").toString()));
            ui->tableWidget_yibuyuan->setItem(i , 1 ,new QTableWidgetItem(settings.value(QString("tongbuma%1").arg(i), "146f").toString()));
            ui->tableWidget_yibuyuan->setItem(i , 2 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(i), 12).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 3 ,new QTableWidgetItem(settings.value(QString("ankonglocation%1").arg(i), 10).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 4 ,new QTableWidgetItem(settings.value(QString("shujuliexing%1").arg(i), "台阶码").toString()));
            ui->tableWidget_yibuyuan->setItem(i , 5 ,new QTableWidgetItem(settings.value(QString("taijiemabujin%1").arg(i), 1).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 6 ,new QTableWidgetItem(settings.value(QString("taijiemainit%1").arg(i), 3).toString()));
            //ui->tableWidget_yibuyuan->setItem(i , 7 ,new QTableWidgetItem(settings.value(QString("tongbumalength%1").arg(i), 8).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 7 ,new QTableWidgetItem(settings.value(QString("zhenjishulength%1").arg(i), 10).toString()));
            ui->tableWidget_yibuyuan->setItem(i , 8 ,new QTableWidgetItem(settings.value(QString("zhenlv%1").arg(i), 100).toString()));
    }
     settings.endGroup();
    }


    QObject::connect(ui->tableWidget_pcm, &QTableWidget::cellClicked, this, [&](int row, int col){
        if (col != 4 && col != 1) return;  // 只处理第4列和第1列

        if(col == 4)
        {
            // 创建选择菜单
            QMenu menu;
           // QStringList options = {"异步源", "GNSS", "安控"};
            QStringList options = {"异步源", "GNSS", "安控状态", "安控自检","安控复位" ,"安控解锁","安控自毁"};
            for (const QString &option : options) {
                QAction *action = menu.addAction(option);
                // 设置选择后的行为 - 使用[=]按值捕获避免悬空引用
                QObject::connect(action, &QAction::triggered, [=, this](){
                    if(auto item = ui->tableWidget_pcm->item(row, col)) {
                        item->setText(option);
                    }
                });
            }

            // 获取单元格位置并弹出菜单
            QRect rect = ui->tableWidget_pcm->visualRect(ui->tableWidget_pcm->model()->index(row, col));
            menu.exec(ui->tableWidget_pcm->viewport()->mapToGlobal(rect.bottomLeft()));
        }
        else if(col == 1)
        {
            // 创建选择菜单
            QMenu menu;
            QStringList options = {"子帧模式","副帧模式"};
            for (const QString &option : options) {
                QAction *action = menu.addAction(option);
                // 设置选择后的行为 - 使用[=]按值捕获避免悬空引用
                QObject::connect(action, &QAction::triggered, [=, this](){
                    if(auto item = ui->tableWidget_pcm->item(row, col)) {
                        item->setText(option);
                    }
                });
            }

            // 获取单元格位置并弹出菜单
            QRect rect = ui->tableWidget_pcm->visualRect(ui->tableWidget_pcm->model()->index(row, col));
            menu.exec(ui->tableWidget_pcm->viewport()->mapToGlobal(rect.bottomLeft()));
        }
    });  // 注意这里是正确的结束符号


    QObject::connect(ui->tableWidget_yibuyuan, &QTableWidget::cellClicked, this, [&](int row, int col){
        if (col != 1 && col != 4) return;  // 只处理第4列和第1列




        else if(col == 4)
        {
            // 创建选择菜单
            QMenu menu;
            QStringList options = {"台阶码","随机码","用户码"};
            for (const QString &option : options) {
                QAction *action = menu.addAction(option);
                // 设置选择后的行为 - 使用[=]按值捕获避免悬空引用
                QObject::connect(action, &QAction::triggered, [=, this](){
                    if(auto item = ui->tableWidget_yibuyuan->item(row, col)) {
                        item->setText(option);
                    }
                });
            }

            // 获取单元格位置并弹出菜单
            QRect rect = ui->tableWidget_yibuyuan->visualRect(ui->tableWidget_yibuyuan->model()->index(row, col));
            menu.exec(ui->tableWidget_yibuyuan->viewport()->mapToGlobal(rect.bottomLeft()));
        }
    });  // 注意这里是正确的结束符号

}

void Dialogfasheset::updateUIFromVariables()
{
    if(pattern == 1)
    {
        ui->comboBox_zichang->setCurrentText(QString(zichang));
        ui->lineEdit_xhfztongbuma->setText(xhfztongbuma);
        ui->lineEdit_tjmbujin->setText(tjmbujin);
        ui->lineEdit_tjmchushizi->setText(tjmchushizi);
        ui->lineEdit_zjsdzjbodao->setText(zjsdzjbodao);
        ui->lineEdit_zjsgzjbodao->setText(zjsgzjbodao);
        //ui->lineEdit_IDmafztz->setText(IDmafztz);
        ui->comboBox_bianmaweizhi->setCurrentText(Bianmaweizhi);
        //ui->comboBox_bianma->setCurrentText(Bianma);
        ui->lineEdit_malv->setText(Malv);
        ui->comboBox_maxing->setCurrentText(maxing);
        ui->comboBox_xinhaoneixing->setCurrentText(xinhaoneixing);
        ui->lineEdit_zhenchang->setText(zhenchang);
        ui->comboBox_zhenmazhu->setCurrentText(zhenmazhu);
        ui->comboBox_fuzhenfanshi->setCurrentText(fuzhenfanshi);
        ui->lineEdit_fuzhenchangdu->setText(fuzhenchangdu);
        ui->comboBox_IDzijizhi->setCurrentText(IDzijizhi);
        ui->comboBox_IDzijishufangshi->setCurrentText(IDzijishufangshi);
        //ui->lineEdit_fuzhentezheng->setText(Fuzhentezheng);
        ui->lineEdit_fuzhenlvxu->setText(fuzhenlvxu);
        ui->lineEdit_fspinlv->setText(fspinlv);
        ui->lineEdit_tzbinpian->setText(tzbinpian);

        ui->comboBox_tiao1->setCurrentText(tiao1);
        ui->comboBox_zai1->setCurrentText(zai1);
        ui->comboBox_tiaokai1->setCurrentText(tiaokai1);
        ui->comboBox_tiaoji1->setCurrentText(tiaoji1);
        ui->lineEdit_fsygonglvkongz->setText(fsygonglvkongz);

        //ui->comboBox_LDPC->setCurrentText(LDPC);
        //ui->comboBox_TPC->setCurrentText(TPC);
        //ui->comboBox_RS->setCurrentText(RS);
        //ui->comboBox_juanji->setCurrentText(juanji);
        ui->Edit_TPCtongbuma->setText(TPCtongbuma);
        ui->Edit_youxiaobiaozi->setText(youxiaobiaozi);

        if(bujielow == 0 )
        {
            ui->checkBox_low->setChecked(false);
        }
        else
        {
            ui->checkBox_low->setChecked(true);
        }
        if(bujiehigh == 0 )
        {
            ui->checkBox_high->setChecked(false);
        }
        else
        {
            ui->checkBox_high->setChecked(true);
        }


        ui->comboBox_bianma->setCurrentText(bianmakai);








    }

    else if(pattern == 2)
    {


           ui->comboBox_zichang->setCurrentText(QString(zichang_2));
           ui->lineEdit_xhfztongbuma->setText(xhfztongbuma_2);
           ui->lineEdit_tjmbujin->setText(tjmbujin_2);
           ui->lineEdit_tjmchushizi->setText(tjmchushizi_2);
           ui->lineEdit_zjsdzjbodao->setText(zjsdzjbodao_2);
           ui->lineEdit_zjsgzjbodao->setText(zjsgzjbodao_2);
           //ui->lineEdit_IDmafztz->setText(IDmafztz_2);
           ui->comboBox_bianmaweizhi->setCurrentText(Bianmaweizhi_2);
           //ui->comboBox_bianma->setCurrentText(Bianma_2);
           ui->lineEdit_malv->setText(Malv_2);
           ui->comboBox_maxing->setCurrentText(maxing_2);
           ui->comboBox_xinhaoneixing->setCurrentText(xinhaoneixing_2);
           ui->lineEdit_zhenchang->setText(zhenchang_2);
           ui->comboBox_zhenmazhu->setCurrentText(zhenmazhu_2);
           ui->comboBox_fuzhenfanshi->setCurrentText(fuzhenfanshi_2);
           ui->lineEdit_fuzhenchangdu->setText(fuzhenchangdu_2);
           ui->comboBox_IDzijizhi->setCurrentText(IDzijizhi_2);
           ui->comboBox_IDzijishufangshi->setCurrentText(IDzijishufangshi_2);
           //ui->lineEdit_fuzhentezheng->setText(Fuzhentezheng_2);
           ui->lineEdit_fuzhenlvxu->setText(fuzhenlvxu_2);
           ui->lineEdit_fspinlv->setText(fspinlv_2);
           ui->lineEdit_tzbinpian->setText(tzbinpian_2);

           ui->comboBox_tiao1->setCurrentText(tiao1_2);
           ui->comboBox_zai1->setCurrentText(zai1_2);
           ui->comboBox_tiaokai1->setCurrentText(tiaokai1_2);
           ui->comboBox_tiaoji1->setCurrentText(tiaoji1_2);
           ui->lineEdit_fsygonglvkongz->setText(fsygonglvkongz_2);

//           ui->comboBox_LDPC->setCurrentText(LDPC_2);
//           ui->comboBox_TPC->setCurrentText(TPC_2);
//           ui->comboBox_RS->setCurrentText(RS_2);
//           ui->comboBox_juanji->setCurrentText(juanji_2);
           ui->Edit_TPCtongbuma->setText(TPCtongbuma_2);
           ui->Edit_youxiaobiaozi->setText(youxiaobiaozi_2);


           if(bujielow_2 == 0 )
           {
               ui->checkBox_low->setChecked(false);
           }
           else
           {
               ui->checkBox_low->setChecked(true);
           }
           if(bujiehigh_2 == 0 )
           {
               ui->checkBox_high->setChecked(false);
           }
           else
           {
               ui->checkBox_high->setChecked(true);
           }

           ui->comboBox_bianma->setCurrentText(bianmakai_2);


    }

}

void Dialogfasheset::lookuptable()
{
    int fspinlv = ui->lineEdit_fspinlv->text().toInt();
    double tzbinpian = ui->lineEdit_tzbinpian->text().toDouble();

    QMap<int, QMap<int, double>> data; // 频率 -> 序号 -> 值
    QVector<int> frequencies;
    QVector<int> indices;

    QString appDir = QCoreApplication::applicationDirPath();

    // 构建taskconfig文件夹路径
    QString configDirPath;

    if(pattern == 1)
    {
       configDirPath = appDir + "/taskconfig/Transmitter1.txt";
    }
    else
    {
       configDirPath = appDir + "/taskconfig/Transmitter2.txt";
    }


    QFile file(configDirPath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
          return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        // 修复数据中的格式错误（如"2200;6.36.80"）
        line = line.replace(";", ",").replace(".", ",");
        QStringList parts = line.split(",");

        if (parts.size() >= 3) {
            bool ok1, ok2, ok3;
            int freq = parts[0].toInt(&ok1);
            int index = parts[1].toInt(&ok2);
            double value = parts[2].toDouble(&ok3);

            if (ok1 && ok2 && ok3) {
                data[freq][index] = value;
            }
        }
    }

    // 提取所有频率和序号用于快速查找
    frequencies = data.keys().toVector();
    std::sort(frequencies.begin(), frequencies.end());

    if (!frequencies.isEmpty()) {
        indices = data[frequencies.first()].keys().toVector();
        std::sort(indices.begin(), indices.end());
    }

    file.close();





}




void Dialogfasheset::ControlAlignment(QString filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "无法打开文件";
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;

            // 按分号分割每行数据
            QStringList parts = line.split(';');
            if (parts.size() < 3) continue;  // 确保有3列数据

            // 转换后两个数字
            bool ok1, ok2;
            int key = parts[1].toInt(&ok1);
            int value = parts[2].toInt(&ok2);

            // 验证转换成功
            if (ok1 && ok2) {
                AlignmentMap.insert(key, value);
            } else {
                qDebug() << "无效数字在行:" << line;
            }
        }
        file.close();

        // 验证输出（实际使用时移除）
        qDebug() << "解析结果:";
        for (auto it = AlignmentMap.begin(); it != AlignmentMap.end(); ++it) {
            qDebug() << "Key:" << it.key() << "Value:" << it.value();
        }

}

void Dialogfasheset::fasheping(int pattern)
{
    doWorkWithDelay(500);
    QByteArray array;

    owner->m_PPACKET_HEADER = new PACKET_HEADER;
    //owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x03;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

    if(pattern == 1)
    {
        owner->m_PTRANSMIT_CONFIG->txSelector = 0x01;
        double texttodub = ui->lineEdit_fspinlv->text().toDouble();
        owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));

        qDebug() << owner->m_PTRANSMIT_CONFIG->freq1;

        //texttoint = ui->lineEdit_tzbinpian->text().toInt();
        int  texttoint = (owner->fo == 0) ? 0 :
                                            static_cast<quint32>(
                                                ui->lineEdit_tzbinpian->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                            );
        owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
        owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
        quint8 tiaozhifangshiint;
        quint8 modPolarity1int;
        quint8 modSwitch1int;
        quint8 carrier1int;
        if(ui->comboBox_tiao1->currentText() == "FM调制")
        {
            tiaozhifangshiint =0b0000;
        }
        else if(ui->comboBox_tiao1->currentText() == "BPSK调制")
        {
            tiaozhifangshiint =0b0001;
        }
        else if(ui->comboBox_tiao1->currentText() == "QPSK调制")
        {
            tiaozhifangshiint =0b0010;
        }

        if(ui->comboBox_zai1->currentText() == "开")
        {
            carrier1int = 1;
        }
        else if(ui->comboBox_zai1->currentText() == "关")
        {
            carrier1int = 0;
        }

        if(ui->comboBox_tiaokai1->currentText() == "开")
        {
            modSwitch1int = 1;
        }
        else if(ui->comboBox_tiaokai1->currentText() == "关")
        {
            modSwitch1int = 0;
        }

        if(ui->comboBox_tiaoji1->currentText() == "正")
        {
            modPolarity1int = 0;
        }
        else if(ui->comboBox_tiaoji1->currentText() == "负")
        {
            modPolarity1int = 1;
        }
        owner->m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
        owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
        owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
        owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
        owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;

        double y = ui->lineEdit_fspinlv->text().toDouble();
        int x = ui->lineEdit_fsygonglvkongz->text().toInt();
        if(x < 6)
        {
            x = 6;
        }
        double result;
        if(pattern == 1)
        {
            QString appDir = QCoreApplication::applicationDirPath();
            qDebug() << "Application file path:" << appDir;
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
               owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}
        }
        else
        {
            QString appDir = QCoreApplication::applicationDirPath();
            qDebug() << "Application file path:" << appDir;
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
                owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}
        }



        owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
        owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_fsygonglvkongz->text().toInt()));

        qDebug() << "插值结果:" << result;

        for(int i= 0 ; i < 50 ; i++)
        {
            owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
        }


        owner->pingdian = ui->lineEdit_fspinlv->text();
        owner->pinpian = ui->lineEdit_tzbinpian->text();
        owner->tiaoz = ui->comboBox_tiao1->currentText();
        owner->gonglv = ui->lineEdit_fsygonglvkongz->text();
        owner->updateui1();

    }
    else if(pattern == 2)
    {
        owner->m_PTRANSMIT_CONFIG->txSelector = 0x02;
        double texttodub = ui->lineEdit_fspinlv->text().toDouble();
        owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));


        //texttoint = ui->lineEdit_tzbinpian->text().toInt();
        int  texttoint = (owner->fo == 0) ? 0 :
                                            static_cast<quint32>(
                                                ui->lineEdit_tzbinpian->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                            );
        owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));

        owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
        quint8 tiaozhifangshiint;
        quint8 modPolarity1int;
        quint8 modSwitch1int;
        quint8 carrier1int;
        if(ui->comboBox_tiao1->currentText() == "FM调制")
        {
            tiaozhifangshiint =0b0000;
        }
        else if(ui->comboBox_tiao1->currentText() == "BPSK调制")
        {
            tiaozhifangshiint =0b0001;
        }
        else if(ui->comboBox_tiao1->currentText() == "QPSK调制")
        {
            tiaozhifangshiint =0b0010;
        }

        if(ui->comboBox_zai1->currentText() == "开")
        {
            carrier1int = 1;
        }
        else if(ui->comboBox_zai1->currentText() == "关")
        {
            carrier1int = 0;
        }

        if(ui->comboBox_tiaokai1->currentText() == "开")
        {
            modSwitch1int = 1;
        }
        else if(ui->comboBox_tiaokai1->currentText() == "关")
        {
            modSwitch1int = 0;
        }

        if(ui->comboBox_tiaoji1->currentText() == "正")
        {
            modPolarity1int = 0;
        }
        else if(ui->comboBox_tiaoji1->currentText() == "负")
        {
            modPolarity1int = 1;
        }
        owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
        owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1 = modSwitch1int;
        owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
        owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;

        double y = ui->lineEdit_fspinlv->text().toDouble();
        int x = ui->lineEdit_fsygonglvkongz->text().toInt();
        double result;
        if(pattern == 1)
        {   QString appDir = QCoreApplication::applicationDirPath();
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
               owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}
        }
        else
        {
            QString appDir = QCoreApplication::applicationDirPath();
            if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
                owner->dataquery.printDataRange();

                result = owner->dataquery.interpolate(y*1000, x);
                qDebug() << "插值结果:" << result;}
        }



        owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
        owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_fsygonglvkongz->text().toInt()));



        owner->pingdian2 = ui->lineEdit_fspinlv->text();
        owner->pinpian2 = ui->lineEdit_tzbinpian->text();
        owner->tiaoz2 = ui->comboBox_tiao1->currentText();
        owner->gonglv2 = ui->lineEdit_fsygonglvkongz->text();
        owner->updateui2();


    }

    for(int i  = 0 ; i < 50 ; i++)
    {
        owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
    }


    qDebug() << owner->m_PTRANSMIT_CONFIG->freq1
             << owner->m_PTRANSMIT_CONFIG->detF1
             << owner->m_PTRANSMIT_CONFIG->ctrl1
             << owner->m_PTRANSMIT_CONFIG->powerCtrl1;

    owner->m_PPACKET_HEADER->dataLength = sizeof(TRANSMIT_CONFIG) + 12;


    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PTRANSMIT_CONFIG),
                                               sizeof(TRANSMIT_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


    int i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    owner->udpManager->sendDatagram(array);
    if(pattern == 1)
    {
       Logger::info("发射机1:配置射频参数下发");
       owner->setmaintable("发射机1:配置射频参数下发", "上位机");
    }
    else
    {
       Logger::info("发射机2:配置射频参数下发");
       owner->setmaintable("发射机2:配置射频参数下发", "上位机");
    }
    array.clear();
}

void Dialogfasheset::doWorkWithDelay(int ms)
{
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    qDebug() << time;

    QEventLoop loop;
    QTimer::singleShot(ms, &loop, &QEventLoop::quit);
    loop.exec(); // 阻塞直到定时器触发


    time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        qDebug() << time;


}

void Dialogfasheset::closeEvent(QCloseEvent *event)
{
      saveSettings();
      event->accept();
}


void Dialogfasheset::on_Btn_peziall_clicked()
{

    if(ui->lineEdit_fspinlv->text().toDouble() < 2200)
    {
        QMessageBox::information(this , "错误" , "发射频率不在合法工作范围里 , 错误");
        return;
    }

    if(ui->lineEdit_fsygonglvkongz->text().toDouble() > 10 && ui->comboBox_zai1->currentText() == "开")
    {
        QMessageBox::information(this , "提示" , "输出功率较大，请确认天线已连接");
    }

    owner->m_PPACKET_HEADER = new PACKET_HEADER;
   // owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;
   // qDebug() << QString("%1").arg(sizeof(TRANSMIT_CONFIG));

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x01;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);




    owner->m_PTELEMETRY_FRAME = new TELEMETRY_FRAME;
    if(pattern == 1)
    {
          owner->m_PTELEMETRY_FRAME->txSelector = 1;

          owner->fuzhengfangshi = ui->comboBox_fuzhenfanshi->currentText();
          owner->zhengmazu = ui->comboBox_zhenmazhu->currentText();
          owner->malv = ui->lineEdit_malv->text();
          owner->maxing = ui->comboBox_maxing->currentText();
          owner->bianmawz = ui->comboBox_bianmaweizhi->currentText();
          owner->updateui1();
    }
    else if(pattern == 2)
    {
          owner->m_PTELEMETRY_FRAME->txSelector = 2;

          owner->fuzhengfangshi2 = ui->comboBox_fuzhenfanshi->currentText();
          owner->zhengmazu2 = ui->comboBox_zhenmazhu->currentText();
          owner->malv2 = ui->lineEdit_malv->text();
          owner->maxing2 = ui->comboBox_maxing->currentText();
          owner->bianmawz2 = ui->comboBox_bianmaweizhi->currentText();
          owner->updateui2();
    }

   //* ui->lineEdit->text().toInt() / 4294967296

   long long int malv = ui->lineEdit_malv->text().toLongLong();
   quint32 byteValue32  = (owner->fo == 0) ? 0 :
                           static_cast<quint32>(
                            ui->lineEdit_malv->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                                        );
   owner->m_PTELEMETRY_FRAME->pcmRate = qToLittleEndian<quint32>(byteValue32);




   quint16 byteValue16;
   quint8 byteValue8;


   byteValue16 = static_cast<quint16>(ui->lineEdit_zhenchang->text().toInt() - 1);

   owner->m_PTELEMETRY_FRAME->subFrameLength.bit.length = qToLittleEndian<quint16>(byteValue16);


   owner->m_PTELEMETRY_FRAME->subFrameLength.bit.moFeiFlag = 0;


   if(ui->comboBox_fuzhenfanshi->currentText() == "无副帧")
   {
       byteValue8 = 0x00;
   }
   else
   {
       byteValue8 = static_cast<quint8>(ui->lineEdit_fuzhenchangdu->text().toInt() - 1);

   }

   byteValue8 = static_cast<quint8>(ui->lineEdit_fuzhenchangdu->text().toInt() - 1); // 0x01
   owner->m_PTELEMETRY_FRAME->subFrameCount = qToLittleEndian<quint16>(byteValue8);

   owner->m_PTELEMETRY_FRAME->WordConfig.bits.wordLengthMinusOne = static_cast<quint8>(ui->comboBox_zichang->currentText().toInt() - 1);
   quint8 codeType;
   if (ui->comboBox_maxing->currentText() == "NRZ-L")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000000;
   }

   else if (ui->comboBox_maxing->currentText() == "NRZ-M")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000010;
   }

   else if (ui->comboBox_maxing->currentText() == "NRZ-S")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000011;
   }
   else if (ui->comboBox_maxing->currentText() == "BIφ-L")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000100;
   }

   else if (ui->comboBox_maxing->currentText() == "BIφ-M")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000110;
   }


   else if (ui->comboBox_maxing->currentText() == "BIφ-S")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00000111;
   }

   else if (ui->comboBox_maxing->currentText() == "RNRZ-L")
   {
       owner->m_PTELEMETRY_FRAME->WordConfig.bits.codeType = 0b00001000;
   }


   byteValue16 = ui->lineEdit_fuzhenlvxu->text().toInt() - 1 ; //ID码副帧时, 副帧的ID码所在路序-1。循环码副帧时，副帧特征字在子帧的路序-1
   owner->m_PTELEMETRY_FRAME->featurePosition = qToLittleEndian<quint16>(byteValue16);

   //if(ui->checkBox_low)
   bool convertOk;
   QString processed = ui->comboBox_zhenmazhu->currentText().trimmed().toUpper();
   quint64 byteValue64 = processed.toULongLong(&convertOk , 16);
   owner->m_PTELEMETRY_FRAME->syncCode = qToLittleEndian<quint64>(byteValue64);

   processed = ui->lineEdit_xhfztongbuma->text().trimmed().toUpper();
   byteValue16 = processed.toULongLong(&convertOk , 16);
   owner->m_PTELEMETRY_FRAME->loopSyncCode = qToLittleEndian<quint16>(byteValue16);


    quint8 subframeType ;
    quint8 bitLengthMinusOne;
   if(ui->comboBox_fuzhenfanshi->currentText() == "无副帧")
   {
       subframeType = 0 ;
   }

   else if(ui->comboBox_fuzhenfanshi->currentText() == "反码副帧")
   {
       subframeType = 2 ;
   }

   else if(ui->comboBox_fuzhenfanshi->currentText() == "循环副帧")
   {
       subframeType = 1 ;
   }

   else if(ui->comboBox_fuzhenfanshi->currentText() == "ID副帧")
   {
       subframeType = 3 ;
   }

   bitLengthMinusOne = ui->comboBox_zhenmazhu->currentText().size() * 4 - 1;


   byteValue8 = (subframeType << 6) | bitLengthMinusOne ;

   owner->m_PTELEMETRY_FRAME->frameType = byteValue8;


   for(int i = 0 ; i < 5 ; i++)
   {

       owner->m_PTELEMETRY_FRAME->reserved1[i] = 0x00;
   }

   if( ui->comboBox_xinhaoneixing->currentText() == "台阶码")
   {
       byteValue8 = 0x00;
   }
   else if(ui->comboBox_xinhaoneixing->currentText() == "随机码")
   {
       byteValue8 = 0x01;
   }
   else if(ui->comboBox_xinhaoneixing->currentText() == "用户码")
   {
       byteValue8 = 0x02;
   }
   owner->m_PTELEMETRY_FRAME->dataType = qToLittleEndian<quint8>(byteValue8);


   byteValue16 = ui->lineEdit_tjmbujin->text().toInt();
   owner->m_PTELEMETRY_FRAME->stepValue = qToLittleEndian<quint8>(byteValue16);


   byteValue16 = ui->lineEdit_tjmchushizi->text().toInt();
   owner->m_PTELEMETRY_FRAME->initStep = qToLittleEndian<quint16>(byteValue16);


   if(ui->checkBox_low->isChecked())
   {
       owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 0;
   }
   else
   {
       owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.notCountEnable = 1;
   }

   if(ui->checkBox_high->isChecked())
   {
       owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 0;
   }
   else
   {
       owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.notCountEnable = 1;
   }


   byteValue16 = ui->lineEdit_zjsdzjbodao->text().toInt();
   owner->m_PTELEMETRY_FRAME->FrameCalcChannel.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;


   byteValue16 = ui->lineEdit_zjsgzjbodao->text().toInt();
   owner->m_PTELEMETRY_FRAME->frameCalcChannelhigh.bits.frameCountLowByteIndex = qToLittleEndian<quint16>(byteValue16) - 1;

   for(int i = 0 ; i < 4 ; i++)
   {
       owner->m_PTELEMETRY_FRAME->reserved2[i] = 0x00;
   }





   if(ui->comboBox_IDzijishufangshi->currentText() == "加计数")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x00;
   }
   else if(ui->comboBox_IDzijishufangshi->currentText() == "减计数")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit1 = 0x01;
   }

   if(ui->comboBox_IDzijizhi->currentText() == "0开始")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x00;
   }
   else if(ui->comboBox_IDzijizhi->currentText() == "1开始")
   {
       owner->m_PTELEMETRY_FRAME->bits.bit0 = 0x01;
   }
  owner->m_PTELEMETRY_FRAME->bits.reserved = 0x00;


  if(ui->comboBox_bianmaweizhi->currentText() == "编码前")
  {
      owner->m_PTELEMETRY_FRAME->codingPosition = 0x01;

  }
  else if(ui->comboBox_bianmaweizhi->currentText() == "编码后")
  {
      owner->m_PTELEMETRY_FRAME->codingPosition = 0x00;
  }


   for(int i = 0 ; i < 22 ; i++)
   {
       owner->m_PTELEMETRY_FRAME->reserved3[i] = 0x00;
   }

   QByteArray array;
   array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                  sizeof(PACKET_HEADER));
   array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_FRAME),
                                                sizeof(TELEMETRY_FRAME));//    quint8  txSelector;        // 发射机选择 [1B]

   quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
   m_crc32 = qToLittleEndian<quint32>(m_crc32);
   array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

   int i  = 1 ;
   for (quint8 byte : array) {
                 QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                 qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
             }

   owner->udpManager->sendDatagram(array);
   if(pattern == 1)
   {
      Logger::info("发射机1:配置帧格式下发");
      owner->setmaintable("发射机1:配置帧格式下发" , "上位机");
   }
   else
   {
      Logger::info("发射机2:配置帧格式下发");
      owner->setmaintable(QString("发射机2:配置帧格式下发"), "上位机");
   }

   delete owner->m_PPACKET_HEADER;
   //owner->m_PTRANSMIT_CONFIG = nullptr;

   array.clear();

       owner->m_PPACKET_HEADER = new PACKET_HEADER;
       //owner->m_PTRANSMIT_CONFIG = new TRANSMIT_CONFIG;

       owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
       owner->m_PPACKET_HEADER->functionCode = 0x03;
       owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
       owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
       owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

       if(pattern == 1)
       {
           owner->m_PTRANSMIT_CONFIG->txSelector = 0x01;
           double texttodub = ui->lineEdit_fspinlv->text().toDouble();
           owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));

           qDebug() << owner->m_PTRANSMIT_CONFIG->freq1;

           //texttoint = ui->lineEdit_tzbinpian->text().toInt();
           int  texttoint = (owner->fo == 0) ? 0 :
                                               static_cast<quint32>(
                                                   ui->lineEdit_tzbinpian->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                               );
           owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
           owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
           quint8 tiaozhifangshiint;
           quint8 modPolarity1int;
           quint8 modSwitch1int;
           quint8 carrier1int;
           if(ui->comboBox_tiao1->currentText() == "FM调制")
           {
               tiaozhifangshiint =0b0000;
           }
           else if(ui->comboBox_tiao1->currentText() == "BPSK调制")
           {
               tiaozhifangshiint =0b0001;
           }
           else if(ui->comboBox_tiao1->currentText() == "QPSK调制")
           {
               tiaozhifangshiint =0b0010;
           }

           if(ui->comboBox_zai1->currentText() == "开")
           {
               carrier1int = 1;
           }
           else if(ui->comboBox_zai1->currentText() == "关")
           {
               carrier1int = 0;
           }

           if(ui->comboBox_tiaokai1->currentText() == "开")
           {
               modSwitch1int = 1;
           }
           else if(ui->comboBox_tiaokai1->currentText() == "关")
           {
               modSwitch1int = 0;
           }

           if(ui->comboBox_tiaoji1->currentText() == "正")
           {
               modPolarity1int = 0;
           }
           else if(ui->comboBox_tiaoji1->currentText() == "负")
           {
               modPolarity1int = 1;
           }
           owner->m_PTRANSMIT_CONFIG->bits1.bit0  = 0;
           owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
           owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1   =   modSwitch1int;
           owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
           owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;


           double y = ui->lineEdit_fspinlv->text().toDouble();
           int x = ui->lineEdit_fsygonglvkongz->text().toInt();
           if(x < 6)
           {
              x = 6;
           }

           double result;
           if(pattern == 1)
           {
               QString appDir = QCoreApplication::applicationDirPath();
               if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
                  owner->dataquery.printDataRange();

                   result = owner->dataquery.interpolate(y*1000, x);
                   qDebug() << "插值结果:" << result;}
           }
           else
           {
               QString appDir = QCoreApplication::applicationDirPath();
               if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
                   owner->dataquery.printDataRange();

                   result = owner->dataquery.interpolate(y*1000, x);
                   qDebug() << "插值结果:" << result;}
           }
           owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
           owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_fsygonglvkongz->text().toInt()));


           for(int i= 0 ; i < 50 ; i++)
           {
               owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
           }


           owner->pingdian = ui->lineEdit_fspinlv->text();
           owner->pinpian = ui->lineEdit_tzbinpian->text();
           owner->tiaoz = ui->comboBox_tiao1->currentText();
           owner->gonglv = ui->lineEdit_fsygonglvkongz->text();
           owner->updateui1();

       }
       else if(pattern == 2)
       {
           owner->m_PTRANSMIT_CONFIG->txSelector = 0x02;
           double texttodub = ui->lineEdit_fspinlv->text().toDouble();
           owner->m_PTRANSMIT_CONFIG->freq1 = qToLittleEndian<quint32>(static_cast<quint32>(texttodub * 1000));

           qDebug() << owner->m_PTRANSMIT_CONFIG->freq1;

           //texttoint = ui->lineEdit_tzbinpian->text().toInt();
           int  texttoint = (owner->fo == 0) ? 0 :
                                               static_cast<quint32>(
                                                   ui->lineEdit_tzbinpian->text().toDouble() * 1000.0 * 4294967296.0 / owner->fo
                                               );
           owner->m_PTRANSMIT_CONFIG->detF1 = qToLittleEndian<quint32>(static_cast<quint32>(texttoint));
           owner->m_PTRANSMIT_CONFIG->reserved1 = qToLittleEndian<quint16>(static_cast<quint16>(0x00));
           quint8 tiaozhifangshiint = '\0';
           quint8 modPolarity1int;
           quint8 modSwitch1int;
           quint8 carrier1int;
           if(ui->comboBox_tiao1->currentText() == "FM调制")
           {
               tiaozhifangshiint =0b0000;
           }
           else if(ui->comboBox_tiao1->currentText() == "BPSK调制")
           {
               tiaozhifangshiint =0b0001;
           }
           else if(ui->comboBox_tiao1->currentText() == "QPSK调制")
           {
               tiaozhifangshiint =0b0010;
           }

           if(ui->comboBox_zai1->currentText() == "开")
           {
               carrier1int = 1;
           }
           else if(ui->comboBox_zai1->currentText() == "关")
           {
               carrier1int = 0;
           }

           if(ui->comboBox_tiaokai1->currentText() == "开")
           {
               modSwitch1int = 1;
           }
           else if(ui->comboBox_tiaokai1->currentText() == "关")
           {
               modSwitch1int = 0;
           }

           if(ui->comboBox_tiaoji1->currentText() == "正")
           {
               modPolarity1int = 0;
           }
           else if(ui->comboBox_tiaoji1->currentText() == "负")
           {
               modPolarity1int = 1;
           }
           owner->m_PTRANSMIT_CONFIG->bits1.modPolarity1 = modPolarity1int;
           owner->m_PTRANSMIT_CONFIG->bits1.modSwitch1 = modSwitch1int;
           owner->m_PTRANSMIT_CONFIG->bits1.carrier1 = carrier1int;
           owner->m_PTRANSMIT_CONFIG->bits1.modType1 = tiaozhifangshiint;

           double y = ui->lineEdit_fspinlv->text().toDouble();
           int x = ui->lineEdit_fsygonglvkongz->text().toInt();
           if(x < 6)
           {
              x = 6;
           }


           double result;
           if(pattern == 1)
           {
               QString appDir = QCoreApplication::applicationDirPath();
               if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter1.txt")) {
                  owner->dataquery.printDataRange();

                   result = owner->dataquery.interpolate(y*1000, x);
                   qDebug() << "插值结果:" << result;}
           }
           else
           {
               QString appDir = QCoreApplication::applicationDirPath();
               if (owner->dataquery.loadData(appDir + "/taskconfig/Transmitter2.txt")) {
                   owner->dataquery.printDataRange();

                   result = owner->dataquery.interpolate(y*1000, x);
                   qDebug() << "插值结果:" << result;}
           }



           owner->m_PTRANSMIT_CONFIG->powerCtrl1 = qToLittleEndian<quint8>(static_cast<quint8>(qRound(result)));
           owner->m_PTRANSMIT_CONFIG->powerCtrl1_UI = qToLittleEndian<quint8>(static_cast<quint8>(ui->lineEdit_fsygonglvkongz->text().toInt()));

           owner->pingdian2 = ui->lineEdit_fspinlv->text();
           owner->pinpian2 = ui->lineEdit_tzbinpian->text();
           owner->tiaoz2 = ui->comboBox_tiao1->currentText();
           owner->gonglv2 = ui->lineEdit_fsygonglvkongz->text();
           owner->updateui2();


       }

       for(int i  = 0 ; i < 50 ; i++)
       {
           owner->m_PTRANSMIT_CONFIG->reserved3[i] = 0x00;
       }



       array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                    sizeof(PACKET_HEADER));
       array.append(reinterpret_cast<const char*>(owner->m_PTRANSMIT_CONFIG),
                                                                sizeof(TRANSMIT_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

       m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
       m_crc32 = qToLittleEndian<quint32>(m_crc32);
       array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


       i  = 1 ;
       for (quint8 byte : array) {
                     QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                     qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                 }


       owner->udpManager->sendDatagram(array);
       if(pattern == 1)
       {
          Logger::info("发射机1:配置射频参数下发");
          owner->setmaintable("发射机1:配置射频参数下发", "上位机");
       }
       else
       {
          Logger::info("发射机2:配置射频参数下发");
          owner->setmaintable("发射机2:配置射频参数下发", "上位机");
       }

       delete owner->m_PPACKET_HEADER;
       //owner->m_PTRANSMIT_CONFIG = nullptr;

       array.clear();

       owner->m_PTELEMETRY_ENCODING_CONFIG = new TELEMETRY_ENCODING_CONFIG;
       owner->m_PPACKET_HEADER = new PACKET_HEADER;

       owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
       owner->m_PPACKET_HEADER->functionCode = 0x05;
       owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
       owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
       owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

       if(pattern == 1)
       {
           owner->m_PTELEMETRY_ENCODING_CONFIG->txSelector = 0x01;
       }
       else if(pattern == 2)
       {
           owner->m_PTELEMETRY_ENCODING_CONFIG->txSelector = 0x02;
       }
       quint8 LDPC;
       if(ui->comboBox_bianma->currentText() == "LDPC")
       {
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 1;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
       }
       else if(ui->comboBox_bianma->currentText() == "TPC")
       {
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 1;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
       }
       else if(ui->comboBox_bianma->currentText() == "RS")
       {
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 1;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
       }
       else if(ui->comboBox_bianma->currentText() == "卷积")
       {
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.ldpcEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.tpcEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.rsEnable = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.convEnable = 1;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved1 = 0;
           owner->m_PTELEMETRY_ENCODING_CONFIG->codeBits.reserved2 = 0;
       }
       else if(ui->comboBox_bianma->currentText() == "关闭")
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




       if(ui->Edit_TPCtongbuma->text().isEmpty())
       {
           Btyevalue32 = 0x1ACFFC1D;
       }
       else
       {
           processed = ui->Edit_TPCtongbuma->text().trimmed().toUpper();
           Btyevalue32 = processed.toULongLong(&convertOk , 16);

       }

       if(ui->Edit_youxiaobiaozi->text().isEmpty())
       {
           Btyevalue16 = 0xFFFF;
       }
       else
       {

           processed = ui->Edit_youxiaobiaozi->text().trimmed().toUpper();
           Btyevalue16 = processed.toULongLong(&convertOk , 16);
       }


        owner->m_PTELEMETRY_ENCODING_CONFIG->tpcSyncCode =  qToLittleEndian<quint32>(static_cast<quint32>(Btyevalue32));
        owner->m_PTELEMETRY_ENCODING_CONFIG->tpcValidFlag=  qToLittleEndian<quint16>(static_cast<quint16>(Btyevalue16));


        for(int i = 0 ;  i < 53 ; i++)
        {
            owner->m_PTELEMETRY_ENCODING_CONFIG->padding[i] = 0x00;
        }





        array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                     sizeof(PACKET_HEADER));
        array.append(reinterpret_cast<const char*>(owner->m_PTELEMETRY_ENCODING_CONFIG),
                                                                 sizeof(TELEMETRY_ENCODING_CONFIG));//    quint8  txSelector;        // 发射机选择 [1B]

        m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
        m_crc32 = qToLittleEndian<quint32>(m_crc32);
        array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));


        i  = 1 ;
        for (quint8 byte : array) {
                      QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                      qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                  }

        owner->udpManager->sendDatagram(array);
        if(pattern == 1)
        {
           Logger::info("发射机1:配置信道编码下发");
           owner->setmaintable("发射机1:配置信道编码下发","上位机");
        }
        else
        {
            Logger::info("发射机2:配置信道编码下发");
            owner->setmaintable("发射机2:配置信道编码下发","上位机");
        }

        delete owner->m_PTELEMETRY_ENCODING_CONFIG;
        owner->m_PPACKET_HEADER = nullptr;

        array.clear();

        on_Btn_Application_clicked();



        owner->m_PPACKET_HEADER = new PACKET_HEADER;

        owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
        owner->m_PPACKET_HEADER->functionCode = 0x09;
        owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
        owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
        owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

        owner->m_PAsyncSourceConfig = new AsyncSourceConfig;

        owner->m_PAsyncSourceConfig->txSelector = pattern;
        owner->m_PAsyncSourceConfig->entryCount = asynum;


        for(int i =0 ; i < asynum ; i++)
        {
            if(ui->tableWidget_yibuyuan->item(i , 6)->text().toInt() == 0)
            {
                QMessageBox::information(this , "提示" ,"帧长度不能为0");
                return;
            }




            bool conversionOk;
            owner->m_PAsyncSourceConfig->entries[i].syncCode = ui->tableWidget_yibuyuan->item(i , 1)->text().trimmed().toUpper().toUInt(&conversionOk , 16);

            if(ui->tableWidget_yibuyuan->item(i , 3)->text().toInt() == 0)
            {
                owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = 0;
            }
            else
            {
                owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = ui->tableWidget_yibuyuan->item(i , 3)->text().toInt() - 1;
            }

            if(ui->tableWidget_yibuyuan->item(i , 4)->text() == "台阶码")
            {
                  owner->m_PAsyncSourceConfig->entries[i].dataType = 0x00;
            }
            else if(ui->tableWidget_yibuyuan->item(i , 4)->text() == "随机码")
            {
                  owner->m_PAsyncSourceConfig->entries[i].dataType = 0x01;
            }
            else if(ui->tableWidget_yibuyuan->item(i , 4)->text() == "用户码")
            {
                  owner->m_PAsyncSourceConfig->entries[i].dataType = 0x02;
            }

            owner->m_PAsyncSourceConfig->entries[i].stepIncrement = ui->tableWidget_yibuyuan->item(i , 5)->text().toInt() ;
            owner->m_PAsyncSourceConfig->entries[i].initialValue = ui->tableWidget_yibuyuan->item(i , 6)->text().toInt();

            owner->m_PAsyncSourceConfig->entries[i].frameLength = ui->tableWidget_yibuyuan->item(i , 2)->text().toInt() - 1;

            owner->m_PAsyncSourceConfig->entries[i].syncCodeLength = ui->tableWidget_yibuyuan->item(i , 1)->text().size()/2;

            owner->m_PAsyncSourceConfig->entries[i].frameCounterLength = ui->tableWidget_yibuyuan->item(i , 7)->text().toInt() - 1;
            owner->m_PAsyncSourceConfig->entries[i].zhenlv = ui->tableWidget_yibuyuan->item(i , 8)->text().toInt();



        }

        for(int i = asynum ; i < 10 ; i++)
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



        array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                       sizeof(PACKET_HEADER));
        array.append(reinterpret_cast<const char*>(owner->m_PAsyncSourceConfig),
                                                     sizeof(AsyncSourceConfig));//    quint8  txSelector;        // 发射机选择 [1B]

        m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
        m_crc32 = qToLittleEndian<quint32>(m_crc32);
        array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

        i = 1 ;
        for (quint8 byte : array) {
                      QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                      qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
                  }

        qDebug() << asynum << anysum;

        owner->udpManager->sendDatagram(array);
        if(pattern == 1)
        {
           Logger::info("发射机1:配置异步源下发");
           owner->setmaintable("发射机1:配置异步源下发" , "上位机");
        }
        else
        {
           Logger::info("发射机2:配置异步源下发");
           owner->setmaintable(QString("发射机2:配置异步源下发"), "上位机");
        }



        fasheping(pattern);







}

void Dialogfasheset::on_Btn_new_clicked()
{
    anysum++;


    if(anysum > 10)
    {
        QMessageBox::information(this , "警告" , "当前只支持10条");
        anysum = 10;
        return ;
    }

    ui->tableWidget_pcm->setRowCount(anysum);

    QSettings settings("settings.ini", QSettings::IniFormat);


    if(pattern == 1)
    {
        // 加载主设置
        settings.beginGroup(QString("fa1pcmtab"));

            ui->tableWidget_pcm->setItem(anysum-1 , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(anysum), "数据块").toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 1 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(anysum), "子帧模式").toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 2 ,new QTableWidgetItem(settings.value(QString("fuzhenweizhi%1").arg(anysum), 1).toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 3 ,new QTableWidgetItem(settings.value(QString("zizhenweizhi%1").arg(anysum), 1).toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 4 ,new QTableWidgetItem(settings.value(QString("datafrom%1").arg(anysum), "异步源").toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 5 ,new QTableWidgetItem(settings.value(QString("fangzhiLength%1").arg(anysum), 10).toString()));

        settings.endGroup();
    }

    else if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2pcmtab"));

            ui->tableWidget_pcm->setItem(anysum-1 , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(anysum), "异步源1").toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 1 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(anysum), "子帧模式").toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 2 ,new QTableWidgetItem(settings.value(QString("fuzhenweizhi%1").arg(anysum), 1).toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 3 ,new QTableWidgetItem(settings.value(QString("zizhenweizhi%1").arg(anysum), 1).toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 4 ,new QTableWidgetItem(settings.value(QString("datafrom%1").arg(anysum), "异步源").toString()));
            ui->tableWidget_pcm->setItem(anysum-1 , 5 ,new QTableWidgetItem(settings.value(QString("fangzhiLength%1").arg(anysum), 10).toString()));

        settings.endGroup();
    }
}

void Dialogfasheset::on_Btn_delete_clicked()
{
    if(anysum <= 0)
    {
        anysum = 0;
        return;
    }






    QSettings settings("settings.ini", QSettings::IniFormat);

    if(pattern == 1)
    {
        // 加载主设置
        settings.beginGroup(QString("fa1pcmtab"));

        settings.setValue("anysum",anysum);

            settings.setValue(QString("name%1").arg(anysum),"数据块");
            settings.setValue(QString("zhenmoshi%1").arg(anysum),"子帧模式");
            settings.setValue(QString("fuzhenweizhi%1").arg(anysum),1);
            settings.setValue(QString("zizhenweizhi%1").arg(anysum),1);
            settings.setValue(QString("datafrom%1").arg(anysum),"异步源");
            settings.setValue(QString("fangzhiLength%1").arg(anysum),10);



        settings.endGroup();
    }

    if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2pcmtab"));

        settings.setValue("anysum",anysum);

            settings.setValue(QString("name%1").arg(anysum),"数据块");
            settings.setValue(QString("zhenmoshi%1").arg(anysum),"子帧模式");
            settings.setValue(QString("fuzhenweizhi%1").arg(anysum),1);
            settings.setValue(QString("zizhenweizhi%1").arg(anysum),1);
            settings.setValue(QString("datafrom%1").arg(anysum),"异步源");
            settings.setValue(QString("fangzhiLength%1").arg(anysum),10);



        settings.endGroup();
    }


    anysum--;

    ui->tableWidget_pcm->setRowCount(anysum);
}



void Dialogfasheset::on_Btn_delete_2_clicked()
{

    if(asynum <= 0)
    {
        asynum = 0;
        return;
    }


    QSettings settings("settings.ini", QSettings::IniFormat);


    if(pattern == 1)
    {
        // 加载主设置
        settings.beginGroup(QString("fa1yibuyuantab"));

        settings.setValue("asynum",asynum);

            settings.setValue(QString("name%1").arg(asynum),"异步源1");
            settings.setValue(QString("tongbuma%1").arg(asynum),"146f");
            settings.setValue(QString("zhenmoshi%1").arg(asynum), 12);
            settings.setValue(QString("ankonglocation%1").arg(asynum),10);
            settings.setValue(QString("shujuliexing%1").arg(asynum),"台阶码");
            settings.setValue(QString("taijiemabujin%1").arg(asynum),10);
            settings.setValue(QString("taijiemainit%1").arg(asynum),1);
          //  settings.setValue(QString("tongbumalength%1").arg(asynum),10);
            settings.setValue(QString("zhenjishulength%1").arg(asynum),10);
            settings.setValue(QString("zhenlv%1").arg(asynum),100);




        settings.endGroup();
    }

    if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2yibuyuantab"));

        settings.setValue("asynum",asynum);

        settings.setValue(QString("name%1").arg(asynum),"异步源1");
        settings.setValue(QString("tongbuma%1").arg(asynum),"146f");
        settings.setValue(QString("zhenmoshi%1").arg(asynum), 12);
        settings.setValue(QString("ankonglocation%1").arg(asynum),10);
        settings.setValue(QString("shujuliexing%1").arg(asynum),"台阶码");
        settings.setValue(QString("taijiemabujin%1").arg(asynum),10);
        settings.setValue(QString("taijiemainit%1").arg(asynum),1);
       // settings.setValue(QString("tongbumalength%1").arg(asynum),10);
        settings.setValue(QString("zhenjishulength%1").arg(asynum),10);
        settings.setValue(QString("zhenlv%1").arg(asynum),100);



        settings.endGroup();

    }
    asynum--;
    ui->tableWidget_yibuyuan->setRowCount(asynum);
}

void Dialogfasheset::on_Btn_new_2_clicked()
{
    asynum++;


    if(asynum > 10)
    {
        QMessageBox::information(this , "警告" , "当前只支持10条");
        asynum = 10;
        return ;
    }

    ui->tableWidget_yibuyuan->setRowCount(asynum);

    QSettings settings("settings.ini", QSettings::IniFormat);




    if(pattern == 1)
    {
             // 加载主设置
            settings.beginGroup(QString("fa1yibuyuantab"));

            ui->tableWidget_yibuyuan->setItem(asynum-1 , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(asynum), "异步源1").toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 1 ,new QTableWidgetItem(settings.value(QString("tongbuma%1").arg(asynum), "146f").toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 2 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(asynum), 12).toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 3 ,new QTableWidgetItem(settings.value(QString("ankonglocation%1").arg(asynum), 10).toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 4 ,new QTableWidgetItem(settings.value(QString("shujuliexing%1").arg(asynum), "台阶码").toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 5 ,new QTableWidgetItem(settings.value(QString("taijiemabujin%1").arg(asynum), 1).toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 6 ,new QTableWidgetItem(settings.value(QString("taijiemainit%1").arg(asynum), 3).toString()));
     //       ui->tableWidget_yibuyuan->setItem(asynum-1 , 7 ,new QTableWidgetItem(settings.value(QString("tongbumalength%1").arg(asynum), 8).toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 7 ,new QTableWidgetItem(settings.value(QString("zhenjishulength%1").arg(asynum), 10).toString()));
            ui->tableWidget_yibuyuan->setItem(asynum-1 , 8 ,new QTableWidgetItem(settings.value(QString("zhenlv%1").arg(asynum), 100).toString()));

        settings.endGroup();
    }

    else if(pattern == 2)
    {
        // 加载主设置
        settings.beginGroup(QString("fa2yibuyuantab"));

        ui->tableWidget_yibuyuan->setItem(asynum-1 , 0 ,new QTableWidgetItem(settings.value(QString("name%1").arg(asynum), "异步源1").toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 1 ,new QTableWidgetItem(settings.value(QString("tongbuma%1").arg(asynum), "146f").toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 2 ,new QTableWidgetItem(settings.value(QString("zhenmoshi%1").arg(asynum), 12).toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 3 ,new QTableWidgetItem(settings.value(QString("ankonglocation%1").arg(asynum), 10).toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 4 ,new QTableWidgetItem(settings.value(QString("shujuliexing%1").arg(asynum), "台阶码").toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 5 ,new QTableWidgetItem(settings.value(QString("taijiemabujin%1").arg(asynum), 1).toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 6 ,new QTableWidgetItem(settings.value(QString("taijiemainit%1").arg(asynum), 3).toString()));
     //   ui->tableWidget_yibuyuan->setItem(asynum-1 , 7 ,new QTableWidgetItem(settings.value(QString("tongbumalength%1").arg(asynum), 8).toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 7 ,new QTableWidgetItem(settings.value(QString("zhenjishulength%1").arg(asynum), 10).toString()));
        ui->tableWidget_yibuyuan->setItem(asynum-1 , 8 ,new QTableWidgetItem(settings.value(QString("zhenlv%1").arg(asynum), 100).toString()));
        settings.endGroup();
    }
}

void Dialogfasheset::on_Btn_Application_clicked()
{


    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x07;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

    owner->m_PPCMEMBEDCONfIG = new PCMEMBEDCONfIG;

    owner->m_PPCMEMBEDCONfIG->txSelector = pattern;
    owner->m_PPCMEMBEDCONfIG->entryCount = anysum;

    qDebug() << anysum;

    for(int i =0 ; i < anysum ; i++)
    {
        if(ui->tableWidget_pcm->item(i , 1)->text() == "子帧模式")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x00;
            owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos = 0x00;
        }
        else if(ui->tableWidget_pcm->item(i , 1)->text() == "副帧模式")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.mode = 0x01;
            if(ui->tableWidget_pcm->item(i , 5)->text().toInt() == 0)
            {
                QMessageBox::information(this , "提示" , "副帧模式:副帧长度不能为0");
                return;
            }
            owner->m_PPCMEMBEDCONfIG->entries[i].subFramePos = ui->tableWidget_pcm->item(i , 2)->text().toInt() - 1;
        }

        owner->m_PPCMEMBEDCONfIG->entries[i].ctrlBits.reserved = 0x00;



        owner->m_PPCMEMBEDCONfIG->entries[i].childFramePos = ui->tableWidget_pcm->item(i , 3)->text().toInt() - 1;

        if(ui->tableWidget_pcm->item(i , 4)->text() == "异步源")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x01;
        }
        else if(ui->tableWidget_pcm->item(i , 4)->text() == "GNSS")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x02;
        }
        else if(ui->tableWidget_pcm->item(i , 4)->text() == "安控状态")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x03;
        }
        else if(ui->tableWidget_pcm->item(i , 4)->text() == "安控自检")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x04;
        }
        else if(ui->tableWidget_pcm->item(i , 4)->text() == "安控复位")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x05;
        }
        else if(ui->tableWidget_pcm->item(i , 4)->text() == "安控解锁")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x06;
        }
        else if(ui->tableWidget_pcm->item(i , 4)->text() == "安控自毁")
        {
            owner->m_PPCMEMBEDCONfIG->entries[i].dataSource = 0x07;
        }
        owner->m_PPCMEMBEDCONfIG->entries[i].entryReserved = 0x00;
        owner->m_PPCMEMBEDCONfIG->entries[i].dataLength = ui->tableWidget_pcm->item(i , 5)->text().toInt();

         if(ui->tableWidget_pcm->item(i , 5)->text().toInt() == 0)
         {
             QMessageBox::information(this , "提示" , "放置长度不能为0");
             return;
         }

    }

    for(int i = anysum ; i < 10 ; i++)
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
    if(pattern == 1)
    {
       Logger::info("发射机1:配置pcm下发");
       owner->setmaintable("发射机1:配置pcm下发" , "上位机");
    }
    else
    {
       Logger::info("发射机2:配置pcm下发");
       owner->setmaintable(QString("发射机2:配置pcm下发"), "上位机");
    }

}

void Dialogfasheset::on_Btn_Application_2_clicked()
{
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x09;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);

    owner->m_PAsyncSourceConfig = new AsyncSourceConfig;

    owner->m_PAsyncSourceConfig->txSelector = pattern;
    owner->m_PAsyncSourceConfig->entryCount = asynum;

    qDebug() << asynum;

    for(int i =0 ; i < asynum ; i++)
    {
        if(ui->tableWidget_yibuyuan->item(i , 6)->text().toInt() == 0)
        {
            QMessageBox::information(this , "提示" ,"帧长度不能为0");
            return;
        }




        bool conversionOk;
        owner->m_PAsyncSourceConfig->entries[i].syncCode = ui->tableWidget_yibuyuan->item(i , 1)->text().trimmed().toUpper().toUInt(&conversionOk , 16);

        if(ui->tableWidget_yibuyuan->item(i , 3)->text().toInt() == 0)
        {
            owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = 0;
        }
        else
        {
            owner->m_PAsyncSourceConfig->entries[i].Securitycontrolposition = ui->tableWidget_yibuyuan->item(i , 3)->text().toInt() - 1;
        }

        if(ui->tableWidget_yibuyuan->item(i , 4)->text() == "台阶码")
        {
              owner->m_PAsyncSourceConfig->entries[i].dataType = 0x00;
        }
        else if(ui->tableWidget_yibuyuan->item(i , 4)->text() == "随机码")
        {
              owner->m_PAsyncSourceConfig->entries[i].dataType = 0x01;
        }
        else if(ui->tableWidget_yibuyuan->item(i , 4)->text() == "用户码")
        {
              owner->m_PAsyncSourceConfig->entries[i].dataType = 0x02;
        }

        owner->m_PAsyncSourceConfig->entries[i].stepIncrement = ui->tableWidget_yibuyuan->item(i , 5)->text().toInt() ;
        owner->m_PAsyncSourceConfig->entries[i].initialValue = ui->tableWidget_yibuyuan->item(i , 6)->text().toInt();

        owner->m_PAsyncSourceConfig->entries[i].frameLength = ui->tableWidget_yibuyuan->item(i , 2)->text().toInt() - 1;

        owner->m_PAsyncSourceConfig->entries[i].syncCodeLength = ui->tableWidget_yibuyuan->item(i , 1)->text().size()/2;

        owner->m_PAsyncSourceConfig->entries[i].frameCounterLength = ui->tableWidget_yibuyuan->item(i , 7)->text().toInt() - 1;
        owner->m_PAsyncSourceConfig->entries[i].zhenlv = ui->tableWidget_yibuyuan->item(i , 8)->text().toInt();



    }

    for(int i = asynum ; i < 10 ; i++)
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

    int i  = 1 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }

    owner->udpManager->sendDatagram(array);
    if(pattern == 1)
    {
       Logger::info("发射机1:配置异步源下发");
       owner->setmaintable("发射机1:配置异步源下发" , "上位机");
    }
    else
    {
       Logger::info("发射机2:配置异步源下发");
       owner->setmaintable(QString("发射机2:配置异步源下发"), "上位机");
    }

}

void Dialogfasheset::on_pushButton_selsetxlsx_clicked()
{
        // 从设置加载上次路径
        QSettings settings("settings.ini", QSettings::IniFormat);
        QString lastPath3 = settings.value("lastPath3", QDir::homePath()).toString();

        QString pathandname =  QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        lastPath3,
                                                        tr("Text Files (*.xlsx);;All Files (*)"));


        if (!pathandname.isEmpty()) {
            // 提取目录路径
            QString path = QFileInfo(pathandname).absolutePath();

            // 保存新路径
            settings.setValue("lastPath3", path);


        }


    ui->lineEdit_xlsxpathname->setText(pathandname);
}

void Dialogfasheset::on_Btn_zhuangzai_clicked()
{
    QByteArray result;
    QString filePath  = ui->lineEdit_xlsxpathname->text();
    if (!QFile::exists(filePath)) {
            qWarning() << "文件不存在:" << filePath;
            return ;
        }

        // 创建文档对象并加载文件
        QXlsx::Document xlsx(filePath);
        if (xlsx.sheetNames().isEmpty()) {
            qWarning() << "无法加载Excel文件:" << filePath;
            return ;
        }

        // 获取所有工作表名称
            QStringList sheetNames = xlsx.sheetNames();
            qDebug() << "工作表列表:" << sheetNames.join(", ");
            qDebug() << "========================\n";


            QString sheetName = "发射机PCM"; // 设置默认值
              if (!sheetNames.contains(sheetName)) {
                  // 尝试查找名称包含"PCM"或"发射机"的工作表
                  QStringList filteredNames = sheetNames.filter("PCM", Qt::CaseInsensitive);
                  if (filteredNames.isEmpty()) {
                      filteredNames = sheetNames.filter("发射机", Qt::CaseInsensitive);
                  }

                  if (!filteredNames.isEmpty()) {
                      sheetName = filteredNames.first();
                      qWarning() << "警告: 未找到'发射机1PCM'工作表，将使用 '" << sheetName << "'";
                  } else {
                      qCritical() << "错误: 未找到'发射机1PCM'工作表，可用工作表: " << sheetNames.join(", ");
                      return ;
                  }
              }

              // 5. 选择工作表
              if (!xlsx.selectSheet(sheetName)) {
                  qCritical() << "错误: 无法选择工作表 '" << sheetName << "'";
                  return ;
              }

              int minRow = 0, minCol = 0;
              int maxRow = 0, maxCol = 0;

              // 6. 获取工作表的有效数据范围
              QXlsx::CellRange range = xlsx.dimension();


             int rowCount = range.lastRow() - range.firstRow() + 1;
             int colCount = range.lastColumn() - range.firstColumn() + 1;

             minRow = range.firstRow();
             minCol = range.firstColumn();
             maxRow = range.lastRow();
             maxCol = range.lastColumn();


             qDebug() << "总行数: " << rowCount;
             qDebug() << "总列数: " << colCount;


             for (int row = minRow; row <= maxRow; ++row) {
                     for (int col = minCol; col <= maxCol; ++col) {
                         // 跳过空单元格
                         QXlsx::Cell* cell = xlsx.cellAt(row, col);
                         if (!cell) continue;

                         // 将单元格数据转为字符串（假设都是文本）
                         QString textValue = cell->value().toString();
                         int len = textValue.length();

                         // 确保处理偶数长度的字符串
                         if (len % 2 != 0) {
                             qWarning() << "Odd length hex string found in cell (" << row << "," << col << "). Adding zero prefix.";
                             textValue = "0" + textValue;  // 补齐为偶数长度
                             len = textValue.length();
                         }

                         // 两两分组转换为十六进制字节
                         for (int i = 0; i < len; i += 2) {
                             QString hexPair = textValue.mid(i, 2);
                             bool ok;
                             char byteVal = static_cast<char>(hexPair.toInt(&ok, 16));
                             if (!ok) {
                                 qWarning() << "Invalid hex char in cell (" << row << "," << col << "):" << hexPair;
                                 byteVal = 0;  // 无效字符用0代替
                             }
                             result.append(byteVal);
                         }
                     }
                 }

//             qDebug() << result.toHex();

             owner->m_PPACKET_HEADER = new PACKET_HEADER;
             //QByteArray result; // 假设这是要发送的数据
             int totalPackets = (result.size() + 1399) / 1400;  // 更精确计算分包数量
             int dataOffset = 0;

             for(int packetIndex = 1 ; packetIndex <= totalPackets ; packetIndex++) {
                 // 重置包头结构体（重要！避免残留值）
                 memset(owner->m_PPACKET_HEADER, 0, sizeof(PACKET_HEADER));

                 // 设置包头字段（统一使用小端序）
                 owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
                 owner->m_PPACKET_HEADER->functionCode = 0x0F;
                 owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(totalPackets);
                 owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(packetIndex);

                 // 获取当前分片数据
                 int fragmentSize = (dataOffset + 1400) <= result.size()
                                   ? 1400
                                   : result.size() - dataOffset;
                 QByteArray dataFragment = result.mid(dataOffset, fragmentSize);
                 dataOffset += fragmentSize;  // 更新偏移量

                 // 动态计算数据长度（包头之后到CRC之前的数据长度）
                 int dataLength = fragmentSize + 15;          // 实际数据

                 owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(dataLength);

                 QByteArray packet;


                 // 添加包头（二进制安全方式）
                 packet.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                               sizeof(PACKET_HEADER));

                 // 添加模式标识
                 packet.append(static_cast<char>(pattern == 1 ? 0x01 : 0x02));

                 // 添加固定0x00
                 packet.append(static_cast<char>(0x00));

                 packet.append(static_cast<char>(0x00));

                 // 添加数据分片
                 packet.append(dataFragment);

                 // 计算CRC（对整个包内容计算）
                 quint32 crcValue = owner->crc32(packet);
                 crcValue = qToLittleEndian<quint32>(crcValue);

                 // 添加CRC校验
                 packet.append(reinterpret_cast<const char*>(&crcValue), sizeof(quint32));

//                 // 调试输出（建议只在开发时开启）
//                  qDebug() << "Packet" << packetIndex << ":" << packet.toHex();

                 // 发送数据包
                 owner->udpManager->sendDatagram(packet);
             }








             QString sheetName2 = "发射机异步"; // 设置默认值
               if (!sheetNames.contains(sheetName2)) {
                   // 尝试查找名称包含"PCM"或"发射机"的工作表
                   QStringList filteredNames2 = sheetNames.filter("异步", Qt::CaseInsensitive);
                   if (filteredNames2.isEmpty()) {
                       filteredNames2 = sheetNames.filter("发射机", Qt::CaseInsensitive);
                   }

                   if (!filteredNames2.isEmpty()) {
                       sheetName2 = filteredNames2.first();
                       qWarning() << "警告: 未找到'发射机PCM'工作表，将使用 '" << sheetName2 << "'";
                   } else {
                       qCritical() << "错误: 未找到'发射机PCM'工作表，可用工作表: " << sheetNames.join(", ");
                       return ;
                   }
               }

               // 5. 选择工作表
               if (!xlsx.selectSheet(sheetName2)) {
                   qCritical() << "错误: 无法选择工作表 '" << sheetName2 << "'";
                   return ;
               }

               int minRow2 = 0, minCol2 = 0;
               int maxRow2 = 0, maxCol2 = 0;

               // 6. 获取工作表的有效数据范围
               QXlsx::CellRange range2 = xlsx.dimension();


              int rowCount2 = range2.lastRow() - range2.firstRow() + 1;
              int colCount2 = range2.lastColumn() - range2.firstColumn() + 1;

              minRow2 = range2.firstRow();
              minCol2 = range2.firstColumn();
              maxRow2 = range2.lastRow();
              maxCol2 = range2.lastColumn();

              quint8 iresqu = 1;
              if(maxRow2 > 10)
              {
                  maxRow2 = 10;
              }

              QByteArray shuli;


              for (int row = minRow2; row <= maxRow2; ++row) {
                      for (int col = minCol2; col <= maxCol2; ++col) {
                          // 跳过空单元格
                          QXlsx::Cell* cell = xlsx.cellAt(row, col);
                          if (!cell) continue;

                          // 将单元格数据转为字符串（假设都是文本）
                          QString textValue = cell->value().toString();
                          int len = textValue.length();

                          // 确保处理偶数长度的字符串
                          if (len % 2 != 0) {
                              qWarning() << "Odd length hex string found in cell (" << row << "," << col << "). Adding zero prefix.";
                              textValue = "0" + textValue;  // 补齐为偶数长度
                              len = textValue.length();
                          }

                          // 两两分组转换为十六进制字节
                          for (int i = 0; i < len; i += 2) {
                              QString hexPair = textValue.mid(i, 2);
                              bool ok;
                              char byteVal = static_cast<char>(hexPair.toInt(&ok, 16));
                              if (!ok) {
                                  qWarning() << "Invalid hex char in cell (" << row << "," << col << "):" << hexPair;
                                  byteVal = 0;  // 无效字符用0代替
                              }
                              shuli.append(byteVal);






                          }
                      }
                      owner->m_PPACKET_HEADER = new PACKET_HEADER;
                      owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
                      owner->m_PPACKET_HEADER->functionCode = 0x0F;
                      owner->m_PPACKET_HEADER->dataLength = shuli.size() + 15;
                      qDebug() << shuli.size() << shuli.size() + 15;
                      owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
                      owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);


                      QByteArray array;
                      array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                                   sizeof(PACKET_HEADER));


                      if(pattern == 1)
                      {
                          array.append(static_cast<quint8>(0x01));
                      }
                      else if(pattern == 2)
                      {
                          array.append(static_cast<quint8>(0x02));
                      }



                      array.append(static_cast<quint8>(iresqu++));

                      array.append(static_cast<char>(0));

                      array.append(shuli);


                      shuli.clear();

                      quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
                      m_crc32 = qToLittleEndian<quint32>(m_crc32);
                      array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

                      qDebug() << array.toHex();


                      owner->udpManager->sendDatagram(array);
              }









}

void Dialogfasheset::on_Btn_readApplication_clicked()
{
    owner->m_PREAD_PCM_CONFIG = new READ_PCM_CONFIG;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x08;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_PCM_CONFIG->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_PCM_CONFIG->fashe = 0x02;
    }


    QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_PCM_CONFIG),
                                                  sizeof(READ_PCM_CONFIG));

    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    int i  = 0 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    owner->udpManager->sendDatagram(array);



    if(pattern == 1)
    {
       Logger::info("发射机1:配置信道编码下发");
       owner->setmaintable("发射机1:配置信道编码下发","上位机");
    }
    else
    {
       Logger::info("发射机2:配置信道编码下发");
       owner->setmaintable("发射机2:配置信道编码下发","上位机");
    }

}

void Dialogfasheset::on_Btn_readApplication_2_clicked()
{
    owner->m_PREAD_ASY_CONFIG = new READ_ASY_CONFIG;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x0a;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);
    if(pattern == 1)
    {
      owner->m_PREAD_ASY_CONFIG->fashe = 0x01;
    }
    else if(pattern == 2)
    {
      owner->m_PREAD_ASY_CONFIG->fashe = 0x02;


    }


    QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREAD_ASY_CONFIG),
                                                  sizeof(READ_ASY_CONFIG));

    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);

    int i  = 1 ;
    for (quint8 byte : array) {
                  QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                  qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
              }


    if(pattern == 1)
    {
       Logger::info("发射机1:配置信道编码下发");
       owner->setmaintable("发射机1:配置信道编码下发","上位机");
    }
    else
    {
       Logger::info("发射机2:配置信道编码下发");
       owner->setmaintable("发射机2:配置信道编码下发","上位机");
    }
}
