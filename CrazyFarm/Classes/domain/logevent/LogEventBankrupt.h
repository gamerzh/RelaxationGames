#pragma once
#include "cocos2d.h"
using namespace cocos2d;




class LogEventBankrupt {

public:
	static LogEventBankrupt* getInstance();
	void init();


	void sendDataToServer(int roomid,int type,int num);
private:
	LogEventBankrupt();
	std::string getDataForJson();
	int m_roomid;
	int m_type;
	int m_num;
	static LogEventBankrupt* _instance;
};


