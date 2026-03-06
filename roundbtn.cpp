#include "roundbtn.h"


roundBtn::roundBtn(QWidget *parent): QPushButton(parent),
    borderWidth(2),  // 默认边框宽度
    borderColor(Qt::gray) {  // 默认边框颜色

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // 固定大小
    setMinimumSize(50, 40); // 确保按钮为正方形

}

void roundBtn::setBorderWidth(int width)
{
    borderWidth = qMax(1, width);
    update();
}

void roundBtn::setBorderColor(const QColor &color)
{
    borderColor = color;
    update();
}

void roundBtn::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
           painter.setRenderHint(QPainter::Antialiasing);

           // 绘制背景圆形
           QRect bgRect = rect().adjusted(borderWidth, borderWidth, -borderWidth, -borderWidth);
           painter.setBrush(GetBackgroundColor());
           painter.setPen(Qt::NoPen);
           painter.drawEllipse(bgRect);

           // 绘制边框
           if (borderWidth > 0) {
               QPen pen(borderColor);
               pen.setWidth(borderWidth);
               painter.setPen(pen);
               painter.setBrush(Qt::NoBrush);
               painter.drawEllipse(bgRect);
           }

           // 绘制文字
           if (!text().isEmpty()) {
               painter.setPen(palette().buttonText().color());
               painter.drawText(rect(), Qt::AlignCenter, text());
           }
       }



bool roundBtn::hitButton(const QPoint &pos) const
{
    // 将点击位置转换为相对于圆心的坐标
            QPoint center = rect().center();
            int radius = width() / 2;
            int dx = pos.x() - center.x();
            int dy = pos.y() - center.y();
            return (dx * dx + dy * dy) <= (radius * radius); // 判断是否在圆内
}

QSize roundBtn::sizeHint() const
{
    return QSize(50, 40); // 推荐大小为60x60
}

QColor roundBtn::GetBackgroundColor() const
{
    if (isDown()) return palette().dark().color();
          if (underMouse()) return palette().light().color();
          return palette().button().color();
}





