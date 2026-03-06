#ifndef TXTWORKER_H
#define TXTWORKER_H

#include <QObject>
#include <QFile>

class txtworker : public QObject
{
    Q_OBJECT
public:
    explicit txtworker(QObject *parent = 0);

    QFile txtfile;


    QString filepath;


signals:

public slots:

    void starting(QString filepath,
                  QString pindian1 , QString pinpian1 ,QString tiaozhi1 ,QString gonglv1,
                  QString malv1 ,QString zhenchang1 ,QString zhenmazu1 ,QString fuzhenfangshi1 ,QString fuzhenchang1,
                  QString maxing1 ,QString bianmaweizhi1,
                  QString pindian2 , QString pinpian2 ,QString tiaozhi2 ,QString gonglv2,
                  QString malv2 ,QString zhenchang2 ,QString zhenmazu2 ,QString fuzhenfangshi2 ,QString fuzhenchang2,
                  QString maxing2 ,QString bianmaweizhi2);

};

#endif // TXTWORKER_H
