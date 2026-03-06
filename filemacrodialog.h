#ifndef FILEMACRODIALOG_H
#define FILEMACRODIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "mstrut.h"

class MainWindow;
class MultiColumnNonEditableDelegate;

namespace Ui {
class fileMacroDialog;
}

class fileMacroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fileMacroDialog(QWidget *parent = 0);
    ~fileMacroDialog();

    void setOwner(MainWindow *mainwindow);



    void closeEvent(QCloseEvent *event) override;

    void saveSettings(int i);
    void loadSettings(int i);
    void onupdatetablewidget(int i);

    quint16 updateankong(QString ankong);

    void doWorkWithDelay(int ms);

    int danqianint = 0;


    void updatetable();


    void copySettings(const QSettings& source, QSettings& target);



private slots:

    void on_Btn_PeiAll_clicked();

    void on_Btn_zhancun_clicked();

    void on_Btn_save_clicked();

    void on_Btn_take_clicked();

    void on_Btn_newsave_clicked();

    void on_Btn_delete_clicked();

    void on_Btn_fayi1_toggled(bool checked);

    void on_Btn_fayi2_toggled(bool checked);


private:
    Ui::fileMacroDialog *ui;
    MainWindow *owner;
    MultiColumnNonEditableDelegate *delegate;
    MultiColumnNonEditableDelegate *delegate2;

public:

    Pdaimoall m_daimoall[6];


    int tablecol;

    int id;
    QString daihao;
    QString savetime;
    QString txSelector;
    QString pcmRate;
    QString subFrameLength_length;
    QString subFrameLength_moFeiFlag;
    QString subFrameCount;
    QString WordConfig_codeType;
    QString WordConfig_wordLengthMinusOne;
    QString featurePosition;
    QString loopSyncCode;
    QString syncCode;
    QString frameType_Length;
    QString frameType_fhuframe;
    QString dataType;
    QString stepValue;
    QString initStep;
    QString FrameCalcChannel_frameCountLowByteIndex;
    QString FrameCalcChannel_notCountEnable;
    QString frameCalcChannelhigh_frameCountLowByteIndex;
    QString frameCalcChannelhigh_notCountEnable;
    QString idtreatrue_jishuaddorred;
    QString idtreatrue_jishuqidian;
    QString codingPosition;
    QString freq;
    QString detF;
    QString alltiaoz_modPolarity;
    QString alltiaoz_modSwitch;
    QString alltiaoz_carrier;
    QString alltiaoz_modType;
    QString powerCtrl;
    QString codeSwitch_ldpcEnable;
    QString codeSwitch_tpcEnable;
    QString codeSwitch_rsEnable;
    QString codeSwitch_convEnable;
    QString tpcSyncCode;
    QString tpcValidFlag;
    QString entryCount;
    QString entries_ctrlBits_mode1;
    QString entries_ctrlBits_mode2;
    QString entries_ctrlBits_mode3;
    QString entries_ctrlBits_mode4;
    QString entries_ctrlBits_mode5;
    QString entries_ctrlBits_mode6;
    QString entries_ctrlBits_mode7;
    QString entries_ctrlBits_mode8;
    QString entries_ctrlBits_mode9;
    QString entries_ctrlBits_mode10;
    QString entries_subFramePos1;
    QString entries_subFramePos2;
    QString entries_subFramePos3;
    QString entries_subFramePos4;
    QString entries_subFramePos5;
    QString entries_subFramePos6;
    QString entries_subFramePos7;
    QString entries_subFramePos8;
    QString entries_subFramePos9;
    QString entries_subFramePos10;
    QString entries_childFramePos1;
    QString entries_childFramePos2;
    QString entries_childFramePos3;
    QString entries_childFramePos4;
    QString entries_childFramePos5;
    QString entries_childFramePos6;
    QString entries_childFramePos7;
    QString entries_childFramePos8;
    QString entries_childFramePos9;
    QString entries_childFramePos10;
    QString entries_dataSource1;
    QString entries_dataSource2;
    QString entries_dataSource3;
    QString entries_dataSource4;
    QString entries_dataSource5;
    QString entries_dataSource6;
    QString entries_dataSource7;
    QString entries_dataSource8;
    QString entries_dataSource9;
    QString entries_dataSource10;
    QString entries_dataLength1;
    QString entries_dataLength2;
    QString entries_dataLength3;
    QString entries_dataLength4;
    QString entries_dataLength5;
    QString entries_dataLength6;
    QString entries_dataLength7;
    QString entries_dataLength8;
    QString entries_dataLength9;
    QString entries_dataLength10;

public:
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

};


#include <QStyledItemDelegate>
#include <QSet>
#include <QModelIndex>

class MultiColumnNonEditableDelegate : public QStyledItemDelegate
{
    QSet<int> nonEditableColumns; // 存储多个不可编辑的列索引
public:
    // 构造方法1：接收单个列索引
    explicit MultiColumnNonEditableDelegate(int column, QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {
        nonEditableColumns.insert(column);
    }

    // 构造方法2：接收列索引列表（支持多个列）
    explicit MultiColumnNonEditableDelegate(const QList<int>& columns, QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {
        for (int col : columns) {
            nonEditableColumns.insert(col);
        }
    }

    // 构造方法3：接收列索引的初始化列表（C++11支持）
    explicit MultiColumnNonEditableDelegate(std::initializer_list<int> columns, QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {
        for (int col : columns) {
            nonEditableColumns.insert(col);
        }
    }

    // 添加更多需要禁止编辑的列
    void addNonEditableColumn(int column) {
        nonEditableColumns.insert(column);
    }

    // 移除禁止编辑的列
    void removeNonEditableColumn(int column) {
        nonEditableColumns.remove(column);
    }

    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override
    {
        // 如果当前列在禁止编辑的集合中，返回 nullptr 禁止编辑
        if (nonEditableColumns.contains(index.column())) {
            return nullptr;
        }
        // 其他列使用默认编辑行为
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
};



#endif // FILEMACRODIALOG_H
