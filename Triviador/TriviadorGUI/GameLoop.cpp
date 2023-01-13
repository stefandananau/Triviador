#include "GameLoop.h"
#include "numericAnswerDialog.h"

void GameLoop::printTestOrder() {
	qDebug() << "Button pressed!";
}

GameLoop::GameLoop(QObject *parent)
	: QObject(parent)
{
	Client* client = Client::getClient();
	std::string serverState = client->getGameState();

	while (serverState != "waiting_for_question_answer") {
		Sleep(1000);
		m_clientState = GameLoop::state::WAITING_ON_SERVER_STATE;
		serverState = client->getGameState();
	}

	cpr::Response currentQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/currentQuestion"));
	auto questionJson = crow::json::load(currentQuestionResponse.text);
	
	if (questionJson["type"] == "numeric") {
		//numeric widget
		
		numericAnswerDialog *nad = new numericAnswerDialog();
		QEventLoop *numericAnswerDialogLoop = new QEventLoop();
		connect(nad, SIGNAL(dialogShouldClose()), this, SLOT(printTestOrder()));
		nad->show();
		qDebug() << "In game loop";

		//with show, it runs multithreaded
		//with exec, it waits for the dialog to close and keeps alive 
	}
	else {
		//multiple widget


	}


	//cpr::Response answerQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/questionAnswer?email=" + m_userEmail + "&answer=" + answer));

}

GameLoop::~GameLoop()
{}
