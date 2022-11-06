#pragma once
#include "cocos2d.h"
#include "utill/Chinese.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC_EXT;
using namespace cocos2d::ui;
USING_NS_CC;
class TwiceSkillSureDialog : public Layer
{
protected:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void closeButtonCallBack(Ref*psend);
	void sureButtonCallBack(Ref*psend);
	MenuItemImage* close;
	MenuItemImage*sure;
	void selectedEvent(Ref* pSender, CheckBox::EventType type);
	CC_SYNTHESIZE(int, m_skiilid, SkillId);
public:
	static TwiceSkillSureDialog* createDialog();
	void setCloseButtonCallback(const ccMenuCallback& closecallback);
	void ToPayShopCallBack(Ref*psend);
	virtual bool init();
	void showRandonBubbleAni();
};

