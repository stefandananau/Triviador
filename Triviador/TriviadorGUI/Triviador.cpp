#include "Triviador.h"
#include "ui_Triviador.h"
using namespace std::chrono_literals;
Triviador::Triviador(QWidget* parent)
    :
    QDialog(parent),
    ui(new Ui::Triviador)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));

    ui->label_3->setText(Client::getClient()->getCurrentUser().c_str());
    
    this->updateThread = new UpdateThread(this);
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
        delete updateThread;
        updateThread = new UpdateThread(this);
        connect(updateThread, SIGNAL(updateSignal()), this, SLOT(updateSignal()));
        updateThread->start();

    }
    else {
        this->ui->message->setText(response.c_str());
    }
}

void Triviador::on_leaveButton_clicked()
{
    std::string response = Client::getClient()->removeCurrentUserFromLobby();
    if (response == "exit lobby") {
        this->ui->joinButton->setEnabled(true);
        this->ui->leaveButton->setEnabled(false);
        this->ui->readyButton->setEnabled(false);
        this->ui->unreadyButton->setEnabled(false);
        this->ui->userLobbyText->setText("");

        updateThread->terminate();
    }
    else {
        this->ui->message->setText(response.c_str());
    }
    
}

void Triviador::on_readyButton_clicked()
{
    std::string response = Client::getClient()->userReadyInLobby();
    if (response == "user ready") {
        this->ui->leaveButton->setEnabled(false);
        this->ui->readyButton->setEnabled(false);
        this->ui->unreadyButton->setEnabled(true);
    }
    else {
        this->ui->message->setText(response.c_str());
    }
}

void Triviador::on_unreadyButton_clicked()
{
    std::string response = Client::getClient()->userUnreadyInLobby();
    if (response == "user unready") {
        this->ui->leaveButton->setEnabled(true);
        this->ui->readyButton->setEnabled(true);
        this->ui->unreadyButton->setEnabled(false);
    }
    else {
        this->ui->message->setText(response.c_str());
    }
}

void Triviador::on_searchUserButton_clicked()
{
    std::string email = this->ui->lineEdit->text().toUtf8().constData();
    std::pair<std::string, std::string> stats = Client::getClient()->getUserStats(email);
    this->ui->label_14->setText(email.c_str());
    this->ui->label_11->setText(stats.first.c_str());
    this->ui->label_9->setText(stats.second.c_str());
}

void Triviador::updateLobby()
{
    
        std::string newText;
        int nrUsers = 0;
        int nrReadyUsers = 0;
        for (std::pair<std::string, bool> p : Client::getClient()->getLobbyUsers()) {
            std::string active = p.second ? " ready" : " not ready";
            nrUsers++;
            if(p.second)
                nrReadyUsers++;
            newText = newText + p.first + active;
            newText = newText + "\n";
        }
        newText = newText + std::to_string(nrReadyUsers) + "/" + std::to_string(nrUsers) + " ready";
        this->ui->userLobbyText->setText(newText.c_str());
    
}

void Triviador::reject()
{
    if (updateThread->isRunning()) {
        updateThread->terminate();
    }
    delete updateThread;
    Client::getClient()->userUnreadyInLobby();
    Client::getClient()->removeCurrentUserFromLobby();
    emit TriviadorClosed();
    QDialog::reject();
}

void Triviador::closeGameWindowSignal()
{
    updateThread = new UpdateThread(this);
    connect(updateThread, SIGNAL(updateSignal()), this, SLOT(updateSignal()));
    updateThread->start();
    this->show();
}

void Triviador::updateSignal() {
    updateLobby();
    if (Client::getClient()->getGameState() != "waiting_for_players") { 
        updateThread->terminate();
        int playerNumber = 2;
        emit GameStarted();
    }
}






