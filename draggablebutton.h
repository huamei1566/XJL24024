#ifndef DRAGGABLEBUTTON_H
#define DRAGGABLEBUTTON_H

#include<QPushButton>

#include<QMimeData>
#include<QDrag>
#include <memory>

class DraggableButton : public QPushButton
{
public:
    DraggableButton(QWidget *parent = nullptr);
    QMimeData* getmimeData() const;

protected:

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void onsetQMimeData(QMimeData &mimedata);

private:
    void createTableAtCursor();
    void startDrag();
    QDrag* drag;  // 指定父对象为当前QObject


    bool m_dragging;
    bool m_tableCreated;
    QPoint m_dragStartPosition;
    QMimeData* m_mimeData;
   // std::unique_ptr<QDrag> drag;


};

#endif // DRAGGABLEBUTTON_H
