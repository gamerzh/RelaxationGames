#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Rocker.h"
#include "FootMan.h"
#include "TeamInfoFactory.h"

#define FOOTBALL_LOCAL_ZORDER 10

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	void createFootballFild();//��������
	Ball* footBall = nullptr;
	Rocker* heroRocker = nullptr;
	cocos2d::Camera* playerCamera;
	FootManTeamProperty currentPlayerTeamProperty;
	FootManTeamProperty currentComputerTeamProperty;
	std::vector<FootMan*> currentPlayerTeam;
	std::vector<FootMan*> currentComputerTeam;
	FootMan* currentFootMan = nullptr;
	float calculateDistance(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
	void passAndTackle();//���������
	void shoot();//����
	void manLootBall();//��Ա��������
	void speedMan();
	void loadGameLayerUI();
	void update(float dt);
};