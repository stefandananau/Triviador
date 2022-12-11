#pragma once
#include <string>
#include <iostream>

class Client
{
private:
	int m_option;
	bool m_userIn;
	bool m_ready;

	std::string m_userEmail;
	std::string m_userPassword;
	std::string m_actionResponse;

	void getUserCredentials();
	void sendReadyAwaitToServer();
	void promptReady();
	void awaitGameStart();
	void checkGameState();
	void gameStarted();

public:
	Client(): m_option(0), m_userIn(false), m_ready(false) {};
	void initClient();

};

