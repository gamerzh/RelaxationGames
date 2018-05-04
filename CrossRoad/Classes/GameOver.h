#pragma once
#include "cocos2d.h"
USING_NS_CC;


class GameOver : public Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameOver);
	void closeView();
};