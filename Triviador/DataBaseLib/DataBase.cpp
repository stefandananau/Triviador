#include "DataBase.h"
#include <filesystem>
DataBase* DataBase::singletonDataBase;

DataBase::DataBase(std::string name) : m_dataBase( DB::CreateDatabase(name))
{
	if(!std::filesystem::exists(name))
	{
		Sync();
	}
}

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
	return m_dataBase.get_all<QuestionMultipleChoiceRecord>();

}

std::vector<std::tuple<int,int,float>> DataBase::GetUserStats(const std::string& email)
{
	return m_dataBase.select(sqlite_orm::columns ( & UserRecord::m_numberOfPlayedGames, &UserRecord::m_numberOfWonGames, &UserRecord::m_winLoseRatio), sqlite_orm::where(sqlite_orm::c(&UserRecord::m_email) = email));
	
}

int DataBase::WipeUsers()
{
	m_dataBase.remove_all<UserRecord>();
	
	return 0;
}

int DataBase::WipeQuestions()
{
	m_dataBase.remove_all<QuestionMultipleChoiceRecord>();
	m_dataBase.remove_all<QuestionNumericRecord>();
	
	return 0;
}
