#pragma once
#include <string>
class User
{
public:
	User(std::string email, std::string password);
	const std::string& GetEmail() const;
	const std::string& GetPassword() const;

private:
	std::string m_email;
	std::string m_password;
};

