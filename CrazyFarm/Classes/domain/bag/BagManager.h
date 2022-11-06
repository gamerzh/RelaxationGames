#ifndef _BAGMANAGER_H_
#define _BAGMANAGER_H_
#include "cocos2d.h"
#include "domain/bag/BagItem.h"
#include "domain/user/User.h"
using namespace cocos2d;


class BagManager {
public :
	static BagManager* getInstance();

    const char* KEY_ITEMID_HEAD = "KEY_ITEMID_HEAD_";
    
    bool changeItemCount(int itemId, int num);
    int getItemNum(int itemId);

	void addreward(int itemId, int num);
	
	
    std::vector<BagItem> getBagList();

	
	BagItem getBagByIndex(int index);
	BagItem getBagByItemId(int itemID);
private :
	BagManager();
	void init();
	PropType getItemType(int itemId);
	std::vector<BagItem> getBagListWithSort();
	std::vector<BagItem> itemsWithSort;
	static BagManager* _instance;

};

#endif
