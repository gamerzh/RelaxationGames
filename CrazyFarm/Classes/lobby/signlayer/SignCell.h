#pragma once

#include "cocos2d.h"

USING_NS_CC;
class SignCell : public Sprite
{
public:
	virtual bool init(int propID,int propNum);
	void setVipX2();
	static SignCell* create(int propID, int propNum);

};
