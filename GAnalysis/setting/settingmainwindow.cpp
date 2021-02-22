#include "settingmainwindow.h"
#include "ui_settingmainwindow.h"
#include<QAction>
#include<QMessageBox>
#include<QSettings>
#include<QMessageBox>
#include<QDir>
#include<QDebug>
#include"Global/global.h"

SettingMainWindow::SettingMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingMainWindow)
    ,itemLayout (new QVBoxLayout)
    ,algoSet(new algorithmSet)
    ,textSet(new TextEditSet)

{
    ui->setupUi(this);
    setLayout(); 
    ListWidgetInit();
    CreateActions();
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

    ui->lineEdit_search->setPlaceholderText("Filter");//设置搜索框的提示符

    //添加的第一个是初始显示画面，这个每新建一个功能界面需要新添加到Layout中
    itemLayout->addWidget(algoSet);
    itemLayout->addWidget(textSet);
    setTabMainTitle("算法");
    ui->saveForWidget->setLayout(itemLayout);
    ui->saveForWidget->show();

}


void SettingMainWindow::CreateActions()
{
    connect(ui->pushButton_OK, &QPushButton::clicked, this, &SettingMainWindow::btnOKFun);
    connect(ui->pushButton_Cancle, &QPushButton::clicked, this, &SettingMainWindow::btnCanaleFun);
    connect(ui->pushButton_Apply, &QPushButton::clicked, this, &SettingMainWindow::btnApplyFun);

    QObject::connect(ui->listWidgetItem,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(JumpWidget(QListWidgetItem*)));
}

//初始化ListWidget的Item
void SettingMainWindow::ListWidgetInit()
{

    ui->listWidgetItem->setMovement(QListView::Static);//设置单元项不可拖动，（Static、Free、Snap）
    ui->listWidgetItem->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//设置垂直滚动条显示方式（ScrollBarAsNeeded：按需显示，ScrollBarAlwaysOff：隐藏，ScrollBarAlwaysOn：常显）

    algoList = new QListWidgetItem(ui->listWidgetItem);
    algoList->setIcon(QIcon(":/image/SettingList/algorithm.png"));
    algoList->setText(tr("算法"));
    algoList->setTextAlignment(Qt::AlignLeft);
    algoList->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    textEditList = new QListWidgetItem(ui->listWidgetItem);
    textEditList->setIcon(QIcon(":/image/SettingList/textEdit.png"));
    textEditList->setText(tr("文本编辑器"));
    textEditList->setTextAlignment(Qt::AlignLeft);
    textEditList->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void SettingMainWindow::btnOKFun()
{
    setConfi("jieming","jianming");

    this->close();
}

void SettingMainWindow::btnCanaleFun()
{
//    QMessageBox::warning(this,tr("setConfi"),tr("btnOKFun执行结束"));

    this->close();
}

void SettingMainWindow::btnApplyFun()
{
QMessageBox::warning(this,tr("setConfi"),tr("btnOKFun执行结束"));
}

void SettingMainWindow::setTabMainTitle(QString str)
{
    ui->tabMainTopTitle->setMargin(30);//设置边距
    ui->tabMainTopTitle->clear();
    ui->tabMainTopTitle->setText(str);
}


void SettingMainWindow::JumpWidget(QListWidgetItem *itemIdex)
{
    setTabMainTitle(itemIdex->text());//设置跳转功能界面的总标题
    if(itemIdex==algoList)
    {
       setOtherHide();
       connectItemToWidget(itemIdex)->show();
    };
    if(itemIdex==textEditList)
    {
        setOtherHide();
        connectItemToWidget(itemIdex)->show();
    };

}

QMainWindow *SettingMainWindow::connectItemToWidget(QListWidgetItem *ItemList)
{
    if(ItemList==algoList)
    {
        return algoSet;
    };
    if(ItemList==textEditList)
    {
        return textSet;
    };

}

//每添加一个新的功能界面，都需要在这里添加hide步骤
void SettingMainWindow::setOtherHide()
{
    algoSet->hide();
    textSet->hide();
}
