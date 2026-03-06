#ifndef SINGLEINSTANCEGUARD_H
#define SINGLEINSTANCEGUARD_H
#include <QObject>
#include <QSharedMemory>
#include <QLocalServer>

class SingleInstanceGuard : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstanceGuard(QObject *parent = nullptr);
    ~SingleInstanceGuard();

    bool isPrimaryInstance() const;
    void notifyPrimary();

signals:
    void activationRequested(); // 主实例收到激活请求时发射

private slots:
    void handleConnection();

private:
    void cleanUp();

    QSharedMemory m_sharedMem;
    QLocalServer m_server;
    bool m_isPrimary = false;
    static const QString SERVER_NAME;
};
#endif // SINGLEINSTANCEGUARD_H
