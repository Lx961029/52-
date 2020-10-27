/********************************************************************************
** Form generated from reading UI file 'uidemo01.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIDEMO01_H
#define UI_UIDEMO01_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UIDemo01
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widgetTitle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labIco;
    QLabel *labTitle;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnMain;
    QToolButton *btnConfig;
    QToolButton *btnData;
    QToolButton *btnHelp;
    QToolButton *btnExit;
    QSpacerItem *horizontalSpacer;
    QWidget *widgetMenu;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *PlotArea;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_6;
    QComboBox *comboBox_2;
    QSpacerItem *verticalSpacer_5;
    QLabel *label;
    QComboBox *comboBox_3;
    QComboBox *comboBox;
    QComboBox *comboBox_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLineEdit *time_input;
    QComboBox *scale;
    QComboBox *comboBox_5;
    QPushButton *pushButton;
    QPushButton *pageButton2;
    QPushButton *pageButton3;
    QPushButton *pageButton4;
    QPushButton *pageButton1;
    QWidget *hi;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *plotA;

    void setupUi(QDialog *UIDemo01)
    {
        if (UIDemo01->objectName().isEmpty())
            UIDemo01->setObjectName(QStringLiteral("UIDemo01"));
        UIDemo01->resize(419, 570);
        UIDemo01->setSizeGripEnabled(true);
        verticalLayout = new QVBoxLayout(UIDemo01);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        widgetTitle = new QWidget(UIDemo01);
        widgetTitle->setObjectName(QStringLiteral("widgetTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetTitle->sizePolicy().hasHeightForWidth());
        widgetTitle->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(widgetTitle);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 0, 0);
        labIco = new QLabel(widgetTitle);
        labIco->setObjectName(QStringLiteral("labIco"));
        labIco->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labIco);

        labTitle = new QLabel(widgetTitle);
        labTitle->setObjectName(QStringLiteral("labTitle"));
        labTitle->setStyleSheet(QStringLiteral(""));
        labTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(labTitle);

        widgetTop = new QWidget(widgetTitle);
        widgetTop->setObjectName(QStringLiteral("widgetTop"));
        horizontalLayout_3 = new QHBoxLayout(widgetTop);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        btnMain = new QToolButton(widgetTop);
        btnMain->setObjectName(QStringLiteral("btnMain"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnMain->sizePolicy().hasHeightForWidth());
        btnMain->setSizePolicy(sizePolicy1);
        btnMain->setToolTipDuration(-5);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/start_102.82503192848px_1231086_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMain->setIcon(icon);
        btnMain->setIconSize(QSize(50, 30));
        btnMain->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnMain);

        btnConfig = new QToolButton(widgetTop);
        btnConfig->setObjectName(QStringLiteral("btnConfig"));
        sizePolicy1.setHeightForWidth(btnConfig->sizePolicy().hasHeightForWidth());
        btnConfig->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/settings_115.24904214559px_1231079_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnConfig->setIcon(icon1);
        btnConfig->setIconSize(QSize(50, 30));
        btnConfig->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnConfig);

        btnData = new QToolButton(widgetTop);
        btnData->setObjectName(QStringLiteral("btnData"));
        sizePolicy1.setHeightForWidth(btnData->sizePolicy().hasHeightForWidth());
        btnData->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/View_Width_128px_1178984_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnData->setIcon(icon2);
        btnData->setIconSize(QSize(50, 30));
        btnData->setChecked(false);
        btnData->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnData);

        btnHelp = new QToolButton(widgetTop);
        btnHelp->setObjectName(QStringLiteral("btnHelp"));
        sizePolicy1.setHeightForWidth(btnHelp->sizePolicy().hasHeightForWidth());
        btnHelp->setSizePolicy(sizePolicy1);
        btnHelp->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/params_128px_1158068_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnHelp->setIcon(icon3);
        btnHelp->setIconSize(QSize(50, 30));
        btnHelp->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnHelp);

        btnExit = new QToolButton(widgetTop);
        btnExit->setObjectName(QStringLiteral("btnExit"));
        sizePolicy1.setHeightForWidth(btnExit->sizePolicy().hasHeightForWidth());
        btnExit->setSizePolicy(sizePolicy1);
        btnExit->setStyleSheet(QStringLiteral(""));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/access_close_exit_logout_sign_out_128px_1225473_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExit->setIcon(icon4);
        btnExit->setIconSize(QSize(50, 30));
        btnExit->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_3->addWidget(btnExit);


        horizontalLayout_2->addWidget(widgetTop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        widgetMenu = new QWidget(widgetTitle);
        widgetMenu->setObjectName(QStringLiteral("widgetMenu"));
        gridLayout_2 = new QGridLayout(widgetMenu);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 2);


        horizontalLayout_2->addWidget(widgetMenu);


        verticalLayout->addWidget(widgetTitle);

        horizontalWidget = new QWidget(UIDemo01);
        horizontalWidget->setObjectName(QStringLiteral("horizontalWidget"));
        horizontalLayout_5 = new QHBoxLayout(horizontalWidget);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        PlotArea = new QWidget(horizontalWidget);
        PlotArea->setObjectName(QStringLiteral("PlotArea"));
        verticalLayout_2 = new QVBoxLayout(PlotArea);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_4 = new QGroupBox(PlotArea);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_3 = new QPushButton(groupBox_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 8, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 5, 4, 1, 1);

        comboBox_2 = new QComboBox(groupBox_4);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 3, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 7, 1, 1, 1);

        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        comboBox_3 = new QComboBox(groupBox_4);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        gridLayout->addWidget(comboBox_3, 5, 1, 1, 1);

        comboBox = new QComboBox(groupBox_4);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 6, 3, 1, 1);

        comboBox_4 = new QComboBox(groupBox_4);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        gridLayout->addWidget(comboBox_4, 5, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 5, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox_4);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 2, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 5, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 9, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 6, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 6, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_4);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 6, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        verticalLayout_2->addWidget(groupBox_4);

        groupBox_2 = new QGroupBox(PlotArea);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_5);

        time_input = new QLineEdit(groupBox_2);
        time_input->setObjectName(QStringLiteral("time_input"));

        formLayout->setWidget(8, QFormLayout::LabelRole, time_input);

        scale = new QComboBox(groupBox_2);
        scale->setObjectName(QStringLiteral("scale"));

        formLayout->setWidget(8, QFormLayout::FieldRole, scale);

        comboBox_5 = new QComboBox(groupBox_2);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));

        formLayout->setWidget(10, QFormLayout::LabelRole, comboBox_5);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(11, QFormLayout::LabelRole, pushButton);

        pageButton2 = new QPushButton(groupBox_2);
        pageButton2->setObjectName(QStringLiteral("pageButton2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pageButton2);

        pageButton3 = new QPushButton(groupBox_2);
        pageButton3->setObjectName(QStringLiteral("pageButton3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, pageButton3);

        pageButton4 = new QPushButton(groupBox_2);
        pageButton4->setObjectName(QStringLiteral("pageButton4"));

        formLayout->setWidget(3, QFormLayout::FieldRole, pageButton4);

        pageButton1 = new QPushButton(groupBox_2);
        pageButton1->setObjectName(QStringLiteral("pageButton1"));

        formLayout->setWidget(0, QFormLayout::FieldRole, pageButton1);


        verticalLayout_2->addWidget(groupBox_2);

        verticalLayout_2->setStretch(0, 1);

        horizontalLayout_5->addWidget(PlotArea);

        hi = new QWidget(horizontalWidget);
        hi->setObjectName(QStringLiteral("hi"));
        verticalLayout_3 = new QVBoxLayout(hi);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        groupBox_3 = new QGroupBox(hi);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        plotA = new QHBoxLayout();
        plotA->setObjectName(QStringLiteral("plotA"));

        horizontalLayout->addLayout(plotA);


        verticalLayout_3->addWidget(groupBox_3);

        verticalLayout_3->setStretch(0, 3);

        horizontalLayout_5->addWidget(hi);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 5);

        verticalLayout->addWidget(horizontalWidget);


        retranslateUi(UIDemo01);

        QMetaObject::connectSlotsByName(UIDemo01);
    } // setupUi

    void retranslateUi(QDialog *UIDemo01)
    {
        UIDemo01->setWindowTitle(QApplication::translate("UIDemo01", "Form", Q_NULLPTR));
        labIco->setText(QString());
        labTitle->setText(QString());
        btnMain->setText(QApplication::translate("UIDemo01", "\345\274\200\345\247\213\351\207\207\351\233\206", Q_NULLPTR));
        btnConfig->setText(QApplication::translate("UIDemo01", "\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        btnData->setText(QApplication::translate("UIDemo01", "\347\274\251\346\224\276\346\250\241\345\274\217", Q_NULLPTR));
        btnHelp->setText(QApplication::translate("UIDemo01", "\346\225\260\346\215\256\344\277\235\345\255\230", Q_NULLPTR));
        btnExit->setText(QApplication::translate("UIDemo01", "\347\224\250\346\210\267\351\200\200\345\207\272", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("UIDemo01", "Channel", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("UIDemo01", "reset", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("UIDemo01", "\347\224\267", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "\345\245\263", Q_NULLPTR)
        );
        label->setText(QApplication::translate("UIDemo01", "\345\247\223\345\220\215\357\274\232", Q_NULLPTR));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("UIDemo01", "HbO", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "HbR", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "HbT", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "ALL", Q_NULLPTR)
        );
        comboBox_4->clear();
        comboBox_4->insertItems(0, QStringList()
         << QApplication::translate("UIDemo01", "EEG1", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "EEG2", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "ALL", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("UIDemo01", "\346\200\247\345\210\253\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("UIDemo01", "\345\271\264\351\276\204\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("UIDemo01", "scale", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("UIDemo01", "Analyze", Q_NULLPTR));
        label_5->setText(QApplication::translate("UIDemo01", "Scale:", Q_NULLPTR));
        scale->clear();
        scale->insertItems(0, QStringList()
         << QApplication::translate("UIDemo01", "10mV", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "1mV", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "100uV", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "10uV", Q_NULLPTR)
        );
        comboBox_5->clear();
        comboBox_5->insertItems(0, QStringList()
         << QApplication::translate("UIDemo01", "fft", Q_NULLPTR)
         << QApplication::translate("UIDemo01", "welch", Q_NULLPTR)
        );
        pushButton->setText(QApplication::translate("UIDemo01", "OK", Q_NULLPTR));
        pageButton2->setText(QApplication::translate("UIDemo01", "page2", Q_NULLPTR));
        pageButton3->setText(QApplication::translate("UIDemo01", "page3", Q_NULLPTR));
        pageButton4->setText(QApplication::translate("UIDemo01", "page4", Q_NULLPTR));
        pageButton1->setText(QApplication::translate("UIDemo01", "page1", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("UIDemo01", "Display", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UIDemo01: public Ui_UIDemo01 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIDEMO01_H
