#pragma once

#include <QObject>
#include <QDebug>
#include <QEventLoop>

#include "Client.h"
#include "numericAnswerDialog.h"


class GameLoop  : public QObject
{
	Q_OBJECT

public:
	enum state {
		WAITING_PLAYER_QUESTION_RESPONSE,
		WAITING_ON_SERVER_STATE,
		SENDING_RESPONSE
	};
	GameLoop(QObject *parent = nullptr);
	state m_clientState;
	QString getGameState();
	~GameLoop();
public slots:
	void sendAnswerToServer();

signals:
	void shouldSetGameState();
	

private:
	numericAnswerDialog* m_nad;
	Client* m_client;
};
