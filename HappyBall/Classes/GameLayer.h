#pragma once
#include "cocos2d.h"
#include "Brick.h"

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void addTouchListener();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event  *event) override;
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event  *event) override;
private:
	std::vector<Brick> brickVector;//×©¿é
	void addHeroToGame();
	void createBrick();
	void recycleBrick();
};