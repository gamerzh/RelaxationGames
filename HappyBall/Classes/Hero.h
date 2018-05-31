#pragma once
#include "cocos2d.h"

#define HERO_BALL_RADIUS 100
#define SPEED_Y 5

class Hero : public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(Hero);
	void flipSpeedY();
private:
	float speed_y = 0;
	void addPhysicsHero();
	void update(float dt);
};  