#pragma once
#include "cocos2d.h"

struct FootManProperty {
	std::string footImage;
	std::string name;
	float runSpeed;
	int skillType;
	bool goalkeeper;
};

struct FootManTeamProperty {
	int teamId;
	std::string teamName;
	std::string teamBanner;
	std::vector<FootManProperty> footManVec;
};


class TeamInfoFactory : public cocos2d::Ref {
public:
	static  TeamInfoFactory* getInstance();
	FootManTeamProperty getTeamPropertyById(int teamId);
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();
private:
	static  TeamInfoFactory* m_instance;
	TeamInfoFactory() {};
	std::vector<FootManTeamProperty> footManTeamPropertyVec;
};
