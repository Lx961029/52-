#include "paraset.h"
#include "ui_paraset.h"
#include <QMessageBox>

#include <stdio.h>
#include <stdlib.h>
#include "myhelper.h"
#include <QGraphicsOpacityEffect>
#include<qdebug.h>
//QSerialPort *serialPort = new QSerialPort;
//HANDLE m_Com = 0;

bool moulde_one = true;

#ifdef MODEBLUETOOTH
    static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805F9B34FB");
    QBluetoothSocket* ParaSet::socket = NULL;
#else
    QSerialPort* ParaSet::serial = NULL;// 不能放在.h文件里面
#endif

ParaSet::ParaSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParaSet)
{
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    QString stylesheet("background-color:rgba(68,68,68,1);QPushButton:hover{background:rgb(100,100,100);} QPushButton:pressed{background:rgb(255,255,255);}");
    setStyleSheet(stylesheet);
    ui->setupUi(this);
    //ui->pushButton->hide();//打开串口按钮默认隐藏
   // m_Com = m_Com;  //
    #ifdef MODEBLUETOOTH
        setWindowState(Qt::WindowMaximized);
        localDevice = new QBluetoothLocalDevice();
        discoveryAgent =new QBluetoothDeviceDiscoveryAgent();
        //discoveryAgent->start();
        socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        if(socket == NULL) QMessageBox::information(this, "提示", "未打开蓝牙设备");

        connect(discoveryAgent,
                   SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
                   this,
                   SLOT(addBlueToothDevicesToList(QBluetoothDeviceInfo))
                   );
        connect(ui->list,
                   SIGNAL(itemActivated(QListWidgetItem *)),
                   this,
                   SLOT(itemActivated(QListWidgetItem *))
                   );
        connect(socket,
                SIGNAL(connected()),
                this,
                SLOT(bluetoothConnectedEvent())
                );
        connect(socket,
                SIGNAL(disconnected()),
                this,
                SLOT(bluetoothDisconnectedEvent())
                );
        if( localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff )  {
            localDevice->powerOn();
        }


    #else
        if(serial) delete serial;
        serial = new QSerialPort;
    #endif
    InitForm();

}

ParaSet::~ParaSet()
{

    delete ui;
#ifdef MODEBLUETOOTH
    if(discoveryAgent->isActive())
        discoveryAgent->stop();
    delete socket;
    delete localDevice;
    delete discoveryAgent;
#else
    serial->close();
    delete serial;
#endif

}

void ParaSet::on_pushButton_3_clicked()
{
    this->close();
}
void ParaSet::InitForm()
{
#ifdef MODEBLUETOOTH

#else
    QStringList portList;
    portList = GetEnableCommPort();
    ui->comboBox->addItems(portList);
    ui->lineEdit->setText("921600");
    ui->lineEdit_2->setText("8");
    ui->lineEdit_3->setText("0");
    ui->lineEdit_4->setText("1");
    //ui->lineEdit_5->setText("1");
#endif
}
// 获取计算机可用口
#ifdef MODEBLUETOOTH
    void ParaSet::addBlueToothDevicesToList( const QBluetoothDeviceInfo &info )
    {
        QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
        QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);

        //discoveryAgent->stop();
        if (items.empty()) {
            QListWidgetItem *item = new QListWidgetItem(label);
            QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
            if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
                item->setTextColor(QColor(Qt::green));
            else
                item->setTextColor(QColor(Qt::black));
            ui->list->addItem(item);
        }
    }

    void ParaSet::itemActivated(QListWidgetItem *item)
    {
        QString text = item->text();

        int index = text.indexOf(' ');

        if (index == -1)
            return;
        //discoveryAgent->stop();
        QBluetoothAddress address(text.left(index));
        QString name(text.mid(index + 1));
        qDebug() << "You has choice the bluetooth address is " << address;
        qDebug() << "The device is connneting.... ";
        QMessageBox::information(this,tr("Info"),tr("The device is connecting..."));
        socket->connectToService(address, QBluetoothUuid(serviceUuid) ,QIODevice::ReadWrite);

        ui->buletoothState->setText("等待蓝牙连接...");
//         while(socket->ConnectedState<=0){}
//           QMessageBox::information(this,tr("Info"),tr("The device is connected!"));
//           ui->buletoothState->setText("蓝牙已连接");
    }
    void ParaSet::bluetoothConnectedEvent()
    {
      // 2017/10/8 更新一下，请在这里插入关闭蓝牙查找服务，否则数据会断。
       // 具体语句是什么我忘记了，反正使用discoveryAgent的一个什么close，或者stop的方法
       discoveryAgent->stop();
        QMessageBox::information(this,tr("Info"),tr("The device is connected"));

        qDebug() << "The android device has been connected successfully!";

    }

    void ParaSet::bluetoothDisconnectedEvent()
    {
        qDebug() << "The android device has been disconnected successfully!";
        QMessageBox::information(this,tr("Info"),tr("disconnected!"));
    }

#else
QStringList ParaSet::GetEnableCommPort()
{
    QStringList CommPortList;
    QString portName=ui->comboBox->currentText();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
      // if(QString::compare(portName,))
        serial->setPort(info);
        if (serial->open(QIODevice::ReadWrite))
        {
            CommPortList.append(serial->portName());
            serial->close();
        }
    }
    return CommPortList;
}
//参数初始化
void ParaSet::PortInit()
{
    QString portName=ui->comboBox->currentText();
    QByteArray Read_buf;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       if(QString::compare(portName,info.portName()) == 0)
        serial->setPort(info);
    }
    //设置串口名
   // serial->setPortName(portName);
    if(serial->open(QIODevice::ReadWrite))
       {
           //qDebug() << "serial->open(QIODevice::ReadWrite)";
           serial->setBaudRate(921600);
           serial->setParity(QSerialPort::NoParity);
           serial->setDataBits(QSerialPort::Data8);
           serial->setStopBits(QSerialPort::OneStop);
           serial->setFlowControl(QSerialPort::NoFlowControl);

           serial->clearError();
           serial->clear();
      }else{
           QMessageBox::information(this, "提示", "串口数据格式设置失败");
      }
}
#endif
void ParaSet::on_pushButton_clicked()
{

    this->close();
}

//发送命令到设备
void ParaSet::on_pushButton_2_clicked()
{
#ifdef MODEBLUETOOTH
    if(getBuleToothState()){

    }else{
        QMessageBox::information(this, "提示", "蓝牙连接失败");
    }
#else
    PortInit();
    emit SendData("确认");  // to row 192
   //qDebug()<<"asd"<<endl;
#endif
    this->close();
}

void ParaSet::on_search_clicked()
{
    #ifdef MODEBLUETOOTH
        discoveryAgent->start();//后面参数设置精度
    #else

    #endif
}





