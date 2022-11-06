#ifndef _MOMENTMANAGER_H_
#define _MOMENTMANAGER_H_
#include "cocos2d.h"



#include "moment/Moment.h"
#include "moment/momentFishGroup/MomentTwo.h"
#include "moment/momentFishGroup/MomentThree.h"
#include "moment/momentFishGroup/MomentFour.h"

using namespace cocos2d;

class MomentManager {

public:
    static MomentManager* getInstance();
    
	Moment* getNewMoment(float FFOneTime);//是否快进某个时间

	Moment* getNewMomentByType(int momentType, float FFOneTime);
private:
    MomentManager();
    void init();
    static MomentManager* _instance;
	Moment* getNewMomentEight(float FFOneTime);
    
	Moment*getNewMomentGroupfish(float FFOneTime);

	std::vector<int> momentEightVec;
	std::vector<int> momentFishGroupVec;

	int getCurrentMomentEight();
	int getCurrentMomentFishGroup();

    int currentPos = 0;
    
	

	int nowMomentType  = -1;
    
};

#endif
