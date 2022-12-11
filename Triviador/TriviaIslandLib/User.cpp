#include "User.h"

User::User(std::string email, std::string password):m_email(email),m_password(password)
{

}

User::User(std::string email, std::string password, int numberOfPlayedGames, int numberOfWonGames):User(email,password)
{
	m_numberOfPlayedGames = numberOfPlayedGames;
	m_numberOfWonGames = numberOfWonGames;
	m_winLoseRatio = numberOfWonGames/numberOfPlayedGames;

}

const std::string& User::GetEmail() const{
	return m_email;
}

const std::string& User::GetPassword() const{
	return m_password;
}

const int& User::GetNumberOfPlayedGames() const
{
	return m_numberOfPlayedGames;
}

const int& User::GetNumberOfWonGames() const
{
	return m_numberOfWonGames;
}

const float& User::GetWinLoseRatio() const
{
	return m_winLoseRatio;
}
