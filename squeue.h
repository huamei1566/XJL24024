#ifndef SQUEUE_H
#define SQUEUE_H


#define MAX_QUEUE_LEN 5242880 //队列容量 5 * 1024 *1024

#include <QMutex>


class SQueue
{
public:
    SQueue();
    ~SQueue();
    void push(unsigned char value);
    void push(unsigned char *value,int len);
    void pop();
    void pop(int len);
    void popall();
    unsigned char getobject(int index=0);
    void getobject(unsigned char* value,int len);


    int getsize();
    void ResetData();
private:
    QMutex mLock;

    int queueLen;
    unsigned char *valueArr;//队列缓存
    int head;
    int tail;
    bool IsEmpty();
    bool IsFull(int len=1);
};

#endif // SQUEUE_H
