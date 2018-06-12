#pragma once
#include "cocos2d.h"
#include "FootMan.h"
#include "TeamInfoFactory.h"

class GameLayer : public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
private:
	float gameTime = 60;//”Œœ∑ ±º‰
	float passTime = 0;
	const float timestep = 0.1f;
	FootManTeamProperty currentPlayerTeamProperty;
	FootManTeamProperty currentComputerTeamProperty;
	std::vector<FootMan*> currentPlayerTeam;
	std::vector<FootMan*> currentComputerTeam;
	void update(float dt);
};