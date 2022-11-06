#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct NormalTurrent {
    int normal_turrent_id;
    int turrent_ui_id; // 显示ui
    int unlock_turrent_level;   // 解锁炮的等级
    double net_per; // 打击面积系数
    double catch_per; // 捕获概率系数
    int ui_type; // 1火焰;2冰冻
    int net_type;  // 1,1张网;2,2张;3,三张
};


class ConfigNormalTurrent {
    
public:
	ConfigNormalTurrent();
	static ConfigNormalTurrent* getInstance();
    
	bool LoadConfig();
    
    NormalTurrent getNormalTurrent(int maxTurrentLevel);
    
private:
	static ConfigNormalTurrent* _instance;
	
    std::map<int, NormalTurrent> normalTurrents;
};

