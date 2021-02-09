#ifndef MYCOMMAND_H
#define MYCOMMAND_H
#include"Command/gcommand.h"
#include"Command/mycommandrules.h"

//在此类中使用自己的G代码指令规则，若使用其他的指令系统可以重新继承基类指令系统开发



class MyCommand : public GCommand
{
public:
    MyCommand(CodeEditor &inputPlainText);
    ~MyCommand();

    virtual void implementCommand();

    virtual bool isCorrectCMD();//按照各自的指令系统来判断是否存在指令错误的情况
    bool isNeedCoordinate();
    CodeType getCodeType(const QString &cmd);
    cmdNeedPara isNeedParameter(const CodeType &cmd);//指令是否需要坐标参数配合使用
protected:
    CommandStatus createCmdByParagraph(QString sentence);//把一段指令解析成一个结构体
};

#endif // MYCOMMAND_H
