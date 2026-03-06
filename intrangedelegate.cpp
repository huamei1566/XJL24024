#include "intrangedelegate.h"

IntRangeDelegate::IntRangeDelegate(int min, int max, QObject *parent)
    : QItemDelegate(parent), minValue(min), maxValue(max)
{
}

QWidget* IntRangeDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QIntValidator *validator = new QIntValidator(minValue, maxValue, editor);
    editor->setValidator(validator);
    return editor;
}

void IntRangeDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(index.data(Qt::EditRole).toString());
}

void IntRangeDelegate::setModelData(QWidget *editor,
                                   QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();

    if (text.isEmpty()) {
        model->setData(index, minValue, Qt::EditRole);
    } else {
        model->setData(index, text, Qt::EditRole);
    }
}

void IntRangeDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
