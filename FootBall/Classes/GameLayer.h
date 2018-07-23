#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Rocker.h"
#include "FootMan.h"
#include "TeamInfoFactory.h"
#include "FootballTeam.h"

#define FOOTBALL_LOCAL_ZORDER 10

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	void createFootballFild();
	void createFootBallTeam();
	Ball* footBall = nullptr;
	Rocker* heroRocker = nullptr;
	cocos2d::Camera* playerCamera;
	FootballTeam* playerTeam;
	FootballTeam* computerTeam;
    FootMan* currentControlFootMan;//玩家队伍目前的控球人员
	void onEnter();
	void onExit();
	void passAndTackle();
	void shoot();
	void manLootBall();
	void speedMan();
	void loadGameLayerUI();
	void addCustomEvent();
	void removeCustomEvent();
    bool checkFootManInShootArea(FootMan* man);//检查球员是否进入射门区域
	void update(float dt);
};
