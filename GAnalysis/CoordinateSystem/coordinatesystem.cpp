#include "coordinatesystem.h"

CoordinateSystem::CoordinateSystem():
    pulseEquivalent(0.01)//初始化脉冲当量为0.01mm，根据需要可以更改
{

}

int CoordinateSystem::distanceToPulses(double distance)
{
    return distance/pulseEquivalent;//返回步进电机所需的脉冲数
}

double CoordinateSystem::pulsesToDistance(int pulses)
{
    return pulses*pulseEquivalent;//返回步进电机执行脉冲数后在机床实际坐标系中表现出来的实际位移（mm）
}


