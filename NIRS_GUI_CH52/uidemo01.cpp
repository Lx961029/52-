#include "uidemo01.h"
#include "ui_uidemo01.h"
#include "iconhelper.h"
#include "paraset.h"
#include <QApplication>
#include <QButtonGroup>
#include <QIcon>
#include <QPushButton>
#include <QComboBox>
#include <QFileDialog>
#include "chartdir.h"
#include "analyzechart.h"
#include "QDebug"
#include <math.h>
//#include <svd.h>

using namespace std;
bool isSaveData = false;
bool isMark = false;

UIDemo01::UIDemo01(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UIDemo01)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);

    /*
    realTime = new RealTimeMultiThread(this);
    ui->plotA->addWidget(realTime);
    */
    this->initForm();
#ifdef ANALYSEC
    Analyzer = new AnalyzeChart(this);
    ui->plotB->addWidget(Analyzer);
    this->initForm();
   QObject::connect(this,SIGNAL(putNIRSData(float*,float*,unsigned long,unsigned char )),  \
                     Analyzer,SLOT(putNIRSData(float *, float *, unsigned long ,unsigned char )));
#endif

//    debug_Timer = new QTimer(this);
//    QObject::connect(debug_Timer, SIGNAL(timeout()),this,SLOT(Debug_OnData()));

    // m_Time.setHMS(0,0,0,0);
    m_Time.setHMS(0,0,0);
    n_Time.setHMS(0,0,0);
    //qDebug()<<m_time.toString()<<endl;

}

void UIDemo01::Debug_OnData(){
//     n_Time = m_Time.addSecs(1);
//     //qDebug()<<m_Time.toString("hh:mm:ss")<<endl;
//     ui->time->setText(m_Time.toString("hh:mm:ss"));
//     m_Time = n_Time;
}

UIDemo01::~UIDemo01()
{
    delete ui;
    delete random;
}

bool UIDemo01::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        if (watched == ui->widgetTitle) {
            on_btnMenu_Max_clicked();
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

void UIDemo01::initForm()
{
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

   // IconHelper::Instance()->setIcon(ui->labIco, QChar(0xf099), 30);

//#ifndef MODEBLUETOOTH
//    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
//    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf067));
//    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
//#endif

    //ui->widgetMenu->setVisible(false);
    ui->widgetTitle->installEventFilter(this);
    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTop->setProperty("nav", "top");
    ui->labTitle->setText("血氧采集系统");
    ui->labTitle->setFont(QFont("Microsoft Yahei", 20));
    this->setWindowTitle(ui->labTitle->text());

   // ui->stackedWidget->setStyleSheet("QLabel{font:60pt;}");

    //单独设置指示器大小
    int addWidth = 20;
    int addHeight = 10;
    int rbtnWidth = 15;
    int ckWidth = 13;
    int scrWidth = 12;
    int borderWidth = 3;
qDebug() << "asdas" <<endl;
    QStringList qss;
    qss.append(QString("QComboBox::drop-down,QDateEdit::drop-down,QTimeEdit::drop-down,QDateTimeEdit::drop-down{width:%1px;}").arg(addWidth));
    qss.append(QString("QComboBox::down-arrow,QDateEdit[calendarPopup=\"true\"]::down-arrow,QTimeEdit[calendarPopup=\"true\"]::down-arrow,"
                       "QDateTimeEdit[calendarPopup=\"true\"]::down-arrow{width:%1px;height:%1px;right:2px;}").arg(addHeight));
    qss.append(QString("QRadioButton::indicator{width:%1px;height:%1px;}").arg(rbtnWidth));
    qss.append(QString("QCheckBox::indicator,QGroupBox::indicator,QTreeWidget::indicator,QListWidget::indicator{width:%1px;height:%1px;}").arg(ckWidth));
    qss.append(QString("QScrollBar:horizontal{min-height:%1px;border-radius:%2px;}QScrollBar::handle:horizontal{border-radius:%2px;}"
                       "QScrollBar:vertical{min-width:%1px;border-radius:%2px;}QScrollBar::handle:vertical{border-radius:%2px;}").arg(scrWidth).arg(scrWidth / 2));
    qss.append(QString("QWidget#widget_top>QToolButton:pressed,QWidget#widget_top>QToolButton:hover,"
                       "QWidget#widget_top>QToolButton:checked,QWidget#widget_top>QLabel:hover{"
                       "border-width:0px 0px %1px 0px;}").arg(borderWidth));
    qss.append(QString("QWidget#widgetleft>QPushButton:checked,QWidget#widgetleft>QToolButton:checked,"
                       "QWidget#widgetleft>QPushButton:pressed,QWidget#widgetleft>QToolButton:pressed{"
                       "border-width:0px 0px 0px %1px;}").arg(borderWidth));
    this->setStyleSheet(qss.join(""));

    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    this->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(1);//设置透明度，0位全透明，1位不透明
    QSize icoSize(32, 32);
    int icoWidth = 85;

    //设置顶部导航按钮
    QList<QToolButton *> tbtns = ui->widgetTop->findChildren<QToolButton *>();
    foreach (QToolButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    //ui->btnMain->click();
}


void UIDemo01::buttonClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    //QMessageBox::information(this, "提示", "port");
    if (name == "开始采集") {
        //-------------测试代码-------------//
//            m_draw=new DrawImage(this);
//            ui->plotA->addLayout(m_draw);

        //ui->stackedWidget->setCurrentIndex(0);

      if(isStart == false){
        //realTime->StartGenData();
        isStart = true;
      }
      // qDebug()<<"asd"<<endl;
    } else if (name == "参数设置") {
        paraSet = new ParaSet(NULL);
        //双屏显示需要额外设置
        connect(paraSet,SIGNAL(SendData(QString)), this, SLOT(AcceptPortMsg(QString)));
        //connect(paraSet,SIGNAL(ParaChanged()), this, SLOT(paraChanged()));
        paraSet->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
        paraSet->show();
        //paraSet->serialPort;

//        this->show();
//        this->hide();
//        ui->stackedWidget->setCurrentIndex(1);
    } else if (name == "缩放模式") {
        //realTime->displayModeChange();
        //ui->stackedWidget->setCurrentIndex(2);
    } else if (name == "数据保存") {
        //ui->stackedWidget->setCurrentIndex(3);
    } else if (name == "用户退出") {
        //delete paraSet;
        //delete random;
        terminate();    //暴力退出所有线程
        exit(0);
    }
}

void UIDemo01::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void UIDemo01::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
    }

    this->setProperty("canMove", max);
    max = !max;
}

void UIDemo01::on_btnMenu_Close_clicked()
{
    close();
}

//void UIDemo01::on_btnMain_clicked()
//{
//    qDebug()<<"start"<<endl;
//    if(paraSet == NULL)
//    {
//        QMessageBox::information(this, "提示", "请到参数设置里打开port");
//    }
//    else
//    {
//        if (ui->btnMain->text() == "停止采集")
//        {

//            //*if (m_Com) CloseHandle(m_Com);
//            //ui->stackedWidget->show();
//            if(random != NULL)random->StopGenData();
//            ui->btnMain->setText("开始采集");
//        }
//        else if (ui->btnMain->text() == "开始采集")
//        {
//            //paraSet->show();
//           if(random != NULL) random->start_trans();
//           //random->setDisconnect();
//           ui->btnMain->setText("停止采集");
//        }
//    }

//}
void UIDemo01::AcceptPortMsg(QString msg)
{
    if (ui->btnMain->text() == "停止采集")
    {
        isMark = true;
    }
   else
    {
   // if(QString::compare(msg,"采集数据") == 0)
       // realTime.StartGenData();
    }
   if(QString::compare(msg,"确认") == 0){

       //--------测试新画图类关闭原来的画图类-------------//
        random = new RandomWalk(this);
        ui->plotA->addLayout(random);
        random->start_trans();
        qDebug() << QString("UIDemo01 thread id:") << QThread::currentThreadId();

//        m_Thread = new QThread();
//        QObject::connect(m_Thread,SIGNAL(started()),random,SLOT(GenerateData()));
//        m_Thread->start();

        //打开计时
    }
/*
    if(QString::compare(msg,"触发模式") == 0){
       //realTime.ParaChanged(1);    //0 为模式 1，1为模式2
    }else if(QString::compare(msg,"连续模式") == 0){
       //realTime.ParaChanged(0);    //0 为模式 1，1为模式2
    }
 */
//    if (serialPort->isOpen())
//        serialPort->close();
    ui->btnMain->setText("停止采集");
}



//数据保存，停止保存按钮
void UIDemo01::on_btnHelp_clicked()
{
//    QString dir_str = "C://NIRS";
//    QDir dir;
//    if (!dir.exists(dir_str)) dir.mkdir(dir_str);
    if(paraSet->getCom()==NULL){
        QMessageBox::information(this, "提示", "请先设置参数");

    }else{
        if (ui->btnHelp->text() == "数据保存")
        {
            isSaveData = true;
            ui->btnHelp->setText("停止保存");
            random->saveDataToFile(true);
    //        debug_Timer->start(1000);
        }
        else if (ui->btnHelp->text() == "停止保存")
        {
            isSaveData = false;
            ui->btnHelp->setText("数据保存");
            random->saveDataToFile(false);
        }
    }
}



void UIDemo01::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "HbO"){
        //realTime->setDisplayChannel(0);
    }else if(arg1 == "HbR"){
       // realTime->setDisplayChannel(1);
    }else if(arg1 == "HbT"){
        //realTime->setDisplayChannel(0);
    }else{

    }
}

void UIDemo01::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "EEG1"){
        //realTime->setDisplayChannel(2);
    }else if(arg1 == "EEG2"){
        //realTime->setDisplayChannel(3);
    }else{
    }
}

void UIDemo01::on_pushButton_clicked()
{
//    float *RawDataHbR,*RawDataHbO;
//    float time_s,time_scale = 1;
//    unsigned long pointCnt;
//    bool ok;
//    if(ui->comboBox_3->currentText() == "HbT");
//    if(ui->time_scale->currentText() == "h") {
//        time_scale = 3600;
//    }
//     else if(ui->time_scale->currentText() == "min"){
//        time_scale = 60;
//    }


//   // time_s =ui->time_input->text().toFloat(&ok) * time_scale;
//    if(ui->time_input->text() == NULL) return ;
//    time_s =ui->time_input->text().toFloat(&ok) * time_scale;
//    if(time_s >= 24*3600){
//         QMessageBox::warning(NULL, "warning", "Time is too long", QMessageBox::Yes, QMessageBox::Yes);
//         return;
//    }
//    //qDebug()<<time_s<<endl;

//    //if(realTime->getNIRSData(4,RawDataHbR,RawDataHbO,(unsigned int)time_s,&pointCnt))
//     emit(putNIRSData(RawDataHbR,RawDataHbR,pointCnt,1));

//  //  emit();
}

/*
void UIDemo01::on_btnConfig_clicked()
{
    //QMessageBox::information(this, "提示", "port");
    paraSet = new ParaSet(NULL);
    //双屏显示需要额外设置
    connect(paraSet,SIGNAL(SendData(QString)), this, SLOT(AcceptPortMsg(QString)));
    //connect(paraSet,SIGNAL(ParaChanged()), this, SLOT(paraChanged()));
    paraSet->setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    paraSet->show();
    qDebug()<<"new paraset"<<endl;
}
*/

void UIDemo01::on_comboBox_3_activated(const QString &arg1)
{

}

void UIDemo01::on_pushButton_3_clicked()
{
    //reset
    random->resetDisp();
}

void UIDemo01::on_pageButton1_clicked()
{
    random->setPage(0);
}

void UIDemo01::on_pageButton2_clicked()
{
    random->setPage(1);
}

void UIDemo01::on_pageButton3_clicked()
{
    random->setPage(2);
}

void UIDemo01::on_pageButton4_clicked()
{
    random->setPage(3);
}
