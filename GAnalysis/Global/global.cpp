#include "global.h"

QTextEdit *exportMessage;

QString addressConfiStr="C://Users//Administrator//Desktop//homework//CONFIG.ini";

void outMessageDisplay(QString str)
{
    exportMessage->append(str);
}

void outMessageClear()
{
    exportMessage->clear();
}

void setConfi(QString SectionName, QString keyName, QString keyValue,QString strFileAddressAndName )
{
    //    QString aFile = QDir::currentPath() + "/zygapp.db";

        if(isFileExist(strFileAddressAndName))//文件存在
        {

            QSettings *settings = new QSettings(strFileAddressAndName,QSettings::IniFormat);//实例化，前面的参数是填写的配置文件的路径 ,后面的是让QSetting 用 ini的格式进行读写
            settings->setIniCodec("UTF-8");
            settings->setValue( SectionName+"/"+keyName,keyValue);//将内容写入ini文件中
            delete settings;
            outMessageDisplay("setConfi函数： 参数写入 完成！");
        }
        else
        {
            outMessageDisplay("setConfi函数： 参数写入 失败！");
        };
}

QString getConfi(QString SectionName,QString keyName,QString strFileAddressAndName)
{
    if(isFileExist(strFileAddressAndName))
    {
        QSettings *settings = new QSettings(strFileAddressAndName,QSettings::IniFormat);//调用QSettings操作ini文件
        QString keyValue = settings->value(SectionName+"/"+keyName).toString();//按照对应的节名和键名，读出ini文件中保存的内容，默认为空
        delete settings;
        outMessageDisplay("getConfi函数： 参数读取 完成！");
        return keyValue;
    }
    else
    {
        outMessageDisplay("getConfi函数： 参数读取 失败！");
        return NULL;
    };
}

bool isFileExist(QString strFileAddress)
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
        outMessageDisplay(strFileAddress+"：不是完整的地址，请输入完整地址，如 \"C://Users//Administrator//Desktop//CONFIG.ini\" ");
        return fileExist;
    };
}
