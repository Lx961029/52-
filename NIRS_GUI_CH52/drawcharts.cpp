#include "drawcharts.h"
#include "datasource.h"
#include "QDebug"

DrawCharts::DrawCharts(QWidget *parent)
{

    initChart2();
    //设置缩放
    this->setRubberBand(QChartView::RectangleRubberBand);
    //GetDate();
}
DrawCharts::~DrawCharts(){
    delete chart;
}

//void DrawCharts::initChart()
//{
//    qDebug()<<"进入初始化";
//   QPen pen1;
//   QBrush brush1;
//   brush1.setColor(Qt::white);
//   pen1.setWidth(1);

//    for(int i=0;i<DispCh;i++){
//      series[i] = new QLineSeries();
//      series[i]->setUseOpenGL(true);
//    }
//    chart = new QChart();
//    chart->setContentsMargins(0,0,0,0);
//    chart->setMargins(QMargins(0,0,0,0));
//    chart->setBackgroundBrush(brush1);
//    for(int i=0;i<DispCh;i++)
//      chart->addSeries(series[i]);

//    chart->createDefaultAxes();
//    axisY=new QCategoryAxis;
//    //chart->axisY()->setRange(-1, 1);
//    chart->axisY()->setRange(-0.1, 0.1);
//    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
//    for(int i=0;i<DispCh;i++)
//       chart->setAxisY(axisY,series[i]);
//     axisY->setGridLinePen(pen1);

//      for(char i=1;i<2;i++){
//       axisY->append(" ",0);
//      }
//        axisX=new QCategoryAxis;
//        axisX->setMin(0);
//        axisX->setMax(RANGE);
//        axisX->setStartValue(0);

//        //下边这一句代码的作用是让刻度线和刻度的label对齐
//      axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
//      for(int i=0;i<DispCh;i++){
//        chart->setAxisX(axisX,series[i]);
//      }
//      chart->setTitle("111");
//    chart->legend()->hide();
//    this->setChart(chart);
//}


void DrawCharts::initChart2(){
        colors << "red" << "blue" << "green" << "black";
        chart = new QChart();
        chart->legend()->hide();


        for (int i = 0; i < seriesCount; i++) {
            series = 0;
            int colorIndex = i % colors.size();
            if (i % 2) {
                series = new QScatterSeries;
                scatter = static_cast<QScatterSeries *>(series);
                scatter->setColor(QColor(colors.at(colorIndex)));
                scatter->setMarkerSize(qreal(colorIndex + 2) / 2.0);
                scatter->setPen(QPen("black"));

            } else {
                series = new QLineSeries;
                series->setPen(QPen(QBrush(QColor(colors.at(colorIndex))),
                                    qreal(colorIndex + 2) / 2.0));
            }

            seriesList.append(series);
            series->setUseOpenGL(true);
            chart->addSeries(series);
          }
             this->setChart(chart);


        DataSource dataSource;
        dataSource.generateData(seriesCount, 10, pointCount);

        QLabel *fpsLabel = new QLabel(this);
        QLabel *countLabel = new QLabel(this);
        QString countText = QStringLiteral("Total point count: %1");
        countLabel->setText(countText.arg(pointCount * seriesCount));
        countLabel->adjustSize();
        fpsLabel->move(10, 2);
        fpsLabel->adjustSize();
        fpsLabel->raise();
        fpsLabel->show();
        countLabel->move(10, fpsLabel->height());
        fpsLabel->raise();
        countLabel->show();

        QObject::connect(chart->scene(), &QGraphicsScene::changed,
                         &dataSource, &DataSource::handleSceneChanged);

    //    for (int i=0 ;i<3;i++) {
    //        seriesList.append(series111[i]);
    //    }
        dataSource.startUpdates(seriesList, fpsLabel);
}



void DrawCharts:: GetDate(){
    DataSource dataSource;
    dataSource.generateData(seriesCount, 10, pointCount);

    QLabel *fpsLabel = new QLabel(this);
    QLabel *countLabel = new QLabel(this);
    QString countText = QStringLiteral("Total point count: %1");
    countLabel->setText(countText.arg(pointCount * seriesCount));
    countLabel->adjustSize();
    fpsLabel->move(10, 2);
    fpsLabel->adjustSize();
    fpsLabel->raise();
    fpsLabel->show();
    countLabel->move(10, fpsLabel->height());
    fpsLabel->raise();
    countLabel->show();

    QObject::connect(chart->scene(), &QGraphicsScene::changed,
                     &dataSource, &DataSource::handleSceneChanged);

//    for (int i=0 ;i<3;i++) {
//        seriesList.append(series111[i]);
//    }
    dataSource.startUpdates(seriesList, fpsLabel);
}
