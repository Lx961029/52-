#ifndef ANALYZECHART_H
#define ANALYZECHART_H

#include <math.h>
#include <QTimer>
#include "QDialog"
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include <QChartView>
#include <QRubberBand>
#include "QCategoryAxis"
#include <qmutex.h>
#include <QDesktopWidget>
#include <vectormath.h>
#include <classicalpse.h>
#include <iostream>

QT_CHARTS_USE_NAMESPACE
using namespace std;
using namespace splab;

class AnalyzeChart : public QChartView
{
Q_OBJECT  // 不加宏，无法连接
public:
    AnalyzeChart(QWidget *parent);
    ~AnalyzeChart();
   static AnalyzeChart *static_this;
public slots:
    void putNIRSData(float *HbrData, float *HboData, unsigned long count,unsigned char transformMode);

  //  void s_cuculated(QVector<double> b);
private:
    QTimer *debug_Timer;
    void initChart();
    QChart *chart;
    QLineSeries *serial;
    static void Debug_NIRSData(float *HbrData, float *HboData, unsigned long count);
    QVector<QPointF> res;
    unsigned char ampMode = 0;
    void wheelEvent(QWheelEvent *event)
    {
     // QRectF oldRect = chart->rect();


        if (event->delta() > 0) {
            //chart->setGeometry(oldRect.x()+1,oldRect.y()+1,oldRect.width(),oldRect.height());
            chart->zoom(1.1);
        } else {
            chart->zoom(0.9);
        }


        QWidget::wheelEvent(event);
    }
private slots:
    void Debug_OnData();
    void cuculated(QVector<double> res);
};

#endif // ANALYZECHART_H
