#pragma once
#include "cocos2d.h"
#include "FootManTeam.h"

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	float gameTime = 60;//”Œœ∑ ±º‰
	float passTime = 0;
	const float timestep = 0.1f;
	FootManTeam* currentPlayerTeamId = nullptr;
	FootManTeam* currentComputerTeamId = nullptr;
	void update(float dt);
	FootManTeam* getFootManTeamById(int id);
};