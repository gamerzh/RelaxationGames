#ifndef _USER_H_
#define _USER_H_
#include "cocos2d.h"

#include "config/ConfigExp.h"
#include "config/ConfigVipLevel.h"
#include "domain/nobility/NobilityManager.h"
#include "utill/define.h"
#include "domain/logevent/LogEventConsume.h"
using namespace cocos2d;

class User{
public:
	static User* getInstance();
    
	std::string getUserId();
	void setUserID(std::string userId);



    std::string getUserName();
    bool setUserName(std::string newUserName);

	int getUserGender();
	void setUserGender(int gender);

	int addCoins(int coins);
	int getCoins();

	int getNobillityCount();

	int getExp(){ return UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0); }
	int addDiamonds(int diamond);
	int getDiamonds();
    
    int getMaxTurrentLevel();

    bool setMaxTurrentLevel(int maxTurrentLevel);

	const char*USERBOXLEVEL = "USERBOXLEVEL";
	CC_SYNTHESIZELOCALINT(USERBOXLEVEL, UserBoxLevel, 0);
	
    int getVipLevel();
    
    bool addChargeMoney(int money);
    int getChargeMoney();

    

	int getGuizuDay();
    /**
     * return true, level up!! else, return false.
     */
    bool addExp(int exp);
    
	bool getIsHaveFirstPay(){ return UserDefault::getInstance()->getBoolForKey(KEY_ISHAVEFIRSTPAY,false); };
	void setHaveFirstPay(){ UserDefault::getInstance()->setBoolForKey(KEY_ISHAVEFIRSTPAY, true); };

	bool getIsHaveBycoin(){ return UserDefault::getInstance()->getBoolForKey(KEY_ISHAVEBYCOIN, false); };
	void setHaveBycoin(){ UserDefault::getInstance()->setBoolForKey(KEY_ISHAVEBYCOIN, true); };


	bool getIsHaveSetName(){ return UserDefault::getInstance()->getBoolForKey(KEY_ISHAVESETNAME, false); };
	void setHaveSetName(){ UserDefault::getInstance()->setBoolForKey(KEY_ISHAVESETNAME, true); };

    LevelData getLevelData();
    
    void resetInfo();


	void syncInfo();
private:
	User();
	void init();
	static User* _instance;
    
    const char* KEY_COINS = "KEY_COINS";
	const char* KEY_NOBILLITYS = "KEY_NOBILLITYS";
    const char* KEY_DIAMONDS = "KEY_DIAMONDS";
    const char* KEY_EXP = "KEY_EXP";
    const char* KEY_M_TURRENT = "KEY_M_TURRENT";
	const char* KEY_CATCHPER = "KEY_CATCHPER";
    const char* KEY_USER_ID = "KEY_USER_ID";
    const char* KEY_USER_NAME = "KEY_USER_NAME";
	const char* KEY_USER_GENDER = "KEY_USER_GENDER";
    const char* KEY_LASTSIGNDAY = "KEY_LASTSIGNDAY";
    const char* KEY_SEQSIGNDAY = "KEY_SEQSIGNDAY";
    const char* KEY_CHARGE_MONEY = "KEY_CHARGE_MONEY";
    const char* KEY_CHEST_LEVEL = "KEY_CHEST_LEVEL";
	const char* KEY_ISHAVEFIRSTPAY = "ISHAVEFIRSTPAY";
	const char* KEY_ISHAVESETNAME = "ISHAVESETNAME";
	const char* KEY_ISHAVEBYCOIN = "KEY_ISHAVEBYCOIN";
	CC_SYNTHESIZE(std::string, session_id, Sessionid);

};

#endif
