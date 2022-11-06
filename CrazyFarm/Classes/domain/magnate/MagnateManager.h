#pragma once

#include "cocos2d.h"
#include "config/ConfigMagnate.h"

using namespace cocos2d;


struct MagnateEvent {
    int fireTimes;
    int itemId;
    int num;
    
};

class MagnateManager {

public:
    static MagnateManager* getInstance();
    
    MagnateEvent getDiamandMagnateEvent(); // 获取钻石赠送事件
    MagnateEvent getItemMagnateEvent(); // 获取道具赠送事件[冰冻、锁定和召唤中三选一]
    
private:
    MagnateManager();
    void init();
    static MagnateManager* _instance;
    
    MagnateItem diamandConfig;
    MagnateItem itemConfig;
    
};

