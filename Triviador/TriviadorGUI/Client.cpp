#include "Client.h"

Client* Client::client;

std::string Client::registerUser(const std::string& email, const std::string& password) {
	std::string registerRequest = std::string("http://localhost/authentication?register&email=" + email + "&password=" + password);
	auto r = cpr::Get(cpr::Url(registerRequest));
	return r.text;
}

std::string Client::loginUser(const std::string& email, const std::string& password) {
	std::string loginRequest = std::string("http://localhost/authentication?login&email=" + email + "&password=" + password);
	auto r = cpr::Get(cpr::Url(loginRequest));
	return r.text;
}

Client* Client::getClient()
{
	if (client == nullptr) {
		client = new Client();
	}
	return client;
}


