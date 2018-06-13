#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Rocker.h"
#include "FootMan.h"
#include "TeamInfoFactory.h"


class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	float gameTime = 60;//游戏时间
	float passTime = 0;
	const float timestep = 0.1f;
	Ball* footBall = nullptr;
	Rocker* heroRocker = nullptr;
	FootManTeamProperty currentPlayerTeamProperty;
	FootManTeamProperty currentComputerTeamProperty;
	std::vector<FootMan*> currentPlayerTeam;
	std::vector<FootMan*> currentComputerTeam;
	float calculateDistance(cocos2d::Vec2 p1,cocos2d::Vec2 p2);
	void passAndTackle();//传球和抢断
	void shoot();//射门
	void ballFindOwner();
	void loadGameLayerUI();
	void update(float dt);
};