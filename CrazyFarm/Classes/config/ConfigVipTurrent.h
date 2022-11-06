#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct VipTurrent {
    int vip_turrent_id;
    int turrent_ui_id; // 显示ui
    double net_per; // 打击面积系数
    double catch_per; // 捕获概率系数
    int ui_type; // 1火焰;2冰冻
    int net_type;  // 1,1张网;2,2张;3,三张
};


class ConfigVipTurrent {
    
public:
	ConfigVipTurrent();
	static ConfigVipTurrent* getInstance();
    
	bool LoadConfig();
    
	std::map<int, VipTurrent> getVipTurrents();
    VipTurrent getVipTurrent(int level);
	std::vector<VipTurrent> getUnUpgradeTurrents();
    
private:
	static ConfigVipTurrent* _instance;
	
    std::map<int, VipTurrent> vipTurrents;
};

