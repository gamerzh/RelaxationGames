#pragma once
#include "cocos2d.h"

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void addTouchListener();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event  *event) override;
private:
	//void addEdgeToGame();
	void addHeroToGame();
	void addBrickToGame();
    //bool onContactBegin(cocos2d::PhysicsContact& contact);
};