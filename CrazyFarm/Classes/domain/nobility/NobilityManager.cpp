#include "domain/nobility/NobilityManager.h"
#include "config/ConfigSign.h"
#include "utill/dayUtil.h"
#include "domain/user/User.h"
NobilityManager* NobilityManager::_instance = NULL;

NobilityManager::NobilityManager(){
    this->init();
}


void NobilityManager::init(){
    NobilityRewadItem item1;
    item1.item_id = 1001;
    item1.num = 20000;
    this->nobilityRewadItems.push_back(item1);
    NobilityRewadItem item2;
    item2.item_id = 1002;
    item2.num = 20;
    this->nobilityRewadItems.push_back(item2);
    NobilityRewadItem item3;
    item3.item_id = 1004;
    item3.num = 5;
    this->nobilityRewadItems.push_back(item3);
    NobilityRewadItem item4;
    item4.item_id = 1003;
    item4.num = 2;
    this->nobilityRewadItems.push_back(item4);
}

NobilityManager* NobilityManager::getInstance(){
    if(_instance == NULL){
        _instance = new NobilityManager();
    }
    return _instance;
}
int NobilityManager::RemainingNobilityday()
{
	int day;
	auto today = SystemTime::getToday();
	auto stayday = UserDefault::getInstance()->getStringForKey(KEY_STARTDAY, "-1");
	if (stayday =="-1")
	{
		return 0;
	}
	int diffday = SystemTime::diffDayByAandB(new SystemTime(stayday), today);
	auto steps = UserDefault::getInstance()->getIntegerForKey(KEY_STEPS, 0);
	day = steps - diffday;
	if (day>0)
	{
		return day;
	}
	else
	{
		return 0;
	}
}
bool NobilityManager::isNobility() {
	auto stayday = UserDefault::getInstance()->getStringForKey(KEY_STARTDAY,"-1");
	auto steps = UserDefault::getInstance()->getIntegerForKey(KEY_STEPS, 0);
	auto today = SystemTime::getToday();
	if (stayday == "-1")
	{
		return false;
	}
	else
	{
		SystemTime* a = new SystemTime(stayday);
		int diffday = SystemTime::diffDayByAandB(a, today);
		if (diffday<steps)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

    return false;   // TODO : wait impl
}

std::vector<NobilityRewadItem> NobilityManager::getNobilityRewadItems() {
    return nobilityRewadItems;
}

bool NobilityManager::isGetRewardToday()
{
	if (isNobility())
	{
		return UserDefault::getInstance()->getBoolForKey(ConfigSign::getInstance()->getToday().c_str(), true);
	}
	return false;
}
void NobilityManager::setGetRewardToday()
{

	UserDefault::getInstance()->setBoolForKey(ConfigSign::getInstance()->getToday().c_str(), false);

}


void NobilityManager::addStepsDay(int dayNum)
{
	auto today = SystemTime::getToday()->getFormatString();
	auto stayday = UserDefault::getInstance()->getStringForKey(KEY_STARTDAY, "-1");
	auto steps = UserDefault::getInstance()->getIntegerForKey(KEY_STEPS, 0);
	if (stayday == "-1")
	{
		//从来没有购买过
		UserDefault::getInstance()->setStringForKey(KEY_STARTDAY, today.c_str());
		UserDefault::getInstance()->setIntegerForKey(KEY_STEPS, steps + dayNum);
	}
	else
	{
		if (steps == 0)
		{
			UserDefault::getInstance()->setStringForKey(KEY_STARTDAY, today.c_str());
			UserDefault::getInstance()->setIntegerForKey(KEY_STEPS, steps + dayNum);
		}
		else
		{
			UserDefault::getInstance()->setIntegerForKey(KEY_STEPS, steps + dayNum);
		}
	}

}