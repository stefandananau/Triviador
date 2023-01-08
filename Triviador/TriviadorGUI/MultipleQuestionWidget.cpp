#include "MultipleQuestionWidget.h"

MultipleQuestionWidget::MultipleQuestionWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void MultipleQuestionWidget::setQuestion(std::string question) {
	this->ui.question->setPlainText(question.c_str());
}

MultipleQuestionWidget::~MultipleQuestionWidget()
{}
