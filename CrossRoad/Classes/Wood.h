#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Wood : public Sprite
{

public:
	static Wood* create(Camera* ca, int type ,int direction, float time);
	virtual bool init(Camera* ca, int type, int direction, float time);
	float getSpeedX();
private:
	Size win = Director::getInstance()->getWinSize();
	Camera* myCamera = nullptr;
	int woodType;
	int woodDir;
	float woodTime = 0;
	float woodSpeed = 0;
	void initSpeed();
	void update(float dt);
	std::string getFileNameByType(int type);
};