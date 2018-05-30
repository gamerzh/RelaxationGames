#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class Brick : public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(Brick);
	void setFrameIndex(int current);
	int getFrameIndex();
private:
	cocostudio::timeline::ActionTimeline* heroTimeLine;
	void loadBrickFile();
	void update(float dt);
};