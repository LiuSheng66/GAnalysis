#ifndef GLOBAL_H
#define GLOBAL_H
#include<QTextEdit>
#include<QSettings>
#include<QDir>

extern QTextEdit *exportMessage;//输出窗口部件
extern QString addressConfiStr;//配置文件的文件目录地址

extern void outMessageDisplay(QString str);//消息输出函数
extern void outMessageClear();//清除输出的消息

//配置文件操作
extern void setConfi( QString SectionName, QString keyName, QString keyValue="NULL",QString strFileAddressAndName = addressConfiStr);
extern QString getConfi(QString SectionName,QString keyName,QString strFileAddressAndName = addressConfiStr);
extern bool isFileExist(QString strFileAddress=addressConfiStr);

#endif // GLOBAL_H
