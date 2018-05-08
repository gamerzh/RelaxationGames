#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Wood : public Sprite
{

public:
	static Wood* create(int type ,int direction, float speed);
	virtual bool init(int type, int direction, float speed);
	float getSpeedX();
private:
	int woodType;
	int woodDir;
	float woodSpeed;
	void update(float dt);
	std::string getFileNameByType(int type);
};