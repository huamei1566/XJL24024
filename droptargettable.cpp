#include "droptargettable.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QDataStream>


DropTargetTable::DropTargetTable( QWidget* parent)
    : QTableWidget(0, 0, parent) {
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setHorizontalHeaderLabels({"A", "B", "C", "D", "E"});
    setVerticalHeaderLabels({"1", "2", "3", "4", "5"});
    setSelectionMode(QAbstractItemView::SingleSelection);

    // 初始填充空数据
    for (int r = 0; r < rowCount(); ++r) {
        for (int c = 0; c < columnCount(); ++c) {
            setItem(r, c, new QTableWidgetItem(""));
        }
    }
}

//void DropTargetTable::setColumnCount(int columns)
//{
//   QTableWidget::setColumnCount(columns);
//}

void DropTargetTable::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-qtablewidget-drag")) {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void DropTargetTable::dragMoveEvent(QDragMoveEvent* event) {
    if (event->mimeData()->hasFormat("application/x-qtablewidget-drag")) {
        event->acceptProposedAction();
    }
    else {
            event->ignore();
        }
}

void DropTargetTable::dropEvent(QDropEvent* event) {


    if (!event->mimeData()->hasFormat("application/x-qtablewidget-drag")) {
           event->ignore();
           return;
       }

       // 获取放置位置
       QPoint pos = event->pos();
       QModelIndex index = indexAt(pos);
       if (!index.isValid()) return;

       int targetRow = index.row();
       int targetCol = index.column();

       // 反序列化数据
       QByteArray itemData = event->mimeData()->data("application/x-qtablewidget-drag");
       QDataStream stream(&itemData, QIODevice::ReadOnly);

       int rows, cols;
       stream >> rows >> cols;

       // 计算实际可填充的区域（不改变表格大小）
       int endRow = qMin(targetRow + rows, rowCount());
       int endCol = qMin(targetCol + cols, columnCount());
       int actualRows = endRow - targetRow ;
       int actualCols = endCol - targetCol ;


//       yibuyuanrow = actualRows ;
//       yibuyuancol = actualCols ;


       // 填充数据到目标位置（不超出表格范围）
       for (int r = 0; r < actualRows; ++r) {

           for (int c = 0; c < actualCols; ++c) {
               QString text;
               stream >> text;

               // 处理目标单元格
               int rowIndex = targetRow + r;
               int colIndex = targetCol + c;



               QTableWidgetItem* item = this->item(rowIndex, colIndex);
               if (!item) {
                   item = new QTableWidgetItem;
                   setItem(rowIndex, colIndex, item);
               }
               item->setText("异步源");

           }
       }

       // 跳过剩余数据（如果有超出表格范围的部分）
       event->acceptProposedAction();


}
