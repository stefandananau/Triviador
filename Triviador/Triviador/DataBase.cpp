#include "DataBase.h"

DataBase* DataBase::singletonDataBase;

DataBase::DataBase(std::string name) : m_dataBase(DB::CreateDatabase(name)) {}

DataBase* DataBase::GetInstance()
{
	if (singletonDataBase == nullptr) {
		singletonDataBase = new DataBase();
	}
	return singletonDataBase;
}

void DataBase::AddUser(const UserRecord& user)
{
	m_dataBase.insert(user);
}

void DataBase::Sync()
{
	m_dataBase.sync_schema();
}

std::vector<UserRecord> DataBase::GetUsers()
{
    return m_dataBase.get_all<UserRecord>();
}

void DataBase::AddQuestionNumeric(const QuestionNumericRecord& questionNumeric)
{
	m_dataBase.insert(questionNumeric);
}

std::vector<QuestionNumericRecord> DataBase::GetQuestionNumeric()
{
	return  m_dataBase.get_all<QuestionNumericRecord>();
}


void DataBase::AddQuestionMultipleChoice(const QuestionMultipleChoiceRecord& questionMultipleChoiceRecord)
{

	m_dataBase.insert(questionMultipleChoiceRecord);

}

std::vector<QuestionMultipleChoiceRecord> DataBase::GetQuestionMultipleChoice()
{
	return 	  m_dataBase.get_all<QuestionMultipleChoiceRecord>();

}