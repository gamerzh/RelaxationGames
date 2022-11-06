/**
 * 奖金池管理
 */

#pragma once

#include "config/ConfigBonuspool.h"

using namespace cocos2d;

struct BonuspoolResult {
	int bouns_position;
    int reward_position;
    std::vector<BonuspoolRewardItem> reward_list;
};


class BonusPoolManager {

public:
    static BonusPoolManager* getInstance();
    
    bool allowBonusPool();              // 是否允许抽奖
    int getAllowCatchFishCounts();       // 允许抽奖的捕获鱼数量
    
    int getCoins();                 // 获取奖金池的数目
    bool addCoins(int coins);       // 增加奖金池的数目
    int getFishCounts();            // 获取捕获奖金鱼的数量
    
    bool cleanCoinsAndFishCounts();              // 清空奖金池的数目
    
    BonuspoolResult getBonuspoolResult();       // 获取奖励区间和奖励结果
	BonuspoolItem*  getNextBonuspool();       // 获取下一级奖金池
	
	int getFishNeedCatchToChoujiang(){ return getAllowCatchFishCounts() - getFishCounts(); };
    
    
private:
    BonusPoolManager();
    void init();
    static BonusPoolManager* _instance;
    
    const char* KEY_BONUSPOOL_COINS = "KEY_BONUSPOOL_COINS";
    const char* KEY_BONUSPOOL_FISHCOUNTS = "KEY_BONUSPOOL_FISHCOUNTS";

	const char* KEY_BONUSPOOL_FIRST = "KEY_BONUSPOOL_FIRST";
};

