#pragma once
#include <string>

class Client
{
private:
	int m_option;
	bool m_userIn;

	std::string userId;
	std::string m_userEmail;
	std::string m_userPassword;
	std::string m_actionResponse;

	void getUserCredentials();
	void sendGameAwaitToServer();

public:
	Client(): m_option(0), m_userIn(false){};
	void initClient();

};

