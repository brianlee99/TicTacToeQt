#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include "board.h"

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

signals:

public slots:
    void handleClick(int i);
private:
    Board* board;
    int next; // 0: O, 1: X
    QLabel* label;
};

#endif // WINDOW_H
