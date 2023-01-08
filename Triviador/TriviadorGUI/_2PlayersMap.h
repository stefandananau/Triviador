#pragma once

#include <qdialog.h>
#include "ui__2PlayersMap.h"
#include "GameLoop.h"

class _2PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_2PlayersMap(QWidget *parent = nullptr);
	~_2PlayersMap();
	
private:
	Ui::_2PlayersMapClass ui;
	GameLoop *gameLoop;
};
