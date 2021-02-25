#ifndef CIRCULARARCPTPCM_H
#define CIRCULARARCPTPCM_H
#include "Algorithm/algorithm.h"

class CircularArcPTPCM : public Algorithm
{   
private:

    int Ac_X = 0, Ac_Y = 0;//实时坐标
    int Line_Result = 0;//偏差判定值
    int Step;
    bool DirectionCircular;//true代表逆时针；false代表顺圆；当三点共线时，默认false顺圆

    QPointF nowBias;//坐标平移后的移动值

    int BeginCoordinate_Value;//起点坐标象限值
    int EndCoordinate_Value;//终点坐标象限值


public:
    QVector<QPoint> transitionCoordinate;//算法计算线段得到的每个坐标的集合

public:
    CircularArcPTPCM();
    CircularArcPTPCM(QPoint begin, QPoint end, QPoint center);
    ~CircularArcPTPCM();

    //直线插补的入口函数
    virtual void algorithmEntry();

    QVector<QPoint> algorithmExport();

    //根据象限值，选择相应的坐标偏差进给函数
    void DeviationCalChooseFun_SR(int& BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);
    void DeviationCalChooseFun_NR(int BeginCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);

    //根据偏差计算公式，并进行坐标进给,第1象限逆圆
    void Point_JudgeChange_NR1_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);
    //根据偏差计算公式，并进行坐标进给,第2象限逆圆
    void Point_JudgeChange_NR2_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);
    //根据偏差计算公式，并进行坐标进给,第3象限逆圆
    void Point_JudgeChange_NR3_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);
    //根据偏差计算公式，并进行坐标进给,第4象限逆圆
    void Point_JudgeChange_NR4_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);

    //根据偏差计算公式，并进行坐标进给,第1象限顺圆
    void Point_JudgeChange_SR1_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);
    //根据偏差计算公式，并进行坐标进给,第2象限顺圆
    void Point_JudgeChange_SR2_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);
    //根据偏差计算公式，并进行坐标进给,第3象限顺圆
    void Point_JudgeChange_SR3_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);
    //根据偏差计算公式，并进行坐标进给,第4象限顺圆
    void Point_JudgeChange_SR4_CA(int& Line_Result, int& Ac_X, int& Ac_Y, int& Step);

    void CircleBegin();




};

#endif // CIRCULARARCPTPCM_H
