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
	auto serverLobbyResponse = cpr::Get(cpr::Url("http://localhost/lobby?email=" + m_userEmail));
	return serverLobbyResponse.text;
}

std::string Client::userReadyInLobby()
{
	auto serverReadySetResponse = cpr::Get(cpr::Url("http://localhost/lobby/ready?email=" + m_userEmail));
	return serverReadySetResponse.text;
}

void Client::setCurrentUser(const std::string email) {
	m_userEmail = email;
}

const std::string Client::getCurrentUser() {
	return m_userEmail;
}

const std::vector<std::string, bool> Client::getLobbyUsers()
{
	auto readyUsersResponse = cpr::Get(cpr::Url("http://localhost/lobby/rplayers"));
	auto unreadyUsersResponse = cpr::Get(cpr::Url("http://localhost/lobby/uplayers"));
	auto readyUsers = crow::json::load(readyUsersResponse.text);
	auto unreadyUsers = crow::json::load(unreadyUsersResponse.text);

	std::vector<std::string, bool> lobbyUsers;
	
	return lobbyUsers;
}

Client* Client::getClient()
{
	if (client == nullptr) {
		client = new Client();
	}
	return client;
}


