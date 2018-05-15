#include "UserData.h"

//�ⲿ��ʼ�� before invoke main
UserData* UserData::m_instance = new UserData();

UserData* UserData::getInstance()
{
	return m_instance;
}

int UserData::getPlayerGoldNum() {
	return UserDefault::getInstance()->getIntegerForKey("user_gold", 0);
}

void UserData::setPlayerGoldNum(int num) {
	UserDefault::getInstance()->setIntegerForKey("user_gold", num);
}