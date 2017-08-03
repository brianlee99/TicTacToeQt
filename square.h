#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>
#include <QPushButton>

class QLabel;
class QPushButton;
class QHBoxLayout;

class Square : public QWidget
{
    Q_OBJECT
public:
    explicit Square(int i, QWidget *parent = nullptr);
    QPushButton* button;
    friend class Window;
    friend class Board;
signals:

public slots:
private:
    int index; // anywhere from 0 to 8
    bool occupied;  // true: if a marker was placed, false otherwise
    QString state; // 'O', 'X', or ''
//    QLabel* state;
};

#endif // SQUARE_H
