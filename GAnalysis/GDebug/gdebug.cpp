#include "gdebug.h"

GDebug::GDebug()
{

}

GDebug::~GDebug()
{

}

void GDebug::GDebugDispaly(QString strDisplay, QTextEdit qTextptr)
{
//    emit debugChange(strDisplay);
    qTextptr.append(strDisplay);
}
