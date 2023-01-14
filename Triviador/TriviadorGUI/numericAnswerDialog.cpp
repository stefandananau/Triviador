#include "numericAnswerDialog.h"
#include <QMessageBox>


numericAnswerDialog::numericAnswerDialog(QWidget *parent,std::string question)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/island5-removebg-preview.png"));
	ui.question->setText(question.c_str());
	timer.start();
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
	m_elapsedTime = static_cast<uint64_t>(timer.elapsed());
	
	//delete this;
}

uint64_t numericAnswerDialog::getAnswerTime() {
	return m_elapsedTime;
}

numericAnswerDialog::~numericAnswerDialog()
{}
