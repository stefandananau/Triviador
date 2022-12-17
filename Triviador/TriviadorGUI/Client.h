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
	int getNumberOfPlayersInLobby();
	void setCurrentUser(const std::string email);
	const std::string getCurrentUser();
	const std::vector<std::pair<std::string, bool>> getLobbyUsers();

	static Client* getClient();


};
