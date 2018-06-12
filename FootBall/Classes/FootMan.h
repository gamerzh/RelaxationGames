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

class FootMan : public cocos2d::Node {
public:
	static FootMan* create(FootManProperty property,cocos2d::Camera* camera = nullptr);
	virtual bool init(FootManProperty property, cocos2d::Camera* camera);
	void setFootManAngle(float angle);
	void setSlideTackle();
	void setShoot();
	bool isGoalkeeper();
private:
	cocos2d::Camera* ball_camera = nullptr;
	float runSpeed = 0;//角色的奔跑速度
	std::string foot_man_img;
	int foot_man_skill_type = 0;
	bool goalkeeper = false;
};