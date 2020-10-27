#ifndef RANDOMWALK_H
#define RANDOMWALK_H

#include <QThread>
#include "QWaitCondition.h"
#include "negdry_qt.h"
#include "QVector"
#include "qmutex.h"
#include "QLayout"
#include "realtimemultithread.h"
#include "QMessageBox"
#include "QFile"
#include "QString"
#include "QTextStream"
#include "QCoreApplication"
#include "QtConcurrent"
#ifndef MODEBLUETOOTH
#include "QSerialPort"
#include "Negdry_qt.h"
#endif

#define CHANNEL_CNT 13

class RandomWalk : public QGridLayout
{
Q_OBJECT
public:

    //typedef void DataHandler(void *param, double elapsedTime, double series0, double series1);
    //typedef void DataHandler(void *param, double elapsedTime, double series0, double series1,double series2, double series3);
    typedef void DataHandler(void* param,double NIRS690,double NIRS830);
    RandomWalk(QWidget *parent);
    virtual ~RandomWalk();
   // void saveToFile();
    // stop the thread
    void stop();
    void setPage(int pn){
        pageNum = pn;
    }
    void start_trans(){
        if(negdry != NULL){
           negdry->start_trans();
           negdry->start(QThread::InheritPriority);
           //negdry->setPriority(QThread::HighestPriority);
        }
    }
    void StopGenData();
    bool getSavePtr( float *RawDataHbR,float *RawDataHbO,unsigned long neededDataCnt){
       // AllDataCnt = HboSaveCnt;
        if(neededDataCnt >= HboSaveCnt-3){
             return false;
        }else{
            RawDataHbR = (float*)(new float(neededDataCnt));
            RawDataHbO = (float*)(new float(neededDataCnt));
            memcpy(RawDataHbR,HbrSave+HbrSaveCnt-3-neededDataCnt,neededDataCnt*sizeof(float));
            memcpy(RawDataHbO,HboSave+HboSaveCnt-3-neededDataCnt,neededDataCnt*sizeof(float));
        }
        return true;
    }
    void saveDataToFile(bool isSave);
    void resetDisp(){
//      if(!stopThread){
        for(unsigned int i=0;i < CHANNEL_CNT;i++){
            (*(realTime+i))->resetDisp();
        }
//      }
//      else{
//         QMessageBox::information(NULL, "", "请先打开串口", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//      }

    }
    void setDisconnect(){   //连接数据接受信号与数据显示槽

    }
    void setConnect(){

    }
public slots:
    void GenerateData_qt(double* data);
//private slots:
 //   void mark_data();
protected :
     QMutex qMutex;
    //void run();


signals:
    void againGenThread();
    void mark_signal();

private :

    // Disable copying and assignment
    RandomWalk & operator=(const RandomWalk&);
    RandomWalk(const RandomWalk&);
    unsigned char IsStartofData;
    // Flag to stop the flag
    bool stopThread;
    Negdry_qt* negdry;
    RealTimeMultiThread **realTime;
    QThread ** m_Thread;

    QTimer timer;
    QThread *qThread;                  // 声明一个QThread线程管理类用来管理testThread
    QThread* m_thread;


    QString FILE_PATH;
    QString runPath;
    QTextStream *out;
    QFile *csvFile;
    int pageNum;
    float *HboSave;
    float *HbrSave;
    unsigned long HboSaveCnt;
    unsigned long HbrSaveCnt;
    unsigned long HboCapacity;
    unsigned long HbrCapacity;

    float *EEG1Save;
    float *EEG2Save;
    unsigned long EEG1SaveCnt;
    unsigned long EEG2SaveCnt;
    unsigned long EEG1Capacity;
    unsigned long EEG2Capacity;

    ThreadTimer **myTimer;

    DataHandler **handler;//数据处理器
    void *param;
    bool isSaveData;
    unsigned char nfr[2] = {CHANNEL_CNT,2};  // {NIRS , EEG}
    unsigned char nch[2] = {CHANNEL_CNT,2} , nchNum = CHANNEL_CNT;

    //ParaSet *paraSet;
};

#endif // RANDOMWALK_H
