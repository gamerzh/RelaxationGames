#pragma once
#include "cocos2d.h"
#include "NobilityLayer.h"
#include "utill/FunUtil.h"
#include "widget/BaseLayer.h"
USING_NS_CC;

class NobilityLayer : public BaseLayer
{
public:
	virtual bool init();
	static NobilityLayer * createLayer();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void updata(float dt);
private:
	void quickPayCallback(Ref* psend);
	void closeButtonCallBack(Ref*psend);
	LabelAtlas* dayTTF;
	MenuItemImage* quickpay;
	CC_SYNTHESIZE(int, m_eventPoint, EventPoint);
	unsigned long lastTouchTime;
};

