#pragma once

#include "cocos2d.h"
#include "core/GameLayer.h"
#include "core/GameGuiLayer.h"
using namespace cocos2d;


class GameManage {
public:
	static GameManage* getInstance();
	void setGuilayer(GameGuiLayer* guilayer){ m_pGuilayer = guilayer; };
	void  setGameyer(GameLayer* layer){ m_pGameyer = layer; };

	GameGuiLayer* getGuiLayer(){
		return m_pGuilayer;
	}
	GameLayer* getGameLayer(){
		return m_pGameyer;
	}

	//升级
	void onPlayerUpgrade();
	
	//弹出钻石
	void showLockTurrent();
	//弹出抽奖
	void showGainMoneyTurrent();
	//某塔捕获某鱼
	void CatchTheFishOntheTurrent(Fish*fish, bool isDead, PlayerTurret* turret); 
	//某塔破产生成破产宝箱
	void onBrokeBySomeTurret(PlayerTurret*turret,int lefttime,float waittime);
	//领取破产宝箱
	void onRebirthBySomeTurret(int reward_coins);

private :
	GameManage();
	static GameManage* _instance;
	GameGuiLayer* m_pGuilayer = nullptr;
	GameLayer*m_pGameyer= nullptr;
 };
