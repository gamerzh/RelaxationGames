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
	void setBallShoot(int  speed);//������
	void setOwnerMan(FootMan* owern);
	FootMan* getOwerMan();
private:
	cocos2d::Camera* myCamera = nullptr;
	FootMan* ballOwner = nullptr;
	void update(float dt);
	void setBallState(int state);
	int ballState = ball_is_free;//
	cocos2d::Point cameraMoveInRect(cocos2d::Point pos);
};