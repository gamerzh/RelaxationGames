#pragma once
#include "cocos2d.h"
#include "fish/FishArrange.h"
using namespace cocos2d;


class FishArrangeThree :public FishArrange{
public:
	CREATE_FUNC(FishArrangeThree);
	virtual void initFishAnim(int fishID);
};
