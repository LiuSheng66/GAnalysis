#include "straightlineptpcm.h"
#include<QDebug>
#include<QPainter>
#include<QMessageBox>

StraightLinePTPCM::StraightLinePTPCM():
    Line_Result(0),
    Step(0),
    shiftValue(QPoint(0,0))
{
    transitionCoordinate.resize(0);//每一个指令的实时坐标初始化为0
}

StraightLinePTPCM::StraightLinePTPCM(QPoint begin,QPoint end):
    Line_Result(0),
    Step(0),
    shiftValue(QPoint(0,0))

{
    transitionCoordinate.resize(0);//每一个指令的实时坐标初始化为0
    beginPoint=begin;
    endPoint=end;
}

StraightLinePTPCM::~StraightLinePTPCM()
{
}

 void StraightLinePTPCM::algorithmEntry()
{
     Step=0;//每次使用
     QString strLine = QString("得到直线起始点坐标信息:(%1 ,%2) -> (%3 ,%4)").arg(beginPoint.rx()).arg(beginPoint.ry()).arg(endPoint.rx()).arg(endPoint.ry());
     OutPutMsgToConsle(Running_INFO,"直线--逐点比较法: 连续切削算法计算  ** 开始  ** :"+strLine);

     //坐标平移，把起点移到从原点开始,shiftValue包含了平移的xy值,并实时坐标初始化
     shiftValue=-beginPoint;
     Ac_XYPoint=beginPoint=QPoint(0,0);

     //把终点坐标按照起点坐标一起，同步位移
     moveToTargetPoint(endPoint,false,shiftValue);

    //用终点坐标判断直线所在象限
     int EndCoordinate_Value = GetQuadrantJudge(endPoint.rx(), endPoint.ry());

     Line_Result =endPoint.rx()*Ac_XYPoint.ry()-Ac_XYPoint.rx()*endPoint.ry();//直线最初偏差计算公式
     while (!(Ac_XYPoint.rx()==endPoint.rx() && Ac_XYPoint.ry()==endPoint.ry()))
     {
         DeviationCalChooseFun(EndCoordinate_Value, Line_Result, Ac_XYPoint.rx(), Ac_XYPoint.ry(), endPoint.rx(), endPoint.ry(), Step);
         //把当前经过平移的坐标转化回去原始的坐标，用于存储实际坐标值
         moveToTargetPoint(Ac_XYPoint,true,shiftValue);
         transitionCoordinate.push_back(Ac_XYPoint);//把临时Qpoint数据放在SL_ZD_array里面
         //前面已经把上一步计算的坐标存储好了，再把实时的计算坐标转化为，起点在原点的坐标，用于下一步循环计算
         moveToTargetPoint(Ac_XYPoint,false,shiftValue);
     }
     OutPutMsgToConsle(Running_INFO,"直线--逐点比较法: 连续切削算法计算  ** 结束  ** :总共步数："+QString::number(Step));
 }

 QVector<QPoint> StraightLinePTPCM::algorithmExport()
 {
     return transitionCoordinate;//返回实际坐标值（按照步进电机的脉冲数为单位）
 }


void StraightLinePTPCM::DeviationCalChooseFun
(int& EndCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& step)
{
    //（1,2,3,4)代表四个象限,5代表X正半轴，6代表X负半轴；7代表Y正轴，8代表Y负半轴，9代表原点
    switch (EndCoordinate_Value)
    {
    case 1:Point_JudgeChange_SL1(Line_Result, Ac_X, Ac_Y,  End_X, End_Y,Step);
        break;
    case 2:Point_JudgeChange_SL2(Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
        break;
    case 3:Point_JudgeChange_SL3(Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
        break;
    case 4:Point_JudgeChange_SL4(Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
        break;
    case 5:Point_JudgeChange_SL5(Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
        break;
    case 6:Point_JudgeChange_SL6(Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
        break;
    case 7:Point_JudgeChange_SL7(Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
        break;
    case 8:Point_JudgeChange_SL8(Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
        break;
    case 9:
        OutPutMsgToConsle(Warning_INFO,"StraightLinePTPCM/DeviationCalChooseFun:当前点所在象限判断（9）——错误警告,该坐标是原点无需要处理");
        break;
    default:
        OutPutMsgToConsle(Critical_INFO,"StraightLinePTPCM/DeviationCalChooseFun: 当前点所在象限判断（default）——象限值存在错误！");
        break;
    }
}

void StraightLinePTPCM::Point_JudgeChange_SL1
(int& Line_Result,int& Ac_X,int& Ac_Y,int& End_X,int& End_Y, int& Step)
{

    if (Line_Result >= 0)//向+X方向进给
    {
        Line_Result = Line_Result - abs(End_Y);
        Ac_X++;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result + abs(End_X);
        Ac_Y++;
        Step++;
    }
}

void StraightLinePTPCM::Point_JudgeChange_SL2
(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Step)
{

    if (Line_Result >= 0)//向+X方向进给
    {
        //Line_Result = Line_Result + End_X;
        Line_Result = Line_Result - abs(End_Y);
        //Ac_Y++;
        Ac_X--;
        Step++;
    }
    else            //向+Y方向进给
    {
        //Line_Result = Line_Result + End_Y;
        Line_Result = Line_Result + abs(End_X);
        //Ac_X--;
        Ac_Y++;
        Step++;
    }
}

void StraightLinePTPCM::Point_JudgeChange_SL3
(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Step)
{

    if (Line_Result >= 0)//向+X方向进给
    {
        Line_Result = Line_Result - abs(End_Y);
        Ac_X--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result + abs(End_X);
        Ac_Y--;
        Step++;
    }
}

void StraightLinePTPCM::Point_JudgeChange_SL4
(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Step)
{

    if (Line_Result >= 0)//向+X方向进给
    {
        Line_Result = Line_Result - abs(End_Y);
        //Line_Result = Line_Result + End_Y;
        //Ac_Y--;
        Ac_X++;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result + abs(End_X);
        //Line_Result = Line_Result + End_X;
        //Ac_X++;
        Ac_Y--;
        Step++;
    }
}
void StraightLinePTPCM::Point_JudgeChange_SL5
(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Step)
{
    if (End_X > 0)
    {
        Ac_X++;
        Step++;
    }
    else
    {
        qDebug()<<"象限判断值和处理函数存在冲突！！";
    }
}

void StraightLinePTPCM::Point_JudgeChange_SL6
(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Step)
{
    if (End_X < 0)
    {
        Ac_X--;
        Step++;
    }
    else
    {
    qDebug()<<"象限判断值和处理函数存在冲突！！";
    }
}


void StraightLinePTPCM::Point_JudgeChange_SL7
(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Step)
{
    if (End_Y > 0)
    {
        Ac_Y++;
        Step++;
    }
    else
    {
    qDebug()<<"象限判断值和处理函数存在冲突！！";
    }
}

void StraightLinePTPCM::Point_JudgeChange_SL8
(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Step)
{
    if (End_Y < 0)
    {
        Ac_Y--;
        Step++;
    }
    else
    {
    qDebug()<<"象限判断值和处理函数存在冲突！！";
    }
}


