#include "Client.h"
Client* Client::client;

std::string Client::registerUser(const std::string& email, const std::string& password) {
	std::string registerRequest = std::string("http://localhost/authentication?register&email=" + email + "&password=" + password);
	auto response = cpr::Get(cpr::Url(registerRequest));
	return response.text;
}

std::string Client::loginUser(const std::string& email, const std::string& password) {
	std::string loginRequest = std::string("http://localhost/authentication?login&email=" + email + "&password=" + password);
	auto response = cpr::Get(cpr::Url(loginRequest));
	return response.text;
}

std::string Client::addCurrentUserToLobby()
{
	auto serverLobbyResponse = cpr::Get(cpr::Url("http://localhost/lobby/join?email=" + m_userEmail));
	return serverLobbyResponse.text;
}

std::string Client::removeCurrentUserFromLobby()
{
	auto serverLobbyResponse = cpr::Get(cpr::Url("http://localhost/lobby/exit?email=" + m_userEmail));
	return serverLobbyResponse.text;
}

std::string Client::userReadyInLobby()
{
	auto serverReadySetResponse = cpr::Get(cpr::Url("http://localhost/lobby/ready?email=" + m_userEmail));
	return serverReadySetResponse.text;
}

std::string Client::userUnreadyInLobby()
{
	auto serverReadySetResponse = cpr::Get(cpr::Url("http://localhost/lobby/unready?email=" + m_userEmail));
	return serverReadySetResponse.text;
}

void Client::setLoggedInUser(const std::string email) {
	m_userEmail = email;
}

const std::string Client::getLoggedInUser() {
	return m_userEmail;
}

const std::vector<std::pair<std::string, bool>> Client::getLobbyUsers()
{
	auto readyUsersResponse = cpr::Get(cpr::Url("http://localhost/lobby/rplayers"));
	auto unreadyUsersResponse = cpr::Get(cpr::Url("http://localhost/lobby/uplayers"));
	nlohmann::json ready = nlohmann::json::parse(readyUsersResponse.text);
	nlohmann::json unready = nlohmann::json::parse(unreadyUsersResponse.text);

	std::vector<std::pair<std::string, bool>> lobbyUsers;
	for (std::string s : ready) {
		lobbyUsers.push_back(std::make_pair(s, true));
	}
	for (std::string s : unready) {
		lobbyUsers.push_back(std::make_pair(s, false));
	}
	return lobbyUsers;
}


std::string Client::getGameState()
{
	cpr::Response currentState = cpr::Get(cpr::Url("http://localhost/lobby/gameState"));
	auto responseInJson = nlohmann::json::parse(currentState.text);
	
	return responseInJson["state"];
}

void Client::attackIsland(int height, int width)
{
	std::string widthS = "&width=" + std::to_string(width);
	std::string heightS = "height=" + std::to_string(height);
	std::string attacker = "&attacker=" + m_userEmail;
	std::string str;
	str = "http://localhost/game/attacker?" + heightS + widthS + attacker;
	cpr::Response response = cpr::Get(cpr::Url(str));
	
}

bool Client::isPermutationMade()
{
	cpr::Response permutatiomMade = cpr::Get(cpr::Url("http://localhost/game/nextPermutation"));
	auto responseInJson = nlohmann::json::parse(permutatiomMade.text);
	return responseInJson;
}

std::pair<std::string, std::string> Client::getUserStats(const std::string& email)
{
	cpr::Response currentStats = cpr::Get(cpr::Url("http://localhost/database/getStats?email=" + email));
	auto responseInJson = nlohmann::json::parse(currentStats.text);

	return std::make_pair<std::string, std::string>(responseInJson["Number of played games"], responseInJson["Number of won games"]);
}

std::vector<std::tuple<std::string, int,std::string>> Client::getIslands()
{
	cpr::Response IslandsResponse = cpr::Get(cpr::Url("http://localhost/game/islandMap"));
	auto responseInJson = nlohmann::json::parse(IslandsResponse.text);
	std::vector<std::tuple<std::string, int,std::string>> islands;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
		std::string owner = responseInJson[i][j][0];
		int points = responseInJson[i][j][1].get<int>();
		std::string color = responseInJson[i][j][2];
		
		std::tuple<std::string, int,std::string> p = std::make_tuple(owner, points,color);	
		islands.push_back(p);
		}
	}
	return islands;
}

std::string Client::getCurrentPlayer()
{
	cpr::Response currentPlayer = cpr::Get(cpr::Url("http://localhost/game/getCurrentPlayer"));

	auto responseInJson = nlohmann::json::parse(currentPlayer.text);
	if (currentPlayer.status_code != 205)
	{
		return responseInJson;
	}
	else
	{
		return std::string("null");
	}
	}

void Client::popCurrentPlayer()
{
	cpr::Response numberOfPlayersResponse = cpr::Get(cpr::Url("http://localhost/game/popCurrentPlayer"));
}

void Client::swapToGameInProgress()
{
	cpr::Response swap = cpr::Get(cpr::Url("http://localhost/game/swapGameInProgress"));
}


int Client::getNumberOfPlayersInLobby()
{
	cpr::Response numberOfPlayersResponse = cpr::Get(cpr::Url("http://localhost/game/numberOfPlayersInLobby"));
	auto numberOfPlayers = nlohmann::json::parse(numberOfPlayersResponse.text);
	return numberOfPlayers["numberOfPlayers"];
}

std::string Client::getRoundWinner() {
	cpr::Response winnerResponse = cpr::Get(cpr::Url("http://localhost/game/validateAnswer"));
	auto winner = nlohmann::json::parse(winnerResponse.text);
	return winner[0];
}
bool Client::multipleWinners() {
	cpr::Response winnerResponse = cpr::Get(cpr::Url("http://localhost/game/validateAnswer"));
	auto winner = nlohmann::json::parse(winnerResponse.text);
	if(winner.size()!=1)
	{
		return false;
	}
	return true;
}

void Client::waitGameState(std::string state) {
	std::string currentState = getGameState();
	while (currentState != state) {
		Sleep(1000);
		currentState = getGameState();
	}
}

crow::json::rvalue Client::getCurrentQuestion() {
	cpr::Response currentQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/currentQuestion"));
	auto questionJson = crow::json::load(currentQuestionResponse.text);
	return questionJson;
}

std::string Client::getMatchPhase() {
	cpr::Response currentQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/matchPhase"));
	auto questionJson = nlohmann::json::parse(currentQuestionResponse.text);

	return questionJson;
}

std::vector<std::string> Client::nextPermutation()
{
	cpr::Response currentQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/nextPermutation"));
	auto playersPermutations = nlohmann::json::parse(currentQuestionResponse.text);
	return playersPermutations;
}

void Client::makePermutation() {
	cpr::Response currentQuestionResponse = cpr::Get(cpr::Url("http://localhost/game/makePermutation"));
}

Client* Client::getClient()
{
	if (client == nullptr) {
		client = new Client();
	}
	return client;
}


