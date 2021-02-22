#ifndef SETTINGMAINWINDOW_H
#define SETTINGMAINWINDOW_H

#include <QMainWindow>
#include<QListWidgetItem>
#include<QVBoxLayout>
#include"setting/algorithmWindow/algorithmset.h"
#include"setting/textEdit/texteditset.h"
#include"Global/global.h"
namespace Ui {
class SettingMainWindow;
}

class SettingMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingMainWindow(QWidget *parent = nullptr);
    ~SettingMainWindow();

    void setLayout();
    void CreateActions();
    void ListWidgetInit();//界面左边的listWidget

    void btnOKFun();
    void btnCanaleFun();
    void btnApplyFun();
private:
    Ui::SettingMainWindow *ui;
signals:
//    void outTextChanged(QString str);//自定义信号，输出栏内容改变信号，str代表需要显示的输出内容


public:
    void setTabMainTitle(QString str);//设置每一个功能界面的总标题

    QMainWindow* connectItemToWidget(QListWidgetItem *ItemList);//把每一个ListItem跟相应需要显示Widget绑定
    void setOtherHide();//把添加到布局中的所有Widget全部设置成Hide
public:
    QVBoxLayout *itemLayout ;//用于设置各个item的布局空间

    //选项总界面的左边ListWidget里面每个Item的指针
    QListWidgetItem *algoList;//算法
    QListWidgetItem *textEditList;//文本编辑器

    //每个具体Item的界面对象指针
    algorithmSet *algoSet;
    TextEditSet *textSet;



private slots:
    void JumpWidget(QListWidgetItem *itemIdex);//槽函数


};

#endif // SETTINGMAINWINDOW_H
