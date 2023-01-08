#include "Island.h"

Island::Island(Player owner, uint16_t islandScore):m_Owner(owner),m_IslandScore(islandScore)
{

}

void Island::SetOwner(const Player& owner)
{
	m_Owner = owner;
}

void Island::SetOwner()
{
	m_Owner = std::move(m_Attacker);
}

const Player& Island::GetOwner() const
{
	return m_Owner;
}

void Island::SetIslandScore(const uint16_t& score)
{
	m_IslandScore = score;
}

const uint16_t& Island::GetIslandScore() const
{
	return m_IslandScore;
}

void Island::SetAttacker(const Player& attacker)
{
	m_Attacker = attacker;
}

const Player& Island::GetAttacker() const
{
	return m_Attacker;
}

void Island::AttackerWon()
{
	m_Owner = std::move(m_Attacker);
}

void Island::IncreaseScore()
{
	m_IslandScore += 100;
}

void Island::DecreaseScore()
{
	m_IslandScore -= 100;
}
