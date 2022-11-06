#pragma once

#include "cocos2d.h"

USING_NS_CC;
class TurntableCell : public Sprite
{
public:
	virtual bool init(const char*path,int propNum);
	static TurntableCell* create(const char*path, int propNum);

};
