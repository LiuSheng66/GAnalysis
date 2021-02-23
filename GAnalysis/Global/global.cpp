#include "global.h"

QTextEdit *exportMessage;

//QPainter p(exportMessage);
QString addressConfiStr="C://Users//Administrator//Desktop//homework//CONFIG.ini";


void outMessageDisplay(QString str, QTextEdit &MessageDisplayWindow)
{
    MessageDisplayWindow.append(str);
}

void outMessageClear(QTextEdit &MessageDisplayWindow)
{
    MessageDisplayWindow.clear();
}

//按照消息等级，输出的个性化消息框
void OutPutMsgToConsle(ConSleLevel level, const QString &strText, QTextEdit &MessageDisplayWindow)
{
//日志等级大于配置文件允许的最高等级，就返回
    //可以用于消息弹出时中止此函数
//    if (level > LocalConfig::GetInstance().GetCfgConsleLevel())
//    {
//        return;
//    }

    MessageDisplayWindow.append(strText);

    //选中需要显示颜色的文字
    QTextCursor cursor = MessageDisplayWindow.textCursor();
//    cursor.setPosition(cursor.position(),QTextCursor::MoveAnchor);
//    cursor.setPosition(cursor.position() + strText.length(),QTextCursor::KeepAnchor);
//    cursor.select(QTextCursor::BlockUnderCursor);//选择光标下的文本块，也可改成只选中单词
    cursor.movePosition(QTextCursor::StartOfBlock, QTextCursor::MoveAnchor,1);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor,1);

    QTextCharFormat fmt;
   //根据不同等级绘制不同颜色
//   QPainter p(exportMessage);
    switch (level)
    {
    case Critical_INFO:
        fmt.setForeground(Qt::red);
        break;
    case Warning_INFO:
        fmt.setForeground(QColor(255 ,185 ,15));//黄色
        break;
    case Running_INFO:
        fmt.setForeground(Qt::blue);
        break;
    case Information_INFO:
        fmt.setForeground(Qt::black);
        break;
    default:
        break;
    }
    cursor.mergeCharFormat(fmt);
    cursor.clearSelection(); //撤销选中
    cursor.movePosition(QTextCursor::EndOfBlock);  //cursor和anchor均移至末尾
}

void OutdatedMsgToConsle(QTextEdit &MessageDisplayWindow)
{
    //选中需要显示颜色的文字
    QTextCursor cursor = MessageDisplayWindow.textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);//QTextCursor::Start代表从输出的全部的消息的最初开始定锚点
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor,1);
    QTextCharFormat fmt;
    fmt.setForeground(QColor(211, 211 ,211));

    cursor.mergeCharFormat(fmt);
    cursor.clearSelection(); //撤销选中
    cursor.movePosition(QTextCursor::EndOfBlock);  //cursor和anchor均移至末尾
    if(!MessageDisplayWindow.toPlainText().isEmpty())
    {
         MessageDisplayWindow.append("\n");
    };

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
            OutPutMsgToConsle(Information_INFO,"setConfi函数： 参数写入 完成！");
        }
        else
        {
            OutPutMsgToConsle(Information_INFO,"setConfi函数： 参数写入 失败！");
        };
}

QString getConfi(QString SectionName,QString keyName,QString strFileAddressAndName)
{
    if(isFileExist(strFileAddressAndName))
    {
        QSettings *settings = new QSettings(strFileAddressAndName,QSettings::IniFormat);//调用QSettings操作ini文件
        QString keyValue = settings->value(SectionName+"/"+keyName).toString();//按照对应的节名和键名，读出ini文件中保存的内容，默认为空
        delete settings;
        OutPutMsgToConsle(Information_INFO,"getConfi函数： 参数读取 完成！");

        return keyValue;
    }
    else
    {
        OutPutMsgToConsle(Information_INFO,"getConfi函数： 参数读取 失败！");
        return NULL;
    };
}

bool isFileExist(QString strFileAddress)
{
    QFile file(strFileAddress);
        if (file.exists())
        {
            return true;
        }else//按照当前给定的地址文件不存在
        {
            QMessageBox msgBox;
            msgBox.setText("按照给定的文件地址，找不到相关文件: 可能是地址错误或文件本身丢失...");
            msgBox.setInformativeText("Are you willing to create a new file based on the given address?");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.button(QMessageBox::Ok)->setText("创建");
            msgBox.button(QMessageBox::Discard)->setText("不创建");
            msgBox.setDetailedText("请输入完整地址，如 \"C://Users//Administrator//Desktop//CONFIG.ini\" ");
            msgBox.setDefaultButton(QMessageBox::Cancel);

            int ret = msgBox.exec();
            switch (ret) {
                case QMessageBox::Ok:{
                     QFile file(strFileAddress);
                     if(!file.open(QIODevice::WriteOnly))
                     {
                         OutPutMsgToConsle(Critical_INFO,"新建文件，尝试开始失败！");
                         return false;
                     }
                     else
                     {
                         OutPutMsgToConsle(Information_INFO,"新建文件，尝试开始成功！");
                     }
                     file.close();
                     return true;
                     break;}
                case QMessageBox::Discard:{
                     OutPutMsgToConsle(Warning_INFO,"按照当前地址，未找到文件，且没有创建文件，程序中止！");
                     return false;
                     break;}
                case QMessageBox::Cancel:{
                     OutPutMsgToConsle(Warning_INFO,"按照当前地址，未找到文件，且没有创建文件，程序中止！");
                     return false;
                     break;}
                default:
                     OutPutMsgToConsle(Critical_INFO,"文件存在判断框 bool isFileExist(QString strFileAddress)，按钮点击出错，请详细排查问题");
                     return false;
                     break;
              }
        };
}



double pulseEquivalent=0.01;//初始化脉冲当量为0.01mm，根据需要可以更改

int distanceToPulses(double distance)
{
    return distance/pulseEquivalent;//返回步进电机所需的脉冲数
}

double pulsesToDistance(int pulses)
{
    return pulses*pulseEquivalent;//返回步进电机执行脉冲数后在机床实际坐标系中表现出来的实际位移（mm）
}

QVector<QPoint> AllCoordinate_array;
