#include "window.h"

#include <QSignalMapper>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

#include <QDebug>

Window::Window(QWidget *parent) :
    QWidget(parent),
    finished(0),
    turn(1),
    next(1),        // x always goes first
    playerMode(2),
    playerMarker(-1),
    board(new Board(this))
{

    // allocate 200 pixels to the right for menu
    setFixedSize(800, 600);

    nextPlayerLabel = new QLabel(this);
    setNextPlayerLabel();
    nextPlayerLabel->setGeometry(QRect(625,0,125,50));


    // initialize signal mapping
    QSignalMapper* signalMapper = new QSignalMapper(this);
    for (int i = 0; i < 9; i++) {
        connect(board->squares[i], SIGNAL (click()), signalMapper, SLOT(map()));
        signalMapper->setMapping(board->squares[i], i);
    }
    connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(handleClick(int)));

    // Initialize and set up reset button
    QPushButton* resetButton = new QPushButton(this);
    resetButton->setGeometry(QRect(650, 300, 100, 50));
    resetButton->setText("Reset");
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));

    // Initialize radio buttons for 1 or 2 player mode
    onePlayerRadioButton = new QRadioButton(this);
    twoPlayerRadioButton = new QRadioButton(this);

//    onePlayerRadioButton->setGeometry(QRect(650, 100, 100, 50));
    onePlayerRadioButton->setText("1-Player");
//    twoPlayerRadioButton->setGeometry(QRect(650, 150, 100, 50));
    twoPlayerRadioButton->setText("2-Player");
    // default is two player mode


    playAsXRadioButton = new QRadioButton(this);
    playAsORadioButton = new QRadioButton(this);

    playAsXRadioButton->setGeometry(QRect(650, 200, 100, 50));
    playAsXRadioButton->setText("Play as X");
    playAsORadioButton->setGeometry(QRect(650, 250, 100, 50));
    playAsORadioButton->setText("Play As O");


    selectNumberPlayersGroupBox = new QGroupBox(this);
    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(onePlayerRadioButton);
    vbox1->addWidget(twoPlayerRadioButton);
    selectNumberPlayersGroupBox->setLayout(vbox1);
    selectNumberPlayersGroupBox->setGeometry(QRect(650, 100, 100, 100));

    selectPlayerMarkerGroupBox = new QGroupBox(this);
    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(playAsXRadioButton);
    vbox2->addWidget(playAsORadioButton);
    selectPlayerMarkerGroupBox->setLayout(vbox2);
    selectPlayerMarkerGroupBox->setGeometry(QRect(650, 200, 100, 100));


    twoPlayerRadioButton->setChecked(true);
    playAsXRadioButton->setChecked(true);

    selectPlayerMarkerGroupBox->setEnabled(false);

    connect(onePlayerRadioButton, &QRadioButton::toggled, this, &Window::togglePlayerMode);

    if (playerMode == 1)
        resolveTurn();

}

void Window::togglePlayerMode(bool b) {
    if (onePlayerRadioButton->isChecked()) {
        selectPlayerMarkerGroupBox->setEnabled(true);
    } else if (twoPlayerRadioButton->isChecked()) {
        selectPlayerMarkerGroupBox->setEnabled(false);
    }
}

void Window::reset() {
    turn = 1;
    finished = false;
    next = 1;

    if (onePlayerRadioButton->isChecked()) {
        playerMode = 1;
        if (playAsXRadioButton->isChecked()) {
            playerMarker = 1;
            qInfo() << "Here we go !";
        } else if (playAsORadioButton->isChecked()) {
            playerMarker = 0;
            qInfo() << "See ya later, X!";
        }
        qInfo() << "One Player Mode activated";
    } else if (twoPlayerRadioButton->isChecked()) {
        playerMode = 2;
        // playerMarker not being used
        playerMarker = -1;
        qInfo() << "Two Player Mode activated";
    }

    // clear the board
    for (auto i = 0; i < 9; i++) {
        Square* currentSquare = board->squares[i];
        currentSquare->setState(-1);
        currentSquare->occupied = false;
    }

    setNextPlayerLabel();


    if (playerMode == 1)
        resolveTurn();
}

void Window::resolveTurn() {
    bool aiTurn = ((turn % 2 == 0) && (playerMarker == 1)) ||
                  ((turn % 2 == 1) && (playerMarker == 0));

    if (aiTurn) {
        int i = aiPlaceMarker(); // i <- index of chosen square

        bool won = checkForWin(i);
        if (won) {
            finished = true;
            QString aiMarker = playerMarker ? "O" : "X";
            nextPlayerLabel->setText(aiMarker + " wins");
            return;
        }

        turn++;
        if (turn == 10) {
            finished = true;
            nextPlayerLabel->setText("Draw!");
            return;
        }

        next = !next;
        setNextPlayerLabel();
    }
}

int Window::aiPlaceMarker() {

    QString aiMarker = playerMarker ? "O" : "X";
    int aiMarkerAsInt = playerMarker ? 0 : 1;
    Square* chosenSquare;
    int i;
    for (i = 0; i < 9; i++) {
        if (!board->squares[i]->occupied) {
            chosenSquare = board->squares[i];
            break;
        }
    }
    chosenSquare->setState(aiMarkerAsInt);
    chosenSquare->update();
    return i;
}

// places a marker at position i (if possible), for the player.
// also does checks for whether a win or draw has occurred.
void Window::handleClick(int i) {
    if (playerMode == 2) {
        if (!finished) {

            QString currMarker = next ? "X" : "O";
            QString nextMarker = next ? "O" : "X";
            Square* currentSquare = board->squares[i];

            if (!currentSquare->occupied) {
                currentSquare->setState(next);
                currentSquare->update();

                bool won = checkForWin(i);
                if (won) {
                    finished = true;
                    nextPlayerLabel->setText(currMarker + " wins");
                    return;
                }

                turn++;
                if (turn == 10) {
                    finished = true;
                    nextPlayerLabel->setText("Draw!");
                    return;
                }

                next = !next;
                setNextPlayerLabel();
            }
        }
    } else if (playerMode == 1) {
        if (!finished) {

            QString currMarker = playerMarker ? "X" : "O";
            Square* currentSquare = board->squares[i];

            if (!currentSquare->occupied) {
                currentSquare->setState(playerMarker);
                currentSquare->update();

                bool won = checkForWin(i);
                if (won) {
                    finished = true;
                    nextPlayerLabel->setText(currMarker + " wins");
                    return;
                }

                turn++;
                if (turn == 10) {
                    finished = true;
                    nextPlayerLabel->setText("Draw!");
                    return;
                }

                next = !next;
                setNextPlayerLabel();
                resolveTurn();
            }
        }
    }
}



bool Window::checkForWin(int i) {
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

    return checkLines(linesToCheck);
}

bool Window::checkLines(const QVector<int> &linesToCheck) {
    for (int lineNum : linesToCheck) {
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

        // checks for 3 in a row
        int numMarkers = 0;
        for (int position : positions) {
            if (board->squares[position]->state == next) {
                numMarkers++;
            }
        }
        if (numMarkers == 3) {
            return true;
        }

    }
    return false;
}

// function prototype for setting the label
// instead of building the string straight up, actually read the "next" parameter.

void Window::setNextPlayerLabel() {
    QString nextPlayerString = next ? "Next player: X" : "Next player: O";
    nextPlayerLabel->setText(nextPlayerString);
}


