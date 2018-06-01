#pragma once
#include "cocos2d.h"
#include "Brick.h"
#include "Hero.h"

#define BRICK_HEIGHT  320
#define BRICK_ANIM_NUM 40
#define BRICK_START_ZORDER  5000

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
	std::vector<Brick*> brickVector;//×©¿é +- 
	cocos2d::Vec2 preTouchPosition;
	Hero* hero = nullptr;
	void addHeroToGame();
	void createBrick();
	void recycleBrick();
	void update(float dt);
};