#pragma once

#include <QDialog>
#include "ui_numericAnswerDialog.h"

class numericAnswerDialog : public QDialog
{
	Q_OBJECT

public:
	numericAnswerDialog(QWidget *parent = nullptr, std::string question = "");
	QString getAnswer();
	~numericAnswerDialog();

private slots:
	void on_answerButton_pressed();

signals:
	void dialogShouldClose();

private:
	Ui::numericAnswerDialogClass ui;
};
