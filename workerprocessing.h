#ifndef WORKERPROCESSING_H
#define WORKERPROCESSING_H


#include <QObject>
#include <QFile>
#include <QByteArray>
#include <QMutex>
#include <QDebug>
#include <QElapsedTimer>
#include <QUdpSocket>

class MainWindow;

class WorkerProcessing : public QObject
{
    Q_OBJECT
public:
    explicit WorkerProcessing(/*const QString &filePath , const QString &filePath2 ,*/  QObject *parent = nullptr);
    ~WorkerProcessing();

    // 检查文件准备状态
    bool isReady() const;
    // 获取当前读取位置
    qint64 currentPosition() const;
    // 获取文件大小
    qint64 fileSize() const;
    // 获取文件路径
    QString filePath() const { return m_filePath; }

    void FillBuffer1();
    void FillBuffer2();

    MainWindow* owner;
    void setOwner(MainWindow* mainwindow);

    int testig = 0;
    void setTestig(int i);

    bool mofei1_ig = false;
    bool mofei2_ig = false;
    void setmofei1_ig(bool t_mofei1_ig);
    void setmofei2_ig(bool t_mofei2_ig);

    bool ensureFileOpen();
    bool ensureFileOpen2();

    void setfilepath1(QString filepath);
    void setfilepath2(QString filepath);

public slots:
    // 核心功能槽函数 - 被信号唤醒读取指定字节数
    void read_tx1_buffer_capacity(int bigreadandsender1 ,int biaoz);
    void read_tx2_buffer_capacity(int bigreadandsender1 ,int biaoz);

    void on_read_buffer(int bigreadandsender1 ,int biaoz , int bigreadandsender2 ,int biaoz2);



    // 重置文件位置到开头
    void resetPosition();
    // 关闭文件（可在对象析构前调用）
    void closeFile();

signals:
    // 数据读取完成信号
    void dataRead(QByteArray data, int bytesProcessed);
    // 错误信号
    void errorOccurred(const QString &message);

    void Refreshprogress1(int value);
    void Refreshprogress2(int value);


    void dataCountsize(int count);



private:


    void readAndSendData(int byteCount ,int portvalue);

    QFile m_file;
    QFile m_file2;
    mutable QMutex m_mutex;
    QString m_filePath;
    QString m_filePath2;
    qint64 m_totalBytesRead = 0;
    qint64 m_totalBytesRead2 = 0;

    QByteArray *Buffer1;
    QByteArray *Buffer2;

    QByteArray *Buffertr1[2];
    QByteArray *Buffertr2[2];


    int mofei1wenjian = 1 ; // 0 不发送 ,1 Buffer1[0]中取数  , 2 Buffer1[1]中取数
    int mofei2wenjian = 1 ; // 0 不发送 ,1 Buffer2[0]中取数  , 2 Buffer2[1]中取数

    QByteArray *testBuffer;

    const int SIZE_SIZE = 63000;

    const int CHUNK_READ_SIZE = 264;   // 每次读取的块大小
    const int CHUNK_HEADER_SIZE = 8;   // 每个块要丢弃的头部大小
    const int VALID_DATA_PER_CHUNK = CHUNK_READ_SIZE - CHUNK_HEADER_SIZE; // 每块有效数据

    const int CHUNK_READ_SIZE2 = 264;   // 每次读取的块大小
    const int CHUNK_HEADER_SIZE2 = 8;   // 每个块要丢弃的头部大小
    const int VALID_DATA_PER_CHUNK2 = CHUNK_READ_SIZE2 - CHUNK_HEADER_SIZE2; // 每块有效数据


    quint8 itext1 = 0;
    quint8 itext2 = 0;

    QUdpSocket* udpender;
};


#endif // WORKERPROCESSING_H
