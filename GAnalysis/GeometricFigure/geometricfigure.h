#ifndef GEOMETRICFIGURE_H
#define GEOMETRICFIGURE_H


//线段的类型：线线型、线弧型、弧线型、弧弧型
enum lineType{
   LINE_STR, //直线
   ARC_LINE, //圆弧
   UNDEFINED_LINE //未定直线类型
};

class GeometricFigure
{
public:
    GeometricFigure();

    void setLineShape(lineType type);
    lineType getLineShape();

public:
    lineType figureLineType;//线段的类型，直线还是圆弧

};

#endif // GEOMETRICFIGURE_H
