#include "mycommand.h"

#include"Command/mycommandrules.h"
#include<QDebug>
#include"mainwindow.h"
MyCommand::MyCommand(CodeEditor &inputPlainText)
{
    numCmdRow=1;//默认从第一行开始解析
    setInCommandText(inputPlainText);
    implementCommand();
    qDebug()<<"cmdFinal.size() :"<<cmdFinal.size();
}

MyCommand::~MyCommand()
{

}

void MyCommand::implementCommand()
{
    QStringList strList=splitBySentence(commandStrTotal);//把整篇G代码按行裁成一段一段指令
    for(int i=0;i < strList.size();i++)
    {
//        qDebug()<<"strList-"<<i<<":"<<strList[i];
         cmdFinal.push_back(createCmdByParagraph(strList[i]));//得到最后处理好的
    }
//    QMessageBox::information(NULL,QObject::tr("implementCommand" ),QObject::tr( "strList 结束"));
}

bool MyCommand::isCorrectCMD(QString paragraphCmd)
{
    return true;//这个默认先直接返回true，具体后期在做
}

//解析一行代码，生成一个指令CommandStatus结构体变量
CommandStatus* MyCommand::createCmdByParagraph(QString sentence){
//    Element** res=new Element*;   
    QString numCmdRowStr = QString::number(numCmdRow);//行号

    CommandStatus *myCmds=new CommandStatus();
    if(sentence.isEmpty())
    {
        QMessageBox::critical(NULL,QObject::tr("段落指令解析" ),QObject::tr( "初步识别指令为空! 请检查指令输入是否存在问题"));
//        return ;
    }

    //每一行进行预处理,两头去空格
    sentence=sentence.trimmed();
    //判断段落指令是否符合规则，没有错误
    if(!isCorrectCMD(sentence))
    {
        myCmds->isCorrect=false;
        return myCmds;
    };


    //提取指令参数
    QString cmd=sentence.left(3);
    //把一行代码转为一个个字符单位来处理
    QStringList singleCommandList=splitByWord(sentence);//按换行符\n分割文本内容

    //根据指令类型更新状态信息，然后创建元素
    switch(getCodeType(cmd))
    {
        case G99_CODE:{
//        QMessageBox::information(NULL,QObject::tr("MyCommand/implementCommand" ),"第 "+numCmdRowStr+" 行——检测到：G99_CODE");
            break;
        }
        case RELATIVE_CODE:{
            myCmds->coordinate_System=RELATIVE_CSYS;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case ABSOLUTE_CODE:{
            myCmds->coordinate_System=ABSOLUTE_CSYS;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case INCH_CODE:{
            myCmds->unitLen=INCH_LENGTH;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case METER_CODE:{
            myCmds->unitLen=METER_LENGTH;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case L_KERF_CODE:{
            myCmds->coordinateOffset=L_OFFSET;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case R_KERF_CODE:{
        myCmds->coordinateOffset=R_OFFSET;
        myCmds->isNeedCoordinate=false;
            break;
       }
        case CANCEL_KERF_CODE:{
        myCmds->coordinateOffset=CANALE_OFFSET;
        myCmds->isNeedCoordinate=false;
            break;
       }
        case EMPTY_QUICKMOVE_CODE:{
        myCmds->isNeedCoordinate=true;
        myCmds->line=STR_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case STR_LINE_WORK_CODE:{
        myCmds->isNeedCoordinate=true;
        myCmds->line=STR_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case CW_ARC_WORK_CODE:{
        myCmds->isNeedCoordinate=true;
        myCmds->line=ARC_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case ACW_ARC_WORK_CODE:{
        myCmds->isNeedCoordinate=true;
        myCmds->line=ARC_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case FIRE_BEGIN_CODE:{
        myCmds->isNeedFire=true;
            break;
       }
        case FIRE_CLOSE_CODE:{
        myCmds->isNeedFire=false;
//        QMessageBox::information(NULL,QObject::tr("MyCommand/implementCommand" ),"第 "+numCmdRowStr+" 行——检测到：FIRE_CLOSE_CODE");
            break;
        }
        case FIRE_END_CODE:{
        QMessageBox::information(NULL,QObject::tr("MyCommand/implementCommand" ),"第 "+numCmdRowStr+" 行——检测到：FIRE_END_CODE");
            break;
       }
        case NO_USE_CODE:{
        myCmds->isCorrect=false;
        QMessageBox::information(NULL,QObject::tr("MyCommand/implementCommand" ),"第 "+numCmdRowStr+" 行——检测到：NO_USE_CODE");
            break;
       }
        default:{
        QMessageBox::information(NULL,QObject::tr("MyCommand/implementCommand" ),"第 "+numCmdRowStr+" 行——未检测到：Cmd-default");
           break;
       }
    };
    numCmdRow++;//解析完一行进行+1
    return myCmds;
}

//获取命令类型
 CodeType MyCommand::getCodeType(const QString &cmd)
 {
    enum CodeType code;
    if(cmd=="G99")//部件选项
        code=G99_CODE;
    else if(cmd=="G91")//相对坐标
        code=RELATIVE_CODE;
    else if(cmd=="G90")//绝对坐标
        code=ABSOLUTE_CODE;
    else if(cmd=="G20")//英制
        code=INCH_CODE;
    else if(cmd=="G21")//米制
        code=METER_CODE;
    else if(cmd=="G41")//左割缝补偿
        code=L_KERF_CODE;
    else if(cmd=="G42")//右割缝补偿
        code=R_KERF_CODE;
    else if(cmd=="G40")//割缝补偿取消
        code=CANCEL_KERF_CODE;
    else if((cmd=="G00") || cmd=="G0")//空车快移
        code=EMPTY_QUICKMOVE_CODE;
    else if((cmd=="G01") || cmd=="G1")//直线切割
        code=STR_LINE_WORK_CODE;
    else if((cmd=="G02") || cmd=="G2")//顺时针圆弧
        code=CW_ARC_WORK_CODE;
    else if(cmd=="G03" || cmd=="G3")//逆时针圆弧
        code=ACW_ARC_WORK_CODE;
    else if(cmd=="M07" || cmd=="M17")//切割开始
        code=FIRE_BEGIN_CODE;
    else if(cmd=="M08" || cmd=="M18")//切割结束
        code=FIRE_CLOSE_CODE;
    else if(cmd=="M02")//程序结束
        code=FIRE_END_CODE;
    else//处理其他情况
        code=NO_USE_CODE;
    return code;
 }

 //判断指令是否需要坐标参数配合使用
  cmdNeedPara MyCommand::isNeedParameter(const CodeType &cmd)
  {
     cmdNeedPara m_cmdNeedPara;

     switch (cmd) {
     case G99_CODE:
         m_cmdNeedPara=NEED_PARA;
         break;
     case RELATIVE_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case ABSOLUTE_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case INCH_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case METER_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case L_KERF_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case R_KERF_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case CANCEL_KERF_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case EMPTY_QUICKMOVE_CODE:
         m_cmdNeedPara=NEED_PARA;
         break;
     case STR_LINE_WORK_CODE:
         m_cmdNeedPara=NEED_PARA;
         break;
     case CW_ARC_WORK_CODE:
         m_cmdNeedPara=NEED_PARA;
         break;
     case ACW_ARC_WORK_CODE:
         m_cmdNeedPara=NEED_PARA;
         break;
     case FIRE_BEGIN_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case FIRE_CLOSE_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case FIRE_END_CODE:
         m_cmdNeedPara=DISNEED_PARA;
         break;
     case NO_USE_CODE:
         m_cmdNeedPara=REGARDLESS_PARA;
         break;
     default:
         m_cmdNeedPara=REGARDLESS_PARA;
         break;
     }

     return m_cmdNeedPara;
  }

  //把相应坐标的X Y I J的字符串数据转换为类的对应的坐标数据
  void MyCommand::cmdConvertPoint(CommandStatus &cmdStatus, QStringList cmdStrList)
  {
      for(int i=0;i < cmdStrList.size();i++)
      {
          if(cmdStrList[i].at(0)=="X")
          {
             cmdStatus.point.x=coordinateStrToDouble(cmdStrList[i]);
          };
          if(cmdStrList[i].at(0)=="Y")
          {
             cmdStatus.point.y=coordinateStrToDouble(cmdStrList[i]);
          };
          if(cmdStrList[i].at(0)=="I")
          {
             cmdStatus.point.i=coordinateStrToDouble(cmdStrList[i]);
          };
          if(cmdStrList[i].at(0)=="J")
          {
             cmdStatus.point.j=coordinateStrToDouble(cmdStrList[i]);
          };
      }
  }




