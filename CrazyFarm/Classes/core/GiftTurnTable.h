#pragma once
#include "cocos2d.h"
#include "core/showTurretCell.h"
USING_NS_CC;















class GiftTurnTable : public cocos2d::Layer
{
public:
    virtual bool init(); //type:1 vip��  type:2 ������

	static  GiftTurnTable*create();

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };

};
