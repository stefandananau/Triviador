#include "multipleAnswerDialog.h"

multipleAnswerDialog::multipleAnswerDialog(QWidget *parent, std::string question,std::string ranswer, std::string wanswer1 , std::string wanswer2 , std::string wanswer3)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.question->setText(question.c_str());
	std::vector<std::string> answers = { ranswer,wanswer1 ,wanswer2 ,wanswer3 };
	std::random_shuffle(answers.begin(), answers.end());

}

multipleAnswerDialog::~multipleAnswerDialog()
{}

QString multipleAnswerDialog::getAnswer() {
	if (ui.answer->text().size() != 0) {
		return ui.answer->text();
	}
	else {
		return "NaN";
	}
}

void multipleAnswerDialog::on_answer1Button_pressed() {
		emit dialogShouldClose();
	
	
}