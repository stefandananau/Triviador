#pragma once
#include <string>
class User
{
public:
	User(std::string email, std::string password);
	User(std::string email, std::string password, int numberOfPlayedGames, int numberOfWonGames);
	const std::string& GetEmail() const;
	const std::string& GetPassword() const;
	const int& GetNumberOfPlayedGames() const;
	const int& GetNumberOfWonGames() const;
	const float& GetWinLoseRatio() const;

private:
	std::string m_email;
	std::string m_password;
	int m_numberOfPlayedGames;
	int m_numberOfWonGames;
	float m_winLoseRatio;
};

