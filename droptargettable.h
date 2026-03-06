#ifndef DROPTARGETTABLE_H
#define DROPTARGETTABLE_H

#include <QTableWidget>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDataStream>

// 可放置的表格控件
class DropTargetTable : public QTableWidget {
    Q_OBJECT
public:
    explicit DropTargetTable(QWidget* parent = nullptr);


    int yibuyuanrow = 0;
    int yibuyuancol = 0;
    int GNSSrow = 0;
    int GNSScol = 0;
    int ankongrow = 0;
    int ankongcol = 0;

//    void setColumnCount(int columns) ;

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    void dropEvent(QDropEvent* event) override;
};
#endif // DROPTARGETTABLE_H
