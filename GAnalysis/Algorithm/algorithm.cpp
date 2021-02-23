#include "algorithm.h"

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

void Algorithm::setInitPoint(QPoint begin, QPoint end)
{
    beginPoint=begin;
    endPoint=end;
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

QPoint Algorithm::OtherToOriginalPoint(QPoint &point)//double Point_X,double Point_Y
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
    if ((Point_X > 0) && (Point_Y > 0))
         return 1;
    else if ((Point_X < 0) && (Point_Y > 0))
         return 2;
    else if ((Point_X < 0) && (Point_Y < 0))
         return 3;
    else if((Point_X > 0) && (Point_Y < 0))
         return 4;
    else if ((Point_Y == 0)&& (Point_X > 0))
         return 5; //x正半轴
    else if((Point_Y == 0) && (Point_X < 0))
         return 6; //x负半轴
    else if ((Point_X == 0) && (Point_Y > 0))
         return 7; //Y正半轴
    else if ((Point_X == 0) && (Point_Y < 0))
         return 8; //Y负半轴
    else
         return 9; //原点

 }

