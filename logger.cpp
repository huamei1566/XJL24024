#include "logger.h"

#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>

Logger* Logger::m_instance = nullptr;

Logger::Logger() {

    QString appDir = QCoreApplication::applicationDirPath();
    QDir dir(appDir);
    QString folderPath = dir.absoluteFilePath("Log日志");

    // 确保文件夹存在
    if (!dir.exists("安控记录")) {
        if (!dir.mkpath("安控记录")) {
            qDebug() << "无法创建目录:" << folderPath;
            return; // 或者处理错误
        }
    }

    QDate currentDate = QDate::currentDate();

    // 默认日志文件，可以后续用setLogFile改变
    setLogFile(folderPath + QString("/log%1.txt").arg(currentDate.toString("yyyy-MM-dd")));
}

Logger::~Logger() {
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
}

Logger* Logger::instance() {
    static QMutex mutex;
    QMutexLocker locker(&mutex);
    if (m_instance == nullptr) {
        m_instance = new Logger();
    }
    return m_instance;
}

void Logger::setLogFile(const QString& filePath) {
    QMutexLocker locker(&m_mutex);
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
    m_logFile.setFileName(filePath);
    // 如果文件所在目录不存在则创建
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.dir();
    if (!dir.exists()) {
        dir.mkpath(dir.path());
    }
    // 以追加方式打开文件
    if (!m_logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        // 打开失败，可以抛出异常或记录到控制台等
        //qWarning() << "Failed to open log file:" << filePath;
    }
}

void Logger::log(LogLevel level, const QString& message) {
    QMutexLocker locker(&m_mutex);
    if (!m_logFile.isOpen()) {
        return;
    }

    QString levelStr;
    switch (level) {
    case Debug: levelStr = "DEBUG"; break;
    case Info: levelStr = "INFO"; break;
    case Warning: levelStr = "WARNING"; break;
    case Critical: levelStr = "CRITICAL"; break;
    case Fatal: levelStr = "FATAL"; break;
    }

    QString logMessage = QString("[%1] [%2] %3\n")
                             .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
                             .arg(levelStr)
                             .arg(message);

    // 写入文件
    m_logFile.write(logMessage.toUtf8());
    m_logFile.flush(); // 确保写入

    // 同时输出到控制台（在调试模式下）
#ifdef QT_DEBUG
    qDebug().noquote() << logMessage.trimmed();
#endif
}

// 便捷方法
void Logger::debug(const QString& message) {
    instance()->log(Debug, message);
}

void Logger::info(const QString& message) {
    instance()->log(Info, message);
}

void Logger::warning(const QString& message) {
    instance()->log(Warning, message);
}

void Logger::critical(const QString& message) {
    instance()->log(Critical, message);
}

void Logger::fatal(const QString& message) {
    instance()->log(Fatal, message);
}
