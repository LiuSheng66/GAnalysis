#include "circulararcdda.h"
#include<QtMath>


CircularArcDDA::CircularArcDDA()
{
    //步长默认为1
    StepLength=1;
}

CircularArcDDA::~CircularArcDDA()
{

}

//直线插补的入口函数
void CircularArcDDA::algorithmEntry()
{
    QString strLine = QString("得到圆弧的坐标信息:(%1 ,%2) -> (%3 ,%4) ,圆心:(%5 ,%6)").arg(beginPoint.rx()).arg(beginPoint.ry()).arg(endPoint.rx()).arg(endPoint.ry()).arg(centerPoint.rx()).arg(centerPoint.ry());
    OutPutMsgToConsle(Running_INFO,"圆弧--逐点比较法: 连续切削算法计算  ** 开始  ** :"+strLine);

    //判断能否构成圆弧
    if( !JudgeIsCircularArc( beginPoint.rx(), beginPoint.ry(), endPoint.rx(), endPoint.ry(),centerPoint.rx(), centerPoint.ry())){return;};
    Square=(beginPoint.rx()-centerPoint.rx())*(beginPoint.rx()-centerPoint.rx())+(beginPoint.ry()-centerPoint.ry())*(beginPoint.ry()-centerPoint.ry());
    //判断顺逆圆弧
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

    //计算起点的所在象限
    BeginCoordinate_Value = GetQuadrantJudge(Ac_XYPoint.rx(), Ac_XYPoint.ry());
    EndCoordinate_Value = GetQuadrantJudge(endPoint.rx(), endPoint.ry());

    //AccumulatorVolume = int(pow(2, DefineAccumulatorVolume( Ac_X, Ac_Y, End_X,End_Y)));//溢出基值 ,也可取为 pow(2,n)
    AccumulatorVolume = (int)sqrt((double)Square);
    CircleBegin();
    OutPutMsgToConsle(Running_INFO,"圆弧--DDA: 连续切削算法计算  ** 结束  ** :总共步数："+QString::number(Step));
}

QVector<QPoint> CircularArcDDA::algorithmExport()
{
    return transitionCoordinate;//返回实际坐标值（按照步进电机的脉冲数为单位）
}

void CircularArcDDA::CircleBegin()
{
    Step = 0; //步骤需要初始化，每轮计算结束，在下一轮里面会累计
    int xEnable = 0, yEnable = 0;

    //int judge = 1;
    while (!(Ac_XYPoint.rx() == endPoint.rx() && Ac_XYPoint.ry()==endPoint.ry() ))//检测终点
    {
        if (Ac_XYPoint.rx() != endPoint.rx())
        {
            xRes += fabs(Ac_XYPoint.ry());
        }
        if (Ac_XYPoint.rx() == endPoint.rx() && ((Ac_XYPoint.ry() * endPoint.ry())<0))
        {
            xRes += fabs(Ac_XYPoint.ry());
        }
        if (Ac_XYPoint.ry() != endPoint.ry())
        {
            yRes += fabs(Ac_XYPoint.rx());
        }
        if (Ac_XYPoint.ry() == endPoint.ry() && ((Ac_XYPoint.rx() * endPoint.rx()) < 0))
        {
            yRes += fabs(Ac_XYPoint.rx());
        }

        if (xRes >= AccumulatorVolume )//(&& fabs(Ac_XYPoint.rx()) <= sqrt(Square))
        {
            xRes = xRes % AccumulatorVolume;
            xEnable = 1;
        }
        if (yRes >= AccumulatorVolume )//(&& fabs(Ac_XYPoint.ry()) <= sqrt(Square))
        {
            yRes = yRes % AccumulatorVolume;
            yEnable = 1;
        }

        if (DirectionCircular == 1)//逆圆插补
        {

            BeginCoordinate_Value =  GetQuadrantJudge(Ac_XYPoint.rx(), Ac_XYPoint.ry());
            if (yEnable == 1)//xRes溢出， y轴进给
            {
                switch (BeginCoordinate_Value)
                {
                case 1:if (fabs(Ac_XYPoint.ry()) < sqrt(Square)) Ac_XYPoint.ry() += StepLength; break;//防止 y轴超出半径范围
                case 2:Ac_XYPoint.ry() -= StepLength; break;
                case 3:if (fabs(Ac_XYPoint.ry()) < sqrt(Square)) Ac_XYPoint.ry() -= StepLength; break;//防止 y轴超出半径范围
                case 4:Ac_XYPoint.ry() += StepLength; break;
                case 5:Ac_XYPoint.ry() += StepLength; break;
                case 6:Ac_XYPoint.ry() -= StepLength; break;
                case 7:Ac_XYPoint.ry() -= StepLength; break;
                case 8:Ac_XYPoint.ry() += StepLength; break;
                case 9:OutPutMsgToConsle(Critical_INFO,"错误！在原点");
                    break;
                }
            }
            if (xEnable == 1)//yRes溢出， x轴进给
            {
                switch (BeginCoordinate_Value)
                {
                case 1:Ac_XYPoint.rx() -= StepLength; break;
                case 2:if (fabs(Ac_XYPoint.rx()) < sqrt(Square)) Ac_XYPoint.rx() -= StepLength; break;//防止 x轴超出半径范围
                case 3:Ac_XYPoint.rx() += StepLength; break;
                case 4:if (fabs(Ac_XYPoint.rx()) < sqrt(Square)) Ac_XYPoint.rx() += StepLength; break;//防止 x轴超出半径范围
                case 5:Ac_XYPoint.rx()-= StepLength; break;
                case 6:Ac_XYPoint.rx() += StepLength; break;
                case 7:Ac_XYPoint.rx() -= StepLength; break;
                case 8:Ac_XYPoint.rx() += StepLength; break;
                case 9:OutPutMsgToConsle(Critical_INFO,"错误！在原点"); break;
                }
            }
        }
        else//顺圆插补
        {
            BeginCoordinate_Value = GetQuadrantJudge(Ac_XYPoint.rx(), Ac_XYPoint.ry());
            if (yEnable == 1)//xRes溢出， y轴进给
            {
                switch (BeginCoordinate_Value)
                {
                case 1:Ac_XYPoint.ry() -= StepLength; break;
                case 2:if (fabs(Ac_XYPoint.ry()) < sqrt(Square)) Ac_XYPoint.ry() += StepLength; break;//防止 y轴超出半径范围
                case 3:Ac_XYPoint.ry() += StepLength; break;
                case 4:if (fabs(Ac_XYPoint.ry()) < sqrt(Square)) Ac_XYPoint.ry() -= StepLength; break;//防止 y轴超出半径范围
                case 5:Ac_XYPoint.ry() -= StepLength; break;
                case 6:Ac_XYPoint.ry() += StepLength; break;
                case 7:Ac_XYPoint.ry() -= StepLength; break;
                case 8:Ac_XYPoint.ry() += StepLength; break;
                case 9:OutPutMsgToConsle(Critical_INFO,"错误！在原点");  break;
                }
            }
            if (xEnable == 1)//yRes溢出， x轴进给
            {
                switch (BeginCoordinate_Value)
                {
                case 1:if (fabs(Ac_XYPoint.rx()) < sqrt(Square)) Ac_XYPoint.rx() += StepLength; break;//防止 x轴超出半径范围
                case 2:Ac_XYPoint.rx() += StepLength; break;
                case 3:if (fabs(Ac_XYPoint.rx()) < sqrt(Square)) Ac_XYPoint.rx() -= StepLength; break;//防止 x轴超出半径范围
                case 4:Ac_XYPoint.rx() -= StepLength; break;
                case 5:Ac_XYPoint.rx() -= StepLength; break;
                case 6:Ac_XYPoint.rx() += StepLength; break;
                case 7:Ac_XYPoint.rx() += StepLength; break;
                case 8:Ac_XYPoint.rx() -= StepLength; break;
                case 9:OutPutMsgToConsle(Critical_INFO,"错误！在原点"); break;
                }
            }
        }
        //judge = (fabs(Ac_XYPoint.rx() - End_X) >= StepLength || fabs(Ac_XYPoint.ry() - End_Y) >= StepLength);
        if (xEnable || yEnable)//判断并进行进给运动
        {
            Step++;
            moveToTargetPoint(Ac_XYPoint,true,shiftValue);
            transitionCoordinate.push_back(Ac_XYPoint);
            moveToTargetPoint(Ac_XYPoint,false,shiftValue);
            xEnable = yEnable = 0;
        }
    }

}


int CircularArcDDA::DefineAccumulatorVolume(int Ac_X, int Ac_Y,int End_X ,int End_Y)
{
    int n = 0;
    int i = 1;
    while (i)
    {
        if (Ac_X > pow(2, n) || Ac_Y > pow(2, n) || End_X > pow(2, n) || End_Y > pow(2, n))
        {
            n++;
            i = 1;
        }
        else
        {
            i = 0;
        }
    }
    return n;
}

