#include "_2PlayersMap.h"

_2PlayersMap::_2PlayersMap(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));
	islandButtons.reserve(3);
	islandButtons[0].reserve(3);
	islandButtons[1].reserve(3);
	islandButtons[2].reserve(3);
	std::string island = "island";
	for (QObject* push : this->children()) {
		std::string name = push->objectName().toUtf8().constData();
		if (name.find(island) != std::string::npos) {
			int pos1 = name[name.length() - 2] - '0';
			int pos2 = name[name.length() - 1] - '0';
			islandButtons[pos1][pos2] = (QPushButton*)push;
		}
	}
	m_client = Client::getClient();

	//this is where match script will go, 
	//TO DO: Make methods out of bare code.
	//		 Create second dialog for multiple choice questions
	//		 Implement dueling and keep track of player score, assign colors to each player and declare winner
	//
	m_client = Client::getClient();
	std::string serverState = m_client->getGameState();

	while (serverState != "waiting_for_question_answer") {
		Sleep(1000);
		//m_clientState = GameLoop::state::WAITING_ON_SERVER_STATE;
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


	//gameLoop = new GameLoop(this);
	//connect(gameLoop, SIGNAL(shouldSetGameState()), this, SLOT(setGameState()));
	qDebug() << "Back to main";
}

void _2PlayersMap::setGameState(){
	if (m_client->getGameState() == "show_answers") {
		QString winner;
		std::string roundwinner = m_client->getRoundWinner();
		for (uint16_t i = 0; i < roundwinner.size(); i++) {
			winner.push_back(roundwinner[i]);
		}
		ui.GameState->setText("round winner:" + winner);
	}

}

void _2PlayersMap::sendAnswerToServer() {
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

	qDebug() << "All players answered!\n";

	setGameState();
}

_2PlayersMap::~_2PlayersMap()
{}
