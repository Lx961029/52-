#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H

#include "QLayout"
#include <vector>
#include <QDesktopWidget>
#include <QChart>
#include <QLineSeries>
#include <QTimer>
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
#include "drawcharts.h"

QT_CHARTS_USE_NAMESPACE//charts的域声明，必须有

#define DispCh 3 //每个通道有三条线，血红蛋白，血氧蛋白，总的
#define RANGE  1000 //1000个点
#define CHANNEL_CNT 13 //每个page 13张表


class DrawImage :public QGridLayout
{
    Q_OBJECT//QT中,类要支持信号与槽机制,需要继承自QObject并在头文件开头添加Q_OBJECT宏
public:

    DrawImage(QWidget *parent);
    virtual ~DrawImage();
//    void DrawInit();
//    void Draw();

private:
    QChart *chart;
    QList<QXYSeries *> seriesList;
    quint16 count;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QChartView *chartView;
    QStringList colors;
    DrawCharts **drawcharts;
    DrawCharts *drawchart;

    DrawImage & operator=(const DrawImage&);
    DrawImage(const DrawImage&);

};

#endif // DRAWIMAGE_H
