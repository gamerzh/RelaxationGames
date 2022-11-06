#pragma once
#include "cocos2d.h"
USING_NS_CC;

class RulePanel : public Node
{
public:
	CREATE_FUNC(RulePanel);

	void showPanel();
	void hidePanel();
	

private:
	bool init();
	EventListenerTouchOneByOne* listenr1;
	float time = 0.2f;
};
