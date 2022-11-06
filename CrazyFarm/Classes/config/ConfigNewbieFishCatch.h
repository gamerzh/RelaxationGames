#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
using namespace cocos2d;

struct NewbieFishCatch
{
	int fishid;
	float per;
};


class ConfigNewbieFishCatch{
public:
	static ConfigNewbieFishCatch* getInstance();

    bool LoadConfig();

	float getperByLevelAndFishID(int level, int fishid);
private:
	ConfigNewbieFishCatch();
	static ConfigNewbieFishCatch* _instance;
	std::map<int,std::vector<NewbieFishCatch>> levelToNewbieFishCatchs;
};


