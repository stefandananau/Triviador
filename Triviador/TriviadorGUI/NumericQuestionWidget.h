#pragma once

#include <QWidget>
#include <QString>
#include "ui_NumericQuestionWidget.h"

class NumericQuestionWidget : public QWidget
{
	Q_OBJECT

public:
	NumericQuestionWidget(QWidget *parent = nullptr);
	void setQuestion(std::string question);
	std::string getAnswer();
	~NumericQuestionWidget();

private slots:
	void on_answerButton_pressed();

private:
	Ui::NumericQuestionWidgetClass ui;
	std::string m_question;
	std::string m_answer;
};
