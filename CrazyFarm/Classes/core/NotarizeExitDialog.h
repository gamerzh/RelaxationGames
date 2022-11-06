#pragma once
#include "cocos2d.h"
#include "widget/MyDialog.h"
USING_NS_CC;
class NotarizeExitDialog : public Layer
{
public:
	CREATE_FUNC(NotarizeExitDialog);
	virtual bool init();
protected:
	void querenCallback(Ref*psend);
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void showRandonBubbleAni();
};

