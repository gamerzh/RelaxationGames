#pragma once
#include "cocos2d.h"
#include "TeamInfoFactory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define ANIMATION_SCALE_RATE 0.4
#define FOOTBALL_MAN_ZORDER 5000

//foot man state
enum FootManState{
    waiting,
    running,
    shoot,
    tackle
};

class FootMan : public cocos2d::Node {
public:
	static FootMan* create(FootManProperty property,cocos2d::Camera* camera = nullptr);
	virtual bool init(FootManProperty property, cocos2d::Camera* camera);
    int getFootManTeamId();
    void setFootManTeamId(int id);
	void setFootManAngle(float angle);
    void doSlideTackle();
	void doShoot();
	bool isGoalkeeper();
	float getShootSpeed();
    void moveRight();
    void moveLeft();
    FootManState getFootManState();
    void changeFootManState(FootManState state);
private:
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Point targetPosition;
	cocos2d::Node* playerCsb;
	cocos2d::Camera* ball_camera = nullptr;
    FootManState manState;
    int belongTeamId = 0;
	float runSpeed = 0;
	std::string foot_man_img;
	int foot_man_skill_type = 0;
	cocos2d::Point moveInSafeRect(cocos2d::Point pos);
	float getPositionXByYLeft(float y);
	float getPositionXByYRight(float y);
	bool goalkeeper = false;
	void updateFootManZorder();
	void showDebugInfo();
	void update(float dt);
    void playFootManRun();
    void playFootManTackle();
    void playFootManShoot();
    void playFootManStand();
};
