#ifndef DRAGGABLETABLE_H
#define DRAGGABLETABLE_H

#include <QTableWidget>

class DraggableTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit DraggableTable(QWidget *parent = nullptr);



public slots:
    void onsetQMimeData(QMimeData &mimedata);



protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void startDrag();
    QMimeData *m_mimeData;
};

#endif // DRAGGABLETABLE_H
