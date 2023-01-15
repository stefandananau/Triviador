#pragma once
#include <string>
#include <crow.h>
#include <cpr/cpr.h>
#include <vector>
#include <nlohmann/json.hpp>
class Client
{
private:

	static Client* client;
	Client() : m_userIn(false), m_ready(false) {};
	bool m_userIn;
	bool m_ready;
	int m_numberOfPlayersInLobby;
	std::string m_userEmail;
	std::string m_actionResponse;

	
public:
	
	std::string loginUser(const std::string& email, const std::string& password);
	std::string registerUser(const std::string& email, const std::string& password);
	std::string addCurrentUserToLobby();
	std::string removeCurrentUserFromLobby();
	std::string userReadyInLobby();
	std::string userUnreadyInLobby();
	std::string getGameState();
	std::pair <std::string, std::string> getUserStats(const std::string& email);
	std::vector<std::pair<std::string, int>> getIslands();
	int getNumberOfPlayersInLobby();
	void setLoggedInUser(const std::string email);
	const std::string getLoggedInUser();
	const std::vector<std::pair<std::string, bool>> getLobbyUsers();
	std::string getRoundWinner();
	void waitGameState(std::string state);
	crow::json::rvalue getCurrentQuestion();
	static Client* getClient();


};
