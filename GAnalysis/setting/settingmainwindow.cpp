#include "settingmainwindow.h"
#include "ui_settingmainwindow.h"

SettingMainWindow::SettingMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingMainWindow)
{
    ui->setupUi(this);
    setLayout();
    ui->lineEdit_search->setPlaceholderText("Filter");//设置搜索框的提示符
}

SettingMainWindow::~SettingMainWindow()
{
    delete ui;
}


void SettingMainWindow::setLayout()
{
    //程序标题
    setWindowTitle(tr("选项-G代码解析"));
    //设置图标
    setWindowIcon(QIcon(":/image/icon/Gtitle.png"));

}
