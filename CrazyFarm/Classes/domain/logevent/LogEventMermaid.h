#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class LogEventMermaid {

public:
	static LogEventMermaid* getInstance();
	void init();
	void addDataToSend(int roomid, int result, int reward);//����id����ʱ��ʧ��Ϊ0��������
private:
	LogEventMermaid();
	std::string getDataForJson();
	void sendDataToServer();
	int m_roomid;
	int m_result;
	int m_reward;
	static LogEventMermaid* _instance;
};


