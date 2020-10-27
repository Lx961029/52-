#ifndef PARASET_H
#define PARASET_H

#include <QDialog>

#ifdef MODEBLUETOOTH
   #include <QtBluetooth/qbluetoothglobal.h>
   #include <QtBluetooth/qbluetoothlocaldevice.h>
   #include <qbluetoothaddress.h>
   #include <qbluetoothdevicediscoveryagent.h>
   #include <qbluetoothlocaldevice.h>
   #include <qbluetoothsocket.h>
   #include <QListWidgetItem>
#else
   #include <QtSerialPort/QSerialPort>
   #include <QtSerialPort/QSerialPortInfo>
#endif
//extern QSerialPort *serialPort;

//是否保存数据
extern bool moulde_one;
extern bool isSaveData;
extern bool isMark;//Mark点是否开启
namespace Ui {
class ParaSet;
}

class ParaSet : public QDialog
{
    Q_OBJECT

public:
    explicit ParaSet(QWidget *parent = nullptr);
    ~ParaSet();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_search_clicked();

private:
    Ui::ParaSet *ui;
    void InitForm();//初始化界面以及其他处理
    QStringList GetEnableCommPort();//获取本机串口
    void PortInit();//串口初始化
   // HANDLE m_Com;
signals:
    void SendData(QString);
    //模式切换
    void ParaChanged();


#ifdef MODEBLUETOOTH

public:
    unsigned char getBuleToothState(){
        return socket->ConnectedState;
    }
   static void* getCom(){
       return (void *)socket;
   }
private:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    static QBluetoothSocket *socket;
    QBluetoothSocket *NoneStaticSocket;
private slots:
    void addBlueToothDevicesToList( const QBluetoothDeviceInfo &info );
    void itemActivated(QListWidgetItem *item);
    void bluetoothConnectedEvent();
    void bluetoothDisconnectedEvent();
#else
private:
    static QSerialPort *serial;
    QSerialPortInfo *com_info;
public:
    static void* getCom(){
        return serial;
    }
#endif
};
// **********静态成员初始化************************

#endif // PARASET_H
