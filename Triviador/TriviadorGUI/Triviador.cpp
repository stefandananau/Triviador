#include "Triviador.h"
#include "ui_Triviador.h"
Triviador::Triviador(QWidget* parent)
    :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Triviador::~Triviador()
{
    
    delete ui;
}



