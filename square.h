#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>

class Square : public QWidget
{
    Q_OBJECT

friend class Window;
friend class Board;

public:
    explicit Square(int i, QWidget *parent = nullptr);

signals:
    void click();

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void mousePressEvent(QMouseEvent *);

private:
    int index;
    bool occupied;
    int state;
    void setState(int next);
    void paintX(QPainter* painter);
    void paintO(QPainter* painter);
};

#endif // SQUARE_H
