#include "DBManager.h"

#define SKILL_INFO "SKill_Info_%d"
DBManager::DBManager(void)
{

	setLongLineEventCount(0);
}

DBManager::~DBManager(void)
{

}

DBManager* DBManager::GetInstance()
{
	static DBManager s_manager;
	return &s_manager;
}

//ÉèÖÃ±³¾°ÒôÀÖÒôÁ¿
void DBManager::SetBgmVolume(float volume)
{
	UserDefault::getInstance()->setFloatForKey("BgmVolume", volume);
}

float DBManager::GetBgmVolume()
{
	return UserDefault::getInstance()->getFloatForKey("BgmVolume", 100);
}



bool  DBManager::getISTaskSuccess()
{
	bool success = GetDayGameTimes() >= 5;
	return success;
}

int DBManager::GetDayGameTimes()
{
	return UserDefault::getInstance()->getIntegerForKey("gametimes");
}
void DBManager::AddDayGameTimes()
{
	int var = UserDefault::getInstance()->getIntegerForKey("gametimes");
	UserDefault::getInstance()->setIntegerForKey("gametimes", ++var);
}
void DBManager::initDayGameTimes()
{
	UserDefault::getInstance()->setIntegerForKey("gametimes",0);
}