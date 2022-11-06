#pragma once
#include "cocos2d.h"
#include "fish/FishArrange.h"
using namespace cocos2d;


class FishArrangeFourh :public FishArrange{
public:
	CREATE_FUNC(FishArrangeFourh);
	virtual void initFishAnim(int fishID);
};
