#ifndef MACHINESTATUS_H
#define MACHINESTATUS_H

#include <QDialog>

class MainWindow;

namespace Ui {
class Machinestatus;
}

class Machinestatus : public QDialog
{
    Q_OBJECT

public:
    explicit Machinestatus(QWidget *parent = 0);
    ~Machinestatus();

    MainWindow* owner;
    void setOwner(MainWindow* mainwindow);

    void loadSettings();

    QString banben;

public slots:
    void onchineStatusRead();

    void onMachineStatusRead(quint16 Power_input_voltage ,quint16 Output_voltage_12V,
                                               quint16 Power_amplifier_28V_supply_voltage,
                                               quint16 Input_current_power_supply ,quint16 Output_current_12V,
                                               quint16 Power_amplifier1 , quint16 Power_amplifier2,
                                               quint16 Detection_voltage1 , quint16 Detection_voltage2,
                                               quint8 Temperature , quint16 Version_number
                                               );
protected:
     void closeEvent(QCloseEvent *event) override;

private:
    Ui::Machinestatus *ui;
};

#endif // MACHINESTATUS_H
