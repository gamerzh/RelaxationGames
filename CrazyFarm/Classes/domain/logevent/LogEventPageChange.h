#pragma once
#include "cocos2d.h"
using namespace cocos2d;

struct EventPageChange
{
	int from_page;
	int to_page;
	int channel;
	int num;
};


class LogEventPageChange {

public:
	static LogEventPageChange* getInstance();
	void init();

	void addEventItems(int from_page, int to_page, int channel);
	void sendDataToServer();
	void clearLocalData();
private:

	void sendLocaLData();
	void sendMemoryData();

	void loadLocalData();
	LogEventPageChange();
	std::string getDataForJson();
	std::vector<EventPageChange> items;
	static LogEventPageChange* _instance;
	const char* EventPageChangeNum = "EventPageChangeNum";
};


