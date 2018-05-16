#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GeometryUtils : public Ref {
public:
	static bool intersectsRect(const Rect& rect1, const Rect& rect2);//修改过得碰撞
	static Vec2 transitionPlayerVec2(Vec2 vec);//玩家配置的坐标转换到标准棋盘
	static Vec2 transitionObjectVec2(Vec2 vec, int index);//障碍物配置的坐标转换到标准棋盘
	static Size transitionObjectSize(Size vec);//障碍物配置的大小转换到标准棋盘
	static float randomFloat(float a, float b);
};