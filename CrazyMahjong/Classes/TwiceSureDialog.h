#pragma once
#include "cocos2d.h"
#include "ChineseWorld.h"
USING_NS_CC;



class TwiceSureDialog : public Layer
{
public:
	static TwiceSureDialog* createDialog(const char* tipStr, const ccMenuCallback& surecallback = nullptr);
	void setCloseButtonCallback(const ccMenuCallback& closecallback);
	void setSureButtonCallback(const ccMenuCallback& surecallback);
private:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void closeButtonCallBack(Ref*psend);
	virtual bool init(const char* tipStr, const ccMenuCallback& callback);
	MenuItemImage* close;
	MenuItemImage*sure;
	LayerColor*colorLayer;

};

