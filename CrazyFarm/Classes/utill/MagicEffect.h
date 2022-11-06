#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MagicEffect :public Sprite
{
	public:
	virtual bool init(const int lightID ,bool isBottomRorato);
	static MagicEffect * create(const int lightID, bool isBottomRorato);
};




