#pragma once

#include <regex>

#include <crow/http_server.h>
#include <crow/app.h>
#include <crow/json.h>
#include <random>
#include <map>

#include "DataBase.h"

#include "QuestionNumericRecord.h"
#include "QuestionMultipleChoiceRecord.h"
#include "UserRecord.h"

#include "QuestionNumeric.h"
#include "QuestionMultipleChoice.h"
#include "User.h"

#include "Parser.h"

enum state {
	waitingForPlayers,
	gameInProgress
};

class Server
{
protected:
	DataBase* m_DataBase;
	state m_GameState;
	std::default_random_engine m_Generator;

	std::map<std::string,bool> m_Lobby;
	crow::SimpleApp m_crowApp;
	
	crow::response DataBaseRoute(const crow::request& req);
	crow::response ReturnRandomQuestionRoute(const crow::request& req, std::default_random_engine& generator);
	crow::response AuthenticationRoute(const crow::request& req);
	crow::response AddUserToLobbyRoute(const crow::request& req);
	crow::response SetUserToReadyInLobbyRoute(const crow::request& req);
	crow::response ReturnUserStats(const crow::request& req);

	crow::json::wvalue CheckGameState();

	void matchStarted();
public:

	Server();
	void PopulateServerDatabase();
	void SetupServer();
	QuestionMultipleChoiceRecord RandomMultipleChoice(std::default_random_engine& generator);
	QuestionNumericRecord RandomNumeric(std::default_random_engine& generator);
	std::default_random_engine GetGenerator() const;
	void wipeUsers();
	void wipeQuestions();
	size_t GetNumberOfQuestionMultipleChoiceRecords() const;
	size_t GetNumberOfQuestionNumericRecords() const;
	size_t GetNumberOfUserRecords() const;
};

