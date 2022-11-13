#pragma once
#include "UserRecord.h"
#include "DataBase.h"

namespace LoginRegisterService {
	std::string Register(const UserRecord& newUser){
		if (newUser.m_password.length() < 8)
			"password too weak";

		for (const auto& user : DataBase::GetInstance()->GetUsers()) {
			if (newUser.m_email == user.m_email)
				return "email already in use";

			if (newUser.id == user.id) 
				return "user already exists";
		}
		DataBase::GetInstance()->AddUser(newUser);
		return "Register Complete";
	}

	std::string Login(const UserRecord& existingUser) {
		for (const auto& user : DataBase::GetInstance()->GetUsers()) {
			if (existingUser.m_email == user.m_email) {
				if (existingUser.m_password == user.m_password) 
					return "Login Complete";
				else 
					return "wrong password";	
			}
		}
		return "wrong username";
	}
}