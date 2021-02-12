/********************************************************************************
** Form generated from reading UI file 'settingmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGMAINWINDOW_H
#define UI_SETTINGMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingMainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancle;
    QPushButton *pushButton_Apply;
    QSplitter *splitter_4;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QLineEdit *lineEdit_search;
    QListWidget *listWidgetItem;
    QSplitter *splitter_3;
    QLabel *tabMainTitle;
    QWidget *saveForWidget;

    void setupUi(QMainWindow *SettingMainWindow)
    {
        if (SettingMainWindow->objectName().isEmpty())
            SettingMainWindow->setObjectName(QString::fromUtf8("SettingMainWindow"));
        SettingMainWindow->resize(1050, 610);
        SettingMainWindow->setMinimumSize(QSize(1050, 610));
        SettingMainWindow->setMaximumSize(QSize(1050, 610));
        centralwidget = new QWidget(SettingMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 570, 1021, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButton_OK = new QPushButton(horizontalLayoutWidget);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));

        horizontalLayout_5->addWidget(pushButton_OK);

        pushButton_Cancle = new QPushButton(horizontalLayoutWidget);
        pushButton_Cancle->setObjectName(QString::fromUtf8("pushButton_Cancle"));

        horizontalLayout_5->addWidget(pushButton_Cancle);

        pushButton_Apply = new QPushButton(horizontalLayoutWidget);
        pushButton_Apply->setObjectName(QString::fromUtf8("pushButton_Apply"));

        horizontalLayout_5->addWidget(pushButton_Apply);

        splitter_4 = new QSplitter(centralwidget);
        splitter_4->setObjectName(QString::fromUtf8("splitter_4"));
        splitter_4->setGeometry(QRect(10, 30, 1031, 531));
        splitter_4->setOrientation(Qt::Horizontal);
        splitter_2 = new QSplitter(splitter_4);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        lineEdit_search = new QLineEdit(splitter);
        lineEdit_search->setObjectName(QString::fromUtf8("lineEdit_search"));
        lineEdit_search->setMinimumSize(QSize(130, 25));
        lineEdit_search->setMaximumSize(QSize(130, 25));
        splitter->addWidget(lineEdit_search);
        listWidgetItem = new QListWidget(splitter);
        listWidgetItem->setObjectName(QString::fromUtf8("listWidgetItem"));
        listWidgetItem->setMinimumSize(QSize(130, 0));
        listWidgetItem->setMaximumSize(QSize(130, 16777215));
        splitter->addWidget(listWidgetItem);
        splitter_2->addWidget(splitter);
        splitter_4->addWidget(splitter_2);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        tabMainTitle = new QLabel(splitter_3);
        tabMainTitle->setObjectName(QString::fromUtf8("tabMainTitle"));
        tabMainTitle->setMinimumSize(QSize(0, 25));
        tabMainTitle->setMaximumSize(QSize(16777215, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\344\273\277\345\256\213"));
        font.setPointSize(17);
        font.setBold(true);
        font.setWeight(75);
        tabMainTitle->setFont(font);
        tabMainTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tabMainTitle->setMargin(2);
        splitter_3->addWidget(tabMainTitle);
        saveForWidget = new QWidget(splitter_3);
        saveForWidget->setObjectName(QString::fromUtf8("saveForWidget"));
        saveForWidget->setMinimumSize(QSize(0, 0));
        splitter_3->addWidget(saveForWidget);
        splitter_4->addWidget(splitter_3);
        SettingMainWindow->setCentralWidget(centralwidget);

        retranslateUi(SettingMainWindow);

        QMetaObject::connectSlotsByName(SettingMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SettingMainWindow)
    {
        SettingMainWindow->setWindowTitle(QCoreApplication::translate("SettingMainWindow", "MainWindow", nullptr));
        pushButton_OK->setText(QCoreApplication::translate("SettingMainWindow", "OK", nullptr));
        pushButton_Cancle->setText(QCoreApplication::translate("SettingMainWindow", "Cancle", nullptr));
        pushButton_Apply->setText(QCoreApplication::translate("SettingMainWindow", "Apply", nullptr));
        tabMainTitle->setText(QCoreApplication::translate("SettingMainWindow", "\347\256\227\346\263\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingMainWindow: public Ui_SettingMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGMAINWINDOW_H
