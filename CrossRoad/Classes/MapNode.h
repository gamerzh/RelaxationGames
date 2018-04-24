#pragma once
#include "cocos2d.h"
USING_NS_CC;

//地图模块,内容可以替换

class MapNode : public Node {
 
public:
	static MapNode* create(Point pos);
	virtual bool init(Point pos);
};