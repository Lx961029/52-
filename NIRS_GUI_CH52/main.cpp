#include "uidemo01.h"
#include <QApplication>
#include "appinit.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <algorithm>
#include <QMetaType>

int qMain(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UIDemo01 w;


//#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
//#if _MSC_VER
//    QTextCodec *codec = QTextCodec::codecForName("gbk");
//#else
//    QTextCodec *codec = QTextCodec::codecForName("utf-8");
//#endif
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
//#else
//    QTextCodec *codec = QTextCodec::codecForName("utf-8");
//    QTextCodec::setCodecForLocale(codec);
//#endif

    //加载样式表

    QFile file(":/new/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
    w.show();

   // a.setFont(QFont("Microsoft Yahei", 9));
//    AppInit::Instance()->start();
    //QFile* file = new QFile("data/xxx11111111.txt");
    //file->close();

    return a.exec();
}
