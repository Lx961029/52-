#ifndef QDOUBLEBUFFEREDQUEUE_H
#define QDOUBLEBUFFEREDQUEUE_H

//#include <QMutex>

#include <mutex>
#include <thread>
#include <QDebug>
template <class T>
class QDoubleBufferedQueue
{
public:
    //
    // Constructor - construct a queue with the given buffer size
    //
    QDoubleBufferedQueue(int bufferSize = 1000) :
        bufferLen(0), bufferSize(bufferSize)
    {
        buffer0 = buffer = new T[bufferSize];
        buffer1 = new T[bufferSize];
    }

    //
    // Destructor
    //
    ~QDoubleBufferedQueue()
    {
         delete[] buffer0;
         delete[] buffer1;
    }

    //
    // Add an item to the queue. Returns true if successful, false if the buffer is full.
    //
    bool put(const T& datum)
    {
        //mutex.lock();
        std::unique_lock<std::mutex> mutex(mtx);
        bool canWrite = bufferLen < bufferSize;
        if (canWrite) buffer[bufferLen++] = datum;
        mutex.unlock();
        return canWrite;
    }

    bool canGet(){

       // mutex.lock();
        std::unique_lock<std::mutex> mutex(mtx);
        //qDebug()<<"error~~"<<endl;
        if(bufferLen>=100){
           mutex.unlock();
           return true;
        }
        else{
           mutex.unlock();
           return false;
        }
    }

    //
    // Get all the items in the queue. The T** argument should be the address of a variable to
    // receive the pointer to the item array. The return value is the size of the array.
    //
    int get(T** data)
    {
        //mutex.lock();
        std::unique_lock<std::mutex> mutex(mtx);
        *data = buffer;
        int ret = bufferLen;
        buffer = (buffer == buffer0) ? buffer1 : buffer0;
        bufferLen = 0;
        mutex.unlock();
        return ret;
    }

private:

    // Disable copying and assignment
    QDoubleBufferedQueue & operator=(const QDoubleBufferedQueue&);
    QDoubleBufferedQueue(const QDoubleBufferedQueue&);

    T* buffer0;
    T* buffer1;
    T* buffer;
    int bufferLen;
    int bufferSize;
    std::mutex mtx;
};


#endif
