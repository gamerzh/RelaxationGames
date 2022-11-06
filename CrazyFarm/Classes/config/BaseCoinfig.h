#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
USING_NS_CC;
class BaseCoinfig
{
public:
	static BaseCoinfig* getInstance();
	bool loadConfigFromServe();
private:
	BaseCoinfig();
	static BaseCoinfig* _instance;

};

