#include "mygraphicsview.h"
#include <QLineF>

MyGraphicsView::MyGraphicsView()
{
    graphicsScene=new QGraphicsScene();

//    scene->setSceneRect(QRectF(0,0,100,100));//此属性保存场景矩形
    graphicsScene->setBackgroundBrush(QBrush(QColor(207, 207 ,207)));//设置背景色

//    QGraphicsLineItem *lineItem1=new QGraphicsLineItem;
//    lineItem1->setLine(-200,65,-100,65);//画一条线
//    lineItem1->setPen(QPen(QBrush(QColor("green")),5));
//    graphicsScene->addItem(lineItem1);

    setScene(graphicsScene);
    initGraphicsView();
}

void MyGraphicsView::initGraphicsView()
{
//    QColor color = QColorDialog::getColor(Qt::red,nullptr, QString("颜色对话框"),QColorDialog::ShowAlphaChannel);
//    QPen pen;
//    pen.setWidth(2);
//    pen.setColor(color);
    creatXYAxis();
}

void MyGraphicsView::creatXYAxis()
{
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 0, 0));
    graphicsScene->addLine(QLineF(QPointF(-450,0),QPointF(450,0)), pen);//X轴
    for (int i=-40;i<=40;i++)//40 代表刻度的数目。
    {
         if(i!=0)
         {//QLineF(QPointF(10*i,-6),QPointF(10*i,0)), pen
             graphicsScene->addLine(QLineF(QPointF(10*i,-3),QPointF(10*i,0)), pen);//间隔10个像素一个刻度，刻度高度3
             if(i%5==0)
             {
//                 graphicsScene->addLine((10*i)-8,10,QString::number(10*i));
//                 graphicsScene->addText(QString::number(10*i),QFont("宋体",11));
                 graphicsScene->addLine(QLineF(QPointF(10*i,-6),QPointF(10*i,0)), pen);
             }
         }

    }
//    graphicsScene->addText(470,15,"X");

    graphicsScene->addLine(QLineF(QPointF(0,450),QPointF(0,-450)), pen);//Y轴
    for (int i=-40;i<=40;i++)
    {
        if(i!=0)
        {
            graphicsScene->addLine(QLineF(QPointF(0,10*i),QPointF(3,10*i)), pen);//刻度
            if(i%5==0)
            {
                graphicsScene->addLine(QLineF(QPointF(0,10*i),QPointF(6,10*i)), pen);
            }
        }
     }


}

void MyGraphicsView::drawCoordinate(QVector<QPoint> &allCoordinate)
{
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 0, 0));


    for (int i=0;i<allCoordinate.size()-1;i++)
    {
        graphicsScene->addLine(QLineF(allCoordinate.at(i),allCoordinate.at(i+1)), pen);
    }
}

void MyGraphicsView::clearDraw()
{
    graphicsScene->clear();
}
