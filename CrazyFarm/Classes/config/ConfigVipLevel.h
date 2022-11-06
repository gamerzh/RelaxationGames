#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;

struct VipLevel {
    int vip_level;
    int charge_money;
    std::string title;      // VIP名称
    std::string desc_title; // 显示标题
    std::string desc_content;// 显示描述
    int vip_turrent_id;   // VIP炮ID
    double double_login_reward;  // 登陆奖励翻倍系数
    double pay_reward;           // 充值奖励百分比
    double kill_per_add;           // 击杀概率系数
    int send_coins_over;         // 金币补足金额
    int send_coins_over_day_time;  // 每日金币补足次数
};


class ConfigVipLevel {
    
public:
	ConfigVipLevel();
	static ConfigVipLevel* getInstance();
    
	bool LoadConfig();
    
	std::map<int, VipLevel> getVipLevels();
    VipLevel getVipLevel(int level);
    
    int getLevel(int chargeMoney);
    
private:
	static ConfigVipLevel* _instance;
	
    std::map<int, VipLevel> vipLevels;
};

