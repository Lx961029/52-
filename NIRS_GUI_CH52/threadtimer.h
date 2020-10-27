#ifndef THREADTIMER_H
#define THREADTIMER_H

#include "QThread"
#include "QTimer"

class ThreadTimer:public QThread
{
    Q_OBJECT
public:
    ThreadTimer(unsigned int time);
    ~ThreadTimer(){

    }
    void stopTimer();
protected:
    void run();
private:

    void startTimer();
    bool isStop;
    unsigned int mTime;
signals:
    void timeOut();
};

#endif // THREADTIMER_H
