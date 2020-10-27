#include "analyzechart.h"
#include "QString"
#include "QDebug"
#include <thread>
#include "QMessageBox"
#include <svd.h>
#include <QDebug>
static unsigned char vecChangeFlag;
static QVector<double> *vecRes;
AnalyzeChart* AnalyzeChart::static_this = NULL;



AnalyzeChart::AnalyzeChart(QWidget *parent = 0)
{

    //cvec为虚数
    initChart();
    static_this = this;

    float *a,*b;
    debug_Timer = new QTimer(this);
//    QObject::connect(debug_Timer, SIGNAL(timeout()),this,SLOT(Debug_OnData()));
//    debug_Timer->start(20);
    //std::thread *caculator;
    //caculator = new std::thread();
    std::thread caculator(Debug_NIRSData,a,b,10);
    caculator.detach();

    this->setRubberBand(QChartView::RectangleRubberBand);

    /*
    while(vecChangeFlag == 0){

    }
    vecChangeFlag = 0 ;
    qDebug()<<vecRes->size()<<endl;
    */
}

AnalyzeChart::~AnalyzeChart(){
    if(serial) delete serial;
}

void AnalyzeChart::initChart(){

    QPen pen1;
    QBrush brush1;
    brush1.setColor(Qt::yellow);
    pen1.setColor(Qt::black);
    pen1.setWidth(1);

    serial = new QLineSeries;
     serial->setUseOpenGL(true);

     chart = new QChart();
     chart->setBackgroundBrush(brush1);

     chart->setMargins(QMargins(0,0,0,0));
     chart->setContentsMargins(0,0,0,0);

       chart->addSeries(serial);
       chart->createDefaultAxes();
         QCategoryAxis *axisY=new QCategoryAxis;

         chart->axisY()->setRange(-5, 10);
        //axisY->setStartValue(0);
         //append要按照大小顺序依次添加
         //chart->axisX()->setGridLineVisible(false);
         //chart->axisY()->setGridLineVisible(true);
         //下边这一句代码的作用是让刻度线和刻度的label对齐
         axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
         chart->setAxisY(axisY,serial);

       axisY->setGridLinePen(pen1);
       axisY->setGridLineColor(Qt::black);


        //
        //axisY->append(" ",0);
        // baseline[i-1] = i*10;   //init the baseline
         //amplify[i-1] = 1;

         QCategoryAxis *axisX=new QCategoryAxis;
         axisX->setMin(0);
         axisX->setMax(1024);
         axisX->setStartValue(0);
         axisX->setGridLineColor(Qt::black);
         axisX->setLabelsColor(Qt::red);
         /*
         for(int i = 0;i< 1024 ;i+=50){
             if(i == 0)
              axisX->append(QString::number(i/50)+"(Hz)",i);
             else{
              axisX->append(QString::number(i/50),i);
             }

         }*/

         axisX->append("",0);

         //下边这一句代码的作用是让刻度线和刻度的label对齐
       axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

         chart->setAxisX(axisX,serial);


    /*hide legend*/
     chart->legend()->hide();
     this->setChart(chart);
}

void AnalyzeChart::putNIRSData(float *HbrData, float *HboData, unsigned long count,unsigned char transformmode){
      //此任务加入线程中?
//      if(count <= 3000){
//          QMessageBox::warning(this,"too short","please collect at least 20s");
//      }

}


void AnalyzeChart::Debug_OnData(){
    if(vecChangeFlag == 1){
      serial->replace(res);
      vecChangeFlag = 0;
    }
}

void AnalyzeChart::Debug_NIRSData(float *hbo,float *hbr,unsigned long count){
/*
         QFile file("C:\\Users\\Administrator\\Desktop\\sin_data.txt");
         if(!file.open(QFile::ReadOnly | QFile::Text))
             {
                 //QMessageBox::warning(this,"file write","can't open",QMessageBox::Yes);
                  qDebug()<<"w"<<endl;
             }

         QTextStream in(&file);
         //qDebug()<<in.readAll();
         std::string array =  in.readAll().toStdString();
     file.close();
*/
     typedef double  Type;
     const   int     N = 1024;  //信号长
     const   int     K = 25;    //overlap
     const   int     M = 50;    //窗长
     const   int     L = 2048; // fft点数
     int mfn = L/2+1;
      Type amp1 = Type(1.0),
           amp2 = Type(0.5);
      Type f1 = Type(0.3),
           f2 = Type(0.4);
      Vector<Type> tn = linspace(Type(0), Type(N-1), N );
      Vector<Type> sn = amp1*sin(TWOPI*f1*tn) + amp2*sin(TWOPI*f2*tn);

      /******************************** [ widow ] ******************************/
      Vector<Type> wn = splab::window( "Hamming", M, Type(1.0));

      /********************************* [ PSD ] *******************************/
  //	Vector<Type> Ps = correlogramPSE( sn, L );
  //	Vector<Type> Ps = periodogramPSE( sn, wn, L );
  //    Vector<Type> Ps = bartlettPSE( sn, M, L );
      Vector<Type> Ps = welchPSE( sn, wn, K, L );
  //	Vector<Type> Ps = btPSE( sn, wn, L );
       cout << "vector v2 : " << Ps << endl;
      /******************************** [ PLOT ] *******************************/

      double temp;
      unsigned int i=0;
      Vector<Type>::iterator itr = Ps.begin();
          while( itr != Ps.end()){
              temp = *itr++;
              static_this->res.push_back( QPointF(i,temp));
              i++;
          }



   // Vec<double> m_vec;  // 只能用double，模拟转换成功
   // array.
     //char* wavDat= array.data();
     //*(wavDat+wavSize) = '\0';
    // Vec<double> aa(10);
     //mat temp(2, 2);
    // vec temp()
        //  Vec<double> m_vec(array);  // 只能用double，模拟转换成功
//          qDebug() << m_vec.size() << endl;
//          Vec<std::complex<double>> out;
//          out = fft_real(m_vec,2048);
//          qDebug() << out.size() << endl;
//          for(int i = 0;i < 2048;i++){
//              std::complex<double> temp = out.get(i);
//              static_this->res.push_back(QPointF(i,log10(pow((pow(temp.real(),2)+pow(temp.imag(),2)),0.5))));
//          }


      vecChangeFlag = 1;
      return ;

}


void AnalyzeChart::cuculated(QVector<double> res){
   //  qDebug() << res.size() << endl;
}

