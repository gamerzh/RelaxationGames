#pragma once
#include "cocos2d.h"
USING_NS_CC;

//��ͼģ��,���ݿ����滻

class MapNode : public Node {
 
public:
	static MapNode* create(Point pos);
	virtual bool init(Point pos);
};