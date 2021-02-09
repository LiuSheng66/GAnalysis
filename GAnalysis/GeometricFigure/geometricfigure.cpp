#include "geometricfigure.h"

GeometricFigure::GeometricFigure():
    figureLineType(lineType(UNDEFINED_LINE))
{

}

void GeometricFigure::setLineShape(lineType type)
{
    figureLineType=type;
}

lineType GeometricFigure::getLineShape()
{
    return figureLineType;
}
