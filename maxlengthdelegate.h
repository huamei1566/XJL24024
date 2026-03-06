#ifndef MAXLENGTHDELEGATE_H
#define MAXLENGTHDELEGATE_H

#include <QItemDelegate>
#include <QLineEdit>

class MaxLengthDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit MaxLengthDelegate(int maxLength = 8, QObject *parent = nullptr);

    // 重写QItemDelegate的必要方法
    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    bool eventFilter(QObject *editor, QEvent *event) override;

private:
    int maxLength;  // 最大输入长度
};

#endif // MAXLENGTHDELEGATE_H
