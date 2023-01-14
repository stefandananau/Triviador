#pragma once

#include <qdialog.h>
#include "ui__2PlayersMap.h"
#include "numericAnswerDialog.h"
#include "multipleAnswerDialog.h"
#include "Client.h"
#include <QTimer>
class _2PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_2PlayersMap(QWidget *parent = nullptr);
;	~_2PlayersMap();

private slots:
	void setGameState();
	void sendNumericAnswerToServer();
	void sendMultipleAnswerToServer();
	void updateBackground();

private:
	Ui::_2PlayersMapClass ui;
	numericAnswerDialog* m_nad;
	multipleAnswerDialog* m_mad;
	std::vector < std::vector<QPushButton*>> islandButtons;
	Client* m_client;
	QTimer* m_timer;
	void numericQuestion(std::string Question);
	void multipleQuestion(crow::json::rvalue question);


};
