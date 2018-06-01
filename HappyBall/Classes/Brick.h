#pragma once
#include "cocos2d.h"
#include "GeometryTools.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define CIRCLE_DIVISION_NUMBER 10 //圆划分数



class Brick : public cocos2d::Sprite {
public:
	static Brick* create(int frame = 0);
	virtual bool init(int frame = 0);
	void setFrameIndex(int current);
	int getFrameIndex();
	//cocos2d::Rect getCollisionRect();
	AngeleRange getOutAngle();//获取去往下一层的角度
	std::vector<AngeleRange> getOutAnglesByFrameIndex(int index);
	std::vector<AngeleRange> getDangousAnglesByFrameIndex(int index);
private:
	cocostudio::timeline::ActionTimeline* heroTimeLine;
	void loadBrickFile();
	void update(float dt);
};