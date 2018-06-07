#pragma once
#include "cocos2d.h"
#include "FootMan.h"

class Hero : public FootMan {
public:
	virtual bool init();
	CREATE_FUNC(Hero);
};