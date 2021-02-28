#ifndef STRAIGHTLINEDIGIT_H
#define STRAIGHTLINEDIGIT_H

#include "Algorithm/algorithm.h"

class StraightLineDDA:public Algorithm
{

private:

    int  Step;//累加的第几步
    int StepLength;//寄存器的步长
//    int ChooseWayRunSL;//

    long XRes, YRes; //寄存器溢出后余数
    int AccumulatorVolume;  //累加器容量
    int AccumulatorValue;//累加值

    //因为算法都是按照原点来计算的，在输入其他起点时，都需要把起点平移到原点计算
    QPoint shiftValue;//平移值，point.x先X轴移动距离；point.y先Y轴移动距离
    QPoint Ac_XYPoint;//轨迹实时坐标


public:
    StraightLineDDA();
    StraightLineDDA(QPoint begin, QPoint end);
    ~StraightLineDDA();

    //接口函数
    virtual void algorithmEntry();
    virtual QVector<QPoint> algorithmExport();//算法的坐标输出

    //根据象限值，选择执行的象限偏差计算函数
    void DeviationCalChooseFun(int& EndCoordinate_Value, int& AccumulatorVolume, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //第一象限坐标判断进给
    void Point_JudgeChange_SL1(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //第二象限坐标判断进给
    void Point_JudgeChange_SL2(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //第三象限坐标判断进给
    void Point_JudgeChange_SL3(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //第四象限坐标判断进给
    void Point_JudgeChange_SL4(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //X正半轴
    void Point_JudgeChange_SL5(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //X负半轴
    void Point_JudgeChange_SL6(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //Y正半轴
    void Point_JudgeChange_SL7(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);

    //Y负半轴
    void Point_JudgeChange_SL8(int& AccumulatorVolume, long& XRes, long& YRes, int& Ac_X, int& Ac_Y, int& End_X, int& End_Y, int& StepLength, int& Step);


};

#endif // STRAIGHTLINEDIGIT_H
