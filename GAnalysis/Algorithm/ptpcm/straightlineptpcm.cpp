#include "straightlineptpcm.h"
#include<QDebug>
#include<QPainter>
#include<QMessageBox>

StraightLinePTPCM::StraightLinePTPCM():
    Ac_X (0),
    Ac_Y(0),
    Line_Result(0)
{
    AllCoordinate_array.resize(0);//每一个指令的实时坐标初始化为0

     beginPoint=QPoint(0,0);
     endPoint=QPoint(100,100);

    Step=0;//初始化
}

StraightLinePTPCM::StraightLinePTPCM(QPoint begin,QPoint end):
    Ac_X (0),
    Ac_Y(0),
    Line_Result(0)
{
    AllCoordinate_array.resize(0);//每一个指令的实时坐标初始化为0

     beginPoint=begin;
     endPoint=end;

    Step=0;//初始化
}

StraightLinePTPCM::~StraightLinePTPCM()
{
}

 void StraightLinePTPCM::algorithmEntry()
{

     QString strLine = QString("得到的输入坐标信息：%1 %2 %3 %4 ").arg(beginPoint.rx()).arg(beginPoint.ry()).arg(endPoint.rx()).arg(endPoint.ry());
     qDebug()<<strLine;


     //坐标平移，把起点移到从原点开始,nowBias包含了平移的xy值，
     QPointF nowBias=Algorithm::OtherToOriginalPoint(beginPoint);
     //实时坐标初始化
     Ac_X = beginPoint.rx();
     Ac_Y = beginPoint.ry();
     //把终点坐标按照起点坐标一起，同步位移
     endPoint.rx()=endPoint.rx()+nowBias.rx();
     endPoint.ry()=endPoint.ry()+nowBias.ry();

    //用终点坐标判断直线所在象限
     int EndCoordinate_Value = Algorithm::GetQuadrantJudge(endPoint.rx(), endPoint.ry());

     Deviation_Cal_SL();
     while (!(Ac_X==endPoint.rx() && Ac_Y==endPoint.ry()))
     {
         DeviationCalChooseFun(EndCoordinate_Value, Line_Result, Ac_X, Ac_Y, endPoint.rx(), endPoint.ry(), Step);

         //把当前经过平移的坐标转化回去原始的坐标，用于存储实际坐标值
         Ac_X=Ac_X-nowBias.rx();
         Ac_Y=Ac_Y-nowBias.ry();

         AllCoordinate_array.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
         //前面已经把上一步计算的坐标存储好了，再把实时的计算坐标转化为，起点在原点的坐标，用于下一步循环计算
         Ac_X=Ac_X+nowBias.rx();
         Ac_Y=Ac_Y+nowBias.ry();
     }
     qDebug()<<"总共步数："<<Step;
     qDebug()<<"成功使用直线的逐点比较法,并输出临时的坐标数据：";
     for(int i=0;i<AllCoordinate_array.size();i++)
     {
         qDebug()<<"第 "<<i+1<<" 步："<<AllCoordinate_array.at(i);
     };
 }

 QVector<QPoint> StraightLinePTPCM::algorithmExport()
 {
     return AllCoordinate_array;//返回实际坐标值（按照步进电机的脉冲数为单位）
 }

 void StraightLinePTPCM::Deviation_Cal_SL()
 {
     Line_Result =endPoint.rx()*Ac_Y-Ac_X*endPoint.ry();
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
        QMessageBox::critical(NULL, "StraightLinePTPCM/DeviationCalChooseFun", "当前点所在象限判断（9）——错误警告,该坐标是原点无需要处理");
        break;
    default:
        QMessageBox::critical(NULL,"StraightLinePTPCM/DeviationCalChooseFun","当前点所在象限判断（default）——象限值存在错误！");
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


