#pragma once
#include "cocos2d.h"
using namespace cocos2d;

struct SpcEvent 
{
	int event_id;
	int event_desc;
	int nums;
};

class LogEventSpcEvent {

public:
	static LogEventSpcEvent* getInstance();
	void init();

	void addEventItems(int event_id, int event_desc);
	void sendDataToServer();
	void clearLocalData();
private:
	std::vector<SpcEvent> datas;
	LogEventSpcEvent();
	void loadLocalData();
	std::string getDataForJson();
	static LogEventSpcEvent* _instance;
	const char* EventSpcEventNum = "EventSpcEventNum";
};


