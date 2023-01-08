#pragma once

#include <qdialog.h>
#include "ui__3PlayersMap.h"

class _3PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_3PlayersMap(QWidget *parent = nullptr);
	~_3PlayersMap();

private:
	Ui::_3PlayersMapClass ui;
};
