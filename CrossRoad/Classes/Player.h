#pragma once

#include "cocos2d.h"
USING_NS_CC;
//�����,֧�ֶ���Ƥ��������
class Player : public cocos2d::Sprite {
public:
	CREATE_FUNC(Player);
	virtual bool init();
	//��Ҳ���
	void playerJumpStraight();
	void playerJumpLeft();
	void playerJumpRight();
	Point getPlayerPoint();
private:
	void update(float dt);
};