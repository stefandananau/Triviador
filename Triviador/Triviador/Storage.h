#pragma once
#include "DataBase.h"
class Storage
{
private:
	DB::SqlDataBase m_dataBase;
public:
	Storage(const std::string& dbName);

	void AddUser(const UserRecord& user);

	void Sync();
	void PrintUsers();
	void PrintQuestionMultipleChoice();
	void PrintQuestionNumeric();
};


