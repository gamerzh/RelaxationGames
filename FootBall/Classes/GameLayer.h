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
	void createFootballFild();//绘制足球场
	//void createFootBallTeam();//添加2个队伍
	Ball* footBall = nullptr;
	Rocker* heroRocker = nullptr;
	cocos2d::Camera* playerCamera;
	//FootManTeamProperty currentPlayerTeamProperty;
	//FootManTeamProperty currentComputerTeamProperty;
	//std::vector<FootMan*> currentPlayerTeam;
	//std::vector<FootMan*> currentComputerTeam;
	//FootMan* currentFootMan = nullptr;//玩家控制的球员
	//FootMan* currentControlFootMan = nullptr;//当前控球的队员
	void onEnter();
	void onExit();
	float calculateDistance(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	void passAndTackle();//传球和抢断
	void shoot();//射门
	void manLootBall();//球员争抢足球
	void speedMan();
	void loadGameLayerUI();
	void addCustomEvent();
	void removeCustomEvent();
	void update(float dt);
};