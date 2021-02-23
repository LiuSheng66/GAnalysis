#ifndef ORDERRULES_H
#define ORDERRULES_H

/*
 //*******************  举个例子  *****************************
G21//米制  G20-英制
G91//相对坐标  G90-绝对坐标
G99 X1.00 Y0.00 I0 J0 //比例因子1 旋转角度0 横向无镜像 纵向无镜像
G41 //左割缝补偿  G42右割缝补偿
M07 //切割开始
G01 X0.00 Y5.000 //y走5mm
G01 X0.00 Y100.000 //y走100mm
G01 X50.000 Y0.00 //x走50mm
G01 X0.00 Y-100.000 //y退100m，
G01 X-50.000 Y0.00 //x退50mm
G01 X-5.000 Y0.00 //x退5mm
M08 //切割结束
G40 //取消割缝补偿
M02 //程序结束

*/

//此系统的指令系统规则
//指令的类型
enum CodeType{
    G99_CODE, //部件选项
    RELATIVE_CODE,//相对坐标
    ABSOLUTE_CODE,//绝对坐标
    INCH_CODE,//英制
    METER_CODE,//米制
    L_KERF_CODE,//左割缝补偿
    R_KERF_CODE,//右割缝补偿
    CANCEL_KERF_CODE,//割缝补偿取消
    EMPTY_QUICKMOVE_CODE,//空车快移位移
    STR_LINE_WORK_CODE,//直线切割
    CW_ARC_WORK_CODE,//顺时针圆弧
    ACW_ARC_WORK_CODE,//逆时针圆弧
    FIRE_BEGIN_CODE,//切割开始
    FIRE_END_CODE,//切割结束
    FIRE_CLOSE_CODE,//程序结束
    NO_USE_CODE,//other
};

//系统的类型
enum systemType{
    RELATIVE_CSYS,//相对坐标系
    ABSOLUTE_CSYS//绝对坐标系
};

//坐标单位
enum lengthUnit{
    INCH_LENGTH,//英制
    METER_LENGTH,//米制
};

//补偿
enum Offset{
    L_OFFSET,//左切割补偿
    R_OFFSET,//右切割补偿
    CANALE_OFFSET//取消切割补偿
};

//绘画的线型
enum lineType{
    STR_LINE,//直线
    ARC_LINE //圆弧
};

//指令是否需要坐标参数配合使用
enum cmdNeedPara{
    NEED_PARA,//需要参数
    DISNEED_PARA,//不需要参数
    REGARDLESS_PARA//有没有参数都可以执行
};


class gPoint
{
public:
    gPoint();
    ~gPoint();
public:
    int x;
    int y;
    int i;
    int j;
};

//指令结构体：储存指令代表的信息
class CommandStatus
{
public:
    CommandStatus();
    ~CommandStatus();

public:
    bool isCorrect;//指令是否正确,功能还没做，先初始化为true
    systemType coordinate_System;//基于何种坐标系计算,默认使用绝对坐标系
    lengthUnit unitLen;//长度单位
    Offset coordinateOffset;//坐标补偿，默认关闭坐标补偿
    lineType line;//指令含义
    bool isNeedCoordinate;//指令是否需要坐标信息
    bool isNeedFire;//是否需要切割工作
    gPoint point;//坐标信息
};


#endif // ORDERRULES_H
