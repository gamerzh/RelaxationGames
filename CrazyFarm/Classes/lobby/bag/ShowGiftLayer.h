#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
#include "config/ConfigItem.h"
#include "lobby/signlayer/SignCell.h"
#include "widget/GiftCell.h"
USING_NS_CC;

class ShowGiftLayer : public cocos2d::Layer
{
public:

    virtual bool init();

	static ShowGiftLayer*create();


private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	void closeButtonCallBack(Ref*psend);
	Item Iitem;
	int m_itemId;
};
