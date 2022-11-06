#pragma once
#include "cocos2d.h"
USING_NS_CC;
class NewbieSureDialog : public Layer
{
protected:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void closeButtonCallBack(Ref*psend);
	void sureButtonCallBack(Ref*psend);
	virtual bool init();
public:
	
	CREATE_FUNC(NewbieSureDialog)
};

