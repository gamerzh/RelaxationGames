#include "domain/bonuspool/BonusPoolManager.h"


BonusPoolManager* BonusPoolManager::_instance = NULL;

BonusPoolManager::BonusPoolManager(){
    this->init();
}


void BonusPoolManager::init(){
}

BonusPoolManager* BonusPoolManager::getInstance(){
    if(_instance == NULL){
        _instance = new BonusPoolManager();
    }
    return _instance;
}

int BonusPoolManager::getAllowCatchFishCounts(){
    return ConfigBonuspool::getInstance()->getBonuspool().allow_draw_fish_counts;
}

int BonusPoolManager::getCoins() {
    return UserDefault::getInstance()->getIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, 0);
}

int BonusPoolManager::getFishCounts() {
    return UserDefault::getInstance()->getIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_FISHCOUNTS, 0);
}

bool BonusPoolManager::addCoins(int coins) {
    if(coins > 0) {
        UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, getCoins() + coins);
        UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_FISHCOUNTS, getFishCounts() + 1);
        return true;
    }
    return false;

}

bool BonusPoolManager::cleanCoinsAndFishCounts() {
    UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_COINS, 0);
	UserDefault::getInstance()->setIntegerForKey(BonusPoolManager::KEY_BONUSPOOL_FISHCOUNTS, 0);
    return true;
}

bool BonusPoolManager::allowBonusPool() {
    if( getFishCounts() >= getAllowCatchFishCounts() ) {
        return true;
    }else {
        return false;
    }
}

BonuspoolResult BonusPoolManager::getBonuspoolResult() {
    BonuspoolResult bonuspoolResult; 
	int coins = getCoins();
    if(allowBonusPool()) {
      
        Bonuspool bonuspool = ConfigBonuspool::getInstance()->getBonuspool();
        for(int i=0; i < bonuspool.bonuspoolItems.size(); i++) {
            if( ( coins >= bonuspool.bonuspoolItems.at(i).start_coins ) &&
                    ( coins < bonuspool.bonuspoolItems.at(i).end_coins ) ) {
				bonuspoolResult.bouns_position = i;
                bonuspoolResult.reward_list = bonuspool.bonuspoolItems.at(i).reward_list;
				if (UserDefault::getInstance()->getBoolForKey(KEY_BONUSPOOL_FIRST,true))
				{
					UserDefault::getInstance()->setBoolForKey(KEY_BONUSPOOL_FIRST, false);
					bonuspoolResult.reward_position = 0;
					return bonuspoolResult;
				}
				else
				{
					int random = rand() % 100 + 1;
					int count = 0;
					for (int j = 0; j < bonuspoolResult.reward_list.size(); j++) {

						count += bonuspoolResult.reward_list.at(j).per;

						if (count >= random) {
							bonuspoolResult.reward_position = j;
							return bonuspoolResult;
						}
				}
			
				}
            }
        }
    }
	else
	{
		Bonuspool bonuspool = ConfigBonuspool::getInstance()->getBonuspool();
		for (int i = 0; i < bonuspool.bonuspoolItems.size(); i++) {
			if (coins >= bonuspool.bonuspoolItems.at(i).start_coins&&coins <= bonuspool.bonuspoolItems.at(i).end_coins)
			{
				bonuspoolResult.reward_list = bonuspool.bonuspoolItems.at(i).reward_list; 
				bonuspoolResult.reward_position = 0;
				return bonuspoolResult;
			}
		}
	}
   
}

///TODO::È±ÉÙ±£»¤
BonuspoolItem*  BonusPoolManager::getNextBonuspool() {
	int coins = getCoins();
	Bonuspool bonuspool = ConfigBonuspool::getInstance()->getBonuspool();
	for (int i = 0; i < bonuspool.bonuspoolItems.size(); i++) {
		if ((coins >= bonuspool.bonuspoolItems.at(i).start_coins) &&
			(coins < bonuspool.bonuspoolItems.at(i).end_coins)) {

			if (i+1>=bonuspool.bonuspoolItems.size())
			{
				return nullptr;
			}
			else
			{
				BonuspoolItem* item = new BonuspoolItem();
				item->start_coins = bonuspool.bonuspoolItems.at(i + 1).start_coins;
				item->end_coins = bonuspool.bonuspoolItems.at(i + 1).end_coins;
				item->reward_list = bonuspool.bonuspoolItems.at(i + 1).reward_list;
				return item;
			}

		}
	}
}

