#include "Server.h"
#include <regex>
Server::Server() {
	m_DataBase = DataBase::GetInstance();
	m_DataBase->Sync();

	
	PopulateServerDatabase();

	//wipeUsers();
	//wipeQuestions();

	//SetupServer();


}

crow::json::wvalue Server::CheckGameState() {
	crow::json::wvalue outJson;

	switch (m_gameState) {
	case state::waitingForPlayers:
		outJson = { { "state", "waiting_for_players" } };
		break;
	case state::gameInProgress:
		outJson = { {"state", "game_in_progress"} };
		break;
	default:
		break;
	}
	return outJson;
}

crow::response Server::DataBaseRoute(const crow::request& req)
{
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
			database = { {"MulipleQuestionTable",x} };
			x.clear();
		}
		else if (std::string(table) == "QuestionNumeric") {
			crow::json::wvalue x;
			std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();

			for (const auto& question : pulledNumericalQuestions) {

				x[question.id - 1] = {
					{"id",question.id},
					{"type", question.m_type},
					{"question", question.m_question},
					{"answer", question.m_correctAnswer},

				};
			}
			database = { {"NumericalQuestionTable",x} };
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
			database = { {"UserTable",x} };
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
			database[0] = { {"MulipleQuestionTable",x} };
			x.clear();

			std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();

			for (const auto& question : pulledNumericalQuestions) {

				x[question.id - 1] = {
					{"id",question.id},
					{"type", question.m_type},
					{"question", question.m_question},
					{"answer", question.m_correctAnswer},

				};
			}
			database[1] = { {"NumericalQuestionTable",x} };
			x.clear();


			std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();

			for (const auto& user : pulledUser) {

				x[user.id - 1] = {
					{"id",user.id},
					{"email", user.m_email},
					{"password", user.m_password},
				};
			}
			database[2] = { {"UserTabe",x} };
			x.clear();

		}
		else {
			return crow::response(404);//Not Found
		}
		return crow::response(std::move(database));
	}
	return crow::response(405);//Method Not Allowed

}

crow::response Server::ReturnRandomQuestionRoute(const crow::request& req, std::default_random_engine& generator)
{
	if (req.url_params.get("type")) {
		std::string type = req.url_params.get("type");
		std::cout << type;

		if (type == "Multiple")

		{
			std::vector<QuestionMultipleChoiceRecord> pulledMultipleQuestions = m_DataBase->GetQuestionMultipleChoice();
			std::uniform_int_distribution<int> distribution(0, pulledMultipleQuestions.size() - 1);
			int QuestionID = distribution(generator);
			return crow::response(crow::json::wvalue({
				{"Id", pulledMultipleQuestions[QuestionID].id},
				{"Question", pulledMultipleQuestions[QuestionID].m_question},
				{"Responses",
				crow::json::wvalue::list(
					{
				pulledMultipleQuestions[QuestionID].m_correctAnswer,
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
}

crow::response Server::AuthenticationRoute(const crow::request& req)
{
	std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();
	if (req.url_params.get("login"))
	{
		auto email = req.url_params.get("email");
		if (email == nullptr)
		{
			return crow::response(405, "email field is null");//Method Not Allowed
		}
		auto password = req.url_params.get("password");
		if (password == nullptr)
		{
			return crow::response(405, "password field is null");//Method Not Allowed
		}
		auto user = std::find_if(pulledUser.begin(), pulledUser.end(), [email](const UserRecord& u) {
			return u.m_email == email;
			});
		if (user != pulledUser.end())
		{
			if (user->m_password == password)
			{
				return crow::response(202, "login succesful");//Accepted
			}
			else
				return crow::response(401, "wrong password");//Unauthorized
		}
		else {
			return crow::response(404, "wrong email");//Not Found
		}
	}
	else if (req.url_params.get("register"))
	{
		auto email = req.url_params.get("email");
		if (email == nullptr)
		{
			return crow::response(405, "email field is null");//Method Not Allowed
		}
		if (!std::regex_match(email, std::regex("^[A-Za-z0-9]+@[a-z]+\.[a-z]+(\.[a-z]+)?$"))) {
			return crow::response(417, "email expectations not satisfied");
		}
		auto password = req.url_params.get("password");
		if (password == nullptr)
		{
			return crow::response(405, "password field is null");//Method Not Allowed
		}
		//password regex (need to add)

		auto user = std::find_if(pulledUser.begin(), pulledUser.end(), [email](const UserRecord& u) {
			return u.m_email == email;
			});
		if (!(user == pulledUser.end()))
		{
			return crow::response(409, "email already exists");//Conflict
		}
		else
		{
			m_DataBase->AddUser(User(email, password));
			return crow::response(200, "register succesful");//Ok

		}

	}
	return crow::response(405);//Method Not Allowed
		
}

crow::response Server::AddUserToLobyRoute(const crow::request& req) {
	auto userName = req.url_params.get("email");

	std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();
	auto email = req.url_params.get("email");

	auto user = std::find_if(pulledUser.begin(), pulledUser.end(), [email](const UserRecord& u) {
		return u.m_email == email;
		});
	if (user == pulledUser.end())
	{
		return crow::response(404);//Not found
	}
	else {
		m_lobby[userName] = false;
		m_gameState = state::waitingForPlayers;
		return crow::response(200);
	}
}

crow::response Server::SetUserToReadyInLobbyRoute(const crow::request& req) {
	auto email = req.url_params.get("email");
	size_t numberOfReadyUsers = 0;
	if (!m_lobby.contains(email)) {
		return crow::response(404);//not found
	}
	else {
		m_lobby[email] = true;
		for (const auto &elem : m_lobby) {
			if (elem.second == true) {
				numberOfReadyUsers++;
			}
		}
		if (numberOfReadyUsers == 4) {
			this->m_gameState = state::gameInProgress;
			std::cout << "Game started!\n";
		}

		return crow::response(200);//ok
	}

}


void Server::PopulateServerDatabase() {
		std::vector<QuestionNumeric> numericalQuestionsToAppend = parser::ParserJsonNumeric();
		std::vector<QuestionMultipleChoice> multipleChoiceQuestionsToAppend = parser::ParserJsonMultiple();
		std::vector<User> usersToAppend;

		if (this->GetNumberOfQuestionNumericRecords() == 0) {
			for (const QuestionNumeric& question : numericalQuestionsToAppend) {
				m_DataBase->AddQuestionNumeric(QuestionNumericRecord(question));
			}
		}
		if (this->GetNumberOfQuestionMultipleChoiceRecords() == 0) {
			for (const QuestionMultipleChoice& question : multipleChoiceQuestionsToAppend) {
				m_DataBase->AddQuestionMultipleChoice(QuestionMultipleChoiceRecord(question));
			}
		}
		if (this->GetNumberOfUserRecords() == 0) {
			for (const User& user : usersToAppend) {
				m_DataBase->AddUser(UserRecord(user));
			}
		}
		User u("admin@admin.com", "admin");
		m_DataBase->AddUser(u);

}
void Server::wipeUsers()
{
	m_DataBase->WipeUsers();
}

void Server::wipeQuestions()
{
	m_DataBase->WipeQuestions();
}




void Server::SetupServer() {

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
		"		If email is not in User Table then the response is Not Found\n"
		"	If register exists then\n"
		"		If email is in User Table then the response is Conflict else new user is added in User Table and response is Ok\n\n\n";

	std::default_random_engine generator;
	CROW_ROUTE(m_crowApp, "/database")([this](const crow::request& req) {
		return DataBaseRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/database/getQuestion")([this, &generator](const crow::request& req) {
		return ReturnRandomQuestionRoute(req, generator);

		});

	CROW_ROUTE(m_crowApp, "/authentication")([this](const crow::request& req) {
		return AuthenticationRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/lobby")([this](const crow::request& req) {
		return AddUserToLobyRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/lobby/ready")([this](const crow::request& req) {
		return SetUserToReadyInLobbyRoute(req);
		});
	
	CROW_ROUTE(m_crowApp, "/lobby/gameState")([this]() {
		return CheckGameState();
		});

	m_crowApp.port(80);
	m_crowApp.multithreaded();
	m_crowApp.run_async();
	m_crowApp.debug_print();


}

size_t Server::GetNumberOfUserRecords() const
{
	std::vector<UserRecord> userRecords = m_DataBase->GetUsers();
	return userRecords.size();
}

size_t Server::GetNumberOfQuestionMultipleChoiceRecords() const
{
	std::vector<QuestionMultipleChoiceRecord> questionMultipleChoiceRecords = m_DataBase->GetQuestionMultipleChoice();
	return questionMultipleChoiceRecords.size();
}

size_t Server::GetNumberOfQuestionNumericRecords() const
{
	std::vector<QuestionNumericRecord> questionMultipleChoiceRecords = m_DataBase->GetQuestionNumeric();
	return questionMultipleChoiceRecords.size();
}
