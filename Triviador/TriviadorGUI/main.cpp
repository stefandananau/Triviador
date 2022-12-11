#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Triviador.h"
#include "_2PlayersMap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    _2PlayersMap w;
    w.show();
    return a.exec();
}
