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
	std::vector<FootMan*> currentPlayerTeam;
	std::vector<FootMan*> currentComputerTeam;
	FootballTeam* playerTeam;
	FootballTeam* computerTeam;
	void onEnter();
	void onExit();
	float calculateDistance(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	void passAndTackle();
	void shoot();
	void manLootBall();
	void speedMan();
	void loadGameLayerUI();
	void addCustomEvent();
	void removeCustomEvent();
	void update(float dt);
};
