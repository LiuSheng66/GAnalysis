/********************************************************************************
** Form generated from reading UI file 'algorithmset.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMSET_H
#define UI_ALGORITHMSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_algorithmSet
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton;
    QWidget *tab_2;
    QPushButton *pushButton_2;
    QWidget *tab_3;
    QPushButton *pushButton_3;

    void setupUi(QMainWindow *algorithmSet)
    {
        if (algorithmSet->objectName().isEmpty())
            algorithmSet->setObjectName(QString::fromUtf8("algorithmSet"));
        algorithmSet->resize(860, 500);
        algorithmSet->setMinimumSize(QSize(860, 500));
        algorithmSet->setMaximumSize(QSize(860, 500));
        centralwidget = new QWidget(algorithmSet);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 861, 501));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 841, 461));
        QFont font;
        font.setPointSize(11);
        groupBox->setFont(font);
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 30, 194, 83));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(verticalLayoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setFont(font);

        verticalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(verticalLayoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 30, 75, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 190, 75, 23));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(490, 170, 75, 23));
        tabWidget->addTab(tab_3, QString());
        algorithmSet->setCentralWidget(centralwidget);

        retranslateUi(algorithmSet);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(algorithmSet);
    } // setupUi

    void retranslateUi(QMainWindow *algorithmSet)
    {
        algorithmSet->setWindowTitle(QCoreApplication::translate("algorithmSet", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("algorithmSet", " \350\277\236\347\273\255\345\210\207\345\211\262\346\250\241\345\274\217", nullptr));
        radioButton->setText(QCoreApplication::translate("algorithmSet", "\351\200\220\347\202\271\346\257\224\350\276\203\346\263\225", nullptr));
        radioButton_2->setText(QCoreApplication::translate("algorithmSet", "DDA\357\274\210\346\225\260\345\255\227\347\247\257\345\210\206\346\263\225\357\274\211", nullptr));
        pushButton->setText(QCoreApplication::translate("algorithmSet", "\351\207\215\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("algorithmSet", "\350\277\236\347\273\255\345\210\207\345\211\262\346\250\241\345\274\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("algorithmSet", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("algorithmSet", "Tab 2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("algorithmSet", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("algorithmSet", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class algorithmSet: public Ui_algorithmSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMSET_H
