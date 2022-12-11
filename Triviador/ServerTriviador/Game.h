#pragma once
#include <utility>
#include <cstdint>
#include <vector>
#include <map>
#include <iostream>

#include "QuestionMultipleChoiceRecord.h"
#include "QuestionNumericRecord.h"
#include "Server.h"

class Game {
private:
	std::pair<uint16_t, uint16_t> m_BoardSize;
	std::vector<std::vector<uint16_t>> m_Board;

	QuestionMultipleChoiceRecord m_CurrentMultipleChoiceQuestion;
	QuestionNumericRecord m_CurrentNumericQuestion;
	
	std::vector<std::pair<std::string, uint16_t>> m_PlayersAndPoints;

	void drawBoard();
public:
	Game(uint16_t numberOfClientsInLobby, std::map<std::string, bool> playersInLobby, Server s);
	~Game();
};