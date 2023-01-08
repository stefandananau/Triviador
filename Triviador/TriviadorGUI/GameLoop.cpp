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
	std::cout << questionJson["question"] << "\n";

	std::string answer;
	//here should spawn answer prompt
	m_answerPrompt = new AnswerPrompt();
	m_answerPrompt->show();


	//cpr::Response answerQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/questionAnswer?email=" + m_userEmail + "&answer=" + answer));

}

GameLoop::~GameLoop()
{}
