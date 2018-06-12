#pragma once
#include "cocos2d.h"

/*
�����������Ϣ
*/
struct FootManProperty {
	std::string footImage;
	std::string name;
	float runSpeed;
	int skillType;
	bool goalkeeper;
};

struct FootManTeamProperty {
	int teamId;//��ӱ��
	std::string teamName;//�������
	std::string teamBanner;//�������
	std::vector<FootManProperty> footManVec;//��Ա�����б�
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
	float runSpeed = 0;//��ɫ�ı����ٶ�
	std::string foot_man_img;
	int foot_man_skill_type = 0;
	bool goalkeeper = false;
};