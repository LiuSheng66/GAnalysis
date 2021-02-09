#ifndef MYHIGHLIGHTER_H
#define MYHIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>
class MyHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    MyHighLighter(QTextDocument *parent = 0);//构造函数传一个 QTextDocument 对象 给父类

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;//重写父类这个函数 自动调用

private:
    struct HighlightingRule//语法规则结构体，包含正则表达式模式串和匹配的样式
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;//规则的集合，可以定义多个高亮规则

//    QRegExp commentStartExpression;//注释的高亮，使用highliangBlock()匹配，下文提到
//    QRegExp commentEndExpression;

    QTextCharFormat commandFormat;//高亮样式，指令，顾名思义
//    QTextCharFormat classFormat;
//    QTextCharFormat singleLineKey;
//    QTextCharFormat singleLineValue;
    QTextCharFormat XYIJFormat;  //XYIJ坐标
//    QTextCharFormat multiLineCommentFormat;
//    QTextCharFormat quotationFormat;
//    QTextCharFormat functionFormat;
};
#endif // MYHIGHLIGHTER_H
