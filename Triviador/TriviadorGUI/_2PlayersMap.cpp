#include "_2PlayersMap.h"
#include <QDateTime>

void _2PlayersMap::multipleQuestion(crow::json::rvalue Question) {
	//numeric widget
	m_mad = new multipleAnswerDialog(nullptr, Question["question"].s(), Question["answer"].s(), Question["wrong_answer1"].s(), Question["wrong_answer2"].s(), Question["wrong_answer3"].s());

	//m_nad communitcates with game loop through following connect(calls sendAnswerToServer on answer button press)

	connect(m_mad, SIGNAL(dialogShouldClose()), this, SLOT(sendMultipleAnswerToServer()));
	m_mad->show();
	qDebug() << "In game loop";

	//with show, it runs multithreaded
	//with exec, it waits for the dialog to close 
}

void _2PlayersMap::numericQuestion(std::string Question) {
	//numeric widget
	m_nad = new numericAnswerDialog(nullptr, Question);

	//m_nad communitcates with game loop through following connect(calls sendAnswerToServer on answer button press)

	connect(m_nad, SIGNAL(dialogShouldClose()), this, SLOT(sendNumericAnswerToServer()));
	m_nad->show();
	qDebug() << "In game loop";

	//with show, it runs multithreaded
	//with exec, it waits for the dialog to close 
}

_2PlayersMap::_2PlayersMap(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateBackground()));
	m_timer->start(1000);

	islandButtons.resize(3);
	islandButtons[0].resize(3);
	islandButtons[1].resize(3);
	islandButtons[2].resize(3);
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
	m_client->waitGameState("waiting_for_question_answer");

	crow::json::rvalue question = m_client->getCurrentQuestion();

	if (question["type"] == "numeric") {
		numericQuestion(question["question"].s());
	}
	else {
		multipleQuestion(question);
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

void _2PlayersMap::sendNumericAnswerToServer() {
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

void _2PlayersMap::sendMultipleAnswerToServer() {
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
	delete m_mad;

	std::string gameState = m_client->getGameState();
	while (gameState != "show_answers")
	{
		Sleep(1000);
		gameState = m_client->getGameState();
	}

	qDebug() << "All players answered!\n";

	setGameState();
}
void _2PlayersMap::updateBackground()
{
	std::vector<QString> backgroundImages;
	backgroundImages.push_back(":/new/prefix1/images/water-2.png");
	backgroundImages.push_back(":/new/prefix1/images/water-3.png");
	backgroundImages.push_back(":/new/prefix1/images/water-4.png");
	backgroundImages.push_back(":/new/prefix1/images/water-5.png");
	backgroundImages.push_back(":/new/prefix1/images/water-6.png");
	int index = QTime::currentTime().second() % backgroundImages.size();
	this->setStyleSheet("background-image: url(" + backgroundImages[index] + ");");


}
_2PlayersMap::~_2PlayersMap()
{}
