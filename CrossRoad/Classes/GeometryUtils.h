#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GeometryUtils : public Ref {
public:
	static bool intersectsRect(const Rect& rect1, const Rect& rect2);

};