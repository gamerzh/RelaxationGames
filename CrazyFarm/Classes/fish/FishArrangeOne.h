#pragma once
#include "cocos2d.h"
#include "fish/FishArrange.h"
using namespace cocos2d;


class FishArrangeOne :public FishArrange{
public:
	CREATE_FUNC(FishArrangeOne);
	virtual void initFishAnim(int fishID);

};
