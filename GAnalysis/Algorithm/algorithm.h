#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<QPoint>
#include<QVector>
#include"Global/global.h"

//算法计算的基本单位为步进电机的步数，为int型，而实际的坐标系统为double型
//本程序算法全是以脉冲数为单位计算
class Algorithm
{
public:
    Algorithm();
    ~Algorithm();

    virtual void algorithmEntry()=0;//接口，实现多态，实现不同的具体算法
    virtual QVector<QPoint> algorithmExport();//算法的坐标输出
    void algorithmFrame(Algorithm *begin);//框架，调用不同的算法，实现多态

    void setInitPoint(QPoint begin,QPoint end);//手动设置算法计算的起始点

    void testAlgorithmExport(QVector<QPoint> temCoordinate);//用于测试，把当前段的计算的临时坐标输出到消息框
    QPoint OtherToOriginalPoint(QPoint &point);//把所给坐标平移到原点，并返回平移值
    int GetQuadrantJudge(double Point_X, double Point_Y);//得到当前点的所在象限
public:
//    QPoint beginPoint;//起点坐标
//    QPoint endPoint;//结束坐标
//     int Begin_X, Begin_Y;//起点坐标
//     int End_X, End_Y;//终点坐标

    QPoint beginPoint;//算法计算开始坐标点
    QPoint endPoint;//算法计算终点
public:
     QVector<QPoint> transitionCoordinate;//算法计算线段得到的每个坐标的集合
};

#endif // ALGORITHM_H
