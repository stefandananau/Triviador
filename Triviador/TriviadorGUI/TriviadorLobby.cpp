#include "TriviadorLobby.h"
using namespace std::chrono_literals;
TriviadorLobby::TriviadorLobby(QWidget* parent)
    :
    QMainWindow(parent)
{
    ui.setupUi(this);
    ui.label_3->setText(Client::getClient()->getCurrentUser().c_str());

    this->updateThread = new UpdateThread(this);
}

TriviadorLobby::~TriviadorLobby()
{
   
}

void TriviadorLobby::on_joinButton_clicked() {
    std::string response = Client::getClient()->addCurrentUserToLobby();
    if (response == "joined lobby") {
        this->ui.joinButton->setEnabled(false);
        this->ui.leaveButton->setEnabled(true);
        this->ui.readyButton->setEnabled(true);
        delete updateThread;
        updateThread = new UpdateThread(this);
        connect(updateThread, SIGNAL(updateSignal()), this, SLOT(updateSignal()));
        updateThread->start();

    }
    else {
        this->ui.message->setText(response.c_str());
    }
}

void TriviadorLobby::on_leaveButton_clicked()
{
    std::string response = Client::getClient()->removeCurrentUserFromLobby();
    if (response == "exit lobby") {
        this->ui.joinButton->setEnabled(true);
        this->ui.leaveButton->setEnabled(false);
        this->ui.readyButton->setEnabled(false);
        this->ui.unreadyButton->setEnabled(false);
        this->ui.userLobbyText->setText("");

        updateThread->terminate();
    }
    else {
        this->ui.message->setText(response.c_str());
    }

}

void TriviadorLobby::on_readyButton_clicked()
{
    std::string response = Client::getClient()->userReadyInLobby();
    if (response == "user ready") {
        this->ui.leaveButton->setEnabled(false);
        this->ui.readyButton->setEnabled(false);
        this->ui.unreadyButton->setEnabled(true);
    }
    else {
        this->ui.message->setText(response.c_str());
    }
}

void TriviadorLobby::on_unreadyButton_clicked()
{
    std::string response = Client::getClient()->userUnreadyInLobby();
    if (response == "user unready") {
        this->ui.leaveButton->setEnabled(true);
        this->ui.readyButton->setEnabled(true);
        this->ui.unreadyButton->setEnabled(false);
    }
    else {
        this->ui.message->setText(response.c_str());
    }
}

void TriviadorLobby::updateLobby()
{

    std::string newText;
    int nrUsers = 0;
    int nrReadyUsers = 0;
    for (std::pair<std::string, bool> p : Client::getClient()->getLobbyUsers()) {
        std::string active = p.second ? " ready" : " not ready";
        nrUsers++;
        if (p.second)
            nrReadyUsers++;
        newText = newText + p.first + active;
        newText = newText + "\n";
    }
    newText = newText + std::to_string(nrReadyUsers) + "/" + std::to_string(nrUsers) + " ready";
    this->ui.userLobbyText->setText(newText.c_str());

}

void TriviadorLobby::closeGameWindowSignal()
{
    updateThread = new UpdateThread(this);
    connect(updateThread, SIGNAL(updateSignal()), this, SLOT(updateSignal()));
    updateThread->start();
    this->show();
}
void TriviadorLobby::closeEvent(QCloseEvent* event) {
    if (updateThread->isRunning()) {
        updateThread->terminate();
    }
    delete updateThread;
    Client::getClient()->userUnreadyInLobby();
    Client::getClient()->removeCurrentUserFromLobby();
    emit TriviadorClosed();
    event->accept();
}

void TriviadorLobby::updateSignal() {
    updateLobby();
    if (Client::getClient()->getGameState() != "waiting_for_players") {
        updateThread->terminate();
        //this->hide();
        int playerNumber = 2;
        switch (playerNumber) {
        case 2:
            map2players = new _2PlayersMap();
            map2players->show();
            break;
        case 3:
            map3players = new _3PlayersMap();
            map3players->show();
            break;
        case 4:
            map4players = new _4PlayersMap();
            map4players->show();
            break;
        }
    }
}