#include "domain/user/User.h"
#include "server/HttpMannger.h"
#include "domain/Newbie/NewbieMannger.h"
User* User::_instance = NULL;

User::User(){
	this->init();
}

void User::init(){
	setSessionid("");
    // TODO : first use init user name and id
}

User* User::getInstance(){
	if(_instance == NULL){
		_instance = new User();
	}
	return _instance;
}

std::string User::getUserId() {
	return UserDefault::getInstance()->getStringForKey(User::KEY_USER_ID, "guest");
}

void User::setUserID(std::string userId) {
	UserDefault::getInstance()->setStringForKey(User::KEY_USER_ID, userId);
}

int User::getUserGender() {
	return UserDefault::getInstance()->getIntegerForKey(User::KEY_USER_GENDER,0);
}

void User::setUserGender(int gender) {
	UserDefault::getInstance()->setIntegerForKey(User::KEY_USER_GENDER, gender);
}

std::string User::getUserName() {
    std::string name = UserDefault::getInstance()->getStringForKey(User::KEY_USER_NAME, "guest");
    if( name.compare("guest") == 0) {
        return getUserId();
    }
     log("guest != guest");
    return name;
}

bool User::setUserName(std::string newUserName) {
    std::string name = UserDefault::getInstance()->getStringForKey(User::KEY_USER_NAME, "guest");
    if(name == "guest") {
        UserDefault::getInstance()->setStringForKey(User::KEY_USER_NAME, newUserName);
        return true;
    }
    return false;
}






int User::getCoins() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_COINS, 0);
}

int User::addCoins(int coins) {
	LogEventConsume::getInstance()->addEventCoin(coins);
	if (coins>0)
	{
		CCLOG("add coins %d", coins);
	}
    UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS,
            this->getCoins() + coins);
    if(this->getCoins() < 0 ) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS, 0);
    }
    return this->getCoins();
}


int User::getDiamonds() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_DIAMONDS, 0);
}

int User::addDiamonds(int diamonds) {
	LogEventConsume::getInstance()->addEventDiamond(diamonds);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS,
            this->getDiamonds() + diamonds);
    if(this->getDiamonds() < 0 ) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS, 0);
    }
    return this->getDiamonds();
}

int User::getMaxTurrentLevel() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_M_TURRENT, 1);
}

bool User::setMaxTurrentLevel(int maxTurrentLevel) {
    if(maxTurrentLevel > 0 && maxTurrentLevel > this->getMaxTurrentLevel()) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_M_TURRENT, maxTurrentLevel);
        return true;
    }
    return false;
    
}





bool User::addExp(int exp) {
    if(exp > 0) {
        int currentLevel = this->getLevelData().levelId;
        UserDefault::getInstance()->setIntegerForKey(User::KEY_EXP,
                UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) + exp);
        if(this->getLevelData().levelId > currentLevel) {
            return true;
        }
    }
    return false;
}

LevelData User::getLevelData() {
    return ConfigExp::getInstance()->getLevelData(
            UserDefault::getInstance()->getIntegerForKey(User::KEY_EXP, 0) );
}

int User::getVipLevel() {
    int chargeMoney = getChargeMoney();
    return ConfigVipLevel::getInstance()->getLevel(chargeMoney);
}

bool User::addChargeMoney(int money) {
    if(money > 0) {
        UserDefault::getInstance()->setIntegerForKey(User::KEY_CHARGE_MONEY, getChargeMoney() + money);
        return true;
    }
    return false;
}

int User::getChargeMoney() {
    return UserDefault::getInstance()->getIntegerForKey(User::KEY_CHARGE_MONEY, 0);
}



void User::resetInfo() {

    setUserID("guest");
	UserDefault::getInstance()->setStringForKey(User::KEY_USER_NAME, "guest");
    UserDefault::getInstance()->setIntegerForKey(User::KEY_COINS, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_DIAMONDS, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_EXP, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_M_TURRENT, 1);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_CHARGE_MONEY, 0);
	UserDefault::getInstance()->setIntegerForKey(User::KEY_LASTSIGNDAY, -1);
	UserDefault::getInstance()->setIntegerForKey(User::KEY_SEQSIGNDAY, 0);
    UserDefault::getInstance()->setIntegerForKey(User::KEY_CHEST_LEVEL, 0);
	UserDefault::getInstance()->setBoolForKey(User::KEY_ISHAVEFIRSTPAY, false);
	UserDefault::getInstance()->setBoolForKey(User::KEY_ISHAVESETNAME,false);
	NewbieMannger::getInstance()->resetInfo();

}
void User::syncInfo()
{
	auto sessionid =getSessionid();
	auto coin =getCoins();
	auto diomad =getDiamonds();
	auto exp =getExp();
	auto lv = getMaxTurrentLevel();
	auto mo = getChargeMoney()*100;
	auto count = getNobillityCount();
	HttpMannger::getInstance()->HttpToPostRequestSyncInfo(sessionid, coin, diomad, exp, lv, mo, count);
}

int User::getNobillityCount()
{
	return NobilityManager::getInstance()->RemainingNobilityday();
}