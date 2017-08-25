#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include "board.h"
#include <QMap>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

signals:

private slots:
    void handleClick(int i);
private:
    Board* board;
    int next; // 0: O, 1: X
    QLabel* label;
    bool finished;

    bool checkForWin(int i);
    bool checkLines(const QVector<int> &linesToCheck);

    void handlePaint(int i, int marker);

};

#endif // WINDOW_H
