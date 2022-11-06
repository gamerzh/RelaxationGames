#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct BonuspoolRewardItem {
    int item_id;
    int num;
    float per;
};

struct BonuspoolItem {
    int start_coins;
    int end_coins;
    std::vector<BonuspoolRewardItem> reward_list;
};

struct Bonuspool {
    int allow_draw_fish_counts;
	int fistRewardItemid;
    std::vector<BonuspoolItem> bonuspoolItems;
};







class ConfigBonuspool {
    
public:
	ConfigBonuspool();
	static ConfigBonuspool* getInstance();
    
	bool LoadConfig();
    Bonuspool getBonuspool();
    
private:
	static ConfigBonuspool* _instance;
    
    Bonuspool bonuspool;
};

