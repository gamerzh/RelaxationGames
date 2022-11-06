#include "PayEventMannger.h"
#include "Room.h"
#include "User.h"
#define PLAYINFO_PICKCARDSCOUNT "goodTimes"
PayEventMannger* PayEventMannger::_instance = 0;
PayEventMannger::PayEventMannger(){
	set_isLastGameDelevel(false);
	set_isLastGainAlms(false);
	set_isSatisfied_Event12(false);
	set_isSatisfied_Event14(false);
	set_isSatisfied_Event15(false);
	init();
}
PayEventMannger* PayEventMannger::getInstance(){
	if(_instance == 0){
		_instance = new PayEventMannger();
	}
	return _instance;
}
void PayEventMannger::init()
{

}
void PayEventMannger::RecordInfoOnGamestart()
{
	setGamecount(getGamecount() + 1);
}
void PayEventMannger::RecordInfoOnGameend(bool isDelevel, bool isGainAlms, bool isWin, bool isCouldUpdateRoom)
{
	if (get_isLastGameDelevel()&&get_isLastGainAlms()&&isWin&&isCouldUpdateRoom)
	{
		setisSatisfied_Event_12or14_count(getisSatisfied_Event_12or14_count()+1);
		if (getisSatisfied_Event_12or14_count() % 2 == 0 && getisSatisfied_Event_12or14_count() / 2 > 0)
		{
			set_isSatisfied_Event12(true);
		}
		if (getisSatisfied_Event_12or14_count() == 1 && getisSatisfied_Event_12or14_count() ==2)
		{
			set_isSatisfied_Event14(true);
		}
	}

	int times = UserDefault::getInstance()->getIntegerForKey(PLAYINFO_PICKCARDSCOUNT, 3);
	if (!isWin&&getIsPay_Coin() && !times)
	{
		setisSatisfied_Event_15_count(getisSatisfied_Event_15_count() + 1);
		if (getisSatisfied_Event_15_count() % 3 == 0 && getisSatisfied_Event_15_count() /3>0)
		{
			set_isSatisfied_Event15(true);
		}
	}

	set_isLastGameDelevel(isDelevel);
	set_isLastGainAlms(isGainAlms);
}

bool PayEventMannger::isSatisfied_Event_5(bool isPickGood)
{
	int times = UserDefault::getInstance()->getIntegerForKey(PLAYINFO_PICKCARDSCOUNT, 3);
	if (isPickGood&&!times)
	{
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_8(bool isPickGood)
{
	if (isPickGood&&!getIsPay_PickGood())
	{
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_9()
{
	static bool isFistComing = true;
	if (isFistComing)
	{
		isFistComing = false;
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_10(int roomCoin)
{
	int coin = User::getInstance()->getMyCoins();
	if (coin<roomCoin)
	{
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_7()
{
	if (getGamecount() == 1)
	{
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_11()
{
	if (getGamecount()%12 == 0)
	{
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_12()
{
	if (get_isSatisfied_Event12())
	{
		set_isSatisfied_Event12(false);
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_13()
{
	int coin = User::getInstance()->getMyCoins();
	if (coin < 1000)
	{
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_14()
{
	if (get_isSatisfied_Event14())
	{
		set_isSatisfied_Event14(false);
		return true;
	}
	return false;
}
bool PayEventMannger::isSatisfied_Event_15()
{
	if (get_isSatisfied_Event15())
	{
		set_isSatisfied_Event15(false);
		return true;
	}
	return false;
}