#include "machinestatus.h"
#include "ui_machinestatus.h"

#include "mainwindow.h"

Machinestatus::Machinestatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Machinestatus)
{
    ui->setupUi(this);

    setWindowTitle("模拟器监控软件");

    // 设置为只读（不可写，但可以选择文本和复制）
    ui->lineEdit_Temperature->setReadOnly(true);
    ui->lineEdit_Version_number->setReadOnly(true);
    ui->lineEdit_Power_amplifier1->setReadOnly(true);
    ui->lineEdit_Power_amplifier2->setReadOnly(true);
    ui->lineEdit_Detection_voltage1->setReadOnly(true);
    ui->lineEdit_Detection_voltage2->setReadOnly(true);
    ui->lineEdit_Output_current_12V->setReadOnly(true);
    ui->lineEdit_Output_voltage_12V->setReadOnly(true);
    ui->lineEdit_Power_input_voltage->setReadOnly(true);
    ui->lineEdit_Input_current_power_supply->setReadOnly(true);
    ui->lineEdit_Power_amplifier_28V_supply_voltage->setReadOnly(true);
    ui->lineEdit_Version_shangweji->setReadOnly(true);


    ui->label_2->hide();
    ui->label_5->hide();
    ui->lineEdit_Output_voltage_12V->hide();
    ui->lineEdit_Output_current_12V->hide();


    loadSettings();
}

Machinestatus::~Machinestatus()
{
    this->owner->isOpenTime =true;
    disconnect(owner->worker , &Worker::MachineStatusRead  ,this , &Machinestatus::onMachineStatusRead);
    delete ui;
}

void Machinestatus::setOwner(MainWindow *mainwindow)
{
    owner = mainwindow;
}

void Machinestatus::loadSettings()
{
    QSettings settings("settings.ini", QSettings::IniFormat);


    banben = settings.value("banben", "V1.04").toString();

    ui->lineEdit_Version_shangweji->setText(banben);


}

void Machinestatus::onchineStatusRead()
{

}

void Machinestatus::onMachineStatusRead(quint16 Power_input_voltage, quint16 Output_voltage_12V,
                                        quint16 Power_amplifier_28V_supply_voltage,
                                        quint16 Input_current_power_supply, quint16 Output_current_12V,
                                        quint16 Power_amplifier1, quint16 Power_amplifier2,
                                        quint16 Detection_voltage1, quint16 Detection_voltage2,
                                        quint8 Temperature, quint16 Version_number)

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

    int  vaun = QString("%1").arg(Version_number, 2, 16).toUpper().toInt();
    value = static_cast<double>(vaun) / 100.0;
    ui->lineEdit_Version_number->setText("V" + QString::number(value, 'f', 2));




}

void Machinestatus::closeEvent(QCloseEvent *event)
{
    this->owner->isOpenTime =true;
    disconnect(owner->worker , &Worker::MachineStatusRead  ,this , &Machinestatus::onMachineStatusRead);
    event->accept();
}

