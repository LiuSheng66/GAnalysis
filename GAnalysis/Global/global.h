#ifndef GLOBAL_H
#define GLOBAL_H
#include<QTextEdit>
#include<QSettings>
#include<QDir>
#include<QPainter>
#include<QBrush>
#include<QMessageBox>
#include <QAbstractButton>

extern QTextEdit *exportMessage;//输出窗口部件
//extern QPainter p;
extern QString addressConfiStr;//配置文件的文件目录地址
extern QString workFileNameAndFath;//工作G代码的工作地址和名字
extern bool isRunAnalysis;//作为程序是否开始解析的信号标志
extern QVector<QPoint> allCoordinateVector;//整体轨迹坐标的集合
//消息输出框的消息等级
enum ConSleLevel{
    Critical_INFO,
    Warning_INFO,
    Running_INFO,
    Information_INFO
};

//以后新增其他规则的指令系统需要在里面添加
//enum CmdSystem{
//    MyCommandSystem//当前默认的指令规则系统

//};

extern void outMessageDisplay(QString str,QTextEdit &MessageDisplayWindow=*exportMessage);//一般的消息输出函数
extern void outMessageClear(QTextEdit &MessageDisplayWindow=*exportMessage);//清除输出的消息
extern void OutPutMsgToConsle(ConSleLevel level,const QString &strText,QTextEdit &MessageDisplayWindow=*exportMessage);//具有消息等级输出的消息输出框函数
extern void OutdatedMsgToConsle(QTextEdit &MessageDisplayWindow=*exportMessage);
extern void OutRunMsgToConsle(const QString &fileNameAndPathWork=workFileNameAndFath,QTextEdit &MessageDisplayWindow=*exportMessage);
//配置文件操作
extern void setConfi( QString SectionName, QString keyName, QString keyValue="NULL",QString strFileAddressAndName = addressConfiStr);
extern QString getConfi(QString SectionName,QString keyName,QString strFileAddressAndName = addressConfiStr);
extern bool isFileExist(QString strFileAddress=addressConfiStr);


extern double pulseEquivalent;//脉冲当量，即步进电机一个脉冲的线位移，本程序以普通机床0.01mm为例
extern int distanceToPulses(double distance);//把坐标系的位移转化步进电机所需要的脉冲数
extern double pulsesToDistance(int pulses);//把步进电机执行的脉冲数转化为实际机床坐标系的位移




#endif // GLOBAL_H
