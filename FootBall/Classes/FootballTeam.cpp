#include "FootballTeam.h"
#include "GameStatus.h"
USING_NS_CC;


FootballTeam* FootballTeam::create(int teamId) {
	auto team = new FootballTeam();
	if (team && team->init(teamId)) {
		//team->autorelease();
		//team->retain();//����һ�μ���,������Ϊû�����ӵ�����������
		return team;
	}
	else {
		CC_SAFE_DELETE(team);
		return NULL;
	}
}

bool FootballTeam::init(int teamid) {
	if (!Node::init()) {
		return false;
	}
	this->teamId = teamid;
	return true;
}


std::vector<FootMan*> FootballTeam::getFootManVector() {
	auto currentPlayerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(this->teamId);
	for (int i = 0; i < currentPlayerTeamProperty.footManVec.size(); i++) {
		auto var1 = currentPlayerTeamProperty.footManVec.at(i);
		auto foot1 = FootMan::create(var1);
		footManVector.push_back(foot1);
	}
	return footManVector;
}

void FootballTeam::setTeamInLeftField(bool b) {
	this->teamInLeftField = b;
}

std::vector<Vec2> FootballTeam::getLeftFieldVec2() {
	std::vector<Vec2> left;
	return left;
}

std::vector<Vec2> FootballTeam::getRightFieldVec2() {
	std::vector<Vec2> right;
	return right;
}