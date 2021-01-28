#include "paintarea.h"
#include<QPainter>
#include<QDebug>
#include<QMouseEvent>
#include<QWheelEvent>
#include<QPoint>
#include <QImage>
#include <QMenu>
#include <QContextMenuEvent>
#include <QStyleOption>
#include <QPainter>
#include <QFileDialog>

PaintArea::PaintArea(int imageWidth,int imageHeight)
{

    XCentre=500;//原点坐标设定值
    YCentre=500;


    image=QImage(imageWidth,imageHeight,QImage::Format_RGB32);//画布初始化大小设为1000*1000，使用32位颜色

    QRgb backGroundColor;
    backGroundColor=qRgb(255,0,255);//画布初始化位白色
    image.fill(backGroundColor);
}
PaintArea::~PaintArea()
{

}

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::black);
    painter.setPen(pen);
    //painter.setWindow(500,500,500,500);

    //画布的绘画
    painter.drawImage(0,0,image);//画布在哪里开始画，且它的大小及颜色

    //绘画坐标系
    CoordinateAxisDraw(&painter);
//    ChooseWayDialog::ChooseWayRun=1;
//    ByAlgorithmDraw(&MainAlgorithmFunction::AllCoordinate_array,&painter);

    painter.end();
}

//*****************************************图像缩放等功能********************************//
void PaintArea::contextMenuEvent(QContextMenuEvent *event)
{
    QPoint pos = event->pos();
    pos = this->mapToGlobal(pos);
    QMenu *menu = new QMenu(this);

    QAction *loadImage = new QAction(tr("Load Image"));
    QObject::connect(loadImage, &QAction::triggered, this, &PaintArea::onLoadImage);
    menu->addAction(loadImage);
    menu->addSeparator();

    QAction *zoomInAction = new QAction(tr("Zoom In"));
    QObject::connect(zoomInAction, &QAction::triggered, this, &PaintArea::onZoomInImage);
    menu->addAction(zoomInAction);

    QAction *zoomOutAction = new QAction(tr("Zoom Out"));
    QObject::connect(zoomOutAction, &QAction::triggered, this, &PaintArea::onZoomOutImage);
    menu->addAction(zoomOutAction);

    QAction *presetAction = new QAction(tr("Preset"));
    QObject::connect(presetAction, &QAction::triggered, this, &PaintArea::onPresetImage);
    menu->addAction(presetAction);

    menu->exec(pos);
}
//*****************************************图像缩放等功能********************************//




//鼠标进入事件
void PaintArea::enterEvent(QEvent *event)
{
//    qDebug()<<"jinru";
}

//鼠标离开事件
void PaintArea::leaveEvent(QEvent *)
{
//    qDebug()<<"exit";
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_Pressed)
        return QWidget::mouseMoveEvent(event);

    this->setCursor(Qt::SizeAllCursor);
    QPoint pos = event->pos();
    int xPtInterval = pos.x() - m_OldPos.x();
    int yPtInterval = pos.y() - m_OldPos.y();

    m_XPtInterval += xPtInterval;
    m_YPtInterval += yPtInterval;

    m_OldPos = pos;
    this->update();
}
void PaintArea::mousePressEvent(QMouseEvent *event)
{
//    QString str=QString("X= %1  Y= %2").arg(event->x()).arg(event->y());
//    qDebug()<<str;
    m_OldPos = event->pos();
    m_Pressed = true;

}
void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    m_Pressed = false;
    this->setCursor(Qt::ArrowCursor);
}

void PaintArea::wheelEvent(QWheelEvent *event)
{
    //******************缩放*****************//
    qDebug()<<"滚轮角度："<<event->delta();
    if (event->delta() > 0)
        onZoomInImage();
    else
        onZoomOutImage();
    this->update();
    //******************缩放*****************//

//    int value = event->delta();
//    double scaleRatio = ((double)value)/RATIO_TO_DOULBE;
//    m_scale += scaleRatio;

//    limitScale();

    update();
    event->accept();
}


void PaintArea::onLoadImage(void)
{
    QString imageFile = QFileDialog::getOpenFileName(this, "Open Image", "./", tr("Images (*.png *.xpm *.jpg)"));

    QFile file(imageFile);
    if (!file.exists())
        return;

    image.load(imageFile);
}

void PaintArea::onZoomInImage(void)
{
    m_ZoomValue += 0.2;
    this->update();
}

void PaintArea::onZoomOutImage(void)
{
    m_ZoomValue -= 0.2;
    if (m_ZoomValue <= 0)
    {
        m_ZoomValue += 0.2;
        return;
    }
    this->update();
}

void PaintArea::onPresetImage(void)
{
    m_ZoomValue = 1.0;
    m_XPtInterval = 0;
    m_YPtInterval = 0;
    this->update();
}

//绘制坐标轴
void PaintArea::CoordinateAxisDraw(QPainter *painterCoordinateAxis)
{

//    QPainter *painterCoordinateAxis = new QPainter(this);
//    painterCoordinateAxis->setPen(Qt::black);

    painterCoordinateAxis->translate(XCentre,YCentre); //将点设为原点

    //绘制X轴
    painterCoordinateAxis->drawLine(-500,0,500,0);
    for (int i=-45;i<=45;i++)//40 代表刻度的数目。
    {
         if(i!=0)
         {
             painterCoordinateAxis->drawLine(10*i,-3,10*i,0);//间隔10个像素一个刻度，刻度高度3
             if(i%5==0)
             {
                 painterCoordinateAxis->drawText((10*i)-8,10,QString::number(10*i));
                 painterCoordinateAxis->drawLine(10*i,-6,10*i,0);
             }
         }

    }
    painterCoordinateAxis->drawText(470,15,"X");

    //绘制Y轴
    painterCoordinateAxis->drawLine(0,500,0,-500);
    for (int i=-45;i<=45;i++)
    {
        if(i!=0)
        {
            painterCoordinateAxis->drawLine(0,10*i,3,10*i);//刻度
            if(i%5==0)
            {
                painterCoordinateAxis->drawText(-24,(-10*i)+8,QString::number(10*i));
                painterCoordinateAxis->drawLine(0,10*i,6,10*i);
            }
        }
     }
    painterCoordinateAxis->drawText(-20,-465,"Y");
}

void PaintArea::ByAlgorithmDraw(QVector<QPoint> *Array,QPainter *painter)
{
    switch (1)
    {
    case 1:
        break;
    case 2:
        break;
    default:
        break;

    }
    //绘画最终由哪种方法计算得到的图画
    if(Array->size()>0)
    {
        for (int i=0;i<(Array->size()-1);i++)
        {
            //此处由于绘画坐标轴是向右x正半轴，向下y正半轴，故把数据的y坐标取负在绘画出来
            painter->drawLine(Array->at(i).x(),-Array->at(i).y(),
                             Array->at(i+1).x(),-Array->at(i+1).y());
        }
    }
}
