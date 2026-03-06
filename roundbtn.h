#ifndef ROUNDBTN_H
#define ROUNDBTN_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>

class roundBtn : public QPushButton
{
public:
     roundBtn(QWidget* parent = nullptr);

      void setBorderWidth(int width) ;
      void setBorderColor(const QColor& color);


protected:
     void paintEvent(QPaintEvent* event) override;

     bool hitButton(const QPoint& pos) const override;

     QSize sizeHint() const override;

private:
     int borderWidth;
     QColor borderColor;

     QColor GetBackgroundColor() const;
};

#endif // ROUNDBTN_H
