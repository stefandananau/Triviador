#include "_2PlayersMap.h"

_2PlayersMap::_2PlayersMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));
	gameLoop = new GameLoop(this);
}

_2PlayersMap::~_2PlayersMap()
{}
