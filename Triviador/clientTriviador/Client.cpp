#include "Client.h"
#include "LoginRegister.h"

void Client::checkGameState() {
	cpr::Response currentState = cpr::Get(cpr::Url("http://localhost/lobby/gameState"));
	auto responseInJson = crow::json::load(currentState.text);

	std::cout << responseInJson["state"];
	while (responseInJson["state"] == "waiting_for_players") {
		currentState = cpr::Get(cpr::Url("http://localhost/lobby/gameState"));
		responseInJson = crow::json::load(currentState.text);
	}
	std::cin >> m_option;
}

void Client::promptReady() {
	std::string promptResponse;
	cpr::Response serverReadySetResponse;

	while (!m_ready) {
		std::cout << "Ready?(Y/N)\n";
		std::cin >> promptResponse;
		if (promptResponse == std::string("Y")) {
			m_ready = true;
			serverReadySetResponse = cpr::Get(cpr::Url("http://localhost/lobby/ready?email=" + m_userEmail));
		}
	}
}

void Client::sendReadyAwaitToServer() {
	cpr::Response serverLobbyResponse = cpr::Get(cpr::Url("http://localhost/lobby?email=" + m_userEmail));
	std::cout << std::endl;
	std::cout << serverLobbyResponse.raw_header<<"\n";
	std::cout << std::endl;
	
}

void Client::initClient() {
	getUserCredentials();
	sendReadyAwaitToServer();
	promptReady();
	checkGameState();
}

void Client::getUserCredentials()
{
	std::cout << "Choose an option:\n";
	std::cout << "1) Login an user:\n";
	std::cout << "2) Register an user:\n";

	std::cin >> m_option;

	while (!m_userIn) {
		switch (m_option) {
		case 1:
			std::cout << "Enter user email:\n";
			std::cin >> m_userEmail;
			std::cout << "Enter user password:\n";
			std::cin >> m_userPassword;
			m_actionResponse = ClientHelper::loginUser(m_userEmail, m_userPassword);
			if (m_actionResponse == "login succesful") {
				m_userIn = true;
			}
			else
				std::cout << m_actionResponse << std::endl;
			break;
		case 2:
			std::cout << "Enter user email:\n";
			std::cin >> m_userEmail;
			std::cout << "Enter user password:\n";
			std::cin >> m_userPassword;
			m_actionResponse = ClientHelper::registerUser(m_userEmail, m_userPassword);
			if (m_actionResponse == "register succesful") {
				m_userIn = true;
			}
			else
				std::cout << m_actionResponse << std::endl;
			break;
		default:
			std::cout << "Please choose an option in the range of possible options(1-2).\n";
			break;
		}
	}
	if (m_userIn) {
		std::cout << "Logged in as: " << m_userEmail << std::endl;

	}
}

