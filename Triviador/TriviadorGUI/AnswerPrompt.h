#pragma once

#include <QWidget>
#include "ui_AnswerPrompt.h"

class AnswerPrompt : public QWidget
{
	Q_OBJECT

public:
	AnswerPrompt(QWidget *parent = nullptr);
	~AnswerPrompt();

private:
	Ui::AnswerPromptClass ui;
};
