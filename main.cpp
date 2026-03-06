#include "mainwindow.h"

#include "singleinstanceguard.h"
#include <QMessageBox>
#include <QApplication>
#include <QtGlobal>
#include <QFile>
#include <QTextStream>
#include <QDateTime>


// 自定义消息处理函数
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    Q_UNUSED(context);

    QString logLevel;
    switch (type) {
    case QtDebugMsg:
        logLevel = "DEBUG";
        break;
    case QtInfoMsg:
        logLevel = "INFO";
        break;
    case QtWarningMsg:
        logLevel = "WARN";
        break;
    case QtCriticalMsg:
        logLevel = "CRITICAL";
        break;
    case QtFatalMsg:
        logLevel = "FATAL";
        break;
    }

    QString logMessage = QString("[%1] [%2] %3")
                             .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"))
                             .arg(logLevel)
                             .arg(msg);

    // 输出到日志文件
    QFile logFile("app.log");
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&logFile);
        stream << logMessage << "\n";
        logFile.close();
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //qInstallMessageHandler(customMessageHandler);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec); // 设置本地编码

    // 设置唯一应用ID
        const QString appId = "com.XJL.demoUI";
        QApplication::setApplicationName(appId);
        QApplication::setOrganizationName("XJL");

        // 设置应用程序图标（影响任务栏）
        a.setWindowIcon(QIcon("qrc/icon.jpg"));

        SingleInstanceGuard guard;

        if (!guard.isPrimaryInstance()) {
            qDebug() << "检测到已有实例，尝试激活主窗口";

            guard.notifyPrimary(); // 尝试激活已有实例

            QMessageBox::warning(nullptr,
                "程序已运行",
                "该程序已在运行中，无法打开多个实例！");

            return 1;
        }

    MainWindow w;
    w.setWindowIcon(QIcon("qrc/icon.jpg")); // 可选：同步设置窗口图标

    w.show();
    return a.exec();
}
