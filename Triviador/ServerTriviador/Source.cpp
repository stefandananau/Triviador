#include <crow/http_server.h>
#include <crow/app.h>
#include <iostream>

#include "../Triviador/DataBase.h"
#include "../Triviador/QuestionNumeric.h"
#include "../Triviador/Parser.h"

int main() {
	DataBase *questionDataBase = DataBase::GetInstance();
	std::vector<QuestionNumeric> numericalQuestionsToAppend = parser::ParserJsonNumeric();
	std::vector<QuestionMultipleChoice> multipleChoiceQuestionsToAppend = parser::ParserJsonMultiple();

	for (const QuestionNumeric& question : numericalQuestionsToAppend) {
		questionDataBase->AddQuestionNumeric(question);
	}
	for (const QuestionMultipleChoice& question : multipleChoiceQuestionsToAppend) {
		questionDataBase->AddQuestionMultipleChoice(question);
	}
	

	crow::SimpleApp crowApp;
	CROW_ROUTE(crowApp, "/database")([] {
		crow::json::wvalue x;
		x["message"] = "test:)";
		return x;
		});
	crowApp.port(80);
	crowApp.multithreaded();
	crowApp.run_async();
	crowApp.debug_print();
}