#include "multipleAnswerDialog.h"

#include <QMessageBox>

multipleAnswerDialog::multipleAnswerDialog(QWidget* parent, std::string question, std::string ranswer, std::string wanswer1, std::string wanswer2, std::string wanswer3)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.question->setText(question.c_str());
	std::vector<std::string> answers = { ranswer,wanswer1 ,wanswer2 ,wanswer3 };
	std::shuffle(answers.begin(), answers.end(), std::default_random_engine());
	m_timer.start();
	ui.answer1Button->text() = answers[0].c_str();
	ui.answer2Button->text() = answers[1].c_str();
	ui.answer3Button->text() = answers[2].c_str();
	ui.answer4Button->text() = answers[3].c_str();
}

multipleAnswerDialog::~multipleAnswerDialog()
{}

QString multipleAnswerDialog::getAnswer() {
	if (this->m_answer != "")
		return m_answer;
	return "NaN";
}

void multipleAnswerDialog::on_answer1Button_pressed() {
	m_answer = ui.answer1Button->text();
	m_elapsedTime = static_cast<uint64_t>(m_timer.elapsed());
	emit dialogShouldClose();
}
void multipleAnswerDialog::on_answer2Button_pressed() {
	m_answer = ui.answer2Button->text();
	m_elapsedTime = static_cast<uint64_t>(m_timer.elapsed());
	emit dialogShouldClose();
}
void multipleAnswerDialog::on_answer3Button_pressed() {
	m_answer = ui.answer3Button->text();
	m_elapsedTime = static_cast<uint64_t>(m_timer.elapsed());
	emit dialogShouldClose();
}
void multipleAnswerDialog::on_answer4Button_pressed() {
	m_answer = ui.answer4Button->text();
	m_elapsedTime = static_cast<uint64_t>(m_timer.elapsed());
	emit dialogShouldClose();
}

uint64_t multipleAnswerDialog::getAnswerTime() {
	return m_elapsedTime;
}