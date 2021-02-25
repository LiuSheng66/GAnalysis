#include "algorithm.h"
#include<math.h>
//所有算法的坐标输入点，从此基类开始
Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}

QVector<QPoint> Algorithm::algorithmExport()
{
    transitionCoordinate.resize(0);
    return transitionCoordinate;
}

void Algorithm::algorithmFrame(Algorithm *begin)
{
    begin->algorithmEntry();
}

void Algorithm::setInitPoint(QPoint begin, QPoint end, QPoint center)
{
    beginPoint=begin;
    endPoint=end;
    centerPoint=center;
}

void Algorithm::testAlgorithmExport(QVector<QPoint> temCoordinate)
{
    //把临时坐标数据输出到输出窗口
    QPoint *temPoint=new QPoint;
    for(int i=0;i<temCoordinate.size();i++)
    {
        *temPoint=temCoordinate.at(i);
        OutPutMsgToConsle(Information_INFO,QString("QPoint: (%1,%2)").arg(temPoint->rx()).arg(temPoint->ry()));
    };
}

QPoint Algorithm::OtherToOriginalPoint(QPoint &point)
{
    QPoint ZeroBias=QPoint(0,0);
    if (point.rx() == 0 && point.ry() == 0)
    {
    //	cout << "此坐标已经是原点坐标，不需要再转化到原点\n";
    }
    ZeroBias.rx() = -point.rx();
    ZeroBias.ry() = -point.ry();

    point.rx() = point.ry() = 0;//把当前点置零
        return ZeroBias;//返回按照当前点置零，其他点需要平移的坐标
}

int Algorithm::GetQuadrantJudge( double Point_X , double Point_Y)
 {   
        if  ((Point_X > 0) && (Point_Y > 0))
         return 1;
    else if ((Point_X > 0) && (Point_Y < 0))
         return 4;
    else if ((Point_X > 0) && (Point_Y == 0))
         return 5;//x正半轴
    else if ((Point_X < 0) && (Point_Y > 0))
         return 2;
    else if ((Point_X < 0)&&  (Point_Y < 0))
         return 3;
    else if ((Point_X < 0) && (Point_Y == 0))
         return 6; //x负半轴
    else if ((Point_X == 0) && (Point_Y > 0))
         return 7; //Y正半轴
    else if ((Point_X == 0) && (Point_Y < 0))
         return 8; //Y负半轴
    else if ((Point_X == 0) && (Point_Y == 0))
         return 9; //原点
    else OutPutMsgToConsle(Critical_INFO,"int Algorithm::GetQuadrantJudge( double Point_X , double Point_Y):坐标象限判断出现异常情况，没有得到正常象限值");
 }

bool Algorithm::JudgeIsCircularArc(const int Begin_X,const int Begin_Y,const int End_X,const int End_Y,const int Center_X,const int Center_Y)
{
     //如果起点和终点分别到圆心的举例相同，则可以构成一个圆
     if((Begin_X-Center_X)*(Begin_X-Center_X)+(Begin_Y-Center_Y)*(Begin_Y-Center_Y)==(End_X-Center_X)*(End_X-Center_X)+(End_Y-Center_Y)*(End_Y-Center_Y))
     {
         return true;//可以构成一个圆
     }else
     {
         OutPutMsgToConsle(Critical_INFO,"三个点构成圆弧检测: 此组合不能构成一个圆，请检查点的坐标.");
         return false;
     };
}

int Algorithm::JudgeCircularArc_Direction(int Center_X, int Center_Y,int Begin_X, int Begin_Y, int End_X, int End_Y)
{
    int Direction=1;
    while (Center_X || Center_Y || Begin_X || Begin_Y || End_X || End_Y)
    {
        int p = (Begin_X - Center_X) * (End_Y - Center_Y) - (Begin_Y - Center_Y) * (End_X - Center_X);
        if (p > 0)
        {
//			cout << "逆时针" << endl;
            Direction = 1;
            break;
        }
        else if (p < 0)
        {
//			cout << "顺时针" << endl;
            Direction = 0;
            break;
        }
        else
        {
//			cout << "三点共线，按顺时针计算";
            Direction = 0;//不知道填什么
            break;
        }
    }
    return Direction;
}
