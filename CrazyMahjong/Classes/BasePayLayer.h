#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "PayDefine.h"
USING_NS_CC;
using namespace ui;


class BasePayLayer :public cocos2d::Layer
{
public:
	static BasePayLayer*create(PAYPOINT paypoint);
private:
	virtual bool init(PAYPOINT paypoint);
	void quedingButton(Ref* pSender, TouchEventType type);
	void quxiaoButton(Ref* pSender, TouchEventType type);
private:
	CC_SYNTHESIZE(std::function<void(EventCustom*)>, _callback, PayCallBack);
	PAYPOINT _paypoint;
};

