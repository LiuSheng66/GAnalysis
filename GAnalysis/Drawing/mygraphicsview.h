#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsLineItem>
#include<QWheelEvent>
//#include<
#include"Global/global.h"

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView();
    void initGraphicsView();
    void creatXYAxis();//创建坐标轴

public:
    QGraphicsScene *graphicsScene;

    //线段颜色
    void drawCoordinate(QVector<QPoint> &allCoordinate);
    void clearDraw();
    void wheelEvent(QWheelEvent *event);


    qreal m_scalingOffset;
    qreal zoom;
    bool sign;
    QPointF lastPos;
    QPointF translateSpeed;
    QCursor cursor1;
    QPoint lastMousePos;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void translate(QPointF delta);
    void MyMove(QPointF delta);
};

#endif // MYGRAPHICSVIEW_H
