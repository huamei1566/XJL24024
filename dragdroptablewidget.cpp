#include "dragdroptablewidget.h"
#include <QUrl>
#include <QFileInfo>
#include <QHeaderView>

DragDropTableWidget::DragDropTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    // 基本表格设置
    setColumnCount(3);
    setHorizontalHeaderLabels({"文件名", "大小", "类型"});
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 启用拖放功能
    setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::DropOnly);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DragDropTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    // 检查拖拽数据中是否包含文件
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void DragDropTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    // 接受文件拖拽操作
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void DragDropTableWidget::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        // 获取所有拖入的文件路径
        QList<QUrl> urlList = mimeData->urls();

        for (const QUrl &url : urlList) {
            QString filePath = url.toLocalFile();
            QFileInfo fileInfo(filePath);

            if (fileInfo.isFile()) {  // 只处理文件
                int row = rowCount();
                insertRow(row);

                // 文件名
                setItem(row, 0, new QTableWidgetItem(fileInfo.fileName()));

                // 文件大小 (格式化显示)
                QString sizeStr = QString("%1 KB").arg(fileInfo.size() / 1024.0, 0, 'f', 1);
                setItem(row, 1, new QTableWidgetItem(sizeStr));

                // 文件类型 (通过后缀判断)
                setItem(row, 2, new QTableWidgetItem(fileInfo.suffix().toUpper() + " 文件"));
            }
        }
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}
