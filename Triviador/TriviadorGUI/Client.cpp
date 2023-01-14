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

void Client::setCurrentUser(const std::string email) {
	m_userEmail = email;
}

const std::string Client::getCurrentUser() {
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

std::pair<std::string, std::string> Client::getUserStats(const std::string& email)
{
	cpr::Response currentStats = cpr::Get(cpr::Url("http://localhost/database/getStats?email=" + email));
	auto responseInJson = nlohmann::json::parse(currentStats.text);
	return std::make_pair<std::string, std::string>(responseInJson["Number of played games"], responseInJson["Number of won games"]);
}

std::vector<Island> Client::getIslands()
{
	cpr::Response IslandsResponse = cpr::Get(cpr::Url("http://localhost/game/islandMap"));
	auto responseInJson = nlohmann::json::parse(IslandsResponse.text);
	std::vector<Island> islands;
	for (auto isl : responseInJson["islands"]) {
		Island is;
		Player player = Player(isl["owner"]);
		is.SetOwner(player);
		is.SetIslandScore(isl["points"]);
	}
	return std::vector<Island>();
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
	return winner["winner"];
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

Client* Client::getClient()
{
	if (client == nullptr) {
		client = new Client();
	}
	return client;
}


