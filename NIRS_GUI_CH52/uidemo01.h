#ifndef UIDEMO01_H
#define UIDEMO01_H
#include <QDialog>
#include "paraset.h"
#include "randomwalk.h"
#include <QElapsedTimer>
#include "drawimage.h"


#ifdef ANALYSEC
  #include "analyzechart.h"
#endif
#include "QTime"
namespace Ui {
class UIDemo01;
}

class UIDemo01 : public QDialog
{
    Q_OBJECT

public:
    explicit UIDemo01(QWidget *parent = 0);
    ~UIDemo01();
signals:
    void putNIRSData(float*,float*,unsigned long,unsigned char );
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::UIDemo01 *ui;
    ParaSet *paraSet = NULL;
   // HANDLE m_Com;
    DrawImage *m_draw;
    RandomWalk *random;
#ifdef ANALYSEC
   AnalyzeChart *Analyzer;
#endif
    QThread *m_Thread;
    unsigned char isStart = false;
    QTimer *debug_Timer;
    QTime m_Time;
    QTime n_Time;
private slots:
    void initForm();
    void buttonClick();

private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
//    void on_btnMain_clicked();
    void AcceptPortMsg(QString);
    void on_btnHelp_clicked();

    void on_comboBox_3_currentIndexChanged(const QString &arg1);
    void on_comboBox_4_currentIndexChanged(const QString &arg1);
    void on_pushButton_clicked();

    void Debug_OnData();
    //void on_btnConfig_clicked();
    void on_comboBox_3_activated(const QString &arg1);
    void on_pushButton_3_clicked();
    void on_pageButton1_clicked();
    void on_pageButton2_clicked();
    void on_pageButton3_clicked();
    void on_pageButton4_clicked();
};

#endif // UIDEMO01_H
