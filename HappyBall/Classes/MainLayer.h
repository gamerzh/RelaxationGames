#pragma once
#include "cocos2d.h"

class  MainLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MainLayer);
private:
	void startGame();
};