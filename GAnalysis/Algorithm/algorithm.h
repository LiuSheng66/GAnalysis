#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<QPoint>

class Algorithm
{
public:
    Algorithm();
    ~Algorithm();

    virtual void algorithmEntry()=0;//接口，实现多态，实现不同的具体算法
    void algorithmBengin(Algorithm *begin);//框架，调用不同的算法，实现多态



    QPointF OtherToOriginalPoint(QPointF &pointF);
    int GetQuadrantJudge(double Point_X, double Point_Y);//得到当前点的所在象限
protected:
    QPoint beginPoint;//起点坐标
    QPoint endPoint;//结束坐标

     int Begin_X, Begin_Y;//起点坐标
     int End_X, End_Y;//终点坐标
};

#endif // ALGORITHM_H
