#include "singleinstanceguard.h"
#include <QLocalSocket>
#include <QCoreApplication>

const QString SingleInstanceGuard::SERVER_NAME = "com.XJL.demoUI";

SingleInstanceGuard::SingleInstanceGuard(QObject *parent)
    : QObject(parent)
{
    // 尝试附加到共享内存
        m_sharedMem.setKey(SERVER_NAME);
        if (m_sharedMem.attach()) {
            m_isPrimary = false;
            m_sharedMem.detach();  // 从共享内存分离
            return;
        }

        // 创建新共享内存（主实例）
        if (m_sharedMem.create(1)) {
            m_isPrimary = true;

            // 清理可能的残留服务器
            QLocalServer::removeServer(SERVER_NAME); // 先移除可能的残留

            // 设置本地服务器
            connect(&m_server, &QLocalServer::newConnection,
                    this, &SingleInstanceGuard::handleConnection);

            if (!m_server.listen(SERVER_NAME)) {
                qWarning() << "无法启动本地服务器:" << m_server.errorString();
                cleanUp();
                m_isPrimary = false; // 如果监听失败，则无法成为主实例
            }
        }
}

SingleInstanceGuard::~SingleInstanceGuard()
{
    if (m_isPrimary) {
        cleanUp();
    }
}

bool SingleInstanceGuard::isPrimaryInstance() const
{
    return m_isPrimary;
}

void SingleInstanceGuard::notifyPrimary()
{
    if (m_isPrimary) return;

    QLocalSocket socket;
    socket.connectToServer(SERVER_NAME, QIODevice::WriteOnly);
    if (socket.waitForConnected(500)) {
        socket.write("ACTIVATE");
        socket.waitForBytesWritten();
    }
    socket.disconnectFromServer();
}

void SingleInstanceGuard::handleConnection()
{
    QLocalSocket *socket = m_server.nextPendingConnection();
    if (socket) {
        socket->waitForReadyRead(100); // 简单读取
        socket->deleteLater();
        emit activationRequested(); // 通知主窗口激活
    }
}

void SingleInstanceGuard::cleanUp()
{
    if (m_server.isListening()) {
        m_server.close();
    }
    QLocalServer::removeServer(SERVER_NAME);

    if (m_sharedMem.isAttached()) {
        m_sharedMem.detach();
    }
}
