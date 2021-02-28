#include "circulararcptpcm.h"
#include<QDebug>
#include<QPainter>
#include<QMessageBox>

CircularArcPTPCM::CircularArcPTPCM():
    Line_Result(0),
    Step(0)
{
    transitionCoordinate.resize(0);//每一个指令的实时坐标初始化为0
}

CircularArcPTPCM::CircularArcPTPCM(QPoint begin,QPoint end,QPoint center):
    Line_Result(0),
    Step(0)
{
    transitionCoordinate.resize(0);//每一个指令的实时坐标初始化为0
    beginPoint=begin;
    endPoint=end;
    centerPoint=center;
}

CircularArcPTPCM::~CircularArcPTPCM()
{

}

//圆弧插补的入口函数
void CircularArcPTPCM::algorithmEntry()
{
    QString strLine = QString("得到圆弧的坐标信息:(%1 ,%2) -> (%3 ,%4) ,圆心:(%5 ,%6)").arg(beginPoint.rx()).arg(beginPoint.ry()).arg(endPoint.rx()).arg(endPoint.ry()).arg(centerPoint.rx()).arg(centerPoint.ry());
    OutPutMsgToConsle(Running_INFO,"圆弧--逐点比较法: 连续切削算法计算  ** 开始  ** :"+strLine);
    //判断能否构成圆弧
    if( !JudgeIsCircularArc( beginPoint.rx(), beginPoint.ry(), endPoint.rx(), endPoint.ry(),centerPoint.rx(), centerPoint.ry())){return;};
    //判断顺逆圆弧
//    DirectionCircular = JudgeCircularArc_Direction(centerPoint.rx(), centerPoint.ry(), beginPoint.rx(), beginPoint.ry(), endPoint.rx(), endPoint.ry());
    if(inCode==CW_ARC_WORK_CODE)//顺时针
    {
        DirectionCircular=false;
    }
    else if(inCode==ACW_ARC_WORK_CODE)//逆时针
    {
        DirectionCircular=true;
    }else
    {
        OutPutMsgToConsle(Critical_INFO,"错误警告: 检测到不是圆弧指令（G02、G03）而执行了圆弧算法，请检查指令的解析,圆弧算法 结束!");
        return;
    };

    //假设把圆心移到原点得到偏差值
    shiftValue=-centerPoint;
    //把终点坐标和起点坐标按照圆心坐标一起同步位移
    moveToTargetPoint(endPoint,false,shiftValue);
    moveToTargetPoint(beginPoint,false,shiftValue);
    //实时坐标初始化
    Ac_XYPoint=beginPoint;

    //最初偏差计算公式
    Line_Result = Ac_XYPoint.rx() * Ac_XYPoint.rx() + Ac_XYPoint.ry() * Ac_XYPoint.ry() - ((Ac_XYPoint.rx())*(Ac_XYPoint.rx())+(Ac_XYPoint.ry())*(Ac_XYPoint.ry()));
    //计算起点的所在象限
    BeginCoordinate_Value = GetQuadrantJudge(Ac_XYPoint.rx(), Ac_XYPoint.ry());
    EndCoordinate_Value=GetQuadrantJudge(endPoint.rx(), endPoint.ry());

    CircleBegin();
    OutPutMsgToConsle(Running_INFO,"圆弧--逐点比较法: 连续切削算法计算  ** 结束  ** :总共步数："+QString::number(Step));
}

QVector<QPoint> CircularArcPTPCM::algorithmExport()
{
    return transitionCoordinate;//返回实际坐标值（按照步进电机的脉冲数为单位）
}


void CircularArcPTPCM::DeviationCalChooseFun_NR
(int BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    switch (BeginCoordinate_Value)
    {
    case 1:Point_JudgeChange_NR1_CA(Line_Result, Ac_X, Ac_Y,Step );
        break;
    case 2:Point_JudgeChange_NR2_CA(Line_Result, Ac_X, Ac_Y, Step);
        break;
    case 3:Point_JudgeChange_NR3_CA(Line_Result, Ac_X, Ac_Y, Step);
        break;
    case 4:Point_JudgeChange_NR4_CA(Line_Result, Ac_X, Ac_Y, Step);
        break;
    case 5:Point_JudgeChange_NR1_CA(Line_Result, Ac_X, Ac_Y, Step);//x正半轴
        break;
    case 6:Point_JudgeChange_NR3_CA(Line_Result, Ac_X, Ac_Y, Step); // X负半轴
        break;
    case 7:Point_JudgeChange_NR2_CA(Line_Result, Ac_X, Ac_Y, Step); // Y正轴
        break;
    case 8:Point_JudgeChange_NR4_CA(Line_Result, Ac_X, Ac_Y, Step); // Y负半轴
        break;
    case 9:
        OutPutMsgToConsle(Warning_INFO,"void CircularArcPTPCM::DeviationCalChooseFun_NR(int& BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step):错误警告,该坐标是原点无需要处理");
        break;
    default:
        OutPutMsgToConsle(Critical_INFO,"void CircularArcPTPCM::DeviationCalChooseFun_NR(int& BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step):象限值存在错误!");
        break;
    }
}

void CircularArcPTPCM::DeviationCalChooseFun_SR
(int& BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)//
{
    switch (BeginCoordinate_Value)
    {
    case 1:Point_JudgeChange_SR1_CA(Line_Result, Ac_X, Ac_Y,Step);
        break;
    case 2:Point_JudgeChange_SR2_CA(Line_Result, Ac_X, Ac_Y, Step);
        break;
    case 3:Point_JudgeChange_SR3_CA(Line_Result, Ac_X, Ac_Y, Step);
        break;
    case 4:Point_JudgeChange_SR4_CA(Line_Result, Ac_X, Ac_Y, Step);
        break;
    case 5:Point_JudgeChange_SR4_CA(Line_Result, Ac_X, Ac_Y,Step);//x正半轴
        break;
    case 6:Point_JudgeChange_SR2_CA(Line_Result, Ac_X, Ac_Y, Step);//X负半轴
        break;
    case 7:Point_JudgeChange_SR1_CA(Line_Result, Ac_X, Ac_Y, Step);//Y正轴
        break;
    case 8:Point_JudgeChange_SR3_CA(Line_Result, Ac_X, Ac_Y, Step);//Y负半轴
        break;
    case 9:
        OutPutMsgToConsle(Warning_INFO,"void CircularArcPTPCM::DeviationCalChooseFun_SR(int& BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step):错误警告,该坐标是原点无需要处理");
        break;
    default:
        OutPutMsgToConsle(Critical_INFO,"void CircularArcPTPCM::DeviationCalChooseFun_SR(int& BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step):象限值存在错误!");
        break;
    }
}

void CircularArcPTPCM::CircleBegin()
{
    Step = 0; //步骤需要初始化，每轮计算结束，在下一轮里面会累计
    while(!(Ac_XYPoint.rx()== endPoint.rx() &&Ac_XYPoint.ry()== endPoint.ry()))
    {
        if (DirectionCircular)//逆时针
        {
            BeginCoordinate_Value = GetQuadrantJudge(Ac_XYPoint.rx(), Ac_XYPoint.ry());
            DeviationCalChooseFun_NR(BeginCoordinate_Value, Line_Result, Ac_XYPoint.rx(), Ac_XYPoint.ry(),Step);
        }
        else//顺时针
        {
            BeginCoordinate_Value = GetQuadrantJudge(Ac_XYPoint.rx(), Ac_XYPoint.ry());
            DeviationCalChooseFun_SR(BeginCoordinate_Value, Line_Result, Ac_XYPoint.rx(), Ac_XYPoint.ry(),Step);
        }
        moveToTargetPoint(Ac_XYPoint,true,shiftValue);//复原
        transitionCoordinate.push_back(Ac_XYPoint);//把临时Qpoint数据放在SL_ZD_array里面
        moveToTargetPoint(Ac_XYPoint,false,shiftValue);
    }

}


//根据偏差计算公式，并进行坐标进给
//根据偏差计算公式，并进行坐标进给,第1象限逆圆
void CircularArcPTPCM::Point_JudgeChange_NR1_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result - 2 * Ac_X + 1;
        Ac_X--;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result + 2 * Ac_Y + 1;
        Ac_Y++;
        //Cout--;
        Step++;
    }
}
//根据偏差计算公式，并进行坐标进给,第2象限逆圆
void CircularArcPTPCM::Point_JudgeChange_NR2_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result - 2 * Ac_Y + 1;
        Ac_Y--;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result - 2 * Ac_X + 1;
        Ac_X--;
        //Cout--;
        Step++;
    }
}
//根据偏差计算公式，并进行坐标进给,第3象限逆圆
void CircularArcPTPCM::Point_JudgeChange_NR3_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result + 2 * Ac_X + 1;
        Ac_X++;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result - 2 * Ac_Y + 1;
        Ac_Y--;
        //Cout--;
        Step++;
    }
}
//根据偏差计算公式，并进行坐标进给,第4象限逆圆
void CircularArcPTPCM::Point_JudgeChange_NR4_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result + 2 * Ac_Y + 1;
        Ac_Y++;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result + 2 * Ac_X + 1;
        Ac_X++;
        //Cout--;
        Step++;
    }
}


//根据偏差计算公式，并进行坐标进给,第1象限顺圆
void CircularArcPTPCM::Point_JudgeChange_SR1_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result - 2 * Ac_Y + 1;
        Ac_Y--;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result + 2 * Ac_X + 1;
        Ac_X++;
        //Cout--;
        Step++;
    }
}
//根据偏差计算公式，并进行坐标进给,第2象限顺圆
void CircularArcPTPCM::Point_JudgeChange_SR2_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result + 2 * Ac_X + 1;
        Ac_X++;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result + 2 * Ac_Y + 1;
        Ac_Y++;
        //Cout--;
        Step++;
    }
}
//根据偏差计算公式，并进行坐标进给,第3象限顺圆
void CircularArcPTPCM::Point_JudgeChange_SR3_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result + 2 * Ac_Y + 1;
        Ac_Y++;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result - 2 * Ac_X + 1;
        Ac_X--;
        //Cout--;
        Step++;
    }
}
//根据偏差计算公式，并进行坐标进给,第4象限顺圆
void CircularArcPTPCM::Point_JudgeChange_SR4_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step)
{
    if (Line_Result >= 0)//向-X方向进给
    {
        Line_Result = Line_Result - 2 * Ac_X + 1;
        Ac_X--;
        //Cout--;
        Step++;
    }
    else            //向+Y方向进给
    {
        Line_Result = Line_Result - 2 * Ac_Y + 1;
        Ac_Y--;
        //Cout--;
        Step++;
    }
}
