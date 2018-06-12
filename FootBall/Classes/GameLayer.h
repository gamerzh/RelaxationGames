#pragma once
#include "cocos2d.h"
#include "FootManTeam.h"

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	float gameTime = 60;//游戏时间
	float passTime = 0;
	const float timestep = 0.1f;
	FootManTeam* currentPlayerTeam = nullptr;
	FootManTeam* currentComputerTeam = nullptr;
	void update(float dt);
	FootManTeam* getFootManTeamById(int id);
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();//球队信息列表
};