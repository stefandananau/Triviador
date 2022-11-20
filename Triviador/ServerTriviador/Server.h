#pragma once

#include <iostream>
#include <crow/http_server.h>
#include <crow/app.h>
#include <crow/json.h>

#include "DataBase.h"

#include "QuestionNumeric.h"
#include "QuestionMultipleChoice.h"

#include "QuestionNumericRecord.h";
#include "QuestionMultipleChoiceRecord.h";

#include "Parser.h"
class Server
{
private:
	DataBase* m_questionDataBase;
	crow::SimpleApp m_crowApp;

	std::vector<QuestionNumeric> m_numericalQuestionsToAppend;
	std::vector<QuestionMultipleChoice> m_multipleChoiceQuestionsToAppend;
	int PopulateServerDatabase();
	int SetupServer();
public:
	Server();
};

