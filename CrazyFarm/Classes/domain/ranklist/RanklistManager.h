#pragma once

#include "cocos2d.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;

struct rankListItem
{
	std::string name;
	int vipLevel;
	long int exp;
	long int coin;
	int gender;//ÐÔ±ð 0 ÄÐ 1Å®
};

struct  rankRange
{
	long int value_start;
	long int value_end;
	long int rank_start;
	long int rank_end;
};

struct RanklistValue 
{
	std::vector<rankListItem > _rankItems;
	std::vector<rankRange> _rankRange;
	int _errorcode;
	std::string _errormsg;
};


class RanklistManager {

public:
	static RanklistManager* getInstance();
	void loadCoin();
	void loadExp();
	void onHttpRequestCompletedForCoin(HttpClient *sender, HttpResponse *response);
	void onHttpRequestCompletedForExp(HttpClient *sender, HttpResponse *response);

	int getRankByCoin(int coin);
	int getRankByExp(int exp);
	int getRankByCoinForMyself(int coin);
private:
	RanklistManager();
	static RanklistManager*_instance;
	CC_SYNTHESIZE(std::vector<rankListItem >, rankItemsByCoin, CoinRankListData);
	CC_SYNTHESIZE(std::vector<rankListItem >, rankItemsByExp, ExpRankListData);
	CC_SYNTHESIZE(std::vector<rankRange >, _rankCoinRange,RankCoinRange);
	CC_SYNTHESIZE(std::vector<rankRange >, _rankExpRange, RankExpRange);
    
};

