#pragma once

#include <string>
#include <cstdint>
#include <vector>

class Player {


public:

	Player(std::string userEmail="unowned",std::string color="");

	void SetAnswer(std::string answer,uint64_t time=0);
	const std::string& GetAnswer() const;
	const uint64_t& GetTime() const;

	void AddPoints(uint16_t pointsToAdd);
	const uint16_t& GetPoints()const;

	const std::string& GetUser() const;

	void SetColor(std::string color);
	const std::string& GetColor() const;

	void RemovePowerUp(std::string powerUp);
	int NumberOfPowerUp();

	~Player();

private:
	std::vector<std::string> m_AvailablePowerUp = {"50/50","PickAnswer","SuggestAnswer"};
	std::string m_UserEmail;
	std::pair<std::string,uint64_t> m_Answer;
	std::string m_Color;
	uint16_t m_Points;
};