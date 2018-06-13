#pragma once
#include "cocos2d.h"
#include "FootMan.h"

#define ball_is_free 0 //����Ա���Ա���
#define ball_is_ower 1 //��������һ����Ա����
#define owner_ball_max_dis 50 //��ȡ��Ȩ��������

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