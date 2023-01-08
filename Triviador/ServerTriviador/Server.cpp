#include "Server.h"
#include <regex>

#define numberOfRequiredPlayers 2 //this is for debugging purposes

Server::Server() {
	m_DataBase = DataBase::GetInstance();
	m_DataBase->Sync();


	PopulateServerDatabase();

	/*wipeUsers();
	wipeQuestions();*/

	//SetupServer();


}

void Server::drawBoard() {
	for (const auto& row : m_Board.GetBoard())
	{
		for (const auto& element : row)
		{
			std::cout << element.GetOwner().GetUser() << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Server::matchStarted() {
	//1. first question has to be numerical and decides which client gets to pick a piece of land first

	size_t numberOfClients = GetNumberOfPlayersInLobby();

	m_Board = Board(numberOfClients);


	for (auto player : m_Lobby) {
		Player playerForMap(player.first);
		m_PlayersInGame[player.first] = playerForMap;
	}


	drawBoard();

	m_CurrentNumericQuestion = RandomNumeric(GetGenerator());

	//m_GameState = state::WAITING_ANSWER;
	m_CurrentQuestionType = questionType::NUMERIC;

	m_GameState = Server::state::waitingForQuestionResponse;

}

crow::json::wvalue Server::CurrentQuestionToJson() {
	crow::json::wvalue outJson;
	if (m_GameState == state::waitingForQuestionResponse) {
		switch (m_CurrentQuestionType) {
		case questionType::NUMERIC:
			outJson = {
				{"question", m_CurrentNumericQuestion.m_question},
				{"answers", m_CurrentNumericQuestion.m_correctAnswer}
			};
			break;
			//TO DO: same for multiple
		default:
			break;
		}
		return outJson;
	}
	return crow::json::wvalue(409);
}

crow::json::wvalue Server::ReturnReadyUsersInLobby()
{
	crow::json::wvalue outJson;
	int index = 0;
	for (auto player : m_Lobby) {
		if (player.second == true) {
			outJson[index] = crow::json::wvalue(player.first);
			index++;
		}
	}
	return outJson;
}

crow::json::wvalue Server::ReturnUnreadyUsersInLobby()
{
	crow::json::wvalue outJson;
	int index = 0;
	for (auto player : m_Lobby) {
		if (player.second == false) {
			outJson[index] = crow::json::wvalue(player.first);
			index++;
		}
	}
	return outJson;
}

bool Server::AllAnswersAreGiven()
{
	bool ok = true;
	for (const auto& player : m_PlayersInGame)
	{
		if (player.second.GetAnswer().empty())
		{
			ok = false;
			break;
		}
	}
	return ok;
}

crow::json::wvalue Server::CheckGameState() {
	crow::json::wvalue outJson;


	switch (m_GameState) {
	case state::waitingForPlayers:
		outJson = { { "state", "waiting_for_players" } };
		break;
	case state::gameInProgress:
		outJson = { {"state", "game_in_progress"} };
		break;
	case state::waitingForQuestionResponse:
		outJson = { {"state", "waiting_for_question_answer"} };
		break;
	case state::showAnswers:
		outJson = { {"state", "show_answers"} };
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
			QuestionMultipleChoiceRecord pulledMultipleQuestions = RandomMultipleChoice(generator);
			return crow::response(crow::json::wvalue({
				{"Id", pulledMultipleQuestions.id},
				{"Question", pulledMultipleQuestions.m_question},
				{"Responses",
				crow::json::wvalue::list(
					{
				pulledMultipleQuestions.m_correctAnswer,
				pulledMultipleQuestions.m_wrongAnswer1,
				pulledMultipleQuestions.m_wrongAnswer2,
				pulledMultipleQuestions.m_wrongAnswer3
				})
				}
				}
			));
		}
		if (type == "Numeric")

		{
			QuestionNumericRecord pulledNumericalQuestions = RandomNumeric(generator);
			return crow::response(std::move(crow::json::wvalue({
				{"Id", pulledNumericalQuestions.id},
				{"Question", pulledNumericalQuestions.m_question},

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
		if (strlen(email) == 0)
		{
			return crow::response(405, "email field is null");//Method Not Allowed
		}
		auto password = req.url_params.get("password");
		if (strlen(password) == 0)
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
			return crow::response(404, "email not found");//Not Found
		}
	}
	else if (req.url_params.get("register"))
	{
		auto email = req.url_params.get("email");
		if (strlen(email) == 0)
		{
			return crow::response(405, "email field is null");//Method Not Allowed
		}
		if (!std::regex_match(email, std::regex("^[A-Za-z0-9]+@[a-z]+\.[a-z]+(\.[a-z]+)?$"))) {
			return crow::response(417, "email expectations not satisfied");
		}
		auto password = req.url_params.get("password");
		if (strlen(password) == 0)
		{
			return crow::response(405, "password field is null");//Method Not Allowed
		}

		if (!std::regex_match(password, std::regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[.,?!*@]).{6,}$")))
		{
			return crow::response(417, "password expectations not satisfied");
		}
		
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

crow::response Server::AddUserToLobbyRoute(const crow::request& req) {
	auto userName = req.url_params.get("email");
	if (m_GameState != waitingForPlayers) {
		return crow::response(403, "game in progress");
	}
	if (m_Lobby.size() == 4) {
		return crow::response(403, "lobby full");
	}
	std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();
	auto email = req.url_params.get("email");
	if (m_Lobby.contains(email)) {
		return crow::response(404, "user already in lobby");
	}
	auto user = std::find_if(pulledUser.begin(), pulledUser.end(), [email](const UserRecord& u) {
		return u.m_email == email;
		});
	if (user == pulledUser.end())
	{
		return crow::response(404, "something bad happened");//Not found
	}
	else {
		m_Lobby[userName] = false;
		m_GameState = state::waitingForPlayers;
		return crow::response(200, "joined lobby");
	}
}

crow::response Server::RemoveUserFromLobbyRoute(const crow::request& req)
{
	auto email = req.url_params.get("email");
	if (!m_Lobby.contains(email)) {
		return crow::response(404, "user not already in lobby");
	}
	m_Lobby.erase(email);
	return crow::response(200, "exit lobby");
}

crow::response Server::SetUserToReadyInLobbyRoute(const crow::request& req) {
	auto email = req.url_params.get("email");
	size_t numberOfReadyUsers = 0;
	if (!m_Lobby.contains(email)) {
		return crow::response(404, "user already ready");//not found
	}
	else {
		m_Lobby[email] = true;
		for (const auto &elem : m_Lobby) {
			if (elem.second == true) {
				numberOfReadyUsers++;
			}
		}
		if ((numberOfReadyUsers >= 2) && (numberOfReadyUsers == m_Lobby.size())) {
			this->m_GameState = state::gameInProgress;
			std::cout << "Game started!\n";
			//first random num question should be set here
			matchStarted();

		}

		return crow::response(200 ,"user ready");//ok
	}
	m_Lobby[email] = true;
	return crow::response(200, "user ready");//ok
}

crow::response Server::SetUserToUnreadyInLobbyRoute(const crow::request& req)
{
	if (m_GameState != waitingForPlayers) {
		return crow::response(403, "game in progress");
	}
	auto email = req.url_params.get("email");
	size_t numberOfReadyUsers = 0;
	if (!m_Lobby.contains(email)) {
		return crow::response(404, "user already unready");//not found
	}
	m_Lobby[email] = false;
	return crow::response(200, "user unready");
}

crow::response Server::ReturnUserStats(const crow::request& req)
{
	std::vector<UserRecord> pulledUser = m_DataBase->GetUsers();
	std::string email = req.url_params.get("email");
	auto user = std::find_if(pulledUser.begin(), pulledUser.end(), [email](const UserRecord& u) {
		return u.m_email == email;
		});
	if (user != pulledUser.end())
	{
		auto Stats = m_DataBase->GetUserStats(email);
		return crow::response(std::move(crow::json::wvalue({
			{ "Number of played games", std::to_string(std::get<0>(Stats[0]))},
			{ "Number of won games", std::to_string(std::get<1>(Stats[0]))},
			{"win/lose Ratio", std::get<2>(Stats[0]) } }
		)));
	}
	else {
		return crow::response(std::move(crow::json::wvalue({
			{ "Number of played games","-"},
			{ "Number of won games", "-"},
			{"win/lose Ratio", "-" }}
		)));
	}
}

crow::response Server::NumberOfPlayersInLobby()
{
	return crow::response(crow::json::wvalue({ "numberOfPlayers", m_Lobby.size() }));
}

crow::response Server::RemovePowerUp(const crow::request& req)
{
	if (!req.url_params.get("user"))
	{
		return crow::response(404);//not found
	}
	else
	{
		auto userName = req.url_params.get("user");
		Player player = m_PlayersInGame[userName];
		if (!req.url_params.get("powerUp"))
		{
			return crow::response(404);//not found
		}
		else
		{
			int numberOfPowerUps = player.NumberOfPowerUp();
			player.RemovePowerUp(req.url_params.get("powerUp"));
			if (numberOfPowerUps == player.NumberOfPowerUp())
			{
				return crow::response(403);//forbidden
			}
			return crow::response(200);
		}
	}
}

crow::response Server::AttackIsland(const crow::request& req)
{
	if (!(req.url_params.get("width") && req.url_params.get("height") && req.url_params.get("attacker")))
	{
		return crow::response(404);
	}
	else
	{
		auto width = int(req.url_params.get("width"));
		auto height = int(req.url_params.get("height"));
		auto attacker = req.url_params.get("attacker");
		m_Board.SetAttacker(height, width, m_PlayersInGame[attacker]);
		return crow::response(200);
	}
}

crow::response Server::OwnerIsland(const crow::request& req)
{
	if (!(req.url_params.get("width") && req.url_params.get("height") ))
	{
		return crow::response(404);
	}
	else
	{
		auto width = int(req.url_params.get("width"));
		auto height = int(req.url_params.get("height"));
		m_Board.ChangeOwner(height, width);
		return crow::response(200);
	}
}

crow::json::wvalue Server::ValidateAnswer()
{
	int diffCur = INT_MAX;
	std::string userWinner;
	crow::json::wvalue res;
	for (const auto& player : m_PlayersInGame)
	{
		int diff = std::abs(stoi(player.second.GetAnswer()) - stoi(m_CurrentNumericQuestion.m_correctAnswer));
		if (diff < diffCur)
		{
			diffCur = diff;
			userWinner = player.first;
		}
	}
	res["winner"] = userWinner;
	return res;
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
		User u("admin@admin.com", "admin");
		m_DataBase->AddUser(u);

		for (const User& user : usersToAppend) {
			m_DataBase->AddUser(UserRecord(user));
		}
	}


}

crow::response Server::AddQuestionAnswerToUser(const crow::request& req) {
	auto userName = req.url_params.get("email");
	auto answer = req.url_params.get("answer");
	//m_Game.PlayerSetAnswer(userName, answer);
	m_PlayersInGame[userName].SetAnswer(answer);
	if (AllAnswersAreGiven())
		m_GameState = state::showAnswers;
	return crow::response(200); //ok
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
		"/database/getStats?email=<value>\n"
		"	If value is a valid email it returns the stats of the player\n"
		"/database/getQuestion?type=<value>\n"
		"	If value is Multiple then the response is a random question from QuestionMultipleChoice Table with id,question and answers\n"
		"	If value is Numeric then the response is a random question from QuestionNumeric Table with id,question\n"
		"/authentication?(login or register)&email=<value1>&password=<value2>\n"
		"	If login exists then\n"
		"		If email and password is in User Table then the response is Ok else if password is incorrect response is Unauthorized\n"
		"		If email is not in User Table then the response is Not Found\n"
		"	If register exists then\n"
		"		If email is in User Table then the response is Conflict else new user is added in User Table and response is Ok\n"
		"/lobby/join?email=<value>\n"
		"	Where <value> is the user email to add to lobby object\n"
		"/lobby/rplayers\n"
		"	Returns the current number of ready players in lobby\n"
		"/lobby/uplayers\n"
		"	Returns the current number of unready players in lobby\n"
		"/game/questionAnswer?email=<value1>&answer=<value2>\n"
		"	Asigns an answer to <value1> (user email) through <value2> (answer) for the currently displayed question\n"
		"/game/validateAnswer\n"
		"	Validate a numeric question answer set for current user\n"
		"/game/currentQuestion\n"
		"	Returns the currently set question in game\n"
		"/game/player/powerUp?user=<value1>&powerUp=<value2>\n"
		"	Removes the value2 powerUp from the value1 player\n\n\n";

	CROW_ROUTE(m_crowApp, "/database")([this](const crow::request& req) {
		return DataBaseRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/database/getQuestion")([this](const crow::request& req) {
		return ReturnRandomQuestionRoute(req, m_Generator);

		});

	CROW_ROUTE(m_crowApp, "/database/getStats")([this](const crow::request& req)
		{
			return ReturnUserStats(req);
		});

	CROW_ROUTE(m_crowApp, "/authentication")([this](const crow::request& req) {
		return AuthenticationRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/lobby/join")([this](const crow::request& req) {
		return AddUserToLobbyRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/lobby/exit")([this](const crow::request& req) {
		return RemoveUserFromLobbyRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/lobby/ready")([this](const crow::request& req) {
		return SetUserToReadyInLobbyRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/lobby/unready")([this](const crow::request& req) {
		return SetUserToUnreadyInLobbyRoute(req);
		});

	CROW_ROUTE(m_crowApp, "/lobby/gameState")([this]() {
		return CheckGameState();
		});

	CROW_ROUTE(m_crowApp, "/lobby/rplayers")([this]() {
		return ReturnReadyUsersInLobby();
		});

	CROW_ROUTE(m_crowApp, "/lobby/uplayers")([this]() {
		return ReturnUnreadyUsersInLobby();
		});
	CROW_ROUTE(m_crowApp, "/game/attacker")([this](const crow::request& req) {
		return AttackIsland(req);
		});

	CROW_ROUTE(m_crowApp, "/game/owner")([this](const crow::request& req) {
		return OwnerIsland(req);
		});

	CROW_ROUTE(m_crowApp, "/game/player/powerUp")([this](const crow::request& req) {
		return RemovePowerUp(req);
		});
	CROW_ROUTE(m_crowApp, "/game/questionAnswer")([this](const crow::request& req) {
		//req: email + questionAnswer
		return AddQuestionAnswerToUser(req);

		});
	CROW_ROUTE(m_crowApp, "/game/validateAnswer")([this]()
		{
			return ValidateAnswer();
		});
	CROW_ROUTE(m_crowApp, "/game/currentQuestion")([this]() {
		return CurrentQuestionToJson();
		});
	CROW_ROUTE(m_crowApp, "/game/numberOfPlayersInLobby")([this]() {
		return NumberOfPlayersInLobby();
		});

	m_crowApp.port(80);
	m_crowApp.multithreaded();
	m_crowApp.run_async();
	m_crowApp.debug_print();


}

QuestionMultipleChoiceRecord Server::RandomMultipleChoice(std::default_random_engine& generator)
{
	std::vector<QuestionMultipleChoiceRecord> pulledMultipleQuestions = m_DataBase->GetQuestionMultipleChoice();
	std::uniform_int_distribution<int> distribution(0, pulledMultipleQuestions.size() - 1);
	int QuestionID = distribution(generator);
	return pulledMultipleQuestions[QuestionID];
}

QuestionNumericRecord Server::RandomNumeric(std::default_random_engine& generator)
{
	std::vector<QuestionNumericRecord> pulledNumericalQuestions = m_DataBase->GetQuestionNumeric();
	std::uniform_int_distribution<int> distribution(0, pulledNumericalQuestions.size() - 1);
	int QuestionID = distribution(generator);
	return pulledNumericalQuestions[QuestionID];
}

std::default_random_engine& Server::GetGenerator()
{
	return m_Generator;
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

size_t Server::GetNumberOfPlayersInLobby() const
{
	return m_Lobby.size();
}

std::map<std::string, bool> Server::GetPlayersInLobby() {
	return m_Lobby;
}

void Server::SetState(state stateToSet) {
	m_GameState = stateToSet;
}