#ifndef INTRANGEDELEGATE_H
#define INTRANGEDELEGATE_H

#include <QItemDelegate>
#include <QLineEdit>
#include <QIntValidator>

class IntRangeDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    IntRangeDelegate(int min, int max, QObject *parent = nullptr);

    // 重写父类的函数
    QWidget* createEditor(QWidget *parent,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

private:
    int minValue;
    int maxValue;
};

#endif // INTRANGEDELEGATE_H
