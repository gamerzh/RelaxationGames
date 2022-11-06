#ifndef _NOBILITYMANAGER_H_
#define _NOBILITYMANAGER_H_
#include "cocos2d.h"

using namespace cocos2d;

struct NobilityRewadItem  {
    int item_id;
    int num;
};

class NobilityManager {

public:
    static NobilityManager* getInstance();
    
    
    bool isNobility();// 是否为贵族
	int  RemainingNobilityday();
    std::vector<NobilityRewadItem> getNobilityRewadItems(); // TODO : 获取单日奖励列表
	void addStepsDay(int dayNum);                        // 添加贵族天数
    bool isGetRewardToday();                       
	void setGetRewardToday();
	const char* KEY_STARTDAY = "KEY_STARTDAY";
	const char* KEY_STEPS = "KEY_STEPS";
	const char* KEY_ISGETGIFTINTODAY = "KEY_ISGETGIFTINTODAY";
private:
    NobilityManager();
    void init();
    static NobilityManager* _instance;
    std::vector<NobilityRewadItem> nobilityRewadItems;
    
    std::string startDay;
    int steps;
};

#endif
