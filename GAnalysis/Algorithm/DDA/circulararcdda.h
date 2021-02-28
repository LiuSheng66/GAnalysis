#ifndef CIRCULARARCDDA_H
#define CIRCULARARCDDA_H

#include "Algorithm/algorithm.h"

class CircularArcDDA:public Algorithm
{   

private:
    int Ac_X = 0, Ac_Y = 0;//实时坐标
    int End_X, End_Y;//终点坐标

    int Line_Result = 0;//偏差判定值
    int Step;//
    int Square;//半径的平方
    int DirectionCircular;//true代表逆时针；false代表顺圆；当三点共线时，默认false顺圆

    int Move_X, Move_Y; //平移值
    int BeginCoordinate_Value;//起点坐标象限值
    int EndCoordinate_Value;//终点坐标象限值

    int StepLength;//寄存器的步长
    long xRes, yRes; //寄存器溢出后余数
    int AccumulatorVolume;  //累加器容量
    int AccumulatorValue;//累加值
    int QuadrantReturn;//是否在同一象限，1是，0不是

    double OriginalAngle;//最开始三个点的夹角

    //因为算法都是按照原点来计算的，在输入其他起点时，都需要把起点平移到原点计算
    QPoint shiftValue;//平移值，point.x先X轴移动距离；point.y先Y轴移动距离
    QPoint Ac_XYPoint;//轨迹实时坐标

public:
    CircularArcDDA();
    ~CircularArcDDA();

    //接口函数
    //圆弧插补的入口函数
    virtual void algorithmEntry();


    //确定累加器的容量
    int DefineAccumulatorVolume(int Ac_X, int Ac_Y, int End_X, int End_Y);

    void CircleBegin();
    QVector<QPoint> algorithmExport();
};

#endif // CIRCULARARCDDA_H
