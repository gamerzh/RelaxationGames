#pragma once
#include "cocos2d.h"
#include "config/ConfigExp.h"
USING_NS_CC;
class UpgradeSureDialog : public Layer
{
protected:
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	void sureButtonCallBack(Ref*psend);
	virtual bool init(std::vector<LevelRewardItem> levelRewardItems);
public:
	static UpgradeSureDialog*create(std::vector<LevelRewardItem> levelRewardItems);
	std::vector<LevelRewardItem> m_levelRewardItems;
	Vector<Sprite*> cells;
};

