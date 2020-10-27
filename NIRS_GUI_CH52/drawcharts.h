#ifndef DRAWCHARTS_H
#define DRAWCHARTS_H


#include <math.h>
#include <vector>
#include <sstream>
#include <QDesktopWidget>

#include <qmutex.h>
#include "qdebug.h"

#include <QTimer>
#include "QDialog"
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include <QChartView>
#include <QRubberBand>
#include "QCategoryAxis"
#include "QThread"
#include "threadtimer.h"
#include "ThreadQueue.h"
#include "QtConcurrent"
#include <QChartView>
#include "QCategoryAxis"
#include "QDialog"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtWidgets/QLabel>

QT_CHARTS_USE_NAMESPACE
#define DEVICENUM 1
#define DispCh 3
#define RANGE  10000


class DrawCharts:public QChartView
{
    Q_OBJECT
public:
    DrawCharts(QWidget *parent = 0);
    ~DrawCharts();
    void initChart();
    void initChart2();
    void GetDate();

    const int seriesCount = 10;
    const int pointCount = 10000;

    QChart *chart;
    QLineSeries *series111[DispCh];
    quint16 count;
    QList<QXYSeries *> seriesList;
    QValueAxis* axisX;
    QValueAxis* axisY;
//    QCategoryAxis *axisY;
//    QCategoryAxis *axisX;
    QXYSeries *series;
    QScatterSeries *scatter ;

    QStringList colors;
    QVector<QPointF> waveDisp[DispCh];

};

#endif // DRAWCHARTS_H
