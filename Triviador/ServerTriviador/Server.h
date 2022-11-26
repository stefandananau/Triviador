#pragma once

#include <iostream>
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
	int PopulateServerDatabase();
	int SetupServer();
public:
	Server();
};

