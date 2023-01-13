#include "numericAnswerDialog.h"

numericAnswerDialog::numericAnswerDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	
}
void numericAnswerDialog::on_answerButton_pressed() {
	emit dialogShouldClose();
	delete this;
}

numericAnswerDialog::~numericAnswerDialog()
{}
