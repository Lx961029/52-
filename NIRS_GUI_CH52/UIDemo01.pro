#-------------------------------------------------
#
# Project created by QtCreator 2019-05-25T03:00:20
#
#-------------------------------------------------

QT       += core gui
QT       += charts
QT        += concurrent
RC_ICONS = EEG.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UIDemo01
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

#DEFINES += ANALYSEC

#DEFINES += MODEBLUETOOTH
#QT       += bluetooth
QT       += serialport

INCLUDEPATH += SP++3.0\\include


if(contains(DEFINES,MODEBLUETOOTH)){

 #   LIBS += -LF:\QTPro\Andorid\NIRS_GUI_V3\SP++3.0\android_lib -lfftw3

}else {
    #INCLUDEPATH += D:\\Qt\\Qt5.10.1\\Tools\\mingw530_32\\include
    #LIBS += -LSP++3.0\win_lib -lfftw3
  #  LIBS += -LF:\QTPro\Andorid\NIRS_GUI_V3\SP++3.0\win_lib -lfftw3
}


SOURCES += \
    datasource.cpp \
    drawcharts.cpp \
    drawimage.cpp \
    main.cpp \
    uidemo01.cpp \
    appinit.cpp \
    iconhelper.cpp \
    negdry.cpp \
    paraset.cpp \
    randomwalk.cpp \
    realtimemultithread.cpp \
    sigproc.cpp \
    analyzechart.cpp \
    threadtimer.cpp \
    negdry_qt.cpp
HEADERS += \
    datasource.h \
    drawcharts.h \
    drawimage.h \
    uidemo01.h \
    appinit.h \
    bchartdir.h \
    chartdir.h \
    filter.h \
    FinanceChart.h \
    iconhelper.h \
    memblock.h \
    multithread.h \
    myhelper.h \
    negdry.h \
    paraset.h \
    qdoublebufferedqueue.h \
    qextserialport_global.h \
    randomwalk.h \
    realtimemultithread.h \
    sigproc.h \
    analyzechart.h\
    SP++3.0/include/*.h \
   # SP++3.0/include/librep.h
CONFIG += mobility \
    threadtimer.h \
    ThreadQueue.h \
    negdry_qt.h
MOBILITY =


DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    image/jjj.qrc \
    qss/as.qrc

FORMS += \
    paraset.ui \
    uidemo01.ui

