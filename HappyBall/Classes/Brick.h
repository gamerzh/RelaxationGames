#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class Brick : public cocos2d::Sprite {
public:
	static Brick* create(int frame = 0);
	virtual bool init(int frame = 0);
	void setFrameIndex(int current);
	int getFrameIndex();
	cocos2d::Rect getCollisionRect();
private:
	cocostudio::timeline::ActionTimeline* heroTimeLine;
	void loadBrickFile();
	void update(float dt);
};