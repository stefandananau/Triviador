#include "_4PlayersMap.h"

_4PlayersMap::_4PlayersMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));
}

_4PlayersMap::~_4PlayersMap()
{}
