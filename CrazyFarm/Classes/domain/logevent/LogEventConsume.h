#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class LogEventConsume {

public:
	static LogEventConsume* getInstance();
	void init();


	void sendDataToServer();
	void clearLocalData();
	void addEventCoin(int coin);
	void addEventDiamond(int diamond);
private:

	static LogEventConsume* _instance;
	std::string getDataForJson();
	LogEventConsume();
	

	const char* EventGetCoin = "EventGetCoin";
	const char* EventCostCoin = "EventCostCoin";
	const char* EventGetDiamond = "EventGetDiamond";
	const char* EventCostDiamond = "EventCostDiamond";
};


