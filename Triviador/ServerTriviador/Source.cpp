#include <crow/http_server.h>
#include <crow/app.h>
#include <iostream>

#include "../Triviador/DataBase.h"
#include "../Triviador/QuestionNumeric.h"
#include "../Triviador/Parser.h"

int main() {
	DataBase *questionDataBase = DataBase::GetInstance();
	//std::vector<QuestionNumeric> numericalQuestionsToAppend = parser::ParserJsonNumeric();

	//for (const QuestionNumeric& question : numericalQuestionsToAppend) {
	//	questionDataBase->AddQuestionNumeric(question);
	//}
	//questionDataBase->AddQuestionNumeric();

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