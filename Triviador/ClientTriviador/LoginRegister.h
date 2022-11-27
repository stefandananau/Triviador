#pragma once
#include <crow/http_server.h>
#include <crow/app.h>
#include <crow/json.h>
#include <string>
#include <cpr/cpr.h>

namespace ClientHelper {
	bool addUser(const std::string& email, const std::string& password) {
		cpr::Response response = cpr::Get(cpr::Url("http://localhost:80/database?table=User"));
		auto json = crow::json::load(response.text);
		for (const auto& i : json["UserTabel: "]) {
			if (i["email"] == email) {
				return false;
			}
		}
		std::string add = std::string("http://localhost/authentication?register&email=" + email + "&password=" + password);
		cpr::Get(cpr::Url(add));
	}
}