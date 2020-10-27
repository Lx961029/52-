#include "drawimage.h"
#include "datasource.h"
#include <QMessageBox>
#include "QDebug"

DrawImage::DrawImage(QWidget *parent)
{
    //------------chart位置分配-------------//
//    this->setColumnStretch(0,1);
//    this->setColumnStretch(1,1);
//    this->setColumnStretch(2,1);
//    this->setColumnStretch(3,1);

//    this->setRowStretch(0,1);
//    this->setRowStretch(1,1);
//    this->setRowStretch(2,1);
//    this->setRowStretch(3,1);

    //创建13个画图类
//    drawcharts = (DrawCharts**)malloc(CHANNEL_CNT*sizeof(DrawCharts*));//size要确认
//    for(int i=0;i<CHANNEL_CNT;i++){
//        *(drawcharts + i) = new DrawCharts(parent);
//        this->addWidget(*(drawcharts + i),i/4,i%4);
//    }
    //--------------一个画图类测试-------------//
    drawchart=new DrawCharts(parent);
    this->addWidget(drawchart);
}

DrawImage::~DrawImage()
{

}



