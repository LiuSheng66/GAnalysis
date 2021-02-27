#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QMainWindow>

class PaintArea : public QMainWindow
{
public:
    PaintArea(int imageWidth,int imageHeight);
    ~PaintArea();

    //坐标系的设立
    void CoordinateAxisDraw(QPainter *painterCoordinateAxis);
    void beginPaint();
protected:
    void enterEvent(QEvent *event);//鼠标进入事件
    void leaveEvent(QEvent *);//鼠标离开事件
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void contextMenuEvent(QContextMenuEvent *event) override;


private slots:
    void onLoadImage(void);
    void onZoomInImage(void);
    void onZoomOutImage(void);
    void onPresetImage(void);

    void ByAlgorithmDraw(QVector<QPoint> *Array,QPainter *painter);

public:
    QImage image;  //QImage类对象，用于在其上绘图
    QPoint  point;

private:
//    QImage m_Image;
    qreal m_ZoomValue = 1.0;//在ARM中是double，在嵌入版中是float
    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    QPoint m_OldPos;
    bool m_Pressed = false;

    int XCentre;//在画布上设置为原心的的x轴的点
    int YCentre;//在画布上设置为原心的的y轴的点

protected:

signals:
//    void mouseMoveSig(QPoint point); //鼠标移动信号，在mouseMoveEvent()事件中触发

public:
//    QPainter *normalPainter;//正常的画笔

};

#endif // PAINTAREA_H
