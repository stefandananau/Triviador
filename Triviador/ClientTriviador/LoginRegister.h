#pragma once

#include <crow.h>
#include <string>
#include <cpr/cpr.h>

namespace ClientHelper {
	std::string registerUser(const std::string& email, const std::string& password) {
		cpr::Response response = cpr::Get(cpr::Url("http://localhost:80/database?table=User"));
		auto json = crow::json::load(response.text);
		for (const auto& i : json["UserTable"]) {
			if (i["email"] == email) {
				return "email already exists";
			}
		}
		std::string add = std::string("http://localhost/authentication?register&email=" + email + "&password=" + password);
		cpr::Get(cpr::Url(add));
		return "register succesful";
	}

	std::string loginUser(const std::string& email, const std::string& password) {
		cpr::Response response = cpr::Get(cpr::Url("http://localhost:80/database?table=User"));
		auto json = crow::json::load(response.text);
		for (const auto& i : json["UserTable"]) {
			if (i["email"] == email) {
				if (i["password"] == password) {
					return "login succesful";
				}
				return "wrong password";
			}
		}
		return "wrong username";
	}
}