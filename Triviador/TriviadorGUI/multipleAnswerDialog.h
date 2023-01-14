#pragma once

#include <QDialog>
#include "ui_multipleAnswerDialog.h"
#include <random>
#include <QElapsedTimer>


class multipleAnswerDialog : public QDialog
{
	Q_OBJECT

public:
	multipleAnswerDialog(QWidget *parent = nullptr, std::string question = "",std::string ranswer="", std::string wanswer1 = "", std::string wanswer2 = "", std::string wanswer3 = "" );
	QString getAnswer();
	~multipleAnswerDialog();
private slots:
	void on_answer1Button_pressed();
	void on_answer2Button_pressed();
	void on_answer3Button_pressed();
	void on_answer4Button_pressed();


signals:
	void dialogShouldClose();

private:
	QString m_answer;
	Ui::multipleAnswerDialogClass ui;
	QElapsedTimer m_timer;
	uint64_t m_elapsedTime;
};
