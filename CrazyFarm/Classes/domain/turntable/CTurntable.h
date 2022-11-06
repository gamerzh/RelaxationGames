#pragma once
#include "cocos2d.h"
#include "domain/bonuspool/BonusPoolManager.h"
USING_NS_CC;


class CTurntable : public cocos2d::Sprite
{
public:
    virtual bool init();  
    
    // a selector callback
	void menuButtonCallbackStop();
    
	void menuButtonCallback(Ref* pSender);

	CREATE_FUNC(CTurntable);
    
private:
	int curPos;
    Sprite* pSprite_circle;
    MenuItemImage *m_menuBegin;
	BonuspoolRewardItem reward;
	BonuspoolResult result;
	float angle[8];
};

