#ifndef SENDERMANGER_H
#define SENDERMANGER_H

#include <QObject>
#include <QUdpSocket>

class sendermanger : public QObject
{
    Q_OBJECT
public:
    explicit sendermanger(QObject *parent = 0);

signals:


public slots:
  void onreadRequest(int count , int port);

private:
    QUdpSocket* m_Sender;


};

#endif // SENDERMANGER_H
