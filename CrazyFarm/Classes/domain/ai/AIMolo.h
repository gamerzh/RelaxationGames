#ifndef _AIMOLO_H_
#define _AIMOLO_H_
#include "cocos2d.h"
#include "PlayerWork.h"
#include "domain/ai/AI.h"
#include "fish/FishManage.h"

using namespace cocos2d;

class AIMolo : public AI {

public:
    virtual PlayerWork nextStep(int currentCoins, Point currentPostion);
    
    
private:
    float angle = 0;
    bool lastFire = false;
    int count = 0;
    int nextCountReset = 60;
    int baseFireLevel = 40;
    int fireLevel =40 /*baseFireLevel*/;
};

#endif
