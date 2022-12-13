#pragma once
#include <qdialog.h>
#include "ui_Triviador.h"
#include "Client.h"
#include "UpdateThread.h"
namespace Ui {
	class Triviador;
}
class Triviador :public QDialog 
{
	Q_OBJECT

public:
	explicit Triviador(QWidget* parent = nullptr);
	~Triviador();

private slots:
	void on_joinButton_clicked();
	void on_leaveButton_clicked();
	void on_readyButton_clicked();
	void on_unreadyButton_clicked();
private:
	void updateLobby();
	Ui::Triviador* ui;
	UpdateThread* updateThread;
public slots:
	void updateSignal();
};