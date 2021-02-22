#ifndef GDEBUG_H
#define GDEBUG_H
#include<QTextEdit>

class GDebug : public QTextEdit
{
public:
    GDebug();
    ~GDebug();

     void GDebugDispaly(QString strDisplay,QTextEdit qTextptr);

signals:
     void debugChange(QString str);//自定义信号，输出栏内容改变信号，str代表需要显示的输出内容

private:

};

#endif // GDEBUG_H
