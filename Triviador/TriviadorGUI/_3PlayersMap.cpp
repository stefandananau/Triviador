#include "_3PlayersMap.h"

_3PlayersMap::_3PlayersMap(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));
}

_3PlayersMap::~_3PlayersMap()
{}
