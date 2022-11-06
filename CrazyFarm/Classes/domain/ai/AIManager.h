#ifndef _AIMANAGER_H_
#define _AIMANAGER_H_
#include "cocos2d.h"
#include "AI.h"
#include "domain/ai/AIMolo.h"
#include "domain/ai/AIHu.h"

using namespace cocos2d;

class AIManager {

public:
    static AIManager* getInstance();
    
    AI* getAI(int maxTurrentLevel);
    
    bool allowAiFire();
    void setAiFire(bool allow);
    

	void addCreateGoldFish();
	void  MainUpdata(float dt);
private:
    AIManager();
    void init();
    static AIManager* _instance;
    
    bool aiFire = true;

	

	///AIÊý¾Ý
	CC_SYNTHESIZE(int, nNowCreateGoldFish, NowCreateGoldFish);

};

#endif
