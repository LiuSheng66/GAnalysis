#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<paintarea.h>
#include<QScrollArea>//提供画布的滚动条
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PaintArea *area;
    QScrollArea *scrollArea;
    QList<QDockWidget*> m_docks;

    //声明菜单栏
    QMenu *fileMenu;//文件菜单栏
    QMenu *EditMenu;//编辑菜单栏
    QMenu *analysisMenu;//绘图菜单栏
    QMenu *HelpMenu;//帮助菜单栏

    //声明工具栏
    QToolBar *fileTool;//文件操作工具栏
    QToolBar *analysisTool;//绘图工具栏
    QToolBar *settingTool;//设置工具栏

    QStatusBar *statusdisplay;//声明状态栏，状态栏最多只能有一个

    QDockWidget *workSpaceDockWidget;
    QDockWidget *gDisplayDockWidget;
    QDockWidget *PropertyDockWidget;
    QDockWidget *outPutdockWidget;

    //声明每个Action的具体内容
    QAction *openFileAct;//打开文件菜单
    QAction *newFileAct;//创建新文件菜单
    QAction * closeAct;//删除单枪文件并对编辑区域清屏
    QAction *saveFileAct;//保存当前文件
    QAction *saveAsFileAct;//另存为当前文件

    QAction *beginAnalysAct;//声明推出程序菜单
    QAction *pauseAnalysAct;//声明推出程序菜单

    QAction *settingAct;//声明推出程序菜单

    QAction *closeSystemAct;//声明推出程序菜单

    QAction *aboutAct;//声明推出程序菜单

private:
    //布局设置
    void setLayout();
    //Action的具体设置  菜单栏、工具栏、状态栏具体设置
    void CreateActions();
    void CreatMenuBar();
    void CreateToolbar();
    void CreateStatusbar();

    //Action槽函数
    void OpenFile();
    void NewFile();
    void SaveFile();
    void SaveAsFile();
    void CloseFile();

    void CloseSystem();

    void TestFun();

    void BeginAnalysis();
    void Setting();


    void removeAllDock();
    void showDock(const QList<int>& index = QList<int>());
};
#endif // MAINWINDOW_H
