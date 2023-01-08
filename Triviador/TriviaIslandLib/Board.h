#pragma once
#include <vector>
#include "Island.h"
class Board
{
public:
	Board();
	Board(uint16_t numberOfPlayers);

	const std::vector<std::vector<Island>>& GetBoard() const;
	const size_t GetHeight() const;
	const size_t GetWidth() const;
	
	void SetAttacker(const size_t& height, const size_t& width, const Player& attacker);
	void ChangeOwner(const size_t& height, const size_t& width);

private:
	size_t m_height;
	size_t m_width;
	std::vector<std::vector<Island>> m_Board;
};

