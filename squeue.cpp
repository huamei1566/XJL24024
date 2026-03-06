#include "squeue.h"
#include "qstring.h"
SQueue::SQueue()
{
    valueArr=new unsigned char[MAX_QUEUE_LEN];
    memset(valueArr,0,MAX_QUEUE_LEN);
    head=0;
    tail=0;

}

SQueue::~SQueue()
{
    delete []valueArr;
}

bool SQueue::IsEmpty()
{
    if(tail==head)
        return true;
    else
        return false;
}

bool SQueue::IsFull(int len)
{
    if((head+len)%MAX_QUEUE_LEN==tail)
        return true;
    else
        return false;
}

void SQueue::push(unsigned char value)
{
    mLock.lock();
    valueArr[head]=value;
    head=(head+1)%MAX_QUEUE_LEN;
    mLock.unlock();
}

void SQueue::push(unsigned char *value,int len)
{
    mLock.lock();
    for(int i=0;i<len;i++)
    {
        valueArr[head]=value[i];
        head=(head+1)%MAX_QUEUE_LEN;
    }
    mLock.unlock();
}

void SQueue::pop()
{
    mLock.lock();
    tail=(tail+1)%MAX_QUEUE_LEN;
    mLock.unlock();
}

void SQueue::pop(int len)
{
    mLock.lock();
    tail=(tail+len)%MAX_QUEUE_LEN;
    mLock.unlock();
}

void SQueue::popall()
{
    mLock.lock();
    tail=head;
    mLock.unlock();
}

unsigned char SQueue::getobject(int index)
{
    return valueArr[(tail+index)%MAX_QUEUE_LEN];
}

void SQueue::getobject(unsigned char* value,int len)
{
    mLock.lock();
    for(int i=0;i<len;i++)
    {
        value[i]=valueArr[(tail+i)%MAX_QUEUE_LEN];
    }
    mLock.unlock();
}

int SQueue::getsize()
{
    int ret;
    mLock.lock();
    if(head>=tail)
    {
        ret=head-tail;
    }
    else
    {
        ret=head+MAX_QUEUE_LEN-tail;

    }
    mLock.unlock();
    return ret;
}
void SQueue::ResetData()
{
    mLock.lock();
    memset(valueArr,0,MAX_QUEUE_LEN);
    head=0;
    tail=0;
    mLock.unlock();
}
