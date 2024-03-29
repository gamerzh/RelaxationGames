//
//  Footballer.hpp
//  球员基类,守门员和场地球员都是其子类
//

#ifndef Footballer_h
#define Footballer_h

#include "TeamInfoFactory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class Footballer : public cocos2d::Node{
public:
    virtual bool init();
    CREATE_FUNC(Footballer);
    virtual int getFootManTeamId(){return 0;};
    virtual void doTumble(){};
    virtual cocos2d::Vec2 getFootballVec2(){return nullptr;};
};
#endif /* Footballer_h */
