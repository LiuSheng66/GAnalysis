#ifndef ALGORITHM_H
#define ALGORITHM_H
#include<QPoint>
#include<QVector>
#include"Global/global.h"
#include"Command/mycommandrules.h"

//算法计算的基本单位为步进电机的步数，为int型，而实际的坐标系统为double型
//本程序算法全是以脉冲数为单位计算
class Algorithm
{
public:
    Algorithm();
    virtual ~Algorithm();

    virtual void algorithmEntry()=0;//接口，实现多态，实现不同的具体算法
    virtual QVector<QPoint> algorithmExport();//算法的坐标输出
    void algorithmFrame(Algorithm *begin);//框架，调用不同的算法，实现多态
    //初始化函数
    //QPoint begin, QPoint end,CodeType code:前面三个参数是直线和圆弧算法需要的参数
    // QPoint center:只有圆弧算法需要
    void setInitPoint(QPoint begin, QPoint end, CodeType mycode=NO_USE_CODE, QPoint center=QPoint(0,0));//手动设置算法计算的起始点

    void testAlgorithmExport(QVector<QPoint> temCoordinate);//用于测试，把当前段的计算的临时坐标输出到消息框
    void moveToTargetPoint (QPoint &point,bool revertFlag,QPoint moveValue);//按照所给的平移标识符，把相关点按照偏差值平移
    void moveToTargetPoint(int &Ac_X, int &Ac_Y, bool revertFlag, QPoint moveValue);
    void revertPointToMove(QPoint &point,QPoint shift);//按照类里面存在的平移值把当前输入点还原到平移前的坐标
    int GetQuadrantJudge(double Point_X, double Point_Y);//得到当前点的所在象限
private:

public:
//    QPoint beginPoint;//起点坐标
//    QPoint endPoint;//结束坐标
//     int Begin_X, Begin_Y;//起点坐标
//     int End_X, End_Y;//终点坐标


    QPoint beginPoint;//算法计算开始坐标点
    QPoint endPoint;//算法计算终点
    CodeType inCode;//指令的类型
    QPoint centerPoint;//算法计算的圆心（注意：只有圆弧的算法会用到圆心，起点和终点直线和圆弧算法共用）
public:
    QVector<QPoint> transitionCoordinate;//算法计算线段得到的每个坐标的集合
    //禁止圆心、起点、终点坐标三个点，两两相等，并判断是否符合圆弧，并返回半径的平方
    bool JudgeIsCircularArc(const int Begin_X,const int Begin_Y,const int End_X,const int End_Y,const int Center_X,const int Center_Y);

    //判断根据起点，终点判断圆弧是顺时针还是逆时针
    //默认圆心在原点,返回值1代表逆时针；0代表顺圆；当三点共线时，默认0顺圆
    int JudgeCircularArc_Direction(int Center_X, int Center_Y, int Begin_X, int Begin_Y, int End_X, int End_Y);

};

#endif // ALGORITHM_H
