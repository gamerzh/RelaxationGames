#pragma once
#include "cocos2d.h"
using namespace cocos2d;



class LogEventTurrentUpgrade {

public:
	static LogEventTurrentUpgrade* getInstance();
	void init();


	void sendDataToServer(int turrent_level,float updata_times);
private:
	LogEventTurrentUpgrade();
	std::string getDataForJson(int turrent_level, float updata_times);
	static LogEventTurrentUpgrade* _instance;
};


