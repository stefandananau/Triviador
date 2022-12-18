#include "Board.h"

Board::Board(uint16_t numberOfPlayers)
{
	switch (numberOfPlayers)
	{
	case 2:
		m_width = 3;
		m_height = 3;
		break;
	case 3:
		m_width = 5;
		m_height = 3;
		break;
	case 4:
		m_width = 6;
		m_height = 4;
		break;
	default:
		break;
	} 
	m_Board.resize(m_width);
	for (auto column : m_Board)
	{
		column.resize(m_height,Island());
	}
}

const std::vector<std::vector<Island>>& Board::GetBoard() const
{
	return m_Board;
}
