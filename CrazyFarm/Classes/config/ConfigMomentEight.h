#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

USING_NS_CC;


struct MomentEightItemFishs {
	std::vector<int> fish_ids;
	float  fish_wait_time_start;
	float  fish_wait_time_end;
	int fish_startcount;
	int fish_endcount;
	float wait_time; //真正的等待时间
	std::vector<int> fishRoutes;
};


struct MomentEightItem {
	float fTempTime; ///////////////随机产生时间 根据start和end产生
    double interval_time_start;
	double interval_time_end;	
	std::vector<MomentEightItemFishs> momentEightItemFishs;
};


class ConfigMomentEight {
    
public:
	ConfigMomentEight();
	static ConfigMomentEight* getInstance();
    
	bool LoadConfig();
	std::map<int, std::vector<MomentEightItem>> getMomentEightItemTypes();
	std::vector<MomentEightItem> getMomentEightItemBytype(int type){ return momentEightItemTypes[type];};
	float getLifeTime(int type){ return lifeTimeForType[type]; };
    
private:
	static ConfigMomentEight* _instance;


	std::map<int, float> lifeTimeForType;
	std::map<int, std::vector<MomentEightItem>> momentEightItemTypes;
	bool LoadConfigByType(int type);

};

