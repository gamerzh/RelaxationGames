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


class TeamFactory : public cocos2d::Ref {
public:
	static  TeamFactory* getInstance();
	FootManTeamProperty getTeamPropertyById(int teamId);
private:
	static  TeamFactory* m_instance;
	TeamFactory() {};
	std::vector<FootManTeamProperty> footManTeamPropertyVec;
	std::vector<FootManTeamProperty> getFootManTeamPropertyVector();//球队信息列表
};