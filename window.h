#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QMap>
#include <QRadioButton>
#include <QGroupBox>
#include "board.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

signals:

private slots:
    void handleClick(int i);
    void reset();
private:
    QRadioButton* onePlayerRadioButton;
    QRadioButton* twoPlayerRadioButton;
    QRadioButton* playAsXRadioButton;
    QRadioButton* playAsORadioButton;

    QGroupBox* selectNumberPlayersGroupBox;
    QGroupBox* selectPlayerMarkerGroupBox;

    Board* board;

    int next;           // 0: O, 1: X
    int turn;
    QLabel* nextPlayerLabel;
    bool finished;
    int playerMode;     // 1: 1-player, 2: 2-player
    int playerMarker;   // same as "next", but only applicable if one-player mode

    void togglePlayerMode(bool b);
    int aiPlaceMarker();
    void resolveTurn();

    bool checkForWin(int i);
    bool checkLines(const QVector<int> &linesToCheck);
    void handlePaint(int i, int marker);
    void setNextPlayerLabel();

};

#endif // WINDOW_H
