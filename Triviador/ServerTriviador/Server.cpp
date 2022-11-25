#include "Server.h"

Server::Server() {
	m_DataBase = DataBase::GetInstance();
	m_DataBase->Sync();
	m_numericalQuestionsToAppend = parser::ParserJsonNumeric();
	m_multipleChoiceQuestionsToAppend = parser::ParserJsonMultiple();
	PopulateServerDatabase();
	m_DataBase->Sync();
	SetupServer();
	m_DataBase->Sync();
	
}

int Server::PopulateServerDatabase() {
	for (const QuestionNumeric& question : m_numericalQuestionsToAppend) {
		m_DataBase->AddQuestionNumeric(QuestionNumericRecord(question));
	}
	for (const QuestionMultipleChoice& question : m_multipleChoiceQuestionsToAppend) {
		m_DataBase->AddQuestionMultipleChoice(QuestionMultipleChoiceRecord(question));
	}
	for (const User& user : m_Users) {
		m_DataBase->AddUser(UserRecord(user));
	}
	return 0;
}

int Server::SetupServer() {
	std::vector<QuestionMultipleChoiceRecord> pulledMultipleQuestions = m_DataBase->GetQuestionMultipleChoice();
	std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();

	CROW_ROUTE(m_crowApp, "/database")([pulledMultipleQuestions, pulledNumericalQuestions] {
		crow::json::wvalue x;

		for (const auto& question : pulledMultipleQuestions) {
			
			x[question.id] = {
				{"type", question.m_type},
				{"question", question.m_question}, 
				{"correct_answer", question.m_correctAnswer}, 
				{"wrong_answer1", question.m_wrongAnswer1},
				{"wrong_answer2", question.m_wrongAnswer2},
				{"wrong_answer3", question.m_wrongAnswer3}
			};
		}
		
		return x;
		
		});
	m_crowApp.port(80);
	m_crowApp.multithreaded();
	m_crowApp.run_async();
	m_crowApp.debug_print();

	return 0;
}