#pragma once

#include "cocos2d.h"
USING_NS_CC;
//玩家类,支持多种皮肤和特性
class Player : public cocos2d::Sprite {
public:
	CREATE_FUNC(Player);
	virtual bool init();
	//玩家操作
	void playerJumpStraight();
	void playerJumpLeft();
	void playerJumpRight();
	Point getPlayerPoint();
private:
	void update(float dt);
};