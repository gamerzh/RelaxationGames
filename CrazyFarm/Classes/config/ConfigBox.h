#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct BoxConfigInfo {
    int item_id; // 对应道具编号
	float catch_fish_per; //提升捕鱼概率
	int money;  //获得金币
};


class ConfigBox {
    
public:
	ConfigBox();
	static ConfigBox* getInstance();
    
	bool LoadConfig();
    
	BoxConfigInfo getBoxConfigInfoByItemId(int itemId);
private:
	static ConfigBox* _instance;
	
	std::vector<BoxConfigInfo> m_BoxConfigInfos;
};

