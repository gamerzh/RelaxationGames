#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "TeamInfoFactory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define ANIMATION_SCALE_RATE 0.4

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
	void setTargetPosition(cocos2d::Vec2 pos);
	cocos2d::Point getTargetPosition();
private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Point targetPosition;
	cocos2d::Node* playerCsb;
	Ball * footBall = nullptr;//球员的持球
	cocos2d::Camera* ball_camera = nullptr;
	float runSpeed = 0;//角色的奔跑速度
	std::string foot_man_img;
	int foot_man_skill_type = 0;
	cocos2d::Point moveInSafeRect(cocos2d::Point pos);
	float getPositionXByYLeft(float y);
	float getPositionXByYRight(float y);
	bool goalkeeper = false;
	void moveRight();
	void moveLeft();
	void playFootManRun();
	void playFootManTackle();
	void playFootManShoot();
	void update(float dt);
};