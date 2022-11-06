#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyDialog : public Layer
{
public:
	CREATE_FUNC(MyDialog);
	virtual bool init();
protected:
	void showRandonBubbleAni();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
};

