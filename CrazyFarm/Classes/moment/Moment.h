#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class Moment {

public:
	virtual void init(float FFOneTime) = 0;
	virtual bool updata(float dt) = 0;

	
};
