#pragma once
#include "cocos2d.h"

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	void addEdgeToGame();
	void addHeroToGame();
	void addBrickToGame();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};