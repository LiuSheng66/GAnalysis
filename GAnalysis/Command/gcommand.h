#ifndef COMMAND_H
#define COMMAND_H
#include<QString>
#include<QTextDocument>
#include<syntax/codeeditor.h>
#include"Command/mycommandrules.h"
#include"Global/global.h"




class GCommand
{
public:
    GCommand();
    GCommand(CodeEditor &commandPlainText);
    virtual ~GCommand();

    virtual void commandEntry()=0;//指令解析的入口
    virtual QVector<CommandStatus*> commandExport();//指令解析的输出
    void commandFrame(GCommand *begin);//指令解析的框架

    void setInCommandText(CodeEditor &inputPlainText);

    void findCommand();
    void getCommand();
    virtual bool isCorrectCMD();//按照各自的指令系统来判断是否存在指令错误的情况
    //根据字符串ch分段、分单词
    QStringList splitBy(const QString &text,QString keyword);
    QStringList splitBySentence(const QString &inText);
    QStringList splitByWord(QString &inText);
    bool PreProcces(QString &textEdit); //预处理,小写改大写，前后文的空格删除
    double coordinateStrToDouble(const QString coordinate);//把指令中的字符类的坐标数据转化为double型的数字,精度6位有效数字XXXX.XX
protected:

    CodeEditor *commandPlainText;//导入需要处理指令
    QString commandStrTotal;//导入的总指令
private:

    QStringList sentenceList;//按照换行符分割字符
    QStringList wordCommandList;//按照空格分割字符
public:
    QVector<CommandStatus*> cmdFinal;//指令解析完成后保存的指令具体信息


};

#endif // COMMAND_H
