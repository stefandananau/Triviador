#include "Triviador.h"
#include "ui_Triviador.h"
Triviador::Triviador(QWidget* parent)
    :
    QDialog(parent),
    ui(new Ui::Triviador)
{
    ui->setupUi(this);
    ui->label_3->setText(Client::getClient()->getCurrentUser().c_str());
}

Triviador::~Triviador()
{
    delete ui;
}

void Triviador::on_joinButton_clicked() {
    std::string response = Client::getClient()->addCurrentUserToLobby();
    if (response == "joined lobby") {
        this->ui->joinButton->setEnabled(false);
        this->ui->leaveButton->setEnabled(true);
        this->ui->readyButton->setEnabled(true);
    }
    else {
        this->ui->message->setText("something bad happened");
    }
}

void Triviador::on_leaveButton_clicked()
{
    //not implemented yet;
}

void Triviador::on_readyButton_clicked()
{
    std::string response = Client::getClient()->userReadyInLobby();
    if (response == "user ready") {
        this->ui->leaveButton->setEnabled(false);
        this->ui->readyButton->setEnabled(false);
    }
    else {
        this->ui->message->setText("something bad happened");
    }
}



