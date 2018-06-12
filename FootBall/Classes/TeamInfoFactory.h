#pragma once
#include "cocos2d.h"

/*
足球队配置信息
*/
struct FootManProperty {
	std::string footImage;
	std::string name;
	float runSpeed;
	int skillType;
	bool goalkeeper;
};

struct FootManTeamProperty {
	int teamId;//球队编号
	std::string teamName;//球队名称
	std::string teamBanner;//球队旗帜
	std::vector<FootManProperty> footManVec;//队员属性列表
};


class TeamInfoFactory : public cocos2d::Ref {
public:
	static  TeamInfoFactory* getInstance();
	FootManTeamProperty getTeamPropertyById(int teamId);
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();//球队信息列表
private:
	static  TeamInfoFactory* m_instance;
	TeamInfoFactory() {};
	std::vector<FootManTeamProperty> footManTeamPropertyVec;
};