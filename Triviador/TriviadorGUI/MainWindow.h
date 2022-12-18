#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include <cstring>
#include "Client.h"
#include "Triviador.h"
#include "ui_MainWindow.h"
#include "_2PlayersMap.h"
#include "_3PlayersMap.h"
#include "_4PlayersMap.h"

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
    void GameStarted();
   
private:
    Ui::MainWindowClass ui;
    Triviador* triv;
    _2PlayersMap* map2players;
    _3PlayersMap* map3players;
    _4PlayersMap* map4players;
};
