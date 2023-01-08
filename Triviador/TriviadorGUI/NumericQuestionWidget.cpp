#include "NumericQuestionWidget.h"

NumericQuestionWidget::NumericQuestionWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_answer = "NaN";
}

void NumericQuestionWidget::on_answerButton_pressed(){
	QString answer = this->ui.answer->text();
	m_answer = answer.toStdString();
}

void NumericQuestionWidget::setQuestion(std::string question) {
	this->ui.question->setPlainText(QString(question.c_str()));
}

std::string NumericQuestionWidget::getAnswer() {
	return m_answer;
}

NumericQuestionWidget::~NumericQuestionWidget()
{}
