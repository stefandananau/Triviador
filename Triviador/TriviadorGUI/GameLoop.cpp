#include "GameLoop.h"

GameLoop::GameLoop(QObject *parent)
	: QObject(parent)
{
	Client* client = Client::getClient();
	std::string state = client->getGameState();

	while (state != "waiting_for_question_answer") {
		Sleep(1000);
		state = client->getGameState();
	}

	cpr::Response currentQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/currentQuestion"));
	auto questionJson = crow::json::load(currentQuestionResponse.text);
	if (questionJson["type"] == "numeric") {
		//numeric widget
		m_numericQuestionWidget = new NumericQuestionWidget();
		m_numericQuestionWidget->setQuestion(questionJson["question"].s());
		m_numericQuestionWidget->show();

		//get answer somehow
	}
	else {
		//multiple widget
		m_multipleQuestionWidget = new MultipleQuestionWidget();
		m_multipleQuestionWidget->setQuestion(questionJson["question"].s());
		m_multipleQuestionWidget->show();

	}


	//cpr::Response answerQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/questionAnswer?email=" + m_userEmail + "&answer=" + answer));

}

GameLoop::~GameLoop()
{}
