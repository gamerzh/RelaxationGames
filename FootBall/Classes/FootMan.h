#pragma once
#include "cocos2d.h"
#include "TeamInfoFactory.h"
#include "Ball.h"


class FootMan : public cocos2d::Node {
public:
	static FootMan* create(FootManProperty property,cocos2d::Camera* camera = nullptr);
	virtual bool init(FootManProperty property, cocos2d::Camera* camera);
	void setFootManAngle(float angle);
	void doSlideTackle();//滑铲和传球
	void doShoot();//射门
	bool isGoalkeeper();
	bool isLootBall();
	void setFootManLootBall(Ball* ball);
private:
	Ball * footBall = nullptr;//球员的持球
	cocos2d::Camera* ball_camera = nullptr;
	float runSpeed = 0;//角色的奔跑速度
	std::string foot_man_img;
	int foot_man_skill_type = 0;
	bool goalkeeper = false;
	void update(float dt);
};