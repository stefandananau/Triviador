#include "_2PlayersMap.h"
#include <QDateTime>
#include <sstream>
void _2PlayersMap::multipleQuestion(crow::json::rvalue Question) {
	std::string questionStr = Question["question"].s();
	toUTF8(questionStr);

	m_mad = new multipleAnswerDialog(nullptr, Question["question"].s(), Question["answer"].s(), Question["wrong_answer1"].s(), Question["wrong_answer2"].s(), Question["wrong_answer3"].s());

	connect(m_mad, SIGNAL(dialogShouldClose()), this, SLOT(sendMultipleAnswerToServer()));
	m_mad->show();
	qDebug() << "In game loop";
}

void _2PlayersMap::getMap()
{
	std::vector <std::pair<std::string, int>> islands = Client::getClient()->getIslands();
	int n = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			std::string str = std::to_string(islands[n].second) + "\n" + islands[n].first;
			islandButtons[i][j]->setText(str.c_str());
			n++;
		}
	}
}

bool _2PlayersMap::islandMine(int i, int j) {
	std::string buttonText = islandButtons[i][j]->text().toUtf8().constData();
	if (buttonText.find(Client::getClient()->getLoggedInUser()) != std::string::npos) {
		return true;
	}
	return false;
}

bool _2PlayersMap::islandUnowned(int i, int j)
{
	std::string unowned = "unowned";
	std::string buttonText = islandButtons[i][j]->text().toUtf8().constData();
	if (buttonText.find(unowned) != std::string::npos) {
		return true;
	}
	return false;
}


void _2PlayersMap::disableButtons()
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			islandButtons[i][j]->setEnabled(false);
		}
	}
}

void _2PlayersMap::enableButtons() {
	std::string matchState = Client::getClient()->getMatchPhase();
	if (matchState == "DUEL_PHASE") {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (!islandMine(i, j)) {
					if (i > 0 && islandMine(i - 1, j)) {
						islandButtons[i][j]->setEnabled(true);
					}
					else if (j > 0 && islandMine(i, j - 1)) {
						islandButtons[i][j]->setEnabled(true);
					}
					else if (i < height - 1 && islandMine(i + 1, j)) {
						islandButtons[i][j]->setEnabled(true);
					}
					else if (j < width - 1 && islandMine(i, j + 1)) {
						islandButtons[i][j]->setEnabled(true);
					}
				}
			}
		}
	}
	else if (matchState == "MAP_BASE_PHASE") {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (islandUnowned(i, j)) {
					islandButtons[i][j]->setEnabled(true);
					if (i > 0 && !islandUnowned(i - 1, j)) {
						islandButtons[i][j]->setEnabled(false);
					}
					if (j > 0 && !islandUnowned(i, j - 1)) {
						islandButtons[i][j]->setEnabled(false);
					}
					if (i < height - 1 && !islandUnowned(i + 1, j)) {
						islandButtons[i][j]->setEnabled(false);
					}
					if (j < width - 1 && !islandUnowned(i, j + 1)) {
						islandButtons[i][j]->setEnabled(false);
					}
				}


			}
		}
	}
	else if (matchState == "MAP_DIVISION_PHASE") {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (islandUnowned(i, j)) {
					if (i > 0 && islandMine(i - 1, j)) {
						islandButtons[i][j]->setEnabled(true);
					}
					else if (j > 0 && islandMine(i, j - 1)) {
						islandButtons[i][j]->setEnabled(true);
					}
					else if (i < height - 1 && islandMine(i + 1, j)) {
						islandButtons[i][j]->setEnabled(true);
					}
					else if (j < width - 1 && islandMine(i, j + 1)) {
						islandButtons[i][j]->setEnabled(true);
					}
				}
			}
		}
	}
}

void _2PlayersMap::numericQuestion(std::string Question) {
	//numeric widget
	toUTF8(Question);
	m_nad = new numericAnswerDialog(nullptr, Question + m_client->getLoggedInUser());

	//m_nad communitcates with game loop through following connect(calls sendAnswerToServer on answer button press)

	connect(m_nad, SIGNAL(dialogShouldClose()), this, SLOT(sendNumericAnswerToServer()));
	m_nad->show();
	qDebug() << "In game loop";

	//with show, it runs multithreaded
	//with exec, it waits for the dialog to close 
}


_2PlayersMap::_2PlayersMap(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateBackground()));
	m_timer->start(1000);

	m_updateTimer = new QTimer(this);
	connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
	m_updateTimer->start(1000);

	for (QPushButton* button : findChildren<QPushButton*>())
	{
		connect(button, &QPushButton::clicked, this, [this, button]() {pressedButton(button->objectName()); });
	}
	islandButtons.resize(height);
	islandButtons[0].resize(width);
	islandButtons[1].resize(width);
	islandButtons[2].resize(width);
	std::string island = "island";
	for (QObject* push : this->children()) {
		std::string name = push->objectName().toUtf8().constData();
		if (name.find(island) != std::string::npos) {
			int pos1 = name[name.length() - 2] - '0';
			int pos2 = name[name.length() - 1] - '0';
			islandButtons[pos1][pos2] = ((QPushButton*)push);
		}
	}
	disableButtons();

	m_client = Client::getClient();
	getMap();

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

void _2PlayersMap::setGameWinner() {
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
	std::string thisClientEmail = m_client->getLoggedInUser();

	answer = m_nad->getAnswer();
	qDebug() << answer;
	std::string answerToStdString;
	for (uint16_t i = 0; i < answer.size(); i++) {
		answerToStdString.push_back(answer[i].unicode());
	}
	//ok. 
	// Send answer to server
	uint64_t time = m_nad->getAnswerTime();

	qDebug() << time;
	cpr::Response answerQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/questionAnswer?email=" + thisClientEmail + "&answer=" + answerToStdString + "&time=" + std::to_string(time)));

	//terminate dialog
	delete m_nad;

	std::string gameState = m_client->getGameState();
	while (gameState != "show_answers")
	{
		gameState = m_client->getGameState();
		Sleep(1000);

	}

	m_updateTimer->start(1000);

	qDebug() << "All players answered!\n";

	setGameWinner();
}

void _2PlayersMap::sendMultipleAnswerToServer() {
	QString answer;
	std::string thisClientEmail = m_client->getLoggedInUser();

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

	setGameWinner();
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

void _2PlayersMap::pressedButton(const QString& name)
{
	disableButtons();
	std::string bName = name.toUtf8().constData();
	int hei = bName[bName.length() - 2] - '0';
	int wid = bName[bName.length() - 1] - '0';
	Client::getClient()->attackIsland(hei, wid);
	getMap();
	Client::getClient()->popCurrentPlayer();

}

void _2PlayersMap::updateGame()
{
	getMap();
	std::string currentPlayer = Client::getClient()->getCurrentPlayer();
	std::string loggedInUser = Client::getClient()->getLoggedInUser();
	qDebug() << currentPlayer.c_str() << loggedInUser.c_str();
	if (currentPlayer == loggedInUser) {
		enableButtons();
	}

	if (Client::getClient()->getGameState() == "waiting_for_question_answer" && Client::getClient()->getMatchPhase() == "MAP_DIVISION_PHASE")
	{
		m_updateTimer->stop();
		crow::json::rvalue question = m_client->getCurrentQuestion();

		if (question["type"] == "numeric") {

			numericQuestion(question["question"].s());
		}
		else {
			multipleQuestion(question);
		}
	}
}

int _2PlayersMap::toUTF8(std::string& s) {
	size_t htmlPos = 0;
	size_t entries = 0;

	std::map<std::string, char> htmlToUtf8_map;
	htmlToUtf8_map.insert(std::make_pair("&quot;", '\"'));
	htmlToUtf8_map.insert(std::make_pair("&#039;", '\''));



	for (const auto& chr : htmlToUtf8_map) {
		while (htmlPos = s.find(chr.first) != std::string::npos) {
			s.replace(s.find(chr.first), chr.first.length(), std::string(1, chr.second));
			htmlPos += chr.first.length();
			entries++;
		}

	}
	return entries;
}


_2PlayersMap::~_2PlayersMap()
{}
