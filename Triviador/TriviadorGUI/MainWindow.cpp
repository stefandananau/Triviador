#include "MainWindow.h"

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
        // open next page
        return;
    }
    this->ui.label->setText(response.c_str());
}


