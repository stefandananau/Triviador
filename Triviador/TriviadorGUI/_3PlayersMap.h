#pragma once

#include <qdialog.h>
#include "ui__3PlayersMap.h"
#include  <QTimer>
class _3PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_3PlayersMap(QWidget *parent = nullptr);
	~_3PlayersMap();

public slots:
	void updateBackground();
private:
	Ui::_3PlayersMapClass ui;
	QTimer* m_timer;
};
