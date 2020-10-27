#include "negdry_qt.h"

Negdry_qt::Negdry_qt()
{
    runReadThread = 1;
    isAlined = 0;
    isConfiged = 0;
//    m_neg = this;
    isSaveData = false;
    baselineConfiged.resize(104);
    for(int i = 0;i < 104;i ++){
        baselineConfiged[i] =false;
    }
    baseline.resize(104);
//    connect(this,SIGNAL(send_computed_data(QVector<double>& dataConv)),this,SLOT(rec_computed_data(QVector<double>& dataConv)));
    QObject::connect(this,SIGNAL(SaveDate(double *)),this,SLOT(SaveData_File(double *)),Qt::QueuedConnection);
}

void Negdry_qt::setDeviceInfo(void* seriel,int *nch,int* freq,int* npkg){ //npkg为一帧数据
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

void Negdry_qt::stopRead(){   
    runReadThread = 0;
    char cmd[6] = {(char)0x55,(char)0XAA,(char)0x00,(char)0x01,(char)0x0D,(char)0x0A};
    m_seriel->write(cmd,6);
    m_seriel->clear();
    m_seriel->close();
}

void Negdry_qt::saveRawData(bool isSave){
//    if(isSave){
//        isSaveData = true;
//        outfile.open("rawData.txt");
//    }else{
//        isSaveData = false;
//        outfile.close();
//    }
    QString file_path;
    QString Devices;
        static int saveCnt = 1;
//        if(csvFile != NULL && csvFile.isOpen()){
//            //negdry->save_to_file(isSaveData,nullptr);
//            csvFile.close();
//        }
        //FILE_PATH = runPath + "\\NIRS4CH_N"+QString::number(saveCnt)+".csv";
        file_path="NIRS4CH_N"+QString::number(saveCnt)+".csv";
        //csvFile = new QFile(file_path);
        csvFile.setFileName(file_path);
        if(csvFile.isOpen()) {csvFile.close();isSaveData = isSave; return;qDebug()<<"return"<<endl;}
        if(!csvFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            qDebug()<<"open file error!"<<endl;
        }
        outfile = new QTextStream(&csvFile);
        saveCnt++;
        isSaveData = isSave;
        //negdry->save_to_file(isSaveData,out);
}

void Negdry_qt::save_to_file(bool isSave, QTextStream *out)
{

//    if(isSave){
//        outfile = out;
//    }
    isSaveData = isSave;
}

void Negdry_qt::rec_computed_data(QByteArray rawData)
{
    //此函数处理 + 分发
    int count = 208;
    double* datasent = new double[104];
    const double refval=2.5/double(0x7fffff);
    long  packSum= rawData.size();
        for(int k = 3,j = 0;k < packSum; k += 6,j ++){
            unsigned int temp = 0;
            temp = (unsigned char)rawData[k];
            temp ^= 0x80;
            temp <<= 8;
            temp |= (unsigned char)rawData[k + 1];
            temp <<= 8;
            temp |= (unsigned char)rawData[k + 2];

            unsigned int temp1 = 0;
            temp1 = (unsigned char)rawData[k + 3];
            temp1 ^= 0x80;
            temp1 <<= 8;
            temp1 |= (unsigned char)rawData[k + 4];
            temp1 <<= 8;
            temp1 |= (unsigned char)rawData[k + 5];

            datasent[j] = pow(((double)temp * refval)  * ((double)temp * refval) + ((double)temp1 * refval) * ((double)temp1 * refval), 0.5);
//            datasent[j] = ((double)temp * refval);
            if(!baselineConfiged[j]){
                baseline[j] = datasent[j] + 1e-5f;
                baselineConfiged[j] = true;
             }
//            datasent[j] -= baseline[j];
        }
        //改变通道
        for(int i = 0;i < 103;i ++){
            if(i % 2 == 0){
                singleCvt(datasent + i,datasent + i + 1,baseline[i],baseline[i + 1]);
            }
            if(i % 4 == 0){
                double tmp = datasent[i];
                datasent[i] = datasent[i + 1];
                datasent[i + 1] = tmp;
            }
        }

// ==>  randomwalk.cpp GenerateData_qt
    //emit getData(datasent);
}


//修改之后的保存文件函数
void Negdry_qt::date_computed(QByteArray dataConv){
    //此函数处理 + 分发
    int count = 208;
    double* datasent = new double[104];
    double* datasent1 = new double[104];
    const double refval=2.5/double(0x7fffff);
    long  packSum= dataConv.size();
        for(int k = 3,j = 0;k < packSum; k += 6,j ++){
            unsigned int temp = 0;
            temp = (unsigned char)dataConv[k];
            temp ^= 0x80;
            temp <<= 8;
            temp |= (unsigned char)dataConv[k + 1];
            temp <<= 8;
            temp |= (unsigned char)dataConv[k + 2];

            unsigned int temp1 = 0;
            temp1 = (unsigned char)dataConv[k + 3];
            temp1 ^= 0x80;
            temp1 <<= 8;
            temp1 |= (unsigned char)dataConv[k + 4];
            temp1 <<= 8;
            temp1 |= (unsigned char)dataConv[k + 5];
            datasent[j] = pow(((double)temp * refval)  * ((double)temp * refval) + ((double)temp1 * refval) * ((double)temp1 * refval), 0.5);


            if(!baselineConfiged[j]){
                baseline[j] = datasent[j] + 1e-5f;
                baselineConfiged[j] = true;
             }
        }
        //改变通道
        for(int i = 0;i < 103;i ++){
            if(i % 2 == 0){
                singleCvt(datasent + i,datasent + i + 1,baseline[i],baseline[i + 1]);
            }
            if(i % 4 == 0){
                double tmp = datasent[i];
                datasent[i] = datasent[i + 1];
                datasent[i + 1] = tmp;
            }
            datasent1[i]=datasent[i];
        }
        //保存文件，测试完打开
        if(isSaveData){
            for(int i = 0;i < 104; i+=2){
                    *outfile<<QString::number(datasent[i],'f',5)<<","<<QString::number(datasent[i + 1],'f',5)<<",";
                    *outfile<<QString::number(datasent[i + 1],'f',5)<<",";
             }
             *outfile<<"\n";
            //emit SaveDate(datasent);
        }
        qDebug() << QString("Negdry_qt thread id:") << QThread::currentThreadId();
       emit getData(datasent1);
}

void Negdry_qt::start_trans()
{
    m_seriel->clear();
    char cmd[6] = {(char)0x55,(char)0XAA,(char)0x00,(char)0x00,(char)0x0D,(char)0x0A};
    m_seriel->write(cmd,6);
}

void Negdry_qt::run(){
    unsigned long readcount;
    static const double refval=2.5/double(0x7fffff);//次处数为NAN  0X7fffff
    QByteArray rawData;
    int npkg[2] = {m_Dev.npkg[0],m_Dev.npkg[1]};
    int nch[2] = {m_Dev.nch[0],m_Dev.nch[1]};// NIRS  / EEG
    int nfr[2] = {1,2};//each channel
//    PORT_TYPE m_seriel = m_seriel;
    double baseline[m_Dev.nch[0]*2];
    int packSum  = 627;//nch[0]*ADC_BYTE*4 + 3;
    QVector<QByteArray> dataConv(10);
    qDebug() << "thread" << endl;
    volatile int data_pos = 0;
   // m_seriel->readAll();
    while(runReadThread){ //runReadThread ==
      if(m_seriel->bytesAvailable() > packSum)
        if(isAlined == 0){
                 rawData = m_seriel->read(1);
                 if((unsigned char)(rawData.at(0)) == 0xAA){
                     rawData = m_seriel->read(packSum-1);
                     if((unsigned char)(rawData.at(0)) == 0x55 && (unsigned char)(rawData.at(1)) == 0){
                         isAlined = 1;
                         qDebug() << "aliened" << endl;
                     }
                 }
           }
        else if(m_seriel->bytesAvailable() > packSum){
               dataConv[data_pos] = m_seriel->read(packSum);
               unsigned char check = dataConv[data_pos][0];
//               char date ;
//               char *date1;
               if(check == 0xAA) {// 690 . 830

//                   if(isSaveData){
//                       for(int i=3;i<dataConv[data_pos].size();i++)
//                          {
//                           *outfile <<(uint8_t)dataConv[data_pos][i];      //把数组中的数据写到数据流，即写入文件中

//                          }
                       //新写的保存文件函数
                       //date_computed(dataConv[data_pos]);
                       //*outfile <<endl;
 //                  }

                    //传给画图模块
                   //QtConcurrent::run(this,&Negdry_qt::date_computed,m_seriel->read(packSum));
                   date_computed(dataConv[data_pos]);
                   data_pos ++;
                   if(data_pos >= 10) data_pos = 0;

               }else{
                  qDebug()<<"error:" + check <<endl;
                  isAlined =0;
               }
           }
      }
    }

void Negdry_qt::SaveData_File(double *data){
    for(int i = 0;i < 104; i+=2){
            *outfile<<QString::number(data[i],'f',5)<<","<<QString::number(data[i + 1],'f',5)<<",";
            *outfile<<QString::number(data[i + 1],'f',5)<<",";
     }
     *outfile<<"\n";
}


