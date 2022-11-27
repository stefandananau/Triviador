#include "User.h"

User::User(std::string email, std::string password)
{
	m_email = email;
	m_password = password;
}

const std::string& User::GetEmail() const{
	return m_email;
}

const std::string& User::GetPassword() const{
	return m_password;
}
