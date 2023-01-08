#pragma once

#include <QObject>
#include "Client.h"
#include "MultipleQuestionWidget.h"
#include "NumericQuestionWidget.h"

class GameLoop  : public QObject
{
	Q_OBJECT

public:
	GameLoop(QObject *parent);
	~GameLoop();
private:
	MultipleQuestionWidget* m_multipleQuestionWidget;
	NumericQuestionWidget* m_numericQuestionWidget;

};
