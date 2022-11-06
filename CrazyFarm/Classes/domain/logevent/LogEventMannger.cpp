#include "LogEventMannger.h"
#include "LogEventConsume.h"
#include "domain/user/User.h"
LogEventMannger* LogEventMannger::_instance = NULL;

LogEventMannger::LogEventMannger(){
    
}

void LogEventMannger::init(){

}

LogEventMannger* LogEventMannger::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventMannger();
    }
    return _instance;
}
void LogEventMannger::sendMsg()
{
	auto sessionid = User::getInstance()->getSessionid();
	if (sessionid=="")
	{
		CCLOG("send logevnt msg failed with no sessionid");
		return;
	}
	LogEventFish::getInstance()->sendDataToServer();
	LogEventMagnate::getInstance()->sendDataToServer();
	LogEventUseSkill::getInstance()->sendDataToServer();
	LogEventSpcEvent::getInstance()->sendDataToServer();
	LogEventConsume::getInstance()->sendDataToServer();
	User::getInstance()->syncInfo();
}
void LogEventMannger::clearData(int type)
{
	switch (type)
	{
	case 1:
		LogEventFish::getInstance()->clearLocalData(); //ÏÈ²»Çå
		break;
	case 3:
		LogEventMagnate::getInstance()->clearLocalData();
		break;
	case 5:
		LogEventUseSkill::getInstance()->clearLocalData();
		break;
	case 6:
		LogEventPageChange::getInstance()->clearLocalData();
		break;
	case 7:
		LogEventSpcEvent::getInstance()->clearLocalData();
		break;
	case 10:
		LogEventConsume::getInstance()->clearLocalData();
		break;
	case 8:
	case 2:
	case 4:
	default:
		break;
	}
}