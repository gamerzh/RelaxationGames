#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct Reward {
    int itemId;
    int num;
};

struct Turrent {
    int turrentId;
    int unlockType;
    int unlockPrice;
    int multiple;
    std::vector<Reward> rewardList;

};


class ConfigTurrent {
    
public:
	ConfigTurrent();
	static ConfigTurrent* getInstance();
    
	bool LoadConfig();
    
	std::vector<Turrent>getTurrent();
    Turrent getTurrent(int turrentId);

	Turrent getNextTurrent(int turrentId);
	Turrent getLastTurrent(int turrentId);
	Turrent getMaxNextTurrent();



	Turrent getTurrentByIndex(int index);

	int     getIndexByMaxlv(int maxlv);
	std::vector<int> getCurrentShowTurrentIndexs();
private:
	static ConfigTurrent* _instance;
	
    std::vector<Turrent> turrents;
};

