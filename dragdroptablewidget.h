#ifndef DRAGDROPTABLEWIDGET_H
#define DRAGDROPTABLEWIDGET_H

#include <QTableWidget>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>



class DragDropTableWidget : public QTableWidget
{
    Q_OBJECT
  public:
      explicit DragDropTableWidget(QWidget *parent = nullptr);

     void startDrag();

  protected:
      // 重写拖放事件处理函数
      void dragEnterEvent(QDragEnterEvent *event) override;
      void dragMoveEvent(QDragMoveEvent *event) override;
      void dropEvent(QDropEvent *event) override;
};

#endif // DRAGDROPTABLEWIDGET_H
