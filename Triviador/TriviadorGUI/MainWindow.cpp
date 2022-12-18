#include "MainWindow.h"
#include <QFontDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButton_clicked()
{
    std::string email = this->ui.lineEdit->text().toUtf8().constData();
    std::string password = this->ui.lineEdit_2->text().toUtf8().constData();
    std::string response = Client::getClient()->registerUser(email, password);
    std::string error = "server is offline";
    if (response == "") {
        QMessageBox::warning(this, "ERROR", error.c_str());
    }
    this->ui.label->setText(response.c_str());
}

void MainWindow::on_pushButton_2_clicked()
{
    std::string email = this->ui.lineEdit->text().toUtf8().constData();
    std::string password = this->ui.lineEdit_2->text().toUtf8().constData();
    std::string response = Client::getClient()->loginUser(email, password);
    std::string error = "server is offline";
    if (response == "") {
        QMessageBox::warning(this, "ERROR", error.c_str());
        return;
    }
    if (response == "login succesful") {
        Client::getClient()->setCurrentUser(email);
        QApplication::processEvents();
        triv = new Triviador(this);
        connect(triv, SIGNAL(TriviadorClosed()), this, SLOT(TriviadorClosed()));
        connect(triv, SIGNAL(GameStarted()), this, SLOT(GameStarted()));
        triv->show();
        this->hide();
        this->ui.label->setText("");
    }
    else {
        this->ui.label->setText(response.c_str());
    }
}

void MainWindow::on_toolButton_pressed()
{
	this->ui.lineEdit_2->setEchoMode(QLineEdit::Normal);
}

void MainWindow::on_toolButton_released()
{
	this->ui.lineEdit_2->setEchoMode(QLineEdit::Password);
}

void MainWindow::GameStarted()
{
   
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



void MainWindow::TriviadorClosed()
{
   this->show();
}


