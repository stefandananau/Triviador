#pragma once

#include <regex>

#include <crow/http_server.h>
#include <crow/app.h>
#include <crow/json.h>
#include <random>
#include <map>
#include <utility>

#include "DataBase.h"

#include "QuestionNumericRecord.h"
#include "QuestionMultipleChoiceRecord.h"
#include "UserRecord.h"

#include "QuestionNumeric.h"
#include "QuestionMultipleChoice.h"
#include "User.h"

#include "Parser.h"
#include "Player.h"
#include <Board.h>
//#include "Game.h"


class Server
{
public:
	enum state {
		waitingForPlayers,
		gameInProgress,
		waitingForQuestionResponse,
		showAnswers
	};
	enum questionType {
		NUMERIC,
		MULTIPLE_ANSWER
	};
	enum matchState {
		NOT_STARTED,
		FIRST_QUESTION_PHASE,
		MAP_BASE_PHASE,
		MAP_DIVISION_PHASE,
		DUEL_PHASE
	};

protected:
	//game logic
	
	Board m_Board;
	struct attack {
		std::string attaker;
		size_t width;
		size_t height;
	} m_attack;
	//state m_GameState;
	questionType m_CurrentQuestionType;
	std::map<std::string, Player> m_PlayersInGame;
	std::vector<std::string> m_playersInGameOrder;

	QuestionMultipleChoiceRecord m_CurrentMultipleChoiceQuestion;
	QuestionNumericRecord m_CurrentNumericQuestion;

	void drawBoard();
	//

	DataBase* m_DataBase;
	
	state m_GameState;
	matchState m_MatchState;

	std::default_random_engine m_Generator;
	std::map<std::string,bool> m_Lobby;
	std::vector<std::pair<std::string, int>> m_firstQuestionAnswerOrderAndWinner;
	
	uint16_t m_roundCounter;

	//Game m_Game;
	
	crow::SimpleApp m_crowApp;
	
	crow::response DataBaseRoute(const crow::request& req);
	crow::response ReturnRandomQuestionRoute(const crow::request& req, std::default_random_engine& generator);
	void RandomQuestion(std::string type,std::default_random_engine& generator);
	crow::response AuthenticationRoute(const crow::request& req);
	crow::response AddUserToLobbyRoute(const crow::request& req);
	crow::response RemoveUserFromLobbyRoute(const crow::request& req);
	crow::response SetUserToReadyInLobbyRoute(const crow::request& req);
	crow::response SetUserToUnreadyInLobbyRoute(const crow::request& req);
	crow::response AddQuestionAnswerToUser(const crow::request& req);
	crow::response ReturnUserStats(const crow::request& req);
	crow::response NumberOfPlayersInLobby();
	crow::response RemovePowerUp(const crow::request& req);
	crow::response AttackIsland(const crow::request& req);
	crow::response OwnerIsland(const crow::request& req);
	crow::response IslandMap();
	crow::response GetCurrentPlayer();
	crow::response PopCurrentPlayer();
	crow::json::wvalue ReturnReadyUsersInLobby();
	crow::json::wvalue ReturnUnreadyUsersInLobby();
	crow::json::wvalue ValidateAnswer();
	crow::json::wvalue CheckGameState();
	crow::json::wvalue CurrentQuestionToJson();
	crow::json::wvalue GetCurrentMatchPhase();

	


	bool IsBoardFull();

	bool AllAnswersAreGiven();
	void matchStarted();

public:

	Server();
	void PopulateServerDatabase();
	void SetupServer();
	QuestionMultipleChoiceRecord RandomMultipleChoice(std::default_random_engine& generator);
	QuestionNumericRecord RandomNumeric(std::default_random_engine& generator);
	std::default_random_engine& GetGenerator();
	
	void wipeUsers();
	void wipeQuestions();
	
	size_t GetNumberOfQuestionMultipleChoiceRecords() const;
	size_t GetNumberOfQuestionNumericRecords() const;
	size_t GetNumberOfUserRecords() const;

	size_t GetNumberOfPlayersInLobby() const;
	std::map<std::string, bool>  GetPlayersInLobby();
	void SetState(state stateToSet);
};

