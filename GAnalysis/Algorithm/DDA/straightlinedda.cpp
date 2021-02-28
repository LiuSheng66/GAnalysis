#include "straightlinedda.h"
#include<QDebug>
#include<QPainter>

//QVector<QPoint> StraightLineDDA::SL_SZ_array;

StraightLineDDA::StraightLineDDA():
    Step(0)
{
    transitionCoordinate.resize(0);//每一个指令的实时坐标初始化为0
}

StraightLineDDA::StraightLineDDA(QPoint begin,QPoint end):
    Step(0)
{
    transitionCoordinate.resize(0);//每一个指令的实时坐标初始化为0
    beginPoint=begin;
    endPoint=end;
}

StraightLineDDA::~StraightLineDDA()
{

}

void StraightLineDDA::algorithmEntry()
{
    QString strLine = QString("得到直线起始点坐标信息:(%1 ,%2) -> (%3 ,%4)").arg(beginPoint.rx()).arg(beginPoint.ry()).arg(endPoint.rx()).arg(endPoint.ry());
    OutPutMsgToConsle(Running_INFO,"直线--DDA: 连续切削算法计算  ** 开始  ** :"+strLine);

    StepLength=1;//后期添加步长手动输入，这里直接默认为1

    shiftValue=-beginPoint;
    Ac_XYPoint=beginPoint=QPoint(0,0);
    moveToTargetPoint(endPoint,false,shiftValue);

    //用终点坐标判断直线所在象限
    int EndCoordinate_Value = GetQuadrantJudge(endPoint.rx(), endPoint.ry());

    Step = 0;//累加步骤
    //如果步长不是1的话，可能这个累加器容量计算有问题，被int，丢失数据
    AccumulatorVolume = (abs(endPoint.rx()) + abs(endPoint.ry())) / StepLength;
    AccumulatorValue = 0;//累加器数值初始化
    while (!(Ac_XYPoint.rx() == endPoint.rx() && Ac_XYPoint.ry() == endPoint.ry())&& AccumulatorValue < AccumulatorVolume)
    {
        DeviationCalChooseFun(EndCoordinate_Value, AccumulatorVolume, Ac_XYPoint.rx(), Ac_XYPoint.ry(), endPoint.rx(), endPoint.ry(), StepLength,Step);
    }
    OutPutMsgToConsle(Running_INFO,"直线--DDA: 连续切削算法计算  ** 结束  ** :总共步数："+QString::number(Step));
}

QVector<QPoint> StraightLineDDA::algorithmExport()
{
    return transitionCoordinate;//返回实际坐标值（按照步进电机的脉冲数为单位）
}

void StraightLineDDA::DeviationCalChooseFun(int& EndCoordinate_Value, int& AccumulatorVolume, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)//
{
    //（1,2,3,4)代表四个象限,5代表X正半轴，6代表X负半轴；7代表Y正轴，8代表Y负半轴，9代表原点
    switch (EndCoordinate_Value)
    {
    case 1:Point_JudgeChange_SL1(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 2:Point_JudgeChange_SL2(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 3:Point_JudgeChange_SL3(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 4:Point_JudgeChange_SL4(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 5:Point_JudgeChange_SL5(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 6:Point_JudgeChange_SL6(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 7:Point_JudgeChange_SL7(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 8:Point_JudgeChange_SL8(AccumulatorVolume, XRes, YRes,Ac_X, Ac_Y, End_X, End_Y,StepLength, Step);
        break;
    case 9:OutPutMsgToConsle(Warning_INFO,"StraightLinePTPCM/DeviationCalChooseFun:当前点所在象限判断（9）——错误警告,该坐标是原点无需要处理");
        break;
    default:
        OutPutMsgToConsle(Critical_INFO,"StraightLinePTPCM/DeviationCalChooseFun: 当前点所在象限判断（default）——象限值存在错误！");
        break;
    }
}


void StraightLineDDA::Point_JudgeChange_SL1
(int& AccumulatorVolume, long& XRes,long& YRes,int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength,int& Step)
{

    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
//        MainAlgorithmFunction::CoordinateMove_OldToInit(Ac_X, Ac_Y, PointMove[0], PointMove[1]);
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面

//        MainAlgorithmFunction::CoordinateMove_InitToOld(Ac_X, Ac_Y, PointMove[0], PointMove[1]);
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}

void StraightLineDDA::Point_JudgeChange_SL2
(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)
{
    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}

void StraightLineDDA::Point_JudgeChange_SL3
(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)
{
    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}

void StraightLineDDA::Point_JudgeChange_SL4
(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)
{
    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}

void StraightLineDDA::Point_JudgeChange_SL5
(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)
{
    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}

void StraightLineDDA::Point_JudgeChange_SL6
(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)
{
    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}

void StraightLineDDA::Point_JudgeChange_SL7
(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)
{
    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}

void StraightLineDDA::Point_JudgeChange_SL8
(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step)
{
    int xOutputSignal = 0, yOutputSignal = 0;
    XRes += End_X / StepLength;
    YRes += End_Y / StepLength;
    if (XRes >= AccumulatorVolume)   //当余数累加到溢出时，对余数进行重新确定，并把相应的坐标轴进行进给
    {
        XRes = XRes % AccumulatorVolume;
        Ac_X += StepLength;
        xOutputSignal = 1;
    }

    if (YRes >= AccumulatorVolume)
    {
        YRes = YRes % AccumulatorVolume;
        Ac_Y += StepLength;
        yOutputSignal = 1;
    }
    if (xOutputSignal == 1 || yOutputSignal == 1)
    {
        moveToTargetPoint(Ac_X,Ac_Y,true,shiftValue);
        transitionCoordinate.push_back(QPoint(Ac_X,Ac_Y));//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_X,Ac_Y,false,shiftValue);
        xOutputSignal = yOutputSignal = 0;
    }
    AccumulatorValue++;
    Step++;
}
