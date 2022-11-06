#pragma once
#include "cocos2d.h"
using namespace cocos2d;

struct RankListItem
{
	std::string name;
	int coin;
	int gender;//ÐÔ±ð 0 ÄÐ 1Å®
};

class RanklistManager {

public:
	static RanklistManager* getInstance();
	std::vector<RankListItem> getCoinRankListData();
private:
	RanklistManager();
	static RanklistManager*_instance;
	void init();
	std::vector<RankListItem > rankItemsByCoin;
    
};

