#ifndef SREPLAY_H
#define SREPLAY_H

#include <QString>
#include <QFile>
#define MAX_REPLAY_FILE 80
class SReplay
{
public:
    SReplay(QString filename);
    bool open();
    qint64 getframecnt();
    void seek(qint64 framecnt);
    QByteArray read(qint64 len);
    QByteArray read(qint64 curCnt, qint64 readCnt);
    void close();
    void setframestyle(int childlen, int sidelen, int wordlen, int fileHead);
    QFile* file;
private:
    void GetFileArrList();
    bool isOneTimeSaved(QString dstfilename);
private:
    QString filename;
    QFile fileArr[MAX_REPLAY_FILE];
    qint64 framecntArr[MAX_REPLAY_FILE];
    QString filenameList[MAX_REPLAY_FILE];
    int filenameIndex[MAX_REPLAY_FILE];
    qint64 filecnt;
    int childlen;
    int sidelen;
    int wordlen;
    int nTimeAndFrameBytes;
    int filehead;
    QString replayfilename;
};

#endif // SREPLAY_H
