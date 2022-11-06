#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct MagnateItem {
    int type;
    int fire_time_from;
    int fire_time_to;
};


class ConfigMagnate {
    
public:
	ConfigMagnate();
	static ConfigMagnate* getInstance();
    
	bool LoadConfig();
    
    MagnateItem getDiamandMagnate();
    MagnateItem getItemMagnate();
    
private:
	static ConfigMagnate* _instance;
	
    std::map<int, MagnateItem> magnateItems;
};

