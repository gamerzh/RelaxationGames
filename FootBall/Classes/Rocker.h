#pragma once
#include "cocos2d.h"

#define ROCKER_NACKGROUMD_TAG  100
#define ROCKER_CONTENT_TAG  101

class Rocker :public cocos2d::Node {
public:
	static Rocker* create(cocos2d::Vec2 pos);	
	bool init(cocos2d::Vec2 pos);
	void openRocker();
	void closeRocker(bool isVisible);
	float getRockerAngle();
private:
	float rockerAngle;
	float rockerRad;
	cocos2d::Vec2 bgCenter;
	cocos2d::Vec2 getPosByAngle(float r, float angle);
	float calculateAngle(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
};
