#pragma once


#include <crow/http_server.h>
#include <crow/app.h>
#include <crow/json.h>
#include <random>

#include "DataBase.h"

#include "QuestionNumericRecord.h"
#include "QuestionMultipleChoiceRecord.h"
#include "UserRecord.h"

#include "QuestionNumeric.h"
#include "QuestionMultipleChoice.h"
#include "User.h"

#include "Parser.h"
class Server
{
protected:
	DataBase* m_DataBase;
	crow::SimpleApp m_crowApp;
	
	crow::response DataBaseRoute(const crow::request& req);
	crow::response ReturnRandomQuestionRoute(const crow::request& req, std::default_random_engine& generator);
	crow::response AuthenticationRoute(const crow::request& req);

	

public:
	Server();
	void PopulateServerDatabase();
	void SetupServer();
	void wipeUsers();
	void wipeQuestions();
	size_t GetNumberOfQuestionMultipleChoiceRecords() const;
	size_t GetNumberOfQuestionNumericRecords() const;
	size_t GetNumberOfUserRecords() const;
};

