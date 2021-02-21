#ifndef ZHUDIANBIJIAO_H
#define ZHUDIANBIJIAO_H
#include "Algorithm/algorithm.h"

//每一段的直线插补，都是把起点平移到原点来计算每个点的坐标，最后在把每个店的坐标还原回没有平移的情况
class StraightLinePTPCM:public Algorithm
{
private:

    int Ac_X, Ac_Y;//实时坐标
    int Line_Result;//每一次计算的偏差判定值
    int Step;

    QPoint beginPoint;//算法计算开始坐标点
    QPoint endPoint;//算法计算终点

public:


public:
    StraightLinePTPCM();
    StraightLinePTPCM(QPoint begin, QPoint end);
    ~StraightLinePTPCM();

    virtual void algorithmEntry();//当前算法的入口
    virtual QVector<QPoint> algorithmExport();//算法的坐标输出

    //直线最初偏差计算公式
    void Deviation_Cal_SL();
//    QPoint returnAC_array();

    //根据象限值，选择执行的象限偏差计算函数
    void DeviationCalChooseFun(int& EndCoordinate_Value, int& Line_Result, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& step);

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
