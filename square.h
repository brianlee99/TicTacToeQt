#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>

class QLabel;
class QHBoxLayout;

class Square : public QWidget
{
    Q_OBJECT
public:
    explicit Square(int i, QWidget *parent = nullptr);
    friend class Window;
    friend class Board;
signals:
    void click();
protected:
//    void paintEvent(QPaintEvent *e);

public slots:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
private:
    void setState(int next);
    int index;
    bool occupied;
    int state;
    void paintX(QPainter* painter);
//    void paintO(QPainter* painter);
};

#endif // SQUARE_H
