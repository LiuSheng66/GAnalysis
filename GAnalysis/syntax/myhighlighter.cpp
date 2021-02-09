#include "myhighlighter.h"
#include<QDebug>
MyHighLighter::MyHighLighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    commandFormat.setForeground(Qt::darkBlue);//设定关键词的高亮样式
    commandFormat.setFontWeight(QFont::DemiBold);
    commandFormat.setFontPointSize(14);
    QStringList commandPatterns;//关键词集合,关键都以正则表达式表示 下面的可以改为我们想要的关键词
    commandPatterns <<"\\bG00\\b"<<"\\bG01\\b"<<"\\bG02\\b"<<"\\bG03\\b"<<"\\bG04\\b"<<"\\bG05\\b"<<"\\bG06\\b"<<"\\bG07\\b"<<"\\bG08\\b"<<"\\bG09\\b"<<"\\bG10\\b"
                    <<"\\bG16\\b"<<"\\bG17\\b"<<"\\bG18\\b"<<"\\bG19\\b"<<"\\bG20\\b"<<"\\bG21\\b"<<"\\bG22\\b"<<"\\bG220\\b"<<"\\bG23\\b"<<"\\bG230\\b"<<"\\bG24\\b"
                    <<"\\bG25\\b"<<"\\bG26\\b"<<"\\bG30\\b"<<"\\bG31\\b"<<"\\bG32\\b"<<"\\bG33\\b"<<"\\bG34\\b"<<"\\bG35\\b"<<"\\bG40\\b"<<"\\bG41\\b"<<"\\bG42\\b"
                    <<"\\bG43\\b"<<"\\bG44\\b"<<"\\bG45\\b"<<"\\bG46\\b"<<"\\bG47\\b"<<"\\bG48\\b"<<"\\bG49\\b"<<"\\bG50\\b"<<"\\bG51\\b"<<"\\bG52\\b"<<"\\bG53\\b"
                    <<"\\bG54\\b"<<"\\bG55\\b"<<"\\bG56\\b"<<"\\bG57\\b"<<"\\bG58\\b"<<"\\bG59\\b"<<"\\bG60\\b"<<"\\bG61\\b"<<"\\bG62\\b"<<"\\bG63\\b"<<"\\bG68\\b"
                    <<"\\bG69\\b"<<"\\bG70\\b"<<"\\bG71\\b"<<"\\bG74\\b"<<"\\bG75\\b"<<"\\bG76\\b"<<"\\bG80\\b"<<"\\bG81\\b"<<"\\bG331\\b"<<"\\bG90\\b"<<"\\bG91\\b"
                    <<"\\bG92\\b"<<"\\bG93\\b"<<"\\bG94\\b"<<"\\bG95\\b"<<"\\bG96\\b"<<"\\bG97\\b"<<"\\bG99\\b"<<"\\bM00\\b"<<"\\bM01\\b"<<"\\bM02\\b"<<"\\bM30\\b"
                    <<"\\bM03\\b"<<"\\bM04\\b"<<"\\bM05\\b"<<"\\bM07\\b"<<"\\bM08\\b"<<"\\bM09\\b"<<"\\bM98\\b"<<"\\bM99\\b"
                    ;
    foreach (const QString &commandPattern, commandPatterns) {
        rule.pattern = QRegExp(commandPattern);
        rule.format = commandFormat;
        highlightingRules.append(rule);

    }

//    XFormat.setForeground(Qt::darkGreen);//设定关键词的高亮样式
//    XFormat.setFontWeight(QFont::DemiBold);
//    XFormat.setFontPointSize(14);
//    QStringList xyPatterns;//关键词集合,关键都以正则表达式表示 下面的可以改为我们想要的关键词
//    keywordPatterns <<"\\b X\\b"<<"\\b Y\\b";
//    foreach (const QString &xyPattern, xyPatterns) {
//        rule.pattern = QRegExp(xyPattern);
//        rule.format = XFormat;
//        highlightingRules.append(rule);
//        qDebug()<<" foreach2";
//    }


//    classFormat.setFontWeight(QFont::Bold);//添加Qt的类到高亮规则中
//    classFormat.setForeground(Qt::darkMagenta);
//    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
//    rule.format = classFormat;
//    highlightingRules.append(rule);

    XYIJFormat.setForeground(Qt::darkGreen);//坐标显示，X Y I J
    XYIJFormat.setFontWeight(QFont::DemiBold);
    rule.pattern = QRegExp("\\040[XYIJ]");//使用正则表达式，其中\\表示字符\,\\040实则是\040。使用八进制代表空格，[XYIJ]匹配其中任意一个
    rule.format = XYIJFormat;
    highlightingRules.append(rule);

//    multiLineCommentFormat.setForeground(Qt::red);//多行注释，只设定了样式，具体匹配在highlightBlock中设置

//    quotationFormat.setForeground(Qt::darkGreen);//字符串
//    rule.pattern = QRegExp("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);//函数
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

//    commentStartExpression = QRegExp("/\\*");//多行注释的匹配正则表达式
//    commentEndExpression = QRegExp("\\*/");
}

void MyHighLighter::highlightBlock(const QString &text)//应用高亮规则，也用于区块的高亮，比如多行注释
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) //>=0带有有匹配到，返回第一个匹配项的位置，-1则代表无
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
//            qDebug()<<"index:"<<index<<" length:"<<length;
            index = expression.indexIn(text, index + length);
        }
    }

//    setCurrentBlockState(0);//以下是多行注释的匹配

//    int startIndex = 0;
//    if (previousBlockState() != 1)
//        startIndex = commentStartExpression.indexIn(text);

//    while (startIndex >= 0) {
//        int endIndex = commentEndExpression.indexIn(text, startIndex);
//        int commentLength;
//        if (endIndex == -1) {
//            setCurrentBlockState(1);
//            commentLength = text.length() - startIndex;
//        } else {
//            commentLength = endIndex - startIndex
//                    + commentEndExpression.matchedLength();
//        }
//        setFormat(startIndex, commentLength, multiLineCommentFormat);
//        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
//    }
}

