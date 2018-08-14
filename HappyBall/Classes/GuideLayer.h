#pragma once
#include "cocos2d.h"

class GuideLayer : public cocos2d::Layer {

public:
	virtual bool init();
	CREATE_FUNC(GuideLayer);
private:
	void finishGuide();
};