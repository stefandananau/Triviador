#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include  "_3PlayersMap.h"
int main(int argc, char *argv[])
{
    Client::getClient()->getMatchState();
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    return a.exec();
}
