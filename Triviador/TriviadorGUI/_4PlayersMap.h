#pragma once

#include <qdialog>
#include "ui__4PlayersMap.h"
#include <QTimer>

class _4PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_4PlayersMap(QWidget *parent = nullptr);
	~_4PlayersMap();

	


private:
	Ui::_4PlayersMapClass ui;
	QTimer* m_timer;

public slots:
	void updateBackground();
};
