#include "draggabletable.h"
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QDataStream>

DraggableTable::DraggableTable( QWidget *parent)
    : QTableWidget(0, 0, parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setDragEnabled(true);
    setAcceptDrops(false);  // 自身不接受放置
    setHorizontalHeaderLabels({"Col1", "Col2", "Col3"});
    setVerticalHeaderLabels({"Row1", "Row2"});

    // 填充示例数据
    for (int r = 0; r < rowCount(); ++r) {
        for (int c = 0; c < columnCount(); ++c) {
            setItem(r, c, new QTableWidgetItem(QString("Data %1-%2").arg(r).arg(c)));
        }
    }
}

void DraggableTable::onsetQMimeData(QMimeData &mimedata)
{
    // 创建MIME数据
    m_mimeData = new QMimeData;
    m_mimeData = &mimedata;

}

void DraggableTable::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        startDrag();
    }
    QTableWidget::mouseMoveEvent(event);
}

void DraggableTable::startDrag()
{


    // 创建拖拽对象
    QDrag *drag = new QDrag(this);
    drag->setMimeData(m_mimeData);
    drag->exec(Qt::CopyAction);
}
