#pragma once
#include "cocos2d.h"

#define ROCKER_NACKGROUMD_TAG  100
#define ROCKER_CONTENT_TAG  101

class Rocker :public cocos2d::Node {
public:
	static Rocker* create(cocos2d::Vec2 pos);	
	bool init(cocos2d::Vec2 pos);//初始摇杆中心位置
	void openRocker();//开启摇杆
	void closeRocker(bool isVisible);//关闭摇杆
	float getRockerAngle();//返回摇杆的角度
private:
	float rockerAngle;//摇杆的状态
	float rockerRad;//摇杆范围
	cocos2d::Vec2 bgCenter;	//摇杆背景图的中心
	cocos2d::Vec2 getPosByAngle(float r, float angle);//根据角度和半径获得坐标
	float calculateAngle(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);//得到两点间的角度
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
};