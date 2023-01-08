#pragma once

#include <QWidget>
#include <string>
#include "ui_MultipleQuestionWidget.h"

class MultipleQuestionWidget : public QWidget
{
	Q_OBJECT

public:
	MultipleQuestionWidget(QWidget *parent = nullptr);
	void setQuestion(std::string question);
	~MultipleQuestionWidget();

private:
	Ui::MultipleQuestionWidgetClass ui;
	std::string m_question;
};
