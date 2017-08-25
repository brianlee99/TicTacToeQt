#include "square.h"
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPen>
#include <QDebug>


Square::Square(int i, QWidget *parent) :
    QWidget(parent),
    index(i),
    state(-1),
    occupied(false)
{
    this->setFixedSize(200,200);


}

void Square::mousePressEvent(QMouseEvent *event)
{


    emit click();
}

void Square::setState(int next)
{
    state = next;
    update();
}

void Square::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(1);
    painter.setPen(pen);

    QRect r(0,0,200,200);
    painter.drawRect(r);

    if (state == 0) {
        QPen bluePen;
        bluePen.setWidth(3);
        bluePen.setColor(Qt::blue);
        painter.setPen(bluePen);
        painter.drawEllipse(r);
    } else if (state == 1) {
        paintX(&painter);
    }
}

void Square::paintX(QPainter* painter)
{
    QPen redPen;
    redPen.setWidth(3);
    redPen.setColor(Qt::red);
    painter->setPen(redPen);
    painter->drawLine(0,0,200,200);
    painter->drawLine(0,200,200,0);
}

//void Square::paintEvent(QPaintEvent *e) {
//    qInfo() << "Hello";
//    // select area of the board to (re)draw
//    int x = index % 3 * 200;
//    int y = index / 3;
//    QRect rect(x, y, 200, 200);
//    QPainter painter(this);

//    if (state == 0) {
//        // draw an O
//        QPen framePen(Qt::blue);
//        framePen.setWidth(5);
//        painter.setPen(framePen);
//        painter.drawEllipse(rect);
//    } else if (state == 1) {
//        // draw an X
//        QPen framePen(Qt::red);
//        framePen.setWidth(5);
//        painter.setPen(framePen);
//        painter.drawEllipse(rect);
//    }




//}
