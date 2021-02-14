#include"Command/mycommandrules.h"



CommandStatus::CommandStatus():
     isCorrect(true),                   //返回指令是否正确,功能还没做，先初始化为true
     coordinate_System(ABSOLUTE_CSYS),  //基于何种坐标系计算,默认使用绝对坐标系
     unitLen(METER_LENGTH),             //默认米制
     coordinateOffset(CANALE_OFFSET) ,   //坐标补偿，默认关闭坐标补偿
     isNeedFire(false),                   //默认不执行画图（即工作）
     isNeedCoordinate(false)               //默认不需要坐标配合指令
{

}

CommandStatus::~CommandStatus()
{

}


gPoint::gPoint():
    x(0),
    y(0),
    i(0),
    j(0)
{

}

gPoint::~gPoint()
{

}
