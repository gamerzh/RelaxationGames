#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
USING_NS_CC;
class TwiceSureDialog : public Layer
{
protected:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void closeButtonCallBack(Ref*psend);
	MenuItemImage* close;
	MenuItemImage*sure;
	LayerColor*colorLayer;
public:
	static TwiceSureDialog* createDialog(const char* tipStr, const ccMenuCallback& surecallback = nullptr);
	void setCloseButtonCallback(const ccMenuCallback& closecallback);
	virtual bool init(const char* tipStr, const ccMenuCallback& callback);
	void showRandonBubbleAni();
};

