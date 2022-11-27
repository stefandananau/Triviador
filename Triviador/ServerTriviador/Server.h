#pragma once


#include <crow/http_server.h>
#include <crow/app.h>
#include <crow/json.h>
#include <random>

#include "DataBase.h"

#include "QuestionNumeric.h"
#include "QuestionMultipleChoice.h"
#include "User.h"

#include "QuestionNumericRecord.h";
#include "QuestionMultipleChoiceRecord.h";
#include "UserRecord.h"

#include "Parser.h"
class Server
{
private:
	DataBase* m_DataBase;
	crow::SimpleApp m_crowApp;

	std::vector<QuestionNumeric> m_numericalQuestionsToAppend;
	std::vector<QuestionMultipleChoice> m_multipleChoiceQuestionsToAppend;
	std::vector<User> m_UsersToAppend;
	void PopulateServerDatabase();
	void SetupServer();

public:
	Server();
	void wipeUsers();
	void wipeQuestions();
	size_t getNumberOfQuestionMultipleChoiceRecords();
	size_t getNumberOfQuestionNumericRecords();
	size_t getNumberOfUserRecords();
};

