#include <QPropertyAnimation>
#include <QTimer>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QFontMetrics>
#include <QDesktopServices>

#include "notify.h"

Notify::Notify (int displayTime, QWidget *parent) : QWidget(parent),
    displayTime(displayTime)
{

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint| Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);

    backgroundLabel = new QLabel(this);
    backgroundLabel->move(0, 0);
    backgroundLabel->setObjectName("notify-background");


    QHBoxLayout *mainLayout = new QHBoxLayout(backgroundLabel);
    QVBoxLayout *contentLayout = new QVBoxLayout();

    iconLabel = new QLabel(backgroundLabel);
    iconLabel->setFixedWidth(40);
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setObjectName("notify-icon");

    titleLabel = new QLabel(backgroundLabel);
    titleLabel->setObjectName("notify-title");

    bodyLabel = new QLabel(backgroundLabel);
    bodyLabel->setObjectName("notify-body");
    QFont font = bodyLabel->font();
    font.setPixelSize(12);
    bodyLabel->setFont(font);

    contentLayout->addWidget(titleLabel);
    contentLayout->addWidget(bodyLabel);

    mainLayout->addWidget(iconLabel);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(contentLayout);


    closeBtn = new QPushButton("×", backgroundLabel);
    closeBtn->setObjectName("notify-close-btn");
    closeBtn->setFixedSize(24, 24);
    connect(closeBtn, &QPushButton::clicked, this, [this]{
        Q_EMIT disappeared();
    });

}


void Notify::showGriant()
{
    this->show();

    titleLabel->setText(title);
    QPixmap tempPix = QPixmap(this->icon);
    tempPix = tempPix.scaled(QSize(30, 30), Qt::KeepAspectRatio);
    iconLabel->setPixmap(tempPix);

    backgroundLabel->setFixedSize(this->size());
    closeBtn->move(backgroundLabel->width() - closeBtn->width(), 0);

    // 超过长度省略号
    QFontMetrics elidfont(bodyLabel->font());
    QString text = elidfont.elidedText(this->body, Qt::ElideRight, bodyLabel->width() - 5);
    bodyLabel->setText(text);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setDuration(200);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, this, [animation, this](){
        animation->deleteLater();
        QTimer::singleShot(displayTime, this, [this](){
            this->hideGriant();
        });
    });
}

void Notify::hideGriant()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setStartValue(this->windowOpacity());
    animation->setEndValue(0);
    animation->setDuration(2000);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, this, [animation, this](){
        this->hide();
        animation->deleteLater();
        Q_EMIT disappeared();
    });
}

void Notify::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        if(!url.isEmpty()){
            QDesktopServices::openUrl(url);
        }
        hideGriant();
    }
}

void Notify::setUrl(const QString &value)
{
    url = value;
}


void Notify::setBody(const QString &value)
{
    body =  value;
}

void Notify::setTitle(const QString &value)
{
    title = value;
    setMySheet();

}

void Notify::setIcon(const QString &value)
{
    icon = value;
    icon = ":/qrc/5.png";
}
void Notify::setMySheet(){

    if(title == "信息")
    {
        this->setStyleSheet(    "#notify-background {"
                                "background-color: white;"
                                "border: 1px solid #e0e0e0;"    /* 更浅的边框 */
                                "border-radius: 6px;"           /* 更大的圆角 */
                                ////"box-shadow: 0 3px 6px rgba(0,0,0,0.1);" /* 添加微妙阴影 */
                                "}"

                                "#notify-close-btn {"
                                "border: 0;"
                                "color: #999;"
                                "font-weight: bold;"
                                "font-size: 16px;"
                                "background: transparent;"      /* 默认透明背景 */
                                "border-radius: 12px;  "         /* 圆形按钮 */
                                "}"

                                "#notify-close-btn:hover {"
                                "background: #f0f0f0;"          /* 更柔和的悬停背景 */
                                "color: #666;"                  /* 文字变深 */
                                 "}");
    }
    else if(title == "警告")
    {
        this->setStyleSheet("#notify-background {"
                            "border: 1px solid #ccc;"
                            "background:white;"
                            "border-radius: 4px;"
                            "} "
                            "#notify-icon{"
                            "background:pink;"
                            "}"
                            "#notify-title{"
                            "font-weight: bold;"
                            "color: #333;"
                            "font-size: 14px;"
                            "}"
                            "#notify-body{"
                            "color: #444;"
                            "}"
                            "#notify-close-btn{ "
                            "border: 0;"
                            "color: #999;"
                            "}"
                            "#notify-close-btn:hover{ "
                            "background: #ccc;"
                            "}");


    }else if(title == "提醒")
    {
        this->setStyleSheet("#notify-background {"
                            "border: 1px solid #ccc;"
                            "background:white;"
                            "border-radius: 4px;"
                            "} "
                            "#notify-icon{"
                            "background:#96a48b;"
                            "}"
                            "#notify-title{"
                            "font-weight: bold;"
                            "color: #333;"
                            "font-size: 14px;"
                            "}"
                            "#notify-body{"
                            "color: #444;"
                            "}"
                            "#notify-close-btn{ "
                            "border: 0;"
                            "color: #999;"
                            "}"
                            "#notify-close-btn:hover{ "
                            "background: #ccc;"
                            "}");


    }
    else
    {
        this->setStyleSheet("#notify-background {"
                            "border: 1px solid #ccc;"
                            "background:white;"
                            "border-radius: 4px;"
                            "} "
                            "#notify-icon{"
                            "background:#C0C4CC;"
                            "}"
                            "#notify-title{"
                            "font-weight: bold;"
                            "color: #333;"
                            "font-size: 14px;"
                            "}"
                            "#notify-body{"
                            "color: #444;"
                            "}"
                            "#notify-close-btn{ "
                            "border: 0;"
                            "color: #999;"
                            "}"
                            "#notify-close-btn:hover{ "
                            "background: #ccc;"
                            "}");

    }

}
