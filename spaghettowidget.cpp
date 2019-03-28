#include <QtGui>
#include <QDebug>
#include "spaghettowidget.h"

spaghettoWidget::spaghettoWidget(QWidget *parent)
: QWidget(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    timer = x = y = 0;
    zoom = 1.0;
    panX = panY = 0.0;
    leftMousePressed = false;
    setMinimumSize(400, 400);
    QPoint p;
    p.setX(0);
    p.setY(0);
    points.append(p);
    //timer = startTimer(33);
}

void spaghettoWidget::addEntry(int x, int y)
{
    QPoint p;
    p.setX(x);
    p.setY(y);
    points.append(p);
    update();
    /*qDebug("Last Point X coord: %d", x);
    qDebug("Last Point Y coord: %d", y);
    qDebug("number of points: %d", points.size());*/
}

void spaghettoWidget::paintEvent(QPaintEvent * ev)
{

    QWidget::paintEvent(ev);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black, 2);
    QBrush brush(Qt::white);
    painter.setPen(pen);
    int height = rect().height();
    int width = rect().width();
    int size = qMin(height, width);
    QRect r(0,0,size,size);
    painter.fillRect(r, brush);
    pen.setWidth(1);
    painter.setPen(pen);
    QLine xAxis(r.left(), r.center().x()+(panY*zoom), r.right(), r.center().x()+(panY*zoom));
    QLine yAxis(r.center().x()+(panX*zoom), r.top(), r.center().x()+(panX*zoom), r.bottom());
    painter.drawLine(xAxis);
    painter.drawLine(yAxis);

    //draw grid
    pen.setWidth(0);
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);
    QVector<QLine> grid;

    int gridLines = 25;
    double gridSpace;
    if(zoom < 1.0)
        gridSpace = ((r.width()/10)*zoom);
    else
    {
        int multiplier = (int)(zoom);
        switch(multiplier) {
        case 1:
        case 2:
        case 4:; break;
        case 3: multiplier = 4; break;
        }
        gridSpace = ((r.width()/10)*zoom)/multiplier;
    }
    qDebug() << "zoom: " << zoom;
    qDebug() << "grid space: " << gridSpace;
    for(int g = 1; g <= gridLines; g++)
    {
        //horizontal grid
        grid << xAxis.translated(0, gridSpace*g);
        grid << xAxis.translated(0, -(gridSpace*g));
        //vertical grid
        grid << yAxis.translated((gridSpace*g), 0);
        grid << yAxis.translated(-(gridSpace*g), 0);
    }

    painter.drawLines(grid);

    //end draw grid

    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    //int xMax, yMax;
    //xMax = yMax = 0;
    for (int i = 1; i < points.size(); ++i)
    {
        QPoint a = points.at(i-1);
        QPoint b = points.at(i);
        painter.drawLine(

                    (a.rx()*zoom)+r.center().rx()+(panX*zoom),
                    (a.ry()*zoom)+r.center().ry()+(panY*zoom),

                    (b.rx()*zoom)+r.center().rx()+(panX*zoom),
                    (b.ry()*zoom)+r.center().ry()+(panY*zoom));
        //if(qAbs(b.rx())>xMax) xMax = qAbs(b.rx());
        //if(qAbs(b.ry())>yMax) yMax = qAbs(b.ry());
    }
    pen.setColor(Qt::green);
    pen.setWidth(8);
    painter.setPen(pen);
    QPoint lastPoint = points.at(points.size()-1);
    painter.drawPoint((lastPoint.rx()*zoom)+r.center().rx()+(panX*zoom),
                      (lastPoint.ry()*zoom)+r.center().ry()+(panY*zoom));
    //if(xMax != 0 || yMax != 0)
    //zoom = (150.0/(double)(qMax(xMax,yMax)))-0.3;
}

void spaghettoWidget::wheelEvent(QWheelEvent *ev)
{
    if(ev->orientation() == Qt::Vertical)
    {
        zoom += (double)(ev->delta()) / 600;
        if(zoom < 0.2) zoom = 0.2;
        if(zoom > 4.0) zoom = 4.0;
        ev->accept();
        update();
    }
}

void spaghettoWidget::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        leftMousePressed = true;
        initialPoint = ev->pos();
        addEntry(ev->pos().rx()-200, ev->pos().ry()-200);
    }
    if(ev->button() == Qt::RightButton)
    {
        rightMousePressed = true;
        initialPoint = ev->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    if(ev->button() == Qt::MiddleButton)
    {
        zoom = 1.0;
        panX = panY = 0.0;
        update();
    }
}

void spaghettoWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        leftMousePressed = false;
    }
    if(ev->button() == Qt::RightButton)
    {
        rightMousePressed = false;
        setCursor(Qt::ArrowCursor);
    }
}

void spaghettoWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if(leftMousePressed == true)
    {
        addEntry(ev->pos().rx()-200, ev->pos().ry()-200);
        update();
    }
    if(rightMousePressed == true)
    {
        panX += (ev->x()-initialPoint.x())/zoom;
        panY += (ev->y()-initialPoint.y())/zoom;
        initialPoint = ev->pos();
        update();
    }
}

/*void spaghettoWidget::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == timer)
    {
        for(int i=0; i<3; i++)
        {
            x+=(rand()%7)-3;
            y+=(rand()%7)-3;
            x=x%100;
            y=y%100;
            addEntry(x,y);
        }
        update();
    }
}*/

QSize spaghettoWidget::minimumSizeHint() const
{
    QSize minSize(400, 400);
    return minSize;
}

QSize spaghettoWidget::minimumSize() const
{
    return minimumSizeHint();
}

QSize spaghettoWidget::sizeHint() const
{
    return minimumSizeHint();
}
