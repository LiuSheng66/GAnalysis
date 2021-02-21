#include "straightlineptpcm.h"
//#include<widget.h>
#include<QDebug>
#include<QPainter>
#include<QMessageBox>

StraightLinePTPCM::StraightLinePTPCM()
{
//    Begin_X=StraightLine::Begin_X;
//    Begin_Y=StraightLine::Begin_Y;
//    End_X=StraightLine::End_X;
//    End_Y=StraightLine::End_Y;
     beginPoint=QPointF(0,0);
     endPoint=QPointF(30,30);

    Step=0;//初始化
}

StraightLinePTPCM::~StraightLinePTPCM()
{
}

//QPoint ZhuDianBiJiao::returnAC_array()
//{
//    return ZhuDianBiJiao::AC_array;
//}
 void StraightLinePTPCM::algorithmEntry()
{

     QString strLine = QString("得到的输入坐标信息：%1 %2 %3 %4 ").arg(beginPoint.rx()).arg(beginPoint.ry()).arg(endPoint.rx()).arg(endPoint.ry());
     qDebug()<<strLine;
     End_X=endPoint.rx();
     End_Y=endPoint.ry();

     //坐标平移，把起点移到从原点开始,PointMove[]数组包含了平移的值，
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

//     QPainter *painterZhuDianSL=new QPainter;
//     painterZhuDianSL
//     painterZhuDianSL->drawLine(0,0,10,10);
     QPoint TemporaryPoint;
     while (!(Ac_X==End_X&& Ac_Y==End_Y))
     {
         DeviationCalChooseFun(EndCoordinate_Value, Line_Result, Ac_X, Ac_Y, End_X, End_Y, Step);
//         MainAlgorithmFunction::CoordinateMove_OldToInit(Ac_X, Ac_Y, nowBias.rx(), nowBias.ry());
         Ac_X=Ac_X-nowBias.rx();
         Ac_Y=Ac_Y-nowBias.ry();
         //把实时坐标存储在AC_array里面
         TemporaryPoint.rx()=Ac_X;
         TemporaryPoint.ry()=Ac_Y;
         AllCoordinate_array.push_back(TemporaryPoint);//把临时Qpoint数据放在SL_ZD_array里面
        // qDebug()<<Ac_X<<" "<< Ac_Y;
//         MainAlgorithmFunction::CoordinateMove_InitToOld(Ac_X, Ac_Y, PointMove[0], PointMove[1]);
         Ac_X=Ac_X+nowBias.rx();
         Ac_Y=Ac_Y+nowBias.ry();
     }
     qDebug()<<"总共步数："<<Step;
     qDebug()<<"成功使用直线的逐点比较法,并输出临时的坐标数据：";
     for(int i=0;i<AllCoordinate_array.size();i++)
     {
         qDebug()<<"第 "<<i<<" 步："<<AllCoordinate_array.at(i);
     };
}

 void StraightLinePTPCM::Deviation_Cal_SL()
 {
//     Line_Result = End_X * Ac_Y - Ac_X * End_Y;
     Line_Result =endPoint.rx()*Ac_Y-Ac_X*endPoint.ry();
 }

void StraightLinePTPCM::DeviationCalChooseFun
(int& EndCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout)
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
        QMessageBox::critical( NULL, "错误警告", "错误警告,该坐标是原点无需要处理");
        break;
    default:
        QMessageBox::critical(NULL,"错误警告","象限值存在错误！");

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


