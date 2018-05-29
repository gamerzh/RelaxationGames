#pragma once
#include "cocos2d.h"


class Brick : public cocos2d::Node {
public:
	virtual bool init();
	CREATE_FUNC(Brick);
private:
	void loadBrickFile();
};