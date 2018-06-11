#pragma once
#include "cocos2d.h"
#include "FootMan.h"

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

class FootManTeam : public cocos2d::Ref {
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