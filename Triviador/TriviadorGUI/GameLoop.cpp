#include "GameLoop.h"

void GameLoop::sendAnswerToServer() {
	QString answer;
	std::string thisClientEmail = m_client->getCurrentUser();
	
	answer = m_nad->getAnswer();
	qDebug() << answer;
	std::string answerToStdString;
	for (uint16_t i = 0; i < answer.size(); i++) {
		answerToStdString.push_back(answer[i].unicode());
	}
	//ok. 
	// Send answer to server
	cpr::Response answerQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/questionAnswer?email=" + thisClientEmail + "&answer=" + answerToStdString));
	

	//terminate dialog
	delete m_nad;

	std::string gameState = m_client->getGameState();
	while (gameState != "show_answers")
	{
		Sleep(1000);
		gameState = m_client->getGameState();
	}
	emit(shouldSetGameState());

	
	qDebug() << "All players answered!\n";
}

QString GameLoop::getGameState() {
	std::string gameState = m_client->getGameState();

	QString stdStringToQString;
	for (int i = 0; i < gameState.size(); i++) {
		stdStringToQString.push_back(gameState[i]);
	}

	return stdStringToQString;
}

GameLoop::GameLoop(QObject *parent)
	: QObject(parent)
{
	//this is where match script will go, 
	//TO DO: Make methods out of bare code.
	//		 Create second dialog for multiple choice questions
	//		 Implement dueling and keep track of player score, assign colors to each player and declare winner
	//
	m_client = Client::getClient();
	std::string serverState = m_client->getGameState();

	while (serverState != "waiting_for_question_answer") {
		Sleep(1000);
		m_clientState = GameLoop::state::WAITING_ON_SERVER_STATE;
		serverState = m_client->getGameState();
	}

	cpr::Response currentQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/currentQuestion"));
	auto questionJson = crow::json::load(currentQuestionResponse.text);
	
	if (questionJson["type"] == "numeric") {
		//numeric widget
		m_nad = new numericAnswerDialog(nullptr, questionJson["question"].s());

		//m_nad communitcates with game loop through following connect(calls sendAnswerToServer on answer button press)

		connect(m_nad, SIGNAL(dialogShouldClose()), this, SLOT(sendAnswerToServer()));
		m_nad->show();
		qDebug() << "In game loop";

		//with show, it runs multithreaded
		//with exec, it waits for the dialog to close 
	}
	else {
		//multiple widget


	}
}

GameLoop::~GameLoop()
{}
