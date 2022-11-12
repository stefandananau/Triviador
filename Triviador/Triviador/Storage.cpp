#include "Storage.h"

#include <iostream>

Storage::Storage(const std::string& dbName) : m_dataBase(DB::CreateDatabase(dbName))
{

}
void Storage::Sync()
{
	m_dataBase.sync_schema();
}

void Storage::AddUser(const UserRecord& user)
{
	m_dataBase.insert(user);
}

void Storage::PrintUsers()
{
	auto allUsers = m_dataBase.get_all<UserRecord>();
	for (const auto& user : allUsers)
	{
		std::cout << m_dataBase.dump(user) << std::endl;
	}
}

void Storage::PrintQuestionMultipleChoice()
{
	auto allQuestions = m_dataBase.get_all<QuestionMultipleChoiceRecord>();
	for (const auto& question : allQuestions)
	{
		std::cout << m_dataBase.dump(question) << std::endl;
	}
}
void Storage::PrintQuestionNumeric()
{
	auto allQuestions = m_dataBase.get_all<QuestionNumericRecord>();
	for (const auto& question : allQuestions)
	{
		std::cout << m_dataBase.dump(question) << std::endl;
	}
}
