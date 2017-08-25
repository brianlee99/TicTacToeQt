#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QPushButton>

#include "square.h"

class Board : public QWidget
{
    Q_OBJECT

friend class Window;

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();
    QVector<Square*> squares;

private:
    int index(int x, int y);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BOARD_H
