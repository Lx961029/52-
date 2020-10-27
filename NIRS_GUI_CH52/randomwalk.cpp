#include "randomwalk.h"
#include "QDebug"
#include "paraset.h"
#include "QTime"
#include "QCoreApplication"
#include "QSerialPort"
#include "thread"

#define dataSaveBlock 1000


//***************************sleep()影响程序运行******************************

FILE* fp[CHANNEL_CNT];

// focus on the handler
RandomWalk::RandomWalk(QWidget *parent)   //handler 为输入的参数
{

    stopThread = true;
    //char str[100];
    IsStartofData = 0;
    isSaveData = 0;
    void* m_series;
    pageNum = 0;
    m_series =  ParaSet::getCom();
    int nch[2] = {6,2};
    int freq[2] = {125,250};
    int npkg[2] = {3,6};
    //realTime = NULL;
    negdry = new Negdry_qt();
    negdry->setDeviceInfo(m_series,nch,freq,npkg);
//   qThread = new QThread();
//    negdry->moveToThread(qThread);

    QObject::connect(negdry,SIGNAL(getData(double *)),this,SLOT(GenerateData_qt(double *)),Qt::QueuedConnection);
    runPath = QCoreApplication::applicationDirPath();

    this->setColumnStretch(0,1);
    this->setColumnStretch(1,1);
    this->setColumnStretch(2,1);
    this->setColumnStretch(3,1);

    this->setRowStretch(0,1);
    this->setRowStretch(1,1);
    this->setRowStretch(2,1);
    this->setRowStretch(3,1);


  //创建13个画图类

    realTime = (RealTimeMultiThread**)malloc(CHANNEL_CNT*sizeof(RealTimeMultiThread*));//size要确认
    handler = (DataHandler **)malloc(CHANNEL_CNT*sizeof(DataHandler*));

//    m_Thread = (QThread **)malloc(4*sizeof(QThread));

    for(unsigned int i = 0;i < CHANNEL_CNT;i ++){
        *(realTime + i) = new RealTimeMultiThread(parent);
        this->addWidget(*(realTime + i),i/4,i%4);   //十进制转2进制 ==> 2行
        *(handler + i) = (*(realTime + i))->getHander();
        QThread::msleep(13);
        (*(realTime + i))->startdraw();

    }
    //*****************************************************
    EEG1Save = (float*)malloc(sizeof(float)*dataSaveBlock);
    EEG2Save = (float*)malloc(sizeof(float)*dataSaveBlock);

    HboSave = (float*)malloc(sizeof(float)*dataSaveBlock);
    HbrSave = (float*)malloc(sizeof(float)*dataSaveBlock);


    EEG1Capacity = dataSaveBlock;
    EEG2Capacity = dataSaveBlock;
    HboCapacity = dataSaveBlock;
    HbrCapacity = dataSaveBlock;

    EEG1SaveCnt = 0;
    EEG2SaveCnt = 0;
    HboSaveCnt = 0;
    HbrSaveCnt = 0;

    //negdry->start();
    //negdry->start_trans();
}


RandomWalk::~RandomWalk()
{
//    float* negSave[4] = {HboSave,HbrSave,EEG1Save,EEG2Save};
    stop();
//    myTimer->stopTimer();
//    delete myTimer;
    delete negdry;
    for(unsigned int i = 0;i < CHANNEL_CNT;i++){
      delete  *(realTime + i) ;

    }
    if(csvFile->isOpen()){
        csvFile->close();
    }
    delete csvFile;

//    for(int i=0;i< 4;i++){
//         delete negSave[i];
//         negSave[i] = nullptr;
//    }
//    for (int i = 0; i < CHANNEL_CNT; i++)
//    {
//        delete fp[i];
//        fp[i] = nullptr;
//    }
}


void RandomWalk::stop()
{
    stopThread = true;
    //mThread->wait();
    //wait();
    stopThread = false;
}

void RandomWalk::StopGenData()
{
    if(negdry != NULL)negdry->stopRead();
}

void RandomWalk::saveDataToFile(bool isSave){//    0/1

//    QString Devices;
//    static int saveCnt = 1;
//    if(csvFile != nullptr && csvFile->isOpen()){
//        negdry->save_to_file(isSaveData,nullptr);
//        csvFile->close();
//    }
//    FILE_PATH = runPath + "\\NIRS4CH_N"+QString::number(saveCnt)+".csv";
//    csvFile = new QFile(FILE_PATH);
//    if(csvFile->isOpen()) {csvFile->close();isSaveData = isSave; return;qDebug()<<"return"<<endl;}
//    if(!csvFile->open(QIODevice::WriteOnly | QIODevice::Text)){
//        qDebug()<<"open file error!"<<endl;
//    }
//    out = new QTextStream(csvFile);
//    saveCnt++;
//    isSaveData = isSave;

//    negdry->save_to_file(isSaveData,out);


//    if(isSave){
//        negdry->start();
//    }else{
//        negdry->stopRead();
//    }
//******************save raw data to file********************;
    negdry->saveRawData(isSave);
}

void RandomWalk::GenerateData_qt(double *data)   // 接受/处理/保存 数据
{
    int tmp;
    int offset = pageNum * 26;
    int limit = offset + 26;
        for(int i = 0;i < 104; i+=2){
            if(i >= offset && i < limit){
                tmp = i - offset;
                //传输数据
                QtConcurrent::run(*(handler+tmp/2),*(realTime + tmp/2),data[i],data[i + 1]);
                (*(handler+tmp/2))(*(realTime + tmp/2),data[i],data[i + 1]);
             }
            //文件保存放在negdry_qt.cpp里了   LI
//             if(isSaveData){
//                *out<<QString::number(data[i],'f',5)<<","<<QString::number(data[i + 1],'f',5)<<",";
//                *out<<QString::number(data[i + 1],'f',5)<<",";
//             }
        }
//        if(isSaveData){
//           *out<<"\n";
//        }
   delete data;
}
