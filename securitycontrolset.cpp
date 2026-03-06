#include "securitycontrolset.h"
#include "ui_securitycontrolset.h"

#include "mainwindow.h"

SecurityControlset::SecurityControlset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecurityControlset)
{
    ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);
    loadSettings();


    setWindowTitle("安控参数设置界面");

    ui->tabWidget->setTabText(0, "DPSK-FM");
    ui->tabWidget->setTabText(1, "多音主字母");

    ui->lineEdit_DPSK_FM_qiandaoma->setReadOnly(true);
    ui->lineEdit_DPSK_FM_tongbu->setReadOnly(true);

    ui->label_45->setStyleSheet("color: #808080;");
    ui->label_49->setStyleSheet("color: #808080;");

    ui->lineEdit_zaibopinlv->setValidator(new StrictIntValidator(0 , 1850000 , this));

    ui->Edit_K1_dizhi->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));
    ui->Edit_K2_dizhi->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));
    ui->Edit_K3_dizhi->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));
    ui->Edit_K4_dizhi->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));

    ui->Edit_K1_tianchong->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));
    ui->Edit_K2_tianchong->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));
    ui->Edit_K3_tianchong->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));
    ui->Edit_K4_tianchong->setValidator(new QRegExpValidator(QRegExp(".{0,2}"), this));

    ui->Edit_K1_gongneng->setValidator(new QRegExpValidator(QRegExp(".{0,4}"), this));
    ui->Edit_K2_gongneng->setValidator(new QRegExpValidator(QRegExp(".{0,4}"), this));
    ui->Edit_K3_gongneng->setValidator(new QRegExpValidator(QRegExp(".{0,4}"), this));
    ui->Edit_K4_gongneng->setValidator(new QRegExpValidator(QRegExp(".{0,4}"), this));

    ui->Edit_K1_1->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K1_2->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K1_3->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K1_4->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K1_5->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K1_6->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K1_7->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));

    ui->Edit_K2_1->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K2_2->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K2_3->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K2_4->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K2_5->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K2_6->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K2_7->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));

    ui->Edit_K3_1->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K3_2->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K3_3->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K3_4->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K3_5->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K3_6->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K3_7->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));

    ui->Edit_K4_1->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K4_2->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K4_3->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K4_4->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K4_5->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K4_6->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));
    ui->Edit_K4_7->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));

    ui->lineEdit_DPSK_FM_tongbu->setValidator(new QRegExpValidator(QRegExp(".{4,4}"), this));

    updatecomboBox_2();

    ui->Btn_peiz_2->setStyleSheet(
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

    ui->Btn_read_peiz->setStyleSheet(
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


}

SecurityControlset::~SecurityControlset()
{

    delete ui;
}

void SecurityControlset::closeEvent(QCloseEvent *event)
{


    saveSettings();

    event->accept();
}

void SecurityControlset::saveSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

            //zichang = ui->comboBox_zichang->currentText();
            zaibopinlv = ui->lineEdit_zaibopinlv->text();
            fuzaibopinlv = ui->comboBox_2->currentText();
            ankongmoshi = ui->comboBox_ankongmoshi->currentText();
            //DPSK_daikuan = ui->lineEdit_DPSK_daikuan->text();
            DPSK_FMzilinmalv = ui->comboBox->currentText();
            DPSK_FM_zilingLength = ui->lineEdit_DPSK_FM_zilingLength->text();
            DPSK_FM_qiandaoma = ui->lineEdit_DPSK_FM_qiandaoma->text();
            DPSK_FM_tongbu = ui->lineEdit_DPSK_FM_tongbu->text();
            maxing = ui->comboBox_maxing->currentText();

            K1_dizhi = ui->Edit_K1_dizhi->text();
            K1_gongneng = ui->Edit_K1_gongneng->text();
            K1_tianchong = ui->Edit_K1_tianchong->text();

            K2_dizhi = ui->Edit_K2_dizhi->text();
            K2_gongneng = ui->Edit_K2_gongneng->text();
            K2_tianchong = ui->Edit_K2_tianchong->text();

            K3_dizhi = ui->Edit_K3_dizhi->text();
            K3_gongneng = ui->Edit_K3_gongneng->text();
            K3_tianchong = ui->Edit_K3_tianchong->text();

            K4_dizhi = ui->Edit_K4_dizhi->text();
            K4_gongneng = ui->Edit_K4_gongneng->text();
            K4_tianchong = ui->Edit_K4_tianchong->text();

            K1_1 = ui->Edit_K1_1->text();
            K1_2 = ui->Edit_K1_2->text();
            K1_3 = ui->Edit_K1_3->text();
            K1_4 = ui->Edit_K1_4->text();
            K1_5 = ui->Edit_K1_5->text();
            K1_6 = ui->Edit_K1_6->text();
            K1_7 = ui->Edit_K1_7->text();
            K2_1 = ui->Edit_K2_1->text();
            K2_2 = ui->Edit_K2_2->text();
            K2_3 = ui->Edit_K2_3->text();
            K2_4 = ui->Edit_K2_4->text();
            K2_5 = ui->Edit_K2_5->text();
            K2_6 = ui->Edit_K2_6->text();
            K2_7 = ui->Edit_K2_7->text();
            K3_1 = ui->Edit_K3_1->text();
            K3_2 = ui->Edit_K3_2->text();
            K3_3 = ui->Edit_K3_3->text();
            K3_4 = ui->Edit_K3_4->text();
            K3_5 = ui->Edit_K3_5->text();
            K3_6 = ui->Edit_K3_6->text();
            K3_7 = ui->Edit_K3_7->text();
            K4_1 = ui->Edit_K4_1->text();
            K4_2 = ui->Edit_K4_2->text();
            K4_3 = ui->Edit_K4_3->text();
            K4_4 = ui->Edit_K4_4->text();
            K4_5 = ui->Edit_K4_5->text();
            K4_6 = ui->Edit_K4_6->text();
            K4_7 = ui->Edit_K4_7->text();

            // 基本参数组
            settings.beginGroup("ankongpeiz");
            settings.setValue("zichang", zichang);
            settings.setValue("zaibopinlv", zaibopinlv);
            settings.setValue("fuzaibopinlv", fuzaibopinlv);
            settings.setValue("ankongmoshi", ankongmoshi);
            settings.setValue("DPSK_daikuan", DPSK_daikuan);
            settings.setValue("DPSK_FMzilinmalv", DPSK_FMzilinmalv);
            settings.setValue("DPSK_FM_zilingLength", DPSK_FM_zilingLength);
            settings.setValue("DPSK_FM_qiandaoma", DPSK_FM_qiandaoma);
            settings.setValue("DPSK_FM_tongbu", DPSK_FM_tongbu);
            settings.setValue("maxing", maxing);
            settings.endGroup();

            // 同步与编码组
            settings.beginGroup("Kkezhi");
            settings.setValue("K1_dizhi", K1_dizhi);
            settings.setValue("K1_gongneng", K1_gongneng);
            settings.setValue("K1_tianchong", K1_tianchong);
            settings.setValue("K2_dizhi", K2_dizhi);
            settings.setValue("K2_gongneng", K2_gongneng);
            settings.setValue("K2_tianchong", K2_tianchong);
            settings.setValue("K3_dizhi", K3_dizhi);
            settings.setValue("K3_gongneng", K3_gongneng);
            settings.setValue("K3_tianchong", K3_tianchong);
            settings.setValue("K4_dizhi", K4_dizhi);
            settings.setValue("K4_gongneng", K4_gongneng);
            settings.setValue("K4_tianchong", K4_tianchong);
            settings.endGroup();

            // 调制组
            settings.beginGroup("Kziling");
            settings.setValue("K1_1", K1_1);
            settings.setValue("K1_2", K1_2);
            settings.setValue("K1_3", K1_3);
            settings.setValue("K1_4", K1_4);
            settings.setValue("K1_5", K1_5);
            settings.setValue("K1_6", K1_6);
            settings.setValue("K1_7", K1_7);
            settings.setValue("K2_1", K2_1);
            settings.setValue("K2_2", K2_2);
            settings.setValue("K2_3", K2_3);
            settings.setValue("K2_4", K2_4);
            settings.setValue("K2_5", K2_5);
            settings.setValue("K2_6", K2_6);
            settings.setValue("K2_7", K2_7);
            settings.setValue("K3_1", K3_1);
            settings.setValue("K3_2", K3_2);
            settings.setValue("K3_3", K3_3);
            settings.setValue("K3_4", K3_4);
            settings.setValue("K3_5", K3_5);
            settings.setValue("K3_6", K3_6);
            settings.setValue("K3_7", K3_7);
            settings.setValue("K4_1", K4_1);
            settings.setValue("K4_2", K4_2);
            settings.setValue("K4_3", K4_3);
            settings.setValue("K4_4", K4_4);
            settings.setValue("K4_5", K4_5);
            settings.setValue("K4_6", K4_6);
            settings.setValue("K4_7", K4_7);
            settings.endGroup();



            owner->setankongjiegongK();


}

void SecurityControlset::loadSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);

    // 基本参数组
    settings.beginGroup("ankongpeiz");
    zichang = settings.value("zichang", "4").toString(); // 默认值示例
    zaibopinlv = settings.value("zaibopinlv", "1000").toString();
    fuzaibopinlv = settings.value("fuzaibopinlv", "1000").toString();
    ankongmoshi = settings.value("ankongmoshi", "DPSK-FM").toString();
    DPSK_daikuan = settings.value("DPSK_daikuan", "1000").toString(); // 默认值示例
    DPSK_FMzilinmalv = settings.value("DPSK_FMzilinmalv", "1000").toString();
    DPSK_FM_zilingLength = settings.value("DPSK_FM_zilingLength", "256").toString();
    DPSK_FM_qiandaoma = settings.value("DPSK_FM_qiandaoma", "FFFFFF").toString();
    DPSK_FM_tongbu = settings.value("DPSK_FM_tongbu", "EB90").toString(); // 默认值示例
    maxing = settings.value("maxing", "NRZ-L").toString();
    settings.endGroup();

    settings.beginGroup("Kkezhi");
    K1_dizhi = settings.value("K1_dizhi", "").toString(); // 默认值示例
    K1_gongneng = settings.value("K1_gongneng", "1234").toString();
    K1_tianchong = settings.value("K1_tianchong", "12").toString();
    K2_dizhi = settings.value("K2_dizhi", "12").toString();
    K2_gongneng = settings.value("K2_gongneng", "1234").toString(); // 默认值示例
    K2_tianchong = settings.value("K2_tianchong", "12").toString();
    K3_dizhi = settings.value("K3_dizhi", "12").toString();
    K3_gongneng = settings.value("K3_gongneng", "1234").toString();
    K3_tianchong = settings.value("K3_tianchong", "12").toString(); // 默认值示例
    K4_dizhi = settings.value("K4_dizhi", "12").toString();
    K4_gongneng = settings.value("K4_gongneng", "1234").toString(); // 默认值示例
    K4_tianchong = settings.value("K4_tianchong", "12").toString();
    settings.endGroup();

    settings.beginGroup("Kziling");
    K1_1 = settings.value("K1_1", "1234").toString();
    K1_2 = settings.value("K1_2", "1234").toString();
    K1_3 = settings.value("K1_3", "1234").toString();
    K1_4 = settings.value("K1_4", "1234").toString();
    K1_5 = settings.value("K1_5", "1234").toString();
    K1_6 = settings.value("K1_6", "1234").toString();
    K1_7 = settings.value("K1_7", "1234").toString();
    K2_1 = settings.value("K2_1", "1234").toString();
    K2_2 = settings.value("K2_2", "1234").toString();
    K2_3 = settings.value("K2_3", "1234").toString();
    K2_4 = settings.value("K2_4", "1234").toString();
    K2_5 = settings.value("K2_5", "1234").toString();
    K2_6 = settings.value("K2_6", "1234").toString();
    K2_7 = settings.value("K2_7", "1234").toString();
    K3_1 = settings.value("K3_1", "1234").toString();
    K3_2 = settings.value("K3_2", "1234").toString();
    K3_3 = settings.value("K3_3", "1234").toString();
    K3_4 = settings.value("K3_4", "1234").toString();
    K3_5 = settings.value("K3_5", "1234").toString();
    K3_6 = settings.value("K3_6", "1234").toString();
    K3_7 = settings.value("K3_7", "1234").toString();
    K4_1 = settings.value("K4_1", "1234").toString();
    K4_2 = settings.value("K4_2", "1234").toString();
    K4_3 = settings.value("K4_3", "1234").toString();
    K4_4 = settings.value("K4_4", "1234").toString();
    K4_5 = settings.value("K4_5", "1234").toString();
    K4_6 = settings.value("K4_6", "1234").toString();
    K4_7 = settings.value("K4_7", "1234").toString();
    settings.endGroup();

    updateUIFromVariables();


}

void SecurityControlset::updateUIFromVariables()
{
//    ui->comboBox_zichang->setCurrentText(zichang);
    ui->lineEdit_zaibopinlv->setText(zaibopinlv);
    ui->comboBox_2->setCurrentText(fuzaibopinlv); //ui->comboBox_2->currentText()
    ui->comboBox_ankongmoshi->setCurrentText(ankongmoshi);
    //ui->lineEdit_DPSK_daikuan->setText(DPSK_daikuan);
    ui->comboBox->setCurrentText(DPSK_FMzilinmalv);
    ui->lineEdit_DPSK_FM_zilingLength->setText(DPSK_FM_zilingLength);
    ui->lineEdit_DPSK_FM_qiandaoma->setText(DPSK_FM_qiandaoma);
    ui->lineEdit_DPSK_FM_tongbu->setText(DPSK_FM_tongbu);
    ui->comboBox_maxing->setCurrentText(maxing);

    ui->Edit_K1_dizhi->setText(K1_dizhi);
    ui->Edit_K1_gongneng->setText(K1_gongneng);
    ui->Edit_K1_tianchong->setText(K1_tianchong);
    ui->Edit_K2_dizhi->setText(K2_dizhi);
    ui->Edit_K2_gongneng->setText(K2_gongneng);
    ui->Edit_K2_tianchong->setText(K2_tianchong);
    ui->Edit_K3_dizhi->setText(K3_dizhi);
    ui->Edit_K3_gongneng->setText(K3_gongneng);
    ui->Edit_K3_tianchong->setText(K3_tianchong);
    ui->Edit_K4_dizhi->setText(K4_dizhi);
    ui->Edit_K4_gongneng->setText(K4_gongneng);
    ui->Edit_K4_tianchong->setText(K4_tianchong);

    ui->Edit_K1_1->setText(K1_1);
    ui->Edit_K1_2->setText(K1_2);
    ui->Edit_K1_3->setText(K1_3);
    ui->Edit_K1_4->setText(K1_4);
    ui->Edit_K1_5->setText(K1_5);
    ui->Edit_K1_6->setText(K1_6);
    ui->Edit_K1_7->setText(K1_7);
    ui->Edit_K2_1->setText(K2_1);
    ui->Edit_K2_2->setText(K2_2);
    ui->Edit_K2_3->setText(K2_3);
    ui->Edit_K2_4->setText(K2_4);
    ui->Edit_K2_5->setText(K2_5);
    ui->Edit_K2_6->setText(K2_6);
    ui->Edit_K2_7->setText(K2_7);
    ui->Edit_K3_1->setText(K3_1);
    ui->Edit_K3_2->setText(K3_2);
    ui->Edit_K3_3->setText(K3_3);
    ui->Edit_K3_4->setText(K3_4);
    ui->Edit_K3_5->setText(K3_5);
    ui->Edit_K3_6->setText(K3_6);
    ui->Edit_K3_7->setText(K3_7);
    ui->Edit_K4_1->setText(K4_1);
    ui->Edit_K4_2->setText(K4_2);
    ui->Edit_K4_3->setText(K4_3);
    ui->Edit_K4_4->setText(K4_4);
    ui->Edit_K4_5->setText(K4_5);
    ui->Edit_K4_6->setText(K4_6);
    ui->Edit_K4_7->setText(K4_7);

}

quint16 SecurityControlset::updateankong(QString ankong)
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

QString SecurityControlset::Reversekong(quint16 reverseankong)
{
    QString result;

        // 遍历quint16的每一位（0-15）
        for (int pos = 0; pos < 16; ++pos) {
            // 检查当前位是否被设置（=1）
            if (reverseankong & (1 << pos)) {
                QChar c;
                // 将位置值映射为字符
                if (pos < 10) {
                    c = '0' + pos;           // 0-9 -> '0'-'9'
                } else {
                    c = 'A' + (pos - 10);    // 10-15 -> 'A'-'F'
                }
                result.append(c);
            }
        }

        return result;
}

void SecurityControlset::updatecomboBox_2()
{
    int value123 = ui->comboBox->currentText().toInt();

    ui->comboBox_2->clear();

    for(int i = 4 ; i <= 16 ; i++)
    {
      if(value123 * i > 64000)
        {
          ui->comboBox_2->addItem(QString("%1").arg(value123 * i));
          break ;
        }

      ui->comboBox_2->addItem(QString("%1").arg(value123 * i));

    }


   ui->comboBox_2->setCurrentText(QString("%1").arg(value123 * 5));

}

void SecurityControlset::on_Btn_peiz_2_clicked()
{
    owner->m_PSecuritySourceConfig = new SecuritySourceConfig;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x0b;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);



    quint32 byteValue32 = static_cast<quint32>(ui->lineEdit_zaibopinlv->text().toInt()); // 0x01
    owner->m_PSecuritySourceConfig->carrierFrequency = qToLittleEndian<quint32>(byteValue32);

    quint16 byteValue16;
    quint8 byteValue8;

    byteValue32 = static_cast<quint32>(ui->comboBox_2->currentText().toInt()* 4294967296 / owner->fo_2); // 0x01
    owner->m_PSecuritySourceConfig->subcarrierFrequency = qToLittleEndian<quint32>(byteValue32);

    if(ui->comboBox_ankongmoshi->currentText()  == "DPSK-FM")
    {
        byteValue8 = 0x00;
    }
    else if(ui->comboBox_ankongmoshi->currentText()  == "主字母")
    {
        byteValue8 = 0x01;
    }
   owner->m_PSecuritySourceConfig->modeBits.modeSelect = qToLittleEndian<quint16>(byteValue8);
   owner->m_PSecuritySourceConfig->modeBits.reserved = 0x00;

   //byteValue8 = static_cast<quint8>(ui->lineEdit_DPSK_daikuan->text().toInt());

   owner->m_PSecuritySourceConfig->dpskFmBandwidth = 0x00;

   byteValue32 = static_cast<quint32>(ui->comboBox->currentText().toInt()* 4294967296 / owner->fo_2);
   owner->m_PSecuritySourceConfig->dpskFmInstructionRate = qToLittleEndian<quint32>(byteValue32);

   byteValue16 = static_cast<quint16>(ui->lineEdit_DPSK_FM_zilingLength->text().toInt() - 1);
   owner->m_PSecuritySourceConfig->dpskFmInstructionLength = qToLittleEndian<quint16>(byteValue16);

   if(ui->comboBox_ankongmoshi->currentText() == "DPSK-FM")
   {
       if(ui->comboBox->currentText().toInt() > 2400)
       {
           owner->m_PSecuritySourceConfig->dpskFmBandwidth = 1;
       }
       else if(ui->comboBox->currentText().toInt() <= 600)
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



   if(ui->lineEdit_DPSK_FM_qiandaoma->text().isEmpty())
   {
       owner->m_PSecuritySourceConfig->dpskFmPreamble[0]  = 0xFF;
       owner->m_PSecuritySourceConfig->dpskFmPreamble[1]  = 0xFF;
       owner->m_PSecuritySourceConfig->dpskFmPreamble[2]  = 0xFF;
   }
   else
   {
       bool ok;
       byteValue32 = static_cast<quint32>(ui->lineEdit_DPSK_FM_qiandaoma->text().toInt(&ok ,16));
       quint8 byte1 = static_cast<quint8>(byteValue32 & 0xFF);// 最低有效字节
       quint8 byte2 = static_cast<quint8>((byteValue32 >> 8) & 0xFF);  // 中间字节
       quint8 byte3 = static_cast<quint8>((byteValue32 >> 16) & 0xFF); // 最高有效字节

       owner->m_PSecuritySourceConfig->dpskFmPreamble[0]  = byte1;
       owner->m_PSecuritySourceConfig->dpskFmPreamble[1]  = byte2;
       owner->m_PSecuritySourceConfig->dpskFmPreamble[2]  = byte3;

   }

   if(ui->lineEdit_DPSK_FM_tongbu->text().isEmpty())
   {
       owner->m_PSecuritySourceConfig->dpskFmInstructionSyncCode = qToLittleEndian<quint16>(0xEB90);
   }
   else
   {
       bool ok;
       byteValue16 = static_cast<quint16>(ui->lineEdit_DPSK_FM_tongbu->text().toInt(&ok ,16));
       owner->m_PSecuritySourceConfig->dpskFmInstructionSyncCode = qToLittleEndian<quint16>(byteValue16);
   }



   if(ui->comboBox_maxing->currentText() == "NRZ-L")
   {
       owner->m_PSecuritySourceConfig->codeBits.codeScheme = 0b0000;
   }
   else if(ui->comboBox_maxing->currentText() == "NRZ-M")
   {
       owner->m_PSecuritySourceConfig->codeBits.codeScheme = 0b0010;
   }
   else if(ui->comboBox_maxing->currentText() == "NRZ-S")
   {
       owner->m_PSecuritySourceConfig->codeBits.codeScheme = 0b0011;
   }

   owner->m_PSecuritySourceConfig->subcarrierTocoderate = owner->m_PSecuritySourceConfig->subcarrierFrequency
                                                        / owner->m_PSecuritySourceConfig->dpskFmInstructionRate - 1;

   //qDebug() << owner->m_PSecuritySourceConfig->subcarrierTocoderate;

   owner->m_PSecuritySourceConfig->codeBits.reserved = static_cast<quint8>(0x00);

   bool ok;
   byteValue8 = static_cast<quint8>(ui->Edit_K1_dizhi->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K1_Address_Code = qToLittleEndian<quint8>(byteValue8);

   byteValue16 = static_cast<quint16>(ui->Edit_K1_gongneng->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K1_Function_Code = qToLittleEndian<quint16>(byteValue16);

   byteValue8 = static_cast<quint8>(ui->Edit_K1_tianchong->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K1_Fill_Code = qToLittleEndian<quint8>(byteValue8);


   byteValue8 = static_cast<quint8>(ui->Edit_K2_dizhi->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K2_Address_Code = qToLittleEndian<quint8>(byteValue8);

   byteValue16 = static_cast<quint16>(ui->Edit_K2_gongneng->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K2_Function_Code = qToLittleEndian<quint16>(byteValue16);

   byteValue8 = static_cast<quint8>(ui->Edit_K2_tianchong->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K2_Fill_Code = qToLittleEndian<quint8>(byteValue8) ;

   byteValue8 = static_cast<quint8>(ui->Edit_K3_dizhi->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K3_Address_Code = qToLittleEndian<quint8>(byteValue8);

   byteValue16 = static_cast<quint16>(ui->Edit_K3_gongneng->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K3_Function_Code = qToLittleEndian<quint16>(byteValue16);

   byteValue8 = static_cast<quint8>(ui->Edit_K3_tianchong->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K3_Fill_Code = qToLittleEndian<quint8>(byteValue8) ;

   byteValue8 = static_cast<quint8>(ui->Edit_K4_dizhi->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K4_Address_Code = qToLittleEndian<quint8>(byteValue8);

   byteValue16 = static_cast<quint16>(ui->Edit_K4_gongneng->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K4_Function_Code = qToLittleEndian<quint16>(byteValue16);

   byteValue8 = static_cast<quint8>(ui->Edit_K4_tianchong->text().toInt(&ok ,16));
   owner->m_PSecuritySourceConfig->DPSK_K4_Fill_Code = qToLittleEndian<quint8>(byteValue8);

   owner->m_PSecuritySourceConfig->MainLetter_Self_check[0] = qToBigEndian<quint16>(updateankong(ui->Edit_K1_1->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_check[1] = qToBigEndian<quint16>(updateankong(ui->Edit_K1_2->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_check[2] = qToBigEndian<quint16>(updateankong(ui->Edit_K1_3->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_check[3] = qToBigEndian<quint16>(updateankong(ui->Edit_K1_4->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_check[4] = qToBigEndian<quint16>(updateankong(ui->Edit_K1_5->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_check[5] = qToBigEndian<quint16>(updateankong(ui->Edit_K1_6->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_check[6] = qToBigEndian<quint16>(updateankong(ui->Edit_K1_7->text()));

   owner->m_PSecuritySourceConfig->MainLetter_Reset[0] = qToBigEndian<quint16>(updateankong(ui->Edit_K2_1->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Reset[1] = qToBigEndian<quint16>(updateankong(ui->Edit_K2_2->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Reset[2] = qToBigEndian<quint16>(updateankong(ui->Edit_K2_3->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Reset[3] = qToBigEndian<quint16>(updateankong(ui->Edit_K2_4->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Reset[4] = qToBigEndian<quint16>(updateankong(ui->Edit_K2_5->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Reset[5] = qToBigEndian<quint16>(updateankong(ui->Edit_K2_6->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Reset[6] = qToBigEndian<quint16>(updateankong(ui->Edit_K2_7->text()));

   owner->m_PSecuritySourceConfig->MainLetter_Unlocked[0] = qToBigEndian<quint16>(updateankong(ui->Edit_K3_1->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Unlocked[1] = qToBigEndian<quint16>(updateankong(ui->Edit_K3_2->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Unlocked[2] = qToBigEndian<quint16>(updateankong(ui->Edit_K3_3->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Unlocked[3] = qToBigEndian<quint16>(updateankong(ui->Edit_K3_4->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Unlocked[4] = qToBigEndian<quint16>(updateankong(ui->Edit_K3_5->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Unlocked[5] = qToBigEndian<quint16>(updateankong(ui->Edit_K3_6->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Unlocked[6] = qToBigEndian<quint16>(updateankong(ui->Edit_K3_7->text()));

   owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[0] = qToBigEndian<quint16>(updateankong(ui->Edit_K4_1->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[1] = qToBigEndian<quint16>(updateankong(ui->Edit_K4_2->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[2] = qToBigEndian<quint16>(updateankong(ui->Edit_K4_3->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[3] = qToBigEndian<quint16>(updateankong(ui->Edit_K4_4->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[4] = qToBigEndian<quint16>(updateankong(ui->Edit_K4_5->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[5] = qToBigEndian<quint16>(updateankong(ui->Edit_K4_6->text()));
   owner->m_PSecuritySourceConfig->MainLetter_Self_destruct[6] = qToBigEndian<quint16>(updateankong(ui->Edit_K4_7->text()));


   for(int i = 0 ; i < 33 ; i++ )
   {
       owner->m_PSecuritySourceConfig->baliu2[i] = 0x00;
   }




   QByteArray array;
   array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                sizeof(PACKET_HEADER));
   array.append(reinterpret_cast<const char*>(owner->m_PSecuritySourceConfig),
                sizeof(SecuritySourceConfig));//    quint8  txSelector;        // 发射机选择 [1B]

   quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
   m_crc32 = qToLittleEndian<quint32>(m_crc32);
   array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

   int i  = 1 ;
   for (quint8 byte : array) {
                 QString hexStr = QString("0x%1").arg(byte, 2, 16, QChar('0'));
                 qDebug() << QString("%1").arg(i++) << " " << hexStr.toUpper(); // 转为大写
             }


   owner->udpManager->sendDatagram(array);

   Logger::info("安控:配置安控参数下发");
   owner->setmaintable("安控:配置安控参数下发", "上位机");
}

void SecurityControlset::on_Btn_read_peiz_clicked()
{

    owner->m_PREADSECURITYCONTROL = new READSECURITYCONTROL;
    owner->m_PPACKET_HEADER = new PACKET_HEADER;

    owner->m_PPACKET_HEADER->syncHeader = qToLittleEndian<quint32>(0xEF91AA55);
    owner->m_PPACKET_HEADER->functionCode = 0x0C;
    owner->m_PPACKET_HEADER->dataLength = qToLittleEndian<quint32>(0x72);
    owner->m_PPACKET_HEADER->totalPackets = qToLittleEndian<quint32>(0x01);
    owner->m_PPACKET_HEADER->currentPacket = qToLittleEndian<quint32>(0x01);


    owner->m_PREADSECURITYCONTROL->result = 0x01;


    QByteArray array;
    array.append(reinterpret_cast<const char*>(owner->m_PPACKET_HEADER),
                                                 sizeof(PACKET_HEADER));
    array.append(reinterpret_cast<const char*>(owner->m_PREADSECURITYCONTROL),
                                                 sizeof(READSECURITYCONTROL));
    quint32 m_crc32 = owner->crc32(array);  // 确保 crc32 返回栈变量
    m_crc32 = qToLittleEndian<quint32>(m_crc32);
    array.append(reinterpret_cast<const char*>(&m_crc32), sizeof(quint32));

    owner->udpManager->sendDatagram(array);

    Logger::info("安控:读取安控设置下发");
    owner->setmaintable("安控:读取安控设置下发","上位机");





}

void SecurityControlset::on_RES_PREADankongpeiz()
{

    ui->lineEdit_zaibopinlv->setText(QString::number(owner->m_PREADankongpeiz_RES->carrierFrequency));


    // 1. 获取值并转换为64位类型
    qint64 pcmRate_val = static_cast<qint64>(owner->m_PREADankongpeiz_RES->subcarrierFrequency);
    qint64 fo_val = static_cast<qint64>(owner->fo_2);

    // 2. 计算常数
    const qint64 BIG_DIVISOR = 4294967296LL;

    // 3. 带四舍五入的计算（一步完成）
    qint64 product = pcmRate_val * fo_val;
    qint64 malv_value = (product + BIG_DIVISOR / 2) / BIG_DIVISOR;



    ui->comboBox_2->setCurrentText(QString::number(malv_value));

    qDebug() << malv_value
             << owner->m_PREADankongpeiz_RES->dpskFmInstructionRate * owner->fo_2 / 4294967296;

    if(owner->m_PREADankongpeiz_RES->controlMode == 0)
    {
       ui->comboBox_ankongmoshi->setCurrentText(QString("DPSK-FM"));
    }
    else if(owner->m_PREADankongpeiz_RES->controlMode == 1)
    {
       ui->comboBox_ankongmoshi->setCurrentText(QString("主字母"));
    }


    pcmRate_val = static_cast<qint64>(owner->m_PREADankongpeiz_RES->dpskFmInstructionRate);
    fo_val = static_cast<qint64>(owner->fo_2);

    // 3. 带四舍五入的计算（一步完成）
    product = pcmRate_val * fo_val;
    malv_value = (product + BIG_DIVISOR / 2) / BIG_DIVISOR;


    //ui->lineEdit_DPSK_daikuan->setText(QString::number(owner->m_PREADankongpeiz_RES->dpskFmBandwidth));
    ui->comboBox->setCurrentText(QString::number(malv_value));
    ui->lineEdit_DPSK_FM_zilingLength->setText(QString::number(owner->m_PREADankongpeiz_RES->dpskFmInstructionLength + 1));
    // 提取三个字节的值
    quint8 b1 = owner->m_PREADankongpeiz_RES->dpskFmPreamble[0];
    quint8 b2 = owner->m_PREADankongpeiz_RES->dpskFmPreamble[1];
    quint8 b3 = owner->m_PREADankongpeiz_RES->dpskFmPreamble[2];

    // 格式化为十六进制字符串，每字节2位宽度，用空格分隔
    QString hexString = QString("%1%2%3")
                        .arg(b3, 2, 16, QLatin1Char('0'))
                        .arg(b2, 2, 16, QLatin1Char('0'))
                        .arg(b1, 2, 16, QLatin1Char('0'))
                        .toUpper();

    // 设置到UI
    ui->lineEdit_DPSK_FM_qiandaoma->setText(hexString);
    ui->lineEdit_DPSK_FM_tongbu->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->dpskFmInstructionSyncCode, 4, 16, QChar('0')).toUpper());

    if(owner->m_PREADankongpeiz_RES->codeBits.codeScheme == 0b0000)
    {
       ui->comboBox_maxing->setCurrentText(QString("NRZ-L"));
    }
    else if(owner->m_PREADankongpeiz_RES->codeBits.codeScheme == 0b0010)
    {
       ui->comboBox_maxing->setCurrentText(QString("NRZ-M"));
    }
    else if(owner->m_PREADankongpeiz_RES->codeBits.codeScheme == 0b0011)
    {
       ui->comboBox_maxing->setCurrentText(QString("NRZ-S"));
    }




    ui->Edit_K1_dizhi->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K1_Address_Code, 2, 16, QChar('0')).toUpper());
    ui->Edit_K1_gongneng->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K1_Function_Code, 4, 16, QChar('0')).toUpper());
    ui->Edit_K1_tianchong->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K1_Fill_Code, 2, 16, QChar('0')).toUpper());

    ui->Edit_K2_dizhi->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K2_Address_Code, 2, 16, QChar('0')).toUpper());
    ui->Edit_K2_gongneng->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K2_Function_Code, 4, 16, QChar('0')).toUpper());
    ui->Edit_K2_tianchong->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K2_Fill_Code, 2, 16, QChar('0')).toUpper());

    ui->Edit_K3_dizhi->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K3_Address_Code, 2, 16, QChar('0')).toUpper());
    ui->Edit_K3_gongneng->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K3_Function_Code, 4, 16, QChar('0')).toUpper());
    ui->Edit_K3_tianchong->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K3_Fill_Code, 2, 16, QChar('0')).toUpper());

    ui->Edit_K4_dizhi->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K4_Address_Code, 2, 16, QChar('0')).toUpper());
    ui->Edit_K4_gongneng->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K4_Function_Code, 4, 16, QChar('0')).toUpper());
    ui->Edit_K4_tianchong->setText(QString("%1").arg(owner->m_PREADankongpeiz_RES->DPSK_K4_Fill_Code, 2, 16, QChar('0')).toUpper());

    ui->Edit_K1_1->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_check[0])));
    ui->Edit_K1_2->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_check[1])));
    ui->Edit_K1_3->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_check[2])));
    ui->Edit_K1_4->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_check[3])));
    ui->Edit_K1_5->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_check[4])));
    ui->Edit_K1_6->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_check[5])));
    ui->Edit_K1_7->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_check[6])));


    ui->Edit_K2_1->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Reset[0])));
    ui->Edit_K2_2->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Reset[1])));
    ui->Edit_K2_3->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Reset[2])));
    ui->Edit_K2_4->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Reset[3])));
    ui->Edit_K2_5->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Reset[4])));
    ui->Edit_K2_6->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Reset[5])));
    ui->Edit_K2_7->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Reset[6])));

    ui->Edit_K3_1->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[0])));
    ui->Edit_K3_2->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[1])));
    ui->Edit_K3_3->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[2])));
    ui->Edit_K3_4->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[3])));
    ui->Edit_K3_5->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[4])));
    ui->Edit_K3_6->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[5])));
    ui->Edit_K3_7->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Unlocked[6])));

    ui->Edit_K4_1->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[0])));
    ui->Edit_K4_2->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[1])));
    ui->Edit_K4_3->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[2])));
    ui->Edit_K4_4->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[3])));
    ui->Edit_K4_5->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[4])));
    ui->Edit_K4_6->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[5])));
    ui->Edit_K4_7->setText(Reversekong(qFromBigEndian<quint16>(owner->m_PREADankongpeiz_RES->MainLetter_Self_destruct[6])));

}

void SecurityControlset::on_comboBox_currentIndexChanged(const QString &arg1)
{
     updatecomboBox_2();
}
