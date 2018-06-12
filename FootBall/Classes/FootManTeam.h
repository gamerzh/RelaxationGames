#pragma once
#include "cocos2d.h"
#include "FootMan.h"
#include "TeamInfoFactory.h"

class FootManTeam : public cocos2d::Layer {
public:
	static FootManTeam* create(FootManTeamProperty teampro);
	virtual bool init(FootManTeamProperty teampro);
	int getTeamId();
	std::vector<FootMan*> getAllFootMan();
private:
	std::vector<FootMan*> footManVec;
	int teamId = 0;
	void createFootMan(std::vector<FootManProperty> provec);
};