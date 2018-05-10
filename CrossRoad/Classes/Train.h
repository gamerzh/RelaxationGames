#pragma once
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Train : public Sprite
{
public:
	static Train* create(int dir,Point pos);
	virtual bool init(int dir, Point pos);
private:
	void update(float dt);
	float speed = 30;
};