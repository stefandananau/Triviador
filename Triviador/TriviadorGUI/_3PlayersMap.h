#pragma once

#include <QMainWindow>
#include "ui__3PlayersMap.h"

class _3PlayersMap : public QMainWindow
{
	Q_OBJECT

public:
	_3PlayersMap(QWidget *parent = nullptr);
	~_3PlayersMap();

private:
	Ui::_3PlayersMapClass ui;
};
