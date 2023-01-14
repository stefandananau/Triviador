#pragma once

#include <qdialog.h>
#include "ui__2PlayersMap.h"
#include "numericAnswerDialog.h"
#include "multipleAnswerDialog.h"
#include "Client.h"

class _2PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_2PlayersMap(QWidget *parent = nullptr);
;	~_2PlayersMap();

private slots:
	void setGameState();
	void sendNumericAnswerToServer();

private:
	Ui::_2PlayersMapClass ui;
	numericAnswerDialog* m_nad;
	multipleAnswerDialog* m_mad;
	Client* m_client;

	void numericQuestion(std::string Question);
	void multipleQuestion(crow::json::rvalue question);


};
