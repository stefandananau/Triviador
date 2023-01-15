#include "Player.h"



Player::Player(std::string userEmail,std::string color) {
	m_UserEmail = userEmail;
	m_Color = color;
	m_Points = 0;
}

void Player::AddPoints(uint16_t pointsToAdd) {
	m_Points += pointsToAdd;
}

const uint16_t& Player::GetPoints() const
{
	return m_Points;
}

const std::string& Player::GetUser() const
{
	return m_UserEmail;
}

void Player::SetColor(std::string color)
{
	m_Color = color;
}

const std::string& Player::GetColor() const
{
	return m_Color;
}

void Player::RemovePowerUp(std::string powerUp)
{
	m_AvailablePowerUp.erase(std::remove(m_AvailablePowerUp.begin(), m_AvailablePowerUp.end(), powerUp), m_AvailablePowerUp.end());
}

void Player::SetAnswer(std::string answer,uint64_t time) {
	m_Answer = make_pair(answer,time);
}

const std::string& Player::GetAnswer() const
{
	return m_Answer.first;
}

const uint64_t& Player::GetTime() const
{
	return m_Answer.second;
}

int Player::NumberOfPowerUp()
{
	return m_AvailablePowerUp.size();
}

Player::~Player() {

}
