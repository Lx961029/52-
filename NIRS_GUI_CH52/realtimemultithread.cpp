
#include "realtimemultithread.h"
#include "QDebug"


float amplifier;
int pointJump;

RealTimeMultiThread::RealTimeMultiThread(QWidget *parent)
{
    //添加左侧快捷按钮
    initChart();
    mTQ690 = new ThreadQueue<double>(5000);
    mTQ830 = new ThreadQueue<double>(5000);

    this->setRubberBand(QChartView::RectangleRubberBand);
    amplifier = 1;
    pointJump = 1;
    ampMode = 0;
    displayChannel = 0;

    for(int i = 0;i < RANGE;i ++){
       waveDisp[0].append(QPointF(i,0));
       waveDisp[1].append(QPointF(i,0));
       waveDisp[2].append(QPointF(i,0));
    }
    series[2]->setVisible(false);
    jump = 1;
    jcnt = 0;
    waveCnt = 0;
    //线程开始

}

RealTimeMultiThread::~RealTimeMultiThread()
{
   // StopGenData();
   m_ChartUpdateTimer->stop();
   delete m_ChartUpdateTimer;
   delete chart;
}

void RealTimeMultiThread::StartGenData()
{

}
void RealTimeMultiThread::StopGenData(){

}

void RealTimeMultiThread::OnData(void* param,double NIRS690,double NIRS830){
    //qDebug()<<"更新数据"<<endl;

    RealTimeMultiThread *self = ((RealTimeMultiThread *)param);
    if(self->jcnt < self->jump){
       self->jcnt ++;
       return;
    }else{
        self->jcnt = 0;
    }
    (self->waveDisp)[0][self->waveCnt].setY(NIRS690);
    (self->waveDisp)[1][self->waveCnt].setY(NIRS830);
    (self->waveDisp)[2][self->waveCnt].setY(NIRS690 + NIRS830);
     self->waveCnt ++;
     if(self->waveCnt >= RANGE) self->waveCnt = 0;
}

void RealTimeMultiThread::Debug_OnData(){

}

void RealTimeMultiThread::onChartUpdateTimer(){
    //qMutex.lock();
        for(int i=0;i<DispCh;i++){  // only HB
           series[i]->replace(waveDisp[i]);
           qDebug() << QString("RealTimeMultiThread thread id:") << QThread::currentThreadId();
        }

    //qMutex.unlock();
}

void RealTimeMultiThread::initChart()
{
   QPen pen1;
   QBrush brush1;
   brush1.setColor(Qt::white);
   pen1.setWidth(1);

    for(int i=0;i<DispCh;i++){
      series[i] = new QLineSeries();
      series[i]->setUseOpenGL(true);
    }
    chart = new QChart();
    chart->setContentsMargins(0,0,0,0);
    chart->setMargins(QMargins(0,0,0,0));
    chart->setBackgroundBrush(brush1);
    for(int i=0;i<DispCh;i++)
      chart->addSeries(series[i]);
      chart->createDefaultAxes();
        QCategoryAxis *axisY=new QCategoryAxis;
//        chart->axisY()->setRange(-3+3.38328, 4.6+1.38368);
        chart->axisY()->setRange(-1, 1);
       //axisY->setStartValue(0);
        //append要按照大小顺序依次添加
        //chart->axisX()->setGridLineVisible(false);
        //chart->axisY()->setGridLineVisible(true);
        //下边这一句代码的作用是让刻度线和刻度的label对齐
        axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
      for(int i=0;i<DispCh;i++)
      chart->setAxisY(axisY,series[i]);

      axisY->setGridLinePen(pen1);


      for(char i=1;i<2;i++){
       //
       axisY->append(" ",0);
       // baseline[i-1] = i*10;   //init the baseline
        //amplify[i-1] = 1;
      }
        QCategoryAxis *axisX=new QCategoryAxis;
        axisX->setMin(0);
        axisX->setMax(RANGE);
        axisX->setStartValue(0);

        //下边这一句代码的作用是让刻度线和刻度的label对齐
      axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
      for(int i=0;i<DispCh;i++){
        chart->setAxisX(axisX,series[i]);
      }
    chart->legend()->hide();
    this->setChart(chart);
}

void RealTimeMultiThread::startdraw(){
    //#ifdef huatu

        thread = new QThread();
        thread->start(QThread::LowPriority);
        //thread->setPriority(QThread::LowPriority);   //设置优先级
        timer = new QTimer();
        timer->setInterval(500);
        timer->moveToThread(thread);


        //qDebug() << QString("RealTimeMultiThread thread id:") << QThread::currentThreadId();
        //connect(timer, SIGNAL(timeout()), this, SLOT(onChartUpdateTimer()), Qt::QueuedConnection);
        connect(timer, SIGNAL(timeout()), this, SLOT(onChartUpdateTimer()), Qt::DirectConnection);
        connect(thread, SIGNAL(started()), timer,SLOT(start()));
    //#endif
}


//*******************************display***************************************
//void RealTimeMultiThread::wheelEvent(QWheelEvent *event)
//{
//  //if(ampMode == 0)
//    if (event->delta() > 0) {
//       chart->zoom(1.1);//amplifier += 0.3;
//    } else {
//       chart->zoom(0.9);//amplifier>0?amplifier -= 0.2:amplifier = 0;
//    }
//    /*
//  else{
//      if (event->delta() > 0) {
//          pointJump<=15?pointJump+=1:pointJump+=0;
//      } else {
//          pointJump>1?pointJump-=1:pointJump-=0;
//      }

//  }
//  */

//    QWidget::wheelEvent(event);
//}


