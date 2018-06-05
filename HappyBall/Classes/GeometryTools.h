#pragma once
#include "cocos2d.h"

struct AngeleRange
{
	int startAngle; 
	int endAngle;
};

class GeometryTools {
public:
	static cocos2d::DrawNode* drawCollisionBox(cocos2d::Rect rect  );
	static cocos2d::DrawNode* drawCollisionCircle(cocos2d::Vec2 point,float radius);
	static bool angleCollision(AngeleRange origin, AngeleRange current);
}; 
