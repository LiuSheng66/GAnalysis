#include "mycommand.h"
#include<QMessageBox>
#include"Command/mycommandrules.h"
MyCommand::MyCommand(CodeEditor &inputPlainText)
{

}

MyCommand::~MyCommand()
{

}

void MyCommand::implementCommand()
{

}

bool MyCommand::isCorrectCMD()
{

}

//解析一行代码，生成一个指令CommandStatus结构体变量
CommandStatus MyCommand::createCmdByParagraph(QString sentence){
//    Element** res=new Element*;
    CommandStatus myCmds;
    if(sentence.isEmpty())
    {
        QMessageBox::critical(NULL,QObject::tr("段落指令解析" ),QObject::tr( "初步识别指令为空! 请检查指令输入是否存在问题"));
//        return ;
    }

    //每一行进行预处理,两头去空格
    sentence=sentence.trimmed();

    //提取指令参数
    QString cmd=sentence.left(3);

    //根据指令类型更新状态信息，然后创建元素
    switch(getCodeType(cmd))
    {
        case G99_CODE:{
//            *res=createNoShapeElement(sentence,status,lastPoint);

            break;
        }
        case RELATIVE_CODE:{
//            status.isRelative=true;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case ABSOLUTE_CODE:{
//            status.isRelative=false;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case INCH_CODE:{
//            status.isMeter=true;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case METER_CODE:{
//            status.isMeter=false;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case L_KERF_CODE:{
//            status.isLeft=1;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case R_KERF_CODE:{
//            status.isLeft=0;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case CANCEL_KERF_CODE:{
//            status.isLeft=-1;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case STR_LINE_WORK_CODE:{
//            status.isFire=true;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case EMPTY_QUICKMOVE_CODE:{
//            status.isFire=false;
//            *res=createNoShapeElement(sentence,status,lastPoint);
            break;
       }
        case CW_ARC_WORK_CODE:{
//            status.isQuickLine=false;
//            *res=createLineElement(sentence,status,lastPoint);
            break;
       }
        case ACW_ARC_WORK_CODE:{
//            status.isQuickLine=false;
//            status.isAcw=1;
//            *res=createArcElement(sentence,status,lastPoint);
            break;
       }
        case FIRE_BEGIN_CODE:{
//            status.isQuickLine=false;
//            status.isAcw=0;
//            *res=createArcElement(sentence,status,lastPoint);
            break;
       }
        case FIRE_END_CODE:{
//            status.isQuickLine=false;
//            status.isAcw=0;
//            *res=createArcElement(sentence,status,lastPoint);
            break;
       }
        case FIRE_CLOSE_CODE:{
//            status.isQuickLine=false;
//            status.isAcw=0;
//            *res=createArcElement(sentence,status,lastPoint);
            break;
       }
        case NO_USE_CODE:{
//            status.isQuickLine=false;
//            status.isAcw=0;
//            *res=createArcElement(sentence,status,lastPoint);
            break;
       }
        default:{
//           qDebug()<<"未知命令";
//           *res=createNoShapeElement(sentence,status,lastPoint);
           break;
       }
    }

    //如果是图元类则将此元素的终点记录下来，作为下一个元素的起点使用
//    if((*res)->isShape()){
//        lastPoint=static_cast<Shape*>(*res)->End();
//    }
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
