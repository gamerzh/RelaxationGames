#pragma once
#include "cocos2d.h"
#include "fish/FishArrange.h"
using namespace cocos2d;






class FishArrangeTwo :public FishArrange{
public:
	CREATE_FUNC(FishArrangeTwo);
	virtual void initFishAnim(int fishID);
};
