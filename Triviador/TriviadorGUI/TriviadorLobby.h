#pragma once
#include <QMainWindow>
#include <QCloseEvent>
#include "ui_TriviadorLobby.h"
#include "Client.h"
#include "UpdateThread.h"
#include "_2PlayersMap.h"
#include "_3PlayersMap.h"
#include "_4PlayersMap.h"

class TriviadorLobby :public QMainWindow
{
	Q_OBJECT

public:
	explicit TriviadorLobby(QWidget* parent = nullptr);
	~TriviadorLobby();

signals:
	void TriviadorClosed();

private slots:
	void on_joinButton_clicked();
	void on_leaveButton_clicked();
	void on_readyButton_clicked();
	void on_unreadyButton_clicked();
private:
	void closeEvent(QCloseEvent* event);
	void updateLobby();
	Ui::TriviadorLobby ui;
	UpdateThread* updateThread;
	_2PlayersMap* map2players;
	_3PlayersMap* map3players;
	_4PlayersMap* map4players;
public slots:
	void updateSignal();
	void closeGameWindowSignal();
};