#include "appconfigure.h"
#include<QDir>
AppConfigure::AppConfigure()
{

}

//strFileAddress完整的文件地址包括文件后缀名
//设置ini文件的参数：SectionName，节名；keyName，键名；keyValue，输入的值
void AppConfigure::setConfi(QString strFileAddressAndName ,QString SectionName,QString keyName,QString keyValue)
{
//    QString aFile = QDir::currentPath() + "/zygapp.db";

    if(isFileExist(strFileAddressAndName))//文件存在
    {
        QSettings *settings = new QSettings(strFileAddressAndName,QSettings::IniFormat);//实例化，前面的参数是填写的配置文件的路径 ,后面的是让QSetting 用 ini的格式进行读写
        settings->setIniCodec("UTF-8");
        settings->setValue( SectionName+"/"+keyName,keyValue);//将内容写入ini文件中
        delete settings;
//        emit aboutConfigureDisplay("setConfi函数： 参数向文件写入 完成！");
    }
    else
    {
//        emit aboutConfigureDisplay("setConfi函数： 参数向文件写入 失败！");
    };
}

//注意文件名需要带后缀
QString AppConfigure::getConfi(QString strFileAddressAndName ,QString SectionName,QString keyName)
{
    if(isFileExist(strFileAddressAndName))
    {
        QSettings *settings = new QSettings(strFileAddressAndName,QSettings::IniFormat);//调用QSettings操作ini文件
        QString keyValue = settings->value(SectionName+"/"+keyName).toString();//按照对应的节名和键名，读出ini文件中保存的内容，默认为空
        delete settings;
//        emit aboutConfigureDisplay("getConfi函数： 参数从文件读取完成！");
        return keyValue;
    }
    else
    {
//        emit aboutConfigureDisplay("getConfi函数： 参数从文件读取 失败！");
        return NULL;
    };
}


//判断当前给定地址下的文件是否存在，是则返回true，反之false
//请输入完整的地址，注意文件名需要带后缀
bool AppConfigure::isFileExist(QString strFileAddress)
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
//        emit aboutConfigureDisplay(strFileAddress+"：不是完整的地址，请输入完整地址，如 \"C://Users//Administrator//Desktop//CONFIG.ini\" ");
        return fileExist;
    };
}
