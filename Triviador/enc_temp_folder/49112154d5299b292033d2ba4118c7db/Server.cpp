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
	User u("admin@admin.com", "admin");
	m_DataBase->AddUser(u);
	return 0;
}

int Server::SetupServer() {

	std::cout << "admin email: admin@admin.com\n"
		"admin password: admin\n\n"
		"Current routes:\n"
		"/database?table=<value>\n"
		"	If value is QuestionMultipleChoice then the response is QuestionMultipleChoice Table\n"
		"	If value is QuestionNumeric then the response is QuestionNumeric Table\n"
		"	If value is User then the response is User Table\n"
		"	If value is All then the response is all tables\n"
		"/database/getQuestion?type=<value>\n"
		"	If value is Multiple then the response is a random question from QuestionMultipleChoice Table with id,question and answers\n"
		"	If value is Numeric then the response is a random question from QuestionNumeric Table with id,question\n"
		"/authentication?(login or register)&email=<value1>&password=<value2>\n"
		"	If login exists then\n"
		"		If email and password is in User Table then the response is Ok else if password is incorrect response is Unauthorized\n"
		"		If email is not in User Table then the response is Not Found"
		"	If register exists then\n"
		"		If email is in User Table then the response is Conflict else new user is added in User Table and response is Ok\n";
		



	std::default_random_engine generator;
	CROW_ROUTE(m_crowApp, "/database")([this](const crow::request& req) {
	auto table = req.url_params.get("table");
	crow::json::wvalue database;
	if (table != nullptr)
	{
		
		if (std::string(table) == "QuestionMultipleChoice")
		{
			crow::json::wvalue x;
			std::vector<QuestionMultipleChoiceRecord> pulledMultipleQuestions = m_DataBase->GetQuestionMultipleChoice();


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
			database = { {"MulipleQuestionTable: ",x} };
			x.clear();
		}
		else if (table == "QuestionNumeric") {
			crow::json::wvalue x;
			std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();

			for (const auto& question : pulledNumericalQuestions) {

				x[question.id - 1] = {
					{"id",question.id},
					{"type", question.m_type},
					{"question", question.m_question},
					{"answer", question.m_answer},

				};
			}
			database = { {"NumericalQuestionTable: ",x} };
			x.clear();
		}
		else if (std::string(table) == "User")
		{
			crow::json::wvalue x;
			std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();

			for (const auto& user : pulledUser) {

				x[user.id - 1] = {
					{"id",user.id},
					{"email", user.m_email},
					{"password", user.m_password},
				};
			}
			database = { {"UserTabel: ",x} };
			x.clear();


		}
		else if (std::string(table) == "All")
		{
			crow::json::wvalue x;

			std::vector<QuestionMultipleChoiceRecord> pulledMultipleQuestions = m_DataBase->GetQuestionMultipleChoice();
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

			std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();

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

			
			std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();

			for (const auto& user : pulledUser) {

				x[user.id - 1] = {
					{"id",user.id},
					{"email", user.m_email},
					{"password", user.m_password},
				};
			}
			database[2] = { {"UserTabel: ",x} };
			x.clear();

		}
		else { 
			return crow::response(404);
 }
		return crow::response(std::move(database));
	}
	return crow::response(405);//Method Not Allowed
	});
	CROW_ROUTE(m_crowApp, "/database/getQuestion")([this, &generator](const crow::request& req) {
	
	

	if (req.url_params.get("type")) {
		std::string type = req.url_params.get("type");
		std::cout << type;

		if (type == "Multiple")

		{std::vector<QuestionMultipleChoiceRecord> pulledMultipleQuestions = m_DataBase->GetQuestionMultipleChoice();
			std::uniform_int_distribution<int> distribution(0, pulledMultipleQuestions.size() - 1);
			int QuestionID = distribution(generator);
			return crow::response(crow::json::wvalue({
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
			));
		}
		if (type == "Numeric")

		{
			std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();
			std::uniform_int_distribution<int> distribution(0, pulledNumericalQuestions.size() - 1);
			int QuestionID = distribution(generator);
			return crow::response(std::move(crow::json::wvalue({
				{"Id", pulledNumericalQuestions[QuestionID].id},
				{"Question", pulledNumericalQuestions[QuestionID].m_question},

				}
			)));
		}
	}
	return crow::response(405);
		});

	CROW_ROUTE(m_crowApp, "/authentication")([this](const crow::request& req) {

		std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();
	if (req.url_params.get("login"))
	{
		auto email = req.url_params.get("email");
		if (email == nullptr)
		{
			return crow::response(405);//Method Not Allowed
		}
		auto password = req.url_params.get("password");
		if (password == nullptr)
		{
			return crow::response(405);//Method Not Allowed
		}
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
	else if (req.url_params.get("register"))
	{
		auto email = req.url_params.get("email");
		if (email == nullptr)
		{
			return crow::response(405);//Method Not Allowed
		}
		auto password = req.url_params.get("password");
		if (password == nullptr)
		{
			return crow::response(405);//Method Not Allowed
		}

		auto user = std::find_if(pulledUser.begin(), pulledUser.end(), [email](const UserRecord& u) {
			return u.m_email == email;
			});
		if (!(user == pulledUser.end()))
		{
			return crow::response(409);//Conflict
		}
		else
		{
			m_DataBase->AddUser(User(email, password));
			return crow::response(200);//Ok

		}

	}
	return crow::response(405);//Method Not Allowed
		
	});
	m_crowApp.port(80);
	m_crowApp.multithreaded();
	m_crowApp.run();
	m_crowApp.debug_print();

	return 0;
}