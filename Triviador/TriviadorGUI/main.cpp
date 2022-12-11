#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Triviador.h"
#include "_4PlayersMap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    _4PlayersMap w;
    w.show();
    return a.exec();
}
