#ifndef SECURITYCONTROLSET_H
#define SECURITYCONTROLSET_H

#include <QDialog>
#include <QSettings>

class MainWindow;

namespace Ui {
class SecurityControlset;
}

class SecurityControlset : public QDialog
{
    Q_OBJECT

public:
    explicit SecurityControlset(QWidget *parent = nullptr);
    void setOwner(MainWindow *mainWindow){owner = mainWindow;}
    ~SecurityControlset();

    // 重写关闭事件
    void closeEvent(QCloseEvent *event) override;

    void updateUIFromVariables();

    quint16 updateankong(QString ankong);
    QString Reversekong(quint16 reverseankong);

    void updatecomboBox_2();



private slots:


    void on_Btn_peiz_2_clicked();

    void on_Btn_read_peiz_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);


public slots:
    void on_RES_PREADankongpeiz();

public:
    void saveSettings();
    void loadSettings();

private:
    QString zichang;
    QString zaibopinlv;
    QString fuzaibopinlv;
    QString ankongmoshi;
    QString DPSK_daikuan;
    QString DPSK_FMzilinmalv;
    QString DPSK_FM_zilingLength;
    QString DPSK_FM_qiandaoma;
    QString DPSK_FM_tongbu;
    QString maxing;

    QString K1_dizhi;
    QString K1_gongneng;
    QString K1_tianchong;

    QString K2_dizhi;
    QString K2_gongneng;
    QString K2_tianchong;

    QString K3_dizhi;
    QString K3_gongneng;
    QString K3_tianchong;

    QString K4_dizhi;
    QString K4_gongneng;
    QString K4_tianchong;


    QString K1_1;
    QString K1_2;
    QString K1_3;
    QString K1_4;
    QString K1_5;
    QString K1_6;
    QString K1_7;
    QString K2_1;
    QString K2_2;
    QString K2_3;
    QString K2_4;
    QString K2_5;
    QString K2_6;
    QString K2_7;
    QString K3_1;
    QString K3_2;
    QString K3_3;
    QString K3_4;
    QString K3_5;
    QString K3_6;
    QString K3_7;
    QString K4_1;
    QString K4_2;
    QString K4_3;
    QString K4_4;
    QString K4_5;
    QString K4_6;
    QString K4_7;




private:
    Ui::SecurityControlset *ui;
    MainWindow* owner;






};

#endif // SECURITYCONTROLSET_H
