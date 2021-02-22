#ifndef MYCOMMAND_H
#define MYCOMMAND_H
#include"Command/gcommand.h"

#include<QMessageBox>
//在此类中使用自己的G代码指令规则，若使用其他的指令系统可以重新继承基类指令系统开发



class MyCommand : public GCommand
{
public:
    MyCommand(CodeEditor &inputPlainText);
    ~MyCommand();

    virtual void commandEntry();
    virtual QVector<CommandStatus *> commandExport();
    virtual bool isCorrectCMD(QString paragraphCmd);//按照各自的指令系统来判断是否存在指令错误的情况
    bool isNeedCoordinate();
    CodeType getCodeType(const QString &cmd);
    cmdNeedPara isNeedParameter(const CodeType &cmd);//指令是否需要坐标参数配合使用
    void cmdConvertPoint(CommandStatus &cmdStatus,QStringList cmdStrList);

    QString isCmdAnalysisFinish();

public:
    QString abnormalCauseStr;//指令解析系统最后异常而没有正常结束的原因

protected:
    CommandStatus* createCmdByParagraph(QString sentence);//把一段指令解析成一个结构体



private:
    bool isAnalysisFinish;//指令解析是否完成的标志

    int numCmdRow;//G代码的行号，用于报错时精准确定
};

#endif // MYCOMMAND_H
