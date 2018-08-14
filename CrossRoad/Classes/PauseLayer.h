#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PauseLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);
private:
	void initView();
	void goBackHome();
	void gameResart();
	void continueGame();
};