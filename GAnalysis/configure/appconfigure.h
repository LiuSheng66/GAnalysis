#ifndef APPCONFIGURE_H
#define APPCONFIGURE_H
#include<QSettings>

class AppConfigure
{
public:
    AppConfigure();

     static void setConfi(QString strFileAddressAndName ,QString SectionName,QString keyName,QString keyValue="0");//设置ini文件的参数
     static QString getConfi(QString strFileAddressAndName ,QString SectionName,QString keyName);
     static bool isFileExist(QString strFileAddress);
signals:
//     void aboutConfigureDisplay(QString str);//自定义信号，输出栏内容改变信号，str代表需要显示的输出内容
};

#endif // APPCONFIGURE_H
