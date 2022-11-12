#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include "QuestionMultipleChoiceRecord.h"
#include "QuestionNumericRecord.h"
#include "UserRecord.h"

namespace DB {
	inline auto CreateDatabase(const std::string& dbName)
	{
		using namespace sqlite_orm;

		return make_storage(dbName,
			make_table("User",
				make_column("id", &UserRecord::id, primary_key()),
				make_column("email", &UserRecord::m_email),
				make_column("password", &UserRecord::m_password)),
			make_table("QuestionNumeric",
				make_column("id",&QuestionNumericRecord::id,primary_key()),
				make_column("question",&QuestionNumericRecord::m_question),
				make_column("answer",&QuestionNumericRecord::m_answer)),
			make_table("QuestionMultipleChoice",
				make_column("id", &QuestionMultipleChoiceRecord::id, primary_key()),
				make_column("question", &QuestionMultipleChoiceRecord::m_question),
				make_column("correct_answer", &QuestionMultipleChoiceRecord::m_correctAnswer),
				make_column("wrong_answer1", &QuestionMultipleChoiceRecord::m_wrongAnswer1),
				make_column("wrong_answer2", &QuestionMultipleChoiceRecord::m_wrongAnswer2),
				make_column("wrong_answer3", &QuestionMultipleChoiceRecord::m_wrongAnswer3)));
	}

	using SqlDataBase = decltype(CreateDatabase(""));

}
