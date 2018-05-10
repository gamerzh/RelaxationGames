#include "UserData.h"

//外部初始化 before invoke main
const Userdata* Userdata::m_instance = new Userdata();

const Userdata* Userdata::getInstance()
{
	return m_instance;
}

int Userdata::getPlayerGoldNum() {
	return UserDefault::getInstance()->getIntegerForKey("user_gold", 0);
}

void Userdata::setPlayerGoldNum(int num) {
	UserDefault::getInstance()->setIntegerForKey("user_gold", num);
}