#pragma once
#include <string>
#include "User.h"
struct UserRecord
{
	int id;
	std::string m_email;
	std::string m_password;
	int m_numberOfPlayedGames;
	int m_numberOfWonGames;
	float m_winLoseRatio;
	
	UserRecord() {

	}

	UserRecord(const User& user):
		id(-1),
		m_email(user.GetEmail()),
		m_password(user.GetPassword()),
		m_numberOfPlayedGames(user.GetNumberOfPlayedGames()),
		m_numberOfWonGames(user.GetNumberOfWonGames()),
		m_winLoseRatio(user.GetWinLoseRatio())
		
	{

	}
};
