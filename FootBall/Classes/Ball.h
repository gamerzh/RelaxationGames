#pragma once
#include "cocos2d.h"

class Ball : public cocos2d::Sprite
{
public:
	static Ball* create(cocos2d::Camera* camera);
	virtual bool init(cocos2d::Camera* camera);
private:
	cocos2d::Camera* myCamera = nullptr;
	void update(float dt);
};