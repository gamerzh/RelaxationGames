#pragma once
#include "cocos2d.h"
using namespace cocos2d;



class LogEventTurnTable {

public:
	static LogEventTurnTable* getInstance();
	void sendDataToServer(int tType, int pType);  ///tType:��������  pType�����

private:
	LogEventTurnTable();
	std::string getDataForJson(int tType, int pType);
	static LogEventTurnTable* _instance;
};


