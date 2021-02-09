#include "gcommand.h"
#include<QDebug>
#include<QMessageBox>
#include<Command/mycommandrules.h>
GCommand::GCommand()
{

}

GCommand::GCommand(CodeEditor &inputPlainText)
{
    setInCommandText(inputPlainText);
    QStringList stringList=splitBy(commandStrTol," ");
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



 void GCommand::setInCommandText(CodeEditor &inputPlainText)
 {
    commandPlainText=&inputPlainText;
    commandStrTol=inputPlainText.toPlainText();

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
     QStringList res;
     res=text.split(keyword);
     return res;
 }

 QStringList GCommand::splitBySentence(const QString &inText, QString keyword)
 {
     keyword="\n";
     //按换行符\n分割文本内容
     QStringList sentenceByEnterList=splitBy(inText,keyword);
     return sentenceByEnterList;
 }

 QStringList GCommand::splitByWord(QString &inText, QString keyword)
 {
     keyword=" ";
     //按换行符\n分割文本内容
     QStringList wordBySpaceList=splitBy(inText,keyword);
     return wordBySpaceList;
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

 //
 double GCommand::coordinateStrToDouble(const QString & coordinate)
 {
     float mycoordinate=0;//返回的数字坐标
     QString str=coordinate;
     if(!str.isEmpty())
     {
         str=str.trimmed();//去前后空格
         str=str.toUpper();//全部大写
         if(str.at(0)=="X"||str.at(0)=="Y"||str.at(0)=="I"||str.at(0)=="J")
         {
             str=str.remove(0,1);//去除坐标的第一个字母，如X10.0->10.0
             mycoordinate=str.toDouble();

         }
         else
         {
             QMessageBox::critical(nullptr, "函数coordinateStrToDouble","分离提取坐标参数失败，如X10.01，没有得到首字母X、Y、I、J");
         };
     }
     else
     {
         QMessageBox::critical(nullptr, "函数coordinateStrToDouble","分离提取坐标参数失败，如X10.01，提取字符为空");
     }
     return mycoordinate;
 }
