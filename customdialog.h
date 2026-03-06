#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H


#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>

class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr);
    QString getText1() const;
    QString getText2() const;

    static std::pair<QString, QString> getInputs(QWidget *parent = nullptr,
                                                const QString &title = "输入对话框",
                                                const QString &label1 = "文本框1:",
                                                const QString &label2 = "文本框2:");

private slots:
    void accept() override;
    void reject() override;

private:
    QLineEdit *m_textEdit1;
    QLineEdit *m_textEdit2;
    QString m_result1;
    QString m_result2;
};
#endif // CUSTOMDIALOG_H
