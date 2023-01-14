#pragma once

#include <QDialog>
#include "ui_multipleAnswerDialog.h"
#include <algorithm>

class multipleAnswerDialog : public QDialog
{
	Q_OBJECT

public:
	multipleAnswerDialog(QWidget *parent = nullptr, std::string question = "",std::string ranswer="", std::string wanswer1 = "", std::string wanswer2 = "", std::string wanswer3 = "" );
	~multipleAnswerDialog();
private slots:
	
	void on_answer1Button_pressed();

signals:
	void dialogShouldClose();

private:
	Ui::multipleAnswerDialogClass ui;
};
