#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include <cstring>
#include "Client.h"
#include "TriviadorLobby.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//register
    void on_pushButton_2_clicked();//login
	void on_toolButton_pressed();
	void on_toolButton_released();
public slots:
    void TriviadorClosed();
   
private:
    Ui::MainWindowClass ui;
    TriviadorLobby* triv;

};
