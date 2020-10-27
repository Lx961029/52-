/********************************************************************************
** Form generated from reading UI file 'paraset.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARASET_H
#define UI_PARASET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ParaSet
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QListWidget *list;
    QLabel *buletoothState;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QPushButton *search;
    QLabel *label_4;
    QComboBox *comboBox_2;

    void setupUi(QDialog *ParaSet)
    {
        if (ParaSet->objectName().isEmpty())
            ParaSet->setObjectName(QStringLiteral("ParaSet"));
        ParaSet->resize(474, 311);
        verticalLayout_2 = new QVBoxLayout(ParaSet);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(ParaSet);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(11);
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        list = new QListWidget(groupBox);
        list->setObjectName(QStringLiteral("list"));

        gridLayout_2->addWidget(list, 4, 3, 1, 2);

        buletoothState = new QLabel(groupBox);
        buletoothState->setObjectName(QStringLiteral("buletoothState"));
        buletoothState->setStyleSheet(QStringLiteral("font: 12pt \"Arial\";"));

        gridLayout_2->addWidget(buletoothState, 4, 1, 1, 2);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 5, 3, 1, 2);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 5, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(11);
        label->setFont(font1);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 1, 1, 1, 1);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 4, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        gridLayout_2->addWidget(label_2, 0, 2, 1, 2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_2->addWidget(lineEdit_3, 1, 4, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_2->addWidget(lineEdit_4, 2, 1, 1, 1);

        search = new QPushButton(groupBox);
        search->setObjectName(QStringLiteral("search"));

        gridLayout_2->addWidget(search, 4, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);

        gridLayout_2->addWidget(label_4, 1, 2, 1, 2);

        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 3, 1, 1, 1);


        verticalLayout->addWidget(groupBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        retranslateUi(ParaSet);

        QMetaObject::connectSlotsByName(ParaSet);
    } // setupUi

    void retranslateUi(QDialog *ParaSet)
    {
        ParaSet->setWindowTitle(QApplication::translate("ParaSet", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ParaSet", "\350\277\236\346\216\245\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        label_6->setText(QApplication::translate("ParaSet", "\350\256\276\345\244\207\351\200\232\351\201\223\346\225\260\357\274\232", Q_NULLPTR));
        buletoothState->setText(QApplication::translate("ParaSet", "\350\257\267\351\200\211\346\213\251\350\223\235\347\211\231\350\256\276\345\244\207\357\274\232", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ParaSet", "\346\211\223\345\274\200", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ParaSet", "\351\200\200\345\207\272", Q_NULLPTR));
        label->setText(QApplication::translate("ParaSet", "\344\270\262\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("ParaSet", "\346\263\242\347\211\271\347\216\207\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("ParaSet", "\346\225\260\346\215\256\344\275\215\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("ParaSet", "\346\240\241\351\252\214\344\275\215\357\274\232", Q_NULLPTR));
        search->setText(QApplication::translate("ParaSet", "\346\220\234\347\264\242", Q_NULLPTR));
        label_4->setText(QApplication::translate("ParaSet", "\345\201\234\346\255\242\344\275\215\357\274\232", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("ParaSet", "1Channel", Q_NULLPTR)
         << QApplication::translate("ParaSet", "4Channel", Q_NULLPTR)
         << QApplication::translate("ParaSet", "52Channel", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class ParaSet: public Ui_ParaSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARASET_H
