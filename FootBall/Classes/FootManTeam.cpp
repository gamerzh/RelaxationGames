#include "FootManTeam.h"
USING_NS_CC;
using namespace std;

FootManTeam* FootManTeam::create(int teamId, std::vector<FootManProperty> provec)
{
	FootManTeam *ret = new FootManTeam();
	if (ret && ret->init(teamId, provec))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FootManTeam::init(int teamId, std::vector<FootManProperty> provec) {
	this->teamId = teamId;
	createFootMan(provec);
	return true;
}


int FootManTeam::getTeamId() {
	return this->teamId;
}

std::vector<FootMan*> FootManTeam::getAllFootMan() {
	return this->footManVec;
}

void FootManTeam::createFootMan(std::vector<FootManProperty> provec) {
	for (auto var : provec) {
		auto man = FootMan::create(var);
		addChild(man);
		footManVec.push_back(man);
	}
}