#pragma once

#include <qdialog.h>
#include "ui__2PlayersMap.h"
#include "numericAnswerDialog.h"
#include "Client.h"

class _2PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_2PlayersMap(QWidget *parent = nullptr);

;	~_2PlayersMap();

private slots:
	void setGameState();
	void sendAnswerToServer();

private:
	Ui::_2PlayersMapClass ui;
	numericAnswerDialog* m_nad;
	Client* m_client;

};
