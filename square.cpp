#include "square.h"
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>


Square::Square(int i, QWidget *parent) :
    QWidget(parent),
    index(i),
    state(""),
    occupied(false)
{
    button = new QPushButton(this);
    // make QPushButton a square
    button->setFixedSize(200, 200);

    QHBoxLayout* layout = new QHBoxLayout();

    button->setText(state);

    layout->addWidget(button);

    setLayout(layout);

}

