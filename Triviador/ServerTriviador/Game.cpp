#include "Game.h"

Game::Game(Server s) {
	size_t numberOfClients = s.GetNumberOfPlayersInLobby();

	switch (numberOfClients)
	{
	case 2:
		m_BoardSize.first = 3;
		m_BoardSize.second = 3;
		break;

	case 3:
		m_BoardSize.first = 5;
		m_BoardSize.second = 3;
		break;

	case 4:
		m_BoardSize.first = 6;
		m_BoardSize.second = 4;
		break;

	default:
		break;
	}

	std::map<std::string, bool> playersInLobby = s.GetPlayersInLobby();

	for (auto player : playersInLobby) {
		m_PlayersAndPoints.push_back(std::make_pair(player.first, 0));
	}

	std::vector<uint16_t> t_boardRows;
	for (uint16_t x = 0; x < m_BoardSize.first;) {
		for (uint16_t y = 0; y < m_BoardSize.second;) {
			t_boardRows.push_back(0);
		}
		m_Board.push_back(t_boardRows);
		t_boardRows.clear();
	}

	drawBoard();

}

void Game::drawBoard() {
	for (size_t y = 0; y < m_Board[0].size(); y++)
		std::cout << y << " ";
	std::cout << std::endl;

	for (size_t x = 0; x < m_Board.size(); x++) {
		std::cout << x <<": ";
		for (size_t y = 0; y < m_Board[x].size(); y++) {
			std::cout<< m_Board[x][y] << " ";
		}
		std::cout << std::endl;
	}
}