#pragma once
#include "cocos2d.h"
#include "GeometryTools.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define CIRCLE_DIVISION_NUMBER 10 //Բ������



class Brick : public cocos2d::Sprite {
public:
	static Brick* create(int frame = 0);
	virtual bool init(int frame = 0);
	void setFrameIndex(int current);
	int getFrameIndex();
	//cocos2d::Rect getCollisionRect();
	AngeleRange getOutAngle();//��ȡȥ����һ��ĽǶ�
	std::vector<AngeleRange> getOutAnglesByFrameIndex(int index);
	std::vector<AngeleRange> getDangousAnglesByFrameIndex(int index);
private:
	cocostudio::timeline::ActionTimeline* heroTimeLine;
	void loadBrickFile();
	void update(float dt);
};