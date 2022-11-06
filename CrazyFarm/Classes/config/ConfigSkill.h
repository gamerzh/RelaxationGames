#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct SkillConfigInfo {
    int skill_id;
    int item_id; // 对应道具编号
    int unlock_buy_turretLv; 
    int unlock_buy_vipLv;  
    int cd_time;        // 技能持续时间。0表示不需要等待。
	const char* m_name;
};


class ConfigSkill {
    
public:
	ConfigSkill();
	static ConfigSkill* getInstance();
    
	bool LoadConfig();
    
    SkillConfigInfo getskillConfigInfoByItemId(int itemId);
    SkillConfigInfo getskillConfigInfoBySkillId(int skillId);
private:
	static ConfigSkill* _instance;
	
    std::map<int, SkillConfigInfo> skillConfigInfos;
};

