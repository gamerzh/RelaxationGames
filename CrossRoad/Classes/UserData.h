#pragma once
#include"cocos2d.h"
USING_NS_CC;

class Userdata {
public:
	static const Userdata* getInstance();

	int getPlayerGoldNum();
	void setPlayerGoldNum(int num);

private:
	static const Userdata* m_instance;
	Userdata() {}
};

