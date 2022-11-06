#pragma once
#include "cocos2d.h"
using namespace cocos2d;

struct EventSkillCell
{
	int skillID;
	int type;
	int prices;
	int nums;
};


class LogEventUseSkill {

public:
	static LogEventUseSkill* getInstance();
	void init();

	void addUseSkillData(int skillID, int type, int prices);  ///type 0 :直接使用  1扣钻石使用 2触发计费
	void sendDataToServer();
	void clearLocalData();
private:
	void loadLocalData();
	LogEventUseSkill();
	std::string getDataForJson();
	std::vector<EventSkillCell> items;
	static LogEventUseSkill* _instance;
	const char* EventUseSkill = "EventUseSkill";
};


