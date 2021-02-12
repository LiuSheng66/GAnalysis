/********************************************************************************
** Form generated from reading UI file 'texteditset.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTEDITSET_H
#define UI_TEXTEDITSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextEditSet
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QSplitter *splitter_2;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QSplitter *splitter_3;
    QLabel *label_3;
    QSpinBox *spinBox;
    QSplitter *splitter;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *tab_2;
    QPushButton *pushButton_2;
    QWidget *tab_3;
    QPushButton *pushButton_3;

    void setupUi(QMainWindow *TextEditSet)
    {
        if (TextEditSet->objectName().isEmpty())
            TextEditSet->setObjectName(QString::fromUtf8("TextEditSet"));
        TextEditSet->resize(860, 502);
        centralwidget = new QWidget(TextEditSet);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 861, 501));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 841, 61));
        QFont font;
        font.setPointSize(11);
        groupBox->setFont(font);
        splitter_2 = new QSplitter(groupBox);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(300, 20, 101, 21));
        splitter_2->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(splitter_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        splitter_2->addWidget(label_2);
        comboBox_2 = new QComboBox(splitter_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(40, 0));
        comboBox_2->setMaximumSize(QSize(40, 16777215));
        splitter_2->addWidget(comboBox_2);
        splitter_3 = new QSplitter(groupBox);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(500, 20, 111, 20));
        splitter_3->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        splitter_3->addWidget(label_3);
        spinBox = new QSpinBox(splitter_3);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(50, 20));
        spinBox->setMaximumSize(QSize(50, 20));
        splitter_3->addWidget(spinBox);
        splitter = new QSplitter(groupBox);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(20, 20, 171, 21));
        splitter->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter);
        label->setObjectName(QString::fromUtf8("label"));
        splitter->addWidget(label);
        comboBox = new QComboBox(splitter);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(100, 0));
        comboBox->setMaximumSize(QSize(16777215, 100));
        splitter->addWidget(comboBox);
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
        TextEditSet->setCentralWidget(centralwidget);

        retranslateUi(TextEditSet);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TextEditSet);
    } // setupUi

    void retranslateUi(QMainWindow *TextEditSet)
    {
        TextEditSet->setWindowTitle(QCoreApplication::translate("TextEditSet", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("TextEditSet", "\345\255\227\344\275\223", nullptr));
        label_2->setText(QCoreApplication::translate("TextEditSet", " \345\255\227\345\217\267\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("TextEditSet", " \347\274\251\346\224\276\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("TextEditSet", " \345\255\227\345\236\213\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("TextEditSet", "\345\255\227\344\275\223\345\222\214\351\242\234\350\211\262", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TextEditSet", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("TextEditSet", "Tab 2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("TextEditSet", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("TextEditSet", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextEditSet: public Ui_TextEditSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTEDITSET_H
