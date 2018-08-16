#pragma once
#include "cocos2d.h"
#include "Hero.h"

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
    Hero* superHero;//脚男
    cocos2d::Rect leftRect;
    cocos2d::Rect rightRect;
    cocos2d::Rect slideRect;
    cocos2d::Rect shootRect;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void loadControlPad();

};
