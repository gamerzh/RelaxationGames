#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
#include "config/ConfigItem.h"
USING_NS_CC;





class ShowSkillLayer : public cocos2d::Layer
{
public:

    virtual bool init(int itemId);

	static ShowSkillLayer*create(int itemId);


private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	void LackVipCallBack(Ref*psend);
	void LackTurrentCallBack(Ref*psend);
	void satisfyCallBack(Ref*psend);
	void closeButtonCallBack(Ref*psend);
	Item Iitem;
	int m_itemId;
};
