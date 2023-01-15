#pragma once

#include <qdialog.h>
#include "ui__2PlayersMap.h"
#include "numericAnswerDialog.h"
#include "multipleAnswerDialog.h"
#include "Client.h"
#include "qmessagebox.h"
#include <QTimer>
class _2PlayersMap : public QDialog
{
	Q_OBJECT

public:
	_2PlayersMap(QWidget *parent = nullptr);
;	~_2PlayersMap();

private slots:
	void setGameWinner();
	void sendNumericAnswerToServer();
	void sendMultipleAnswerToServer();
	void updateBackground();
	void pressedButton(const QString& name);
	void updateGame();
private:
	Ui::_2PlayersMapClass ui;
	numericAnswerDialog* m_nad;
	multipleAnswerDialog* m_mad;
	std::vector < std::vector<QPushButton*>> islandButtons;
	Client* m_client;
	bool isWindowShowing = false;
	QTimer* m_timer;
	QTimer* m_updateTimer;
	int height = 3;
	int width = 3;
	void getMap();
	bool islandMine(int i , int j);
	bool islandUnowned(int i, int j);
	void disableButtons();
	void enableButtons();
	void numericQuestion(std::string Question);
	void multipleQuestion(crow::json::rvalue question);
	int toUTF8(std::string& s);

};
