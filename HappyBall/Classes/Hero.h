#pragma once
#include "cocos2d.h"

#define HERO_BALL_RADIUS 100

class Hero : public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(Hero);
private:
	void addPhysicsHero();
};  