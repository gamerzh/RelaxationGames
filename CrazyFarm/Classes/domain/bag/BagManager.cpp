#include "domain/bag/BagManager.h"
#include "config/ConfigItem.h"

BagManager* BagManager::_instance = NULL;

BagManager::BagManager(){
    this->init();
}

void BagManager::init(){
    // TODO
	auto k = getBagListWithSort();
}

BagManager* BagManager::getInstance(){
    if(_instance == NULL){
        _instance = new BagManager();
    }
    return _instance;
}

bool BagManager::changeItemCount(int itemId, int num) {
	if (itemId == 1012)
	{
		return true;
	}
    int currentCount = getItemNum(itemId);
    auto key = String::createWithFormat("%s%d", BagManager::KEY_ITEMID_HEAD, itemId);
    UserDefault::getInstance()->setIntegerForKey(key->getCString(), currentCount+num);
	getBagListWithSort();
    if(getItemNum(itemId) < 0) {
        UserDefault::getInstance()->setIntegerForKey(key->getCString(), 0);
    }
    if( currentCount == getItemNum(itemId) ) {
        return false;
    }
    return true;
    
}

int BagManager::getItemNum(int itemId) {
    auto key = String::createWithFormat("%s%d", BagManager::KEY_ITEMID_HEAD, itemId);
	return UserDefault::getInstance()->getIntegerForKey(key->getCString(), 0);
}

std::vector<BagItem> BagManager::getBagList() 
{
	std::vector<BagItem> items;
	auto itemList = ConfigItem::getInstance()->getItemList();
	for (auto var:itemList)
	{
		BagItem item;
		item.itemId = var.second.itemId;
		item.num = getItemNum(var.second.itemId);
		items.push_back(item);
	}
    return items;
}

std::vector<BagItem> BagManager::getBagListWithSort()
{
	itemsWithSort.clear();
	itemsWithSort.push_back(BagItem(1012, getItemNum(1012),getItemType(1012)));
	for (int i = 1003; i <= 1011;i++)
	{
		auto num = getItemNum(i);
		auto type = getItemType(i);
		if (type == Prop_ItemBox&&num == 0)
		{		
			continue;
		}
		itemsWithSort.push_back(BagItem(i,num,type));
	}
	return itemsWithSort;
}

PropType BagManager::getItemType(int itemId)
{
	switch (itemId)
	{
	case 1001:
	case 1002:
		return Prop_Currency;
	case 1003:
	case 1004:
	case 1005:
	case 1006:
	case 1007:
		return Prop_Skill;
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		return Prop_ItemBox;
	case 1012:
		return Prop_upgradeBox;
	default:
		return InvalidType;
	}
}
BagItem BagManager::getBagByIndex(int index)
{ 
	if (index<itemsWithSort.size())
	{
		return itemsWithSort.at(index); 
	}
	else
	{
		return  BagItem(-1, -1, InvalidType);
	}
}


BagItem BagManager::getBagByItemId(int itemid)
{
	for (auto var:itemsWithSort)
	{
		if (var.itemId == itemid)
		{
			return var;
		}
	}
}

void BagManager::addreward(int itemId, int num)
{
	if (itemId==1001)
	{
		User::getInstance()->addCoins(num);
	}
	else if (itemId==1002)
	{
		User::getInstance()->addDiamonds(num);
	}
	else
	{
		changeItemCount(itemId, num);
	}
}