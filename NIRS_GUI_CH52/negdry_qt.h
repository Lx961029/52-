#ifndef NEGDRY_QT_H
#define NEGDRY_QT_H
#include "memory.h"
#include "QThread"
#include "QTimer"
#include "sigproc.h"
#include "QDebug"
#include "QTime"
#include "QCoreApplication"
#include "QList"
#include "QVector"
#include "fstream"
#include "QtConcurrent"
#include "filter.h"
#include "qDebug"
#include "sigproc.h"
#include "QTextStream"
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


class Negdry_qt : public QThread
{
    Q_OBJECT
public:
    Negdry_qt();
    ~Negdry_qt(){
       runReadThread = 0;
       stopRead();
    }
    QFile csvFile;
    void stopRead();
    void setDeviceInfo(void* seriel,int *nch,int* freq,int* npkg);
    void saveRawData(bool isSave);

    void save_to_file(bool isSave,QTextStream* out);

    void start_trans();
    QVector<bool> baselineConfiged;
    QVector<double> baseline;
//public slots:
    void rec_computed_data(QByteArray dataConv);
    void date_computed(QByteArray dataConv);
public slots:
    void SaveData_File(double *data);

signals:
    void getData(double *);
    void SaveDate(double *);
//    void rec_computed_data(QVector<double>& dataConv);
protected:
    void run();
private:
    QTextStream *outfile;
    bool isSaveData;
    int numFrameNIRS; // 690+830 -> ch ->2
    int numFrameEEG;
    PORT_TYPE m_seriel;
    Dev m_Dev;
    volatile unsigned char isAlined;
    unsigned char isConfiged;
    unsigned char runReadThread;

};

#endif // NEGDRY_QT_H
