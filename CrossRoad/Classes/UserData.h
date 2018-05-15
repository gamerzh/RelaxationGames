#pragma once
#include"cocos2d.h"
USING_NS_CC;

class UserData {
public:
	static  UserData* getInstance();

	int getPlayerGoldNum();
	void setPlayerGoldNum(int num);

private:
	static  UserData* m_instance;
	UserData() {}
};

