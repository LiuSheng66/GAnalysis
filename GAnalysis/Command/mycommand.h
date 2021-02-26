#ifndef MYCOMMAND_H
#define MYCOMMAND_H
#include"Command/gcommand.h"

#include<QMessageBox>
//在此类中使用自己的G代码指令规则，若使用其他的指令系统可以重新继承基类指令系统开发
//输出的坐标都是绝对坐标系，如果是相对坐标系，则被转化为绝对坐标系


class MyCommand : public GCommand
{
public:
    MyCommand();
    MyCommand(CodeEditor &inputPlainText);
    ~MyCommand();

    virtual void commandEntry();
    virtual QVector<CommandStatus *> commandExport();
    virtual bool isCorrectCMD(QString paragraphCmd);//按照各自的指令系统来判断是否存在指令错误的情况
    bool isNeedCoordinate();
    CodeType getCodeType(const QString &cmd);
    cmdNeedPara isNeedParameter(const CodeType &cmd);//指令是否需要坐标参数配合使用
    void cmdConvertPoint(CommandStatus &cmdStatus,QStringList cmdStrList);
    //把解析后的指令的坐标转化为绝对坐标系（如果已经是绝对坐标则不转化）
    void holdPointAbsolute();



protected:
    CommandStatus* createCmdByParagraph(QString sentence);//把一段指令解析成一个结构体



private:

    int numCmdRow;//G代码的行号，用于报错时精准确定
};

#endif // MYCOMMAND_H
