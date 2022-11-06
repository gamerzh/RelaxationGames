#pragma once
#include "cocos2d.h"
#include "domain/bonuspool/BonusPoolManager.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class  CTurntable;
class TurnTableDialog : public Layer
{
public:
	CREATE_FUNC(TurnTableDialog);
	virtual bool init();
	void onGetRewards(BonuspoolRewardItem reward);
	void createBottomFrame(bool isFinish);
protected:
	void closeButtonCallBack(Ref*psend);
	void choujiangButtonCallBack(Ref*psend);
	void beginChoujiangButtonCallBack(Ref*psend);
	void showGoldFishButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent){ return true; };
	CTurntable*table;
	LoadingBar* bar;
	LabelAtlas* labelNowCoin;
};

