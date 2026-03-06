#include "CustomDialog.h"
#include <QDialogButtonBox>

CustomDialog::CustomDialog(QWidget *parent)
    : QDialog(parent)
    , m_textEdit1(new QLineEdit(this))
    , m_textEdit2(new QLineEdit(this))
    , m_result1("")
    , m_result2("")
{
    setWindowTitle("输入对话框");

    QLabel *label1 = new QLabel("代号:", this);
    QLabel *label2 = new QLabel("保存时间:", this);

    label2->setEnabled(false);
    m_textEdit2->setEnabled(false);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    m_textEdit2->setText("未保存");

    // 第一个文本框
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(label1);
    layout1->addWidget(m_textEdit1);

    // 第二个文本框
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(label2);
    layout2->addWidget(m_textEdit2);

    // 按钮
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                       QDialogButtonBox::Cancel,
                                                       this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CustomDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CustomDialog::reject);

    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
    resize(300, 150);
}

QString CustomDialog::getText1() const
{
    return m_result1;
}

QString CustomDialog::getText2() const
{
    return m_result2;
}

void CustomDialog::accept()
{
    m_result1 = m_textEdit1->text();
    m_result2 = m_textEdit2->text();
    QDialog::accept();
}

void CustomDialog::reject()
{
    m_result1.clear();
    m_result2.clear();
    QDialog::reject();
}

std::pair<QString, QString> CustomDialog::getInputs(QWidget *parent,
                                                   const QString &title,
                                                   const QString &label1,
                                                   const QString &label2)
{
    CustomDialog dialog(parent);
    dialog.setWindowTitle(title);

    QLayout *layout = dialog.layout();
    if (layout && layout->itemAt(0) && layout->itemAt(0)->layout()) {
        QHBoxLayout *hLayout1 = qobject_cast<QHBoxLayout*>(layout->itemAt(0)->layout());
        if (hLayout1 && hLayout1->itemAt(0) && hLayout1->itemAt(0)->widget()) {
            QLabel *label = qobject_cast<QLabel*>(hLayout1->itemAt(0)->widget());
            if (label) label->setText(label1);
        }
    }

    if (layout && layout->itemAt(1) && layout->itemAt(1)->layout()) {
        QHBoxLayout *hLayout2 = qobject_cast<QHBoxLayout*>(layout->itemAt(1)->layout());
        if (hLayout2 && hLayout2->itemAt(0) && hLayout2->itemAt(0)->widget()) {
            QLabel *label = qobject_cast<QLabel*>(hLayout2->itemAt(0)->widget());
            if (label) label->setText(label2);
        }
    }

    dialog.exec();
    return std::make_pair(dialog.getText1(), dialog.getText2());
}
