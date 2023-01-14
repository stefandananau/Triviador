#pragma once

#include <QDialog>
#include "ui_numericAnswerDialog.h"
#include <QElapsedTimer>
class numericAnswerDialog : public QDialog
{
	Q_OBJECT

public:
	numericAnswerDialog(QWidget *parent = nullptr, std::string question = "");
	QString getAnswer();
	~numericAnswerDialog();
	uint64_t getAnswerTime();

private slots:
	void on_answerButton_pressed();

signals:
	void dialogShouldClose();

private:
	Ui::numericAnswerDialogClass ui;
	QElapsedTimer timer;
	uint64_t m_elapsedTime;
};
