#include "window.h"
#include <QSignalMapper>

Window::Window(QWidget *parent) : QWidget(parent)
{
    board = new Board(this);
    setMinimumSize(800, 600);
    setMaximumSize(800, 600);

    /* need a label here */
    label = new QLabel("Next player: X", this);
    label->setGeometry(QRect(600,0,200,50));

    next = 1; // X always goes first

    QSignalMapper* signalMapper = new QSignalMapper(this);
    for (int i = 0; i < 9; i++) {
        connect(board->squares[i]->button, SIGNAL (clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(board->squares[i]->button, i);
    }

    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(handleClick(int)));
}

void Window::handleClick(int i) {
    // stuff
//    label->setText("We clicked " + QString::number(i));
    next = !next;
    QString nextMarker = next ? "X" : "O";
    QString nextText = "Next player: " + nextMarker;
    label->setText(nextText);

    // change the cool thing we were talking about
    Square* currentSquare = board->squares[i];
    if (!currentSquare->occupied) {
        currentSquare->occupied = true;
        currentSquare->state = nextMarker;
        currentSquare->button->setText(nextMarker);
    }
}
