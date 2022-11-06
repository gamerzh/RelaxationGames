#include "SignManager.h"
#include "SystemTime.h"

const char* KEY_LASTSIGNDAY = "KEY_LASTSIGNDAY";
const char* KEY_SEQSIGNDAY = "KEY_SEQSIGNDAY";
SignManager* SignManager::_instance = NULL;

SignManager::SignManager(){

}
SignManager* SignManager::getInstance(){
    if(_instance == NULL){
		_instance = new SignManager();
    }
    return _instance;
}
int SignManager::getCurrentSignDay()
{

	auto str = UserDefault::getInstance()->getStringForKey(KEY_LASTSIGNDAY, "-1");
	auto Today = SystemTime::getToday();
	auto formatStrToday = Today->getFormatString();
	if (str == "-1")
	{
		return 1;
	}
	else if (str == formatStrToday)
	{
		return 0;
	}
	SystemTime* lastDay = new SystemTime(str);
	int diffday= SystemTime::diffDayByAandB(lastDay, Today);
	if (diffday==1)
	{
		int dayCout = UserDefault::getInstance()->getIntegerForKey(KEY_SEQSIGNDAY, 0);
		return (dayCout + 1) > 7 ? 1 : dayCout + 1;
	}
	else
	{
		return 1;
	}


}
void SignManager::sign(int seqDay)
{
	UserDefault::getInstance()->setIntegerForKey(KEY_SEQSIGNDAY, seqDay);
	UserDefault::getInstance()->setStringForKey(KEY_LASTSIGNDAY, SystemTime::getToday()->getFormatString());
	CCLOG("day = %s signed", SystemTime::getToday()->getFormatString().c_str());
}