#ifndef ZHUDIANBIJIAO_H
#define ZHUDIANBIJIAO_H
#include "Algorithm/algorithm.h"
#include<QVector>

class StraightLinePTPCM:public Algorithm
{
private:

    int Move_X, Move_Y; //平移值
    int Ac_X = 0, Ac_Y =0;//实时坐标
    int Line_Result = 0;//偏差判定值
    int Step;

    QPointF beginPoint;
    QPointF endPoint;
    QVector<QPoint> AllCoordinate_array;
public:


public:
    StraightLinePTPCM();
    ~StraightLinePTPCM();

    virtual void algorithmEntry();//当前算法的入口

    //直线最初偏差计算公式
    void Deviation_Cal_SL();
//    QPoint returnAC_array();

    //根据象限值，选择执行的象限偏差计算函数
    void DeviationCalChooseFun(int& EndCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //象限一，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL1(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //象限二，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL2(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //象限三，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL3(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //象限四，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL4(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //x轴，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL5(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //Y轴，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL6(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //Y轴，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL7(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

    //Y轴，根据偏差值计算，下一步的偏差值计算并完成坐标进给,参数：偏差值，象限值，实时坐标值X,Y,终点坐标值X,Y,剩余步数
    void Point_JudgeChange_SL8(int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& Cout);

};

#endif // ZHUDIANBIJIAO_H
