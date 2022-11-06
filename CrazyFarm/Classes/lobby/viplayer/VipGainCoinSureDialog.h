#pragma once
#include "cocos2d.h"
USING_NS_CC;
class VipGainCoinSureDialog : public Layer
{
protected:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void showRandonBubbleAni();
	void sureButtonCallBack(Ref*psend);
	virtual bool init();
public:
	
	CREATE_FUNC(VipGainCoinSureDialog);
	CC_SYNTHESIZE(int, m_seqDay, seqDay);
};

