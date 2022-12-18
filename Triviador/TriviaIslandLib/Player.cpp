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

void Player::SetAnswer(std::string answer) {
	m_Answer = answer;
}

const std::string& Player::GetAnswer() const
{
	return m_Answer;
}

Player::~Player() {

}
