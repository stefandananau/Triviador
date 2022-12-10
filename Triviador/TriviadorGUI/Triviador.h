#pragma once
#include <qdialog.h>
#include "ui_Triviador.h"
namespace Ui {
	class Triviador;
}
class Triviador :public QDialog 
{
	Q_OBJECT

public:
	explicit Triviador(QWidget* parent = nullptr);
	~Triviador();

private:
	Ui::Dialog* ui;

};