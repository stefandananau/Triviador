#pragma once
#include <vector>
#include "Island.h"
class Board
{
public:
	Board(uint16_t numberOfPlayers);

	const std::vector<std::vector<Island>>& GetBoard() const;

	
private:
	size_t m_height;
	size_t m_width;
	std::vector<std::vector<Island>> m_Board;
};

