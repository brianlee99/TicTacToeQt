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
public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();
    QGridLayout *grid;
    friend class Window;
    QVector<Square*> squares;
    //QVector<QPushButton*> squares;
private:
    int index(int x, int y);

signals:

public slots:

};

#endif // BOARD_H
