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
    std::string email = this->ui.lineEdit->text().toStdString();
    std::string password = this->ui.lineEdit_2->text().toStdString();
    std::string response = Client::getClient()->registerUser(email, password);
    QMessageBox::warning(this, "register", response.c_str());
}

void MainWindow::on_pushButton_2_clicked()
{
    std::string email = this->ui.lineEdit->text().toStdString();
    std::string password = this->ui.lineEdit_2->text().toStdString();
    std::string response = Client::getClient()->loginUser(email, password);
    QMessageBox::warning(this, "login", response.c_str());
}


