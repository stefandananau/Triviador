#include "numericAnswerDialog.h"

numericAnswerDialog::numericAnswerDialog(QWidget *parent,std::string question)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/island5-removebg-preview.png"));
	ui.question->setText(question.c_str());
}

QString numericAnswerDialog::getAnswer() {
	if (ui.answer->text().size() != 0) {
		return ui.answer->text();
	}
	else {
		return "NaN";
	}
}

void numericAnswerDialog::on_answerButton_pressed() {
	if (ui.answer->text() != "")
		emit dialogShouldClose();
	else
		ui.actionResponse->setText("Answer should not be empty!");
	//delete this;
}

numericAnswerDialog::~numericAnswerDialog()
{}
