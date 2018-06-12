#include "FootManTeam.h"
USING_NS_CC;
using namespace std;

FootManTeam* FootManTeam::create(FootManTeamProperty teampro)
{
	FootManTeam *ret = new FootManTeam();
	if (ret && ret->init(teampro))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FootManTeam::init(FootManTeamProperty teampro) {
	if (!Layer::init()) {
		return false;
	}
	this->teamId = teampro.teamId;
	createFootMan(teampro.footManVec);
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