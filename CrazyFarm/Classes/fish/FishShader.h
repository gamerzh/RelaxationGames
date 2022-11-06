#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;
class Fish;
class FishShader :public Sprite{
public:
	virtual bool init(Fish*fish);
	static FishShader* createShader(Fish*fish);
	void onDead();
protected:	
	void update(float);
	//“ı”∞
	Fish* target;

	
};

