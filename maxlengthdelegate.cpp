#include "maxlengthdelegate.h"
#include <QKeyEvent>
#include <QLineEdit>
#include <QDebug>

MaxLengthDelegate::MaxLengthDelegate(int maxLength, QObject *parent)
    : QItemDelegate(parent), maxLength(maxLength)
{
}

QWidget* MaxLengthDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QLineEdit *editor = new QLineEdit(parent);
    // 设置最大长度
    editor->setMaxLength(maxLength);

    return editor;
}

void MaxLengthDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(value);
}

void MaxLengthDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);
}

bool MaxLengthDelegate::eventFilter(QObject *editor, QEvent *event)
{
    // 只处理QLineEdit
    if (event->type() == QEvent::KeyPress) {
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        if (lineEdit) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

            // 当文本达到最大长度时，阻止字符输入
            if (lineEdit->text().length() >= maxLength &&
                !(keyEvent->key() == Qt::Key_Backspace ||
                  keyEvent->key() == Qt::Key_Delete ||
                  keyEvent->key() == Qt::Key_Left ||
                  keyEvent->key() == Qt::Key_Right ||
                  keyEvent->key() == Qt::Key_Home ||
                  keyEvent->key() == Qt::Key_End)) {
                // 阻止超过限制的输入
                return true;
            }
        }
    }

    // 其他事件传递给基类处理
    return QItemDelegate::eventFilter(editor, event);
}
