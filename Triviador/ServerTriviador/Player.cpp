#include "Player.h"

Player::Player() {

}

Player::Player(std::string userEmail) {
	m_UserEmail = userEmail;
	m_Points = 0;
}

void Player::AddPoints(uint16_t pointsToAdd) {
	m_Points += pointsToAdd;
}

void Player::SetAnswer(std::string answer) {
	m_Answer = answer;
}

Player::~Player() {

}