#include "draggablebutton.h"
#include "droptargettable.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QDataStream>
#include <QtWidgets>


DraggableButton::DraggableButton(QWidget *parent)
                   : QPushButton(parent), m_dragging(false), m_tableCreated(false)
{
    // 设置按钮样式
            setStyleSheet("QPushButton {"
                          "background-color: #4CAF50;"
                          "color: white;"
                          "border: none;"
                          "border-radius: 5px;"
                          "padding: 10px 20px;"
                          "font-weight: bold;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #45a049;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #3d8b40;"
                          "}");

             m_mimeData = new QMimeData;
//    drag = std::make_unique<QDrag>(this);
//    drag->exec(Qt::CopyAction);
    //drag.reset();

}

QMimeData *DraggableButton::getmimeData() const
{
    return m_mimeData;
}



void DraggableButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
               m_dragStartPosition = event->pos();
               m_dragging = true;
               setCursor(Qt::ClosedHandCursor);
           }
           QPushButton::mousePressEvent(event);
}

void DraggableButton::mouseMoveEvent(QMouseEvent *event)
{



    if (event->buttons() & Qt::LeftButton) {
        startDrag();
    }
    QPushButton::mouseMoveEvent(event);
}

void DraggableButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
              m_dragging = false;
              setCursor(Qt::ArrowCursor);
              m_tableCreated = false; // 重置标志，允许下次拖动创建新表格
          }
    QPushButton::mouseReleaseEvent(event);
}

void DraggableButton::onsetQMimeData(QMimeData &mimedata)
{
    // 创建MIME数据
    m_mimeData = &mimedata;




}

void DraggableButton::createTableAtCursor()
{
    // 获取鼠标全局位置
          QPoint cursorPos = QCursor::pos();

          // 创建表格控件
          DropTargetTable *table = new DropTargetTable(parentWidget());

          // 设置表格位置（居中于鼠标）
          table->move(cursorPos - QPoint(table->width()/2, table->height()/2));

          // 设置表格标题
          table->setWindowTitle("动态创建的表格");

          // 显示表格
          table->show();

          // 添加淡入动画
          QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(table);
          table->setGraphicsEffect(effect);
          QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
          animation->setDuration(300);
          animation->setStartValue(0);
          animation->setEndValue(1);
          animation->start(QAbstractAnimation::DeleteWhenStopped);

          qDebug() << "表格创建于位置: " << table->pos();
}

void DraggableButton::startDrag()
{


    // 创建拖拽对象
    auto drag = std::make_unique<QDrag>(this);
    drag->setMimeData(m_mimeData);
    Qt::DropAction result = drag->exec(Qt::CopyAction);
    drag.reset();

}

