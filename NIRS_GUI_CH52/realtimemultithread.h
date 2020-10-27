#ifndef REALTIMEMULTITHREAD_H
#define REALTIMEMULTITHREAD_H


#include "qdoublebufferedqueue.h"
#include <math.h>
#include <vector>
#include <sstream>
#include <QDesktopWidget>

#include <qmutex.h>
#include "qdebug.h"

#include <QTimer>
#include "QDialog"
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include <QChartView>
#include <QRubberBand>
#include "QCategoryAxis"
#include "QThread"
#include "threadtimer.h"
#include "ThreadQueue.h"
#include "QtConcurrent"
QT_CHARTS_USE_NAMESPACE
#define DEVICENUM 1
#define DispCh 3
#define DATATYPE double
static const int freq[2] = {125,250};
typedef void DataHandler(void* param,double NIRS690,double NIRS830);
#define RANGE  1000
class RealTimeMultiThread :public QChartView{
    Q_OBJECT
public:
    RealTimeMultiThread(QWidget *parent = 0);
    ~RealTimeMultiThread();
    void StartGenData();
    void StopGenData();
    void displayModeChange(){
          if(ampMode == 0){
              ampMode = 1;
          }else{
              ampMode = 0;
          }
    }

    void setDisplayChannel(unsigned char i){
        displayChannel = i;
    }

    DataHandler*  getHander(){
        return (DataHandler *)(this->OnData);
    }
    void resetDisp(){
        chart->axisX()->setRange(0,RANGE);
//        chart->axisY()->setRange(-5+3.38328, 4.6+3.38368);
         chart->axisY()->setRange(-1, 1);
    }
/*
    bool getNIRSData(unsigned char channelMode,    \
                     float *RawDataHbR,float *RawDataHbO, \
                     unsigned int time_s,                  \
                     unsigned long* pointCnt)
    {
         *pointCnt = time_s*freq[0];
         if(dataSource->getSavePtr(RawDataHbR,RawDataHbO,*pointCnt)) return true;
         else return false;
         //RawDataHbR
    }
*/
    void startdraw();
private:
    //static RealTimeMultiThread *self;
    unsigned char ampMode;
    unsigned char displayChannel;
   //unsigned char moudle_one;
    static void OnData(void* param,double NIRS690,double NIRS830);
    QTimer *debug_Timer;
    void  initChart();
    ThreadTimer *myTimer;
    QTimer *timer;


    QMutex qMutex;

    QTimer *m_ChartUpdateTimer;
  //  static void OnData(void *self, double elapsedTime,double series0, double series1, double series2, double series3);
    QChart *chart;

    QLineSeries *series[DispCh];
    quint16 count;
    bool isStopping;
    QVector<QPointF> waveDisp[DispCh];  // tow_channel EEG
    int waveCnt;
    //Filter_IIR<double> *filterIIR[2*DEVICENUM];  // length = 20
    float baseline;
    //unsigned int pointCnt[4*DEVICENUM];
    double amplify;

    ThreadQueue<double> *mTQ690,*mTQ830;
    QThread* thread;
    void rec_computed_data();
    volatile int jump;
    volatile int jcnt;
    // QDoubleBufferedQueue<float> buffer;
    //***********display***********
    //void wheelEvent(QWheelEvent *event);
 //   QDoubleBufferedQueue<DataPacket> buffer;
public slots:
    void onChartUpdateTimer();
    void Debug_OnData();
};
#endif // REALTIMEMULTITHREAD_H
