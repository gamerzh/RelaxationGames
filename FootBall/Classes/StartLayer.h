#pragma once
#include "cocos2d.h"

class StartLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(StartLayer);
private:
	void startGame();
};