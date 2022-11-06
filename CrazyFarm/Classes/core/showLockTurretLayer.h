#pragma once
#include "cocos2d.h"
#include "core/showTurretCell.h"
USING_NS_CC;










class showLockTurretLayer : public Layer
{
public:
    virtual bool init(); 

	CREATE_FUNC(showLockTurretLayer);

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event){ return true; };
	void chankanCallBack(Ref*);
	void ButtonCallback(Ref* psend);

};
