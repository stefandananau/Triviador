#include "MainWindow.h"
#include "_3PlayersMap.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    _3PlayersMap w;
    w.show();
    return a.exec();
}
