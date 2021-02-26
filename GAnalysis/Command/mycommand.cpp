#include "mycommand.h"

#include"Command/mycommandrules.h"
#include<QDebug>
#include"mainwindow.h"
MyCommand::MyCommand()
{
}
MyCommand::MyCommand(CodeEditor &inputPlainText)
{
    setInCommandText(inputPlainText);//从G代码编辑窗口初始化得到指令文本，指令文本要么从文件打开呈现在编辑框，要么自己手动在编辑框输入
}

MyCommand::~MyCommand()
{
}

void MyCommand::commandEntry()
{ 
    //初始化
    numCmdRow=1;//默认从第一行开始解析
    cmdFinal.resize(0);//每次开始指令解析之前先把空间大小初始化为0，清除之前可能存在的数据

    if(commandPlainText->toPlainText().isEmpty())
    {
        OutPutMsgToConsle(Critical_INFO ,"MyCommand/implementCommand():没有指令输入! 请检查指令输入是否存在问题");
        return;
    }
    OutPutMsgToConsle(Running_INFO,"指令解析: **************************** 开始 ******************************");
    QStringList strList=splitBySentence(commandStrTotal);//把整篇G代码按行裁成一段一段指令
    for(int i=0;i < strList.size();i++)
    {
//        OutPutMsgToConsle(Information_INFO,strList[i]);
         cmdFinal.push_back(createCmdByParagraph(strList[i]));//得到最后处理好的
    }
    holdPointAbsolute();//检测坐标系的绝对、相对，默认是绝对坐标系，如果是相对坐标系则转化为绝对坐标系

//测试指令
//    for(int i=0;i<cmdFinal.size();i++)
//    {
//        if(cmdFinal.at(i)->coordinate_System==ABSOLUTE_CSYS)
//        {
//            OutPutMsgToConsle(Information_INFO,QString::number(i)+"test:ABSOLUTE_CSYS");
//        }else if(cmdFinal.at(i)->coordinate_System==RELATIVE_CSYS)//只有检测到存在相对坐标系的指令，才会把整体指令里面的移动类坐标转化
//        {
//            OutPutMsgToConsle(Information_INFO,QString::number(i)+"test:RELATIVE_CSYS");
//        }else if(cmdFinal.at(i)->coordinate_System==NO_CSYS)
//        {
//            OutPutMsgToConsle(Information_INFO,QString::number(i)+"test:NO_CSYS");
//        }
//        if(cmdFinal.at(indx)->code==G99_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:G99_CODE");};
//        if(cmdFinal.at(indx)->code==RELATIVE_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:RELATIVE_CODE");};
//        if(cmdFinal.at(indx)->code==ABSOLUTE_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:ABSOLUTE_CODE");};
//        if(cmdFinal.at(indx)->code==INCH_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:INCH_CODE");};
//        if(cmdFinal.at(indx)->code==METER_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:METER_CODE");};
//        if(cmdFinal.at(indx)->code==L_KERF_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:L_KERF_CODE");};
//        if(cmdFinal.at(indx)->code==R_KERF_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:R_KERF_CODE");};
//        if(cmdFinal.at(indx)->code==CANCEL_KERF_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:CANCEL_KERF_CODE");};
//        if(cmdFinal.at(indx)->code==EMPTY_QUICKMOVE_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:EMPTY_QUICKMOVE_CODE");};
//        if(cmdFinal.at(indx)->code==STR_LINE_WORK_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:STR_LINE_WORK_CODE");};
//        if(cmdFinal.at(indx)->code==CW_ARC_WORK_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:CW_ARC_WORK_CODE");};
//        if(cmdFinal.at(indx)->code==ACW_ARC_WORK_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:ACW_ARC_WORK_CODE");};
//        if(cmdFinal.at(indx)->code==FIRE_BEGIN_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:FIRE_BEGIN_CODE");};
//        if(cmdFinal.at(indx)->code==FIRE_END_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:FIRE_END_CODE");};
//        if(cmdFinal.at(indx)->code==FIRE_CLOSE_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:FIRE_CLOSE_CODE");};
//        if(cmdFinal.at(indx)->code==NO_USE_CODE){OutPutMsgToConsle(Information_INFO,QString::number(indx)+"test:NO_USE_CODE");};
//    };

    OutPutMsgToConsle(Running_INFO,"指令解析: **************************** 结束 ******************************");
    OutPutMsgToConsle(Information_INFO,"指令容器的大小："+QString::number(cmdFinal.size()));
}

QVector<CommandStatus *> MyCommand::commandExport()
{
    return cmdFinal;
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
        OutPutMsgToConsle(Critical_INFO,"MyCommand/createCmdByParagraph():指令解析中发现存在一行指令为空! 请检查指令是否存在问题");
        return NULL;
    }

    //每一行进行预处理,两头去空格
    sentence=sentence.trimmed();
    //判断段落指令是否符合规则，没有错误
    if(!isCorrectCMD(sentence))
    {
        myCmds->isCorrect=false;
        return myCmds;
    };

    //把一行代码转为一个个字符单位来处理
    QStringList singleCommandList=splitBy(sentence," ");//按空格分割文本内容

    //根据指令类型更新状态信息，然后创建元素
    switch(getCodeType(sentence.left(3)))
    {
        case G99_CODE:{
        myCmds->code=G99_CODE;
//        QMessageBox::information(NULL,QObject::tr("MyCommand/implementCommand" ),"第 "+numCmdRowStr+" 行——检测到：G99_CODE");
            break;
        }
        case RELATIVE_CODE:{
            myCmds->code=RELATIVE_CODE;
            myCmds->coordinate_System=RELATIVE_CSYS;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case ABSOLUTE_CODE:{
            myCmds->code=ABSOLUTE_CODE;
            myCmds->coordinate_System=ABSOLUTE_CSYS;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case INCH_CODE:{
            myCmds->code=INCH_CODE;
            myCmds->unitLen=INCH_LENGTH;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case METER_CODE:{
            myCmds->code=METER_CODE;
            myCmds->unitLen=METER_LENGTH;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case L_KERF_CODE:{
            myCmds->code=L_KERF_CODE;
            myCmds->coordinateOffset=L_OFFSET;
            myCmds->isNeedCoordinate=false;
            break;
       }
        case R_KERF_CODE:{
        myCmds->code=R_KERF_CODE;
        myCmds->coordinateOffset=R_OFFSET;
        myCmds->isNeedCoordinate=false;
            break;
       }
        case CANCEL_KERF_CODE:{
        myCmds->code=CANCEL_KERF_CODE;
        myCmds->coordinateOffset=CANALE_OFFSET;
        myCmds->isNeedCoordinate=false;
            break;
       }
        case EMPTY_QUICKMOVE_CODE:{
        myCmds->code=EMPTY_QUICKMOVE_CODE;
        myCmds->isNeedCoordinate=true;
        myCmds->isMove=true;
        myCmds->line=STR_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case STR_LINE_WORK_CODE:{
        myCmds->code=STR_LINE_WORK_CODE;
        myCmds->isNeedCoordinate=true;
        myCmds->isMove=true;
        myCmds->isNeedFire=true;
        myCmds->line=STR_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case CW_ARC_WORK_CODE:{
        myCmds->code=CW_ARC_WORK_CODE;
        myCmds->isNeedCoordinate=true;
        myCmds->isMove=true;
        myCmds->isNeedFire=true;
        myCmds->line=ARC_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case ACW_ARC_WORK_CODE:{
        myCmds->code=ACW_ARC_WORK_CODE;
        myCmds->isNeedCoordinate=true;
        myCmds->isMove=true;
        myCmds->isNeedFire=true;
        myCmds->line=ARC_LINE;
        cmdConvertPoint(*myCmds, singleCommandList);
            break;
       }
        case FIRE_BEGIN_CODE:{
        myCmds->code=FIRE_BEGIN_CODE;
//        myCmds->isNeedFire=true;
        OutPutMsgToConsle(Running_INFO,"MyCommand/implementCommand:"+numCmdRowStr+" 行——检测到：FIRE_BEGIN_CODE");
            break;
       }
        case FIRE_CLOSE_CODE:{
        myCmds->code=FIRE_CLOSE_CODE;
//        myCmds->isNeedFire=false;
        OutPutMsgToConsle(Running_INFO,"MyCommand/implementCommand:"+numCmdRowStr+" 行——检测到：FIRE_CLOSE_CODE");
            break;
        }
        case FIRE_END_CODE:{
        myCmds->code=FIRE_END_CODE;
        OutPutMsgToConsle(Running_INFO,"MyCommand/implementCommand:"+numCmdRowStr+" 行——检测到：FIRE_END_CODE");
            break;
       }
        case NO_USE_CODE:{
        myCmds->code=NO_USE_CODE;
        myCmds->isCorrect=false;
        OutPutMsgToConsle(Running_INFO,"MyCommand/implementCommand:"+numCmdRowStr+" 行——检测到：NO_USE_CODE");
            break;
       }
        default:{
        OutPutMsgToConsle(Warning_INFO,"MyCommand/implementCommand:"+numCmdRowStr+" 行——未检测到：Cmd-default");
           break;
       }
    };
    numCmdRow++;//解析完一行进行+1
    return myCmds;
}

//把解析后的指令的坐标转化为绝对坐标系
void MyCommand::holdPointAbsolute()
{
    int temx=0,temy=0,temi=0,temj=0;
    for(int i=0;i < cmdFinal.size();i++)
    {
        if(cmdFinal.at(i)->coordinate_System==ABSOLUTE_CSYS)
        {
            OutPutMsgToConsle(Information_INFO,"当前指令系统采用坐标系: 绝对坐标系");
            return;
        };

        if(cmdFinal.at(i)->coordinate_System==RELATIVE_CSYS)//只有检测到存在相对坐标系的指令，才会把整体指令里面的移动类坐标转化
        {
            for(int indx=0;indx<cmdFinal.size();indx++)
            {
                if(cmdFinal.at(indx)->isMove)//只有需要移动的指令才需要转化坐标系
                {
                    temx=cmdFinal.at(indx)->point.x=cmdFinal.at(indx)->point.x+temx;
                    temy=cmdFinal.at(indx)->point.y=cmdFinal.at(indx)->point.y+temy;
                    temi=cmdFinal.at(indx)->point.i=cmdFinal.at(indx)->point.i+temi;
                    temj=cmdFinal.at(indx)->point.j=cmdFinal.at(indx)->point.j+temj;
                };
            };
            OutPutMsgToConsle(Information_INFO,"当前指令系统采用坐标系: 相对坐标系（当然内部是采用绝对坐标系计算）");
            return;
        }
    }
    OutPutMsgToConsle(Warning_INFO,"当前指令文本未包含指定坐标: NO_CSYS");
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
             cmdStatus.point.x=coordinateStrToInt(cmdStrList[i]);
          };
          if(cmdStrList[i].at(0)=="Y")
          {
             cmdStatus.point.y=coordinateStrToInt(cmdStrList[i]);
          };
          if(cmdStrList[i].at(0)=="I")
          {
             cmdStatus.point.i=coordinateStrToInt(cmdStrList[i]);
          };
          if(cmdStrList[i].at(0)=="J")
          {
             cmdStatus.point.j=coordinateStrToInt(cmdStrList[i]);
          };
      }
  }






