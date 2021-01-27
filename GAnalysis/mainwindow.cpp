#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSettings>
#include<QMessageBox>
#include<QToolBar>
#include<QStatusBar>
#include<QDockWidget>
#include<QSizePolicy>
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
    //设置图标
    setWindowIcon(QIcon(":/image/icon/Gtitle.png"));
    //初始化窗口大小
    resize(1400,900);
    //使用样式表设置菜单栏颜色为两灰色(#D5D5D5十六进制)
    setStyleSheet("QMenuBar:item{background-color:#D5D5D5;}QMenuBar{background-color:#D5D5D5;}"
                  "QToolBar:item{background-color:#D5D5D5;}QToolBar{background-color:#D5D5D5;}"
                  "QStatusBar:item{background-color:#D5D5D5;}QStatusBar{background-color:#D5D5D5;}");

    //使用调色板设置背景颜色为深灰色(RGB(74,75,75)十进制)
    QPalette MainBlackgroundpal=this->palette();
    MainBlackgroundpal.setColor(QPalette::Background,QColor(255,255,255));
    this->setPalette(MainBlackgroundpal);

    //删除中央窗体,QMainWindow中自带中央窗体，如果不去除的话，可能会造成窗口间有空块的情况
    QWidget* p = takeCentralWidget();
    if (p){
        delete p;
    }


    //定义QDockWidgetd的背景色
    QPalette dockWidgetPal=this->palette();
    dockWidgetPal.setColor(QPalette::Background, Qt::green);
//    允许嵌套dock
    setDockNestingEnabled(true);
    workSpaceDockWidget = new QDockWidget(tr("工作区"), this);
    addDockWidget(Qt::LeftDockWidgetArea,workSpaceDockWidget);
    workSpaceDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
    workSpaceDockWidget ->setMinimumWidth(200);
//    workSpaceDockWidget ->setMinimumSize(200, this->height());
    workSpaceDockWidget->setAutoFillBackground(true);//加这句，下面设置颜色时，可以设置标题和控件主体的颜色，否则只能设置标题栏的颜色
    workSpaceDockWidget->setPalette(dockWidgetPal);

    gDisplayDockWidget = new QDockWidget(tr("G代码显示"), this);
    tabifyDockWidget(workSpaceDockWidget, gDisplayDockWidget);
    gDisplayDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
//    gDisplayDockWidget ->setMinimumSize(200, this->height());
    gDisplayDockWidget ->setMinimumWidth(200);

    PropertyDockWidget = new QDockWidget(tr("属性"), this);
    addDockWidget(Qt::RightDockWidgetArea,PropertyDockWidget);
    PropertyDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
//    PropertyDockWidget ->setMinimumSize(150, this->height());
    PropertyDockWidget ->setMinimumWidth(150);

    outPutdockWidget = new QDockWidget(tr("输出"), this);
    addDockWidget(Qt::BottomDockWidgetArea,outPutdockWidget);
    outPutdockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
    outPutdockWidget ->setMinimumSize(this->width()-workSpaceDockWidget->width()-PropertyDockWidget->width(),150 );

//    splitDockWidget(dockWidget_1,dockWidget_2,Qt::Horizontal);

    area=new PaintArea(this->width(),this->height());//创建画布
    scrollArea=new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);//scrollArea对象的背景色设置为Dark
    scrollArea->setWidget(area) ;//将画布添加到scrollArea中
    scrollArea->setGeometry(0,0,this->width(),this->height());//scrollArea的布局(左上角定位x,左上角定位y, 外框宽度，外框高度)
    scrollArea->widget()->setGeometry(0,0,this->width(),this->height());//用于填充绘画对象的空间大小
    scrollArea->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
//    scrollArea->widget()->setMinimumSize(area->image.width(),area->image.height());//根据画布的大小初始化scrollArea的内部空间
//    Flickable {
//        contentHeight: 2000
//        scrollArea.vertical: ScrollBar {
//            policy: ScrollBar.AlwaysOn
//        }
//    }

    setCentralWidget(scrollArea);

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

    const QIcon PauseAnalysActIcon =QIcon(":/image/icon/pauseAnalysis.png");
    pauseAnalysAct = new QAction(PauseAnalysActIcon, QStringLiteral("暂停(&U)"), this);
    pauseAnalysAct->setStatusTip(QStringLiteral("暂停"));
    connect(pauseAnalysAct, &QAction::triggered, this, &MainWindow::BeginAnalysis);

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
    analysisTool->addAction(pauseAnalysAct);


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


// 移除并隐藏所有的dock
void MainWindow::removeAllDock()
{
    for(int i=0;i<1;++i)
    {
        removeDockWidget(m_docks[i]);
    }
}

// 显示指定序号的dock
// index 指定序号，如果不指定，则会显示所有
void MainWindow::showDock(const QList<int>& index )
{
    if (index.isEmpty())
    {
        for(int i=0;i<1;++i)
        {
            m_docks[i]->show();
        }
    }
    else
    {
        foreach (int i, index) {
            m_docks[i]->show();
        }
    }
}

void MainWindow::TestFun()
{
    QMessageBox::information(this,tr("测试函数"),tr("按钮测试成功!"));
}

void MainWindow::OpenFile()
{

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

}

void MainWindow::BeginAnalysis()
{

}

void MainWindow::Setting()
{

}
void MainWindow::CloseSystem()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("是否退出系统?"), QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {//如果选择是
        this->close();//退出系统
    }
}
