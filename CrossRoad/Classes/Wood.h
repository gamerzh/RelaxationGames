#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Wood : public Sprite
{

public:
	static Wood* create(int type);
	virtual bool init();
	float getSpeedX();
private:
	void update(float dt);
};