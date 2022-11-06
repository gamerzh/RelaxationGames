#include "GlobalSchedule.h"  
#include "domain/logevent/LogEventMannger.h"
#include "data/GameData.h"
#define LOGEVENTINTERVAL 300
GlobalSchedule* GlobalSchedule::m_pSchedule = NULL;  
   
GlobalSchedule::GlobalSchedule() {
	init();
}

GlobalSchedule* GlobalSchedule::getInstance(){
	if (m_pSchedule == NULL){
		m_pSchedule = new GlobalSchedule();
	}
	return m_pSchedule;
}

bool GlobalSchedule::init()
{
	Director::getInstance()->getScheduler()->schedule(schedule_selector(GlobalSchedule::updataByMin), this, 10.0f, false);
	return true;
}


void GlobalSchedule::updataByMin(float dt)
{
	if (GameData::getInstance()->getisOnGameScene())
	{
		addGameTime(dt);
	}
	else
	{
		addRoomTime(dt);
	}

	addLogEventTime(dt);

	//if (getLogEventTime() > LOGEVENTINTERVAL)
	//{
	//	addLogEventTime(-getLogEventTime());
	///*	LogEventMannger::getInstance()->sendMsg();*/
	//}
}

void GlobalSchedule::addGameTime(float dt)
{
	UserDefault::getInstance()->setFloatForKey(SCHEDULE_GAMETIME, UserDefault::getInstance()->getFloatForKey(SCHEDULE_GAMETIME, 0) + dt);
}

void GlobalSchedule::addRoomTime(float dt)
{
	UserDefault::getInstance()->setFloatForKey(SCHEDULE_ROOMTIME, UserDefault::getInstance()->getFloatForKey(SCHEDULE_ROOMTIME, 0) + dt);
}

float GlobalSchedule::getGameTime()
{
	return UserDefault::getInstance()->getFloatForKey(SCHEDULE_GAMETIME);
}
float GlobalSchedule::getRoomTime()
{
	return UserDefault::getInstance()->getFloatForKey(SCHEDULE_ROOMTIME);
}

void GlobalSchedule::addLogEventTime(float dt)
{
	UserDefault::getInstance()->setFloatForKey(SCHEDULE_LOGEVETTIME, UserDefault::getInstance()->getFloatForKey(SCHEDULE_LOGEVETTIME, 0) + dt);
}

float GlobalSchedule::getLogEventTime()
{
	return UserDefault::getInstance()->getFloatForKey(SCHEDULE_LOGEVETTIME);
}