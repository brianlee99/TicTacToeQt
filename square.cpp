#include "square.h"
#include <QPainter>
#include <QPen>


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
    occupied = true;
    update();
}

void Square::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(1);
    painter.setPen(pen);

    QRect r(0,0,200,200);
//    painter.drawRect(r);

    if (state == 0) {
        paintO(&painter);
    } else if (state == 1) {
        paintX(&painter);
    }
}

void Square::paintX(QPainter* painter) {
    QPen redPen;
    redPen.setWidth(3);
    redPen.setColor(Qt::red);
    painter->setPen(redPen);
    painter->drawLine(0,0,200,200);
    painter->drawLine(0,200,200,0);
}

void Square::paintO(QPainter* painter) {
    QPen bluePen;
    bluePen.setWidth(3);
    bluePen.setColor(Qt::blue);
    painter->setPen(bluePen);
    painter->drawEllipse(QRect(0,0,200,200));
}


