#ifndef __GAME_GUI_LAYER_H__
#define __GAME_GUI_LAYER_H__
#include "cocos2d.h"
#include "domain/room/RoomManager.h"
#include "utill/define.h"
#include "utill/SkillButton.h"
#include "utill/AnimationUtil.h"
#include "utill/Audio.h"
#include "lobby/LobbyScene.h"
#include "domain/user/User.h"
#include "domain/skill/SkillFreezeButton.h"
#include "domain/skill/SkillSummonButton.h"
#include "domain/skill/SkillLightButton.h"
#include "domain/skill/SkillLockButton.h"
#include "domain/skill/SkillBombButton.h"
#include "widget/MyMenuItemUpgrade.h"
#include "core/SettingDialog.h"
#include "core/NotarizeExitDialog.h"
#include "domain/nobility/NobilityManager.h"
#include "core/GuizuGiftDialog.h"
#include "widget/MyMenuItemGainMoney.h"
#include "data/GameData.h"
#include "core/maridTaskPlane.h"
#include "domain/skill/skillManager.h"
#include "server/HttpMannger.h"
#include "utill/Audio.h"
#include "data/GameData.h"

USING_NS_CC;




class GameGuiLayer: public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameGuiLayer);
	void refreshSkillNum();
	void ShowUseLockTip(Point dmDropPos);
	void ShowUpgradeTurretTip();
	void setLayerAlpha(int alpha);

	Vec2 getItemPos(int itemid);//展示道具飞入时候需要
private :
	void showRandonBubbleAni();
	void exitCallback(Ref *pSender);
	void settingCallback(Ref *pSender);
	void showFishCallback(Ref *pSender);
	void showSettingCallback(Ref*pSender);
	void addCoinCallBack(Ref*psend);
	void createSettingBoard();
	void createGuizuGiftLayer();
	

	/////////美人鱼相关///////////////////////////////////////////////
	float fmaridNowTime = 0;
	void maridTaskTime(float dt);
	void createMermaidTaskPlane();

public:
	void beginMaridTaskTime(float diffTime);

	void showLockUpgradeTurret();

	void onBossWarning(int fishID);

	void showGainMoneyTurrent();
	
	void anastole();
private:
	////
	//播放真人声音
	void update(float delta);
	void playRandVoice(float dt);
	virtual void onExit();
	MenuItemImage* setttingBoard;
	MyMenuItemGainMoney* sEainCoin;
	MyMenuItemUpgrade* sUpgradeTurret;
	LayerColor*colorBg;
	 
};
#endif