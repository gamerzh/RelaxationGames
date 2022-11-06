#include "RanklistManager.h"
#include "NameMannger.h"
#include "Room.h"
#include "User.h"
RanklistManager* RanklistManager::_instance = NULL;

RanklistManager::RanklistManager(){
	init();
}
RanklistManager* RanklistManager::getInstance(){
    if(_instance == NULL){
		_instance = new RanklistManager();
    }
    return _instance;
}
void RanklistManager::init()
{
	for (unsigned int i = 0; i < 10;i++)
	{
		RankListItem item;
		item.name = NameMannger::getName();
		item.gender = rand() % 2;
		item.coin = 58000000 + rand() % (58000000 - 45000000) * 100;
		rankItemsByCoin.push_back(item);
	}
	RankListItem item;
	item.name = User::getInstance()->getMyName();
	item.gender = rand() % 2;
	item.coin = User::getInstance()->getMyCoins();
	rankItemsByCoin.push_back(item);
	std::sort(rankItemsByCoin.begin(), rankItemsByCoin.end(), [](const RankListItem  m1, const RankListItem  m2){return m1.coin > m2.coin; });
	rankItemsByCoin.pop_back();

}

std::vector<RankListItem> RanklistManager::getCoinRankListData()
{
	return rankItemsByCoin;
}