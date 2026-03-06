#include "sreplay.h"
#include <QDir>
#include <QFileInfo>
#include<QFileInfoList>
#include <QDebug>
//#include "function.h"
SReplay::SReplay(QString filename)
{
    this->filename=filename;
    childlen=256;
    sidelen=64;
    wordlen=8;
    int nChildFrameBytes=childlen;
    if(wordlen>8) nChildFrameBytes*=2;
    nTimeAndFrameBytes=(nChildFrameBytes+8)*sidelen;
}
void SReplay::setframestyle(int childlen,int sidelen,int wordlen,int fileHead)
{
    this->childlen=childlen;
    this->sidelen=sidelen;
    this->wordlen=wordlen;
    this->filehead = fileHead;
    int nChildFrameBytes=childlen;
    if(wordlen>8) nChildFrameBytes*=2;
    nTimeAndFrameBytes=(nChildFrameBytes+8)*sidelen;
}

bool SReplay::open()
{   QString path=filename.left(filename.lastIndexOf('/')+1);
    QDir dir(path);
    QFileInfoList list=dir.entryInfoList();
    dir.setFilter(QDir::Files|QDir::NoSymLinks);
    int file_count=list.count();
    int index=0;
    filecnt=0;

    QStringList srcindex=filename.split('.');
    filenameIndex[filecnt]=srcindex.at(1).toInt();
    filenameList[filecnt++]=filename;
    for(index=0;index<file_count;index++)
    {
        QFileInfo file_info=list.at(index);
        QString suffix=file_info.suffix();
        if(QString::compare(suffix,QString("dat"),Qt::CaseInsensitive)==0)
        {
            QString absolute_file_path=file_info.absoluteFilePath();
            if(filename==absolute_file_path)
                continue;
            if(isOneTimeSaved(absolute_file_path))
            {
                filenameList[filecnt++]=absolute_file_path;
            }
        }

    }

    GetFileArrList();

    for(int i=0;i<filecnt;i++)
    {
        //qDebug()<<filenameList[i];
        fileArr[i].setFileName(filenameList[filenameIndex[i]]);
        if(!fileArr[i].open(QIODevice::ReadOnly))
        {
            for(int j=0;j<i;j++)
                fileArr[j].close();
            return false;
        }
        // qDebug()<<filenameList[filenameIndex[i]];

    }
    file=&fileArr[0];

    return true;
}

qint64 SReplay::getframecnt()
{
    int allcnt=0;
    for(int i=0;i<filecnt;i++)
    {
        framecntArr[i]= (quint64)(fileArr[i].size() - filehead)/(childlen + 8);
        allcnt+= framecntArr[i];
    }
    // qDebug()<<allcnt;
    return allcnt;
}

void SReplay::seek(qint64 framecnt)
{
    qint64 totelcnt=0;
    for(int i=0;i<filecnt;i++)
    {
        totelcnt+=framecntArr[i];
        if(framecnt<totelcnt)
        {
            file=&fileArr[i];
            replayfilename=file->fileName();
            if(i==0)
                file->seek(framecnt*(childlen + 8) + filehead);
            else
                file->seek((framecnt-(totelcnt-framecntArr[i-1]))*(childlen + 8) + filehead);
            break;
        }
    }
}

QByteArray SReplay::read(qint64 len)
{
    return file->read(len);
}
QByteArray SReplay::read(qint64 curCnt,qint64 readCnt)
{
    qint64 totelcnt=0;
    QByteArray ret;
    for(int i=0;i<filecnt;i++)
    {
        totelcnt+=framecntArr[i];
        if(curCnt+readCnt<=totelcnt)
        {
            file=&fileArr[i];
            replayfilename=file->fileName();

            file->seek((curCnt-(totelcnt-framecntArr[i]))*(childlen + 8) + filehead);
            return file->read(readCnt*(childlen + 8));
        }
        else if((curCnt+readCnt>totelcnt)&&((curCnt-totelcnt)<0))
        {
            int precnt=totelcnt-curCnt;
            int backcnt=readCnt-precnt;

            file->seek((curCnt-(totelcnt-framecntArr[i]))*(childlen + 8) + filehead);

            ret=file->read(precnt*(childlen + 8));
            if(i==filecnt-1)
                return ret;
            file=&fileArr[i+1];
            replayfilename=file->fileName();
            file->seek(filehead);
            ret.append(file->read(backcnt*(childlen + 8)));
            return ret;
        }
    }
    return 0;
}

void SReplay::close()
{
    for(int i=0;i<filecnt;i++)
    {
        fileArr[i].close();
    }
}
bool SReplay::isOneTimeSaved(QString dstfilename)
{
    QString src=filename.right(filename.size()-filename.lastIndexOf('/')-1);
    src=src.left(src.indexOf('.'));
    QString dst=dstfilename.right(dstfilename.size()-dstfilename.lastIndexOf('/')-1);
    dst=dst.left(dst.indexOf('.'));
    if(src==dst)
    {
        QStringList dstindex=dstfilename.split('.');
        filenameIndex[filecnt]=dstindex.at(1).toInt();

        return true;
    }
    else
    {
        return false;
    }
}

void SReplay::GetFileArrList()
{
    int tmp;
    int index;
    int indexArr[MAX_REPLAY_FILE];
    int tmpArr[MAX_REPLAY_FILE];
    for(int i=0;i<filecnt;i++)
    {
        indexArr[i]=filenameIndex[i];
    }
    for(int i=0;i<filecnt;i++)
    {
        for(int j=i;j<filecnt;j++)
        {
            if(indexArr[j]<indexArr[i])
            {
                tmp= indexArr[i];
                indexArr[i]=indexArr[j];
                indexArr[j]=tmp;
            }
        }
    }
    for(int i=0;i<filecnt;i++)
    {
        for(int j=0;j<filecnt;j++)
        {
            if(indexArr[i]==filenameIndex[j])
            {
                tmpArr[i]=j;
                break;
            }
        }
    }
    for(int i=0;i<filecnt;i++)
    {
        filenameIndex[i]=tmpArr[i];
        // qDebug()<<tmpArr[i];
    }

}
