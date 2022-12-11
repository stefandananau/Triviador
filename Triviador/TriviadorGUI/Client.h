#pragma once
#include <string>
#include <crow.h>
#include <cpr/cpr.h>

class Client
{
private:

	static Client* client;
	Client() : m_option(0), m_userIn(false), m_ready(false) {};
	int m_option;
	bool m_userIn;
	bool m_ready;

	std::string m_userEmail;
	std::string m_actionResponse;

	
public:
	
	std::string loginUser(const std::string& email, const std::string& password);
	std::string registerUser(const std::string& email, const std::string& password);
	std::string addCurrentUserToLobby();
	std::string userReadyInLobby();
	
	void setCurrentUser(const std::string email);
	const std::string getCurrentUser();

	static Client* getClient();


};
