#include "window.h"
#include <QApplication>
#include <QGridLayout>
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.show();

    return a.exec();
}

// Planning:

// window has a layout that consists of the board and some random buttons

// the board consists of a gridlayout and 9 squares
