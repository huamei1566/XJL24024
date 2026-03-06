#ifndef DIALOGFASHESET_H
#define DIALOGFASHESET_H

#include <QDialog>


#include "dragdroptablewidget.h"
#include "droptargettable.h"
#include "draggabletable.h"
#include "draggablebutton.h"
#include <QUdpSocket>
#include <QThread>
#include <QVector>

#include "intrangedelegate.h"
#include "maxlengthdelegate.h"

class MainWindow;
class StrictIntValidator;


namespace Ui {
class Dialogfasheset;
}

class Dialogfasheset : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogfasheset(int sig = 0 ,  QWidget *parent = nullptr);
    ~Dialogfasheset();
    void setOwner(MainWindow *mainWindow){owner = mainWindow;}




private slots:
    void on_Btn_peiz_clicked();

    void on_Btn_readpeiz_clicked();

    void on_Btn_readpeiz_2_clicked();

    void on_Btn_readpeiz_3_clicked();

    void on_Btn_readpcmpeiz_clicked();

    void on_lineEdit_zhenchang_textChanged(const QString &arg1);

    void on_lineEdit_fuzhenchangdu_textChanged(const QString &arg1);

    void on_Btn_pcmpeiz_clicked();

    void on_Btn_peziall_clicked();

    void on_Btn_new_clicked();

    void on_Btn_delete_clicked();


    void on_Btn_delete_2_clicked();

    void on_Btn_new_2_clicked();

    void on_Btn_Application_clicked();

    void on_Btn_Application_2_clicked();

    void on_pushButton_selsetxlsx_clicked();

    void on_Btn_zhuangzai_clicked();

    void on_Btn_readApplication_clicked();

    void on_Btn_readApplication_2_clicked();

public slots:

    void onRES_FRAMEFORMAT(int fasheji);
    void onRES_yaocFRAMEFORMAT(int fasheji);
    void onRES_ENCODING_CONFIG(int fasheji);
    void onRES_PCM_CONFIG(int fasheji);
    void onRES_ASY_CONFIG(int fasheji);



public:
    void saveSettings();
    void loadSettings();

    void settableUI();


    void updateUIFromVariables();

    void lookuptable();
    QPair<int, int> findClosestFrequencies(int targetFreq);
    double getValue(int freq, int index);



    void ControlAlignment(QString filepath);


    void fasheping(int pattern);

    void doWorkWithDelay(int ms);



protected:
     void closeEvent(QCloseEvent *event) override;


private:
    QString zichang;
    QString xhfztongbuma;
    QString tjmbujin;
    QString tjmchushizi;
    QString zjsdzjbodao;
    QString zjsgzjbodao;
    QString IDmafztz;
    QString Bianmaweizhi;
    QString Bianma;
    QString Malv;
    QString maxing;
    QString xinhaoneixing;
    QString zhenchang;
    QString zhenmazhu;
    QString fuzhenfanshi;
    QString tzfzweizhi;
    QString fuzhenchangdu;
    QString IDzijizhi;
    QString IDzijishufangshi;
    QString Fuzhentezheng;
    QString fuzhenlvxu;
    QString fspinlv;
    QString tzbinpian;
    QString tiao1;
    QString zai1;
    QString tiaokai1;
    QString tiaoji1;
    QString fsygonglvkongz;
    QString bianmakai;
    QString LDPC;
    QString TPC;
    QString RS;
    QString juanji;
    QString TPCtongbuma;
    QString youxiaobiaozi;

    int anysum;
    int asynum;

    int     bujielow;    // checkBox_low的判断值
    int     bujiehigh;   // checkBox_high的判断值
    int     ismofei;     // 是否模飞

    QString zichang_2;
    QString xhfztongbuma_2;
    QString tjmbujin_2;
    QString tjmchushizi_2;
    QString zjsdzjbodao_2;
    QString zjsgzjbodao_2;
    QString IDmafztz_2;
    QString Bianmaweizhi_2;
    QString Bianma_2;
    QString Malv_2;
    QString maxing_2;
    QString xinhaoneixing_2;
    QString zhenchang_2;
    QString zhenmazhu_2;
    QString fuzhenfanshi_2;
    QString tzfzweizhi_2;
    QString fuzhenchangdu_2;
    QString IDzijizhi_2;
    QString IDzijishufangshi_2;
    QString Fuzhentezheng_2;
    QString fuzhenlvxu_2;
    QString fspinlv_2;
    QString tzbinpian_2;
    QString tiao1_2;
    QString zai1_2;
    QString tiaokai1_2;
    QString tiaoji1_2;
    QString fsygonglvkongz_2;
    QString bianmakai_2;
    QString LDPC_2;
    QString TPC_2;
    QString RS_2;
    QString juanji_2;
    QString TPCtongbuma_2;
    QString youxiaobiaozi_2;


    int     bujielow_2;    // checkBox_low的判断值
    int     bujiehigh_2;   // checkBox_high的判断值
    int     ismofei_2;     // 是否模飞


    QMap<int , int> AlignmentMap;


    QVector<QVector<int>> m_QVector;



private:
    Ui::Dialogfasheset *ui;
    MainWindow *owner;


    int  pattern;


};


#endif // DIALOGFASHESET_H
