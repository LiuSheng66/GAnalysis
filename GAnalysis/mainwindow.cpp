#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSettings>
#include<QMessageBox>
#include<QToolBar>
#include<QStatusBar>
#include<QDockWidget>
#include<QSizePolicy>
#include<QDebug>
//#include<QFile>
#include<QFileDialog>
#include<QTextCodec>
#include<QColorDialog>
#include<QDateTime>

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

    statusBar()->showMessage(tr("就绪"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{

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
    QPalette MainBackgroundpal=this->palette();
    MainBackgroundpal.setColor(QPalette::Background,QColor(255,255,255));
    this->setPalette(MainBackgroundpal);

    //删除中央窗体,QMainWindow中自带中央窗体，如果不去除的话，可能会造成窗口间有空块的情况
    QWidget* p = takeCentralWidget();
    if (p){
        delete p;
    }

//    //设置文字颜色
    QPalette *textEditGCodePal=new QPalette;
    textEditGCodePal->setColor(QPalette::Text,QColor(0,0,0));// 黑色，文字显示的前景色
    textEditGCodePal->setColor(QPalette::Base,QColor(190,190,190));//白色 文字显示的背景色, 默认是白色的
    textEditGCodePal->setColor(QPalette::HighlightedText,QColor(255,255,255));//白色 被选中后文字的前景色
    textEditGCodePal->setColor(QPalette::Highlight,QColor(0,0,0)); //黑色 被选中后文字的背景色


    //定义QDockWidgetd的背景色
//    QPalette dockWidgetPal=this->palette();
//    dockWidgetPal.setColor(QPalette::Background,QColor(255,255,255));
//    允许嵌套dock
    setDockNestingEnabled(true);
    workSpaceDockWidget = new QDockWidget(tr("工作区"), this);
    addDockWidget(Qt::LeftDockWidgetArea,workSpaceDockWidget);
    workSpaceDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置都可以
    workSpaceDockWidget ->setMinimumWidth(200);
//    workSpaceDockWidget ->setMinimumSize(200, this->height());
//    workSpaceDockWidget->setAutoFillBackground(true);//加这句，下面设置颜色时，可以设置标题和控件主体的颜色，否则只能设置标题栏的颜色
//    workSpaceDockWidget->setPalette(dockWidgetPal);
    textEditGCode=new QTextEdit(workSpaceDockWidget);
//    QPalette textEditGCodePal=this->palette();
//    textEditGCodePal.setColor(QPalette::Base,QColor(100,190,190));//白色 文字显示的背景色, 默认是白色的
//    textEditGCode->setPalette(textEditGCodePal);
//    textEditGCode->setPalette(*textEditGCodePal);
    textEditGCode->setReadOnly(true);
    QColor *color=new QColor(250,250,0);
    QColor *color1=new QColor(250,22,0);
    setTextColor(textEditGCode,color);
    setTextColor(textEditGCode,color1);
    workSpaceDockWidget->setWidget(textEditGCode);

    gDisplayDockWidget = new QDockWidget(tr("G代码显示"), this);
    tabifyDockWidget(workSpaceDockWidget, gDisplayDockWidget);
    // raise()函数可使指定窗口置于最前
    workSpaceDockWidget->raise();//可设置那个显示在最前面
    gDisplayDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
//    gDisplayDockWidget ->setMinimumSize(200, this->height());
    gDisplayDockWidget ->setMinimumWidth(200);
    textDisplayGCode=new QTextEdit(workSpaceDockWidget);
    gDisplayDockWidget->setWidget(textDisplayGCode);

    PropertyDockWidget = new QDockWidget(tr("属性"), this);
    addDockWidget(Qt::RightDockWidgetArea,PropertyDockWidget);
    PropertyDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
//    PropertyDockWidget ->setMinimumSize(150, this->height());
    PropertyDockWidget ->setMinimumWidth(150);

    outPutdockWidget = new QDockWidget(tr("输出"), this);
    addDockWidget(Qt::BottomDockWidgetArea,outPutdockWidget);
    outPutdockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures); // 设置可移动
    outPutdockWidget ->setMinimumSize(this->width()-workSpaceDockWidget->width()-PropertyDockWidget->width(),150 );
    textOutput=new QTextEdit(this);
    outPutdockWidget->setWidget(textOutput);

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
    AnalysAct = new QAction(BeginAnalysActIcon, QStringLiteral("执行(&U)"), this);
    AnalysAct->setStatusTip(QStringLiteral("执行"));
    AnalysAct->setShortcuts(QKeySequence::Open);//打开快捷键
    connect(AnalysAct, &QAction::triggered, this, &MainWindow::DealWithAnalysis);


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
    editMenu = menuBar()->addMenu(QStringLiteral("编辑").trimmed()+tr("(&E)"));//实例化一个编辑菜单栏
    viewMenu = menuBar()->addMenu(QStringLiteral("视图").trimmed()+tr("(&V)"));//实例化一个视图菜单栏
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

    editMenu->addAction(settingAct);

    analysisMenu->addAction(AnalysAct);

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

    analysisTool->addAction(AnalysAct);

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

    // 设置高度
    statusBar()->setMinimumHeight(25);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 1px}")); // 不显示边框

    outputStatusLabel = new QLabel();
    outputStatusLabel->setFrameStyle(QFrame::WinPanel | QFrame::Raised);

    QFont font("Microsoft YaHei", 10);//设置显示文字的字体和文字大小

    // 添加提示信息标签
//    outputStatusLabel->setMinimumWidth(this->width() / 2);
    outputStatusLabel->setFont(font);
    outputStatusLabel->setText("状态栏标签");
    outputStatusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar()->addPermanentWidget(outputStatusLabel);
//    statusBar()->addWidget(outputStatusLabel);

    pushBtn=new QPushButton(this);
    pushBtn->setText("1 输出");
    pushBtn->setFont(font);
    pushBtn->setFlat(true);//就是这句实现按钮透明的效果。
    statusBar()->addPermanentWidget(pushBtn);
    //点击按钮显示或
    connect(pushBtn, &QPushButton::clicked, this,[=](){
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
    QString path=QFileDialog::getOpenFileName(this,"打开文件","C://Users//Administrator//Desktop");
//    lineEdit->setText(path);//可以把路径输出到编辑框中

    //编码格式类,默认UTF-8
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");

    //读取内容
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray FileContent=file.readAll();
//    ui->textEditGCode->setText(FileContent);
    textEditGCode->setText(codec->toUnicode(FileContent));
    file.close();

    //设置文字颜色
    QPalette TextColorPal=this->palette();
    TextColorPal.setColor(QPalette::Text,QColor(0,0,0));// 黑色，文字显示的前景色
    TextColorPal.setColor(QPalette::Base,QColor(255,255,255));//白色 文字显示的背景色, 默认是白色的
    TextColorPal.setColor(QPalette::HighlightedText,QColor(255,255,255));//白色 被选中后文字的前景色
    TextColorPal.setColor(QPalette::Highlight,QColor(0,0,0)); //黑色 被选中后文字的背景色
    textEditGCode->setPalette(TextColorPal);

}


//写入文件内容
void MainWindow::NewFile()
{
    textEditGCode->clear();
    textEditGCode->setReadOnly(false);
    textEditGCode->setAutoFillBackground(true);
    QColor *color=new QColor(0,250,0);
    setTextColor(textEditGCode,color);
//    textEditGCode->setStyleSheet("QPushButton{background-color: white;  color: rgb(100, 100, 100) ;}");

}

void MainWindow::SaveFile()
{
    bool exist;


    QDir *coordinateFolder = new QDir;
    exist = coordinateFolder->exists("C://Users//Administrator//Desktop//坐标数据");//查看目录是否存在（默认保存到桌面）
    //不存在就创建
    if(!exist)
    {
        bool ok = coordinateFolder->mkdir("C://Users//Administrator//Desktop//坐标数据");//创建子目录
        if(ok)
        {
            QMessageBox::information(this,tr("创建数据保存文件夹"),tr("文件夹创建成功!"));//添加提示方便查看是否成功创建
        }else
        {
            QMessageBox::warning(this,tr("创建数据保存文件夹"),tr("文件夹创建失败！！"));
        }
    }
    //为了点击保存，就直接保存，且不会覆盖以往的文件，采用时间为文件名进行保存
    QDateTime Time = QDateTime::currentDateTime();//获取系统现在的时间
    QString strTime = Time.toString("坐标数据 yyyy_MM_dd hh_mm_ss");//设置显示格式
    QString fileName = tr("C://Users//Administrator//Desktop//坐标数据//%1.txt").arg(strTime);//设置保存文件的文件名

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))//追加写入 添加结束符\r\n
    {
        QMessageBox::warning(this,tr("打开文件"),tr("打开文件失败,数据保存失败！！请重新尝试"));
        return ;
    }
    else
    {

          file.write("尝试保存数据");
//        if(MainAlgorithmFunction::AllCoordinate_array.size()>0)
//        {
//            for (int i=0;i<(MainAlgorithmFunction::AllCoordinate_array.size()-1);i++)
//            {
//                int xDisply=MainAlgorithmFunction::AllCoordinate_array.at(i).x();
//                int yDisply=MainAlgorithmFunction::AllCoordinate_array.at(i).y();
//                QString content = QString("%1,%2\n").arg(xDisply).arg(yDisply);
//                //写入内容,这里需要转码，否则报错。
//                QByteArray str = content.toUtf8();
//                file.write(str);
//            }
//        }
//        else
//        {
//            file.write("warning:无数据需要保存");
//        }

    }
    file.close();
    QMessageBox::information(this,tr("创建新文件"),tr("已创建新的数据保存文件"));
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
    textEditGCode->clear();
    textDisplayGCode->clear();
    textEditGCode->setReadOnly(true);
    QPalette *textEditGCodePal=new QPalette;
    //设置文字颜色
    textEditGCodePal->setColor(QPalette::Base,QColor(190,190,190));//白色 文字显示的背景色, 默认是灰色的

    textEditGCode->setPalette(*textEditGCodePal);

}

void MainWindow::DealWithAnalysis()
{

        const QIcon PauseAnalysActIcon =QIcon(":/image/icon/pauseAnalysis.png");
        AnalysAct ->setIcon(PauseAnalysActIcon);
        AnalysAct->setStatusTip(QStringLiteral("暂停"));
//        QMessageBox::information(this,tr("测试函数"),tr("已点击"));

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
