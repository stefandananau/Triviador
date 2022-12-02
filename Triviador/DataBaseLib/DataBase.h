#pragma once

#include <sqlite_orm/sqlite_orm.h>
#include "QuestionMultipleChoiceRecord.h"
#include "QuestionNumericRecord.h"
#include "UserRecord.h"
namespace DB {
	inline auto CreateDatabase(const std::string& dbName)
	{	
		return sqlite_orm::make_storage(dbName,
			sqlite_orm::make_table("User",
				sqlite_orm::make_column("id", &UserRecord::id, sqlite_orm::primary_key()),
				sqlite_orm::make_column("email", &UserRecord::m_email),
				sqlite_orm::make_column("password", &UserRecord::m_password)),
			sqlite_orm::make_table("QuestionNumeric",
				sqlite_orm::make_column("id",&QuestionNumericRecord::id, sqlite_orm::primary_key()),
				sqlite_orm::make_column("type",&QuestionNumericRecord::m_type),
				sqlite_orm::make_column("question",&QuestionNumericRecord::m_question),
				sqlite_orm::make_column("answer",&QuestionNumericRecord::m_correctAnswer)),
			sqlite_orm::make_table("QuestionMultipleChoice",
				sqlite_orm::make_column("id", &QuestionMultipleChoiceRecord::id, sqlite_orm::primary_key()),
				sqlite_orm::make_column("type", &QuestionMultipleChoiceRecord::m_type),
				sqlite_orm::make_column("question", &QuestionMultipleChoiceRecord::m_question),
				sqlite_orm::make_column("correct_answer", &QuestionMultipleChoiceRecord::m_correctAnswer),
				sqlite_orm::make_column("wrong_answer1", &QuestionMultipleChoiceRecord::m_wrongAnswer1),
				sqlite_orm::make_column("wrong_answer2", &QuestionMultipleChoiceRecord::m_wrongAnswer2),
				sqlite_orm::make_column("wrong_answer3", &QuestionMultipleChoiceRecord::m_wrongAnswer3)));
	}
	using SqlDataBase = decltype(CreateDatabase(""));
}

class DataBase {
private:
	static DataBase* singletonDataBase;
	DB::SqlDataBase m_dataBase;
	DataBase(std::string  name = "DB");

public:
	static DataBase* GetInstance();

	void AddUser(const UserRecord& user);
	std::vector<UserRecord> GetUsers();

	void AddQuestionNumeric(const QuestionNumericRecord& questionNumeric);
	std::vector< QuestionNumericRecord> GetQuestionNumeric();

	void AddQuestionMultipleChoice(const QuestionMultipleChoiceRecord& questionMultipleChoiceRecord);
	std::vector<QuestionMultipleChoiceRecord>GetQuestionMultipleChoice();

	int WipeUsers();
	int WipeQuestions();


	void Sync();
	
};
