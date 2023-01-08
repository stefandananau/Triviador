#pragma once
#include "Player.h"
class Island
{
public:
	Island(Player owner = Player(), uint16_t islandScore = 100);

	void SetOwner(const Player& owner);
	void SetOwner();
	const Player& GetOwner() const;


	void SetIslandScore(const uint16_t & score);
	const uint16_t& GetIslandScore() const;

	void SetAttacker(const Player& attacker);
	const Player& GetAttacker() const;

	void AttackerWon();
	
	void IncreaseScore();
	void DecreaseScore();



private:
	Player m_Owner;
	uint16_t m_IslandScore;
	Player m_Attacker;
};

