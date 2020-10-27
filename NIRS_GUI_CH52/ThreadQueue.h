#ifndef THREADQUEUE
#define THREADQUEUE
#include<cassert>
#include <mutex>
#include <thread>
#include <QDebug>
using namespace std;

// from the brain hardware group huang

template<typename T>
class ThreadQueue{
public:
    ThreadQueue(int maxsize = 100);
    ~ThreadQueue();
    bool isFull();
    bool isEmpty();
    char push(T elem);
    char pop(T& elem);
    char at(int count,T& elem);
    unsigned int size();
private:
    T* array;
    int front;
    int rear;
    std::mutex mtx;
    int capacity;
};


template <typename T>
ThreadQueue<T>::ThreadQueue(int maxsize):front(0),rear(0),capacity(maxsize+1)
{
   array = new T[maxsize+1];
   assert(array != NULL);   //错误即终止执行
}

template <typename T>
ThreadQueue<T>::~ThreadQueue(){
   delete(array);
}

template <typename T>
bool ThreadQueue<T>::isFull(){
    bool res;
    std::unique_lock<std::mutex> mutex(mtx);
    res = (rear+1)%capacity == front;
    mutex.unlock();
    return res; //往正数看
}

template <typename T>
bool ThreadQueue<T>::isEmpty(){

    bool res;
    std::unique_lock<std::mutex> mutex(mtx);
    res = rear == front;
    mutex.unlock();

    return res;
}

template <typename T>
char ThreadQueue<T>::push(T elem){
    if(isFull()){
        return -1;
    }else{
        std::unique_lock<std::mutex> mutex(mtx);
        array[rear] = elem;
        rear = (rear + 1)%capacity;
        mutex.unlock();
        return 1;
    }
}

template <typename T>
char ThreadQueue<T>::pop(T& elem){   // oldest data
     if(isEmpty())
       return -1;
     else {
        std::unique_lock<std::mutex> mutex(mtx);
        elem = array[front];
        front = (front + 1) % capacity;
        mutex.unlock();
        return 1;
     }
}

template <typename T>
char ThreadQueue<T>::at(int count,T& elem){ // count 0~9
     unsigned int loc;
     if(isEmpty())
       return -1;
     else {
        std::unique_lock<std::mutex> mutex(mtx);
        loc = (front + count) % capacity;
        elem = array[loc];
        mutex.unlock();
        return 1;
     }
}


template <typename T>
unsigned int ThreadQueue<T>::size(){ // count 0~9
    unsigned int res;
     std::unique_lock<std::mutex> mutex(mtx);
     res = ((rear - front + capacity)%capacity);
     mutex.unlock();
     return res;
}



#endif
