#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QMutex>

class Logger : public QObject
{
    Q_OBJECT
public:
    enum LogLevel {
        Debug,
        Info,
        Warning,
        Critical,
        Fatal
    };

    static Logger* instance();
    void setLogFile(const QString& filePath);
    void log(LogLevel level, const QString& message);

    // 便捷方法
    static void debug(const QString& message);
    static void info(const QString& message);
    static void warning(const QString& message);
    static void critical(const QString& message);
    static void fatal(const QString& message);

private:
    Logger();
    ~Logger();
    static Logger* m_instance;
    QFile m_logFile;
    QMutex m_mutex;
};

#endif // LOGGER_H
