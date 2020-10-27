#include "threadtimer.h"
#include "QDebug"
ThreadTimer::ThreadTimer(unsigned int time)
{
    isStop = false;
    mTime = time;
}

void ThreadTimer::run(){

    while(!isStop){
        usleep(mTime);
        emit timeOut();
    }
}

void ThreadTimer::stopTimer(){
    isStop = 1;
}

void ThreadTimer::startTimer(){
    isStop = 0;
}


