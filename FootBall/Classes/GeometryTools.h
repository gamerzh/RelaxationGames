#pragma once
#include "cocos2d.h"


class GeometryTools {
public:
	static cocos2d::DrawNode* drawCollisionBox(cocos2d::Rect rect  );
	static cocos2d::DrawNode* drawCollisionCircle(cocos2d::Vec2 point,float radius);
    static float calculateDistance(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
    static float calculateDistanceX(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
    static float calculateDistanceY(cocos2d::Vec2 p1, cocos2d::Vec2 p2);
    static float getPositionXByYLeft(float y);
    static float getPositionXByYRight(float y);
}; 