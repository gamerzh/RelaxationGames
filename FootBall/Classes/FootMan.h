#pragma once
#include "cocos2d.h"

class FootMan : public cocos2d::Node {
public:
	static FootMan* create(cocos2d::Camera* camera = nullptr);
	virtual bool init(cocos2d::Camera* camera);
	void setFootManAngle(float angle);
	void setSlideTackle();
	void setShoot();
private:
	cocos2d::Camera* ball_camera = nullptr;
	float runSpeed = 0;//��ɫ�ı����ٶ�
	std::string foot_man_img;
	int foot_man_skill_type;
};