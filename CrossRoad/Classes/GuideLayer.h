#pragma once
#include "cocos2d.h"
USING_NS_CC;

class  GuideLayer : public Layer {
public:
	virtual bool init();
	CREATE_FUNC(GuideLayer);
private:
	void closeView();
};