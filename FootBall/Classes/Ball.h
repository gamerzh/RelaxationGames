#pragma once
#include "cocos2d.h"
#include "FootMan.h"

#define ball_is_free 0 //球可以被球员获得
#define ball_is_ower 1 //球在其中一个球员手里
#define owner_ball_max_dis 50 //获取球权的最大距离

class Ball : public cocos2d::Sprite
{
public:
	static Ball* create(cocos2d::Camera* camera);
	virtual bool init(cocos2d::Camera* camera);
	int getBallState();
	void setBallState(int state);
	void setOwnerMan(FootMan* owern);
private:
	cocos2d::Camera* myCamera = nullptr;
	FootMan* ballOwner = nullptr;
	void update(float dt);
	int ballState = ball_is_free;//
};