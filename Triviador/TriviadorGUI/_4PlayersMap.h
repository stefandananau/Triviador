#pragma once

#include <QMainWindow>
#include "ui__4PlayersMap.h"

class _4PlayersMap : public QMainWindow
{
	Q_OBJECT

public:
	_4PlayersMap(QWidget *parent = nullptr);
	~_4PlayersMap();

private:
	Ui::_4PlayersMapClass ui;
};
