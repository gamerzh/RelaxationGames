#pragma once
#include "cocos2d.h"
#include "ChangeGiftCell.h"
#include "widget/BaseLayer.h"
USING_NS_CC;






class ChangeGiftLayer : public BaseLayer
{
public:

    virtual bool init();

	CREATE_FUNC(ChangeGiftLayer);
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void  onTouchMoved(Touch *touch, Event *unused_event);
	void  onTouchEnded(Touch *touch, Event *unused_event);
private:
	
	void closeButtonCallBack(Ref*psend);
	ChangeGiftCell *cell1;
	ChangeGiftCell *cell2;
	ChangeGiftCell *cell3;
};
