#include"mainwindow.h"
#include"ui_mainwindow.h"
#include<QSettings>
#include<QMessageBox>
#include<QToolBar>
#include<QStatusBar>
#include<QDockWidget>
#include<QSizePolicy>
#include<QDebug>
#include<QFileDialog>
#include<QTextCodec>
#include<QColorDialog>
#include<QDateTime>
#include<QPainter>
#include<syntax/myhighlighter.h>
#include<syntax/codeeditor.h>
#include<Command/mycommand.h>
#include"setting/settingmainwindow.h"
#include"Algorithm/ptpcm/straightlineptpcm.h"
#include"Algorithm/ptpcm/circulararcptpcm.h"
#include"Global/global.h"
#include<QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,textEditGCode(new QTextEdit)
    ,textDisplayGCode(new QTextEdit)
    ,gEditWidget(new CodeEditor)

{
    ui->setupUi(this);

    setLayout();
    //由于创建菜单栏和工具栏的时候就把动作加进去，所以这里需要先创建动作Action
    CreateActions();//创建动作Action
    CreatMenuBar();//创建菜单栏
    CreateToolbar();//创建工具栏
    CreateStatusbar();//创建状态栏

    statusBar()->showMessage(tr("就绪"));
    centralWidget()->setMouseTracking(true);//开启鼠标跟踪事件
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{

}

void MainWindow:: mouseMovePoint()
{ //鼠标移动响应
    QPointF pt=QPointF(area->x(),area->y());
    xyLabel->setText(QString::asprintf("X=%.1f,Y=%.2f",pt.x(),pt.y())); //状态栏显示
}





void MainWindow::setLayout()
{
    //程序标题
    setWindowTitle(tr("G代码解析"));
    //设置图标
    setWindowIcon(QIcon(":/image/icon/Gtitle.png"));
    //初始化窗口大小
    resize(1200,900);
    //使用样式表设置菜单栏颜色为两灰色(#D5D5D5十六进制)
    setStyleSheet("QMenuBar:item{background-color:#D5D5D5;}QMenuBar{background-color:#D5D5D5;}"
                  "QToolBar:item{background-color:#D5D5D5;}QToolBar{background-color:#D5D5D5;}"
                  "QStatusBar:item{background-color:#D5D5D5;}QStatusBar{background-color:#D5D5D5;}");

    //使用调色板设置背景颜色为深灰色(RGB(74,75,75)十进制)
    QPalette MainBackgroundpal=this->palette();
    MainBackgroundpal.setColor(QPalette::Background,QColor(255,255,255));
    this->setPalette(MainBackgroundpal);

    //删除中央窗体,QMainWindow中自带中央窗体，如果不去除的话，可能会造成窗口间有空块的情况
    QWidget* p = takeCentralWidget();
    if (p){
        delete p;
    }

//    //设置工作区背景色
    QPalette *workSpacePal=new QPalette;
    workSpacePal->setColor(QPalette::Window,QColor(190,190,190));


//    允许嵌套dock
    setDockNestingEnabled(true);
    workSpaceDockWidget = new QDockWidget(tr("工作区"), this);
    addDockWidget(Qt::LeftDockWidgetArea,workSpaceDockWidget);
    workSpaceDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置都可以
    workSpaceDockWidget ->setMinimumWidth(200);
    workSpaceDockWidget->setAutoFillBackground(true);
    workSpaceDockWidget->setPalette(*workSpacePal);

    //*****************************************************
    gEditWidget = new CodeEditor();
    gEditWidget->setReadOnly(true);
    QFont *gEditFont=new QFont( "Times New Roman", 13);
    gEditWidget->setFont(*gEditFont);
    MyHighLighter *highlighter = new MyHighLighter(gEditWidget->document());
    workSpaceDockWidget->setWidget(gEditWidget);
    //*****************************************************


//    workSpaceDockWidget->setWidget(textEditGCode);
//    textEditGCode->setReadOnly(true);

//    textEditGCode->setStyleSheet("QTextEdit { background: rgb(190,190,190) }");

    gDisplayDockWidget = new QDockWidget(tr("G代码显示"), this);
    tabifyDockWidget(workSpaceDockWidget, gDisplayDockWidget);
    // raise()函数可使指定窗口置于最前
    workSpaceDockWidget->raise();//可设置那个显示在最前面
    gDisplayDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
//    gDisplayDockWidget ->setMinimumSize(200, this->height());
    gDisplayDockWidget ->setMinimumWidth(200);
    gDisplayDockWidget->setWidget(textDisplayGCode);
    textDisplayGCode->setReadOnly(true);

    PropertyDockWidget = new QDockWidget(tr("属性"), this);
    addDockWidget(Qt::RightDockWidgetArea,PropertyDockWidget);
    PropertyDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
//    PropertyDockWidget ->setMinimumSize(150, this->height());
    PropertyDockWidget ->setMinimumWidth(150);

    outPutdockWidget = new QDockWidget(tr("输出"), this);
    addDockWidget(Qt::BottomDockWidgetArea,outPutdockWidget);
    outPutdockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
    outPutdockWidget ->setMinimumSize(this->width()-workSpaceDockWidget->width()-PropertyDockWidget->width(),150 );
    exportMessage=new QTextEdit(this);//消息全局对象
    QFont *exportMessageFont=new QFont( "宋体", 11);
    exportMessage->setFont(*exportMessageFont);
    outPutdockWidget->setWidget(exportMessage);



//    splitDockWidget(dockWidget_1,dockWidget_2,Qt::Horizontal);

    area=new PaintArea(100,100);//按照当前的窗口大小初始化创建多大的画布
    scrollArea=new QScrollArea(this);//对scrollArea实例化分配空间

    //如果把画布的存放空间跟画布大小一致，那么画布的大小设置跟画布空间大小不一致就看不出来了
    //使用调色板设置背景颜色为深灰色(RGB(74,75,75)十进制)
    QPalette scrollAreaBackgroundpal=this->palette();
    scrollAreaBackgroundpal.setColor(QPalette::Background,QColor(0,255,255));
    scrollArea->setPalette(scrollAreaBackgroundpal);
//    scrollArea->setBackgroundRole(QPalette::Dark);//scrollArea对象的背景色设置为Dark


    scrollArea->setWidget(area) ;//将画布添加到scrollArea中
    scrollArea->setGeometry(0,0,this->width(),this->height());//scrollArea的布局(左上角定位x,左上角定位y, 外框宽度，外框高度)
    scrollArea->widget()->setGeometry(0,0,this->width(),this->height());//用于填充绘画对象的空间大小
    QPalette scrollAreaWidgetBackgroundpal=this->palette();
    scrollAreaWidgetBackgroundpal.setColor(QPalette::Background,QColor(0,255,0));
    scrollArea->widget()->setPalette(scrollAreaWidgetBackgroundpal);
    scrollArea->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    scrollArea->widget()->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
//    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏横向滚动条
//    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏竖向滚动条
//    scrollArea->widget()->setMinimumSize(area->image.width(),area->image.height());//根据画布的大小初始化scrollArea的内部空间
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
    analysisAndDawAct = new QAction(BeginAnalysActIcon, QStringLiteral("执行(&U)"), this);
    analysisAndDawAct->setStatusTip(QStringLiteral("执行"));
    analysisAndDawAct->setShortcuts(QKeySequence::Open);//打开快捷键
    connect(analysisAndDawAct, &QAction::triggered, this, &MainWindow::beginAnalysis);

    const QIcon AnalysActIcon =QIcon(":/image/icon/analysis.png");
    analysisAct = new QAction(AnalysActIcon, QStringLiteral("解析(&U)"), this);
    analysisAct->setStatusTip(QStringLiteral("解析"));
    analysisAct->setShortcuts(QKeySequence::Open);//打开快捷键
    connect(analysisAct, &QAction::triggered, this, &MainWindow::onlyAnalysis);


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
    connect(closeSystemAct, &QAction::triggered, this, &MainWindow::ExitSystem);

    //**************************************************************************************************//
    //*************************************    帮助     *********************************************//
    aboutAct = new QAction( QStringLiteral("关于(&X)"), this);
    aboutAct->setStatusTip(QStringLiteral("关于"));
    connect(aboutAct, &QAction::triggered, this, [=](){
     QMessageBox::about(this, "关于","G代码解析 V1.0\n\n"
                                   "本软件基于G代码解析开发，使用时请参开一下说明\n"
                                   "使用时，需要注意一下问题：\n"
                                   "  1.精度为6位有效数字 ");
    });

    //**************************************************************************************************//
    //*************************************    状态栏     *********************************************//
//    void(PaintArea:: *qw)(QPoint)=&PaintArea::mouseMoveSig;


//    connect(area,qw,this,&MainWindow::mouseMovePoint);  //鼠标移动事件
//SIGNAL(mouseMovePoint(QPoint)) SLOT(mouseMovePoint)

}

//实例化菜单栏
void MainWindow::CreatMenuBar()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("文件").trimmed()+tr("(&F)"));//实例化一个文件菜单栏
    editMenu = menuBar()->addMenu(QStringLiteral("编辑").trimmed()+tr("(&E)"));//实例化一个编辑菜单栏
    viewMenu = menuBar()->addMenu(QStringLiteral("视图").trimmed()+tr("(&V)"));//实例化一个视图菜单栏
    analysisMenu = menuBar()->addMenu(QStringLiteral("RUN").trimmed()+tr("(&D)"));//实例化一个编辑菜单栏
    toolMenu= menuBar()->addMenu(QStringLiteral("工具").trimmed()+tr("(&T)"));//实例化一个编辑菜单栏
    HelpMenu = menuBar()->addMenu(QStringLiteral("帮助").trimmed()+tr("(&H)"));//实例化一个编辑菜单栏

    fileMenu->addAction(openFileAct);//添加动作
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(saveFileAct);
    fileMenu->addAction(saveAsFileAct);
    fileMenu->addSeparator();
    fileMenu->addAction( closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeSystemAct);

    editMenu->addAction(settingAct);

    analysisMenu->addAction(analysisAndDawAct);
    analysisMenu->addAction(analysisAct);

    toolMenu->addAction(settingAct);

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
    fileTool->setToolButtonStyle(Qt::ToolButtonIconOnly);//设置工具栏中图标显示在文字上方
    fileTool->setIconSize(QSize(20,20));//设置图标的大小

    fileTool->addAction(newFileAct);
    fileTool->addAction(openFileAct);//添加动作
    fileTool->addAction(saveFileAct);
    fileTool->addAction(saveAsFileAct);
    fileTool->addAction( closeAct);
//    fileTool->addSeparator();
//
    //---------------------------- 绘图工具栏 -----------------------------------//
    ProcessTool=addToolBar("解析");
    ProcessTool->setAllowedAreas(Qt::TopToolBarArea);//设置停靠区域
    ProcessTool->setFloatable(false);//设置是否能够浮动
    ProcessTool->setMovable(true);//设置能否移动的总开关
//    settingTool->setToolButtonStyle(Qt::ToolButtonIconOnly);//设置工具栏中图标显示在文字上方
    ProcessTool->setToolButtonStyle(Qt::ToolButtonIconOnly);//设置工具栏中图标显示在文字上方
    ProcessTool->setIconSize(QSize(20,20));//设置图标的大小

    ProcessTool->addAction(analysisAndDawAct);
    ProcessTool->addAction(analysisAct);
    //---------------------------- 设置工具栏 -----------------------------------//
    settingTool=addToolBar("设置");
    settingTool->setAllowedAreas(Qt::TopToolBarArea);//设置停靠区域
    settingTool->setFloatable(false);//设置是否能够浮动
    settingTool->setMovable(true);//设置能否移动的总开关
//    settingTool->setToolButtonStyle(Qt::ToolButtonIconOnly);//设置工具栏中图标显示在文字上方
    settingTool->setToolButtonStyle(Qt::ToolButtonIconOnly);//设置工具栏中图标显示在文字上方
    settingTool->setIconSize(QSize(20,20));//设置图标的大小

    settingTool->addAction(settingAct);

}

//实例化状态栏
void MainWindow::CreateStatusbar()
{
    QFont font("Microsoft YaHei", 10);//设置显示文字的字体和文字大小

    statusdisplay=statusBar();//实例化一个状态栏
    setStatusBar(statusdisplay);//设置到窗口中

    // 设置高度
    statusBar()->setMinimumHeight(25);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 1px}")); // 不显示边框

    currentWorkFileNameAndFath = new QLabel();
    currentWorkFileNameAndFath->setFont(font);
    currentWorkFileNameAndFath->setText(workFileNameAndFath);
    currentWorkFileNameAndFath->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar()->addWidget(currentWorkFileNameAndFath);

    xyLabel = new QLabel("X=  ,  Y=  "); //状态栏显示鼠标点的坐标
    xyLabel->setMinimumWidth(20);
    xyLabel->setFont(font);
    statusBar()->addPermanentWidget(xyLabel);


    outputStatusLabel = new QLabel();
    outputStatusLabel->setFrameStyle(QFrame::WinPanel | QFrame::Raised);



    // 添加提示信息标签
//    outputStatusLabel->setMinimumWidth(this->width() / 2);
    outputStatusLabel->setFont(font);
    outputStatusLabel->setText("状态栏标签");
    outputStatusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar()->addPermanentWidget(outputStatusLabel);
//    statusBar()->addWidget(outputStatusLabel);

    outBtn=new QPushButton(this);
    outBtn->setText("1 输出");
    outBtn->setFont(font);
    outBtn->setFlat(true);//就是这句实现按钮透明的效果。
    statusBar()->addPermanentWidget(outBtn);

    //点击按钮显示或
    connect(outBtn, &QPushButton::clicked, this,[=](){
        ConvertShowOrHide(outPutdockWidget);
    });

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
    QString filename=QFileDialog::getOpenFileName(this,"打开文件","C://Users//Administrator//Desktop");
    if(filename=="") return;//如果没有点击文件打开，就返回空的文件名
    //编码格式类,默认UTF-8
//    QTextCodec *codec=QTextCodec::codecForName("UTF-8");

    //读取内容
    if(filename.right(3)=="txt"||filename.right(3)=="cnc"||filename.right(3)=="CNC"||filename.right(3)=="TXT")
    {
       QFile file(filename);
       if(file.open(QIODevice::ReadOnly))
      {
           workFileNameAndFath=file.fileName();
           QTextStream stream(&file);
           stream.setCodec("UTF-8");//设置编码,默认UTF-8
           QString buf = stream.readAll();
           gEditWidget->setPlainText(buf);
       }
       else
       {
           OutPutMsgToConsle(Critical_INFO,"打开文件失败!! 请尝试重新打开");
       };
       file.close();
       //显示工作文件的路径
       QFont font("Microsoft YaHei", 10);//设置显示文字的字体和文字大小
       currentWorkFileNameAndFath->setText(filename);
    }
    else{
        OutPutMsgToConsle(Warning_INFO,"不支持该格式的文件");};

    gEditWidget->setReadOnly(false);
    QFont *gEditFont=new QFont( "Times New Roman", 13);//设置字体及大小
    gEditWidget->setFont(*gEditFont);
    MyHighLighter *highlighter = new MyHighLighter(gEditWidget->document());

//    file.close();

    //设置文字颜色
    QPalette TextColorPal=this->palette();
    TextColorPal.setColor(QPalette::Text,QColor(0,0,0));// 黑色，文字显示的前景色
    TextColorPal.setColor(QPalette::Base,QColor(255,255,255));//白色 文字显示的背景色, 默认是白色的
    TextColorPal.setColor(QPalette::HighlightedText,QColor(255,255,255));//白色 被选中后文字的前景色
    TextColorPal.setColor(QPalette::Highlight,QColor(0,0,0)); //黑色 被选中后文字的背景色
    textEditGCode->setPalette(TextColorPal);

//    GCommand *sdf=new GCommand(*gEditWidget);

}


//创建新的编辑文件
void MainWindow::NewFile()
{
    /*
    textEditGCode->clear();
    textDisplayGCode->clear();
    textEditGCode->setReadOnly(false);
    textDisplayGCode->setReadOnly(true);
    QPalette *textEditGCodePal=new QPalette;
    textEditGCodePal->setColor(QPalette::Text,QColor(0,0,0));// 黑色，文字显示的前景色
    textEditGCodePal->setColor(QPalette::Base,QColor(255,255,255));//白色 文字显示的背景色, 默认是白色的
    textEditGCodePal->setColor(QPalette::HighlightedText,QColor(255,255,255));//白色 被选中后文字的前景色
    textEditGCodePal->setColor(QPalette::Highlight,QColor(0,0,0)); //黑色 被选中后文字的背景色
    textEditGCode->setPalette(*textEditGCodePal);
    workSpaceDockWidget->setWidget(textEditGCode);*/

    if(gEditWidget->toPlainText()!="")	//如果编辑框不为空
     {
        QMessageBox msgBox;
        msgBox.setText("Save?");
        msgBox.setInformativeText("请问是否保存当前G代码和坐标数据？");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        msgBox.button(QMessageBox::Save)->setText("Save&New");
        msgBox.button(QMessageBox::Cancel)->setText("noSave&New");
        msgBox.setDefaultButton(QMessageBox::Save);

        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Save:{//仅保存G代码
                 SaveFile();
                 workFileNameAndFath="";
                 currentWorkFileNameAndFath->setText(workFileNameAndFath);//更新当前的状态栏，显示当前工作文件地址
                 gEditWidget->clear();
                 gEditWidget->setReadOnly(false);
                 allCoordinateVector.resize(0);
                 OutPutMsgToConsle(Information_INFO,"保存文件结束，并新建文件 成功 !");
                 break;}
            case QMessageBox::Cancel:{//都不保存
                 workFileNameAndFath="";
                 currentWorkFileNameAndFath->setText(workFileNameAndFath);
                 gEditWidget->clear();
                 gEditWidget->setReadOnly(false);
                 allCoordinateVector.resize(0);
                 OutPutMsgToConsle(Warning_INFO,"没有保存G代码和坐标数据！并新建文件 成功 !");
                 break;}
            default:
                 OutPutMsgToConsle(Critical_INFO,"文件保存判断框:int MainWindow::CloseFile()，按钮点击出错，请详细排查问题");
                 return;
                 break;
          }
        }
        else//编辑框为空
        {
            gEditWidget->clear();
            gEditWidget->setReadOnly(false);
            workFileNameAndFath="";
            currentWorkFileNameAndFath->setText(workFileNameAndFath);
            allCoordinateVector.resize(0);
            OutPutMsgToConsle(Information_INFO,"新建文件 成功 !");
        }

    QFont *gEditFont=new QFont( "Times New Roman", 13);//设置字体及大小
    gEditWidget->setFont(*gEditFont);
    MyHighLighter *highlighter = new MyHighLighter(gEditWidget->document());
    workSpaceDockWidget->setWidget(gEditWidget);



//    workSpaceDockWidget ->setMinimumSize(200, this->height());
//    workSpaceDockWidget->setAutoFillBackground(true);//加这句，下面设置颜色时，可以设置标题和控件主体的颜色，否则只能设置标题栏的颜色
//    workSpaceDockWidget->setPalette(dockWidgetPal);
//    textEditGCode=new QTextEdit(workSpaceDockWidget);
//    QPalette textEditGCodePal=this->palette();
//    textEditGCodePal.setColor(QPalette::Base,QColor(100,190,190));//白色 文字显示的背景色, 默认是白色的
//    textEditGCode->setPalette(textEditGCodePal);
//    textEditGCode->setPalette(*textEditGCodePal);
//    textEditGCode->setReadOnly(true);
//    QColor *color=new QColor(250,250,0);
//    setTextColor(textEditGCode,color);

//    workSpaceDockWidget->setAutoFillBackground(true);
    QPalette *workSpacePal=new QPalette;
    workSpacePal->setColor(QPalette::Window,QColor(255,255,255));//白色 文字显示的背景色, 默认是白色的
    workSpaceDockWidget->setPalette(*workSpacePal);

//    MyHighLighter * h1 = new MyHighLighter(textEditGCode->document());//传一个QTextDocument,添加语言高亮
//    MyHighLighter * h2 = new MyHighLighter(textDisplayGCode->document());//传一个QTextDocument,添加语言高亮


}

void MainWindow::SaveFile()
{
    //需要保存的东西:1.文本编辑框的G代码，2.轨迹坐标，3.绘画图形
    //可能存在的问题:1.只有编辑框有内容 2.只有轨迹坐标 ，3.只有轨迹坐标和图形 （暂不考虑），4.编辑框有内容+轨迹坐标，5.编辑框有内容+轨迹坐标+图形（暂不考虑）
    //保存编辑框的G代码文本
    if(gEditWidget->toPlainText()==""){
        OutPutMsgToConsle(Information_INFO,"无G代码需要保存");
        return;
    };

    if(workFileNameAndFath==""&&gEditWidget->toPlainText()!=""){
        SaveAsFile();
    }else
    {
        QFile file(workFileNameAndFath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))//追加写入 添加结束符\r\n
        {
            OutPutMsgToConsle(Critical_INFO,"打开文件进行G代码保存失败!! 请检查当前的G代码文件地址并尝试重新保存，当前文件地址: "+workFileNameAndFath);
            return ;
        }
        else
        {
            file.write(gEditWidget->toPlainText().toUtf8());
        }
        file.close();
//**************************************
        //保存坐标轨迹到数据文本
        if(allCoordinateVector.size()>0)
        {
            QFile coordinateDataFile("C://Users//Administrator//Desktop//homework//坐标数据.csv");
            if(!coordinateDataFile.open(QIODevice::WriteOnly | QIODevice::Text))//追加写入 添加结束符\r\n
            {
                OutPutMsgToConsle(Critical_INFO,"打开文件进行坐标数据保存失败!! 请尝试重新保存");
                return ;
            }
            else
            {
                int i=0;
                for (i=0;i<(allCoordinateVector.size());i++)
                {
                    //写入内容,这里需要转码，否则报错。
                    QByteArray str = QString("%1,%2\n").arg(allCoordinateVector.at(i).x()).arg(allCoordinateVector.at(i).y()).toUtf8();
                    coordinateDataFile.write(str);
                };

                if(i==allCoordinateVector.size())
                {
                    OutPutMsgToConsle(Information_INFO,"数据文件保存成功!!");
                };
            }
        }else
        {
            OutPutMsgToConsle(Information_INFO,"无坐标数据需要被保存!!");
        };
    };

}

void MainWindow::SaveAsFile()
{

    if(gEditWidget->toPlainText()==""){
        OutPutMsgToConsle(Information_INFO,"无G代码需要保存");
        return;
    };
    if(gEditWidget->toPlainText()!=""){
        //弹出保存的窗口,使用多个格式过滤器时，使用;;来分隔每种格式,同一种文件拥有多种格式"Images (*.png *.xpm *.jpg)"
        QString gfileNmae=QFileDialog::getSaveFileName(this,"文件另存为","C://Users//Administrator//Desktop","Text files (*.txt);;CSV(逗号分隔)(*.csv);;Excel工作簿(*.xlsx);;XML files (*.xml)");
        workFileNameAndFath=gfileNmae;
        //保存输入的保存文件名
        QFile gfile(gfileNmae);
        if(!gfile.open(QIODevice::WriteOnly | QIODevice::Text))//追加写入 添加结束符\r\n
        {
            OutPutMsgToConsle(Critical_INFO,"打开文件进行G代码保存失败!! 请检查当前的G代码文件地址并尝试重新保存，当前文件地址: "+workFileNameAndFath);
            return ;
        }
        else
        {
            gfile.write(gEditWidget->toPlainText().toUtf8());
        }
        gfile.close();
    };
//*************************************************

    //保存坐标轨迹到数据文本
    if(allCoordinateVector.size()>0)
    {
        QFile coordinateDataFile("C://Users//Administrator//Desktop//homework//坐标数据.csv");
        if(!coordinateDataFile.open(QIODevice::WriteOnly | QIODevice::Text))//追加写入 添加结束符\r\n
        {
            OutPutMsgToConsle(Critical_INFO,"打开文件进行坐标数据保存失败!! 请尝试重新保存");
            return ;
        }
        else
        {
            int i=0;
            for (i=0;i<(allCoordinateVector.size());i++)
            {
                //写入内容,这里需要转码，否则报错。
                QByteArray str = QString("%1,%2\n").arg(allCoordinateVector.at(i).x()).arg(allCoordinateVector.at(i).y()).toUtf8();
                coordinateDataFile.write(str);
            };

            if(i==allCoordinateVector.size())
            {
                OutPutMsgToConsle(Information_INFO,"数据文件保存成功!!");
            };
        }
        coordinateDataFile.close();
    }else
    {
        OutPutMsgToConsle(Information_INFO,"无坐标数据需要被保存!!");
    };

}

void MainWindow::CloseFile()
{
//    textDisplayGCode->clear();
//    textEditGCode->clear();
//    textDisplayGCode->setReadOnly(true);
//    textEditGCode->setReadOnly(true);

//    textEditGCode=new QTextEdit;
//    delete textEditGCode;
//    textEditGCode->clear();
//    textEditGCode->hide();
//    QPalette *textEditGCodePal=new QPalette;
    //设置文字颜色
//    textEditGCodePal->setColor(QPalette::Base,QColor(190,190,190));//白色 文字显示的背景色, 默认是灰色的
//    textEditGCode->setPalette(*textEditGCodePal);

    if(gEditWidget->toPlainText()!=""||allCoordinateVector.size()!=0)	//如果编辑框不为空
     {
        QMessageBox msgBox;
        msgBox.setText("Save?");
        msgBox.setInformativeText("请问是否保存当前G代码和坐标数据？");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Save |QMessageBox::Close |QMessageBox::Cancel);
        msgBox.button(QMessageBox::Save)->setText("Save");
        msgBox.button(QMessageBox::Close)->setText("no Save");
        msgBox.button(QMessageBox::Cancel)->setText("Cancel");
        msgBox.setDefaultButton(QMessageBox::Save);

        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Save:{//仅保存G代码
                 SaveFile();
                 workFileNameAndFath="";
                 currentWorkFileNameAndFath->setText(workFileNameAndFath);//更新当前的状态栏，显示当前工作文件地址
                 gEditWidget->clear();
                 gEditWidget->setReadOnly(true);
                 allCoordinateVector.resize(0);
                 OutPutMsgToConsle(Information_INFO,"保存G代码和轨迹坐标并关闭当前编辑文件 成功 !");
                 break;}
            case QMessageBox::Close:{//都不保存
                 workFileNameAndFath="";
                 currentWorkFileNameAndFath->setText(workFileNameAndFath);
                 gEditWidget->clear();
                 gEditWidget->setReadOnly(true);
                 allCoordinateVector.resize(0);
                 OutPutMsgToConsle(Warning_INFO,"关闭当前编辑文件并把轨迹坐标清空 成功 !");
                 break;}
            case QMessageBox::Cancel:{
                return;
                 break;}
            default:
                 OutPutMsgToConsle(Critical_INFO,"文件保存判断框:int MainWindow::CloseFile()，按钮点击出错，请详细排查问题");
                 return;
                 break;
          }
        }
        else//编辑框为空，轨迹坐标为空
        {
            gEditWidget->clear();
            gEditWidget->setReadOnly(true);
            workFileNameAndFath="";
            currentWorkFileNameAndFath->setText(workFileNameAndFath);
            allCoordinateVector.resize(0);
        }


    QPalette *workSpacePal=new QPalette;
    workSpacePal->setColor(QPalette::Window,QColor(190,190,190));//灰色 ，表示没有文件能被编辑
    workSpaceDockWidget->setPalette(*workSpacePal);
    textEditGCode->setStyleSheet("QTextEdit { background: rgb(190,190,190) }");


}

void MainWindow::beginAnalysis()
{
//    onlyAnalysis();//算法解析
//    area->beginPaint();
    area->image.save("C://Users//Administrator//Desktop//homework//CONFIG1.png");

}
void MainWindow::onlyAnalysis()
{
    OutdatedMsgToConsle();//把之前可能存在的消息，置于灰色代表是上一次的过时消息

//第一步，输入指令得到解析的指令
    if(gEditWidget->toPlainText().isEmpty()){//判断是否有指令输入
        QMessageBox::critical(nullptr,"指令输入检测","没有指令输入!! 请先手动输入指令，或者导入外部指令");
        return;};
    isRunAnalysis=true;//设置当前程序开始运行的标志
    OutRunMsgToConsle();
    GCommand *baseCommand=NULL;//抽象类，指令解析基类
    MyCommand *mycommand=new MyCommand;
    mycommand->setInCommandText(*gEditWidget);//初始化指令文本输入
    //判断读取到的指令系统
    if(getConfi("CommandSystem","GCommand")=="MyCommand")
    {
        OutPutMsgToConsle(Warning_INFO,"MainWindow::onlyAnalysis(): 读取到的指令解析系统为 MyCommand");
//第二步，按照解析后的指令，通过匹配算法进行计算
//        mycommand->commandExport();
        if(getConfi("algorithmSet","algorithmWay")=="ZhuDian")//但是逐点比较法时
        {
            OutPutMsgToConsle(Warning_INFO,"读取到当前执行算法为:逐点比较法");
//            outCurrentWorkMsg();
            AlgoRunByCmd(baseCommand->commandFrame(mycommand)->commandExport());//先按照输入的文本指令得到解析后的指令，再按照指令执行算法计算，得到总的轨迹坐标
            OutPutMsgToConsle(Running_INFO,"按照指令和算法计算总坐标，结束！");
//第三步，根据算法计算后的坐标轨迹进行输出（绘画，坐标输出，文件输出）

        }
        else if(getConfi("algorithmSet","algorithmWay")=="DDA")//按照DDA算法来执行相关计算
        {
            OutPutMsgToConsle(Warning_INFO,"读取到当前执行算法为:DDA(数字积分法)，但由于尚未添加相关算法，暂不执行，结束");
            return;
        };
    }
    else
    {
        OutPutMsgToConsle(Critical_INFO,"MainWindow::onlyAnalysis(): 没有读取到具体的指令解析系统，程序终止！");
        return;//没有读取到指令系统则直接结束整体所有工作
    };
    isRunAnalysis=false;//设置当前程序结束运行的标志
    OutRunMsgToConsle();
}

void MainWindow::Setting()
{
    SettingMainWindow *settingWindow = new SettingMainWindow(this);
    settingWindow->setWindowModality(Qt::ApplicationModal);//设置当前窗口为模态对话框
    settingWindow->show();
}

void MainWindow::ExitSystem()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this, QStringLiteral("提示"), QStringLiteral("是否退出系统?"), QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes) {//如果选择是
        this->close();//退出系统
    }
}


void MainWindow::setTextColor( QTextEdit *textEdit,QColor *color) {

//    QPalette palette = textEdit->palette();
//    const QColor &color = QColorDialog::getColor(palette.color(QPalette::Background), this);
//    qDebug()<<"color"<<color;
//    if (color.isValid()) {
//        palette.setColor(QPalette::Highlight, color);
//        textEdit->setPalette(palette);
//    }

    textEdit->setAutoFillBackground(true);
    QPalette textEditGCodePal=textEdit->palette();
    //设置文字颜色
    textEditGCodePal.setColor(QPalette::Text,QColor(0,250,0));// 黑色，文字显示的前景色
    textEditGCodePal.setColor(QPalette::Base,*color);//白色 文字显示的背景色, 默认是白色的
    textEditGCodePal.setColor(QPalette::HighlightedText,QColor(255,255,255));//白色 被选中后文字的前景色
    textEditGCodePal.setColor(QPalette::Highlight,QColor(0,0,0)); //黑色 被选中后文字的背景色
    textEdit->setPalette(textEditGCodePal);
}

void MainWindow::outCurrentWorkMsg()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间

    OutPutMsgToConsle(Running_INFO,time.toString("hh:mm:ss"));
}

void MainWindow::ConvertShowOrHide(QWidget *widget)
{
    //根据是否显示决定显示或隐藏，点击一次切换状态，显示或隐藏
    if(widget->isVisibleTo(this))
    {
        widget->hide();
    }else
    {
        widget->show();
    }
}

//把解析后的指令，按照一种确定的切割算法，计算出轨迹坐标
void MainWindow::AlgoRunByCmd(QVector<CommandStatus *> temCmdTotal)
{
    allCoordinateVector.resize(0);//每次需要计算一整份指令文本，需要提前把轨迹坐标总容器置0，排除前一轮计算的结果干扰
    Algorithm *base=NULL;

    StraightLinePTPCM *algoPTPCM=new StraightLinePTPCM();
    CircularArcPTPCM *algoDDA=new CircularArcPTPCM();
    QPoint beginPoint(0,0);//整体的轨迹坐标都是从（0,0）开始的

    for (int i=0;i<temCmdTotal.size();i++) {
        //当前行的指令是否需要切割工作
        if(temCmdTotal.at(i)->isMove)
        {
            OutPutMsgToConsle(Running_INFO,"当前需要切割的行号i: "+QString::number(i+1));
            if(temCmdTotal.at(i)->line==STR_LINE)//指令是直线切割
            {
                //每条指令计算轨迹之前，给当前线段赋起点和终点
                algoPTPCM->setInitPoint(beginPoint,QPoint(temCmdTotal.at(i)->point.x,temCmdTotal.at(i)->point.y));
                beginPoint=QPoint(temCmdTotal.at(i)->point.x,temCmdTotal.at(i)->point.y);//把上一次的终点赋值给下一段的开始
                base->algorithmFrame(algoPTPCM);//开始计算轨迹坐标，此处根据传入的算法对象不同，实现不同的算法，多态发生

                allCoordinateVector<<(algoPTPCM->algorithmExport());//把当前线段的临时坐标添加到总的坐标容器里
                OutPutMsgToConsle(Information_INFO,"直线_切割算法计算后，此次及之前坐标累加的容器大小: "+QString::number(allCoordinateVector.size()));
//                base->testAlgorithmExport(algoPTPCM->algorithmExport());//输出当前的临时坐标
            }
            else if(temCmdTotal.at(i)->line==ARC_LINE)//指令是圆弧切割
            {
                //每条指令计算轨迹之前，给当前线段赋起点，终点和圆心
                algoDDA->setInitPoint(beginPoint,QPoint(temCmdTotal.at(i)->point.x,temCmdTotal.at(i)->point.y),temCmdTotal.at(i)->code, QPoint(temCmdTotal.at(i)->point.i,temCmdTotal.at(i)->point.j));
//                OutPutMsgToConsle(Critical_INFO,"测试圆弧算法: "+QString::number(beginPoint.rx())+","+QString::number(beginPoint.ry())+"|"+QString::number(temCmdTotal.at(i)->point.x)+","+QString::number(temCmdTotal.at(i)->point.y)+"|"+QString::number(temCmdTotal.at(i)->point.i)+","+QString::number(temCmdTotal.at(i)->point.j));
                beginPoint=QPoint(temCmdTotal.at(i)->point.x,temCmdTotal.at(i)->point.y);//把上一次的终点赋值给下一段的开始
                base->algorithmFrame(algoDDA);//开始计算轨迹坐标，此处根据传入的算法对象不同，实现不同的算法，多态发生

                allCoordinateVector<<(algoDDA->algorithmExport());//把当前线段的临时坐标添加到总的坐标容器里
                OutPutMsgToConsle(Information_INFO,"圆弧_切割算法计算后，此次及之前坐标累加的容器大小: "+QString::number(allCoordinateVector.size()));
            };
        }else
        {
            OutPutMsgToConsle(Running_INFO,"当前执行的指令(已被解析后): "+QString::number(i+1)+" ,此指令不需要移动，是功能性指令，具体功能还没有做...");
        };
    }

}



