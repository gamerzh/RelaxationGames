#pragma once

#include "cocos2d.h"

USING_NS_CC;
class GiftCell : public Sprite
{
public:
	virtual bool init(int propID, int propNum);
	static GiftCell* create(int propID, int propNum);

};
