#ifndef __USER_H__
#define __USER_H__
#include "cocos2d.h"
USING_NS_CC;
#define PLAYINFO_COIN "coins"
#define USER_NAME  "user_name"
#define USER_ROLE  "user_role"
#define USER_ROLE_NOWINDEX  "user_role_nowindex"
#define USER_VIP  "user_vip"
#define USRE_ISPAYFIRSTPOINT "user_ispayfirstpaypoint"
#define USRE_GAMECOUNT "user_gamecount"

#define CC_SYNTHESIZELOCALINT(KeyName, funName,initValue)\
public: int get##funName(void) const { return UserDefault::getInstance()->getIntegerForKey(KeyName,initValue); }\
public: void set##funName(int var){ UserDefault::getInstance()->setIntegerForKey(KeyName,var); }

#define CC_SYNTHESIZELOCALSTRING(KeyName, funName,initValue)\
public: std::string get##funName(void) const { return UserDefault::getInstance()->getStringForKey(KeyName,initValue); }\
public: void set##funName(std::string var){ UserDefault::getInstance()->setStringForKey(KeyName,var); }


class User
{

public:
	static User* getInstance()
	{
		if (nullptr == instance)
		{
			instance = new User();
		}
		return instance;
	}
	void addCoin(int difCoin);


	bool isAvailableRole(int index);
	void setAvailableRole(int index);

	CC_SYNTHESIZELOCALINT(USRE_GAMECOUNT, gamecount, 0);
	CC_SYNTHESIZELOCALINT(USER_ROLE_NOWINDEX, roleNowIndex, 1);
	CC_SYNTHESIZELOCALINT(PLAYINFO_COIN, MyCoins, 10000);
	CC_SYNTHESIZELOCALSTRING(USER_NAME, MyName, "defulat");
	CC_SYNTHESIZELOCALINT(USER_VIP, isVip, 0);
	CC_SYNTHESIZELOCALINT(USRE_ISPAYFIRSTPOINT, isPayFirstPayPoint, 0);
private:
	static User* instance;
	User();

};

#endif