#ifndef SETTINGMAINWINDOW_H
#define SETTINGMAINWINDOW_H

#include <QMainWindow>
#include<QListWidgetItem>
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
    void outTextChanged(QString str);//自定义信号，输出栏内容改变信号，str代表需要显示的输出内容


public:
    void setConfi(QString strFileAddressAndName ,QString SectionName,QString keyName,QString keyValue="0");//设置ini文件的参数
    QString getConfi(QString strFileAddressAndName ,QString SectionName,QString keyName);
    bool isFileExist(QString strFileAddress);

    void setTabMainTitle(QString str);

public:
    //选项总界面的左边ListWidget里面每个Item的指针
    QListWidgetItem *algoList;//算法
    QListWidgetItem *textEditList;//文本编辑器
};

#endif // SETTINGMAINWINDOW_H
