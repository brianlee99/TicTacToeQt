#include "window.h"
#include <QSignalMapper>
#include <QtDebug>
Window::Window(QWidget *parent) :
    QWidget(parent),
    finished(0)
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


    // check that the currentSquare is unoccupied

    // change the state and stateMarker of the target square

    // check for a win
    if (!finished) {
        QString currMarker = next ? "X" : "O";
        QString nextMarker = next ? "O" : "X";

        // check that the clicked square is unoccupied
        Square* currentSquare = board->squares[i];
        if (!currentSquare->occupied) {
            currentSquare->occupied = true;
            currentSquare->state = next;
            //currentSquare->stateMarker = currMarker;


            currentSquare->button->setText(currMarker);

            bool won = checkForWin(i);
            if (won) {
                finished = true;
            }
            // TODO: check for a win
            // Possible wins:
            // 0,1,2; 3,4,5; 6,7,8; 0,3,6; 1,4,7; 2,5,8; 0,4,8; 2,4,6;

            next = !next;
            QString nextText = "Next player: " + nextMarker;
            label->setText(nextText);
        }
    }
}

bool Window::checkForWin(int i) {
    bool foundWin = false;
    QVector<int> linesToCheck;
    switch (i) {
        case 0:
            linesToCheck = {0, 3, 6};
            break;
        case 1:
            linesToCheck = {0, 4};
            break;
        case 2:
            linesToCheck = {0, 5, 7};
            break;
        case 3:
            linesToCheck = {1, 3};
            break;
        case 4:
            linesToCheck = {1, 4, 6, 7};
            break;
        case 5:
            linesToCheck = {1, 5};
            break;
        case 6:
            linesToCheck = {2, 3, 7};
            break;
        case 7:
            linesToCheck = {2, 4};
            break;
        case 8:
            linesToCheck = {2, 5, 6};
            break;
    }

    foundWin = checkLines(linesToCheck);
    return foundWin;
}

bool Window::checkLines(const QVector<int> &linesToCheck) {
    for (int lineNum : linesToCheck) {

        qInfo("Line number %d", lineNum);

        QVector<int> positions;

        switch(lineNum) {
            case 0:
                positions = {0, 1, 2};
                break;
            case 1:
                positions = {3, 4, 5};
                break;
            case 2:
                positions = {6, 7, 8};
                break;
            case 3:
                positions = {0, 3, 6};
                break;
            case 4:
                positions = {1, 4, 7};
                break;
            case 5:
                positions = {2, 5, 8};
                break;
            case 6:
                positions = {0, 4, 8};
                break;
            case 7:
                positions = {2, 4, 6};
                break;
        }

        int numMarkers = 0;
        // for each in positions
        for (int position : positions) {

            // check if the position is "next"
            // if true, then don't do anything
            // if false, then BREAK
            if (board->squares[position]->state == next) {
                numMarkers++;
            }
        }

        // check that the line has three of the same
        if (numMarkers == 3) {
            // we found a winner!
            return true;
        }


    }

    return false;
}
