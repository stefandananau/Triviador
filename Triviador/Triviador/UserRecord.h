#pragma once
#include <string>
#include "User.h"
struct UserRecord
{
	int id;
	std::string m_email;
	std::string m_password;
	
	UserRecord() {

	}

	UserRecord(const User& user):
		id(-1),
		m_email(user.GetEmail()),
		m_password(user.GetPassword())
	{

	}
};
