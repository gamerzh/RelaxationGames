#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GeometryUtils : public Ref {
public:
	static bool intersectsRect(const Rect& rect1, const Rect& rect2);//�޸Ĺ�����ײ
	static Vec2 transitionPlayerVec2(Vec2 vec);//������õ�����ת������׼����
	static Vec2 transitionObjectVec2(Vec2 vec, int index);//�ϰ������õ�����ת������׼����
	static Size transitionObjectSize(Size vec);//�ϰ������õĴ�Сת������׼����
	static float randomFloat(float a, float b);
};