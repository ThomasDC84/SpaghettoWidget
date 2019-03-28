#ifndef SPAGHETTOWIDGET_H
#define SPAGHETTOWIDGET_H

#include <QList>
#include <QPoint>
#include <QTimer>
#include <QWidget>
#include <QTouchEvent>
#include <QDebug>

class spaghettoWidget : public QWidget
{
    Q_OBJECT
    
public:
    spaghettoWidget(QWidget *parent = 0);

    QSize sizeHint() const;
    QSize minimumSize() const;
    QSize minimumSizeHint () const;
    void addEntry(int x, int y);

protected:
    void paintEvent(QPaintEvent *ev);
    void wheelEvent(QWheelEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    //void timerEvent(QTimerEvent *ev);

private:
    QVector<QPoint> points;
    QPoint initialPoint;
    int timer, x, y;
    double zoom, panX, panY;
    bool leftMousePressed, rightMousePressed;

};

#endif // SPAGHETTOWIDGET_H
