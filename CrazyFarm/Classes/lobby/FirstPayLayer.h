#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
#include "widget/BaseLayer.h"
USING_NS_CC;





class FirstPayLayer : public BaseLayer
{
public:

    virtual bool init();

	CREATE_FUNC(FirstPayLayer);

private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	void closeButtonCallBack(Ref*psend);
	bool checkTheName(const char* name);
	CC_SYNTHESIZE(int, m_eventPoint, EventPoint);
};
