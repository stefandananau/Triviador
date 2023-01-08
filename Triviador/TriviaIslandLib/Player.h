#pragma once

#include <string>
#include <cstdint>
#include <vector>

class Player {


public:

	Player(std::string userEmail="unowned");

	void SetAnswer(std::string answer);
	const std::string& GetAnswer() const;

	void AddPoints(uint16_t pointsToAdd);
	const uint16_t& GetPoints()const;

	const std::string& GetUser() const;

	void RemovePowerUp(std::string powerUp);
	int NumberOfPowerUp();

	~Player();

private:
	std::vector<std::string> m_AvailablePowerUp = {"50/50","PickAnswer","SuggestAnswer"};
	std::string m_UserEmail;
	std::string m_Answer;
	uint16_t m_Points;
};