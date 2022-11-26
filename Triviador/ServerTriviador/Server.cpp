#include "Server.h"

Server::Server() {
	m_DataBase = DataBase::GetInstance();
	m_DataBase->Sync();

	m_numericalQuestionsToAppend = parser::ParserJsonNumeric();
	m_multipleChoiceQuestionsToAppend = parser::ParserJsonMultiple();
	PopulateServerDatabase();

	SetupServer();


}

int Server::PopulateServerDatabase() {

	for (const QuestionNumeric& question : m_numericalQuestionsToAppend) {
		m_DataBase->AddQuestionNumeric(QuestionNumericRecord(question));
	}
	for (const QuestionMultipleChoice& question : m_multipleChoiceQuestionsToAppend) {
		m_DataBase->AddQuestionMultipleChoice(QuestionMultipleChoiceRecord(question));
	}
	for (const User& user : m_UsersToAppend) {
		m_DataBase->AddUser(UserRecord(user));
	}
	User u("abc@gmail.com", "123");
	m_DataBase->AddUser(u);
	return 0;
}

int Server::SetupServer() {
	std::vector<QuestionMultipleChoiceRecord> pulledMultipleQuestions = m_DataBase->GetQuestionMultipleChoice();
	std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();
	std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();
	std::default_random_engine generator;
	CROW_ROUTE(m_crowApp, "/database")([&pulledMultipleQuestions, &pulledNumericalQuestions, &pulledUser] {
		crow::json::wvalue database;
		crow::json::wvalue x;


		for (const auto& question : pulledMultipleQuestions) {

			x[question.id - 1] = {
				{"id",question.id},
				{"type", question.m_type},
				{"question", question.m_question},
				{"correct_answer", question.m_correctAnswer},
				{"wrong_answer1", question.m_wrongAnswer1},
				{"wrong_answer2", question.m_wrongAnswer2},
				{"wrong_answer3", question.m_wrongAnswer3}
			};
		}
		database[0] = { {"MulipleQuestionTable: ",x} };
		x.clear();

		for (const auto& question : pulledNumericalQuestions) {

			x[question.id - 1] = {
				{"id",question.id},
				{"type", question.m_type},
				{"question", question.m_question},
				{"answer", question.m_answer},

			};
		}
		database[1] = { {"NumericalQuestionTable: ",x} };
		x.clear();

		for (const auto& user : pulledUser) {

			x[user.id - 1] = {
				{"id",user.id},
				{"email", user.m_email},
				{"password", user.m_password},
			};
		}
		database[2] = { {"UserTabel: ",x} };
		x.clear();

		return database;

		});
	CROW_ROUTE(m_crowApp, "/database/getQuestion")([&pulledMultipleQuestions, &pulledNumericalQuestions, &generator](const crow::request& req) {
		std::string type = req.url_params.get("type");
		std::cout << type;

		if (type == "Multiple")

		{
			std::uniform_int_distribution<int> distribution(0, pulledMultipleQuestions.size() - 1);
			int QuestionID = distribution(generator);
			return crow::json::wvalue({
				{"Id", pulledMultipleQuestions[QuestionID].id},
				{"Question", pulledMultipleQuestions[QuestionID].m_question},
				{"Responses",
				crow::json::wvalue::list(
					{pulledMultipleQuestions[QuestionID].m_correctAnswer,
				pulledMultipleQuestions[QuestionID].m_wrongAnswer1,
				pulledMultipleQuestions[QuestionID].m_wrongAnswer2,
				pulledMultipleQuestions[QuestionID].m_wrongAnswer3
				})
					}
				}
			);
		}
		if (type == "Numeric")

		{
			std::uniform_int_distribution<int> distribution(0, pulledNumericalQuestions.size() - 1);
			int QuestionID = distribution(generator);
			return crow::json::wvalue({
				{"Id", pulledNumericalQuestions[QuestionID].id},
				{"Question", pulledNumericalQuestions[QuestionID].m_question},

				}
			);
		}

		});
	CROW_ROUTE(m_crowApp, "/authentication")([&pulledUser](const crow::request& req) {
		if (req.url_params.get("login"))
		{
			std::string email = req.url_params.get("email");
			std::string password = req.url_params.get("password");
			auto user = std::find_if(pulledUser.begin(), pulledUser.end(), [email](const UserRecord& u) {
				return u.m_email == email;
				});
			if (user != pulledUser.end())
			{
				if (user->m_password == password)
				{
					return crow::response(202);//Accepted
				}
				else
					return crow::response(401);//Unauthorized
			}
			else {
				return crow::response(404);//Not Found
			}
		}
		return crow::response(405);
		}

	);
	m_crowApp.port(80);
	m_crowApp.multithreaded();
	m_crowApp.run();
	m_crowApp.debug_print();

	return 0;
}