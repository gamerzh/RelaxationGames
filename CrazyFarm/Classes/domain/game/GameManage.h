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

	//����
	void onPlayerUpgrade();
	
	//������ʯ
	void showLockTurrent();
	//�����齱
	void showGainMoneyTurrent();
	//ĳ������ĳ��
	void CatchTheFishOntheTurrent(Fish*fish, bool isDead, PlayerTurret* turret); 
	//ĳ���Ʋ������Ʋ�����
	void onBrokeBySomeTurret(PlayerTurret*turret,int lefttime,float waittime);
	//��ȡ�Ʋ�����
	void onRebirthBySomeTurret(int reward_coins);

private :
	GameManage();
	static GameManage* _instance;
	GameGuiLayer* m_pGuilayer = nullptr;
	GameLayer*m_pGameyer= nullptr;
 };
