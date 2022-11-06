#pragma once
#include "cocos2d.h"
#include "moment/Moment.h"
using namespace cocos2d;

class MomentNine : public Moment {

public:
	virtual void init(float FFOneTime);
	virtual bool updata(float dt);
private:
	float nNowtime = 0;

};