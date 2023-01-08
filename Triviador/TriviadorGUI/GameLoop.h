#pragma once

#include <QObject>
#include "Client.h"
#include "AnswerPrompt.h"

class GameLoop  : public QObject
{
	Q_OBJECT

public:
	GameLoop(QObject *parent);
	~GameLoop();
private:
	AnswerPrompt* m_answerPrompt;
};
