#pragma once
#include "cocos2d.h"
#include "FootManTeam.h"





class TeamFactory : public cocos2d::Ref {
public:
	static  TeamFactory* getInstance();
	std::vector<FootManTeam*> getFootManTeamVector();
private:
	static  TeamFactory* m_instance;
	TeamFactory() {};
	std::vector<FootManTeam*> footTeamVec;
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();//球队信息列表
};