#include "MainWindow.h"
#include "_4PlayersMap.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    _4PlayersMap w;
    w.show();
    return a.exec();
}
