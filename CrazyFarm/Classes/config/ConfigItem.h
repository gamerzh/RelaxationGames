#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct Item {
    int itemId;
    std::string itemName;
    std::string itemDesc;
    int buyType;    // 0,不支持购买;1,金币;2,钻石;
    int buyPrice;
};


class ConfigItem {
    
public:
	ConfigItem();
	static ConfigItem* getInstance();
    
	bool LoadConfig();
    
	Item getItemById(int itemId);
	std::map<int, Item> getItemList(){ return items; };
private:
	static ConfigItem* _instance;
	
    std::map<int, Item> items;
};

