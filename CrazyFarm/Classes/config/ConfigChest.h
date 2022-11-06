#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;



struct Chest {
    int chest_level;
    std::string chest_name;
    int item_id;
    bool allow_presented;
    double catch_per;        
    int have_get_reward;
};


class ConfigChest {
    
public:
	ConfigChest();
	static ConfigChest* getInstance();
    
	bool LoadConfig();
    
    Chest getChestByItemId(int itemId);
    Chest getChestByLevel(int chestLevel);
    
private:
	static ConfigChest* _instance;
	
    std::map<int, Chest> chests;
};

