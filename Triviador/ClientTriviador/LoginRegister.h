#pragma once

#include <crow.h>
#include <string>
#include <cpr/cpr.h>

namespace ClientHelper {
	std::string registerUser(const std::string& email, const std::string& password) {
		std::string registerRequest = std::string("http://localhost/authentication?register&email=" + email + "&password=" + password);
		auto r = cpr::Get(cpr::Url(registerRequest));
		return r.text;
	}

	std::string loginUser(const std::string& email, const std::string& password) {
		std::string loginRequest = std::string("http://localhost/authentication?login&email=" + email + "&password=" + password);
		auto r = cpr::Get(cpr::Url(loginRequest));
		return r.text;
	}
}