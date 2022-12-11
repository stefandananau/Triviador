#pragma once

#include <string>
#include <cstdint>

class Player {
private:
	std::string m_UserEmail;
	std::string m_Answer;

	uint16_t m_Points;

public:
	Player();
	Player(std::string userEmail);
	void SetAnswer(std::string answer);
	void AddPoints(uint16_t pointsToAdd);
	~Player();
};