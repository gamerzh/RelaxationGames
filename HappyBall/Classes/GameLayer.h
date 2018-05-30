#pragma once
#include "cocos2d.h"
#include "Brick.h"

#define BRICK_START_ZORDER  10000
#define BRICK_HEIGHT  320
#define BRICK_ANIM_NUM 41

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void addTouchListener();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event  *event) override;
private:
	cocos2d::Size win = cocos2d::Director::getInstance()->getVisibleSize();
	std::vector<Brick*> brickVector;//×©¿é
	cocos2d::Vec2 preTouchPosition;
	void addHeroToGame();
	void createBrick();
	void recycleBrick();
};