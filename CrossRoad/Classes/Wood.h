#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Wood : public Sprite
{

public:
	static Wood* create(int type ,int direction, float time);
	virtual bool init(int type, int direction, float time);
	float getSpeedX();
private:
	int woodType;
	int woodDir;
	float woodTime = 0;
	float woodSpeed = 0;
	void update(float dt);
	std::string getFileNameByType(int type);
};