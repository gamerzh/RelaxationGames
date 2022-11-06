#include "User.h"
#define  USERDEFAULT UserDefault::getInstance()
User* User::instance = nullptr;

User::User()
{
	
}
void User::addCoin(int difCoin)
{
	int coin = getMyCoins() + difCoin;
	coin = coin > 0 ? coin : 0;
	setMyCoins(coin);
}

bool User::isAvailableRole(int index)
{
	bool defultValue = index == 1 ? true : false;
	auto key = String::createWithFormat("%s_%d", USER_ROLE, index);
	return USERDEFAULT->getBoolForKey(key->getCString(), defultValue);
}
void User::setAvailableRole(int index)
{
	auto key = String::createWithFormat("%s_%d", USER_ROLE, index);
	return USERDEFAULT->setBoolForKey(key->getCString(), true);
}