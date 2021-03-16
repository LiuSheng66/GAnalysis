#include"Drawing/mygraphicsview.h"
#include <QLineF>
#include<QDebug>
//#include<butt

MyGraphicsView::MyGraphicsView():
    sign(false),
    m_scalingOffset(1)
{
    graphicsScene=new QGraphicsScene();

//    graphicsScene->setSceneRect(QRectF(0,0,1000,1000));//此属性保存场景矩形
    graphicsScene->setBackgroundBrush(QBrush(QColor(207, 207 ,207)));//设置背景色

//    QGraphicsLineItem *lineItem1=new QGraphicsLineItem;
//    lineItem1->setLine(-200,65,-100,65);//画一条线
//    lineItem1->setPen(QPen(QBrush(QColor("green")),5));
//    graphicsScene->addItem(lineItem1);
lastMousePos=QPoint(0,0);
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
//    graphicsScene->addLine(QLineF(QPointF(-450,0),QPointF(450,0)), pen);//X轴
//    for (int i=-40;i<=40;i++)//40 代表刻度的数目。
//    {
//         if(i!=0)
//         {//QLineF(QPointF(10*i,-6),QPointF(10*i,0)), pen
//             graphicsScene->addLine(QLineF(QPointF(10*i,-3),QPointF(10*i,0)), pen);//间隔10个像素一个刻度，刻度高度3
//             if(i%5==0)
//             {
//                 graphicsScene->addLine((10*i)-8,10,QString::number(10*i));
//                 graphicsScene->addText(QString::number(10*i),QFont("宋体",11));
//                 graphicsScene->addLine(QLineF(QPointF(10*i,-6),QPointF(10*i,0)), pen);
//             }
//         }

//    }
//    graphicsScene->addText(470,15,"X");

//    graphicsScene->addLine(QLineF(QPointF(0,450),QPointF(0,-450)), pen);//Y轴
//    for (int i=-40;i<=40;i++)
//    {
//        if(i!=0)
//        {
//            graphicsScene->addLine(QLineF(QPointF(0,10*i),QPointF(3,10*i)), pen);//刻度
//            if(i%5==0)
//            {
//                graphicsScene->addLine(QLineF(QPointF(0,10*i),QPointF(6,10*i)), pen);
//            }
//        }
//     }
    graphicsScene->addLine(QLineF(QPointF(-10,0),QPointF(10,0)), pen);//X轴
    graphicsScene->addLine(QLineF(QPointF(0,10),QPointF(0,-10)), pen);//Y轴
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


void MyGraphicsView::wheelEvent(QWheelEvent* event) {

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);//为了改善缩放效果，以鼠标为中心进行缩放
    qreal factor_out = transform().scale(1.2, 1.2).mapRect(QRectF(0,0,1,1)).width();
        qreal factor_in=transform().scale(1/1.2,1/1.2).mapRect(QRectF(0,0,1,1)).width();
        if(event->delta()>0){
            if(factor_out>70) return;//防止视图过大
            scale(1.2,1.2);//放大
        }
        else if(event->delta()<0){
            if(factor_in<0.1)return;//防止视图过小
            scale(1/1.2,1/1.2);//缩小
        }
}


//*************************

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //若按下左键
//        cursor1;//创建光标对象
        cursor1.setShape(Qt::ClosedHandCursor);//设置光标形态为手掌
        setCursor(cursor1); //使用手掌光标
        //qDebug()<<mapToScene(event->pos());
        sign = true;//触发平移信号
        lastPos = event->pos();
        lastMousePos= event->pos();
    }
    QGraphicsView::mousePressEvent(event);
}
//void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
//{
//    if (sign){
//        QPointF mouseDelta = event->pos() - lastPos;
//        OutPutMsgToConsle(Information_INFO,QString::number(mouseDelta.rx())+QString::number(mouseDelta.ry()));
////        OutPutMsgToConsle(Information_INFO,"moveing");
//        translate(mouseDelta);
//    }
//    lastPos = event->pos();
//    QGraphicsView::mouseMoveEvent(event);
//}
void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        sign = false;
    cursor1.setShape(Qt::ArrowCursor);//设置光标形态为手掌
    setCursor(cursor1); //拖动完成后，光标恢复默 认形状
//    QGraphicsView::mouseReleaseEvent(event);
}
// 平移
void MyGraphicsView::translate(QPointF delta)
{
    delta *= 0.1;
    // view 根据鼠标下的点作为锚点来定位 scene
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QPoint newCenter(this->width()/2-delta.x(),this->height()/2-delta.y());
    centerOn(mapToScene(newCenter));
    // scene 在 view 的中心点作为锚点
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}
//鼠标平移事件
void MyGraphicsView::mouseMoveEvent(QMouseEvent* event) {

if (sign){
//    QPointF mouseDelta = event->pos() - lastPos;
//    OutPutMsgToConsle(Information_INFO,QString::number(mouseDelta.rx())+QString::number(mouseDelta.ry()));
//        OutPutMsgToConsle(Information_INFO,"moveing");
//    translate(mouseDelta);
    //获取每次鼠标在场景坐标系下的平移量
    QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(this->lastMousePos);
    //调用平移方法
    this->MyMove(mouseDelta);
    //lastMousePos是MyGraphicsView的私有成员变量，用以记录每次的事件结束时候的鼠标位置
    this->lastMousePos = event->pos();

}
lastPos = event->pos();
this->lastMousePos = event->pos();
//QGraphicsView::mouseMoveEvent(event);

}

//自定义的平移方法
void MyGraphicsView::MyMove(QPointF delta) {
    //如果是在缩放之后，调用的平移方法，那么平移量先要乘上缩放比，transform是view的变换矩阵，m11可以用为缩放比
    delta *= this->transform().m11();
OutPutMsgToConsle(Warning_INFO,"moving");
    //修改锚点，调用缩放方法
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->centerOn(this->mapToScene(QPoint(this->viewport()->rect().width()/ 2 - delta.x(),
                                                                        this->viewport()->rect().height()/ 2 - delta.y())));
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}
