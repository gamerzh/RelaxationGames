#pragma once
#include "cocos2d.h"
#include "fish/Fish.h"
using namespace cocos2d;


class FishOfAllKilled :public Fish{
public:
	virtual void initFish(int fishID);
	CREATE_FUNC(FishOfAllKilled);
	virtual void addShader(){};

};
