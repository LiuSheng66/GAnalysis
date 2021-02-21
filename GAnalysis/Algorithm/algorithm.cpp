#include "algorithm.h"

Algorithm::Algorithm()
{

}

Algorithm::~Algorithm()
{

}

QVector<QPoint> Algorithm::algorithmExport()
{
    AllCoordinate_array.resize(0);
    return AllCoordinate_array;
}

void Algorithm::algorithmBengin(Algorithm *begin)
{
    begin->algorithmEntry();
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
