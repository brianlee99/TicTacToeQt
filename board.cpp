#include "board.h"
#include <QPainter>
#include <QGridLayout>

Board::Board(QWidget *parent) :
    QWidget(parent),
    squares(9, 0)
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setMargin(0);
    grid->setSpacing(0);

    for (int i = 0; i < 9; i++) {
        squares[i] = new Square(i, this);
        grid->addWidget(squares[i], i/3, i%3);
    }

    this->setFixedSize(600, 600);
    this->setLayout(grid);
}

Board::~Board() {
    for (int i = 0; i < 9; i++) {
        delete squares[i];
    }
}

int Board::index(int x, int y) {
    return x + 3 * y;
}

void Board::paintEvent(QPaintEvent *event) {
    // draw the grid
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);

    painter.drawLine(0, 0, 600, 0);
    painter.drawLine(0, 200, 600, 200);
    painter.drawLine(0, 400, 600, 400);
    painter.drawLine(0, 600, 600, 600);

    painter.drawLine(0,0,0,600);
    painter.drawLine(200,0,200,600);
    painter.drawLine(400,0,400,600);
    painter.drawLine(600,0,600,600);

}
