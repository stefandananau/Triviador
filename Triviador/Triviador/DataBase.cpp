#include "DataBase.h"


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
