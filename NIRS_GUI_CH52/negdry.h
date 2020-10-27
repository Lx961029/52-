#ifndef NEGDRY_H
#define NEGDRY_H

#include <thread> // c++11
#include "memory.h"
//#include <fileapi.h>
#include "filter.h"
#include "QDebug"
#include "list"
#include "QTime"
#include "QCoreApplication"
#include "QList"
#include "qthread.h"
#include "qdoublebufferedqueue.h"
#include "fstream"

//#include "QFile"
//#include "QTextStream"

#ifndef MODEBLUETOOTH
    #include "QSerialPort"
    #define PORT_TYPE QSerialPort*
#else
#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>
#include <QListWidgetItem>
    #define PORT_TYPE QBluetoothSocket*

#endif

//using namespace std;
 // explicit 禁止隐式转换/ 成员 - c_asd   方法 xxxXxx
//线程结束后不要继续调用 .detach 并发执行 != join 截断
 // 函数return

#include "sigproc.h"

#define ADC_BYTE 3

typedef struct{
    int nch[2];
    int freq[2];
    int npkg[2]; //nirs :  // np[2]为脑电的数据量
}Dev;
//**************************
typedef struct{
    unsigned short samplingRate;
    unsigned int numSamples;
    unsigned char nChannels;
}EEG_Info;

typedef struct{
    //personal information
}NEG_Info;

typedef struct{
    unsigned short samplingRate;
    unsigned int numSamples;
    double locDistance;
    double dpf;
    unsigned char nChannels;
}NIRS_Info;

typedef struct{
    EEG_Info Info;
    double* data;
}EEG;

typedef struct{
    NIRS_Info Info;
    double* data;
}NIRS;


typedef struct{
    NEG_Info info;
    EEG eeg;
    NIRS nirs;
}NEG;

typedef struct{
    double *EEGMat;
    double *NIRSMat;
}NEGMat;

class Negdry
{
public:
    Negdry(){
        buffer1 = new QDoubleBufferedQueue<vector<double>>(10000);
        runReadThread = 1;
        isAlined = 0;
        isConfiged = 0;
        m_neg = this;
        isSaveData = false;
    }
    ~Negdry(){
        runReadThread = 0;
        delete m_rawRead;
    }
    void run(){
      if(isConfiged){
        m_rawRead = new thread(rawRead);
        m_rawRead->detach();
      }else{
          qDebug()<<"no config dev"<<endl;
          exit(0);
      }
    }
    void stopRead(){
        runReadThread = 0;
    }

    void negMatRelease(NEGMat* a){
        if(a)
        {
        }

    }

    void saveRawData(bool isSave){
        if(isSave){
            isSaveData = true;
            outfile.open("rawData.txt");
        }else{
            isSaveData = false;
            outfile.close();
        }

    }


    bool getNEGFrame(NEGMat* m_Mat){//注意析构
        NEGMat out;
        //qDebug()<<buffer.size()<<endl;
        if(buffer.size() < 5){
            return false;
        }else{
         // ********************* 注意容器用法****************
            out = buffer.back();
            *m_Mat = out;
            buffer.pop_back();
            negMatRelease(&out);
            // 回收！！！
        }
        return true;
    }
    bool getNIRSFrame(vector<double>** m_Mat, int *ret){//注意析构
        //qDebug()<<"????"<<endl;
        if(buffer1->canGet()){
            //qDebug()<<"!!!!"<<endl;
            *ret = buffer1->get(m_Mat);
            return true;
        }else{
            return false;
        }

    }
    static NEGMat * newNEGFrame(){
        NEGMat* NEGFrame = new NEGMat;
       // qDebug()<<numFrameNIRS<<endl;
        //double* EEGMat = new double[numFrameEEG]; // = 对象  //注意数组声明方法
        double* NIRSMat = new double[numFrameNIRS];
       // NEGFrame->EEGMat = EEGMat;
        NEGFrame->NIRSMat = NIRSMat;
        return NEGFrame;
    }
    void  setDeviceInfo(void* seriel,int *nch,int* freq,int* npkg){ //npkg为一帧数据
        isConfiged = 1;
        m_seriel = (PORT_TYPE)seriel;
        //memcopy(m_Dev.freq,freq,sizeof(int)*2); // (d,s,c)
        int i = 2;
        while(i--){
          m_Dev.freq[i] = *(freq+i);
          m_Dev.nch[i] = *(nch+i);
          m_Dev.npkg[i] = *(npkg+i);
        }

        numFrameNIRS = 8;// m_Dev.nch[0]*2; // 690+830 -> ch ->2  ; 4ch = 16 * 3 bit
        numFrameEEG = m_Dev.nch[1]*2;
    }
    static string bytestohexstring(char* bytes,int bytelength)
    {
      string str("");
      string str2("0123456789ABCDEF");
       for (int i=0;i<bytelength;i++) {
         int b;
         b = 0x0f&(bytes[i]>>4);
         char s1 = str2.at(b);
         str.append(1,str2.at(b));
         b = 0x0f & bytes[i];
         str.append(1,str2.at(b));
         char s2 = str2.at(b);
         str.append(1,' ');
       }
       return str;
    }
private:
    //   缓冲
     static std::list<NEGMat> buffer;
     static std::list<int> debug_Buffer;
     static QDoubleBufferedQueue<vector<double>>* buffer1;
   //  static QList<NEGMat*> buffer;
    //
    static int numFrameNIRS; // 690+830 -> ch ->2
    static int numFrameEEG;
    static Negdry* m_neg;   // get access to static function

    static ofstream outfile;

    static bool isSaveData;

    thread* m_rawRead;
    PORT_TYPE m_seriel;
    Dev m_Dev;
    unsigned char isAlined;
    unsigned char isConfiged;
    unsigned char runReadThread;

   static void rawRead(){
        //read to buffer;
       QByteArray rawData;
       // unsigned char pCollectData[20];
        unsigned long readcount;
        static const double refval=2.5/double(0x7fffff);//次处数为NAN  0X7fffff


        int npkg[2] = {m_neg->m_Dev.npkg[0],m_neg->m_Dev.npkg[1]};
        int nch[2] = {m_neg->m_Dev.nch[0],m_neg->m_Dev.nch[1]};// NIRS  / EEG
        int nfr[2] = {1,2};//each channel
        PORT_TYPE m_seriel = m_neg->m_seriel;
        double baseline[m_neg->m_Dev.nch[0]*2];
        unsigned char baselineConfiged[m_neg->m_Dev.nch[0] * 2] = {0}; //通道数为
        qDebug()<<m_neg->m_Dev.nch[0]<<endl;
/*
        double *test = new double[2*nch[0]];
        double **test1;
        *test = 9;
        *(test + 1) = 3;
        buffer1 = new QDoubleBufferedQueue<double*>(10000);
        buffer1->put(test);
        buffer1->get(&test1);
        qDebug()<<*(*test1 + 1)<<endl;
        while(1);
*/
       // int packSum = (npkg[0]+npkg[1])*2 + 2;  // n[0] = 3 ,n[1] = 6 (Byte)
        int packSum  = nch[0]*ADC_BYTE*4 + 3;
        //qDebug()<<packSum<<endl;
        int numSec = 9; // npkg[0]/2 + npkg[1]/2  (double)
        unsigned char Alined = 0;
        //for(int i )
       // Filter_IIR *NIRS_IIR = new Filter_IIR<double>();
        Filter_IIR<double>* NIRS_IIR[nch[0]];
        Filter_IIR<double>* EEG_IIR[nch[1]];
       for(int i =0 ;i < nch[0];i++)
        NIRS_IIR[i] = new Filter_IIR<double>();//2
       for(int i =0 ;i < nch[1];i++)
        EEG_IIR[i] = new Filter_IIR<double>();//

       //vector<double>**m_Mat;

       //buffer1->get(m_Mat);

       // Filter_IIR *EEG_IIR = new Filter_IIR<double>();
        //Filter_IIR *EEG_IIR = new Filter_IIR<double>();
        m_seriel->readAll();
        rawData.clear();
       // qDebug()<<nch[0]<<endl;
         while(m_neg->runReadThread == 1){

             if(Alined == 0){
                 // qDebug()<<"header check" <<endl;
                  // 获取
                      rawData = m_seriel->read(1);
                  //    qDebug()<<(unsigned char)(rawData.at(0))<<endl;
                      if((unsigned char)(rawData.at(0)) == 0xAA){
                          rawData = m_seriel->read(1);
                        //  qDebug()<<rawData.at(0)<<endl;
                          if((unsigned char)(rawData.at(0)) == 0x55){
                              rawData = m_seriel->read(packSum-2);
                               // qDebug()<<refval<<endl;
                              Alined = 1;
                          }
                      }
                }
             else if(m_seriel->bytesAvailable() > packSum){
                  //m_seriel->readBufferSize();
                 //fread(m_neg->DevCom, pCollectData, 1, &readcount, NULL);

                 rawData = m_seriel->read(packSum);

                 //NEGMat* NEGFrame = newNEGFrame();
                // double* EEGMat = NEGFrame->EEGMat; // = 对象
                //double* NIRSMat = NEGFrame->NIRSMat;


                 //double *NIRSMat = new double[2*nch[0]];
                vector<double> NIRSMat;

                if(isSaveData){
                    outfile<<bytestohexstring(rawData.data(),rawData.size());
                }
         //   read mat
                if((unsigned char)(rawData.at(0)) == 0xAA) {// 690 . 830

                    for(int i = 0;i < 2*nch[0] - 1;){

                       // *(NIRSMat + i) = pow(pow(((double)((((unsigned int)(0x80^rawData.at(3 + 6*i)))<<16)&0x00FF0000) +
                        NIRSMat.push_back(   pow(pow(((double)((((unsigned int)(0x80^rawData.at(3 + 6*i)))<<16)&0x00FF0000) +
                                         (double)((((unsigned int)(rawData.at(4 + 6*i)))<<8)&0x0000FF00) +
                                         (double)((((unsigned int)(rawData.at(5 + 6*i))))&0x000000FF)),2) +
                                             pow(((double)((((unsigned int)(0x80^rawData.at(6 + 6*i)))<<16)&0x00FF0000) +
                                         (double)((((unsigned int)(rawData.at(7 + 6*i)))<<8)&0x0000FF00) +
                                         (double)((((unsigned int)(rawData.at(8 + 6*i))))&0x000000FF)),2)
                                             ,0.5)*refval);
                        //qDebug()<<*(NIRSMat+i)<<endl;
                        i++;

                       // *(NIRSMat + i) = ((unsigned long)(0x80^rawData.at(3 + 6*i))<<16);
                        // qDebug()<<*(NIRSMat+i)<<endl;
                       // *(NIRSMat + i) = pow(pow(((double)((((unsigned int)(0x80^rawData.at(3 + 6*i)))<<16)&0x00FF0000) +
                        NIRSMat.push_back( pow(pow(((double)((((unsigned int)(0x80^rawData.at(3 + 6*i)))<<16)&0x00FF0000) +
                                         (double)((((unsigned int)(rawData.at(4 + 6*i)))<<8)&0x0000FF00) +
                                         (double)((((unsigned int)(rawData.at(5 + 6*i))))&0x000000FF)),2) +
                                             pow(((double)((((unsigned int)(0x80^rawData.at(6 + 6*i)))<<16)&0x00FF0000) +
                                         (double)((((unsigned int)(rawData.at(7 + 6*i)))<<8)&0x0000FF00) +
                                         (double)((((unsigned int)(rawData.at(8 + 6*i))))&0x000000FF)),2)
                                             ,0.5)*refval);
                        i++;

                        if(baselineConfiged[(i-2)/2] == 0){
                            baseline[i - 2] = NIRSMat.at(i -2) + 1e-5f;
                            baseline[i - 1] = NIRSMat.at(i -1) + 1e-5f;
                            baselineConfiged[(i-2)/2] = 1;
                         }

                       double res690,res830;
                        res690 = NIRSMat.at(i-2);
                        res830 = NIRSMat.at(i-1);
                        //singleCvt(NIRSMat + i - 1,NIRSMat + i,baseline + i -1);
                       singleCvt(&res690,&res830,baseline[i - 2],baseline[i - 1]);
                       NIRSMat.at(i-2) = res690;
                       NIRSMat.at(i-1) = res830;
                    }
                }else{
                    qDebug()<<"error"<<endl;
                    Alined =0;
                    continue;
                }



                /*else{
                    *(NIRSMat+1) = ((unsigned int)rawData.at(0+2) + ((unsigned int)rawData.at(1+2))<<8)*refval;
                    *NIRSMat = ((unsigned int)rawData.at(6+2) + ((unsigned int)rawData.at(7+2))<<8)*refval;
                }*/


 //                 //filter :: 至少滤除50hz
//                 NIRS_IIR[0]->filterData(*NIRSMat,NIRSMat);
//                 NIRS_IIR[1]->filterData(*(NIRSMat+1),NIRSMat+1);



//               for(int i = 0;i<nch[1];i++)
//                for(int j = 0;j<nfr[1];j++){
//                 *(EEGMat+ i + j*nch[1]) = ((unsigned int)rawData.at(numSec*j + ADC_BYTE*i + 5) + ((unsigned int)rawData.at(numSec*j+ ADC_BYTE*i + 5 + 1))<<8 + ((unsigned int)rawData.at(numSec*j+ ADC_BYTE*i + 5 + 1))<<16)*refval;
//                 // *********************filter ::*********************
//                    //EEG_IIR[i] ->filterData(*(EEGMat+ i + j),EEGMat+ i + j);
//                }
                 // 缓冲
/*
                if(buffer.size() <= 3000){
                   buffer.push_front(*NEGFrame);

                //    debug_Buffer.push_back(123);

                  //qDebug()<<*NEGFrame<<endl;
                }
                else{
                    qDebug()<<"error in buffer"<<endl;
                }

*/
             buffer1->put(NIRSMat);
             NIRSMat.clear();
             rawData.clear();
           }
           //QThread::usleep(300)
          std::this_thread::sleep_for(chrono::microseconds(5));
         }//while
         m_neg->isAlined = 0;
         for(int i =0 ;i < nch[0];i++)
          delete NIRS_IIR[i];//2
         for(int i =0 ;i < nch[1];i++)
          delete EEG_IIR[i];//
       return;
    }
};

#endif // NEGDRY_H
