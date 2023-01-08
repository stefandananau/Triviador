#include "Board.h"

Board::Board()
{
}

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

	m_Board.resize(m_width, std::vector<Island>(m_height,Island()));
}

const std::vector<std::vector<Island>>& Board::GetBoard() const
{
	return m_Board;
}

const size_t Board::GetHeight() const
{
	return m_height;
}

const size_t Board::GetWidth() const
{
	return m_width;
}

void Board::SetAttacker(const size_t& height,const size_t& width, const Player& attacker)
{
	m_Board[height][width].SetAttacker(attacker);
}

void Board::ChangeOwner(const size_t& height, const size_t& width)
{
	m_Board[height][width].SetOwner();
}
