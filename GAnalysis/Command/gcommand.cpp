#include "gcommand.h"
#include<QDebug>
#include<QMessageBox>
#include<Command/mycommandrules.h>
GCommand::GCommand()
{
    cmdFinal.resize(0);//初始化空间大小为0，清除可能存在的数据
}

GCommand::GCommand(CodeEditor &inputPlainText)
{
    setInCommandText(inputPlainText);
//    QStringList stringList=splitBy(commandStrTotal," ");
//    for(int row=0;row<stringList.length();row++)
//    {
//        qDebug()<<"gcommand QStringList:"<<stringList[row];
//    }
//    commandPlainText=&inputPlainText;
//    QRegExp pattern1=QRegExp("\\bG01\\b");
//    bool test= commandPlainText->find(pattern1);
//    if(test)
//    {
//            qDebug()<<"GCommand test ok";
//            qDebug()<<"commandPlainText->blockCount():"<<commandPlainText->blockCount();
//    }
//    else
//            qDebug()<<"GCommand test false";

}

GCommand::~GCommand()
{

}

QVector<CommandStatus *> GCommand::commandExport()
{
    return cmdFinal;
}

GCommand * GCommand::commandFrame(GCommand *begin)
{
    begin->commandEntry();
    return begin;
}

 void GCommand::setInCommandText(CodeEditor &inputPlainText)
 {
    commandPlainText=&inputPlainText;
    commandStrTotal=inputPlainText.toPlainText();

 }

 void GCommand::findCommand()
 {
     QRegExp pattern1=QRegExp("\\bG01\\b");

     bool test= commandPlainText->find(pattern1);
     if(test)
     {
        qDebug()<<"GCommand findCommand test ok";
     }
     else
        qDebug()<<"GCommand findCommand test false";
 }

 void GCommand::getCommand()
 {

 }

 bool GCommand::isCorrectCMD()
 {
     return true;
 }

 QStringList GCommand::splitBy(const QString &text, QString keyword)
 {
     return text.split(keyword);
 }

 QStringList GCommand::splitBySentence(const QString &inText)
 {
     QString keyword="\n";
     //按换行符\n分割文本内容
     return splitBy(inText,"\n");
//     inText.split("\n", QString::SkipEmptyParts);
 }

 QStringList GCommand::splitByWord(QString &inText)
 {
//     QString keyword=" ";
     //按换行符\n分割文本内容
//     QStringList wordBySpaceList=splitBy(inText,keyword);
     return splitBy(inText," ");
 }

 //预处理
 bool GCommand::PreProcces(QString & inToOutText)
 {
     if(!inToOutText.isEmpty())
     {
         //去前后空格
         inToOutText=inToOutText.trimmed();
         //全部大写
         inToOutText=inToOutText.toUpper();
         return true;
     }
     else
         return false;
 }

 //把如X10.02等字符串处理为步进电机的步数
 int GCommand::coordinateStrToInt(const QString  coordinate)
 {
     int coordinateResult=0;//返回的数字坐标
     QString str=coordinate;
     if(!str.isEmpty())
     {
         str=str.trimmed();//去前后空格
         str=str.toUpper();//全部大写
         if(str.at(0)=="X"||str.at(0)=="Y"||str.at(0)=="I"||str.at(0)=="J")
         {
             str=str.remove(0,1);//去除坐标的第一个字母，如X10.0->10.0
             coordinateResult=distanceToPulses(str.toDouble());
         }
         else
         {
             OutPutMsgToConsle(Critical_INFO,"函数coordinateStrToInt:分离提取坐标参数失败，如X10.01，没有得到首字母X、Y、I、J");
         };
     }
     else
     {
         OutPutMsgToConsle(Critical_INFO,"函数coordinateStrToInt:分离提取坐标参数失败，如X10.01，提取字符为空");
     }
     return coordinateResult;
 }

