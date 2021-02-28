#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsLineItem>

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
};

#endif // MYGRAPHICSVIEW_H
