#pragma once
#include "cocos2d.h"
#include "utill/define.h"
using namespace cocos2d;

class LoginMannger{
public:
	static LoginMannger* getInstance();
	void login();
private:
	LoginMannger();
	static LoginMannger* _instance;
};

