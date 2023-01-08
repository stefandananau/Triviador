#include "Player.h"



Player::Player(std::string userEmail) {
	m_UserEmail = userEmail;
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

void Player::RemovePowerUp(std::string powerUp)
{
	m_AvailablePowerUp.erase(std::remove(m_AvailablePowerUp.begin(), m_AvailablePowerUp.end(), powerUp), m_AvailablePowerUp.end());
}

void Player::SetAnswer(std::string answer) {
	m_Answer = answer;
}

const std::string& Player::GetAnswer() const
{
	return m_Answer;
}

int Player::NumberOfPowerUp()
{
	return m_AvailablePowerUp.size();
}

Player::~Player() {

}
