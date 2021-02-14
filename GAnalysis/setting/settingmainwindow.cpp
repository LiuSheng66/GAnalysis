#include "settingmainwindow.h"
#include "ui_settingmainwindow.h"
#include<QAction>
#include<QMessageBox>
#include<QSettings>
#include<QMessageBox>
#include<QDir>
#include<QDebug>

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
    setConfi("C://Users//Administrator//Desktop//CONFIG.ini","jieming","jianming");

    this->close();
}

void SettingMainWindow::btnCanaleFun()
{

    QMessageBox::warning(this,tr("setConfi"),tr("btnOKFun执行结束"));
    this->close();
}

void SettingMainWindow::btnApplyFun()
{
QMessageBox::warning(this,tr("setConfi"),tr("btnOKFun执行结束"));
}

//strFileAddress完整的文件地址包括文件后缀名
//设置ini文件的参数：SectionName，节名；keyName，键名；keyValue，输入的值
void SettingMainWindow::setConfi(QString strFileAddressAndName ,QString SectionName,QString keyName,QString keyValue)
{
//    QString aFile = QDir::currentPath() + "/zygapp.db";

    if(isFileExist(strFileAddressAndName))//文件存在
    {

        QSettings *settings = new QSettings(strFileAddressAndName,QSettings::IniFormat);//实例化，前面的参数是填写的配置文件的路径 ,后面的是让QSetting 用 ini的格式进行读写
        settings->setIniCodec("UTF-8");
        settings->setValue( SectionName+"/"+keyName,keyValue);//将内容写入ini文件中
        delete settings;
        emit outTextChanged("setConfi函数： 参数向文件写入 完成！");
    }
    else
    {
        emit outTextChanged("setConfi函数： 参数向文件写入 失败！");
    };
}

//注意文件名需要带后缀
QString SettingMainWindow::getConfi(QString strFileAddressAndName ,QString SectionName,QString keyName)
{
    if(isFileExist(strFileAddressAndName))
    {
        QSettings *settings = new QSettings(strFileAddressAndName,QSettings::IniFormat);//调用QSettings操作ini文件
        QString keyValue = settings->value(SectionName+"/"+keyName).toString();//按照对应的节名和键名，读出ini文件中保存的内容，默认为空
        delete settings;
        emit outTextChanged("getConfi函数： 参数从文件读取完成！");
        return keyValue;
    }
    else
    {
        emit outTextChanged("getConfi函数： 参数从文件读取 失败！");
        return NULL;
    };
}


//判断当前给定地址下的文件是否存在，是则返回true，反之false
//请输入完整的地址，注意文件名需要带后缀
bool SettingMainWindow::isFileExist(QString strFileAddress)
{
    QString driveNum = strFileAddress.at(1);//得到完整地址的第二个字符，用于判断是否是:字符，因此知道是否输入的是完整地址
    bool fileExist=false;
    if(driveNum==":")//判断地址是否是完整地址
    {
        QDir *coordinateFolder = new QDir;
        fileExist = coordinateFolder->exists(strFileAddress);//查看文件是否存在
        return fileExist;
    }
    else
    {
        emit outTextChanged(strFileAddress+"：不是完整的地址，请输入完整地址，如 \"C://Users//Administrator//Desktop//CONFIG.ini\" ");
        return fileExist;
    };
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
