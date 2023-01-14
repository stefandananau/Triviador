#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include  "_3PlayersMap.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    _3PlayersMap w;
    w.show();
    return a.exec();
}
