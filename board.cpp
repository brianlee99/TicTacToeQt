#include "board.h"
#include <QDebug>

Board::Board(QWidget *parent) :
    QWidget(parent),
    squares(9, 0)
{
    grid = new QGridLayout(this);

    for (int i = 0; i < 9; i++) {
        squares[i] = new Square(i, this);
//        QPushButton* button = new QPushButton(this);
//        button->setText(QString::number(i));
//        squares[i] = button;
        grid->addWidget(squares[i], i/3, i%3);
    }



    this->resize(600, 600);
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

