#pragma once
#include "cocos2d.h"
#include "FootMan.h"

class FootManTeam : public cocos2d::Node {
public:
	static FootManTeam* create(int teamId,std::vector<FootManProperty> provec);
	virtual bool init(int teamId, std::vector<FootManProperty> provec);
	int getTeamId();
	std::vector<FootMan*> getAllFootMan();
private:
	std::vector<FootMan*> footManVec;
	int teamId = 0;
	void createFootMan(std::vector<FootManProperty> provec);
};