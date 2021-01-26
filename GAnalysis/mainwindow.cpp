#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSettings>
#include<QMessageBox>
#include<QToolBar>
#include<QStatusBar>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setLayout();

    //由于创建菜单栏和工具栏的时候就把动作加进去，所以这里需要先创建动作Action
    CreateActions();//创建动作Action
    CreatMenuBar();//创建菜单栏
    CreateToolbar();//创建工具栏
    CreateStatusbar();//创建状态栏


    //显示程序启动初始化完成后的状态栏信息
    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLayout()
{
    //程序标题
    setWindowTitle(tr("G代码解析"));
    //初始化窗口大小
    resize(1442,900);
    //使用样式表设置菜单栏颜色为两灰色(#D5D5D5十六进制)
    setStyleSheet("QMenuBar:item{background-color:#D5D5D5;}QMenuBar{background-color:#D5D5D5;}"
                  "QToolBar:item{background-color:#D5D5D5;}QToolBar{background-color:#D5D5D5;}"
                  "QStatusBar:item{background-color:#D5D5D5;}QStatusBar{background-color:#D5D5D5;}");

    //使用调色板设置背景颜色为深灰色(RGB(74,75,75)十进制)
    QPalette palette0=this->palette();
    palette0.setColor(QPalette::Background,QColor(74,75,75));
    this->setPalette(palette0);

}

//设置Action的图标、显示文字、 快捷键、connect槽函数
void MainWindow::CreateActions()//实例化下拉菜单功能
{
    //**************************************************************************************************//
    //*************************************    文件操作相关    *********************************************//
    const QIcon newFileActIcon =QIcon(":/image/icon/newfile.png");
    newFileAct = new QAction(newFileActIcon, QStringLiteral("新建文件(&N)"), this);
    newFileAct->setStatusTip(QStringLiteral("新建文件"));
    newFileAct->setShortcuts(QKeySequence::New);//创建快捷键
    connect(newFileAct, &QAction::triggered, this, &MainWindow::NewFile);

    const QIcon openFileActIcon =QIcon(":/image/icon/openfile.png");
    openFileAct = new QAction(openFileActIcon, QStringLiteral("打开文件(&O)"),this);//实例化readAct
    openFileAct->setStatusTip(QStringLiteral("打开文件"));//设置鼠标停留显示内容，且显示在状态栏里面，且默认显示在状态栏左侧
    openFileAct->setShortcuts(QKeySequence::Open);//打开快捷键
    connect(openFileAct, &QAction::triggered, this, &MainWindow::OpenFile);//绑定动作执行内容

    const QIcon saveFileActIcon =QIcon(":/image/icon/savefile.png");
    saveFileAct = new QAction(saveFileActIcon, QStringLiteral("保存文件(&E)"), this);
    saveFileAct->setStatusTip(QStringLiteral("保存文件"));
    saveFileAct->setShortcuts(QKeySequence::Close);//退出系统快捷键
    connect(saveFileAct, &QAction::triggered, this, &MainWindow::SaveFile);

    const QIcon saveAsFileActIcon =QIcon(":/image/icon/saveasfile.png");
    saveAsFileAct = new QAction(saveAsFileActIcon, QStringLiteral("另存为(&E)"), this);
    saveAsFileAct->setStatusTip(QStringLiteral("另存为"));
    saveAsFileAct->setShortcuts(QKeySequence::Close);//退出系统快捷键
    connect(saveAsFileAct, &QAction::triggered, this, &MainWindow::SaveAsFile);

    const QIcon closeActIcon =QIcon(":/image/icon/close.png");
    closeAct = new QAction(closeActIcon, QStringLiteral(" 关闭(&U)"), this);
    closeAct->setStatusTip(QStringLiteral("删除G代码文件并清屏"));
    openFileAct->setShortcuts(QKeySequence::Open);//打开快捷键
    connect( closeAct, &QAction::triggered, this, &MainWindow::CloseFile);

    //**************************************************************************************************//
    //*************************************    数据执行绘图相关    *********************************************//
    const QIcon BeginAnalysActIcon =QIcon(":/image/icon/beginanalysis.png");
    beginAnalysAct = new QAction(BeginAnalysActIcon, QStringLiteral("执行(&U)"), this);
    beginAnalysAct->setStatusTip(QStringLiteral("执行"));
    beginAnalysAct->setShortcuts(QKeySequence::Open);//打开快捷键
    connect(beginAnalysAct, &QAction::triggered, this, &MainWindow::BeginAnalysis);

    //**************************************************************************************************//
    //*************************************    设置相关    *********************************************//
    const QIcon settingActIcon =QIcon(":/image/icon/setting.png");
    settingAct = new QAction(settingActIcon, QStringLiteral("设置(&U)"), this);
    settingAct->setStatusTip(QStringLiteral("设置"));
    connect(settingAct, &QAction::triggered, this, &MainWindow::Setting);

    //**************************************************************************************************//
    //*************************************    系统     *********************************************//
    closeSystemAct = new QAction( QStringLiteral("退出(&X)"), this);
    closeSystemAct->setStatusTip(QStringLiteral("退出"));
    closeSystemAct->setShortcuts(QKeySequence::Close);//创建快捷键
    connect(closeSystemAct, &QAction::triggered, this, &MainWindow::CloseSystem);

    //**************************************************************************************************//
    //*************************************    帮助     *********************************************//
    aboutAct = new QAction( QStringLiteral("关于(&X)"), this);
    aboutAct->setStatusTip(QStringLiteral("关于"));
    connect(aboutAct, &QAction::triggered, this, [=](){
    TestFun();
    });

}

//实例化菜单栏
void MainWindow::CreatMenuBar()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("文件").trimmed()+tr("(&F)"));//实例化一个文件菜单栏
    EditMenu = menuBar()->addMenu(QStringLiteral("编辑").trimmed()+tr("(&E)"));//实例化一个编辑菜单栏
    analysisMenu = menuBar()->addMenu(QStringLiteral("执行").trimmed()+tr("(&D)"));//实例化一个编辑菜单栏
    HelpMenu = menuBar()->addMenu(QStringLiteral("帮助").trimmed()+tr("(&H)"));//实例化一个编辑菜单栏

    fileMenu->addAction(openFileAct);//添加动作
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(saveFileAct);
    fileMenu->addAction(saveAsFileAct);
    fileMenu->addSeparator();
    fileMenu->addAction( closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeSystemAct);

    EditMenu->addAction(settingAct);

    analysisMenu->addAction(beginAnalysAct);

    HelpMenu->addAction(aboutAct);
}

//实例化工具栏
void MainWindow::CreateToolbar()
{
    //---------------------------- 文件操作工具栏 -----------------------------------//
    fileTool = addToolBar(QStringLiteral("文件工具栏"));
    fileTool->setAllowedAreas(Qt::TopToolBarArea);//设置停靠区域
    fileTool->setFloatable(false);//设置是否能够浮动
    fileTool->setMovable(true);//设置能否移动的总开关
    //The default is Qt::ToolButtonIconOnly.
//    fileTool->setToolButtonStyle(Qt::ToolButtonFollowStyle);//设置工具栏中图标显示在文字上方
    fileTool->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//设置工具栏中图标显示在文字上方
    fileTool->setIconSize(QSize(20,20));//设置图标的大小

    fileTool->addAction(newFileAct);
    fileTool->addAction(openFileAct);//添加动作
    fileTool->addAction(saveFileAct);
    fileTool->addAction(saveAsFileAct);
    fileTool->addAction( closeAct);
//    fileTool->addSeparator();

    //---------------------------- 绘图工具栏 -----------------------------------//
    analysisTool=addToolBar("解析");
    analysisTool->setAllowedAreas(Qt::TopToolBarArea);//设置停靠区域
    analysisTool->setFloatable(false);//设置是否能够浮动
    analysisTool->setMovable(true);//设置能否移动的总开关
//    settingTool->setToolButtonStyle(Qt::ToolButtonIconOnly);//设置工具栏中图标显示在文字上方
    analysisTool->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//设置工具栏中图标显示在文字上方
    analysisTool->setIconSize(QSize(20,20));//设置图标的大小

    analysisTool->addAction(beginAnalysAct);

    //---------------------------- 设置工具栏 -----------------------------------//
    settingTool=addToolBar("设置");
    settingTool->setAllowedAreas(Qt::TopToolBarArea);//设置停靠区域
    settingTool->setFloatable(false);//设置是否能够浮动
    settingTool->setMovable(true);//设置能否移动的总开关
//    settingTool->setToolButtonStyle(Qt::ToolButtonIconOnly);//设置工具栏中图标显示在文字上方
    settingTool->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//设置工具栏中图标显示在文字上方
    settingTool->setIconSize(QSize(20,20));//设置图标的大小

    settingTool->addAction(settingAct);

}

//实例化状态栏
void MainWindow::CreateStatusbar()
{
    statusdisplay=statusBar();//实例化一个状态栏
    setStatusBar(statusdisplay);//设置到窗口中

}

void MainWindow::TestFun()
{
    QMessageBox::information(this,tr("测试函数"),tr("按钮测试成功!"));
}

void MainWindow::OpenFile()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);//调用QSettings操作ini文件
    QString lang = settings->value("jieming/jianming").toString();//按照对应的节名和键名，读出ini文件中保存的内容，默认为空
    ui->textEdit->setText(lang);//将读出的内容显示到窗口中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("读取成功!"));
}


//写入文件内容
void MainWindow::NewFile()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);
    settings->setIniCodec("UTF-8");
    settings->setValue( "jieming/jianming","我利用节名和键名，写入对应的值成功了");//将内容写入ini文件中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("写入成功!"));
}

void MainWindow::SaveFile()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("是否退出系统?"), QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {//如果选择是
        this->close();//退出系统
    }
}

void MainWindow::SaveAsFile()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("是否退出系统?"), QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {//如果选择是
        this->close();//退出系统
    }
}

void MainWindow::CloseFile()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);
    settings->setValue("jieming/jianming",ui->textEdit->toPlainText());//将当前选择的语言写入ini文件中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("更新成功!"));
}

void MainWindow::BeginAnalysis()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);
    settings->setValue("jieming/jianming",ui->textEdit->toPlainText());//将当前选择的语言写入ini文件中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("更新成功!"));
}

void MainWindow::Setting()
{
    QSettings *settings = new QSettings("./file.ini",QSettings::IniFormat);
    settings->setValue("jieming/jianming",ui->textEdit->toPlainText());//将当前选择的语言写入ini文件中
    delete settings;
    QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("更新成功!"));
}
void MainWindow::CloseSystem()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("是否退出系统?"), QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {//如果选择是
        this->close();//退出系统
    }
}
